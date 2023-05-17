#include <iostream>
#include <algorithm>
#include <cmath>
#include <format>
#include <range/v3/all.hpp>

namespace g = ranges;
namespace v = ranges::views;

using namespace std;

auto is_sqrt_int(int i) 
{
  auto s = (int)sqrt(i);

  return s*s == i;
}

int main(int argc, char* argv[])
{
  auto rng = v::for_each(v::iota(1), [](int i) {
      return v::for_each(v::iota(1, i), [i](int j) {
          return g::yield_if(is_sqrt_int(i+j) && is_sqrt_int(i-j),
              make_pair(i, j));
          });
      });

  for (auto const& [e1, e2] : rng | v::take(5))
    cout << format("({}:{})", e1, e2) << " ";

  return 0;
}