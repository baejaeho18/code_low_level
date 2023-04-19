#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <range/v3/view/transform.hpp>
#include <range/v3/range/conversion.hpp>

using namespace ranges::v3;
using namespace std;

auto open_file(string const& filename) -> ifstream 
{
  try { return ifstream{filename}; } catch(...) {}

  return ifstream{};
}

auto count_file_lines(ifstream in) -> int
{ 
  return count(istreambuf_iterator<char>(in), 
               istreambuf_iterator<char>(), '\n');
}

auto count_lines_in_files2(vector<string>& files) -> vector<int> 
{ 
  return files 
    | view::transform(open_file) 
    | view::transform(count_file_lines)
    | to<vector>();
}

int main(int argc, char* argv[])
{
  vector<string> files{
    "/Users/yielding/code/big.read.write.cpp",
    "/Users/yielding/code/big.read.write.cpp"
  };

  auto res = count_lines_in_files2(files);
  for (auto r : res)
    cout << r << " ";

  return 0;
}