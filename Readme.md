# Deep-Shallow suffix sorting

This repository contains the companion code of the paper "Engineering a Lightweight Suffix Array
Construction Algorithm" by Giovanni Manzini and Paolo Ferragina first published in the Proceedings of the [European Symposium on Algorithms, 2002](https://doi.org/10.1007/3-540-45749-6_61) and later, in extended format, in [Algorithmica 40:33–50, 2004](https://doi.org/10.1007/s00453-004-1094-1). The paper won the [2023 ESA Test of Time Award](https://algo-conference.org/esa/test-of-time-award/) since it was (quting the award committee): "a significant step towards the efficient solution of an importat practical problem".

The algorithm computes the Suffix Array, and possibly the Burrows-Wheeler Transform, of an input text of size at most $2^{31}-1$ over the standard byte alphabet. The main feature of the algorithm is that it is lighweight in the sense that it uses very little space in addition to space used by the input (the text) and the output (the suffix Array), see the above papers for further details. Although the algorithm was a standard reference for many years, it is no longer the state of the art for suffix array construction. For most practical uses we recommend [libdivsufsort](https://github.com/y-256/libdivsufsort) by Yuta Mori which is also lightweight and very fast practice. Other alternatives are the algorithms SAIS and SACA-K by Ge Nong et al. for example in the [implementation of Felipe Louza](https://github.com/felipelouza/gsa-is) that offers simple and powerful API. 


For an in depth evaluation of the availble suffix array constrcution algorithms see the paper  
[SACABench: Benchmarking Suffix Array Construction}(https://link.springer.com/chapter/10.1007/978-3-030-32686-9_29) and the [companion repository](https://github.com/sacabench/sacabench).



## Running the algorithm

As we stated above, the algorithm is no longer the state of the art, however the code should compile on any linux/unix system. To try it just clone/download and then `make`.


