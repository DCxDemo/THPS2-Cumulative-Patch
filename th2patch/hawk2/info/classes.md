# C++ classes 101

Under the hood, classes is nothing more but a structure with an array of function pointers, called virtual table or vtable.

https://pabloariasal.github.io/2017/06/10/understanding-virtual-tables/

Virtual table is a simple array of function pointers.

The very first pointer of the class structure is the pointer to the vTable.

Now instead of calling a class function directyby its address, under the hood it is recovered using vTable[functionIndex](<params) call.

If you inherit a class, it simply creates anoter vtable, copies all original function pointers and adds additional funcptr to the end of the new table.

# Recovering class structure for decompilation

Ghidra "auto-create structure" feature works fine for C++ classes as well.

Here's some example from actual THPS2 code:

First, game tries to create a new CClass instance, the parameter here is SizeOf(<your_class_to_recover_>). Remember this number.
```
      puVar9 = .__nw__6CClassFUl(0x140c);
```

Next it checks for NULL to figure out whether memory allocation was succesful or not:
```
      if (puVar9 == NULL) {
        puVar9 = NULL;
      }
```

And finally, if it was succesful, it calls target class constructor. Typically it should be of __thiscall calling convention.
```
      else {
        puVar9 = TrickDatabase::TrickDatabase(puVar9);
      }
```

Now open target class constructor, edit function signature, tick "Use custom storage". This will allow to modify the first "this" param.
Auto-create structure of "this", in the structure dialog, go to the bottom and type in the size of structure we got earlier in CClass constructor.

We have defined proper sized struct we can pass around and rename its fields accordingly.
Now you can keep working with it like with any other structure.

# Confusions to avoid

In this case, pointer to class instance equals to pointer to virtual table, euqals to first function in the table, which is usually destructor.

Ghidra will put in its best guess, which is destructor function.

In reality you should check the context and figure out what it does exactly.

If it's a constructor - it's probably assigning a vtable.

If it's used as a param, it's probably pointer to instance.

Ans if it's a delete operator function, it actually calls the destructor. Easy to spot by additional params passed in.