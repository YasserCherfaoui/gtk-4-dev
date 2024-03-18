CC=clang
CFLAGS=-Wall `pkg-config --cflags gtk4`
LIBS=`pkg-config --libs gtk4`

TARGET=myapp

$(TARGET): main.o
	$(CC) -o $(TARGET) main.o $(LIBS)

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f *.o $(TARGET)

