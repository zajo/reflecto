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
    unknown,
    type_name,
    enum_name,
    enum_value_name,
    unqualified_enum_value_name
};

constexpr char const * to_string(name_kind kind) noexcept
{
    switch( kind )
    {
    case name_kind::empty:
        return "empty";
    case name_kind::unknown:
        return "unknown";
    case name_kind::type_name:
        return "type_name";
    case name_kind::enum_name:
        return "enum_name";
    case name_kind::enum_value_name:
        return "enum_value_name";
    case name_kind::unqualified_enum_value_name:
        return "unqualified_enum_value_name";
    }
    return nullptr;
}

////////////////////////////////////////

class name:
    public std::string_view
{
    name(name const &) = delete;
    name & operator=(name const &) = delete;

    std::uint64_t hash_;
    name_kind kind_;

public:

    constexpr name() noexcept:
        std::string_view(),
        hash_(0),
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

}

#endif // #ifndef BOOST_REFLECTO_NAME_HPP_INCLUDED
