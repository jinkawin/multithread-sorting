#include <iostream>
#include <vector>

#include "context.hpp"
#include "filemanager.hpp"
#include "util.hpp"

using namespace std;

int main(){
  vector<vector<char>> data;

  FileManager::read("test.txt", data);

  Util::printVector2d(data);
}
