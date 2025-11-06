# Edit distance / Levenshtein distance
The edit distance (or Levenshtein distance) is a metric that specifies
how close two words are to each other. The distance is defined as the
minimal amount of insertions, deletions and/or substitutions of individual
characters to transform one word into the other.

Included in this repository are two different implementations: one simple
implementation that you would mimick when calculating the distance by hand,
and one that only keeps the last two rows (which is recommended for real use).

I left the table implementation in as a reference, and to have a program that
can print out table (altough that printing could be done in the better version
as well).


## Compilation
Both c-files have to be compiled seperatly with your favourite C compiler,
with gcc it might look like this:
```
gcc -O3 edit_distance.c -o edit_distance
```

The resulting program can be used like this:
```
./edit_distance banana ananas

Edit distance: 2
```


### Compiling to a library
When you want to include this as a library, you can specify the `-D LIBRARY`
macro:
```
gcc -O3 -D LIBRARY -c edit_distance.c -o edit_distance.o
```
This will strip the `main` function. You could also modify the source file
before compiling to not need the `-D LIBRARY`.


### Misc
Inside the `misc/` folder there are two little programs that do the same as the
main program compiled without `-D LIBARARY`, but that I wanted to include
just for the sake of trying out linking with an object file. Do with them
as you please.
