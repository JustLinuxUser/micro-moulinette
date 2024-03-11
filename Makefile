LIB_FILES = $(wildcard libs/**/*.c)
LIB_FILES += $(wildcard libs/*.c)
HDRS = $(wildcard libs/**/*.h)
HDRS += $(wildcard libs/*.h)

BDIR = build
SRCS = $(LIB_FILES)
OBJS = $(patsubst libs/%.c,$(BDIR)/%.o,$(SRCS))
CFLAGS = -I. -Ilibs/ -ggdb -march=x86-64


.PHONY=teseting
testing:
	echo $(OBJS)

$(BDIR)/%.o : libs/%.c $(HDRS)
	gcc $(CFLAGS) -c $< -o $@ 

$(BDIR)/lib.a: $(OBJS)
	ar -crs $@ $^

test: test.c $(BDIR)/lib.a
	gcc $(CFLAGS) -o $@ $^

.PHONY = run
run: test
	./test

.PHONY = lib
lib: $(BDIR)/lib.a

