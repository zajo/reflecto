#ifndef BOOST_REFLECTO_HPP_INCLUDED
#define BOOST_REFLECTO_HPP_INCLUDED

// Boost Reflecto single header distribution. Do not edit.
// Generated on Apr 26, 2026 from https://github.com/zajo/reflecto/tree/c156352.

// Copyright 2026 Emil Dotchevski
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// >>> #include <boost/reflecto/config.hpp>
#ifndef BOOST_REFLECTO_CONFIG_HPP_INCLUDED
#define BOOST_REFLECTO_CONFIG_HPP_INCLUDED

// #line 6 "boost/reflecto/config.hpp"
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

template <class>
struct enum_lookup_range: unspecialized
{
    static constexpr int min_value = BOOST_REFLECTO_DEFAULT_ENUM_MIN_VALUE;
    static constexpr int max_value = BOOST_REFLECTO_DEFAULT_ENUM_MAX_VALUE;
};

}

#endif // #ifndef BOOST_REFLECTO_CONFIG_HPP_INCLUDED
// >>> #include <boost/reflecto/bind_instance.hpp>
#ifndef BOOST_REFLECTO_BIND_INSTANCE_HPP_INCLUDED
#define BOOST_REFLECTO_BIND_INSTANCE_HPP_INCLUDED

// #line 6 "boost/reflecto/bind_instance.hpp"
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// #include <boost/reflecto/config.hpp> // Expanded at line 17
// >>> #include <boost/reflecto/detail/pretty_function_traits.hpp>
#ifndef BOOST_REFLECTO_DETAIL_PRETTY_FUNCTION_TRAITS_HPP_INCLUDED
#define BOOST_REFLECTO_DETAIL_PRETTY_FUNCTION_TRAITS_HPP_INCLUDED

// #line 6 "boost/reflecto/detail/pretty_function_traits.hpp"
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// #include <boost/reflecto/config.hpp> // Expanded at line 17
#include <cstdint>
#include <type_traits>

#ifdef _MSC_VER
#   define BOOST_REFLECTO_CDECL __cdecl
#else
#   define BOOST_REFLECTO_CDECL
#endif

namespace boost::reflecto {

// Single letter identifiers are used to minimize bloat.
namespace d
{
    enum class type_processing_requirements
    {
        none,
        strip_space_before_template_closing_bracket,
        strip_keywords_and_space_before_template_closing_bracket
    };

    enum class enum_value_processing_requirements
    {
        none,
        copy_pretty_function_string,
        strip_space_before_template_closing_bracket,
        strip_type_prefix_and_space_before_template_closing_bracket
    };

    enum class c
    {
        unknown,
        clang,
        clang_cdecl,
        gcc,
        gcc_cdecl,
        legacy_clang1,
        legacy_clang1_cdecl,
        legacy_clang2,
        legacy_clang2_cdecl,
        msvc_cdecl
    };

    template <c C>
    struct pretty_function_traits;

    template <>
    struct pretty_function_traits<c::clang>
    {
        static constexpr int type_prefix_size = sizeof("t boost::reflecto::d::q() [T = ") - 1;
        static constexpr int type_prefix_size_constexpr = type_prefix_size;
        static constexpr int enum_prefix_size = sizeof("t boost::reflecto::d::g() [Enum = ") - 1;
        static constexpr int enum_prefix_size_constexpr = enum_prefix_size;
        static constexpr int enum_separator_size = sizeof("; Value = ") - 1;
        static constexpr int suffix_size = sizeof("]") - 1;
        static constexpr auto type_processing = type_processing_requirements::none;
        static constexpr auto scoped_enum_value_processing = enum_value_processing_requirements::none;
        static constexpr auto unscoped_enum_value_processing = enum_value_processing_requirements::none;
        static constexpr auto unqualified_enum_value_processing = enum_value_processing_requirements::none;
    };

    template <>
    struct pretty_function_traits<c::clang_cdecl>
    {
        static constexpr int type_prefix_size = sizeof("t __cdecl boost::reflecto::d::q(void) [T = ") - 1;
        static constexpr int type_prefix_size_constexpr = type_prefix_size;
        static constexpr int enum_prefix_size = sizeof("t __cdecl boost::reflecto::d::g(void) [Enum = ") - 1;
        static constexpr int enum_prefix_size_constexpr = enum_prefix_size;
        static constexpr int enum_separator_size = sizeof("; Value = ") - 1;
        static constexpr int suffix_size = sizeof("]") - 1;
        static constexpr auto type_processing = type_processing_requirements::none;
        static constexpr auto scoped_enum_value_processing = enum_value_processing_requirements::none;
        static constexpr auto unscoped_enum_value_processing = enum_value_processing_requirements::none;
        static constexpr auto unqualified_enum_value_processing = enum_value_processing_requirements::none;
    };

    template <>
    struct pretty_function_traits<c::gcc>
    {
        static constexpr int type_prefix_size = sizeof("boost::reflecto::d::t boost::reflecto::d::q() [with T = ") - 1;
        static constexpr int type_prefix_size_constexpr = type_prefix_size + sizeof("constexpr ") - 1;
        static constexpr int enum_prefix_size = sizeof("boost::reflecto::d::t boost::reflecto::d::g() [with Enum = ") - 1;
        static constexpr int enum_prefix_size_constexpr = enum_prefix_size + sizeof("constexpr ") - 1;
        static constexpr int enum_separator_size = sizeof("; Enum Value = ") - 1;
        static constexpr int suffix_size = sizeof("]") - 1;
        static constexpr auto type_processing = type_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto scoped_enum_value_processing = enum_value_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto unscoped_enum_value_processing = enum_value_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto unqualified_enum_value_processing = enum_value_processing_requirements::none;
    };

    template <>
    struct pretty_function_traits<c::gcc_cdecl>
    {
        static constexpr int type_prefix_size = sizeof("boost::reflecto::d::t __cdecl boost::reflecto::d::q() [with T = ") - 1;
        static constexpr int type_prefix_size_constexpr = type_prefix_size + sizeof("constexpr ") - 1;
        static constexpr int enum_prefix_size = sizeof("boost::reflecto::d::t __cdecl boost::reflecto::d::g() [with Enum = ") - 1;
        static constexpr int enum_prefix_size_constexpr = enum_prefix_size + sizeof("constexpr ") - 1;
        static constexpr int enum_separator_size = sizeof("; Enum Value = ") - 1;
        static constexpr int suffix_size = sizeof("]") - 1;
        static constexpr auto type_processing = type_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto scoped_enum_value_processing = enum_value_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto unscoped_enum_value_processing = enum_value_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto unqualified_enum_value_processing = enum_value_processing_requirements::none;
    };

    template <>
    struct pretty_function_traits<c::legacy_clang1>
    {
        static constexpr int type_prefix_size = sizeof("boost::reflecto::d::t boost::reflecto::d::q() [T = ") - 1;
        static constexpr int type_prefix_size_constexpr = type_prefix_size;
        static constexpr int enum_prefix_size = sizeof("boost::reflecto::d::t boost::reflecto::d::g() [Enum = ") - 1;
        static constexpr int enum_prefix_size_constexpr = enum_prefix_size;
        static constexpr int enum_separator_size = sizeof("; Value = ") - 1;
        static constexpr int suffix_size = sizeof("]") - 1;
        static constexpr auto type_processing = type_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto scoped_enum_value_processing = enum_value_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto unscoped_enum_value_processing = enum_value_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto unqualified_enum_value_processing = enum_value_processing_requirements::copy_pretty_function_string;
    };

    template <>
    struct pretty_function_traits<c::legacy_clang1_cdecl>
    {
        static constexpr int type_prefix_size = sizeof("boost::reflecto::d::t __cdecl boost::reflecto::d::q(void) [T = ") - 1;
        static constexpr int type_prefix_size_constexpr = type_prefix_size;
        static constexpr int enum_prefix_size = sizeof("boost::reflecto::d::t __cdecl boost::reflecto::d::g(void) [Enum = ") - 1;
        static constexpr int enum_prefix_size_constexpr = enum_prefix_size;
        static constexpr int enum_separator_size = sizeof("; Value = ") - 1;
        static constexpr int suffix_size = sizeof("]") - 1;
        static constexpr auto type_processing = type_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto scoped_enum_value_processing = enum_value_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto unscoped_enum_value_processing = enum_value_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto unqualified_enum_value_processing = enum_value_processing_requirements::copy_pretty_function_string;
    };

    template <>
    struct pretty_function_traits<c::legacy_clang2>
    {
        static constexpr int type_prefix_size = sizeof("boost::reflecto::d::t boost::reflecto::d::q() [T = ") - 1;
        static constexpr int type_prefix_size_constexpr = type_prefix_size;
        static constexpr int enum_prefix_size = sizeof("boost::reflecto::d::t boost::reflecto::d::g() [Enum = ") - 1;
        static constexpr int enum_prefix_size_constexpr = enum_prefix_size;
        static constexpr int enum_separator_size = sizeof("; Value = ") - 1;
        static constexpr int suffix_size = sizeof("]") - 1;
        static constexpr auto type_processing = type_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto scoped_enum_value_processing = enum_value_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto unscoped_enum_value_processing = enum_value_processing_requirements::strip_type_prefix_and_space_before_template_closing_bracket;
        static constexpr auto unqualified_enum_value_processing = enum_value_processing_requirements::copy_pretty_function_string;
    };

    template <>
    struct pretty_function_traits<c::legacy_clang2_cdecl>
    {
        static constexpr int type_prefix_size = sizeof("boost::reflecto::d::t __cdecl boost::reflecto::d::q(void) [T = ") - 1;
        static constexpr int type_prefix_size_constexpr = type_prefix_size;
        static constexpr int enum_prefix_size = sizeof("boost::reflecto::d::t __cdecl boost::reflecto::d::g(void) [Enum = ") - 1;
        static constexpr int enum_prefix_size_constexpr = enum_prefix_size;
        static constexpr int enum_separator_size = sizeof("; Value = ") - 1;
        static constexpr int suffix_size = sizeof("]") - 1;
        static constexpr auto type_processing = type_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto scoped_enum_value_processing = enum_value_processing_requirements::strip_space_before_template_closing_bracket;
        static constexpr auto unscoped_enum_value_processing = enum_value_processing_requirements::strip_type_prefix_and_space_before_template_closing_bracket;
        static constexpr auto unqualified_enum_value_processing = enum_value_processing_requirements::copy_pretty_function_string;
    };

    template <>
    struct pretty_function_traits<c::msvc_cdecl>
    {
        static constexpr int type_prefix_size = sizeof("struct boost::reflecto::d::t __cdecl boost::reflecto::d::q<") - 1;
        static constexpr int type_prefix_size_constexpr = type_prefix_size;
        static constexpr int enum_prefix_size = type_prefix_size;
        static constexpr int enum_prefix_size_constexpr = enum_prefix_size;
        static constexpr int enum_separator_size = sizeof(",") - 1;
        static constexpr int suffix_size = sizeof(">(void)") - 1;
        static constexpr auto type_processing = type_processing_requirements::strip_keywords_and_space_before_template_closing_bracket;
        static constexpr auto scoped_enum_value_processing = enum_value_processing_requirements::none;
        static constexpr auto unscoped_enum_value_processing = enum_value_processing_requirements::none;
        static constexpr auto unqualified_enum_value_processing = enum_value_processing_requirements::none;
    };

    ////////////////////////////////////////

    constexpr std::uint64_t hash_start = 14695981039346656037ull;

    constexpr std::uint64_t hash_step(std::uint64_t h, char c) noexcept
    {
        return (h ^ static_cast<std::uint64_t>(c)) * 1099511628211;
    }

    constexpr std::uint64_t hash_sequence(char const * b, char const * e) noexcept
    {
        std::uint64_t h = hash_start;
        while( b != e )
            h = hash_step(h, *b++);
        return h;
    }

    ////////////////////////////////////////

    template <int MaxSize>
    struct stripped
    {
        char buf[MaxSize + 1];
        int len;
        std::uint64_t hash;
    };

    template <int MaxSize>
    constexpr stripped<MaxSize> strip_space_before_template_closing_bracket(char const * src, int size) noexcept
    {
        stripped<MaxSize> result{};
        char const * end = src + size;
        int len = 0;
        std::uint64_t h = hash_start;
        while( src != end )
        {
            if( src[0] == ' ' && src != end - 1 && src[1] == '>' )
                ++src;
            else
            {
                h = hash_step(h, *src);
                result.buf[len++] = *src++;
            }
        }
        result.len = len;
        result.hash = h;
        return result;
    }

    constexpr int find_parent_ns_end(char const * s, int end) noexcept
    {
        int depth = 0;
        for( int i = end; i != 1; --i )
        {
            char ch = s[i - 1];
            if( ch == '>' )
                ++depth;
            else if( ch == '<' )
                --depth;
            else if( depth == 0 && ch == ':' && s[i - 2] == ':' )
                return i - 2;
        }
        return 0;
    }

    template <int MaxSize>
    constexpr stripped<MaxSize> strip_keywords_and_space_before_template_closing_bracket(char const * src, int size) noexcept
    {
        stripped<MaxSize> result{};
        char const * end = src + size;
        int len = 0;
        std::uint64_t h = hash_start;
        while( src != end )
        {
            if( end - src >= 7 && src[0] == 's' && src[1] == 't' && src[2] == 'r' && src[3] == 'u' && src[4] == 'c' && src[5] == 't' && src[6] == ' ' )
                src += 7;
            else if( end - src >= 6 && src[0] == 'c' && src[1] == 'l' && src[2] == 'a' && src[3] == 's' && src[4] == 's' && src[5] == ' ' )
                src += 6;
            else if( end - src >= 5 && src[0] == 'e' && src[1] == 'n' && src[2] == 'u' && src[3] == 'm' && src[4] == ' ' )
                src += 5;
            else if( src[0] == ' ' && src != end - 1 && src[1] == '>' )
                ++src;
            else
            {
                h = hash_step(h, *src);
                result.buf[len++] = *src++;
            }
        }
        result.len = len;
        result.hash = h;
        return result;
    }

    ////////////////////////////////////////

    template <int N, int M>
    constexpr bool cmp_signature(char const (&pf)[N], char const (&expected)[M]) noexcept
    {
        if( N != M )
            return false;
        for( int i = 0; i < N - 1; ++i )
            if( pf[i] != expected[i] )
                return false;
        return true;
    }

    enum e { w };

    template <class Enum, Enum Value>
    constexpr c BOOST_REFLECTO_CDECL p()
    {
        static_assert(std::is_enum<Enum>::value);
        return
            // clang style:
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "c boost::reflecto::d::p() [Enum = boost::reflecto::d::e, Value = boost::reflecto::d::w]") ? c::clang :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "c boost::reflecto::d::p() [Enum = boost::reflecto::d::e; Value = w]") ? c::clang :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "c __cdecl boost::reflecto::d::p(void) [Enum = boost::reflecto::d::e, Value = boost::reflecto::d::w]") ? c::clang_cdecl :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "c __cdecl boost::reflecto::d::p(void) [Enum = boost::reflecto::d::e; Value = w]") ? c::clang_cdecl :
            // gcc style:
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "constexpr boost::reflecto::d::c boost::reflecto::d::p() [with Enum = boost::reflecto::d::e; Enum Value = boost::reflecto::d::w]") ? c::gcc :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "constexpr boost::reflecto::d::c boost::reflecto::d::p() [with Enum = e; Enum Value = boost::reflecto::d::w]") ? c::gcc :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "constexpr boost::reflecto::d::c __cdecl boost::reflecto::d::p() [with Enum = boost::reflecto::d::e; Enum Value = boost::reflecto::d::w]") ? c::gcc_cdecl :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "constexpr boost::reflecto::d::c __cdecl boost::reflecto::d::p() [with Enum = e; Enum Value = boost::reflecto::d::w]") ? c::gcc_cdecl :
            // old clang style:
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "boost::reflecto::d::c boost::reflecto::d::p() [Enum = boost::reflecto::d::e, Value = boost::reflecto::d::w]") ? c::legacy_clang1 :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "boost::reflecto::d::c boost::reflecto::d::p() [Enum = boost::reflecto::d::e, Value = w]") ? c::legacy_clang1 :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "boost::reflecto::d::c boost::reflecto::d::p() [Enum = boost::reflecto::d::e; Value = w]") ? c::legacy_clang1 :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "boost::reflecto::d::c __cdecl boost::reflecto::d::p(void) [Enum = boost::reflecto::d::e, Value = boost::reflecto::d::w]") ? c::legacy_clang1_cdecl :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "boost::reflecto::d::c __cdecl boost::reflecto::d::p(void) [Enum = boost::reflecto::d::e, Value = w]") ? c::legacy_clang1_cdecl :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "boost::reflecto::d::c __cdecl boost::reflecto::d::p(void) [Enum = boost::reflecto::d::e; Value = w]") ? c::legacy_clang1_cdecl :
            // old clang style (with enum type prefix on unscoped values):
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "boost::reflecto::d::c boost::reflecto::d::p() [Enum = boost::reflecto::d::e, Value = boost::reflecto::d::e::w]") ? c::legacy_clang2 :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "boost::reflecto::d::c boost::reflecto::d::p() [Enum = boost::reflecto::d::e; Value = boost::reflecto::d::e::w]") ? c::legacy_clang2 :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "boost::reflecto::d::c __cdecl boost::reflecto::d::p(void) [Enum = boost::reflecto::d::e, Value = boost::reflecto::d::e::w]") ? c::legacy_clang2_cdecl :
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "boost::reflecto::d::c __cdecl boost::reflecto::d::p(void) [Enum = boost::reflecto::d::e; Value = boost::reflecto::d::e::w]") ? c::legacy_clang2_cdecl :
            // msvc style:
            cmp_signature(BOOST_REFLECTO_PRETTY_FUNCTION, "enum boost::reflecto::d::c __cdecl boost::reflecto::d::p<enum boost::reflecto::d::e,boost::reflecto::d::w>(void)") ? c::msvc_cdecl :
            // Unrecognized, please file a github issue:
            c::unknown;
    }

    ////////////////////////////////////////

    using pf_traits = pretty_function_traits<p<e, w>()>;

    struct t
    {
        char const * begin;
        int size;
    };

    constexpr bool has_unnamed_ns(char const * s, int size) noexcept
    {
        for( int i = 1; i < size; ++i )
            if( s[i] == ':' && (s[i - 1] == ')' || s[i - 1] == '\'' || s[i - 1] == '}') )
                return true;
        return false;
    }

    template <class T>
    constexpr t BOOST_REFLECTO_CDECL q()
    {
        constexpr char const * pf = BOOST_REFLECTO_PRETTY_FUNCTION;
        constexpr int b = pf_traits::type_prefix_size_constexpr;
        constexpr int size = sizeof(BOOST_REFLECTO_PRETTY_FUNCTION) - 1 - pf_traits::suffix_size - b;
        static_assert(!has_unnamed_ns(pf + b, size), "unnamed namespaces are not allowed");
        return { pf + b, size };
    }
} // namespace d

} // namespace boost::reflecto

#endif // #ifndef BOOST_REFLECTO_DETAIL_PRETTY_FUNCTION_TRAITS_HPP_INCLUDED
// <<< #include <boost/reflecto/detail/pretty_function_traits.hpp>
// #line 11 "boost/reflecto/bind_instance.hpp"
// >>> #include <boost/reflecto/detail/mp11.hpp>
#ifndef BOOST_REFLECTO_DETAIL_MP11_HPP_INCLUDED
#define BOOST_REFLECTO_DETAIL_MP11_HPP_INCLUDED

// #line 6 "boost/reflecto/detail/mp11.hpp"
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// The following are based on Boost.Mp11 by Peter Dimov.
// Copyright 2015-2023 Peter Dimov.

namespace boost::reflecto::d {
namespace mp11_reflecto {

    template<class... T> struct mp_list
    {
    };

    ////////////////////////////////////////

    template<class L> struct mp_front_impl
    {
    };

    template<template<class...> class L, class T1, class... T> struct mp_front_impl<L<T1, T...>>
    {
        using type = T1;
    };

    template<class L> using mp_front = typename mp_front_impl<L>::type;

    ////////////////////////////////////////

    template<class L, class... T> struct mp_push_front_impl
    {
    };

    template<template<class...> class L, class... U, class... T> struct mp_push_front_impl<L<U...>, T...>
    {
        using type = L<T..., U...>;
    };

    template<class L, class... T> using mp_push_front = typename mp_push_front_impl<L, T...>::type;

    ////////////////////////////////////////

    template<class L, class... T> struct mp_push_back_impl
    {
    };

    template<template<class...> class L, class... U, class... T> struct mp_push_back_impl<L<U...>, T...>
    {
        using type = L<U..., T...>;
    };

    template<class L, class... T> using mp_push_back = typename mp_push_back_impl<L, T...>::type;

    ////////////////////////////////////////

    template<
        class L1 = mp_list<>, class L2 = mp_list<>, class L3 = mp_list<>,
        class L4 = mp_list<>, class L5 = mp_list<>, class L6 = mp_list<>,
        class L7 = mp_list<>, class L8 = mp_list<>, class L9 = mp_list<>,
        class L10 = mp_list<>, class L11 = mp_list<>>
    struct append_11_impl
    {
    };

    template<
        template<class...> class L1, class... T1,
        template<class...> class L2, class... T2,
        template<class...> class L3, class... T3,
        template<class...> class L4, class... T4,
        template<class...> class L5, class... T5,
        template<class...> class L6, class... T6,
        template<class...> class L7, class... T7,
        template<class...> class L8, class... T8,
        template<class...> class L9, class... T9,
        template<class...> class L10, class... T10,
        template<class...> class L11, class... T11>
    struct append_11_impl<
        L1<T1...>, L2<T2...>, L3<T3...>, L4<T4...>, L5<T5...>, L6<T6...>,
        L7<T7...>, L8<T8...>, L9<T9...>, L10<T10...>, L11<T11...>>
    {
        using type = L1<T1..., T2..., T3..., T4..., T5..., T6..., T7..., T8..., T9..., T10..., T11...>;
    };

    template<class... L> using mp_append = typename append_11_impl<L...>::type;

    ////////////////////////////////////////

    template<class L, template<class...> class B> struct mp_rename_impl
    {
    };

    template<template<class...> class L, class... T, template<class...> class B> struct mp_rename_impl<L<T...>, B>
    {
        using type = B<T...>;
    };

    template<class L, template<class...> class B> using mp_rename = typename mp_rename_impl<L, B>::type;

    ////////////////////////////////////////

    template<class L1, class L2> struct mp_assign_impl
    {
    };

    template<template<class...> class L1, class... T, template<class...> class L2, class... U> struct mp_assign_impl<L1<T...>, L2<U...>>
    {
        using type = L1<U...>;
    };

    template<class L1, class L2> using mp_assign = typename mp_assign_impl<L1, L2>::type;

    ////////////////////////////////////////

    template<template<class...> class F, class P, class... L> struct mp_product_impl_2
    {
    };

    template<template<class...> class F, class P> struct mp_product_impl_2<F, P>
    {
        using type = mp_list<mp_rename<P, F>>;
    };

    template<template<class...> class F, class P, template<class...> class L1, class... T1, class... L>
    struct mp_product_impl_2<F, P, L1<T1...>, L...>
    {
        using type = mp_append<typename mp_product_impl_2<F, mp_push_back<P, T1>, L...>::type...>;
    };

    template<template<class...> class F, class... L> struct mp_product_impl
    {
    };

    template<template<class...> class F> struct mp_product_impl<F>
    {
        using type = mp_list< F<> >;
    };

    template<template<class...> class F, class L1, class... L> struct mp_product_impl<F, L1, L...>
    {
        using type = mp_assign<L1, typename mp_product_impl_2<F, mp_list<>, L1, L...>::type>;
    };

    template<template<class...> class F, class... L> using mp_product = typename mp_product_impl<F, L...>::type;

} // namespace mp11_reflecto
} // namespace boost::reflecto::d

#endif // #ifndef BOOST_REFLECTO_DETAIL_MP11_HPP_INCLUDED
// <<< #include <boost/reflecto/detail/mp11.hpp>
// #line 12 "boost/reflecto/bind_instance.hpp"
#include <type_traits>

namespace boost::reflecto {

template <class>
struct resolve_for {};

template <class T>
struct is_specialization
{
    static constexpr bool value = !std::is_base_of_v<unspecialized, T>;
};

namespace d
{
    using mp11_reflecto::mp_list;
    using mp11_reflecto::mp_front;
    using mp11_reflecto::mp_push_front;
    using mp11_reflecto::mp_product;

    template <std::uint64_t>
    struct Within {};

    template <std::uint64_t>
    struct Exact {};

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
    constexpr std::uint64_t ns_hash() noexcept
    {
        constexpr auto info = n<T>();
        return hash_sequence(info.begin, info.begin + info.size);
    }

    template <class T>
    constexpr std::uint64_t within_scope_hash() noexcept
    {
        constexpr auto info = n<T>();
        static_assert(info.size != 0, "within_scope_of cannot be used with globally-scoped types");
        return hash_sequence(info.begin, info.begin + info.size);
    }

    ////////////////////////////////////////

    template <class T>
    struct is_rf: std::false_type {};

    template <class T>
    struct is_rf<resolve_for<T>>: std::true_type {};

    template <class Inst>
    struct has_rf;

    template <template <class...> class S, class... Args>
    struct has_rf<S<Args...>>
    {
        static constexpr bool value = (is_rf<Args>::value || ...);
    };

    ////////////////////////////////////////

    template <class... Levels>
    struct chain;

    template <class Lv>
    struct chain<Lv> {};

    template <class Lv, class... Rest>
    struct chain<Lv, Rest...>: chain<Rest...> {};

    template <class Chain>
    struct suffixes;

    template <class Lv>
    struct suffixes<chain<Lv>>
    {
        using type = mp_list<chain<Lv>>;
    };

    template <class Lv, class... Rest>
    struct suffixes<chain<Lv, Rest...>>
    {
        using type = mp_push_front<typename suffixes<chain<Rest...>>::type, chain<Lv, Rest...>>;
    };

    ////////////////////////////////////////

    template <class T, int End, class... Levels>
    struct walk_chain
    {
        static constexpr char const * begin = n<T>().begin;
        static constexpr std::uint64_t h = hash_sequence(begin, begin + End);
        static constexpr int pe = find_parent_ns_end(begin, End);
        using type = typename walk_chain<T, pe, Levels..., Within<h>>::type;
    };

    template <class T, class... Levels>
    struct walk_chain<T, 0, Levels...>
    {
        using type = chain<Levels...>;
    };

    template <class T, int End, class... Levels>
    struct start_chain
    {
        static constexpr char const * begin = n<T>().begin;
        static constexpr std::uint64_t h = hash_sequence(begin, begin + End);
        static constexpr int pe = find_parent_ns_end(begin, End);
        using type = typename walk_chain<T, pe, Levels..., Exact<h>, Within<h>>::type;
    };

    template <class T, class... Levels>
    struct start_chain<T, 0, Levels...>
    {
        using type = chain<Levels..., Exact<hash_start>>;
    };

    template <class T>
    struct make_chain
    {
        static constexpr auto info = n<T>();
        using type = typename start_chain<T, info.size, T>::type;
    };

    ////////////////////////////////////////

    template <class... Args>
    struct collect_rf_suffixes;

    template <>
    struct collect_rf_suffixes<>
    {
        using type = mp_list<>;
    };

    template <class T, class... Rest>
    struct collect_rf_suffixes<resolve_for<T>, Rest...>
    {
        using chain_t = typename make_chain<T>::type;
        using sfx = typename suffixes<chain_t>::type;
        using type = mp_push_front<typename collect_rf_suffixes<Rest...>::type, sfx>;
    };

    template <class Arg, class... Rest>
    struct collect_rf_suffixes<Arg, Rest...>
    {
        using type = typename collect_rf_suffixes<Rest...>::type;
    };

    template <class Inst>
    struct collect_rf_suffixes_from;

    template <template <class...> class S, class... Args>
    struct collect_rf_suffixes_from<S<Args...>>
    {
        using type = typename collect_rf_suffixes<Args...>::type;
    };

    template <class... Args>
    struct collect_full_chains;

    template <>
    struct collect_full_chains<>
    {
        using type = mp_list<>;
    };

    template <class T, class... Rest>
    struct collect_full_chains<resolve_for<T>, Rest...>
    {
        using chain_t = typename make_chain<T>::type;
        using type = mp_push_front<typename collect_full_chains<Rest...>::type, chain_t>;
    };

    template <class Arg, class... Rest>
    struct collect_full_chains<Arg, Rest...>
    {
        using type = typename collect_full_chains<Rest...>::type;
    };

    template <class Inst>
    struct collect_full_chains_from;

    template <template <class...> class S, class... Args>
    struct collect_full_chains_from<S<Args...>>
    {
        using type = typename collect_full_chains<Args...>::type;
    };

    ////////////////////////////////////////

    template <class SuffixLists>
    struct product_from_list;

    template <class... SLs>
    struct product_from_list<mp_list<SLs...>>
    {
        using type = mp_product<mp_list, SLs...>;
    };

    ////////////////////////////////////////

    template <template <class...> class S, class Prefix, class Replacements, class... Suffix>
    struct subst_all_rf;

    template <template <class...> class S, class... Prefix, class... Rs>
    struct subst_all_rf<S, mp_list<Prefix...>, mp_list<Rs...>>
    {
        using type = S<Prefix...>;
    };

    template <template <class...> class S, class... Prefix, class R, class... Rs, class T, class... Suffix>
    struct subst_all_rf<S, mp_list<Prefix...>, mp_list<R, Rs...>, resolve_for<T>, Suffix...>
    {
        using type = typename subst_all_rf<S, mp_list<Prefix..., R>, mp_list<Rs...>, Suffix...>::type;
    };

    template <template <class...> class S, class... Prefix, class Replacements, class Arg, class... Suffix>
    struct subst_all_rf<S, mp_list<Prefix...>, Replacements, Arg, Suffix...>
    {
        using type = typename subst_all_rf<S, mp_list<Prefix..., Arg>, Replacements, Suffix...>::type;
    };

    template <class Inst, class Replacements>
    struct apply_subst;

    template <template <class...> class S, class... Args, class Replacements>
    struct apply_subst<S<Args...>, Replacements>
    {
        using type = typename subst_all_rf<S, mp_list<>, Replacements, Args...>::type;
    };

    template <class T>
    struct strip_rf { using type = T; };

    template <class T>
    struct strip_rf<resolve_for<T>> { using type = T; };

    template <class Inst>
    struct default_subst;

    template <template <class...> class S, class... Args>
    struct default_subst<S<Args...>>
    {
        using type = S<typename strip_rf<Args>::type...>;
    };

    ////////////////////////////////////////

    template <class Inst, class ChainSuffixTuple, class = void>
    struct one_overload
    {
        struct no_match;
        static void call(no_match);
    };

    template <class Inst, class... Suffixes>
    struct one_overload<Inst, mp_list<Suffixes...>,
        std::enable_if_t<is_specialization<
            typename apply_subst<Inst, mp_list<mp_front<Suffixes>...>>::type>::value>>
    {
        static typename apply_subst<Inst, mp_list<mp_front<Suffixes>...>>::type
        call(Suffixes...);
    };

    template <class Inst, class CrossProduct>
    struct overload_set_impl;

    template <class Inst, class... Tuples>
    struct overload_set_impl<Inst, mp_list<Tuples...>>: one_overload<Inst, Tuples>...
    {
        using one_overload<Inst, Tuples>::call...;
    };

    template <class Inst, class CrossProduct>
    struct overload_set: overload_set_impl<Inst, CrossProduct>
    {
        using overload_set_impl<Inst, CrossProduct>::call;
        static typename default_subst<Inst>::type call(...);
    };

    template <class OverloadSet, class FullChains>
    struct resolve_call;

    template <class OverloadSet, class... Chains>
    struct resolve_call<OverloadSet, mp_list<Chains...>>
    {
        using type = decltype(OverloadSet::call(Chains{}...));
    };

    ////////////////////////////////////////

    template <class Inst, bool = has_rf<Inst>::value>
    struct bind_instance_;

    template <class Inst>
    struct bind_instance_<Inst, false>
    {
        using type = Inst;
    };

    template <class Inst>
    struct bind_instance_<Inst, true>
    {
        using suffix_lists = typename collect_rf_suffixes_from<Inst>::type;
        using cp = typename product_from_list<suffix_lists>::type;
        using full_chains = typename collect_full_chains_from<Inst>::type;
        using type = typename resolve_call<overload_set<Inst, cp>, full_chains>::type;
    };
} // namespace d

template <class T>
using within_scope_of = d::Within<d::within_scope_hash<T>()>;

template <class T>
using exact_scope_of = d::Exact<d::ns_hash<T>()>;

template <class Inst>
using bind_instance = typename d::bind_instance_<Inst>::type;

} // namespace boost::reflecto

#endif // #ifndef BOOST_REFLECTO_BIND_INSTANCE_HPP_INCLUDED
// >>> #include <boost/reflecto/name.hpp>
#ifndef BOOST_REFLECTO_NAME_HPP_INCLUDED
#define BOOST_REFLECTO_NAME_HPP_INCLUDED

// #line 6 "boost/reflecto/name.hpp"
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// #include <boost/reflecto/config.hpp> // Expanded at line 17
#include <cstdint>
#include <string_view>

namespace boost::reflecto {

enum class name_kind
{
    empty,
    scope_name,
    type_name,
    value_name,
    short_value_name,
    unnamed_value,
    value_out_of_lookup_range
};

////////////////////////////////////////

class name:
    public std::string_view
{
    std::uint64_t hash_;
    name_kind kind_;

public:

    explicit name(name const &) = default;

    constexpr name() noexcept:
        std::string_view(),
        hash_(14695981039346656037ull),
        kind_(name_kind::empty)
    {
    }

    constexpr name(char const * begin, int size, std::uint64_t hash, name_kind kind) noexcept:
        std::string_view(begin, size),
        hash_(hash),
        kind_(kind)
    {
        BOOST_REFLECTO_ASSERT(empty() == (kind_ == name_kind::empty));
    }

    constexpr name_kind kind() const noexcept
    {
        return kind_;
    }

    constexpr std::uint64_t hash() const noexcept
    {
        return hash_;
    }

    friend constexpr bool operator==(name const & a, name const & b) noexcept
    {
        return a.hash_ == b.hash_;
    }

    friend constexpr bool operator!=(name const & a, name const & b) noexcept
    {
        return !(a == b);
    }
};

} // namespace boost::reflecto

#endif // #ifndef BOOST_REFLECTO_NAME_HPP_INCLUDED
// >>> #include <boost/reflecto/scope_name_of.hpp>
#ifndef BOOST_REFLECTO_SCOPE_NAME_OF_HPP_INCLUDED
#define BOOST_REFLECTO_SCOPE_NAME_OF_HPP_INCLUDED

// #line 6 "boost/reflecto/scope_name_of.hpp"
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// #include <boost/reflecto/config.hpp> // Expanded at line 17
// #include <boost/reflecto/detail/pretty_function_traits.hpp> // Expanded at line 73
// #include <boost/reflecto/name.hpp> // Expanded at line 924

namespace boost::reflecto {

namespace d
{
    template <class T, type_processing_requirements>
    struct scope_name_of_;

    template <class T>
    struct scope_name_of_<T, type_processing_requirements::none>
    {
        static constexpr t x = q<T>();
        static constexpr int ns_size = find_parent_ns_end(x.begin, x.size);
        static constexpr name n{x.begin, ns_size,
            hash_sequence(x.begin, x.begin + ns_size),
            ns_size > 0 ? name_kind::scope_name : name_kind::empty};
    };

    template <class T>
    struct scope_name_of_<T, type_processing_requirements::strip_space_before_template_closing_bracket>
    {
        static constexpr t x = q<T>();
        static constexpr int ns_size = find_parent_ns_end(x.begin, x.size);
        static constexpr d::stripped<ns_size> s = strip_space_before_template_closing_bracket<ns_size>(x.begin, ns_size);
        static constexpr name n{s.buf, s.len, s.hash,
            s.len > 0 ? name_kind::scope_name : name_kind::empty};
    };

    template <class T>
    struct scope_name_of_<T, type_processing_requirements::strip_keywords_and_space_before_template_closing_bracket>
    {
        static constexpr t x = q<T>();
        static constexpr int ns_size = find_parent_ns_end(x.begin, x.size);
        static constexpr d::stripped<ns_size> s = strip_keywords_and_space_before_template_closing_bracket<ns_size>(x.begin, ns_size);
        static constexpr name n{s.buf, s.len, s.hash,
            s.len > 0 ? name_kind::scope_name : name_kind::empty};
    };
} // namespace d

template <class T>
constexpr name const & scope_name_of() noexcept
{
    return d::scope_name_of_<T, d::pf_traits::type_processing>::n;
}

} // namespace boost::reflecto

#endif // #ifndef BOOST_REFLECTO_SCOPE_NAME_OF_HPP_INCLUDED
// >>> #include <boost/reflecto/scope_traits.hpp>
#ifndef BOOST_REFLECTO_SCOPE_TRAITS_HPP_INCLUDED
#define BOOST_REFLECTO_SCOPE_TRAITS_HPP_INCLUDED

// #line 6 "boost/reflecto/scope_traits.hpp"
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// #include <boost/reflecto/config.hpp> // Expanded at line 17
// #include <boost/reflecto/detail/pretty_function_traits.hpp> // Expanded at line 73
// #include <boost/reflecto/scope_name_of.hpp> // Expanded at line 1000
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
// >>> #include <boost/reflecto/type_name.hpp>
#ifndef BOOST_REFLECTO_TYPE_NAME_HPP_INCLUDED
#define BOOST_REFLECTO_TYPE_NAME_HPP_INCLUDED

// #line 6 "boost/reflecto/type_name.hpp"
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// #include <boost/reflecto/config.hpp> // Expanded at line 17
// #include <boost/reflecto/detail/pretty_function_traits.hpp> // Expanded at line 73
// #include <boost/reflecto/name.hpp> // Expanded at line 924

namespace boost::reflecto {

namespace d
{
    template <class T, type_processing_requirements>
    struct type_name_;

    template <class T>
    struct type_name_<T, type_processing_requirements::none>
    {
        static constexpr t x = q<T>();
        static constexpr name n{x.begin, x.size, hash_sequence(x.begin, x.begin + x.size),
            name_kind::type_name};
    };

    template <class T>
    struct type_name_<T, type_processing_requirements::strip_space_before_template_closing_bracket>
    {
        static constexpr t x = q<T>();
        static constexpr d::stripped<x.size> s = strip_space_before_template_closing_bracket<x.size>(x.begin, x.size);
        static constexpr name n{s.buf, s.len, s.hash,
            name_kind::type_name};
    };

    template <class T>
    struct type_name_<T, type_processing_requirements::strip_keywords_and_space_before_template_closing_bracket>
    {
        static constexpr t x = q<T>();
        static constexpr d::stripped<x.size> s = strip_keywords_and_space_before_template_closing_bracket<x.size>(x.begin, x.size);
        static constexpr name n{s.buf, s.len, s.hash,
            name_kind::type_name};
    };
} // namespace d

template <class T>
constexpr name const & type_name() noexcept
{
    return d::type_name_<T, d::pf_traits::type_processing>::n;
}

} // namespace boost::reflecto

#endif // #ifndef BOOST_REFLECTO_TYPE_NAME_HPP_INCLUDED
// >>> #include <boost/reflecto/value_name.hpp>
#ifndef BOOST_REFLECTO_VALUE_NAME_HPP_INCLUDED
#define BOOST_REFLECTO_VALUE_NAME_HPP_INCLUDED

// #line 6 "boost/reflecto/value_name.hpp"
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// #include <boost/reflecto/config.hpp> // Expanded at line 17
// #include <boost/reflecto/bind_instance.hpp> // Expanded at line 64
// #include <boost/reflecto/name.hpp> // Expanded at line 924
#include <utility>

#if defined(__clang__) && __clang_major__ >= 15 && __clang_major__ < 20
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wenum-constexpr-conversion"
#endif

namespace boost::reflecto {

template <class Enum>
using lookup_range = bind_instance<enum_lookup_range<resolve_for<Enum>>>;

namespace d
{
    constexpr t strip_enum_value_qualification(t x) noexcept
    {
        char const * b = x.begin;
        char const * e = x.begin + x.size;
        for( char const * p = e; p != b; --p )
        {
            if( p[-1] == ':' && p[-2] == ':' )
                return { p, static_cast<int>(e - p) };
        }
        return x;
    }

    template <int MaxSize>
    constexpr stripped<MaxSize> strip_enum_type_prefix_and_space_before_template_closing_bracket(char const * value, int value_len, int type_len) noexcept
    {
        BOOST_REFLECTO_ASSERT(value_len > 0);
        BOOST_REFLECTO_ASSERT(type_len > 0);
        if( value_len <= type_len + 2 )
            return strip_space_before_template_closing_bracket<MaxSize>(value, value_len);
        stripped<MaxSize> result{};
        int unqual_start = 0;
        for( int i = type_len - 1; i != 0; --i )
        {
            if( value[i] == ':' && value[i - 1] == ':' )
            {
                unqual_start = i + 1;
                break;
            }
        }
        int len = 0;
        std::uint64_t h = hash_start;
        for( int i = 0; i != unqual_start; ++i )
        {
            h = hash_step(h, value[i]);
            result.buf[len++] = value[i];
        }
        char const * src = value + type_len + 2;
        char const * end = value + value_len;
        while( src != end )
        {
            if( src[0] == ' ' && src != end - 1 && src[1] == '>' )
                ++src;
            else
            {
                h = hash_step(h, *src);
                result.buf[len++] = *src++;
            }
        }
        result.len = len;
        result.hash = h;
        return result;
    }

    template <class Enum, Enum Value>
    constexpr t BOOST_REFLECTO_CDECL g()
    {
        static_assert(std::is_enum<Enum>::value, "d::g requires an enum type");
        constexpr char const * pf = BOOST_REFLECTO_PRETTY_FUNCTION;
        constexpr int type_len = q<Enum>().size;
        constexpr int value_start = pf_traits::enum_prefix_size_constexpr + type_len + pf_traits::enum_separator_size;
        constexpr int end = sizeof(BOOST_REFLECTO_PRETTY_FUNCTION) - 1 - pf_traits::suffix_size;
        return { pf + value_start, end - value_start };
    }

    template <int MaxSize>
    constexpr stripped<MaxSize> strip_enum_value_qualification_to_buffer(char const * src, int size) noexcept
    {
        BOOST_REFLECTO_ASSERT(size > 0);
        int start = 0;
        for( int i = size; i != 1; --i )
        {
            if( src[i - 1] == ':' && src[i - 2] == ':' )
            {
                start = i;
                break;
            }
        }
        stripped<MaxSize> result{};
        int len = 0;
        std::uint64_t h = hash_start;
        for( int i = start; i != size; ++i )
        {
            h = hash_step(h, src[i]);
            result.buf[len++] = src[i];
        }
        result.len = len;
        result.hash = h;
        return result;
    }

    constexpr bool is_named_enum_value_name(char c) noexcept
    {
        return c != '(' && c != '-' && !(c >= '0' && c <= '9');
    }

    template <auto EnumValue, bool Unqualify, enum_value_processing_requirements>
    struct value_name_;

    template <auto EnumValue>
    struct value_name_<EnumValue, false, enum_value_processing_requirements::none>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = g<Enum, EnumValue>();
        static constexpr name n{x.begin, x.size, hash_sequence(x.begin, x.begin + x.size),
            is_named_enum_value_name(x.begin[0]) ? name_kind::value_name : name_kind::unnamed_value};
    };

    template <auto EnumValue>
    struct value_name_<EnumValue, false, enum_value_processing_requirements::strip_space_before_template_closing_bracket>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = g<Enum, EnumValue>();
        static constexpr stripped<x.size> s = strip_space_before_template_closing_bracket<x.size>(x.begin, x.size);
        static constexpr bool named = is_named_enum_value_name(x.begin[0]);
        static constexpr name n{
            named ? s.buf : x.begin,
            named ? s.len : x.size,
            named ? s.hash : hash_sequence(x.begin, x.begin + x.size),
            named ? name_kind::value_name : name_kind::unnamed_value};
    };

    template <auto EnumValue>
    struct value_name_<EnumValue, false, enum_value_processing_requirements::strip_type_prefix_and_space_before_template_closing_bracket>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = g<Enum, EnumValue>();
        static constexpr stripped<x.size> s = strip_enum_type_prefix_and_space_before_template_closing_bracket<x.size>(x.begin, x.size, q<Enum>().size);
        static constexpr bool named = is_named_enum_value_name(x.begin[0]);
        static constexpr name n{
            named ? s.buf : x.begin,
            named ? s.len : x.size,
            named ? s.hash : hash_sequence(x.begin, x.begin + x.size),
            named ? name_kind::value_name : name_kind::unnamed_value};
    };

    template <auto EnumValue>
    struct value_name_<EnumValue, true, enum_value_processing_requirements::none>
    {
        using Enum = decltype(EnumValue);
        static constexpr t raw = g<Enum, EnumValue>();
        static constexpr t x = strip_enum_value_qualification(raw);
        static constexpr bool named = is_named_enum_value_name(raw.begin[0]);
        static constexpr name n{
            named ? x.begin : raw.begin,
            named ? x.size : raw.size,
            named ? hash_sequence(x.begin, x.begin + x.size) : hash_sequence(raw.begin, raw.begin + raw.size),
            named ? name_kind::short_value_name : name_kind::unnamed_value};
    };

    template <auto EnumValue>
    struct value_name_<EnumValue, true, enum_value_processing_requirements::copy_pretty_function_string>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = g<Enum, EnumValue>();
        static constexpr stripped<x.size> s = strip_enum_value_qualification_to_buffer<x.size>(x.begin, x.size);
        static constexpr bool named = is_named_enum_value_name(x.begin[0]);
        static constexpr name n{
            named ? s.buf : x.begin,
            named ? s.len : x.size,
            named ? s.hash : hash_sequence(x.begin, x.begin + x.size),
            named ? name_kind::short_value_name : name_kind::unnamed_value};
    };
} // namespace d

template <auto EnumValue>
constexpr name const & value_name() noexcept
{
    using Enum = decltype(EnumValue);
    static_assert(std::is_enum_v<Enum>);
    using r = lookup_range<Enum>;
    static_assert(static_cast<int>(EnumValue) >= r::min_value, "enum value is below enum_lookup_range::min_value");
    static_assert(static_cast<int>(EnumValue) <= r::max_value, "enum value is above enum_lookup_range::max_value");
    constexpr auto s = std::is_convertible_v<Enum, int>
        ? d::pf_traits::unscoped_enum_value_processing
        : d::pf_traits::scoped_enum_value_processing;
    return d::value_name_<EnumValue, false, s>::n;
}

template <auto EnumValue>
constexpr name const & short_value_name() noexcept
{
    using Enum = decltype(EnumValue);
    static_assert(std::is_enum_v<Enum>);
    using r = lookup_range<Enum>;
    static_assert(static_cast<int>(EnumValue) >= r::min_value, "enum value is below enum_lookup_range::min_value");
    static_assert(static_cast<int>(EnumValue) <= r::max_value, "enum value is above enum_lookup_range::max_value");
    return d::value_name_<EnumValue, true, d::pf_traits::unqualified_enum_value_processing>::n;
}

////////////////////////////////////////

struct enumerator
{
    name const & value_name;
    int value;
};

////////////////////////////////////////

namespace d
{
    // In a constexpr context, some newer compilers do not allow casting int to an invalid enum value.
    // This isn't a check for validity, but a tool to avoid casting to prevent a compile error.
    template <class Enum, int I, class = void>
    struct check_enum_cast_sfinae : std::false_type {};

    template <class Enum, int I>
    struct check_enum_cast_sfinae<Enum, I, std::void_t<std::integral_constant<Enum, static_cast<Enum>(I)>>>
        : std::true_type {};

    template <class Enum, int I, bool = check_enum_cast_sfinae<Enum, I>::value>
    struct enum_cast_sfinae
    {
        static constexpr Enum value = Enum{};
    };

    template <class Enum, int I>
    struct enum_cast_sfinae<Enum, I, true>
    {
        static constexpr Enum value = static_cast<Enum>(I);
    };

    inline constexpr name out_of_lookup_range_name{"*unknown*", 9, 11775755009147575841ull, name_kind::value_out_of_lookup_range};

    template <class Enum, bool Unqualify,
        class = std::make_integer_sequence<int,
            lookup_range<Enum>::max_value -
            lookup_range<Enum>::min_value + 1>>
    struct value_lookup_table;

    template <class Enum, bool Unqualify, int... Is>
    struct value_lookup_table<Enum, Unqualify, std::integer_sequence<int, Is...>>
    {
        static constexpr int minv = lookup_range<Enum>::min_value;

        static constexpr auto s = Unqualify
            ? pf_traits::unqualified_enum_value_processing
            : std::is_convertible_v<Enum, int>
                ? pf_traits::unscoped_enum_value_processing
                : pf_traits::scoped_enum_value_processing;

        static constexpr name const * values[sizeof...(Is)] = { &value_name_<enum_cast_sfinae<Enum, minv + Is>::value, Unqualify, s>::n... };

        static constexpr name const & get(Enum value) noexcept
        {
            int i = static_cast<int>(value);
            if( i >= minv && i - minv < static_cast<int>(sizeof...(Is)) )
                return *values[i - minv];
            return out_of_lookup_range_name;
        }
    };
} // namespace d

template <class Enum>
constexpr name const & value_name(Enum value) noexcept
{
    return d::value_lookup_table<Enum, false>::get(value);
}

template <class Enum>
constexpr name const & short_value_name(Enum value) noexcept
{
    return d::value_lookup_table<Enum, true>::get(value);
}

////////////////////////////////////////

namespace d
{
    template <class Enum, int I, bool = check_enum_cast_sfinae<Enum, I>::value>
    struct is_named_enum_value : std::false_type {};

    template <class Enum, int I>
    struct is_named_enum_value<Enum, I, true>
    {
        static constexpr bool value = is_named_enum_value_name(g<Enum, static_cast<Enum>(I)>().begin[0]);
    };

    template <class Enum, int I, int Max, int... NamedIs>
    struct collect_named
    {
        using type = typename std::conditional_t<
            is_named_enum_value<Enum, I>::value,
            collect_named<Enum, I + 1, Max, NamedIs..., I>,
            collect_named<Enum, I + 1, Max, NamedIs...>
        >::type;
    };

    template <class Enum, int Max, int... NamedIs>
    struct collect_named<Enum, Max, Max, NamedIs...>
    {
        using type = std::integer_sequence<int, NamedIs...>;
    };

    template <class Enum>
    struct named_values_seq_
    {
        using r = lookup_range<Enum>;
        using type = typename collect_named<Enum, r::min_value, r::max_value + 1>::type;
    };

    template <class Enum>
    using named_values_seq = typename named_values_seq_<Enum>::type;

    template <class Enum, int I, int Max, bool = is_named_enum_value<Enum, I>::value>
    struct find_first_named
    {
        static constexpr int value = find_first_named<Enum, I + 1, Max>::value;
    };

    template <class Enum, int I, int Max>
    struct find_first_named<Enum, I, Max, true>
    {
        static constexpr int value = I;
    };

    template <class Enum, int I, int Min, bool = is_named_enum_value<Enum, I>::value>
    struct find_last_named
    {
        static constexpr int value = find_last_named<Enum, I - 1, Min>::value;
    };

    template <class Enum, int I, int Min>
    struct find_last_named<Enum, I, Min, true>
    {
        static constexpr int value = I;
    };

    template <class Enum, bool Unqualify, class NamedSeq>
    struct named_values_holder;

    template <class Enum, int... NamedIs>
    struct named_values_holder<Enum, false, std::integer_sequence<int, NamedIs...>>
    {
        static constexpr enumerator values[sizeof...(NamedIs)] = { { value_name<static_cast<Enum>(NamedIs)>(), NamedIs }... };
    };

    template <class Enum, int... NamedIs>
    struct named_values_holder<Enum, true, std::integer_sequence<int, NamedIs...>>
    {
        static constexpr enumerator values[sizeof...(NamedIs)] = { { short_value_name<static_cast<Enum>(NamedIs)>(), NamedIs }... };
    };
} // namespace d

template <class Enum>
constexpr int named_value_count() noexcept
{
    return int(d::named_values_seq<Enum>::size());
}

template <class Enum>
constexpr Enum min_named_value() noexcept
{
    using r = lookup_range<Enum>;
    return static_cast<Enum>(d::find_first_named<Enum, r::min_value, r::max_value + 1>::value);
}

template <class Enum>
constexpr Enum max_named_value() noexcept
{
    using r = lookup_range<Enum>;
    return static_cast<Enum>(d::find_last_named<Enum, r::max_value, r::min_value>::value);
}

template <class Enum>
constexpr enumerator const (&named_values() noexcept)[named_value_count<Enum>()]
{
    return d::named_values_holder<Enum, false, d::named_values_seq<Enum>>::values;
}

template <class Enum>
constexpr enumerator const (&short_named_values() noexcept)[named_value_count<Enum>()]
{
    return d::named_values_holder<Enum, true, d::named_values_seq<Enum>>::values;
}

////////////////////////////////////////

namespace d
{
    template <int N>
    struct idx_array
    {
        int v[N];
    };

    template <class Enum, bool Unqualify, class NamedSeq>
    struct sorted_indices;

    template <class Enum, bool Unqualify, int... NamedIs>
    struct sorted_indices<Enum, Unqualify, std::integer_sequence<int, NamedIs...>>
    {
        static constexpr int N = sizeof...(NamedIs);
        using holder = named_values_holder<Enum, Unqualify, std::integer_sequence<int, NamedIs...>>;

        static constexpr idx_array<N> sorted() noexcept
        {
            idx_array<N> r{};
            for( int i = 0; i != N; ++i )
                r.v[i] = i;
            for( int i = 1; i != N; ++i )
            {
                int key = r.v[i];
                int j = i;
                for( ; j && holder::values[key].value_name < holder::values[r.v[j - 1]].value_name; --j )
                    r.v[j] = r.v[j - 1];
                r.v[j] = key;
            }
            return r;
        }

        static constexpr idx_array<N> value = sorted();
    };

    template <class Enum, bool Unqualify, class NamedSeq, class IndexSeq>
    struct sorted_named_values_holder;

    template <class Enum, bool Unqualify, class NamedSeq, std::size_t... Js>
    struct sorted_named_values_holder<Enum, Unqualify, NamedSeq, std::index_sequence<Js...>>
    {
        using si = sorted_indices<Enum, Unqualify, NamedSeq>;
        using holder = named_values_holder<Enum, Unqualify, NamedSeq>;

        static constexpr enumerator values[sizeof...(Js)] = { holder::values[si::value.v[Js]]... };
    };
} // namespace d

template <class Enum>
constexpr enumerator const (&sorted_named_values() noexcept)[named_value_count<Enum>()]
{
    return d::sorted_named_values_holder<
        Enum, false,
        d::named_values_seq<Enum>,
        std::make_index_sequence<named_value_count<Enum>()>
    >::values;
}

template <class Enum>
constexpr enumerator const (&sorted_short_named_values() noexcept)[named_value_count<Enum>()]
{
    return d::sorted_named_values_holder<
        Enum, true,
        d::named_values_seq<Enum>,
        std::make_index_sequence<named_value_count<Enum>()>
    >::values;
}

} // namespace boost::reflecto

#if defined(__clang__) && __clang_major__ >= 15 && __clang_major__ < 20
#   pragma clang diagnostic pop
#endif

#endif // #ifndef BOOST_REFLECTO_VALUE_NAME_HPP_INCLUDED

#endif // BOOST_REFLECTO_HPP_INCLUDED
