using namespace std;

#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class FileManager {
public:
  static void read(string file_name, vector<vector<char>> &data) {
    string line {};
    ifstream infile(file_name);

    while (getline (infile, line)) {
      std::stringstream ss {line};
      std::vector<char> row {};
      char charactor;

      while (ss >> charactor)
        row.push_back(charactor);

      data.push_back(row);
    }
  }
};

#endif