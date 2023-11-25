#include <gtest/gtest.h>
#include <type_list.hpp>

#include <string>

namespace ink::test {

// Note: tests always pass if they compile

// Basics
TEST(TypeList, LookUp) {
  using type_list = ink::TypeList<int, double, class SomeTag>;
  static_assert(ink::size_v<type_list> == 3);
  static_assert(std::is_same_v<int, type_list::Head>);
  static_assert(std::is_same_v<class SomeTag, type_list::Tail>);

  using empty_tl = ink::TypeList<>;
  static_assert(ink::size_v<empty_tl> == 0);
  static_assert(!std::is_same_v<int, empty_tl::Head>);
  static_assert(!std::is_same_v<class SomeTag, empty_tl::Tail>);
}

TEST(TypeList, PushBackBasic) {
  using type_list = ink::TypeList<int, double, class SomeTag>;
  using expected_tl = ink::TypeList<int, double, class SomeTag, std::string>;
  using resulted_tl = ink::push_back_v<std::string, type_list>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PushBackToEmptyList) {
  using empty_tl = ink::TypeList<>;
  using expected_tl = ink::TypeList<int>;
  using resulted_tl = ink::push_back_v<int, empty_tl>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PushFrontBasic) {
  using type_list = ink::TypeList<int, double, class SomeTag>;
  using expected_tl = ink::TypeList<std::string, int, double, class SomeTag>;
  using resulted_tl = ink::push_front_v<std::string, type_list>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PushFrontToEmptyList) {
  using empty_tl = ink::TypeList<>;
  using expected_tl = ink::TypeList<int>;
  using resulted_tl = ink::push_front_v<int, empty_tl>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PopFrontBasic) {
  using type_list = ink::TypeList<int, double, class SomeTag>;
  using expected_tl = ink::TypeList<double, class SomeTag>;
  using resulted_tl = ink::pop_front_v<type_list>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PopFrontFromOneTypeList) {
  using one_type_tl = ink::TypeList<int>;
  using expected_tl = ink::TypeList<>;
  using resulted_tl = ink::pop_front_v<one_type_tl>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PopFrontFromEmptyList) {
  using empty_tl = ink::TypeList<>;
  using expected_tl = ink::TypeList<>;
  using resulted_tl = ink::pop_front_v<empty_tl>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, At) {
  using type_list = ink::TypeList<int, double, class SomeTag>;

  static_assert(std::is_same_v<int, ink::at_t<0, type_list>>);
  static_assert(std::is_same_v<double, ink::at_t<1, type_list>>);
  static_assert(std::is_same_v<class SomeTag, ink::at_t<2, type_list>>);
}

TEST(TypeList, Find) {
  using type_list = ink::TypeList<int, double, class SomeTag, int>;

  static_assert(ink::find_v<int, type_list> == 0);
  static_assert(ink::find_v<double, type_list> == 1);
  static_assert(ink::find_v<class SomeTag, type_list> == 2);
}

// Algorithms
TEST(TypeList, Contains) {
  using type_list = ink::TypeList<int, double, class SomeTag>;

  static_assert(ink::contains_v<int, type_list>);
  static_assert(ink::contains_v<double, type_list>);
  static_assert(ink::contains_v<class SomeTag, type_list>);

  static_assert(!ink::contains_v<void, type_list>);
  static_assert(!ink::contains_v<std::string, type_list>);
  static_assert(!ink::contains_v<float, type_list>);

  using empty_tl = ink::TypeList<>;
  static_assert(!ink::contains_v<int, empty_tl>);
}

TEST(TypeList, Count) {
  using type_list = ink::TypeList<int, double, int>;

  static_assert(ink::count_v<int, type_list> == 2);
  static_assert(ink::count_v<double, type_list> == 1);
  static_assert(ink::count_v<class SomeTag, type_list> == 0);
}

}  // namespace ink::test
