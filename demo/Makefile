#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -Wall -g

# define any directories containing header files other than /usr/include
#
INCLUDES = 
#-I/home/newhall/include  -I../usr/include

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L./lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lctegaki 

# define the C source files
SRCS = main.c

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# define the executable file 
MAIN = tegaki

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:	$(MAIN)
	@echo	compilation finished

$(MAIN): $(OBJS) 
		$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

main.o: ctegaki.h xml.h kanji.h /usr/include/stdint.h
main.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
main.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
main.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
main.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
main.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
main.o: /usr/include/sys/_symbol_aliasing.h
main.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
main.o: /usr/include/i386/_types.h /usr/include/sys/_types/_intptr_t.h
main.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
main.o: /usr/include/_types/_uintmax_t.h /usr/include/stdlib.h
main.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
main.o: /usr/include/_types.h /usr/include/sys/wait.h
main.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
main.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
main.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
main.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
main.o: /usr/include/mach/i386/_structs.h
main.o: /usr/include/sys/_types/_sigaltstack.h
main.o: /usr/include/sys/_types/_ucontext.h
main.o: /usr/include/sys/_types/_pthread_attr_t.h
main.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_size_t.h
main.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
main.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
main.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
main.o: /usr/include/libkern/_OSByteOrder.h
main.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
main.o: /usr/include/sys/_types/_ct_rune_t.h
main.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
main.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
main.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
main.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
main.o: binary.h kanjis.h globals.h /usr/include/wchar.h
main.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/stdio.h
main.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/_types/_off_t.h
main.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
main.o: /usr/include/secure/_common.h /usr/include/time.h
main.o: /usr/include/_structs.h /usr/include/sys/_structs.h
main.o: /usr/include/sys/_types/_timespec.h
main.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h
main.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
main.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
main.o: /usr/include/runetype.h /usr/include/locale.h /usr/include/_locale.h
main.o: distance.h strokemap.h rasterize.h recognizer.h tinydir.h
main.o: /usr/include/errno.h /usr/include/sys/errno.h
main.o: /usr/include/sys/_types/_errno_t.h /usr/include/string.h
main.o: /usr/include/sys/_types/_rsize_t.h /usr/include/strings.h
main.o: /usr/include/secure/_string.h /usr/include/dirent.h
main.o: /usr/include/sys/dirent.h /usr/include/sys/_types/_ino_t.h
main.o: /usr/include/libgen.h /usr/include/sys/stat.h
main.o: /usr/include/sys/_types/_blkcnt_t.h
main.o: /usr/include/sys/_types/_blksize_t.h
main.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_nlink_t.h
main.o: /usr/include/sys/_types/_gid_t.h /usr/include/sys/_types/_s_ifmt.h
main.o: /usr/include/sys/_types/_filesec_t.h
