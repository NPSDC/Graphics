CC = g++
PROG = sampleCode

SRCS = sampleCode_openGL3.cpp

LIBS = -lglut -lGL -lGLEW

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
