#ifndef BOOST_REFLECTO_CONFIG_HPP_INCLUDED
#define BOOST_REFLECTO_CONFIG_HPP_INCLUDED

// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_REFLECTO_ASSERT
#   include <cassert>
#   define BOOST_REFLECTO_ASSERT assert
#endif

#ifndef BOOST_REFLECTO_PRETTY_FUNCTION
#   if defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUC__)
#       define BOOST_REFLECTO_PRETTY_FUNCTION __FUNCSIG__
#   else
#       define BOOST_REFLECTO_PRETTY_FUNCTION __PRETTY_FUNCTION__
#   endif
#endif

#ifdef _MSC_VER
#   define BOOST_REFLECTO_ALWAYS_INLINE __forceinline
#else
#   define BOOST_REFLECTO_ALWAYS_INLINE __attribute__((always_inline)) inline
#endif

////////////////////////////////////////

#ifndef BOOST_REFLECTO_ENUM_MIN
#   define BOOST_REFLECTO_ENUM_MIN -32
#endif

#ifndef BOOST_REFLECTO_ENUM_MAX
#   define BOOST_REFLECTO_ENUM_MAX 127
#endif

namespace boost::reflecto {

template <class Enum>
struct enum_lookup_range
{
    static constexpr int min_value = BOOST_REFLECTO_ENUM_MIN;
    static constexpr int max_value = BOOST_REFLECTO_ENUM_MAX;
};

}

#endif // #ifndef BOOST_REFLECTO_CONFIG_HPP_INCLUDED
