#include "../inc/datetime.h"

namespace ltd
{
    namespace time
    {
        time_point now() {
            return std::chrono::high_resolution_clock::now();
        }

        time_point first_epoch() {
            time_point epoch;
            return epoch;
        }
    } // namespace time
} // namespace ltd