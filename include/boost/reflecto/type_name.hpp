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
