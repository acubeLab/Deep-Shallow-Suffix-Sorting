# Deep-Shallow suffix sorting

This repository contains the companion code of the paper "Engineering a Lightweight Suffix Array
Construction Algorithm" by Giovanni Manzini and Paolo Ferragina, first published in the Proceedings of the [European Symposium on Algorithms, 2002](https://doi.org/10.1007/3-540-45749-6_61) and later, in extended format, in [Algorithmica 40:33–50, 2004](https://doi.org/10.1007/s00453-004-1094-1). The paper won the [2023 ESA Test of Time Award](https://algo-conference.org/esa/test-of-time-award/) since it was (quoting the award committee): "a significant step towards the efficient solution of an importat practical problem".

The algorithm computes the Suffix Array, and possibly the Burrows-Wheeler Transform, of an input text of size at most $2^{31}-1$ over the standard byte alphabet. The main feature of the algorithm is that it is lighweight in the sense that it uses very little space in addition to space used by the input (the text) and the output (the suffix array), see the above papers for further details. Although the algorithm was a standard reference for many years, it is no longer the state of the art for suffix array construction. For most practical uses we recommend [libdivsufsort](https://github.com/y-256/libdivsufsort) by Yuta Mori which is also lightweight and very fast in practice. Other alternatives are the algorithms SAIS and SACA-K by Ge Nong et al. for example in the [implementation of Felipe Louza](https://github.com/felipelouza/gsa-is) that offers a simple and uniform API. 


For an in-depth evaluation of the availble suffix array construction algorithms see the paper  
[SACABench: Benchmarking Suffix Array Construction](https://link.springer.com/chapter/10.1007/978-3-030-32686-9_29) and the [companion repository](https://github.com/sacabench/sacabench).



## Running the algorithm

As we stated above, the algorithm is no longer the state of the art, however the code should compile on any linux/unix system. To try it just clone/download and then `make`. This should produce the following executable (without any no error or warining):

* `sa32`: computes the suffix array of an input file and store the result using 4 bytes per entry

* `ds`: computes the suffix array, and optionally the BWT of an input file and store the result using $\lceil\log n\rceil$ bits per entry. Allows to change all the internal parameters of the algorithm 

* `bwt`: computes the suffix array and then the BWT saving only the latter. The BWT is stored using one byte x entry following by 4 bytes storing the EOS position

* `unbwt`: takes as input a file produced by `bwt` and recover the original input file


If for some reason you need to use this algorithm in your project look at the `sa32.c` file which shows the simplest usage using the default parameters.  



## Additional software

The repository contains also the implementations of the LCP array construction algorithms described in the paper "Two Space Saving Tricks for Linear Time LCP Array Computation" published in the Proceedings of the [Scandinavian Workshop on Algorithm Theory, 2004](https://link.springer.com/chapter/10.1007/978-3-540-27810-8_32) (files `bwt_aux.c` and `lcp_aux.c`). The executable `testlcp` computes the suffix array using Deep-Shallow suffix sorting and then the LCP array using the algorithms described in the paper (called `lcp9`, `lcp13`, `lcp9125` and `lcp6`).

