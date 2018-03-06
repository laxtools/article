# Lua Integration 

## Introduction 

script languague can make development faster than doing it in pure c++. main reasons are: 

- zero build overhead for 80 % of script work 
- more developers include game designers to some degree



There are other problems introduced by adding scripting into pure c++ dev. Major cons are: 

- debugging two different languages and runtime
- definitely slower than c++ even with Jit
  - tendency to use more dynamic features like GC, json or some others 
  - call overhead between two languages even with lua 



The major goals of  this research are: 

- make it easy to develop scripting with lua
  - bug free, easy and fast binding with c++
    - no memory leak 
      - memory debugging
  - lua debugger enabled on request while lax runs 
    - remote debugging
    - gui debugger
  - debugging lua functions from c++ 
  - database support with json protocol
  - coroutines instead of callback
    - database 
    - continuation with message(s)
- increase performance
  - script parsing and loading
  - lua <--> c++ function calls
- IDE
  - use atom
  - use lua extension
  - remote debugging
    - per VM debugging



## Binding 

### Sol

https://github.com/ThePhD/sol2

It claims the fastest lua binding. If it is easy to bind c++ class, then it seems to be perfect. 

### Test 



## Debugger

https://github.com/slembcke/debugger.lua



 ## Distraction 

Other languages. How about C#?  Multiple C# runtime communicating with C++ core. 

How about using Python?  Hmm.... 

https://pybind11.readthedocs.io

http://yizhang82.me/hosting-coreclr



how about changing language completely? go? rust? 

- Experience matters
- c++ is such a powerful language and a tool 



Drop this for some time. No scripting, but data scripting / DSL per domain. 



















