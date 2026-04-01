// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_REFLECTO_TEST_SINGLE_HEADER
#   include "reflecto.hpp"
#else
#   include <boost/reflecto/name.hpp>
#endif

#include "test_helpers.hpp"

using boost::reflecto::name;
using boost::reflecto::name_kind;
using boost::reflecto::to_string;

////////////////////////////////////////

int main()
{
    TEST_CONSTEXPR name empty_name;

    CHECK(empty_name.empty());
    CHECK(empty_name.kind() == name_kind::empty);
    CHECK(empty_name.size() == 0);
    CHECK(empty_name.hash() == 0);

    ////////////////////////////////////////

    TEST_CONSTEXPR name a("hello", 5, 100, name_kind::type_name);
    TEST_CONSTEXPR name b("world", 5, 200, name_kind::enum_name);
    TEST_CONSTEXPR name c("hello", 5, 100, name_kind::enum_value_name);

    CHECK(!a.empty());
    CHECK(a.kind() == name_kind::type_name);
    CHECK(a.size() == 5);
    CHECK(a.hash() == 100);

    CHECK(!b.empty());
    CHECK(b.kind() == name_kind::enum_name);
    CHECK(b.size() == 5);
    CHECK(b.hash() == 200);

    CHECK(a == c);
    CHECK(!(a != c));
    CHECK(a != b);
    CHECK(!(a == b));

    ////////////////////////////////////////

    CHECK_STR(to_string(name_kind::empty), "empty");
    CHECK_STR(to_string(name_kind::unknown), "unknown");
    CHECK_STR(to_string(name_kind::type_name), "type_name");
    CHECK_STR(to_string(name_kind::enum_name), "enum_name");
    CHECK_STR(to_string(name_kind::enum_value_name), "enum_value_name");
    CHECK_STR(to_string(name_kind::unqualified_enum_value_name), "unqualified_enum_value_name");
    CHECK(to_string(static_cast<name_kind>(999)) == nullptr);

    ////////////////////////////////////////

    return errcount;
}
