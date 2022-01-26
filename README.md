# Overview
This programme is written for sorting a file by using a multithreading technique. This programme uses two sorting techniques: the Bucket sort and any stable sort that can sort in a specific column. This programme has four processes: file reading, buckets swapping, local sorting, and file writing.

## Read File
The first process is reading a file. Data will be read and buffered into a two-dimensional vector. The first dimension represents rows or lines of the file. The second dimension represents characters in each line. Vector is allocated in advance, and the allocation size roughly is the number of rows in the file.

For example, given file input.csv

```
USR:cxm,03d
USR:lsk,03d
```
will be converted to
```
{
   {'U'}, {'S'}, {'R'}, {':'}, {'c'}, {'x'}, {'m'}. {','}, {'0'}, {'3'}, {'d'},
   {'U'}, {'S'}, {'R'}, {':'}, {'l'}, {'s'}, {'k'}. {','}, {'0'}, {'3'}, {'d'}
}
```

## Swap Bucket
After the file was read and converted into the two-dimensional vector, each row of the vector will be partitioned into buckets by considering the iteration of each column. The first iteration, the last index of CUID, will be regarded for distributing into buckets. Also, the second last index of CUID will be considered for the second iteration.

The number of buckets will be considered by the number of threads equal to the cores. The first bucket will contain only numbers 0-9, and the others will equally have 26/(number_of_bucket - 1).

For example, if there are 4 cores, there will be 4 buckets:
1. The first bucket contains `0-9`
2. The second bucket contains `a-h`
3. The third bucket contains `i-p`
4. The last one contains `q-z`

A secondary index is introduced to optimise a memory usage, which is `buckets_index`. `buckets_index` is an array that points to the last index of each bucket.

For example,
```cpp
vector<int> buckets_index { 2, 5, 7, 19 };
```
The last row's index of the first bucket is 2, and the last row's index of the second bucket is 5.

## Local Sort
Local sort is an element sorting in the bucket by swapping rows in the bucket in ascending order. Each thread will process only one bucket. After characters are distributed into buckets, threads will be mapped to a bucket. Then, threads will start to sort concerning an iteration number. For example, the first iteration will sort the last position of CUID.

## Write File
The programme will convert a two-dimensional vector into a file. The first dimension of the vector will be the file's row, and the second dimension of the vector will be a column. The file will be written sequentially.

# Prerequisite
- C++ 17
- GCC Compiler
- 500MB of Memory (at least for 1m rows)

# How to run
1. Use terminal
```sh
g++ -std=c++17 ./src/index.cpp -pthread -o ./.src/index && ./.src/index
```
2. Use shell script

```sh
./run.sh
```
3. Use docker-compose

```sh
docker-compose up
```
# Configuration

Configuaration can be done in `config.hpp` file
|Varaiable       |Description                                           |
|----------------|------------------------------------------------------|
|START_INDEX     |The first index of CUID                               |
|ALLOC_ROW_SIZE  |A number of file's row. Used for vector's allocation  |
|ALLOC_COL_SIZE  |The length of each row. Used for vector's allocation  |
|FILE_IN         |The name of an input file with extension              |
|FILE_OUT        |The name of an output file with extension             |