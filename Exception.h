#ifndef Exception_h
#define Exception_h

#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;



class Exception {
  
public :
  Exception();
  ~Exception();
  
  class FolderNameInvalid{
public:
	FolderNameInvalid(string fileName){name=fileName;};
	virtual void PrintError() {
		cerr << "ERROR: cannot create directory \"" << name <<"\".";
	}
  	private:
	string name;
  }; 
  
  class DirectoryNonExistent{
  public:
	DirectoryNonExistent(string fileName){ name=fileName;}
    virtual void PrintError() {
      cerr << "ERROR: directory \""<< name <<"\" does not exist.\n";
    }
    private:
     string name;
  };
  
  
  class directoryNameFormatError{
  public:
	  directoryNameFormatError(string fileName){ name=fileName;}
    virtual void PrintError() {
      cerr << "ERROR: directory's name format error.\""
      << name <<"\" must end with /.\n";
    }
  private:
     string name;
  };
  
  class FileNameFormatError{
  public:
	  FileNameFormatError(string fileName){ name=fileName;}
    virtual void PrintError() {
      cerr << "ERROR: file's name format error.\""
      << name <<"\" must not end with /.\n";
    }
  private:
     string name;    
  };
  
  
  class IndexOutOfRange{
  public:
	  IndexOutOfRange(int n_index, int n_size){
      size=n_size;
      index=n_index;
    }
    virtual void PrintError() {
      cerr << "ERROR: The index \""
      << index <<"\" is out of range(0," << size  << ") .\n";
    }
    
  private:
     int size;
     int index;
  };
  
  class FileNonExistent{
  public:
	  FileNonExistent(string fileName){
      name=fileName;
    }
    virtual void PrintError() {
      cerr << "ERROR: no such file \""
      << name <<"\".\n";
    }
    
  private:
     string name;
  };
  
  
  class FolderNoneExistent{
  public:
	  FolderNoneExistent(string fileName){
      name=fileName;
    }
    virtual void PrintError() {
      cerr << "ERROR: no such directory \""<< name <<"\".\n";
    }
    
  private:
     string name;
  };
  
  
  class FormatIndexError{
    public:
	  FormatIndexError(string arg){
      argument=arg;
    }
    virtual void PrintError() {
      cerr << "ERROR: non digit argument passed as index : \""<< argument <<"\".\n";
    }
    
  private:
     string argument;
  };
  
  
  class Invalid_command_argumentsNum{
     public:
    Invalid_command_argumentsNum(string theCommand, int arguPass, int argNeed){ 
      command=theCommand;
      pass=arguPass;
      need=argNeed;
    }
    virtual void PrintError() {
      cerr << "ERROR: invalid arguments' number for command \""
      << command <<"\".\n";
      cerr << "Number of passed arguments= " << pass << endl;
      cerr << "Number of needed arguments= " << need<<endl;
    }
    
  private:
     string command;
     int need;
     int pass;
    
  };
  
  
  class Invalid_command{
  public:
    Invalid_command(){}
    virtual void PrintError(){
	cerr << "Error: invalid command"<< endl;
    }
  };
  
};

#endif
