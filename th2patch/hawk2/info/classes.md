# C++ classes 101

## Disclaimer
This article entirely describes a very specific case of Visual Studio compiled code, which may or may not match other patterns based on the compiler used, compilation flags, etc. To fully understand how it actually works and why it may not work in other cases, you have to somewhat go down to assembler and cpu registers level.

## Class
First of all, ```class``` is an abstract concept, essentially a code pattern, thus, it is built on top of "older technology". Under the hood, class is nothing more but a structure that contains an array of pointers to all class related functions, called ```virtual table``` or vtable.

## Virtual tables
https://pabloariasal.github.io/2017/06/10/understanding-virtual-tables/

```Virtual table``` is a plain array of function pointers - ```funcptr[]```.

The very first pointer of the class structure is the pointer to the vTable.

Now instead of calling a class function directly by its address, under the hood it is recovered using ```pClass->vTable[functionIndex](<params>)``` call.

If you inherit a class, it simply creates anoter vtable, copies all original function pointers and adds additional funcptrs to the end of the new table.

## Recovering class structure for decompilation

Hence we already know that class is simply a structure, Ghidra "auto-create structure" feature works fine for C++ classes as well.

Here's an example from actual THPS2 code. For some context, originally it likely was just a plain ```TrickDatabase trickDB = new TrickDatabase();```, yet a lot of additional supporting code is added under the hood.

First, game tries to allocate memory for a new generic CClass instance, the parameter here is ```SizeOf(<your_class_to_recover>)```. Remember this number.
```
      puVar9 = .__nw__6CClassFUl(0x140c);
```

Next it checks for NULL to figure out whether memory allocation was succesful or not:
```
      if (puVar9 == NULL) {
        puVar9 = NULL;
      }
```

And finally, if it was succesful, it calls target class constructor. Typically it should be of __thiscall calling convention. Essentially we just declare that whatever we allocated for CClass should be treated as TrickDatabase:
```
      else {
        puVar9 = TrickDatabase::TrickDatabase(puVar9);
      }
```

Now open target class constructor, edit function signature, tick "Use custom storage". This will allow to modify the first "this" param.
Auto-create structure of "this", in the structure dialog, go to the bottom and type in the size of structure we got earlier in CClass constructor.

We have defined proper sized struct we can pass around and rename its fields accordingly.
Now you can keep working with it like with any other structure.

Now you can track functions that receive instances of this class and update param types accordingly, Ghidra will automatically turn address calculations to unnamed fields.

## Confusions to avoid

In this case, pointer to class instance equals to pointer to virtual table, euqals to first function in the table, which is usually a destructor.

Ghidra will put in its best guess, which is destructor function.

In reality you should check the context and figure out what it does exactly.

If it's a constructor - it's probably assigning a vtable.

If it's used as a param, it's probably a pointer to a class instance.

And if it's a delete operator function, it actually calls the destructor. Easy to spot by additional params passed in.
