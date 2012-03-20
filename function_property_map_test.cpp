#include "function_property_map.hpp"

struct foo {
  int operator()(int i) const { return i + 23; }
};

int main()
{
  util::function_property_map<foo, int> functor_map{foo()};
  get(functor_map, 4);
  return 0;
}

