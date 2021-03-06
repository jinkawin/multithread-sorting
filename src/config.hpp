#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <thread>
#include <string>

using namespace std;

class Config {
public:
  static const int START_INDEX = 4; // start after "USR:"
  static const int ALLOC_ROW_SIZE = 10; // Number of ALLOC_ROW_SIZE = number of rows
  static const int ALLOC_COL_SIZE = 10;
  static const inline string FILE_IN = "data/reversed_users_10.csv";
  static const inline string FILE_OUT = "./output/out.csv";
};

#endif