# {Ltd.}
A suite of C++ library and build tools.

Sometimes, at least in my case, it can be quite difficult to build a team of C++ 
programmers with even levels of proficiency. This will lead to inconsistent ways
of doing certain basic tasks in our project codebase.

This library should address this issue by introducing some restrictions, hence the 
name, and framework in doing things to ensure that there will not be too many 
variations in techniques used to perform basic and routine tasks in our code base. 

## Features

... or a lack thereof.

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

- **Application Framework**

  Application framework encapsulate functionalities in creating application using C++.
  It also gives an underlying functionalities in creating test unit framework.
  
  ```C++
  class my_app : public application
  {
  public:
    int main()
    {
      // Do something...
      return 0;
    }
  };
  
  my_app the_app;
  
  ```

- **Pointers**

  `std`'s smart pointers are powerful. But it can lead into several performance and
  stability problems if the programmer does not have enough experience with them. 
  Therefore `ltd` only provide one model of smart pointer. It only provides functionalities 
  similar with `std::unique_ptr`. The use of shared pointers and weak pointers are 
  not advised with `ltd`.

  Ownership of a pointer is underlined very stringly in `ltd`. Pointers can be owned 
  by a class, a cointainer or local vaariable. When passing a raw pointer to a function, 
  the function should not claim ownership to the pointer. When a function expecting 
  to own a pointer, it should specify r-value to allow the use of `std::move()`.

- **Removal of [] operator**

  To prevent array out of bound error and to help with map get operation, the [] operator
  is removed from `ltd`'s containers. It will use `ret<T,error> at(K)` instead. Where T
  is the type of the value and K is the type of the index or key. Expect `error::not_found` 
  for key-value containers when the element requested does not exist or `error::index_out_of_bound`
  for index based containers.

- **Containers: array, slice and map**

  `ltd` supports basic containers with its own flavors. 2 major difference with `std`'s 
  containers are memory layout and API. They supports `std::iterator`s, but they do 
  not support [] operator.

  `ltd::array` provides random read and write access to a typed buffer with static size.
  It will not call default constructor of its value type while being created. Hence, 
  the elements of array are not initialized. It allows the insertion of an object anywhere
  between 0 to N-1 from the get go. When insertin an object, it check whether the index
  given contains an object. If it's empty, it will place the object in the given index. 
  When it is occupied by an object, the existing object will be destroyed and then the 
  new empty space will be filled by the new object.

  `ltd::slice` provides dynamic array functionalities similar with `std::vector`. It 
  supports append and pop back operations. Initially, it's size is 0. The size increases 
  when append operation performed. If the size is > 0 then it allows read and write 
  access, similar with `ltd::array`, from 0 to size - 1. `ltd::slize` has the ability
  to do storage sharing among its instances and copy-on-write.

- **Asynch and threading framework**

  TBD.