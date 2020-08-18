#ifndef _LTD_INCLUDE_TEST_UNIT_H_
#define _LTD_INCLUDE_TEST_UNIT_H_

#include <functional>

#include "../inc/application.h"

namespace ltd {

    class test_case
    {
    private:
        int pass_count = 0;
        int fail_count = 0;
        
        const char *name;
        std::function<error(test_case*)> func;

    public:
        test_case(const char *case_name, std::function<error(test_case*)> test_func);
        ~test_case();

        error run();
        void test(bool value, const char* comment);

        int get_pass_count() const;
        int get_fail_count() const;
    };

    class test_unit : application 
    {
    private:

    public:
        test_unit();
        ~test_unit();

        void test(const char* case_name, std::function<error(test_case*)> test_func);
    };

}

#endif // _LTD_INCLUDE_TEST_UNIT_H_