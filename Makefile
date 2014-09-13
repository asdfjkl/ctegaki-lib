# source files.
SRC = ctegaki.c recognizer.c xml.c binary.c rasterize.c normalize.c strokemap.c kanjis.c kanji.c math_ext.c distance.c
 
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

ctegaki.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
ctegaki.o: /usr/include/sys/_symbol_aliasing.h
ctegaki.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
ctegaki.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
ctegaki.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
ctegaki.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
ctegaki.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
ctegaki.o: /usr/include/sys/_types/_off_t.h
ctegaki.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
ctegaki.o: /usr/include/secure/_common.h ezxml.h /usr/include/stdlib.h
ctegaki.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
ctegaki.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
ctegaki.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
ctegaki.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
ctegaki.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
ctegaki.o: /usr/include/sys/_types/_sigaltstack.h
ctegaki.o: /usr/include/sys/_types/_ucontext.h
ctegaki.o: /usr/include/sys/_types/_pthread_attr_t.h
ctegaki.o: /usr/include/sys/_types/_sigset_t.h
ctegaki.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
ctegaki.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
ctegaki.o: /usr/include/sys/_types/_int16_t.h
ctegaki.o: /usr/include/sys/_types/_int32_t.h
ctegaki.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
ctegaki.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
ctegaki.o: /usr/include/_types/_uint64_t.h
ctegaki.o: /usr/include/sys/_types/_intptr_t.h
ctegaki.o: /usr/include/sys/_types/_uintptr_t.h
ctegaki.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
ctegaki.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
ctegaki.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
ctegaki.o: /usr/include/libkern/_OSByteOrder.h
ctegaki.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
ctegaki.o: /usr/include/sys/_types/_ct_rune_t.h
ctegaki.o: /usr/include/sys/_types/_rune_t.h
ctegaki.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
ctegaki.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
ctegaki.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
ctegaki.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h
ctegaki.o: /usr/include/sys/_types/_o_sync.h
ctegaki.o: /usr/include/sys/_types/_o_dsync.h
ctegaki.o: /usr/include/sys/_types/_seek_set.h
ctegaki.o: /usr/include/sys/_types/_s_ifmt.h
ctegaki.o: /usr/include/sys/_types/_timespec.h
ctegaki.o: /usr/include/sys/_types/_filesec_t.h xml.h kanji.h binary.h
ctegaki.o: kanjis.h globals.h normalize.h /usr/include/wchar.h
ctegaki.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/time.h
ctegaki.o: /usr/include/_structs.h /usr/include/sys/_structs.h
ctegaki.o: /usr/include/sys/_types/_clock_t.h
ctegaki.o: /usr/include/sys/_types/_time_t.h /usr/include/_wctype.h
ctegaki.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
ctegaki.o: /usr/include/ctype.h /usr/include/runetype.h /usr/include/locale.h
ctegaki.o: /usr/include/_locale.h distance.h strokemap.h rasterize.h
ctegaki.o: recognizer.h tinydir.h /usr/include/errno.h
ctegaki.o: /usr/include/sys/errno.h /usr/include/sys/_types/_errno_t.h
ctegaki.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
ctegaki.o: /usr/include/strings.h /usr/include/secure/_string.h
ctegaki.o: /usr/include/dirent.h /usr/include/sys/dirent.h
ctegaki.o: /usr/include/sys/_types/_ino_t.h /usr/include/libgen.h
ctegaki.o: /usr/include/sys/stat.h /usr/include/sys/_types/_blkcnt_t.h
ctegaki.o: /usr/include/sys/_types/_blksize_t.h
ctegaki.o: /usr/include/sys/_types/_ino64_t.h
ctegaki.o: /usr/include/sys/_types/_nlink_t.h
ctegaki.o: /usr/include/sys/_types/_gid_t.h
recognizer.o: kanji.h /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
recognizer.o: /usr/include/sys/_types/_int16_t.h
recognizer.o: /usr/include/sys/_types/_int32_t.h
recognizer.o: /usr/include/sys/_types/_int64_t.h
recognizer.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
recognizer.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
recognizer.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
recognizer.o: /usr/include/sys/_symbol_aliasing.h
recognizer.o: /usr/include/sys/_posix_availability.h
recognizer.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
recognizer.o: /usr/include/sys/_types/_intptr_t.h
recognizer.o: /usr/include/sys/_types/_uintptr_t.h
recognizer.o: /usr/include/_types/_intmax_t.h
recognizer.o: /usr/include/_types/_uintmax_t.h /usr/include/stdlib.h
recognizer.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
recognizer.o: /usr/include/_types.h /usr/include/sys/wait.h
recognizer.o: /usr/include/sys/_types/_pid_t.h
recognizer.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
recognizer.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
recognizer.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
recognizer.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
recognizer.o: /usr/include/sys/_types/_sigaltstack.h
recognizer.o: /usr/include/sys/_types/_ucontext.h
recognizer.o: /usr/include/sys/_types/_pthread_attr_t.h
recognizer.o: /usr/include/sys/_types/_sigset_t.h
recognizer.o: /usr/include/sys/_types/_size_t.h
recognizer.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
recognizer.o: /usr/include/sys/_types/_timeval.h
recognizer.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
recognizer.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
recognizer.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
recognizer.o: /usr/include/sys/_types/_ct_rune_t.h
recognizer.o: /usr/include/sys/_types/_rune_t.h
recognizer.o: /usr/include/sys/_types/_wchar_t.h
recognizer.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
recognizer.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
recognizer.o: /usr/include/sys/_types/_dev_t.h
recognizer.o: /usr/include/sys/_types/_mode_t.h kanjis.h binary.h
recognizer.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
recognizer.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
recognizer.o: /usr/include/sys/_types/_off_t.h
recognizer.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
recognizer.o: /usr/include/secure/_common.h /usr/include/time.h
recognizer.o: /usr/include/_structs.h /usr/include/sys/_structs.h
recognizer.o: /usr/include/sys/_types/_timespec.h
recognizer.o: /usr/include/sys/_types/_clock_t.h
recognizer.o: /usr/include/sys/_types/_time_t.h /usr/include/_wctype.h
recognizer.o: /usr/include/sys/_types/_wint_t.h
recognizer.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
recognizer.o: /usr/include/runetype.h distance.h strokemap.h math_ext.h
xml.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
xml.o: /usr/include/sys/_symbol_aliasing.h
xml.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
xml.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
xml.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
xml.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
xml.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
xml.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
xml.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h ezxml.h
xml.o: /usr/include/stdlib.h /usr/include/sys/wait.h
xml.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
xml.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
xml.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
xml.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
xml.o: /usr/include/mach/i386/_structs.h
xml.o: /usr/include/sys/_types/_sigaltstack.h
xml.o: /usr/include/sys/_types/_ucontext.h
xml.o: /usr/include/sys/_types/_pthread_attr_t.h
xml.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
xml.o: /usr/include/sys/resource.h /usr/include/stdint.h
xml.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
xml.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
xml.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
xml.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
xml.o: /usr/include/sys/_types/_intptr_t.h
xml.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
xml.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
xml.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
xml.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
xml.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
xml.o: /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h
xml.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
xml.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
xml.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
xml.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h
xml.o: /usr/include/sys/_types/_o_sync.h /usr/include/sys/_types/_o_dsync.h
xml.o: /usr/include/sys/_types/_seek_set.h /usr/include/sys/_types/_s_ifmt.h
xml.o: /usr/include/sys/_types/_timespec.h
xml.o: /usr/include/sys/_types/_filesec_t.h kanji.h /usr/include/string.h
xml.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
xml.o: /usr/include/strings.h /usr/include/secure/_string.h
xml.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
xml.o: /usr/include/time.h /usr/include/_structs.h
xml.o: /usr/include/sys/_structs.h /usr/include/sys/_types/_clock_t.h
xml.o: /usr/include/sys/_types/_time_t.h /usr/include/_wctype.h
xml.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
xml.o: /usr/include/ctype.h /usr/include/runetype.h /usr/include/locale.h
xml.o: /usr/include/_locale.h
binary.o: /usr/include/stdlib.h /usr/include/Availability.h
binary.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
binary.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
binary.o: /usr/include/sys/_symbol_aliasing.h
binary.o: /usr/include/sys/_posix_availability.h
binary.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
binary.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
binary.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
binary.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
binary.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
binary.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
binary.o: /usr/include/sys/_types/_sigaltstack.h
binary.o: /usr/include/sys/_types/_ucontext.h
binary.o: /usr/include/sys/_types/_pthread_attr_t.h
binary.o: /usr/include/sys/_types/_sigset_t.h
binary.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_uid_t.h
binary.o: /usr/include/sys/resource.h /usr/include/stdint.h
binary.o: /usr/include/sys/_types/_int8_t.h
binary.o: /usr/include/sys/_types/_int16_t.h
binary.o: /usr/include/sys/_types/_int32_t.h
binary.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
binary.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
binary.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
binary.o: /usr/include/sys/_types/_uintptr_t.h
binary.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
binary.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
binary.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
binary.o: /usr/include/libkern/_OSByteOrder.h
binary.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
binary.o: /usr/include/sys/_types/_ct_rune_t.h
binary.o: /usr/include/sys/_types/_rune_t.h
binary.o: /usr/include/sys/_types/_wchar_t.h /usr/include/sys/_types/_null.h
binary.o: /usr/include/machine/types.h /usr/include/i386/types.h
binary.o: /usr/include/sys/_types/___offsetof.h
binary.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
binary.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
binary.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
binary.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h kanji.h
binary.o: kanjis.h
rasterize.o: /usr/include/stdbool.h /usr/include/stdio.h
rasterize.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
rasterize.o: /usr/include/sys/_posix_availability.h
rasterize.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
rasterize.o: /usr/include/_types.h /usr/include/sys/_types.h
rasterize.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
rasterize.o: /usr/include/sys/_types/_va_list.h
rasterize.o: /usr/include/sys/_types/_size_t.h
rasterize.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_off_t.h
rasterize.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
rasterize.o: /usr/include/secure/_common.h /usr/include/string.h
rasterize.o: /usr/include/sys/_types/_rsize_t.h
rasterize.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
rasterize.o: /usr/include/secure/_string.h kanji.h /usr/include/stdint.h
rasterize.o: /usr/include/sys/_types/_int8_t.h
rasterize.o: /usr/include/sys/_types/_int16_t.h
rasterize.o: /usr/include/sys/_types/_int32_t.h
rasterize.o: /usr/include/sys/_types/_int64_t.h
rasterize.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
rasterize.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
rasterize.o: /usr/include/sys/_types/_intptr_t.h
rasterize.o: /usr/include/sys/_types/_uintptr_t.h
rasterize.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
rasterize.o: /usr/include/stdlib.h /usr/include/sys/wait.h
rasterize.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
rasterize.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
rasterize.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
rasterize.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
rasterize.o: /usr/include/mach/i386/_structs.h
rasterize.o: /usr/include/sys/_types/_sigaltstack.h
rasterize.o: /usr/include/sys/_types/_ucontext.h
rasterize.o: /usr/include/sys/_types/_pthread_attr_t.h
rasterize.o: /usr/include/sys/_types/_sigset_t.h
rasterize.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
rasterize.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
rasterize.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
rasterize.o: /usr/include/libkern/_OSByteOrder.h
rasterize.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
rasterize.o: /usr/include/sys/_types/_ct_rune_t.h
rasterize.o: /usr/include/sys/_types/_rune_t.h
rasterize.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
rasterize.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
rasterize.o: /usr/include/sys/_types/_dev_t.h
rasterize.o: /usr/include/sys/_types/_mode_t.h math_ext.h globals.h
rasterize.o: distance.h
normalize.o: globals.h kanji.h /usr/include/stdint.h
normalize.o: /usr/include/sys/_types/_int8_t.h
normalize.o: /usr/include/sys/_types/_int16_t.h
normalize.o: /usr/include/sys/_types/_int32_t.h
normalize.o: /usr/include/sys/_types/_int64_t.h
normalize.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
normalize.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
normalize.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
normalize.o: /usr/include/sys/_symbol_aliasing.h
normalize.o: /usr/include/sys/_posix_availability.h
normalize.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
normalize.o: /usr/include/sys/_types/_intptr_t.h
normalize.o: /usr/include/sys/_types/_uintptr_t.h
normalize.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
normalize.o: /usr/include/stdlib.h /usr/include/Availability.h
normalize.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
normalize.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
normalize.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
normalize.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
normalize.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
normalize.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
normalize.o: /usr/include/sys/_types/_sigaltstack.h
normalize.o: /usr/include/sys/_types/_ucontext.h
normalize.o: /usr/include/sys/_types/_pthread_attr_t.h
normalize.o: /usr/include/sys/_types/_sigset_t.h
normalize.o: /usr/include/sys/_types/_size_t.h
normalize.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
normalize.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
normalize.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
normalize.o: /usr/include/libkern/_OSByteOrder.h
normalize.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
normalize.o: /usr/include/sys/_types/_ct_rune_t.h
normalize.o: /usr/include/sys/_types/_rune_t.h
normalize.o: /usr/include/sys/_types/_wchar_t.h
normalize.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
normalize.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
normalize.o: /usr/include/sys/_types/_dev_t.h
normalize.o: /usr/include/sys/_types/_mode_t.h /usr/include/stdio.h
normalize.o: /usr/include/sys/_types/_va_list.h
normalize.o: /usr/include/sys/_types/_off_t.h
normalize.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
normalize.o: /usr/include/secure/_common.h /usr/include/math.h
strokemap.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
strokemap.o: /usr/include/sys/_types/_int16_t.h
strokemap.o: /usr/include/sys/_types/_int32_t.h
strokemap.o: /usr/include/sys/_types/_int64_t.h
strokemap.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
strokemap.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
strokemap.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
strokemap.o: /usr/include/sys/_symbol_aliasing.h
strokemap.o: /usr/include/sys/_posix_availability.h
strokemap.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
strokemap.o: /usr/include/sys/_types/_intptr_t.h
strokemap.o: /usr/include/sys/_types/_uintptr_t.h
strokemap.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
strokemap.o: /usr/include/stdlib.h /usr/include/Availability.h
strokemap.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
strokemap.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
strokemap.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
strokemap.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
strokemap.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
strokemap.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
strokemap.o: /usr/include/sys/_types/_sigaltstack.h
strokemap.o: /usr/include/sys/_types/_ucontext.h
strokemap.o: /usr/include/sys/_types/_pthread_attr_t.h
strokemap.o: /usr/include/sys/_types/_sigset_t.h
strokemap.o: /usr/include/sys/_types/_size_t.h
strokemap.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
strokemap.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
strokemap.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
strokemap.o: /usr/include/libkern/_OSByteOrder.h
strokemap.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
strokemap.o: /usr/include/sys/_types/_ct_rune_t.h
strokemap.o: /usr/include/sys/_types/_rune_t.h
strokemap.o: /usr/include/sys/_types/_wchar_t.h
strokemap.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
strokemap.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
strokemap.o: /usr/include/sys/_types/_dev_t.h
strokemap.o: /usr/include/sys/_types/_mode_t.h /usr/include/stdio.h
strokemap.o: /usr/include/sys/_types/_va_list.h
strokemap.o: /usr/include/sys/_types/_off_t.h
strokemap.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
strokemap.o: /usr/include/secure/_common.h /usr/include/stdbool.h distance.h
strokemap.o: kanji.h xml.h math_ext.h
kanjis.o: kanji.h /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
kanjis.o: /usr/include/sys/_types/_int16_t.h
kanjis.o: /usr/include/sys/_types/_int32_t.h
kanjis.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
kanjis.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
kanjis.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
kanjis.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
kanjis.o: /usr/include/sys/_posix_availability.h
kanjis.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
kanjis.o: /usr/include/sys/_types/_intptr_t.h
kanjis.o: /usr/include/sys/_types/_uintptr_t.h
kanjis.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
kanjis.o: /usr/include/stdlib.h /usr/include/Availability.h
kanjis.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
kanjis.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
kanjis.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
kanjis.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
kanjis.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
kanjis.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
kanjis.o: /usr/include/sys/_types/_sigaltstack.h
kanjis.o: /usr/include/sys/_types/_ucontext.h
kanjis.o: /usr/include/sys/_types/_pthread_attr_t.h
kanjis.o: /usr/include/sys/_types/_sigset_t.h
kanjis.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_uid_t.h
kanjis.o: /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h
kanjis.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
kanjis.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
kanjis.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
kanjis.o: /usr/include/sys/_types/_ct_rune_t.h
kanjis.o: /usr/include/sys/_types/_rune_t.h
kanjis.o: /usr/include/sys/_types/_wchar_t.h /usr/include/sys/_types/_null.h
kanjis.o: /usr/include/machine/types.h /usr/include/i386/types.h
kanjis.o: /usr/include/sys/_types/___offsetof.h
kanjis.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
kanji.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
kanji.o: /usr/include/sys/_symbol_aliasing.h
kanji.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
kanji.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
kanji.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
kanji.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
kanji.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
kanji.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
kanji.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
kanji.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
kanji.o: /usr/include/sys/_types/_int16_t.h
kanji.o: /usr/include/sys/_types/_int32_t.h
kanji.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
kanji.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
kanji.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
kanji.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
kanji.o: /usr/include/_types/_uintmax_t.h /usr/include/stdlib.h
kanji.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
kanji.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
kanji.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
kanji.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
kanji.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
kanji.o: /usr/include/sys/_types/_sigaltstack.h
kanji.o: /usr/include/sys/_types/_ucontext.h
kanji.o: /usr/include/sys/_types/_pthread_attr_t.h
kanji.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
kanji.o: /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h
kanji.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
kanji.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
kanji.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
kanji.o: /usr/include/sys/_types/_ct_rune_t.h
kanji.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
kanji.o: /usr/include/machine/types.h /usr/include/i386/types.h
kanji.o: /usr/include/sys/_types/___offsetof.h
kanji.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
kanji.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
kanji.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
kanji.o: /usr/include/secure/_string.h math_ext.h
math_ext.o: /usr/include/math.h /usr/include/sys/cdefs.h
math_ext.o: /usr/include/sys/_symbol_aliasing.h
math_ext.o: /usr/include/sys/_posix_availability.h
math_ext.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
distance.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
distance.o: /usr/include/sys/_types/_int16_t.h
distance.o: /usr/include/sys/_types/_int32_t.h
distance.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
distance.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
distance.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
distance.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
distance.o: /usr/include/sys/_posix_availability.h
distance.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
distance.o: /usr/include/sys/_types/_intptr_t.h
distance.o: /usr/include/sys/_types/_uintptr_t.h
distance.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
distance.o: /usr/include/stdlib.h /usr/include/Availability.h
distance.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
distance.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
distance.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
distance.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
distance.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
distance.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
distance.o: /usr/include/sys/_types/_sigaltstack.h
distance.o: /usr/include/sys/_types/_ucontext.h
distance.o: /usr/include/sys/_types/_pthread_attr_t.h
distance.o: /usr/include/sys/_types/_sigset_t.h
distance.o: /usr/include/sys/_types/_size_t.h
distance.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
distance.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
distance.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
distance.o: /usr/include/libkern/_OSByteOrder.h
distance.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
distance.o: /usr/include/sys/_types/_ct_rune_t.h
distance.o: /usr/include/sys/_types/_rune_t.h
distance.o: /usr/include/sys/_types/_wchar_t.h
distance.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
distance.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
distance.o: /usr/include/sys/_types/_dev_t.h
distance.o: /usr/include/sys/_types/_mode_t.h /usr/include/math.h
distance.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
distance.o: /usr/include/sys/_types/_off_t.h
distance.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
distance.o: /usr/include/secure/_common.h math_ext.h kanji.h globals.h
