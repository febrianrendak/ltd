#ifndef _LTD_INCLUDE_TEST_UNIT_H_
#define _LTD_INCLUDE_TEST_UNIT_H_

#include "../inc/application.h"

namespace ltd {

    class test_unit : application 
    {
    private:

    public:
        test_unit();
        ~test_unit();

        void test(const char* case_name, int func);
    };

}

#endif // _LTD_INCLUDE_TEST_UNIT_H_