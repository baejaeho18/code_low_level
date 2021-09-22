#include <iostream>
#include <vector>
#include <string>
#include <range/v3/view/enumerate.hpp>

namespace view = ranges::views;

int main(int argc, char *argv[])
{
  using namespace std;

  auto v = vector<string> {"apple", "banana", "kiwi" };
  for (auto&& [f, s] : v | view::enumerate) 
    cout << f + 1 << ", " << s << endl;
  
  return 0;
}
