#include "../inc/ltd.h"
 
int main(int argc, char *argv[])
{
    if (ltd::application::get_instance() != nullptr)
        return ltd::application::get_instance()->bootstrap(argc, argv);

    return -1;
}