#ifndef _LTD_INCLUDE_BUFFERS_H_
#define _LTD_INCLUDE_BUFFERS_H_

namespace ltd
{
    template<int InitialSize>
    class static_buffer
    {
    private:
        std::byte buffer[InitialSize];

    public:
        
    };

    template<int InitialSize>
    class dynamic_buffer
    {
    private:
        std::byte *main_buffer;
        std::byte **overflows;
        
    public:
        
    };

} // namespace ltd

#endif // _LTD_INCLUDE_BUFFERS_H_