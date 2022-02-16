#ifndef File_h
#define File_h

#include "RCPtr.h"
#include "FileValue.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;
using std::cout;

class File
{
public:
   class CharControl {
    public: 
	   CharControl(fstream &file, fstream::pos_type pos) : file_(file), pos_(pos) {}
	   CharControl& operator=(char c)
      { 
	file_.seekp(pos_); 
	file_.put(c); 
	return *this; 
	
      } 
      
      operator char() 
      { 
	file_.seekg(pos_); 
	return char(file_.get()); 	
      } 
      
    private: 
      fstream& file_; 
      fstream::pos_type pos_; 
    
  };  
  
  File(const string& fileName);
  File& operator=(const File& rhs);
  char operator[](fstream::pos_type i) const;
  CharControl operator[](fstream::pos_type i);
  void copy(File& sourceFile);
  void move(File& sourceFile);
  void cat();
  void wc();
  void ln(const File& rhs);
  string getFileName() const;
  int getReferenceCounting() const;
  int Size() const;
   
private:
  RCPtr<FileValue> value;
  string fileName;
};


void ftouch(string file); //global function

#endif
