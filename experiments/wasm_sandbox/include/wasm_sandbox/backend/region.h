#pragma once

#include <snmalloc/backend/fixedglobalconfig.h>
#include <snmalloc/backend/standard_range.h>
#include <snmalloc/backend_helpers/backend_helpers.h>
#include <snmalloc/snmalloc.h>

using namespace snmalloc;

namespace sandbox
{
  namespace allocator
  {
    /**
     * A single fixed address range allocator configuration
     */
    template<SNMALLOC_CONCEPT(IsPAL) PAL = DefaultPal>
    class MultiRegionConfig final : public CommonConfig
    {
    public:
      using PagemapEntry = DefaultPagemapEntry;

    private:
      using ConcretePagemap =
        FlatPagemap<MIN_CHUNK_BITS, PagemapEntry, PAL, false>;

      using Pagemap = BasicPagemap<PAL, ConcretePagemap, PagemapEntry, false>;

      static inline FlagWord pagemap_init_lock{};

    public:
      class LocalState
      {
      public:
        using ObjectRange = Pipe<
          EmptyRange<>,
          LargeBuddyRange<bits::BITS - 1, bits::BITS - 1, Pagemap>,
          SmallBuddyRange>;

        // Dummy impl to keep concept happy.
        using Stats = Pipe<EmptyRange<>, StatsRange>;

      private:
        ObjectRange object_range;

        void ensure_pagemap_init()
        {
          auto& pagemap = Pagemap::concretePagemap;
          if (pagemap.is_initialised())
            return;

          FlagLock lock(pagemap_init_lock);

          if (pagemap.is_initialised())
            return;

          pagemap.init();
        }

      public:
        // This should not be called.
        using GlobalMetaRange = EmptyRange<>;

        // Where we get user allocations from.
        ObjectRange* get_object_range()
        {
          return &object_range;
        }

        // Where we get meta-data allocations from.
        ObjectRange& get_meta_range()
        {
          // Use the object range to service meta-data requests.
          return object_range;
        }

        LocalState(void* base, size_t size) : object_range()
        {
          // Ensure the communal pagemap is initialised.
          ensure_pagemap_init();

          // Notify that pagemap requires committed memory for this range.
          Pagemap::register_range(address_cast(base), size);

          // Fill the range owned by this region with memory.
          object_range.dealloc_range(
            capptr::Arena<void>::unsafe_from(base), size);
        }
      };

      using Backend = BackendAllocator<PAL, PagemapEntry, Pagemap, LocalState>;
      using Pal = PAL;

    private:
    public:
      constexpr static snmalloc::Flags Options{
        .IsQueueInline = true,
        .CoreAllocOwnsLocalState = false,
        .CoreAllocIsPoolAllocated = false,
        .LocalAllocSupportsLazyInit = false,
        .QueueHeadsAreTame = true,
        .HasDomesticate = false,
      };

      static void register_clean_up() {}
    };

    using CustomConfig = MultiRegionConfig<DefaultPal>;
    using FixedAlloc = LocalAllocator<CustomConfig>;
    using CoreAlloc = CoreAllocator<CustomConfig>;

    class Region
    {
    public:
      FixedAlloc alloc;

    private:
      CustomConfig::LocalState region_state;

      CoreAlloc core_alloc;

    public:
      Region(void* base, size_t size)
      : region_state(base, size),
        core_alloc(&alloc.get_local_cache(), &region_state)
      {
        // Bind the core_alloc into the region local allocator
        alloc.init(&core_alloc);
      }
    };

  } // namespace allocator.
} // namespace sandbox.
