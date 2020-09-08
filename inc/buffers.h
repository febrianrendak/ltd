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
        
        auto grow() -> error
        {
            return error::allocation_failure;
        }

        auto ensure_capacity(size_t new_capacity) -> error 
        {
            return error::allocation_failure;
        }

        auto at(size_t pos) const -> ret<void*,error> 
        {
            if (pos >= length()) 
                return {nullptr, error::index_out_of_bound};

            return {&buffer[pos*ItemSize], error::no_error};
        }
    };

    template<unsigned int ItemCount=1, unsigned int ItemSize=1, unsigned int Overflows=2>
    class dynamic_buffer
    {
    private:
        std::byte *main_buffer;
        std::byte *overflows[Overflows];
        
        size_t main_buffer_len;

        void clear_overflow_buffers()
        {
            for(int i=0; i < Overflows; i++) {
                if(overflows[i] != nullptr) {
                    delete[] overflows[i];
                    overflows[i] = nullptr;
                }
            }
        }

    public:
        dynamic_buffer() 
        {
            main_buffer_len = ItemCount;
            main_buffer     = new std::byte[ItemCount*ItemSize];
        }

        ~dynamic_buffer()
        {
            clear_overflow_buffers();
            delete[] main_buffer;
        }

        constexpr auto raw_length() const -> size_t 
        { 
            return ItemCount * ItemSize; 
        }
        
        constexpr auto length() const -> size_t
        { 
            return ItemCount; 
        }

        auto grow() -> error
        {
            for(int i=0; i<Overflows; i++) {
                if(overflows[i] == nullptr) {
                    int new_len  = main_buffer_len * pow(2,i);
                    overflows[i] = new std::byte[new_len];
                }
            }
        }
        
    };

} // namespace ltd

#endif // _LTD_INCLUDE_BUFFERS_H_