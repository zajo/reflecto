// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_REFLECTO_TEST_SINGLE_HEADER
#   include "reflecto.hpp"
#else
#   include <boost/reflecto/enum_value_name.hpp>
#endif

#include "test_helpers.hpp"

using namespace boost::reflecto;

namespace test_ns
{
    enum class enum1 { value1 = 0, value2 = 1, value0 = 2 };
    enum class enum2 { y = 10, x = 20 };
    enum enum3 { enum3_value2 = 0, enum3_value0 = 1, enum3_value1 = 2 };
}

enum class global_enum1 { c = 0, a = 1, b = 2 };

enum class partial_enum { b = 0, a = 1, c = 2 };

enum class shuffled { z = 0, a = 1, m = 2 };

template <>
struct boost::reflecto::enum_lookup_range<partial_enum>
{
    static constexpr int min_value = 0;
    static constexpr int max_value = 1;
};

#if defined(__clang__) && __clang_major__ >= 15 && __clang_major__ < 20
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wenum-constexpr-conversion"
#endif

template <class Enum, int I, bool = d::check_enum_cast_sfinae<Enum, I>::value>
struct check_unnamed_invariants
{
    static constexpr bool value = true;
};

template <class Enum, int I>
struct check_unnamed_invariants<Enum, I, true>
{
    static constexpr bool value =
        enum_value_name<static_cast<Enum>(I)>().kind() == name_kind::unnamed_enum_value
        && !enum_value_name<static_cast<Enum>(I)>().empty()
        && unqualified_enum_value_name<static_cast<Enum>(I)>().kind() == name_kind::unnamed_enum_value
        && !unqualified_enum_value_name<static_cast<Enum>(I)>().empty()
        && enum_value_name(static_cast<Enum>(I)).kind() == name_kind::unnamed_enum_value
        && unqualified_enum_value_name(static_cast<Enum>(I)).kind() == name_kind::unnamed_enum_value;
};

#if defined(__clang__) && __clang_major__ >= 15 && __clang_major__ < 20
#   pragma clang diagnostic pop
#endif

int main()
{
    CHECK((check_unnamed_invariants<test_ns::enum1, 42>::value));
    CHECK((check_unnamed_invariants<test_ns::enum2, 42>::value));
    CHECK((check_unnamed_invariants<test_ns::enum3, 42>::value));

    CHECK(enum_value_name(static_cast<test_ns::enum1>(200)).kind() == name_kind::enum_value_out_of_lookup_range);

    ////////////////////////////////////////

    CHECK(named_enum_value_count<test_ns::enum1>() == 3);
    CHECK(named_enum_value_count<test_ns::enum2>() == 2);
    CHECK(named_enum_value_count<test_ns::enum3>() == 3);
    CHECK(named_enum_value_count<global_enum1>() == 3);
    CHECK(named_enum_value_count<partial_enum>() == 2);

    ////////////////////////////////////////

    CHECK(min_named_enum_value<test_ns::enum1>() == test_ns::enum1::value1);
    CHECK(max_named_enum_value<test_ns::enum1>() == test_ns::enum1::value0);
    CHECK(min_named_enum_value<test_ns::enum2>() == test_ns::enum2::y);
    CHECK(max_named_enum_value<test_ns::enum2>() == test_ns::enum2::x);
    CHECK(min_named_enum_value<global_enum1>() == global_enum1::c);
    CHECK(max_named_enum_value<global_enum1>() == global_enum1::b);
    CHECK(min_named_enum_value<shuffled>() == shuffled::z);
    CHECK(max_named_enum_value<shuffled>() == shuffled::m);
    CHECK(min_named_enum_value<partial_enum>() == partial_enum::b);
    CHECK(max_named_enum_value<partial_enum>() == partial_enum::a);

    ////////////////////////////////////////

    TEST_CONSTEXPR name const (&v1)[3] = enum_value_names<test_ns::enum1>();
    CHECK_NAME(v1[0], "test_ns::enum1::value1");
    CHECK_NAME(v1[1], "test_ns::enum1::value2");
    CHECK_NAME(v1[2], "test_ns::enum1::value0");

    TEST_CONSTEXPR name const (&v2)[2] = enum_value_names<test_ns::enum2>();
    CHECK_NAME(v2[0], "test_ns::enum2::y");
    CHECK_NAME(v2[1], "test_ns::enum2::x");

    TEST_CONSTEXPR name const (&v3)[3] = enum_value_names<test_ns::enum3>();
    CHECK_NAME(v3[0], "test_ns::enum3_value2");
    CHECK_NAME(v3[1], "test_ns::enum3_value0");
    CHECK_NAME(v3[2], "test_ns::enum3_value1");

    TEST_CONSTEXPR name const (&v4)[3] = enum_value_names<global_enum1>();
    CHECK_NAME(v4[0], "global_enum1::c");
    CHECK_NAME(v4[1], "global_enum1::a");
    CHECK_NAME(v4[2], "global_enum1::b");

    TEST_CONSTEXPR name const (&v5)[2] = enum_value_names<partial_enum>();
    CHECK_NAME(v5[0], "partial_enum::b");
    CHECK_NAME(v5[1], "partial_enum::a");

    ////////////////////////////////////////

    TEST_CONSTEXPR name const (&uv1)[3] = unqualified_enum_value_names<test_ns::enum1>();
    CHECK_NAME(uv1[0], "value1");
    CHECK_NAME(uv1[1], "value2");
    CHECK_NAME(uv1[2], "value0");

    TEST_CONSTEXPR name const (&uv2)[2] = unqualified_enum_value_names<test_ns::enum2>();
    CHECK_NAME(uv2[0], "y");
    CHECK_NAME(uv2[1], "x");

    TEST_CONSTEXPR name const (&uv3)[3] = unqualified_enum_value_names<global_enum1>();
    CHECK_NAME(uv3[0], "c");
    CHECK_NAME(uv3[1], "a");
    CHECK_NAME(uv3[2], "b");

    ////////////////////////////////////////

    TEST_CONSTEXPR name const (&sv1)[3] = sorted_enum_value_names<test_ns::enum1>();
    CHECK_NAME(sv1[0], "test_ns::enum1::value0");
    CHECK_NAME(sv1[1], "test_ns::enum1::value1");
    CHECK_NAME(sv1[2], "test_ns::enum1::value2");

    TEST_CONSTEXPR name const (&sv2)[3] = sorted_enum_value_names<shuffled>();
    CHECK_NAME(sv2[0], "shuffled::a");
    CHECK_NAME(sv2[1], "shuffled::m");
    CHECK_NAME(sv2[2], "shuffled::z");

    TEST_CONSTEXPR name const (&suv1)[3] = sorted_unqualified_enum_value_names<test_ns::enum1>();
    CHECK_NAME(suv1[0], "value0");
    CHECK_NAME(suv1[1], "value1");
    CHECK_NAME(suv1[2], "value2");

    TEST_CONSTEXPR name const (&suv2)[3] = sorted_unqualified_enum_value_names<shuffled>();
    CHECK_NAME(suv2[0], "a");
    CHECK_NAME(suv2[1], "m");
    CHECK_NAME(suv2[2], "z");

    ////////////////////////////////////////

    return errcount;
}
