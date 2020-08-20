#ifndef _LTD_INCLUDE_APPLICATION_H_
#define _LTD_INCLUDE_APPLICATION_H_

#include "../inc/errors.h"

namespace ltd
{
    /**
     * @brief Provides the main functionality for creating application using copeland framework.
     * 
     * Derive a class from this class and implement its `int main()` function to define the actual
     * action of the application.
     * 
     * To access the command line arguments, use its interface flags member variable. See `ltd::cli`.
     * 
     * User `set_exit_code()` function to set the application's return value to the operating system. 
     */ 
    class application
    {
    private:
        int exit_code = 0;

    public:
        /**
         * @brief default constructor.
         */
        application();
        ~application();

        /**
         * @brief Sets the exit code for this application.
         * 
         * The code value will be returned to the operating system when the applcation
         * quits.
         */ 
        void set_exit_code(int code);

        /**
         * @brief Abstract function for application's entry point.
         * 
         * Derived the class and implement this function to use the ltd application framework.
         */ 
        virtual int main() = 0;

        /**
         * @brief This is the main function for application framework.
         * 
         * This function is called internally by the framework. This should not
         * be called directly.
         */ 
        int bootstrap(int argc, char *argv[]);

        /**
         * @brief Get the single instance of application
         */ 
        static application * get_instance();
    };
} // namespace ltd

#endif // _LTD_INCLUDE_APPLICATION_H_