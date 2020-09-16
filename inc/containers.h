#ifndef _LTD_INCLUDE_CONTAINERS_H_
#define _LTD_INCLUDE_CONTAINERS_H_

#include "memory.h"

namespace ltd
{
    namespace containers
    {
        template<typename T, size_t SIZE>
        class array
        {
        private:

        public:
            array() {}
        };

        template<typename T, size_t SIZE=0, typename A=memory::static_allocator<T,SIZE>, typename B=memory::global_allocator>
        class slice
        {
        private:
            using allocator_type = typename std::conditional<SIZE != 0, A, B>::type;
            allocator_type allocator;

        public:
        };
    }
} // namespace ltd

#endif // _LTD_INCLUDE_CONTAINERS_H_