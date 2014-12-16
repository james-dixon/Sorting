Sorting
=======

Playing around with different sorting algorithms

based on an STL like design:
 -> takes only iterators as arguments
 -> tested on vectors only 
 -> should also work on lists and arrays.
 
 Radix sort is nice but only works on unsigned integer types
 
 Heap sort is much slower than the others O(Nlog(N)) sorts is this due to not all being in the cache? It gets worse (more slower) as the size increases

 Parallel sorts are (very) slow for very small lists, but significantly faster for large lists

 Is it possible to beat STL for general (non-radix) sorts?

To implement:
 - shell 
 - bogo (?)
 - comb
 - bucket (related to radix)
 - counting
 - cocktail
 - tim
