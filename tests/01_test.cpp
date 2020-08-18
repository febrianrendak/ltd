#include "../inc/ltd.h"

using namespace ltd;

class test01 : test_unit
{
public:
    int testing() 
    {
        this->test("First", [](test_case *tc) -> error {
            tc->test(true, "Expected to be true");
            return error::no_error;
        });

        return 0;
    }
};

test01 t;