#ifndef _LTD_INCLUDE_STDALIAS_H_
#define _LTD_INCLUDE_STDALIAS_H_


#include <tuple>

namespace ltd 
{
    template<typename... Args>  
    using ret = std::tuple<Args...>;

} // namespace ltd

#endif // _LTD_INCLUDE_STDALIAS_H_