#ifndef _LTD_INCLUDE_PTR_H_
#define _LTD_INCLUDE_PTR_H_

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
} // namespace ltd

#endif // _LTD_INCLUDE_PTR_H_