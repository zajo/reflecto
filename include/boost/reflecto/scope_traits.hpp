#ifndef BOOST_REFLECTO_SCOPE_TRAITS_HPP_INCLUDED
#define BOOST_REFLECTO_SCOPE_TRAITS_HPP_INCLUDED

// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/reflecto/config.hpp>
#include <boost/reflecto/detail/pretty_function_traits.hpp>
#include <boost/reflecto/scope_name_of.hpp>
#include <type_traits>

namespace boost::reflecto {

namespace d
{
    template <class T>
    constexpr bool scope_chain_contains(std::uint64_t target) noexcept
    {
        auto const & sn = scope_name_of<T>();
        char const * begin = sn.data();
        int end = static_cast<int>(sn.size());
        while( end > 0 )
        {
            if( hash_sequence(begin, begin + end) == target )
                return true;
            end = find_parent_ns_end(begin, end);
        }
        return target == hash_start;
    }
} // namespace d

template <class T, class U>
struct same_scope:
    std::bool_constant<scope_name_of<T>() == scope_name_of<U>()>
{
};

template <class T, class U>
inline constexpr bool same_scope_v = same_scope<T, U>::value;

template <class T, class U>
struct in_scope_of:
    std::bool_constant<d::scope_chain_contains<T>(scope_name_of<U>().hash())>
{
};

template <class T, class U>
inline constexpr bool in_scope_of_v = in_scope_of<T, U>::value;

} // namespace boost::reflecto

#endif // #ifndef BOOST_REFLECTO_SCOPE_TRAITS_HPP_INCLUDED
