// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_REFLECTO_TEST_HELPERS_HPP_INCLUDED
#define BOOST_REFLECTO_TEST_HELPERS_HPP_INCLUDED

#ifndef BOOST_REFLECTO_TEST_SINGLE_HEADER
#   include <boost/reflecto/name.hpp>
#   include <boost/reflecto/detail/pretty_function_traits.hpp>
#endif
#include <iostream>
#include <cstdint>
#include <string_view>

int errcount;

constexpr bool check_name(boost::reflecto::name const & n, char const * expected)
{
    char const * p = n.data();
    char const * e = n.data() + n.size();
    std::uint64_t h = 14695981039346656037ull;
    while( p != e )
    {
        if( !*expected || *p != *expected )
            return false;
        h = (h ^ static_cast<std::uint64_t>(*p)) * 1099511628211;
        ++p;
        ++expected;
    }
    return !*expected && n.hash() == h;
}

bool check_name_rt(boost::reflecto::name const & n, char const * expected, char const * file, int line)
{
    if( check_name(n, expected) )
        return true;
    std::cerr << file << "(" << line << "): FAIL: got \"" << n << "\", expected \"" << expected << "\"\n";
    ++errcount;
    return false;
}

bool check_rt(bool cond, char const * expr, char const * file, int line)
{
    if( cond )
        return true;
    std::cerr << file << "(" << line << "): FAIL: " << expr << "\n";
    ++errcount;
    return false;
}

constexpr bool check_str(char const * a, char const * b)
{
    while( *a && *a == *b )
        ++a, ++b;
    return *a == *b;
}

bool check_str_rt(char const * a, char const * b, char const * file, int line)
{
    if( check_str(a, b) )
        return true;
    std::cerr << file << "(" << line << "): FAIL: got \"" << (a ? a : "(null)") << "\", expected \"" << (b ? b : "(null)") << "\"\n";
    ++errcount;
    return false;
}

#define CHECK_NAME_CONSTEXPR(n, expected) static_assert(check_name(n, expected))
#define CHECK_NAME_RT(n, expected) check_name_rt((n), (expected), __FILE__, __LINE__)

#define CHECK_STR_CONSTEXPR(a, b) static_assert(check_str(a, b))
#define CHECK_STR_RT(a, b) check_str_rt((a), (b), __FILE__, __LINE__)

#define CHECK_CONSTEXPR(expr) static_assert(expr)
#define CHECK_RT(expr) check_rt((expr), #expr, __FILE__, __LINE__)

#define CHECK_TYPE_NAME_CONSTEXPR(entity, expected) static_assert(check_name(boost::reflecto::type_name<entity>(), expected))
#define CHECK_VALUE_NAME_CONSTEXPR(entity, expected) static_assert(check_name(boost::reflecto::value_name<entity>(), expected))
#define CHECK_SHORT_VALUE_NAME_CONSTEXPR(entity, expected) static_assert(check_name(boost::reflecto::short_value_name<entity>(), expected))

#ifdef RUNTIME_TEST

namespace boost::reflecto::d
{
    template <class T>
    constexpr t BOOST_REFLECTO_CDECL a()
    {
        std::cerr << "  a: " << BOOST_REFLECTO_PRETTY_FUNCTION << '\n';
        return {};
    }

    template <class Enum, Enum Value>
    constexpr t BOOST_REFLECTO_CDECL b()
    {
        std::cerr << "  b: " << BOOST_REFLECTO_PRETTY_FUNCTION << '\n';
        return {};
    }
}

#define CHECK_TYPE_NAME_RT(entity, expected) \
    do { \
        if( !check_name_rt(boost::reflecto::type_name<entity>(), expected, __FILE__, __LINE__) ) \
            (void) boost::reflecto::d::a<entity>(); \
    } while(0)

#define CHECK_VALUE_NAME_RT(entity, expected) \
    do { \
        if( !check_name_rt(boost::reflecto::value_name<entity>(), expected, __FILE__, __LINE__) ) \
            (void) boost::reflecto::d::b<decltype(entity), entity>(); \
    } while(0)

#define CHECK_SHORT_VALUE_NAME_RT(entity, expected) \
    do { \
        if( !check_name_rt(boost::reflecto::short_value_name<entity>(), expected, __FILE__, __LINE__) ) \
            (void) boost::reflecto::d::b<decltype(entity), entity>(); \
    } while(0)

#   define TEST_CONSTEXPR
#   define CHECK_NAME CHECK_NAME_RT
#   define CHECK_STR CHECK_STR_RT
#   define CHECK CHECK_RT
#   define CHECK_TYPE_NAME CHECK_TYPE_NAME_RT
#   define CHECK_VALUE_NAME CHECK_VALUE_NAME_RT
#   define CHECK_SHORT_VALUE_NAME CHECK_SHORT_VALUE_NAME_RT

#else

#   define TEST_CONSTEXPR constexpr
#   define CHECK_NAME CHECK_NAME_CONSTEXPR
#   define CHECK_STR CHECK_STR_CONSTEXPR
#   define CHECK CHECK_CONSTEXPR
#   define CHECK_TYPE_NAME CHECK_TYPE_NAME_CONSTEXPR
#   define CHECK_VALUE_NAME CHECK_VALUE_NAME_CONSTEXPR
#   define CHECK_SHORT_VALUE_NAME CHECK_SHORT_VALUE_NAME_CONSTEXPR

#endif

#endif
