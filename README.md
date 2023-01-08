# bufferbuddy
bufferbuddy is a simple C library meant to simplify working with matrices.
the main goal is make it easier for the user to implement multi-threaded operations on these matrices.

## the way of bufferbuddy
bufferbuddy implements 2 types to make the abstraction we wanted possible: buffer handles and rendering sequences.

### buffer handles
the buffer handle type in bufferbuddy is bb_buffer_t.

bb_buffer_t is handled like this:
- an empty buffer is created:
```c
bb_buffer_t* myBuffer = bb_buffer_create();
```
- the object is either binded to an existing matrix or it gets assigned a dynamic matrix:
```c
//binding an existing matrix
int array[/*width}*/16 * /*height*/16];
//you specify width and height of the matrix, as well as the size of the single element.
bb_buffer_bind(myBuffer, array, 16, 16, sizeof(*array));
//creating a matrix private to our object
//we specify width, height and the size of the single element.
bb_buffer_allocate(myBuffer, 16, 16, sizeof(int));
```
- we use the buffer via either a rendering sequence or just by accesing its data ourselves:
```c
//this is a list of every function that can alter the array without using a rendering sequence
//returns the size of the single element of our buffer
bb_buffer_element_size(myBuffer);
//returns the width / height of our buffer
bb_buffer_width(myBuffer);
bb_buffer_height(myBuffer);
//returns BB_TRUE or BB_FALSE based on whether the buffer is binded or has been generated.
bb_buffer_is_binded(myBuffer);
//returns a pointer to the start of our buffer's actual data.
bb_buffer_data(myBuffer);
//destroys the binding between our buffer and the matrix we binded it to.
bb_buffer_unbind(myBuffer);
//destroys the dynamic matrix we created before by using bb_buffer_allocate
bb_buffer_deallocate(myBuffer);
//after having cleaned the buffer with the above two functions, you can always bind it or allocate it.
```
- we destroy the buffer.
```c
//so long.
bb_buffer_destroy(myBuffer);
```

### TODO rendering sequences

