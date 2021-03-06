#include "catch.hpp"
#include "my_project/dummy.h"

namespace {

using my_project::Dummy;

TEST_CASE("A newly created default dummy", "[creation]") {
    Dummy dummy{};
    REQUIRE(dummy.speechless());
}

TEST_CASE("A english dummy", "[creation]")
{
    Dummy dummy{"Hello", "World"};

    REQUIRE(not dummy.speechless());
    REQUIRE(dummy.say_hello() == "Hello World");
}

} //namespace
