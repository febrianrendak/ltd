#ifndef _LTD_INCLUDE_TEST_UNIT_H_
#define _LTD_INCLUDE_TEST_UNIT_H_

#include <functional>

#include "../inc/application.h"

namespace ltd {

    /**
     * @brief Internal class to provide functionalities of a test case.
     */ 
    class test_case
    {
    private:
        int pass_count = 0;
        int fail_count = 0;
        
        const char *name;
        std::function<error(test_case*)> func;

    public:
        /**
         * @brief Constructor.
         */ 
        test_case();

        /**
         * @brief Destructor
         */ 
        ~test_case();

        /**
         * @brief Setup the test case with test case name and test function.
         */
        void set(const char *case_name, std::function<error(test_case*)> test_func);

        /**
         * @brief Runs the test case.
         */ 
        error run();
        
        /**
         * @brief Test a value and gives a comment when the test fails.
         */ 
        void test(bool value, const char* comment);

        /**
         * @bried Short hand help for test function without comment.
         */ 
        void test(bool value);

        /**
         * @brief Returns the number of passed checks.
         */ 
        int get_pass_count() const;
        
        /**
         * @brief Returns the number of failed checks.
         */
        int get_fail_count() const;

    };

    #define MAX_CASE    32

    /**
     * @brief This is a class that provides the functionalities for test units.
     * 
     * To user this class, create a derived class from this class and implements the `setup()` method and 
     * then create the instance of the class on the stack.
     * 
     * In the method, calls the `test()` function to register a test function. The class will execute the
     * test functions automatically.
     * 
     * ```
     *  class test01 : test_unit
     *  {
     *  public:
     *      void setup() 
     *      {
     *          this->test("First", [](test_case *tc) -> error {
     * 
     *              tc->test(true, "Expected to be true");
     *              tc->test(true, "Expected to be true");
     * 
     *              return error::no_error;
     *          });
     * 
     *          this->test("Second", [](test_case *tc) -> error {
     * 
     *              tc->test(true, "Expected to be true");
     *              tc->test(false, "Expected to be true");
     *              tc->test(true, "Expected to be true");
     * 
     *              return error::no_error;
     *          });
     *      }
     * };
     * 
     * test01 t;
     * ```
     */ 
    class test_unit : application 
    {
    private:
        test_case cases[MAX_CASE];
        int cases_count;

    public:

        /**
         * @brief Constructor.
         */ 
        test_unit();

        /**
         * @brief Destrutctor.
         */ 
        ~test_unit();

        /**
         * @brief Register a test function with a given name.
         */ 
        error test(const char* case_name, std::function<error(test_case*)> test_func);

        /**
         * @brief internal usage for the framework.
         */ 
        int main();

        /**
         * @brief Setups the test unit.
         */ 
        virtual void setup() = 0;
    };

}

#endif // _LTD_INCLUDE_TEST_UNIT_H_