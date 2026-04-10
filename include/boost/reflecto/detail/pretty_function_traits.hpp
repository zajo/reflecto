#ifndef BOOST_REFLECTO_DETAIL_PRETTY_FUNCTION_TRAITS_HPP_INCLUDED
#define BOOST_REFLECTO_DETAIL_PRETTY_FUNCTION_TRAITS_HPP_INCLUDED

// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/reflecto/config.hpp>
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

    constexpr bool has_unnamed_ns(char const * s, int size) noexcept
    {
        for( int i = 1; i < size; ++i )
            if( s[i] == ':' && (s[i - 1] == ')' || s[i - 1] == '}' || s[i - 1] == '\'') )
                return true;
        return false;
    }

    ////////////////////////////////////////

    template <int MaxSize>
    struct stripped
    {
        char buf[MaxSize];
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
}

}

#endif // #ifndef BOOST_REFLECTO_DETAIL_PRETTY_FUNCTION_TRAITS_HPP_INCLUDED
