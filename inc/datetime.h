#ifndef _LTD_INCLUDE_TIME_H_
#define _LTD_INCLUDE_TIME_H_

#include <chrono>

namespace ltd
{
    namespace time
    {
        using duration = std::chrono::_V2::system_clock::duration;
        using time_point = std::chrono::high_resolution_clock::time_point;

        /**
         * @brief Returns a time_point of now.
         */ 
        time_point now();

        /**
         * @brief Returns a time_point of the first epoch.
         */ 
        time_point first_epoch();
        
    } // namespace time
} // namespace ltd

#endif // _LTD_INCLUDE_TIME_H_