#include "../inc/ltd.h"

using namespace ltd;

class test01 : test_unit
{
public:
    int main() 
    {
        this->test("First", [](test_case *test) -> error {
            return error::no_error;
        });

        return 0;
    }
};