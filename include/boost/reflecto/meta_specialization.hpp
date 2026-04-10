#ifndef BOOST_REFLECTO_META_SPECIALIZATION_HPP_INCLUDED
#define BOOST_REFLECTO_META_SPECIALIZATION_HPP_INCLUDED

// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/reflecto/config.hpp>
#include <boost/reflecto/detail/pretty_function_traits.hpp>
#include <type_traits>

namespace boost::reflecto {

namespace d
{
    constexpr int find_parent_ns_end(char const * s, int end) noexcept
    {
        for( int i = end; i != 1; --i )
            if( s[i - 1] == ':' && s[i - 2] == ':' )
                return i - 2;
        return 0;
    }

    template <class T>
    constexpr t BOOST_REFLECTO_CDECL n()
    {
        constexpr char const * pf = BOOST_REFLECTO_PRETTY_FUNCTION;
        constexpr int b = pf_traits::type_prefix_size_constexpr;
        constexpr int total = sizeof(BOOST_REFLECTO_PRETTY_FUNCTION) - 1 - pf_traits::suffix_size - b;
        static_assert(total >= 1);
        return { pf + b, find_parent_ns_end(pf + b, total) };
    }

    template <class T>
    constexpr t BOOST_REFLECTO_CDECL m()
    {
        constexpr char const * pf = BOOST_REFLECTO_PRETTY_FUNCTION;
        constexpr int b = pf_traits::type_prefix_size_constexpr;
        constexpr int total = sizeof(BOOST_REFLECTO_PRETTY_FUNCTION) - 1 - pf_traits::suffix_size - b;
        static_assert(total >= 1);
        return { pf + b, total };
    }

    template <template <std::uint64_t, class...> class Setting, class T, int End, bool Found, class... Args>
    struct ns_walk;

    template <template <std::uint64_t, class...> class Setting, class T, int End, class... Args>
    struct ns_walk<Setting, T, End, true, Args...>
    {
        using type = Setting<hash_sequence(n<T>().begin, n<T>().begin + End), Args...>;
    };

    template <template <std::uint64_t, class...> class Setting, class T, class... Args>
    struct ns_walk<Setting, T, 0, false, Args...>
    {
        using type = Setting<0, Args...>;
    };

    template <template <std::uint64_t, class...> class Setting, class T, int End, class... Args>
    struct ns_walk<Setting, T, End, false, Args...>
    {
        static constexpr char const * s = n<T>().begin;
        static constexpr int pe = find_parent_ns_end(s, End);
        static constexpr std::uint64_t ph = hash_sequence(s, s + pe);
        static constexpr bool pf = !std::is_base_of_v<unspecialized, Setting<ph, Args...>>;
        using type = typename ns_walk<Setting, T, pe, pf, Args...>::type;
    };

    template <template <std::uint64_t, class...> class Setting, class T, bool TypeFound, class... Args>
    struct meta_select_impl;

    template <template <std::uint64_t, class...> class Setting, class T, class... Args>
    struct meta_select_impl<Setting, T, true, Args...>
    {
        static constexpr auto info = m<T>();
        using type = Setting<hash_sequence(info.begin, info.begin + info.size), Args...>;
    };

    template <template <std::uint64_t, class...> class Setting, class T, class... Args>
    struct meta_select_impl<Setting, T, false, Args...>
    {
        static constexpr auto info = n<T>();
        static constexpr std::uint64_t h = hash_sequence(info.begin, info.begin + info.size);
        static constexpr bool f = !std::is_base_of_v<unspecialized, Setting<h, Args...>>;
        using type = typename ns_walk<Setting, T, info.size, f, Args...>::type;
    };
}

using meta_key = std::uint64_t;

template <class T>
inline constexpr meta_key specialize_for_namespace = []() constexpr {
    constexpr auto info = d::n<T>();
    static_assert(info.size != 0, "specialize_for_namespace can not be used with the global namespace");
    return d::hash_sequence(info.begin, info.begin + info.size);
}();

template <class T>
inline constexpr meta_key specialize_for_type = []() constexpr {
    constexpr auto info = d::m<T>();
    return d::hash_sequence(info.begin, info.begin + info.size);
}();

template <template <std::uint64_t, class...> class Setting, class T, class... Args>
struct meta_select
{
    static constexpr auto info = d::m<T>();
    static constexpr std::uint64_t th = d::hash_sequence(info.begin, info.begin + info.size);
    static constexpr bool type_found = !std::is_base_of_v<unspecialized, Setting<th, Args...>>;
    using type = typename d::meta_select_impl<Setting, T, type_found, Args...>::type;
};

template <template <std::uint64_t, class...> class Setting, class T, class... Args>
using meta_select_t = typename meta_select<Setting, T, Args...>::type;

}

#endif // #ifndef BOOST_REFLECTO_META_SPECIALIZATION_HPP_INCLUDED
