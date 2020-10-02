#ifndef _LTD_INCLUDE_BUFFERS_H_
#define _LTD_INCLUDE_BUFFERS_H_

#include "errors.h"
#include "stdalias.h"
#include "allocators.h"

#include <cstddef>

namespace ltd
{
    namespace memory
    {
        template<typename T>
        class typed_buffer
        {
        public:
            virtual auto raw_length() const -> size_t = 0; 
            
            virtual auto length() const -> size_t = 0;
            
            virtual auto grow() -> error = 0;

            virtual auto ensure_capacity(size_t new_capacity) -> error;

            virtual auto at(size_t pos) const -> ret<void*,error>;
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

#endif // _LTD_INCLUDE_BUFFERS_H_