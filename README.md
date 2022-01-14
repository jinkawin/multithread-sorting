# Prerequisite
- GCC Complier

# How to run


```sh
cd {FOLDER} && g++ -std=c++17 index.cpp -o index && ./index
```

# Configuration

Configuaration can be done in `config.hpp` file
|Varaiable       |Description                                         |
|----------------|----------------------------------------------------|
|START_INDEX     |The first index of CUID                             |
|ALLOC_ROW_SIZE  |Number of file's row. Used for vector's allocation  |
|ALLOC_COL_SIZE  |The lenght of each row. Used for vector's allocation|
|FILE_IN         |The name of an input file with extension            |
|FILE_OUT        |The name of an output file with extension           |

# How it works
This programme is divided into 4 parts: Read File, Swap Bucket, Local Sort, and Write File.

## Read File
File will be read from the given configuration. File will be converted into 2-dimensions array. The first dimension represents rows or line of file. The second dimension represents character in each line.

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
After file was read and converted into the 2-dimensions vector, each row of vector will be partitioned into buckets by considering iteration of each column. The first iteration, the last index of CUID will be considered for distributing into buckets. Also, for the second iteration, the second last index of CUID will be considered.

A number of buckets will be considered by a number of threads which will equal to the number of cores. The first bucket will contain only nunber 0-9, and the others will equally contain 26/(number_of_bucket - 1).

For example, if there are 4 cores, there will be 4 buckets:
1. The first bucket contains `0-9`
2. The second bucket contains `a-h`
3. The third bucket contains `i-p`
4. The last one contains `q-z`

To optimise a memory usage, a secondary index is introduced which name is `buckets_index`. `buckets_index` is an array that point to the last index of each bucket.

For example,
```cpp
vector<int> buckets_index { 2, 5, 7, 19 };
```
The last row's index of the first bucket is 2, and the last row's index of the second bucket is 5.

## Local Sort
## Write File