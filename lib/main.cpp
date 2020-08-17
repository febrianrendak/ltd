#include "../inc/ltd.h"

int main(int argc, char *argv[])
{
    if (ltd::application::get_instance() != nullptr) {
        auto err = ltd::application::get_instance()->bootstrap(argc, argv);
        if (err == ltd::error::no_error)
            return 0;
    }

    return -1;
}