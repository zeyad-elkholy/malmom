#include <ios>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
unsigned char freq[256]={0};
using std::ifstream;
int main (int argc, char *argv[]) {
  ifstream file;
  file.open("txt",std::ios::binary);
  char buffer[4096];
  if (!file) {
      std::cerr << "Error: File could not be opened." << std::endl;
      return 1;
  }
  while (file.read(buffer, 4096) || file.gcount() >0) {
    std::streamsize count = file.gcount();
    for (int i = 0 ; i < count ; i++) {
      unsigned char byte = reinterpret_cast<unsigned char&>(buffer[i]);
      freq[byte]++;
    }
    if(file.eof())break;
  }
  file.close();
  for (int i = 0 ; i < 256 ; i++) {
    if(!freq[i])continue;
    std::cout << i << " " << static_cast<char>(i)<< ":" <<static_cast<int>(freq[i])<< std::endl; 
  }
  return 0;
}
