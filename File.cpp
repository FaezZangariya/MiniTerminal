#include "File.h"



File::File(const string& fName)
{
  fileName = fName;
  value = new FileValue(fileName);
}


File& File::operator=(const File& rhs)
{
  if (this != &rhs) {
    value=rhs.value;
  }
  return *this;
}

char File::operator[](fstream::pos_type i) const
{
  (value->file)->seekg(i);
  return char((value->file)->peek());
}



File::CharControl File::operator[](fstream::pos_type i)
{
  return CharControl(*(value->file),i);
}


void File::copy(File& sourceFile){
  int length = sourceFile.Size();
  for(int i=0; i<length;i++)
  {
    value->file->seekp(i); 
    value->file->put(sourceFile[i]); 
  } 
}


void File::move(File& sourceFile)
{
 value=sourceFile.value;
}


void File::cat()
{
  char c;
  int length = Size();
  for(int i=0;i<length;i++)
  {
    (value->file)->seekg(i);
    c= char((value->file)->peek());
    cout << c;
  }
  cout<<endl;
}


void File::wc()
{
  int countWord = 0;
  int lineCount = 0;
  int characterCount = 0;
  
  char c,c1;
  int length =Size();
  for(int i=0;i<length;i++)
  {
    (value->file)->seekg(i);
    c= char((value->file)->peek());
    characterCount++;
    if(c=='\n') lineCount++;
    if(c!='\n' && c!=' '){
      if(i!=length-1){
       (value->file)->seekg(i+1);
       c1= char((value->file)->peek());
       if(c1==' ') countWord++;
      
      }
      else countWord++;
    }  
  }
  
  if(characterCount>0 && lineCount==0) lineCount++;
  cout<<endl;
    
  cout << "Characters' Number: " << characterCount << endl;
  cout << "Words' Number: " << countWord << endl;
  cout << "Lines' Number: " << lineCount << endl;   
}


void File::ln(const File& rhs)
{
 value = rhs.value; 
}


string File::getFileName() const
{
 return fileName; 
}

int File::getReferenceCounting() const
{
 return value->getRefCount(); 
}

int File::Size() const
{
  int end;
  value->file->seekg (0, ios::end);
  end = value->file->tellg();
  return end;
}


//globalFunction
void ftouch(string file){
  ofstream xfile;
  xfile.open(file.c_str());
  xfile.flush();
  xfile.close();
}
