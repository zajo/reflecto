#ifndef BOOST_REFLECTO_CONFIG_HPP_INCLUDED
#define BOOST_REFLECTO_CONFIG_HPP_INCLUDED

// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <cstdint>

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

////////////////////////////////////////

#ifndef BOOST_REFLECTO_DEFAULT_ENUM_MIN_VALUE
#   define BOOST_REFLECTO_DEFAULT_ENUM_MIN_VALUE -8
#endif

#ifndef BOOST_REFLECTO_DEFAULT_ENUM_MAX_VALUE
#   define BOOST_REFLECTO_DEFAULT_ENUM_MAX_VALUE 63
#endif

namespace boost::reflecto {

struct unspecialized { };

template <std::uint64_t>
struct enum_lookup_range: unspecialized
{
    static constexpr int min_value = BOOST_REFLECTO_DEFAULT_ENUM_MIN_VALUE;
    static constexpr int max_value = BOOST_REFLECTO_DEFAULT_ENUM_MAX_VALUE;
};

}

#endif // #ifndef BOOST_REFLECTO_CONFIG_HPP_INCLUDED
