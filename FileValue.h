#ifndef FileValue_h
#define FileValue_h

#include "RCObject.h"

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class FileValue: public RCObject{
public:
  fstream* file;
  FileValue(const string& fileName):file(new fstream(fileName.c_str())){}
  ~FileValue(){delete file;}  
};

#endif
