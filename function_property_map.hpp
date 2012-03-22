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

#ifndef FUNCTION_PROPERTY_MAP_H
#define FUNCTION_PROPERTY_MAP_H

#include <boost/property_map/property_map.hpp>
#include <type_traits>

namespace util {

template<typename Func, typename Key>
struct function_property_map {
  typedef Key                                           key_type;
  typedef typename std::result_of<Func(key_type)>::type reference;
  typedef 
    typename std::remove_const<typename std::remove_reference<reference>::type>::type 
  value_type;
  typedef boost::readable_property_map_tag              category;

  function_property_map(Func f = Func()) : f(f) {}

  reference operator[](Key&& k) const {
    return f(std::forward<Key>(k));
  }

  reference operator[](Key&& k) {
    return f(std::forward<Key>(k));
  }

  Func f;
};

template<typename Func, typename Key>
typename boost::property_traits< function_property_map<Func, Key> >::reference
get(function_property_map<Func, Key> const& m, Key&& k) 
{ return m[std::forward<Key>(k)]; }

template<typename Func, typename Key>
typename boost::property_traits< function_property_map<Func, Key> >::reference
get(function_property_map<Func, Key>& m, Key&& k) 
{ return m[std::forward<Key>(k)]; }


template<typename Key, typename Func>
function_property_map<Func, Key>
make_function_property_map(Func f) { return function_property_map<Func, Key>(f); }

} // util

#endif /* FUNCTION_PROPERTY_MAP_H */
