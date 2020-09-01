#ifndef _LTD_INCLUDE_MEMORY_H_
#define _LTD_INCLUDE_MEMORY_H_

namespace ltd
{
    /**
     * @brief Template class ptr provides scoped pointer container. 
     * 
     * Use this pointer container to handle non-shared raw pointers to objects.
     * Once this container leaves its scope it will delete the pointer. Unless
     * the content of this container is moved to another container using
     * std::move().
     * 
     * ```C++     
     *      ptr<Object> new_container(std::move(old_container));
     * ```
     */ 
    template<typename T>
    class ptr
    {
        T *raw;
    public:
        ptr() : raw(0) {}

        ptr(T *p) : raw(p) {}

        ptr(ptr&& other)
        {
            raw = other.raw;
            other.raw = nullptr;
        }

        template<typename... A>
        ptr(A&&... args)
        {
            raw = new T(std::forward<A>(args)...);
        }

        ptr(ptr& other) = delete;
        ptr(const ptr& other) = delete;
        ptr& operator=(ptr other) = delete;

        bool is_null() const { return raw == nullptr; }

        inline T* operator->() { return raw; }
        inline const T& operator*() const { return *raw; }

        ~ptr() { delete raw; }
    };

    template<typename T, typename... A>
    inline ptr<T> make_ptr(A&&... args)
    {
        return ptr<T>(new T(std::forward<A>(args)...));
    }

    template<typename T, size_t Capacity>
    class stack_array_allocator
    {
    private:
        std::byte raw_block[Capacity*sizeof(T)];

    public:
        stack_array_allocator() {}
        
        size_t capacity() const { return Capacity; }

        T *get_raw_block() { return (T*)raw_block; }

        error realloc(size_t size) { return error::allocation_failure; }

    };

    template<typename T>
    class heap_array_locator
    {
    private:
        std::byte *raw_block;
        size_t raw_block_size;
    public:
        heap_array_locator() : raw_block(nullptr), raw_block_size(0) {}

        size_t capacity() const { return raw_block_size; }

        T *get_raw_block() { return (T*)raw_block; }

        error realloc(size_t size) 
        {
            if(raw_block != nullptr) 
                return error::allocation_failure;
            
            raw_block = new std::byte[size];
            raw_block_size = size;

            return error::no_error; 
        }

        ~heap_array_locator()
        {
            if(raw_block != nullptr)
            {
                delete raw_block;

                raw_block = nullptr;
                raw_block_size = 0;
            }
        }

    };

    template<typename T, size_t C=5, 
                         typename A=stack_array_allocator<T,C>, 
                         typename B=heap_array_locator<T>>
    class array
    {
    private:
        using allocator_type = typename std::conditional<C != 0, A, B>::type;
        allocator_type allocator;

    public:
        array() {}
    };
    
} // namespace ltd

#endif // _LTD_INCLUDE_MEMORY_H_