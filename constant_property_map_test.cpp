#include "constant_property_map.hpp"

int main()
{
  util::constant_property_map<int, int> map{3};
  get(map, 5);
  return 0;
}
