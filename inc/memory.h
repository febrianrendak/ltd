#ifndef _LTD_INCLUDE_MEMORY_H_
#define _LTD_INCLUDE_MEMORY_H_

#include <new> 
#include <utility>
#include <atomic>

#include "errors.h"
#include "stdalias.h"

namespace ltd
{
    namespace memory 
    {
        /**
         * Construct object of type T on the given memory address.
         */ 
        template<typename T, typename... Args>
        void construct(T *instance, Args&&... args)
        {
            new (instance) T(std::forward<Args>(args)...);
        }

        /**
         * Destruct the object by calling its destructor. 
         * This does not release the memory.
         */ 
        template<typename T>
        void destruct(T *instance)
        {
            (*instance).~T();
        }

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

        template<typename T>
        class typed_buffer
        {
        private:

        public:
            typed_buffer() = default;

            virtual T *at(int i) = 0;

            template<typename... Args>
            T* construct(int i, Args&&... args)
            {
                T* instance = at(i);
                return new(instance) T(std::forward<Args>(args)...);
            }

            void destruct(T* instance)
            {
                (*instance).~T();
            }
        };

        template<typename T, size_t SIZE>
        class static_buffer
        {
        private:
        static_allocator<T, SIZE> allocator;
        T* buffer;

        public:
            static_buffer()
            {
                buffer = allocator.allocate();
            }

        };
    } // namespace memory
} // namespace ltd

#endif // _LTD_INCLUDE_MEMORY_H_