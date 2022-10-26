#pragma once

#include <memory>
namespace sandbox {

template <std::size_t N, std::size_t... I, class Tp>
constexpr auto reverse_tuple_impl(std::index_sequence<I...>, Tp const &tp) {
  return std::make_tuple(std::get<N - 1 - I>(tp)...);
}

template <class Tp, std::size_t N = std::tuple_size<Tp>::value,
          class S = std::make_index_sequence<N>>
constexpr auto reverse_tuple(Tp const &tp) {
  return reverse_tuple_impl<N>(S(), tp);
}

namespace internal {
/**
 * Template that deduces the return type and argument types for a function
 * `signature<void(int, float)>::return_type` is `void` and
 * `signature<void(int, float)>::argument_type` is `std::tuple<int, float>`.
 */
template <typename T> struct signature;

/**
 * Specialisation for when the callee is a value.
 */
template <typename R, typename... Args> struct signature<R(Args...)> {
  /**
   * The return type of the function whose type is being extracted.
   */
  using return_type = R;

  /**
   * A tuple type containing all of the argument types of the function
   * whose type is being extracted.
   */
  using argument_type = std::tuple<Args...>;
};

/**
 * Specification for when the callee is a reference.
 */
template <typename R, typename... Args> struct signature<R (&)(Args...)> {
  /**
   * The return type of the function whose type is being extracted.
   */
  using return_type = R;

  /**
   * A tuple type containing all of the argument types of the function
   * whose type is being extracted.
   */
  using argument_type = std::tuple<Args...>;
};
} // namespace internal
} // namespace sandbox
