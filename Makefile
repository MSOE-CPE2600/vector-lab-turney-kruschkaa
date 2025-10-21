CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lm -s
SOURCES= main.c vect.c input_parsing.c file_io.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=minivec

all: $(SOURCES) $(EXECUTABLE)
 
# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o: 
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d