# source files.
SRC = ctegaki.c recognizer.c binary.c rasterize.c normalize.c strokemap.c kanjis.c kanji.c math_ext.c distance.c
 
OBJ = $(SRC:.c=.o)
 
OUT = ./libctegaki.a
 
# include directories
#INCLUDES = -I/Library/Developer/CommandLineTools/usr/lib/clang/6.0/include 
#INCLUDES = -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/5.1/include
#INCLUDES = -I. -I../include/ -I/home/newhall/include -I../usr/include
 
# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = -g -static
 
# compiler
CCC = g++
 
# library paths
LIBS = -L../ -L/usr/local/lib -L./lib -lezxml
 
# compile flags
LDFLAGS = -g
 
.SUFFIXES: .c
 
default: dep $(OUT)
 
.c.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@
 
$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ)
 
depend: dep
 
dep:
	makedepend -- $(CFLAGS) -- $(INCLUDES) $(SRC)
 
clean:
	rm -f $(OBJ) $(OUT)
# DO NOT DELETE

ctegaki.o: /usr/include/stdio.h /usr/include/features.h /usr/include/libio.h
ctegaki.o: /usr/include/_G_config.h /usr/include/wchar.h
ctegaki.o: /usr/include/xlocale.h ezxml.h /usr/include/stdlib.h
ctegaki.o: /usr/include/alloca.h /usr/include/fcntl.h /usr/include/time.h
ctegaki.o: xml.h kanji.h /usr/include/stdint.h binary.h kanjis.h globals.h
ctegaki.o: normalize.h /usr/include/locale.h distance.h strokemap.h
ctegaki.o: rasterize.h recognizer.h tinydir.h /usr/include/errno.h
ctegaki.o: /usr/include/string.h /usr/include/dirent.h /usr/include/libgen.h
recognizer.o: kanji.h /usr/include/stdint.h /usr/include/features.h
recognizer.o: /usr/include/stdlib.h /usr/include/alloca.h kanjis.h binary.h
recognizer.o: /usr/include/wchar.h /usr/include/stdio.h /usr/include/libio.h
recognizer.o: /usr/include/_G_config.h /usr/include/xlocale.h distance.h
recognizer.o: strokemap.h math_ext.h
binary.o: /usr/include/stdlib.h /usr/include/features.h /usr/include/alloca.h
binary.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
binary.o: /usr/include/wchar.h /usr/include/xlocale.h kanji.h
binary.o: /usr/include/stdint.h kanjis.h
rasterize.o: /usr/include/stdio.h /usr/include/features.h
rasterize.o: /usr/include/libio.h /usr/include/_G_config.h
rasterize.o: /usr/include/wchar.h /usr/include/xlocale.h
rasterize.o: /usr/include/string.h kanji.h /usr/include/stdint.h
rasterize.o: /usr/include/stdlib.h /usr/include/alloca.h math_ext.h globals.h
rasterize.o: distance.h
normalize.o: globals.h kanji.h /usr/include/stdint.h /usr/include/features.h
normalize.o: /usr/include/stdlib.h /usr/include/alloca.h /usr/include/stdio.h
normalize.o: /usr/include/libio.h /usr/include/_G_config.h
normalize.o: /usr/include/wchar.h /usr/include/xlocale.h /usr/include/math.h
strokemap.o: /usr/include/stdint.h /usr/include/features.h
strokemap.o: /usr/include/stdlib.h /usr/include/alloca.h /usr/include/stdio.h
strokemap.o: /usr/include/libio.h /usr/include/_G_config.h
strokemap.o: /usr/include/wchar.h /usr/include/xlocale.h distance.h kanji.h
strokemap.o: math_ext.h
kanjis.o: kanji.h /usr/include/stdint.h /usr/include/features.h
kanjis.o: /usr/include/stdlib.h /usr/include/alloca.h
kanji.o: /usr/include/stdio.h /usr/include/features.h /usr/include/libio.h
kanji.o: /usr/include/_G_config.h /usr/include/wchar.h /usr/include/xlocale.h
kanji.o: /usr/include/stdint.h /usr/include/stdlib.h /usr/include/alloca.h
kanji.o: /usr/include/string.h math_ext.h
math_ext.o: /usr/include/math.h /usr/include/features.h
distance.o: /usr/include/stdint.h /usr/include/features.h
distance.o: /usr/include/stdlib.h /usr/include/alloca.h /usr/include/math.h
distance.o: /usr/include/stdio.h /usr/include/libio.h
distance.o: /usr/include/_G_config.h /usr/include/wchar.h
distance.o: /usr/include/xlocale.h math_ext.h kanji.h globals.h
