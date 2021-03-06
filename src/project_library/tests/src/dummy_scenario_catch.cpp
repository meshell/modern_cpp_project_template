#include "catch.hpp"
#include "my_project/dummy.h"

namespace {

using my_project::Dummy;

SCENARIO("Default dummy", "[creation]") {
    GIVEN("A default dummy") {
        Dummy dummy;

        WHEN("the dummy wants to speak") {
            THEN("the dummy is speechless") {
                REQUIRE(dummy.speechless());
            }
        }
    }
}

SCENARIO("English dummy", "[creation]") {
    GIVEN("A english dummy") {
        Dummy dummy{"Hello", "World"};

        WHEN("the dummy speak") {
            THEN("the dummy speaks english") {
                REQUIRE(not dummy.speechless());
                REQUIRE(dummy.say_hello() == "Hello World");
            }
        }
    }
}

} //namespace
