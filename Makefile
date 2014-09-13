CC = g++
AR = ar
RM = rm -f
CFLAGS = -Wall -O2
OBJS = ctegaki.o recognizer.o binary.o rasterize.o normalize.o strokemap.o kanjis.o kanji.o math_ext.o distance.o 
LIB = libctegaki.a

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) rcs $(LIB) $(OBJS)

debug: all

ctegaki.o: ctegaki.h ctegaki.c
recognizer.o: recognizer.h recognizer.c
binary.o: binary.h binary.c
rasterize.o: rasterize.h rasterize.c
normalize.o: normalize.h normalize.c
strokemap.o: strokemap.h strokemap.c
kanjis.o: kanjis.h kanjis.c
kanji.o: kanji.h kanji.c
math_ext.o: math_ext.h math_ext.c
distance.o: distance.h distance.c

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS) $(LIB) $(TEST) *~
