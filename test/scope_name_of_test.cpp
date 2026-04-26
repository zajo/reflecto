// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_REFLECTO_TEST_SINGLE_HEADER
#   include "reflecto.hpp"
#else
#   include <boost/reflecto/scope_name_of.hpp>
#endif

#include "test_helpers.hpp"

using namespace boost::reflecto;

namespace test_ns
{
    class class_ {};

    namespace inner
    {
        struct struct_ {};
    }

    template <class> struct tmpl {};
}

class global_ {};
template <class> struct global_tmpl {};

int main()
{
    CHECK_NAME(scope_name_of<test_ns::class_>(), "test_ns");
    CHECK_NAME(scope_name_of<test_ns::inner::struct_>(), "test_ns::inner");
    CHECK_NAME(scope_name_of<test_ns::tmpl<int>>(), "test_ns");
    CHECK_NAME(scope_name_of<test_ns::tmpl<test_ns::class_>>(), "test_ns");

    CHECK(scope_name_of<test_ns::class_>().kind() == name_kind::scope_name);
    CHECK(scope_name_of<test_ns::inner::struct_>().kind() == name_kind::scope_name);

    CHECK(scope_name_of<int>().kind() == name_kind::empty);
    CHECK(scope_name_of<int>().empty());
    CHECK(scope_name_of<global_>().kind() == name_kind::empty);
    CHECK(scope_name_of<global_>().empty());
    CHECK(scope_name_of<global_tmpl<int>>().kind() == name_kind::empty);
    CHECK(scope_name_of<global_tmpl<int>>().empty());

    CHECK_NAME(scope_name_of<boost::reflecto::name>(), "boost::reflecto");

    return errcount;
}
