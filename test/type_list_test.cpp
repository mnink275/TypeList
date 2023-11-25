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
  using resulted_tl = ink::push_back_t<std::string, type_list>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PushBackToEmptyList) {
  using empty_tl = ink::TypeList<>;
  using expected_tl = ink::TypeList<int>;
  using resulted_tl = ink::push_back_t<int, empty_tl>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PushFrontBasic) {
  using type_list = ink::TypeList<int, double, class SomeTag>;
  using expected_tl = ink::TypeList<std::string, int, double, class SomeTag>;
  using resulted_tl = ink::push_front_t<std::string, type_list>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PushFrontToEmptyList) {
  using empty_tl = ink::TypeList<>;
  using expected_tl = ink::TypeList<int>;
  using resulted_tl = ink::push_front_t<int, empty_tl>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, Concatenate) {
  using left_tl = ink::TypeList<int, double>;
  using right_tl = ink::TypeList<class SomeTag, int>;
  using expected_tl = ink::TypeList<int, double, class SomeTag, int>;
  using resulted_tl = ink::concat_t<left_tl, right_tl>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, ConcatenateOneEmpty) {
  using left_tl = ink::TypeList<int, double>;
  using right_tl = ink::TypeList<>;
  using expected_tl = ink::TypeList<int, double>;
  using resulted_tl = ink::concat_t<left_tl, right_tl>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, ConcatenateBothEmpty) {
  using left_tl = ink::TypeList<>;
  using right_tl = ink::TypeList<>;
  using expected_tl = ink::TypeList<>;
  using resulted_tl = ink::concat_t<left_tl, right_tl>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PopFrontBasic) {
  using type_list = ink::TypeList<int, double, class SomeTag>;
  using expected_tl = ink::TypeList<double, class SomeTag>;
  using resulted_tl = ink::pop_front_t<type_list>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PopFrontFromOneTypeList) {
  using one_type_tl = ink::TypeList<int>;
  using expected_tl = ink::TypeList<>;
  using resulted_tl = ink::pop_front_t<one_type_tl>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PopFrontChain) {
  using tl_size_3 = ink::TypeList<int, double, class SomeTag>;
  using expected_tl_size_2 = ink::TypeList<double, class SomeTag>;
  static_assert(
      std::is_same_v<expected_tl_size_2, ink::pop_front_t<tl_size_3>>);

  using tl_size_2 = expected_tl_size_2;
  using expected_tl_size_1 = ink::TypeList<class SomeTag>;
  static_assert(
      std::is_same_v<expected_tl_size_1, ink::pop_front_t<tl_size_2>>);

  using tl_size_1 = expected_tl_size_1;
  using expected_tl_empty = ink::TypeList<>;
  static_assert(std::is_same_v<expected_tl_empty, ink::pop_front_t<tl_size_1>>);
}

TEST(TypeList, PopFrontFromEmptyList) {
  using empty_tl = ink::TypeList<>;
  using expected_tl = ink::TypeList<>;
  using resulted_tl = ink::pop_front_t<empty_tl>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PopBackBasic) {
  using type_list = ink::TypeList<int, double, class SomeTag>;
  using expected_tl = ink::TypeList<int, double>;
  using resulted_tl = ink::pop_back_t<type_list>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PopBackFromOneTypeList) {
  using one_type_tl = ink::TypeList<int>;
  using expected_tl = ink::TypeList<>;
  using resulted_tl = ink::pop_back_t<one_type_tl>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PopBackChain) {
  using tl_size_3 = ink::TypeList<int, double, class SomeTag>;
  using expected_tl_size_2 = ink::TypeList<int, double>;
  static_assert(std::is_same_v<expected_tl_size_2, ink::pop_back_t<tl_size_3>>);

  using tl_size_2 = expected_tl_size_2;
  using expected_tl_size_1 = ink::TypeList<int>;
  static_assert(std::is_same_v<expected_tl_size_1, ink::pop_back_t<tl_size_2>>);

  using tl_size_1 = expected_tl_size_1;
  using expected_tl_empty = ink::TypeList<>;
  static_assert(std::is_same_v<expected_tl_empty, ink::pop_back_t<tl_size_1>>);
}

TEST(TypeList, PopBackFromEmptyList) {
  using empty_tl = ink::TypeList<>;
  using expected_tl = ink::TypeList<>;
  using resulted_tl = ink::pop_back_t<empty_tl>;
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
