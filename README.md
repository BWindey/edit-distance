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

## Usage
In `edit_distance.c` there are two functions:
- `edit_distance(char*, uint len1, char*, uint len2)`:
    calculates the edit distance between two given strings of given length
- `has_max_edit_distance(char*, uint len1, char*, uint len2, uint max_distance)`:
    calculates whether the edit distance is <= the max_distance

That second function was inspired by me learning about the Levenshtein Automaton,
an automaton that you can create in linear time for a search-word, and then
test in linear time against many other words (f.e. all words in a dictionary),
as oposed to the `Th(n * m)` you normally get.
I looked into implementing that, but that's above my current skillset, so instead
I looked where we can return early inside the `edit_distance()` function to
prevent computing more then needed, and that's where `has_max_edit_distance()`
comes into view. You can see under the Benchmark section at the end of this
README that it does manage to perform a bit better.


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


## Benchmarks:
I ran benchmarks with
`gcc -O3 -D LIBRARY -c edit_distance.c && c3c compile-run misc/test.c3 edit_distance.o`:
```
-------------- BENCHMARKS --------------
Benchmarking test::normal_short ... [COMPLETE] 29.75 milliseconds, 95026560.00 CPU clocks, 10000 iterations (runtime 297.52 seconds)
Benchmarking test::normal_long .... [COMPLETE] 52.98 milliseconds, 169220560.00 CPU clocks, 10000 iterations (runtime 529.81 seconds)
Benchmarking test::has_max_short .. [COMPLETE] 17.76 milliseconds, 56712600.00 CPU clocks, 10000 iterations (runtime 177.56 seconds)
Benchmarking test::has_max_long ... [COMPLETE] 19.07 milliseconds, 60902256.00 CPU clocks, 10000 iterations (runtime 190.68 seconds)
```
With `-march=native` on only the `gcc` part:
```
Benchmarking test::normal_short ... [COMPLETE] 30.67 milliseconds, 97951192.00 CPU clocks, 10000 iterations (runtime 306.67 seconds)
Benchmarking test::normal_long .... [COMPLETE] 52.43 milliseconds, 167448432.00 CPU clocks, 10000 iterations (runtime 524.26 seconds)
Benchmarking test::has_max_short .. [COMPLETE] 16.99 milliseconds, 54257372.00 CPU clocks, 10000 iterations (runtime 169.87 seconds)
Benchmarking test::has_max_long ... [COMPLETE] 18.31 milliseconds, 58489276.00 CPU clocks, 10000 iterations (runtime 183.12 seconds)
```
(Slight improvement might be because I closed Discord, but my system
only was at ~20% cpu useage max.)
Maybe I should implement it in assembly?

The `short` benchmark tests `brain` against all words inside
`/usr/share/dict/words` (all english words) with a maximum edit distance of 2.

The `long` benchmark tests `unsophisticated` against the same word set with
a maximum edit distance of 4.

The `normal` benchmark uses `edit_distance(word1, word2) <= k`, while the
`has_max` benchmark uses the `has_max_edit_distance(word1, word2, k)` function,
which is an edited version of `edit_distance()` that can return early.

The used benchmark code is still available under `misc/test.c3`.
