# C++ hooking 101
This tutorial briefly covers existing binary code hooking in C++. Keep in mind, this is written with MSVC is mind (Visual Studio C++) and might not work as intended for other compilers.

## Requirements
* you have to be used to Visual Studio workflow (code writing, compiling, etc)
* you have to understand the concept of pointers https://en.wikipedia.org/wiki/Pointer_(computer_programming)

## Variable usage
This is as simple as casting hex address to pointer type. We declare someValue of pointer to int type and save original address value as this pointer value. Then the pointer points to the original variable.
```int* someValue = (int*)0x12345678;```

From now on you can use *someValue to read/write the value along with the original code.

## Function hooking
In short, knowing the address of the function in the executable file, we can declare a function pointer and use it like we would use a normal library function. 

Example:
```
typedef void(_cdecl *SOUNDLIB_Init_t)(HWND* hWnd);
static const SOUNDLIB_Init_t SOUNDLIB_Init = (SOUNDLIB_Init_t)0x4ef8b0;
```

First line is used to declare the function signature:
* ```typedef``` - declares the type you will use to map the pointer to.
* ```void``` - denotes the return type of the function. if it returns an integer, here will be int instead.
* ```_cdecl``` - denotes the calling convention used. _cdecl can be omitted in MSVC, since it's the default one for standard C style functions. classes use _thiscall, which will be described later.
* ```<typename>``` - just a name for the function pointer type. for convenience i go with ```<funcname>_t```.
* ```(params)``` - whatever goes after that is gathered through the decompiled code analysis and function usage. Most of the times it will coincide with Ghidra declarations, but sometimes it may fail. In this case we know that the result of window creation (which is of HWND type) is passed as the only param, so this is what we write. It is enough to declare param types only, but for convenience i give it a name as well.

Second line is used to declare the pointer itself of previously created type:
* ```static const``` - this means our pointer never changes and always points to this memory area. We can do that because we are working with the static code that never relocates.
* ```<functype> <funcname> =(<functype>)0x<address>``` - rather standard var declaration, similar to how we work with vars. we say that this address must be treated as function pointer, casted to our previously declared type.

In case we are trying to hook a C++ class method, there is a slight change we need to introduce.
* first of all, the calling convention of the function pointer type must be changed to _thiscall
* param list always starts with a pointer to class, passed as this keyword. But since we don't have the class itself, just call the 1st param _this. rest of params are declared as usual.

Now as we mapped the function we want to call, we can write a wrapper function for it that will execute the original code and do something more eventually.
This is done by creating a usual C function, but its params, calling convention and return type must fully coincide with the hooked function.
Inside the wrapper function you write a call to the original function like you would normally used any other function.

In case of thiscall there are additonal rules:
* the wrapper function must use _fastcall convention
* you have to insert additional param right after _this. you can call it void* _edx.
* inside the function you write your call to the original function as usual and just leave _edx unused, do not pass it. that should do the trick and allow you to hook thiscall func.

But how this new function will be called then? You have to find the original function calls and redirect them to the wrapper function.
Sometimes you'll want all of them, sometimes you just need a specific call, it's totally on you.
You can go as low as asm and patch the address manually or you can use any existing lib that will do it for you.

So how do you know it succeeded? If it didn't crash, you probably got it right.

## Additional reading on calling conventions
* Wikipedia: https://en.wikipedia.org/wiki/X86_calling_conventions
* Microsoft: https://docs.microsoft.com/en-us/cpp/cpp/calling-conventions?view=msvc-170
* Intel: https://www.intel.com/content/www/us/en/develop/documentation/cpp-compiler-developer-guide-and-reference/top/compiler-reference/c-c-calling-conventions.html