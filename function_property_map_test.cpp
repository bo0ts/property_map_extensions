#include "function_property_map.hpp"

struct functor_const {
  int operator()(int i) const { return i + 23; }
};

struct functor_mutable {
  functor_mutable() : i(0) {}
  int operator()(int x) { return ++i + x; }
  int i;
};

int main()
{
  {
    util::function_property_map<functor_const, int> functor_map{functor_const()};
    get(functor_map, 4);
  }

  {
    util::function_property_map<functor_mutable, int> functor_map{functor_mutable()};
    get(functor_map, 4);
  }
  return 0;
}

