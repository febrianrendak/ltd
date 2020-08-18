#include "../inc/ltd.h"

using namespace ltd;

ret<int,float> get_values()
{
    return {1,.5};
}

class test_returns : test_unit
{
public:
    void setup() 
    {
        this->test("Return values", [](test_case *tc) -> error {

            auto[count, price] = get_values();
            
            tc->test(count == 1);
            tc->test(price == .5);

            return error::no_error;
        });
    }
};

test_returns t;