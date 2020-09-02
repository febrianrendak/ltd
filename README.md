# {Ltd.}
A suite of C++ library and build tools.

Sometimes, at least in my case, it can be quite difficult to build a team of C++ 
programmers with even levels of proficiency. This will lead to inconsistent ways
of doing certain basic tasks in our project codebase.

This library should address this issue by introducing some restrictions, hence the 
name, and framework in doing things to ensure that there will not be too many 
variations in techniques used to perform basic and routine tasks in our code base. 

## Features
- **Error Handling**
  
  Errors are handled by returning status in every functions in the code base. There 
  should not be try-and-catch error handling used in the library.
  
  There is a class under the ltd namespace called `error`. You can use the provided
  error in the class' static constant member or use `error make_error(const char *message)`
  to create custom error.
  
- **Multiple Return Values**

  To support error handling by returning error status, the library supports multiple 
  return values. I.e. when the function needs to return value(s) along with the error 
  status.
  
  ```c++
  ret<int,error> do_something() 
  {
    return {0, error::no_error};
  }
  ```

  

