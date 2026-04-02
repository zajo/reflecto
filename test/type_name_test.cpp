// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_REFLECTO_TEST_SINGLE_HEADER
#   include "reflecto.hpp"
#else
#   include <boost/reflecto/type_name.hpp>
#endif

#include "test_helpers.hpp"

using namespace boost::reflecto;

namespace test_ns
{
    class class_ { };
    struct struct_ { };
    enum enum_ { };
    template <int> class class_template1 { };
    template <int> struct struct_template1 { };
    template <class> class class_template2 { };
    template <class> struct struct_template2 { };
}

namespace boost::reflecto {
    struct in_namespace_boost_reflecto { };
}

class class_ { };
struct struct_ { };
enum enum_ { };
template <int> class class_template1 { };
template <int> struct struct_template1 { };
template <class> class class_template2 { };
template <class> struct struct_template2 { };

int main()
{
    CHECK_TYPE_NAME(int, "int");

    ////////////////////////////////////////

    CHECK_TYPE_NAME(test_ns::class_, "test_ns::class_");
    CHECK_TYPE_NAME(test_ns::struct_, "test_ns::struct_");
    CHECK_TYPE_NAME(test_ns::enum_, "test_ns::enum_");
    CHECK_TYPE_NAME(test_ns::class_template1<42>, "test_ns::class_template1<42>");
    CHECK_TYPE_NAME(test_ns::struct_template1<42>, "test_ns::struct_template1<42>");
    CHECK_TYPE_NAME(test_ns::class_template2<int>, "test_ns::class_template2<int>");
    CHECK_TYPE_NAME(test_ns::struct_template2<int>, "test_ns::struct_template2<int>");
    CHECK_TYPE_NAME(test_ns::class_template2<test_ns::class_>, "test_ns::class_template2<test_ns::class_>");
    CHECK_TYPE_NAME(test_ns::class_template2<test_ns::struct_>, "test_ns::class_template2<test_ns::struct_>");
    CHECK_TYPE_NAME(test_ns::class_template2<test_ns::enum_>, "test_ns::class_template2<test_ns::enum_>");
    CHECK_TYPE_NAME(test_ns::struct_template2<test_ns::class_>, "test_ns::struct_template2<test_ns::class_>");
    CHECK_TYPE_NAME(test_ns::struct_template2<test_ns::struct_>, "test_ns::struct_template2<test_ns::struct_>");
    CHECK_TYPE_NAME(test_ns::struct_template2<test_ns::enum_>, "test_ns::struct_template2<test_ns::enum_>");

    ////////////////////////////////////////

    CHECK_TYPE_NAME(class_, "class_");
    CHECK_TYPE_NAME(struct_, "struct_");
    CHECK_TYPE_NAME(enum_, "enum_");
    CHECK_TYPE_NAME(class_template1<42>, "class_template1<42>");
    CHECK_TYPE_NAME(struct_template1<42>, "struct_template1<42>");
    CHECK_TYPE_NAME(class_template2<int>, "class_template2<int>");
    CHECK_TYPE_NAME(struct_template2<int>, "struct_template2<int>");
    CHECK_TYPE_NAME(class_template2<class_>, "class_template2<class_>");
    CHECK_TYPE_NAME(class_template2<struct_>, "class_template2<struct_>");
    CHECK_TYPE_NAME(class_template2<enum_>, "class_template2<enum_>");
    CHECK_TYPE_NAME(struct_template2<class_>, "struct_template2<class_>");
    CHECK_TYPE_NAME(struct_template2<struct_>, "struct_template2<struct_>");
    CHECK_TYPE_NAME(struct_template2<enum_>, "struct_template2<enum_>");

    ////////////////////////////////////////

    CHECK_TYPE_NAME(test_ns::class_template2<test_ns::struct_template2<test_ns::class_>>, "test_ns::class_template2<test_ns::struct_template2<test_ns::class_>>");

    CHECK_TYPE_NAME(boost::reflecto::in_namespace_boost_reflecto, "boost::reflecto::in_namespace_boost_reflecto");

    ////////////////////////////////////////

    return errcount;
}
