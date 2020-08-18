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
        test_case();
        ~test_case();

        void set(const char *case_name, std::function<error(test_case*)> test_func);

        error run();
        void test(bool value, const char* comment);

        int get_pass_count() const;
        int get_fail_count() const;

    };

    #define MAX_CASE    32
    class test_unit : application 
    {
    private:
        test_case cases[MAX_CASE];
        int cases_count;

    public:
        test_unit();
        ~test_unit();

        error test(const char* case_name, std::function<error(test_case*)> test_func);

        int main();

        virtual void setup() = 0;
    };

}

#endif // _LTD_INCLUDE_TEST_UNIT_H_