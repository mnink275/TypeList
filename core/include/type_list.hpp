#pragma once

#include <array>
#include <cstddef>
#include <type_traits>
#include <typeindex>

namespace ink {

namespace impl {

struct EmptyList;

}  // namespace impl

template <class... Types>
struct TypeList;

// TypeList types pack size
template <class TList>
struct Size;

template <class... Types>
struct Size<TypeList<Types...>> final {
  static constexpr auto kSize = sizeof...(Types);
};

template <class TList>
inline constexpr auto size_v = Size<TList>::kSize;

// Front type
template <class TList>
struct Front;

template <class FirstType, class... Others>
struct Front<TypeList<FirstType, Others...>> final {
  using FrontType = FirstType;
};

template <>
struct Front<TypeList<>> final {
  using FrontType = impl::EmptyList;
};

template <class TList>
using front_t = typename Front<TList>::FrontType;

// Back type
template <class TList>
struct Back;

template <class... Types>
struct Back<TypeList<Types...>> {
  // C++20 std::type_identity
  template <class T>
  struct TypeIdentity {
    using Type = T;
  };

  // 1) Fold-expression:
  //    E = (A<Args>{}, ...) --> (A<T1>{}, (..., (A<Tn - 1>{}, A<Tn>{})))
  // 2) decltype(E) == decltype(A<Tn>{}) == A<Tn>
  // 3) A<Tn>::Type == Tn
  using BackType = typename decltype((TypeIdentity<Types>{}, ...))::Type;
};

template <>
struct Back<TypeList<>> final {
  using BackType = impl::EmptyList;
};

template <class TList>
using back_t = typename Back<TList>::BackType;

// Pushing
template <class NewType, class TList>
struct Pusher;

template <class NewType, class... Types>
struct Pusher<NewType, TypeList<Types...>> final {
  using PushBackValue = TypeList<Types..., NewType>;
  using PushFrontValue = TypeList<NewType, Types...>;
};

template <class NewType, class TList>
using push_back_v = typename Pusher<NewType, TList>::PushBackValue;

template <class NewType, class TList>
using push_front_v = typename Pusher<NewType, TList>::PushFrontValue;

// Popping
template <class TList>
struct PopFront;

template <class FirstType, class... Others>
struct PopFront<TypeList<FirstType, Others...>> final {
  using PopFrontValue = TypeList<Others...>;
};

template <>
struct PopFront<TypeList<>> final {
  using PopFrontValue = TypeList<>;
};

template <class TList>
using pop_front_v = typename PopFront<TList>::PopFrontValue;

// At
template <std::size_t target_index, std::size_t curr_inex, class TList>
struct AtImpl {
  using Type =
      typename AtImpl<target_index, curr_inex + 1, pop_front_v<TList>>::Type;
};

template <std::size_t target_index, class TList>
struct AtImpl<target_index, target_index, TList> {
  using Type = front_t<TList>;
};

template <std::size_t target_index, class TList>
struct At {
  using Type = typename AtImpl<target_index, 0, TList>::Type;
};

template <std::size_t target_index, class TList>
using at_t = typename At<target_index, TList>::Type;

// Find
template <class TargetType, std::size_t curr_inex, class TList>
struct FindImpl
    : std::integral_constant<std::size_t, FindImpl<TargetType, curr_inex + 1,
                                                   pop_front_v<TList>>::value> {
};

template <std::size_t curr_inex, class TList>
struct FindImpl<front_t<TList>, curr_inex, TList>
    : std::integral_constant<std::size_t, curr_inex> {};

template <class TargetType, class TList>
struct Find : std::integral_constant<std::size_t,
                                     FindImpl<TargetType, 0, TList>::value> {};

template <class TargetType, class TList>
inline constexpr auto find_v = Find<TargetType, TList>::value;

// Contains
template <class TargetType, class TList>
struct Contains;

template <class TargetType, class... Types>
struct Contains<TargetType, TypeList<Types...>>
    : std::integral_constant<
          bool,
          std::is_same_v<TargetType, front_t<TypeList<Types...>>> ||
              Contains<TargetType, pop_front_v<TypeList<Types...>>>::value> {};

template <class TargetType>
struct Contains<TargetType, TypeList<>> : std::false_type {};

template <class TargetType, class TList>
inline constexpr auto contains_v = Contains<TargetType, TList>::value;

// Count
template <class TargetType, class TList>
struct Count;

template <class TargetType, class... Types>
struct Count<TargetType, TypeList<Types...>>
    : std::integral_constant<
          std::size_t,
          std::is_same_v<TargetType, front_t<TypeList<Types...>>> +
              Contains<TargetType, pop_front_v<TypeList<Types...>>>::value> {};

template <class TargetType>
struct Count<TargetType, TypeList<>> : std::integral_constant<std::size_t, 0> {
};

template <class TargetType, class TList>
inline constexpr auto count_v = Count<TargetType, TList>::value;

// TypeList definition
template <class... Types>
struct TypeList final {
  using Head = front_t<TypeList<Types...>>;
  using Tail = back_t<TypeList<Types...>>;
};

}  // namespace ink
