#ifndef _LTD_INCLUDE_MEMORY_H_
#define _LTD_INCLUDE_MEMORY_H_

#include <atomic>

#include "errors.h"
#include "stdalias.h"

namespace ltd
{
    namespace memory 
    {
        class global_allocator
        {
            static std::atomic_ulong bytes_allocated;
            
        public:
            ret<void*, error> allocate(size_t bytes_count);
            error deallocate(void* buffer); 
        };

        template<typename T, size_t SIZE>
        class static_allocator
        {
            std::byte raw_block[sizeof(T)*SIZE];
            uint32_t  allocated = 0;

        public:
            ret<T*, error> allocate(size_t count=SIZE)
            {
                if (count != SIZE)
                    return {nullptr, error::allocation_failure};

                return {(T*)&raw_block[0], error::no_error};
            }

            error deallocate(T* buffer)
            {
                return error::no_error;
            }
        };
    } // namespace memory
} // namespace ltd

#endif // _LTD_INCLUDE_MEMORY_H_