CC = g++
PROG = lattu

SRCS = spinningtop.cpp imageloader.cpp text2D.cpp texture.cpp shader.cpp 

LIBS = -lglut -lGL -lGLEW

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
