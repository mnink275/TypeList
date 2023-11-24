#include <gtest/gtest.h>
#include <type_list.hpp>

#include <string>

namespace ink::test {

TEST(TypeList, LookUp) {
  using type_list = ink::TypeList<int, double, class SomeTag>;
  static_assert(ink::size_v<type_list> == 3);
  static_assert(std::is_same_v<int, type_list::Head>);
  static_assert(std::is_same_v<class SomeTag, type_list::Tail>);
}

TEST(TypeList, PushBack) {
  using type_list = ink::TypeList<int, double, class SomeTag>;
  using expected_tl = ink::TypeList<int, double, class SomeTag, std::string>;
  using resulted_tl = ink::push_back_v<std::string, type_list>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PushFront) {
  using type_list = ink::TypeList<int, double, class SomeTag>;
  using expected_tl = ink::TypeList<std::string, int, double, class SomeTag>;
  using resulted_tl = ink::push_front_v<std::string, type_list>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, PopFront) {
  using type_list = ink::TypeList<int, double, class SomeTag>;
  using expected_tl = ink::TypeList<double, class SomeTag>;
  using resulted_tl = ink::pop_front_v<type_list>;
  static_assert(std::is_same_v<expected_tl, resulted_tl>);
}

TEST(TypeList, Contains) {
  using type_list = ink::TypeList<int, double, class SomeTag>;

  static_assert(ink::contains_v<int, type_list>);
  static_assert(ink::contains_v<double, type_list>);
  static_assert(ink::contains_v<class SomeTag, type_list>);

  static_assert(!ink::contains_v<void, type_list>);
  static_assert(!ink::contains_v<std::string, type_list>);
  static_assert(!ink::contains_v<float, type_list>);
}

}  // namespace ink::test
