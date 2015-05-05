CC = g++
CFLAGS = -Wall
PROG = terrain

SRCS = main.cpp imageloader.cpp vec3f.cpp
LIBS = -lglut -lGLU -lGL

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
