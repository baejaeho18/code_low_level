#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class user_info_fields {
  uiName, uiEmail, uiRepu
};

using user_info =
  tuple<string,  // name
        string,  // email
        size_t>; // reputation

template <typename E>
constexpr auto
toUType(E enumerator) noexcept
{
  return static_cast<underlying_type_t<E>>(enumerator);
}

int main(int argc, char *argv[])
{
  user_info i{"lee", "lee@gmail.com", 12};

  auto val = get<toUType(user_info_fields::uiEmail)>(i);
  cout << val;
  
  return 0;
}