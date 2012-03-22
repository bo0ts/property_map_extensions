//
//=======================================================================
// Author: Philipp Moeller
//
// Copyright 2012, Philipp Moeller
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

#ifndef CONSTANT_PROPERTY_MAP_H
#define CONSTANT_PROPERTY_MAP_H

#include <boost/property_map/property_map.hpp>

namespace util {

template<typename Key, typename Value>
struct constant_property_map {
  typedef Key                              key_type;
  typedef Value                            value_type;
  typedef const value_type&                reference;
  typedef boost::readable_property_map_tag category;

  constant_property_map(Value&& v) : v(v) {}
  
  reference
  operator[](const Key&) const { return v; }

  const value_type v;
};

template<typename Key, typename Value>
typename boost::property_traits< constant_property_map<Key, Value> >::reference
get(const constant_property_map<Key, Value>& m, const Key& k) { return m[k]; }

template<typename Key, typename Value>
typename boost::property_traits< constant_property_map<Key, Value> >::reference
get(constant_property_map<Key, Value>& m, const Key& k) { return m[k]; }

} // util

#endif /* CONSTANT_PROPERTY_MAP_H */
