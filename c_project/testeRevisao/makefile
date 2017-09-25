CC = gcc
CFLAGS=-Wall -g -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include/libxml2 -L/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/lib -lxml2 -lz -lpthread -licucore -lm
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

prog: $(OBJS)
		$(CC) $(CFLAGS) -o prog $(OBJS) $(LIBS)

clean:
		rm prog *.o
