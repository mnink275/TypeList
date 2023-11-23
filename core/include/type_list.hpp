#pragma once

#include <array>
#include <cstddef>
#include <type_traits>
#include <typeindex>

namespace ink {

template <class ...Types>
struct TypeList final {};

// TypeList types pack size
template <class TList>
struct Size;

template <class ...Types>
struct Size<TypeList<Types...>> final {
  static constexpr auto kSize = sizeof...(Types);
};

template <class TList>
inline constexpr auto size_v = Size<TList>::kSize;

// Front type
template <class TList>
struct Front;

template <class FirstType, class ...Others>
struct Front<TypeList<FirstType, Others...>> final {
  using FrontType = FirstType;
};

template <class TList>
using front_t = typename Front<TList>::FrontType;

// Pushing
template <class NewType, class TList>
struct Pusher;

template <class NewType, class ...Types>
struct Pusher<NewType, TypeList<Types...>> final {
  using PushBackValue = TypeList<Types..., NewType>;
  using PushFrontValue = TypeList<NewType, Types...>;
};

template <class NewType, class TList>
using push_back_v = typename Pusher<NewType, TList>::PushBackValue;

template <class NewType, class TList>
using push_front_v = typename Pusher<NewType, TList>::PushFrontValue;

}  // namespace ink
