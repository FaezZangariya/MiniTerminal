#include "MiniTerminal.h"

MiniTerminal::MiniTerminal(): currentCommandNum(0){}

void MiniTerminal::init()
{
    argumentNum["read"]=2;
    argumentNum["write"]=3;
    argumentNum["touch"]=1;
    argumentNum["copy"]=2;
    argumentNum["remove"]=1;
    argumentNum["move"]=2;
    argumentNum["cat"]=1;
    argumentNum["wc"]=1;
    argumentNum["ln"]=2;
    argumentNum["mkdir"]=1;
    argumentNum["chdir"]=1;
    argumentNum["rmdir"]=1;
    argumentNum["ls"]=1;
    argumentNum["lproot"]=0;
    argumentNum["pwd"]=0;
    argumentNum["exit"]=0;
    
    commandNum["read"]=1;
    commandNum["write"]=2;
    commandNum["touch"]=3;
    commandNum["copy"]=4;
    commandNum["remove"]=5;
    commandNum["move"]=6;
    commandNum["cat"]=7;
    commandNum["wc"]=8;
    commandNum["ln"]=9;
    commandNum["mkdir"]=10;
    commandNum["chdir"]=11;
    commandNum["rmdir"]=12;
    commandNum["ls"]=13;
    commandNum["lproot"]=14;
    commandNum["pwd"]=15;
    commandNum["exit"]=16;
    
}

vector<string> MiniTerminal::isValidCommand(const string& command){
    stringstream ss(command);
    std::istream_iterator<string> begin(ss);
    std::istream_iterator<string> end;
    std::vector<string> vstrings(begin, end);
    std::map<string,int>::iterator it;
    string Mycommand = vstrings[0];
    int passArgNum = vstrings.size()-1;
    it = argumentNum.find(Mycommand);
    if(it!=argumentNum.end()){
      if(passArgNum!=argumentNum[Mycommand])
	 throw Exception::Invalid_command_argumentsNum(Mycommand,passArgNum,argumentNum[Mycommand]);
      currentCommandNum=commandNum[Mycommand];
      return vstrings;
    }
    throw Exception::Invalid_command();    
}

//global
int getIntFromString(string myString)
{
  for(int i=0; i<myString.length(); i++)
    if(!isdigit(myString[i]))
    	throw Exception::FormatIndexError(myString);
  istringstream buffer(myString);
  int myint;
  buffer >> myint;
  return myint;
}

void MiniTerminal::start()
{
  init();
  string line;
  string command;
  int value;
  bool on=true;
  while(on){
    try{
      std::getline(cin,line);
      if(line!=""){
      vector<string> words = isValidCommand(line);
      switch(currentCommandNum){
      case 1 :
    	  value = getIntFromString(words[2]);
    	  cout << FSystem.readCharFromFile(words[1],value)<<endl;
    	  break;
	  
      case 2:
    	  value = getIntFromString(words[2]);
    	  FSystem.writeCharToFile(words[1], words[3].at(0), value);
    	  break;
	  
      case 3:
    	  FSystem.touch(words[1]);
    	  break;
	  
      case 4:
    	  FSystem.copy(words[1],words[2]);
    	  break;
	  
      case 5:
    	  FSystem.remove(words[1]);
    	  break;
	
      case 6:
    	  FSystem.move(words[1],words[2]);
    	  break;
	  
      case 7:
    	  FSystem.cat(words[1]);
    	  break;
	  
      case 8:
    	  FSystem.wc(words[1]);
	  	  break;
	  
      case 9:
    	  FSystem.doLn(words[1],words[2]);
    	  break;
	  
      case 10:
    	  FSystem.mkdir(words[1]);
    	  break;
	  
      case 11:
    	  FSystem.chdir(words[1]);
    	  break;
	  
      case 12:
    	  FSystem.rmdir(words[1]);
    	  break;
	  
      case 13:
    	  FSystem.ls(words[1]);
    	  break;
	  
      case 14:
    	  FSystem.lproot();
    	  break;
	  
      case 15:
    	  FSystem.pwd();
    	  break;
      case 16:
    	  on=false;
    	  break;
	  	  
      default:
    	  break;
	
      }
    }
	
      
      
      
    }
    catch(Exception::FolderNameInvalid& e){
      e.PrintError();
    }
    catch(Exception::DirectoryNonExistent& e){
      e.PrintError(); 
    }
    catch(Exception::FileNameFormatError& e){
      e.PrintError(); 
    }
    catch(Exception::directoryNameFormatError& e){
      e.PrintError();
    }
    catch(Exception::IndexOutOfRange& e){
      e.PrintError(); 
    }
    catch(Exception::FileNonExistent& e){
      e.PrintError();
    }
    catch(Exception::FormatIndexError& e){
      e.PrintError(); 
    }
    catch(Exception::FolderNoneExistent& e){
      e.PrintError(); 
    }
    catch(Exception::Invalid_command_argumentsNum& e){
      e.PrintError();
    }
    catch(Exception::Invalid_command& e){
      e.PrintError(); 
    }
    
    
  }
  
  
}
