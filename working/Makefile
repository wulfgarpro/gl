CC = g++

CFLAGS 	= -I. -g
LDFLAGS = -lGL -lGLU -lglut

TEMPLATE_SRC = template.cpp
TEMPLATE_OBJ = template.o

.PHONY: clean

$(TEMPLATE_OBJ): $(TEMPLATE_SRC) 
	$(CC) -c template.cpp $(CFLAGS)

%: %.cpp $(TEMPLATE_OBJ)
	$(CC) $@.cpp $(TEMPLATE_OBJ) -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *_source $(TEMPLATE_OBJ)	
