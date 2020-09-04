#ifndef _LTD_INCLUDE_BUFFERS_H_
#define _LTD_INCLUDE_BUFFERS_H_

#include "errors.h"
#include "stdalias.h"

namespace ltd
{
    /**
     * @brief Class static_buffer provides functionalities for static buffer.
     */ 
    template<size_t InitialSize>
    class static_buffer
    {
    private:
        std::byte buffer[InitialSize];

    public:

        /**
         * Construct static_buffer object.
         */ 
        static_buffer() {}

        /**
         * Access the memory at the given position.
         */ 
        ret<void*,error> at(size_t pos) const {
            if (pos >= InitialSize) 
                return {nullptr, error::index_out_of_bound};

            return {&buffer[pos], error::no_error};
        }

        /**
         * Returns the length of the buffer.
         */ 
        constexpr size_t length() const { return InitialSize; }
        
        /**
         * This function only serves the compability purpose.
         */
        error ensure_capacity(size_t new_capacity) 
        {
            return error::allocation_failure;
        } 
    };

    template<int InitialSize>
    class dynamic_buffer
    {
    private:
        std::byte *main_buffer;
        std::byte **overflows;
        
        size_t overflows_len;
        size_t main_buffer_len;

        void delete_overflow_buffers()
        {
            for(int i=0; i < overflows_len; i++) {
                if(overflows[i] != nullptr) {
                    delete[] overflows[i];
                    overflows[i] = nullptr;
                }
            }

            delete[] overflows;
        }

        void resize_overflows()
        {
            if(overflows == nullptr) {
                overflows_len = 1;
                overflows = new std::byte*[overflows_len];
                for (int i=0; i < overflows_len; i++) {
                    overflows_len[i] = nullptr;
                }
            } else {
                std::byte **new_array;
                size_t      new_len = overflows_len * 2;

                new_array = new std::byte*[new_len];
                for (int i=0; i < new_len; i++)
                    new_array[i] = i < overflows_len ? overflows[i] : nullptr;

                delete[] overflows;

                overflows_len = new_len;
                overflows     = new_array;
            }
        }
    public:
        dynamic_buffer() 
        {
            main_buffer_len = InitialSize;
            main_buffer     = new std::byte[InitialSize];
        }

        ~dynamic_buffer()
        {
            delete_overflow_buffers();
            delete[] main_buffer;
        }
        
    };

} // namespace ltd

#endif // _LTD_INCLUDE_BUFFERS_H_