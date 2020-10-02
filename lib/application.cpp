#include <stdio.h>
#include <stdlib.h>
#include "../inc/application.h"

ltd::application *app_instance = nullptr;

namespace ltd
{
    int application::bootstrap(int argc, char *argv[])
    {
        set_exit_code(main());

        return exit_code;
    }

    application::application()
    {
        if(app_instance != nullptr) {
            fprintf(stderr, "Fatal error: duplicate application instance.\n");
            exit(-1);
        }

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