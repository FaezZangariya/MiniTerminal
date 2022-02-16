#ifndef Folder_h
#define Folder_h

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#include "Exception.h"
#include "File.h"

using namespace std;
using std::map;
using std::cout;
using std::endl;

class Folder{
public:
  Folder();
  void mkdir(string FolderName);
  void chdir(string workingFolder);
  void rmdir(string fileName);
  void ls(string FolderName);
  void lproot();
  void pwd();
  
  const char readCharFromFile(string fileName, int index); 
  void writeCharToFile(string fileName, char c, int index);
  void touch(string fileName);
  void copy(string source, string destination);
  void remove(string fileName);
  void move(string source, string destination);
  void cat(string fileName);
  void wc(string fileName);
  void doLn(string source, string destination );
  void addFileToFolder(string fileName); 
  ~Folder();
  
 
private:
  string currentFolder;    //save the current directory
  vector<string> myFolder;  //files and directories with the path
  map<string,vector<File> > MyFiles;   //files in each Folder
  map<string,vector<string> > MyDirectories;   //directories in each Folder
  
  std::vector<File>::iterator getFileIterator(string fileName);
  bool isFileExist(string fileName);
};


int findTheIndexOfTheSlashNumber(int slashNumber,const string& fileName);  //global function
int findNumOfSlash(const string& fileName);  //global function

#endif
