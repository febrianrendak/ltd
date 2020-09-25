#include "../inc/memory.h"

namespace ltd
{
    namespace memory
    {
        std::atomic_ulong system_allocator::bytes_allocated(0);

        ret<void*,error> system_allocator::allocate(size_t byte_count)
        {
            size_t* raw_buffer = (size_t*) malloc(byte_count+sizeof(size_t));

            if(raw_buffer==nullptr)
                return {nullptr, error::allocation_failure};

            *raw_buffer = byte_count;                   // save the allocated bytes
            raw_buffer++;                               // increment the buffer to the first byte

            bytes_allocated.fetch_add(byte_count);

            return {(void*)raw_buffer, error::no_error};
        }

        error system_allocator::deallocate(void* buffer)
        {
            if (buffer==nullptr)
                return error::null_pointer;
            
            size_t* raw_buffer = (size_t*)buffer;
            raw_buffer--;

            size_t allocated = *raw_buffer;
            size_t total_allocated = bytes_allocated.load();
            
            if (allocated > total_allocated)
                return error::allocation_failure;

            free(raw_buffer);
            
            bytes_allocated.fetch_sub(allocated);

            return error::no_error;
        }        
    } // namespace memory
} // namespace ltd