using namespace std;

#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class FileManager {
public:
  static void read(string file_name, vector<vector<char>> &data) {
    string line {};
    ifstream infile(file_name);

    int64_t row_index = 0;
    while (getline (infile, line)) {
      stringstream ss {line};
      vector<char> row {};
      char charactor;

      while (ss >> charactor) {
        row.push_back(charactor);
      }

      data[row_index++] = row;
    }

    infile.close();
  }

  static void write(string file_name, vector<vector<char>> &data) {
    ofstream outfile(file_name);

    for (const auto& row : data) {
      for (const auto& elem : row) {
        if(elem == 0) return; // NULL

        outfile.write((char*) &elem, sizeof(elem));
      }
      outfile << endl;
    }

    outfile.close();
  }
};

#endif