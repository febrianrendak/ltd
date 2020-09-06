#ifndef _LTD_INCLUDE_BUFFERS_H_
#define _LTD_INCLUDE_BUFFERS_H_

#include "errors.h"
#include "stdalias.h"

#include <cstddef>

namespace ltd
{
    template<unsigned int ItemCount, unsigned int ItemSize = 1>
    class static_buffer
    {
    private:
        std::byte buffer[ItemCount*ItemSize];

    public:
        constexpr auto raw_length() const -> size_t 
        { 
            return ItemCount * ItemSize; 
        }
        
        constexpr auto length() const -> size_t
        { 
            return ItemCount; 
        }
        
        auto at(size_t pos) const -> ret<void*,error> 
        {
            if (pos >= length()) 
                return {nullptr, error::index_out_of_bound};

            return {&buffer[pos*ItemSize], error::no_error};
        }

        auto ensure_capacity(size_t new_capacity) const -> error 
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