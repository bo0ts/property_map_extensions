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

#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/type_traits.hpp>


// This should also use !defined(BOOST_NO_0X_HDR_TYPE_TRAITS) but
// boost/config.hpp considers it unusable. We make the assumption that
// every compiler with decltype has type_traits, which is a little
// over-eager
#if !defined(BOOST_NO_DECLTYPE)
#include <type_traits>
#else
#include <boost/utility/result_of.hpp>
#endif

namespace util {

namespace detail {
struct deduce_tag {};
} // detail

template<typename Func
         , typename Key
#if defined(BOOST_NO_DECLTYPE)
         // Ret can still be provided for situations where neither
         // inference nor compliance with boost::result_of is possible
         , typename Ret = detail::deduce_tag
#endif
         >
struct function_property_map {
  typedef Key key_type;
#if !defined(BOOST_NO_DECLTYPE)
  typedef typename std::result_of<Func(key_type)>::type reference;
#else
  typedef typename boost::mpl::if_< 
    typename boost::is_same< Ret, detail::deduce_tag >::type
      , typename boost::result_of<Func(key_type)>::type
      , Ret 
    >::type reference;
#endif

  typedef 
    typename boost::remove_const<
      typename boost::remove_reference<reference>::type
    >::type 
  value_type;

  typedef boost::readable_property_map_tag              category;

  function_property_map(Func f = Func()) : f(f) {}

#if !defined(BOOST_NO_RVALUE_REFERENCES)
  reference operator[](Key&& k) const {
    return f(std::forward<Key>(k));
  }

  reference operator[](Key&& k) {
    return f(std::forward<Key>(k));
  }
#else
  reference operator[](const Key& k) const {
    return f(k);
  }

  reference operator[](const Key& k) {
    return f(k);
  }
#endif

  Func f;
};

template<typename Func, typename Key>
typename boost::property_traits< function_property_map<Func, Key> >::reference
#if !defined(BOOST_NO_RVALUE_REFERENCES)
get(function_property_map<Func, Key> const& m, Key&& k) 
{ return m[std::forward<Key>(k)]; }
#else
get(function_property_map<Func, Key> const& m, const Key& k) 
{ return m[k]; }
#endif


template<typename Func, typename Key>
typename boost::property_traits< function_property_map<Func, Key> >::reference
#if !defined(BOOST_NO_RVALUE_REFERENCES)
get(function_property_map<Func, Key>& m, Key&& k) 
{ return m[std::forward<Key>(k)]; }
#else
get(function_property_map<Func, Key>& m, const Key& k) 
{ return m[k]; }
#endif


template<typename Key, typename Func>
function_property_map<Func, Key>
make_function_property_map(Func f) { return function_property_map<Func, Key>(f); }

} // util

#endif /* FUNCTION_PROPERTY_MAP_H */
