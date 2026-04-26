// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_REFLECTO_TEST_SINGLE_HEADER
#   include "reflecto.hpp"
#else
#   include <boost/reflecto/name.hpp>
#endif

#include "test_helpers.hpp"

using namespace boost::reflecto;

int main()
{
    TEST_CONSTEXPR name empty_name;

    CHECK(empty_name.empty());
    CHECK(empty_name.kind() == name_kind::empty);
    CHECK(empty_name.size() == 0);
    CHECK(empty_name.hash() == 14695981039346656037ull);

    ////////////////////////////////////////

    TEST_CONSTEXPR name a("hello", 5, 100, name_kind::type_name);
    TEST_CONSTEXPR name b("world", 5, 200, name_kind::type_name);
    TEST_CONSTEXPR name c("hello", 5, 100, name_kind::value_name);

    CHECK(!a.empty());
    CHECK(a.kind() == name_kind::type_name);
    CHECK(a.size() == 5);
    CHECK(a.hash() == 100);

    CHECK(!b.empty());
    CHECK(b.kind() == name_kind::type_name);
    CHECK(b.size() == 5);
    CHECK(b.hash() == 200);

    CHECK(a == c);
    CHECK(!(a != c));
    CHECK(a != b);
    CHECK(!(a == b));

    ////////////////////////////////////////

    return errcount;
}
