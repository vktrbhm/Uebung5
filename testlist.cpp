#define CATCH_CONFIG_RUNNER
#include "List.hpp"
#include "catch.hpp"


// Aufgabe 5.1
TEST_CASE("Standard Konstuktor", "[list][standard_ctor]")
{
  List<int> list;

  REQUIRE( list.empty());
  REQUIRE( list.size() == 0 );
}

// Aufgabe 5.2
TEST_CASE("Test push_front", "[list][push_front]")
{
  List<int> list;
  list.push_front(1);
  REQUIRE( 1 == list.front());
}

TEST_CASE("Test push_back", "[list][push_back]")
{
  List<int> list;
  list.push_back(14);
  REQUIRE(14 == list.back());
}

TEST_CASE("test pop_back and pop_front", "[pop_back][pop_front]")
{
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  list.pop_back();
  REQUIRE( 3 == list.back());
  REQUIRE( 3 == list.size());

  list.pop_front();
  REQUIRE( 2 == list.front());
  REQUIRE( 2 == list.size());
}

// Aufgabe 5.3
TEST_CASE("should be empty after clearing", "[list][clear]")
{
  List<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  list.clear();
  REQUIRE( list.empty());
}

// Aufgabe 5.5
TEST_CASE("should be an empty range after default construction", "[begin][end]")
{
  List<int> list;
  auto e = list.end();
  auto b = list.begin();
  REQUIRE( b == e );
}

TEST_CASE("provide access to the first element with begin", "[list][begin]")
{
  List<int> list;
  list.push_front(42);
  REQUIRE( 42 == *list.begin());
}

// Aufgabe 5.7
TEST_CASE("copy constructor", "[copy][constructor]")
{
  List<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  List<int> list2(list);

  REQUIRE( list.size() == list2.size() );
  REQUIRE( list == list2 );
}

TEST_CASE("move constructor", "[move][constructor]")
{
  List<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  List<int> list2(std::move(list));

  REQUIRE( 0 == list.size() );
  REQUIRE( list.empty() );
  REQUIRE( 4 == list2.size() );
}

// Aufgabe 5.8
TEST_CASE("test insert", "[list][insert]")
{
  List<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  //ListIterator<int> iter(list.begin());
  //REQUIRE( 4 == *iter );

  for ( ListIterator<int> it(list.begin()); it != nullptr; ++it )
    list.insert(it, 0);
  list.print();
}

// Aufgabe 5.9
TEST_CASE("test reverse", "[list][reverse]")
{
  List<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  list.print();
  list.reverse();
  list.print();

  REQUIRE( 4 == list.back() );
  REQUIRE( 1 == list.front() );
}

int main(int argc, char* argv[])
{
  
  return Catch::Session().run(argc, argv);

}