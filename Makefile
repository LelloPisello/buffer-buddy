bufferbuddy.o: bb_buffer.c bb_render.c
	gcc -c -fpic -o bufferbuddy.o bb_buffer.c bb_render.c bb_render_threaded.c -Wall -O2 -pthread -lpthread -lrt

bufferbuddy.so: bufferbuddy.o
	gcc -shared -o bufferbuddy.so bufferbuddy.o
