#include "../inc/ltd.h"
#include <array>

using namespace ltd;

int CounterA = 0;

class entity 
{
public:
    entity() {
        CounterA++;
    }
};

class test_app : test_unit
{
public:
    void setup() 
    {
        this->test("std::array instatiation Test", [](test_case *tc) -> error {
                       
            std::array<entity, 5> a;

            tc->test(CounterA==0, "The constructor has been called");

            return error::no_error;
        });
    }
};

test_app t;