#ifndef BOOST_REFLECTO_SCOPE_NAME_OF_HPP_INCLUDED
#define BOOST_REFLECTO_SCOPE_NAME_OF_HPP_INCLUDED

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
