#ifndef BOOST_REFLECTO_NAME_HPP_INCLUDED
#define BOOST_REFLECTO_NAME_HPP_INCLUDED

// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/reflecto/config.hpp>
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
