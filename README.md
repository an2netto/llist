<p align="center">
  <b>llist</b><br>
  <a>A circular linked list dynamic library</a>
</p>

##### WTF

The library is a set of operations on type oblivious, easy-to-use, circularly-linked list.

#### Usage:
``` c
struct my_kernail_list {
         int data;
         char c;
         struct list_head list;
};
```
The list is inside the user-defined data item. A member of type `struct list_head` can be anywhere in the user-defined structure. The `struct list_head` variable can have any name.

_**llist** is not meant to be embedded into any project and is for pracice's sake only._

#### Build from source on Mac:

``` console
gcc -shared -fpic llist.c -o libllist.dylib
```

To test the library compile and run:

``` console
gcc -o test test.c libllist.dylib
./test
```

#### Build from source on Ubuntu:

Compile the library sources into position-independent code:
``` console
gcc -c -Wall -Werror -fpic llist.c
```

Turn the object file into a shared library:

``` console
gcc -shared -o libllist.so llist.o
```

The run path will embed location in the executable during the linking
stage, instead of relying on default locations or environment variables.

``` console
gcc -L. -Wl,-rpath=. -Wall -o test test.c -lllist
```
  * **-L** tells the linker where to find the library.

  * **-Wl** sends comma-separated options to the linker.

  * **-rpath** tells the loader where to find the library.
