#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

class Dat
{
  public:
    Dat() = default;
    Dat(const std::string &filename);
    ~Dat();
    void read_data();
    void print_data();
  private:
    std::string m_filename;
    std::ifstream file;
    std::vector<unsigned short> data;
};

Dat::Dat(const std::string &filename):m_filename(filename)
{
  file.open(filename, std::ios::binary);
  if (!file.is_open()) 
  {
    std::cerr << "Error: Could not open file: " << filename << std::endl;
    return;
  }
  std::cout<<" Success open file"<<std::endl;
}
Dat::~Dat()
{
  if(file.is_open())
  {
    file.close();
  }
  std::cout<<"File has closed."<<std::endl;
}
void Dat::read_data() 
{
  std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
  std::size_t bytes_read = buffer.size();
  for (std::size_t i = 0; i < bytes_read; i += 2) 
  {
    unsigned short pair = (buffer[i] << 8) | buffer[i + 1];
    data.push_back(pair);
  }
}
void Dat::print_data()
{
  for(int i = 0;i<data.size();i++)
  {
    std::cout << std::hex << std::setw(4) << std::setfill('0') << data[i] << " ";
    if((i+1)%8==0)
    {
      std::cout<<std::endl;
    }
  }
}

int main()
{
  std::string filename = "2024-10-16-14-57-42.dat";
  Dat dat(filename);
  std::vector<unsigned short> data;
  dat.read_data();
  dat.print_data();
  return 0;
}
