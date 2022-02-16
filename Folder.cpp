#include "Folder.h"


Folder::Folder()
:currentFolder("V/")
{ 
  myFolder.push_back("V/");
}


void Folder::mkdir(string FolderName)
{
  //check Folder's name - it must end with '/'
  if(FolderName.at(FolderName.length()-1)!='/')
    throw Exception::directoryNameFormatError(FolderName);
  
  int slashNum = findNumOfSlash(FolderName);
  int index = findTheIndexOfTheSlashNumber(--slashNum,FolderName);

    //check if the pre Folder of the new Folder exists
  string findFolder=FolderName.substr(0,index+1);
  string newFolder=FolderName.substr(index+1,FolderName.length()-index-1);
  
  //check if the Folder already exists
  if(std::find(myFolder.begin(),myFolder.end(),findFolder)==myFolder.end())
    throw Exception::DirectoryNonExistent(findFolder);
    //the Folder doesn't exist
  if(std::find(myFolder.begin(),myFolder.end(),FolderName)==myFolder.end()){
      myFolder.push_back(FolderName);
      MyDirectories[findFolder].push_back(newFolder);
  }
  else throw Exception::FolderNameInvalid(FolderName);
}



void Folder::chdir(string workingFolder){
  //check if the wanted Directory exists
  if(std::find(myFolder.begin(),myFolder.end(),workingFolder)==myFolder.end())
      throw Exception::DirectoryNonExistent(workingFolder);
  else currentFolder=workingFolder;
}



void Folder::rmdir(string FolderName)
{
  std::vector<string>::iterator it;
  //check if the wanted directory exists
  if((it=std::find(myFolder.begin(),myFolder.end(),FolderName))==myFolder.end())
      throw Exception::DirectoryNonExistent(FolderName);
  else{
    //the wanted directory exists
    myFolder.erase(it);
    MyDirectories.erase(FolderName);
    MyFiles.erase(FolderName);
  }
  
}



void Folder::ls(string FolderName) 
{
 std::vector<string>::iterator it;
 if((std::find(myFolder.begin(),myFolder.end(),FolderName))==myFolder.end())
   throw Exception::DirectoryNonExistent(FolderName);
 cout << FolderName << ":" << endl;
 vector<File> filesInDir = MyFiles[FolderName];
 for(File &file : filesInDir)
 {
	 cout << file.getFileName() << endl;
 }
 vector<string> DirsInDir = MyDirectories[FolderName];
 
 for(string &dir : DirsInDir)
 {
	 cout << dir.substr(0,dir.length()-1) << endl;
 }
 
}



void Folder::lproot() 
{
  int length;
  sort(myFolder.begin(),myFolder.end());
  for(string &d : myFolder)
  {
    cout << d << ":" << endl;
    for(File &f : MyFiles[d]){
	cout << f.getFileName() << " " << f.getReferenceCounting()<< endl;
    }
   }
}



void Folder::pwd()
{
 cout << currentFolder << endl; 
}



const char Folder::readCharFromFile(string fileName, int index)
{
    try{ 
    std::vector<File>::iterator it;
    it=getFileIterator(fileName);
    File& f = *it;
  
    if(index<0 || index>f.Size()) 
      throw Exception::IndexOutOfRange(index,f.Size());
    return f[index];
   }
  catch (Exception &e) {
   throw e; 
  }
}



void Folder::writeCharToFile(string fileName, char c, int index)
{   
  try{ 
    std::vector<File>::iterator it;
    it=getFileIterator(fileName);
    File& f = *it;
  
    if(index<0 || index>f.Size()) 
      throw Exception::IndexOutOfRange(index,f.Size());
    f[index]=c;
   }
  catch (Exception::FileNonExistent &e) {
   throw e; 
  }
}


void Folder::touch(string fileName)
{
 try{
   addFileToFolder(fileName);
 }
 catch (Exception &e)
 {
   throw e;
 }
}



void Folder::copy(string source, string destination)
{
  try{
    int d_numSlash = findNumOfSlash(destination);
    if(d_numSlash==0) 
    {
      //the destination file's name doesn't contain directory's name
      if(isFileExist(currentFolder+destination)==false){
    	  //add the destination file to the current Directory
    	  addFileToFolder(currentFolder+destination);
    	  destination = currentFolder + destination;
      }
    }
    else if(isFileExist(destination)==false) 
      addFileToFolder(destination); 
    
    int s_numSlash = findNumOfSlash(source);
    if(s_numSlash==0) 
    {
      //the source file's name doesn't contain directory's name
      if(isFileExist(currentFolder+source)==false){
    	  //add the source file to the current Directory
    	  addFileToFolder(currentFolder+source);
    	  source= currentFolder + source;
      }
    }
    else if(isFileExist(source)==false) 
      addFileToFolder(source); 
    
    std::vector<File>::iterator s_it, d_it;
    s_it=getFileIterator(source);
    d_it=getFileIterator(destination);
    d_it->copy(*s_it);
    
  }
  catch (Exception::FileNonExistent &e) {
   throw e; 
  }
  
}



void Folder::remove(string fileName)
{
  try{
    int slashNum = findNumOfSlash(fileName);
    int index = findTheIndexOfTheSlashNumber(slashNum,fileName);
      //check if the pre Folder of the new Folder exists
    string findFolder=fileName.substr(0,index+1);
    string n_fileName=fileName.substr(index+1,fileName.length()-index-1);

    std::vector<File>::iterator it;
    it = getFileIterator(fileName);
    MyFiles[findFolder].erase(it);
  }
  catch (Exception::FileNonExistent &e) {
   throw e; 
  }
}


void Folder::move(string destination, string source)
{
  try{
    if(isFileExist(destination)==false) addFileToFolder(destination); 
    std::vector<File>::iterator s_it,d_it;
    s_it = getFileIterator(destination);
    d_it = getFileIterator(source); 
    d_it->move(*s_it);
    remove(source);
  }
  catch (Exception &e) {
   throw e; 
  }
}


void Folder::cat(string fileName)
{
  try{
    std::vector<File>::iterator it;
    it = getFileIterator(fileName);
    it->cat();
  }
  catch (Exception &e) {
    throw e;   
  }
}

void Folder::wc(string fileName)
{
  try{
    std::vector<File>::iterator it;
    it = getFileIterator(fileName);
    it->wc();
  }
  catch (Exception &e) {
    throw e;   
  }
  
}


void Folder::doLn(string destination, string source)
{
  try{
    std::vector<File>::iterator s_it,d_it;
    s_it = getFileIterator(source);
    d_it = getFileIterator(destination);    
    d_it->ln(*s_it);
  }
  catch (Exception::FileNonExistent &e) {
   throw e; 
  }
}



void Folder::addFileToFolder(string fileName)
{
  int slashNum = findNumOfSlash(fileName);
  int index = findTheIndexOfTheSlashNumber(slashNum,fileName);
   
  string FolderName=fileName.substr(0,index+1);
  string n_fileName=fileName.substr(index+1,fileName.length()-index-1);
  
  //check if the file name is in the correct directory
   if(fileName.at(fileName.length()-1)=='/')
     throw Exception::FileNameFormatError(fileName);
  //check if the pre Folder(directory) of the new file exists
   if(std::find(myFolder.begin(),myFolder.end(),FolderName)==myFolder.end())
	throw Exception::FolderNoneExistent(FolderName);
   else {
     ftouch(n_fileName);
     MyFiles[FolderName].push_back(File(n_fileName));
      }
}



std::vector<File>::iterator Folder::getFileIterator(string fileName)
{
  int slashNum = findNumOfSlash(fileName);
  int index = findTheIndexOfTheSlashNumber(slashNum,fileName);
    //check if the pre Folder of the new Folder exit
  string findFolder=fileName.substr(0,index+1);
  string n_fileName=fileName.substr(index+1,fileName.length()-index-1);
  std::vector<File>::iterator it;
  for(it=MyFiles[findFolder].begin() ; it!=MyFiles[findFolder].end();)
  {
    if(it->getFileName()==n_fileName) 
      return it;
    it++;
  }
  throw Exception::FileNonExistent(fileName);
}


bool Folder::isFileExist(string fileName)
{
  try{
    std::vector<File>::iterator it;
    it=getFileIterator(fileName);
    return true;
  }
  catch(Exception::FileNonExistent& e)
  {
    return false;
  }
}


Folder::~Folder(){}




int findNumOfSlash(const string& fileName){     //global function
  int SlashCnt=0;
  for(int i=0; i<fileName.length();i++)
    if(fileName.at(i)=='/') SlashCnt++;
    return SlashCnt;
}



int findTheIndexOfTheSlashNumber(int slashNum,const string& fileName){      //global function
  int temp=0,index,j=0;   
    for(j=0;j<fileName.length();j++){
      if(fileName.at(j)=='/'){
	  temp++;
	  if(temp==slashNum) {index=j;}
      }
    }   
    return index; 
}
