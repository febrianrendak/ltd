#include "../inc/application.h"

ltd::application *app_instance = nullptr;

namespace ltd
{
    error application::bootstrap(int argc, char *argv[])
    {
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
}