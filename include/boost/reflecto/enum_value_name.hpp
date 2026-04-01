#ifndef BOOST_REFLECTO_ENUM_VALUE_NAME_HPP_INCLUDED
#define BOOST_REFLECTO_ENUM_VALUE_NAME_HPP_INCLUDED

// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/reflecto/config.hpp>
#include <boost/reflecto/detail/pretty_function_traits.hpp>
#include <boost/reflecto/name.hpp>

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wenum-constexpr-conversion"
#elif defined(__GNUC__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wconversion"
#endif

namespace boost::reflecto {

// Single letter identifiers are used to minimize bloat.
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
        if( value_len <= type_len + 2 )
            return strip_space_before_template_closing_bracket<MaxSize>(value, value_len);
        stripped<MaxSize> result{};
        int unqual_start = 0;
        for( int i = type_len - 1; i > 0; --i )
        {
            if( value[i] == ':' && value[i - 1] == ':' )
            {
                unqual_start = i + 1;
                break;
            }
        }
        int len = 0;
        std::uint64_t h = hash_start;
        for( int i = 0; i < unqual_start; ++i )
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

    struct v { int value; };

    template <class T>
    BOOST_REFLECTO_ALWAYS_INLINE constexpr v BOOST_REFLECTO_CDECL r()
    {
        return { sizeof(BOOST_REFLECTO_PRETTY_FUNCTION) - 1 - pf_traits::type_prefix_size_constexpr - pf_traits::suffix_size };
    }

    template <class Enum, Enum Value>
    BOOST_REFLECTO_ALWAYS_INLINE constexpr t BOOST_REFLECTO_CDECL g()
    {
        static_assert(std::is_enum<Enum>::value, "d::g requires an enum type");
        constexpr char const * pf = BOOST_REFLECTO_PRETTY_FUNCTION;
        constexpr int type_len = r<Enum>().value;
        constexpr int value_start = pf_traits::enum_prefix_size_constexpr + type_len + pf_traits::enum_separator_size;
        constexpr int end = sizeof(BOOST_REFLECTO_PRETTY_FUNCTION) - 1 - pf_traits::suffix_size;
        return { pf + value_start, end - value_start };
    }

    template <int MaxSize>
    constexpr stripped<MaxSize> strip_enum_value_qualification_to_buffer(char const * src, int size) noexcept
    {
        int start = 0;
        for( int i = size; i > 1; --i )
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
        for( int i = start; i < size; ++i )
        {
            h = hash_step(h, src[i]);
            result.buf[len++] = src[i];
        }
        result.len = len;
        result.hash = h;
        return result;
    }

    template <auto EnumValue, bool Unqualify, enum_value_processing_requirements>
    struct enum_value_name_impl;

    template <auto EnumValue>
    struct enum_value_name_impl<EnumValue, false, enum_value_processing_requirements::none>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = g<Enum, EnumValue>();
        static constexpr name n{x.begin, x.size, hash_sequence(x.begin, x.begin + x.size), name_kind::enum_value_name};
    };

    template <auto EnumValue>
    struct enum_value_name_impl<EnumValue, false, enum_value_processing_requirements::strip_space_before_template_closing_bracket>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = g<Enum, EnumValue>();
        static constexpr stripped<x.size> s = strip_space_before_template_closing_bracket<x.size>(x.begin, x.size);
        static constexpr name n{s.buf, s.len, s.hash, name_kind::enum_value_name};
    };

    template <auto EnumValue>
    struct enum_value_name_impl<EnumValue, false, enum_value_processing_requirements::strip_type_prefix_and_space_before_template_closing_bracket>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = g<Enum, EnumValue>();
        static constexpr stripped<x.size> s = strip_enum_type_prefix_and_space_before_template_closing_bracket<x.size>(x.begin, x.size, r<Enum>().value);
        static constexpr name n{s.buf, s.len, s.hash, name_kind::enum_value_name};
    };

    template <auto EnumValue>
    struct enum_value_name_impl<EnumValue, true, enum_value_processing_requirements::none>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = strip_enum_value_qualification(g<Enum, EnumValue>());
        static constexpr name n{x.begin, x.size, hash_sequence(x.begin, x.begin + x.size), name_kind::unqualified_enum_value_name};
    };

    template <auto EnumValue>
    struct enum_value_name_impl<EnumValue, true, enum_value_processing_requirements::copy_pretty_function_string>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = g<Enum, EnumValue>();
        static constexpr stripped<x.size> s = strip_enum_value_qualification_to_buffer<x.size>(x.begin, x.size);
        static constexpr name n{s.buf, s.len, s.hash, name_kind::unqualified_enum_value_name};
    };
}

template <auto EnumValue>
constexpr name const & enum_value_name() noexcept
{
    static_assert(std::is_enum_v<decltype(EnumValue)>);
    constexpr auto s = std::is_convertible_v<decltype(EnumValue), int>
        ? d::pf_traits::unscoped_enum_value_processing
        : d::pf_traits::scoped_enum_value_processing;
    return d::enum_value_name_impl<EnumValue, false, s>::n;
}

template <auto EnumValue>
constexpr name const & unqualified_enum_value_name() noexcept
{
    static_assert(std::is_enum_v<decltype(EnumValue)>);
    return d::enum_value_name_impl<EnumValue, true, d::pf_traits::unqualified_enum_value_processing>::n;
}

////////////////////////////////////////

namespace d
{
    template <class Enum, int I, class = void>
    struct enum_cast_sfinae
    {
        static constexpr Enum value = Enum{};
    };

    template <class Enum, int I>
    struct enum_cast_sfinae<Enum, I, std::void_t<std::integral_constant<Enum, static_cast<Enum>(I)>>>
    {
        static constexpr Enum value = static_cast<Enum>(I);
    };

    template <int I, int Max, bool Unqualify>
    struct enum_value_lookup
    {
        template <class Enum>
        static constexpr name const & find(Enum value)
        {
            if( static_cast<int>(value) == I )
            {
                constexpr auto s = Unqualify
                    ? pf_traits::unqualified_enum_value_processing
                    : std::is_convertible_v<Enum, int>
                        ? pf_traits::unscoped_enum_value_processing
                        : pf_traits::scoped_enum_value_processing;
                return enum_value_name_impl<enum_cast_sfinae<Enum, I>::value, Unqualify, s>::n;
            }
            return enum_value_lookup<I + 1, Max, Unqualify>::find(value);
        }
    };

    template <int Max, bool Unqualify>
    struct enum_value_lookup<Max, Max, Unqualify>
    {
        static constexpr name unknown_name{"*unknown*", 9, 11775755009147575841ull, name_kind::unknown};

        template <class Enum>
        static constexpr name const & find(Enum)
        {
            return unknown_name;
        }
    };
}

template <class Enum>
constexpr name const & enum_value_name(Enum value) noexcept
{
    return d::enum_value_lookup<enum_lookup_range<Enum>::min_value, enum_lookup_range<Enum>::max_value + 1, false>::find(value);
}

template <class Enum>
constexpr name const & unqualified_enum_value_name(Enum value) noexcept
{
    return d::enum_value_lookup<enum_lookup_range<Enum>::min_value, enum_lookup_range<Enum>::max_value + 1, true>::find(value);
}

}

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif

#endif // #ifndef BOOST_REFLECTO_ENUM_VALUE_NAME_HPP_INCLUDED
