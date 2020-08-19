#include "../inc/application.h"

ltd::application *app_instance = nullptr;

namespace ltd
{
    error application::bootstrap(int argc, char *argv[])
    {
        int code = main();
        set_exit_code(code);
        return error::no_error;
    }

    application::application()
    {
        app_instance = this;
    }
    
    application::~application()
    {
    }

    application * application::get_instance()
    {
        return app_instance;
    }

    void application::set_exit_code(int code)
    {
        exit_code = code;
    }
}