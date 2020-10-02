#ifndef _LTD_INCLUDE_MEMORY_H_
#define _LTD_INCLUDE_MEMORY_H_

#include <new> 
#include <utility>

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
    } // namespace memory
} // namespace ltd

#endif // _LTD_INCLUDE_MEMORY_H_