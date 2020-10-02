#ifndef _LTD_INCLUDE_ALLOCATORS_H_
#define _LTD_INCLUDE_ALLOCATORS_H_

#include <atomic>

#include "errors.h"
#include "stdalias.h"

namespace ltd
{
    namespace memory
    {
        /**
         * Memory allocator using operating system's memory allocator.
         */ 
        class system_allocator
        {
        private:
            static std::atomic_ulong bytes_allocated;
            
        public:
            ret<void*, error> allocate(size_t bytes_count);
            error deallocate(void* buffer); 
        };

        class span_allocator
        {
        private:
        
        public:
        };

        class global_allocator
        {
        private:

        public:
        };

        /**
         * Memory allocator 
         */ 
        template<typename T, size_t SIZE>
        class static_allocator
        {
        private:
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
} // namesoace ltd

#endif // _LTD_INCLUDE_ALLOCATORS_H_