# Introduction

ctegaki is a simple, yet powerful Japanese online
handwriting recognition engine.

Here online means "recognize as you write", as 
opposed of offline recognition/OCR.

It is thus suitable in a dictionary tool (to look up
kanji), or as an input keyboard for a tablet.

Compared to other libraries, cTegaki provides
character recognition that is independent of

* stroke order, and
* stroke number

This means that you can write kanji with an incorrect
stroke number and stroke order (up to a certain extent),
and yet they will still be recognized. It is thus suited
to be used by beginners of the language. 

ctegaki is a C library and provides a simple C interface.
Supported platforms are Linux and Mac OS X. Since the library
is written in C, building and compiling should also work on
Windows, but as of now, it has not been tested yet.

# Setup

Basically, setting up and using the library consists of
three steps:

1. Compiling. Note that on OSX, clang is recommended.
   You might need to symbolically link g++ to clang
   or modify the makefile
2. (optional) If no compressed binary pattern data
   exist for your platform, convert the provided xml
   pattern data to binary form with the converter tool
3. including relevant headers, and building your project.

## Compiling ctegaki

Clone the ctegaki repo

```
git clone https://github.com/asdfjkl/ctegaki-lib.git
```

Build

```
cd ctegaki-lib
make clean
make
```

You know have a static library build libctegaki.a

## (optional, make platform dependent binary data)

Right now, binary data are provided for

* Mac OSX 64 bit, Intel (data_osx64_intel.dat)
* Linux x86 (data_linux_x86.dat) 

If your platform is one of the above, you are done here
and can step to the next section. Otherwise you need
to first generate platform dependent binary recognition
data with the converter tool. Clone the converter tool

```
git clone https://github.com/asdfjkl/convert.git
```

Build the XML library ezxml, which is needed for
the converter tool:

```
cd convert
cd ezxml
make clean
make
```

Copy the resulting static lib to convert/lib/ezxml.a:

```
cd ..
mkdir lib
cd lib
cp ../ezxml/libezxml.a .
cd ..
```

Finally, compile the converter tool:

```
make clean
make
```

and convert the provided xml pattern data to a binary
format for your platform:

```
./convert -i ./xmls
```

You now have platform dependent binary file data.dat

## Use it in your project

Supplied with the library is a (very rudiment) demo on
how to use the library in your project. See ./demo/main.c

To compile go to the directioy

```
cd ctegaki-lib/demo
```

Copy libctegaki.a and data.dat

```
mkdir lib
cp ../libctegaki.a ./lib
cp ../../convert/data.dat .
```

Build and run:

```
make clean
make
./tegaki
```

The output should be ten Japanese characters.

## The sourcecode

Let's take a look at demo/main.c
First we set the locale to an UTF-8 compatible one,
in order to later print to the output:

```
setlocale(LC_ALL, "de_DE.UTF-8");
```

Next we "build" a kanji. A kanji is basically a 
number of strokes, which itself consist of points, i.e.
(x,y) coordinates.

The library assumes that the input is in the range (1,255)
for both x and y coordinates. Note that while some image
normalization is applied in the background, ideally, your
input is alredy centered at around 128,128, and uses approx.
2/3s of the whole space. To get an impression on what is optimal,
see the xml raw data in /convert/xmls

Next we load the binary data file:

```
kanjis data = load_data("data.dat");
```

and init a kanji. The kanji is our input.

```
kanji k;
k.c_strokes = 0;
k.c_points = 0;
k.xy = 0;
```

As an example, we recognize the character for "day". See
[day](http://en.wiktionary.org/wiki/%E6%97%A5)

We characterize this character by six points, and use
these six points to create four strokes.

Note that ideally much more points should be given as input
(i.e. higher density), which should come from the user
drawing with a pen or his mouse. Also here we only use
the upper left corner (range 0,120) for the ease of
presentation, and the kanji is not
centered at all. Recognition still succeeds, but in general,
this is not optimal

```
point p1,p2,p3,p4,p5,p6;
p1.x = 0;
p1.y = 0;
```

Next we create the first stroke:

```
point* stroke1 = (point*) malloc(2*sizeof(point));
```

Space is allocated for two points. Note that in general, strokes
should be exactly as long as the points they contain. In your program
you will thus probably have one array of fixed length to record
the current user's stroke, and then construct from this user input
a dedicated stroke with precise length, in order to avoid frequent 
reallocations. A stroke must _not_ have unitialized values or
zeros at the end, as this will affect the recognition.

Points are added to the first stroke:

```
stroke1[0] = p1;
stroke1[1] = p4;
```

and the stroke is added to the kanji. The second
argument denots the length of the stroke, i.e.
the number of points.

```
add_stroke(&k,stroke1,2);
```

This continues, until we build up our kanji. Time
for recognition!

```
wchar_t *results = recognize_kanji(k,data);
```

The result will _always_ a pointer to the best
ten wchar's. We can print out the recognition result:

```
for(int i=0;i<10;i++) {
    wprintf(L"%lc ",results[i]);
}
```

Tricky point here: Do not try to use both printf
and wprintf in your program. Likely, no output
from printf will be given (undefined compiler behaviour,
worked for me in OS X / Clang, but not in Linux/gcc).

