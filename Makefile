CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread -D PROGRAM_NAME=\"$(TARGET)\"

TARGET = exec
LIBRARY = libsearch_file.a

LIB_SOURCES = search_file.c
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(LIBRARY) main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o -L . -lsearch_file

$(LIBRARY): search_file.o
	ar rc $@ $^
	ranlib $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o *.a
