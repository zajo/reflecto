#ifndef BOOST_REFLECTO_TYPE_NAME_HPP_INCLUDED
#define BOOST_REFLECTO_TYPE_NAME_HPP_INCLUDED

// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/reflecto/config.hpp>
#include <boost/reflecto/detail/pretty_function_traits.hpp>
#include <boost/reflecto/name.hpp>

namespace boost::reflecto {

namespace d
{
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
}

template <class T>
constexpr name const & type_name() noexcept
{
    return d::type_name_<T, d::pf_traits::type_processing>::n;
}

}

#endif // #ifndef BOOST_REFLECTO_TYPE_NAME_HPP_INCLUDED
