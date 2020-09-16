#include "../inc/memory.h"

namespace ltd
{
    namespace memory
    {
        std::atomic_ulong global_allocator::bytes_allocated(0);

        ret<void*,error> global_allocator::allocate(size_t byte_count)
        {
            auto buffer = malloc(byte_count);
            if(buffer==nullptr)
                return {nullptr, error::allocation_failure};

            bytes_allocated.fetch_add(byte_count);

            return {buffer, error::no_error};
        }

        error global_allocator::deallocate(void* buffer)
        {
            if (buffer==nullptr)
                return error::null_pointer;

            free(buffer);
            
            return error::no_error;
        }

    } // namespace memory
} // namespace ltd