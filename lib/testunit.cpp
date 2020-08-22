
#include <stdio.h>

#include "../inc/testunit.h"
#include "../inc/fmt.h"
#include "../inc/datetime.h"

namespace ltd
{
    test_case::test_case()
        : name(nullptr), func(nullptr)
    {

    }

    test_case::~test_case()
    {

    }

    void test_case::set(const char *case_name, std::function<error(test_case*)> test_func)
    {
        name = case_name;
        func = test_func;
    }

    error test_case::run()
    {
        printf("==> RUN '%s'\n", name);

        auto start = time::now(); 
        error err = func(this);
        auto end = time::now();
        
        auto elapsed = end - start;

        if (err != error::no_error) {
            printf("%s    '%s'     %.3fs\n", "ERROR", name, (float) elapsed.count()/1000000);
        } else {
            printf("%s    '%s'     %.3fs\n", fail_count == 0 ? "PASS" : "FAIL", name, (float) elapsed.count()/1000000);
        }

        printf("\n");
        
        return err;
    }

    void test_case::test(bool value, const char* comment)
    {
        if(value == true) {
            pass_count++;
            printf("    ok....... %d/%d\n", pass_count, pass_count + fail_count);
        } else {
            fail_count++;
            printf("    failed... %d/%d - %s\n", pass_count, pass_count + fail_count, comment != nullptr ? comment : "");
        }
    }

    void test_case::test(bool value)
    {
        test(value, nullptr);
    }

    int test_case::get_pass_count() const
    {
        return pass_count;
    }

    int test_case::get_fail_count() const
    {
        return fail_count;
    }

    test_unit::test_unit() : cases_count(0)
    {

    }
 
    test_unit::~test_unit()
    {

    }

    error test_unit::test(const char *case_name, std::function<error(test_case*)> test_func)
    {
        if (cases_count < MAX_CASE) 
        {
            cases[cases_count].set(case_name, test_func);
            cases_count++;
            return error::no_error;
        } 

        return error::overflow;
    }

    int test_unit::main()
    {
        this->setup();

        for (int i=0; i < cases_count; i++) {
            cases[i].run();
        }

        return 0;
    }

} // namespace ltd