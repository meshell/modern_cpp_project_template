#include "catch.hpp"
#include "trompeloeil.hpp"

extern template struct trompeloeil::reporter<trompeloeil::specialized>;


class IFoo
{
public:
    virtual ~IFoo() = default;
    virtual void foo() const = 0;
    virtual void bar() const = 0;
};


class MockFoo : public IFoo
{
public:
    MAKE_CONST_MOCK0(foo, void());
    MAKE_CONST_MOCK0(bar, void());
};

class Testee
{
public:
    explicit Testee(const IFoo& foo)
            : my_foo(foo)
    {
    }

    void call_foo () const
    {
        my_foo.foo();
    }

private:
    const IFoo& my_foo;
};

/*
This test is used to show google mock in action
*/
namespace {

TEST_CASE("Call expectations can be set on a Mock", "[mock]")
{
    MockFoo foo{};
    Testee testee{foo};
    REQUIRE_CALL(foo, foo());

    testee.call_foo();
    SUCCEED();
}

SCENARIO("Using trompeloeil in catch", "[mock]")
{
    GIVEN("A Mock class")
    {
        MockFoo foo{};
        Testee testee{foo};

        using named_expectation = std::unique_ptr<trompeloeil::expectation>;

        WHEN("the method foo is called on the mock")
        {
            named_expectation foo_called;
            named_expectation bar_not_called;

            THEN("a call to foo is expected")
            {
                foo_called = NAMED_REQUIRE_CALL(foo, foo());
            }

            THEN("a call to bar is not expected")
            {
                bar_not_called = NAMED_REQUIRE_CALL(foo, foo());
                FORBID_CALL(foo, bar());
            }
            testee.call_foo();

        }
    }
}

} //namespace