
#include <stdio.h>

#include "../inc/testunit.h"

namespace ltd
{
    test_case::test_case(const char *case_name, std::function<error(test_case*)> test_func)
        : name(case_name), func(test_func)
    {

    }

    test_case::~test_case()
    {

    }

    error test_case::run()
    {
        error err = func(this);
        
        if (err != error::no_error) {
            printf("Error running '%s'\n", name);
        }

        return err;
    }

    void test_case::test(bool value, const char* comment)
    {
        if(value == true) {
            pass_count++;
            printf("Pass... %d/%d\n", pass_count, pass_count + fail_count);
        } else {
            fail_count++;
            printf("Fail... %d/%d - %s\n", pass_count, pass_count + fail_count, comment);
        }
    }

    int test_case::get_pass_count() const
    {
        return pass_count;
    }

    int test_case::get_fail_count() const
    {
        return fail_count;
    }

    test_unit::test_unit()
    {

    }

    test_unit::~test_unit()
    {

    }

    void test_unit::test(const char* case_name, std::function<error(test_case*)> test_func)
    {
        test_case test(case_name, test_func);
        test.run();
    }

} // namespace ltd