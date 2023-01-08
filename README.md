# buffer-buddy
buffer buddy is a simple library that simplifies working with matrices.

### the bb_buffer_t handle
this handle is meant to be an opaque structure containing all the data the framework needs to work on your buffer. 
it acts as this library's protagonist. bb_buffer_t gets passed to almost every function in the library.

here is how you would handle one of these objects generically.
```c
//by default the buffer is going to be empty
bb_buffer_t* myBuffer = bb_buffer_create();
...
//deallocates your buffer
bb_buffer_destroy(myBuffer);
```
