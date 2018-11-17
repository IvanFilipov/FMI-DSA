Some rules and coding conventions that this repository is following.
Please read them carefully before make any contribution (pull request, push).

#### Naming conventions

The naming conventions for **everything** in this repository is ***snake_case***. 
Exceptions are the constants. Use uppercase snake_case for them.
After pointer type variables use appendix *ptr*.
For references and pointers to objects write *&, \** immediately after the type.

 E.g :

````c++
int some_var;
class dynamic_array;
node* next_ptr;
dynamic_array& lhs = rhs;
const size_t MAX_SIZE = 1024;
````



#### Coding conventions

* placing braces and spaces - opening bracket is on the same line, **everywhere**. The next line is always an empty line. E.g :

  ````C++
  class class_definition {
  
  private :
      //...
  };
  struct struct_definition {
      
      int x;
  };
  void func() {
      
      do_something;
  }
  ````

  

  After each statement block (if, switch, for, while, do .. etc) there should be a space. E.g : 

  ``` c++
  if (cond) {
      // do something
  } else {
      // do something else
  }
  ```

  If your block contains only one operation the braces are optional, also it can be done on the same line. E.g :

  ```C++
  if(cond)
      long_long_op;
  
  if (cond) short_op;
  ```

  In conditionals or function calls, there are **no** spaces after the opening brace.

  ````C++
  func_call(param, other_param);
  if (a < b && b > c) do_something;
  ````

  Between binary operations there **are** spaces, but before/after unary operators there are **not**.

#### General rules

Indentations are **tabs** and each tab is 4 characters.
Choose names that are meaningful, but not too long.

Comments : in header files describe what a function/class should do, what parameters does it take,
some theoretical information about complexity, usages etc. In source files write single line comments
with information what logical steps does the algorithm make.