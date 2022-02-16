#ifndef MiniTerminal_h
#define MiniTerminal_h

#include "Folder.h"
#include <map>
#include <string>
#include <sstream>
#include "Exception.h"
#include <iterator>
#include <iostream>
#include <vector>
#include <stdlib.h>


using namespace std;
using std::cout;
using std::cin;

class MiniTerminal{
public:
  MiniTerminal();
  void init();
  void start();
  
  
private:
  Folder FSystem;
  int currentCommandNum;
  map<string,int> argumentNum;
  map<string,int> commandNum;
  vector<string> isValidCommand(const string& command);
  
};

int getIntFromString(string myString);
#endif