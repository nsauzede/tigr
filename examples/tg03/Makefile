CFLAGS = -I../..
ifeq ($(OS),Windows_NT)
    LDFLAGS = -s -lopengl32 -lgdi32
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        LDFLAGS = -framework OpenGL -framework Cocoa
    else ifeq ($(UNAME_S),Linux)
        LDFLAGS = -s -lGLU -lGL -lX11
    endif
endif

all: tg03

tg03: tg03.c ../../tigr.c
	$(CC) $^ -Os -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) tg03
