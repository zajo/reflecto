// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_REFLECTO_TEST_SINGLE_HEADER
#   include "reflecto.hpp"
#else
#   include <boost/reflecto/value_name.hpp>
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

enum class range_test_enum { b = 0, a = 1, c = 2 };

enum class shuffled { z = 0, a = 1, m = 2 };

namespace boost::reflecto {
template <>
struct enum_lookup_range<range_test_enum>
{
    static constexpr int min_value = 0;
    static constexpr int max_value = 1;
};
}

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
        value_name<static_cast<Enum>(I)>().kind() == name_kind::unnamed_value
        && !value_name<static_cast<Enum>(I)>().empty()
        && short_value_name<static_cast<Enum>(I)>().kind() == name_kind::unnamed_value
        && !short_value_name<static_cast<Enum>(I)>().empty()
        && value_name(static_cast<Enum>(I)).kind() == name_kind::unnamed_value
        && short_value_name(static_cast<Enum>(I)).kind() == name_kind::unnamed_value;
};

#if defined(__clang__) && __clang_major__ >= 15 && __clang_major__ < 20
#   pragma clang diagnostic pop
#endif

int main()
{
    CHECK((check_unnamed_invariants<test_ns::enum1, 42>::value));
    CHECK((check_unnamed_invariants<test_ns::enum2, 42>::value));
    CHECK((check_unnamed_invariants<test_ns::enum3, 42>::value));

    CHECK(value_name(static_cast<test_ns::enum1>(200)).kind() == name_kind::value_out_of_lookup_range);

    ////////////////////////////////////////

    CHECK(named_value_count<test_ns::enum1>() == 3);
    CHECK(named_value_count<test_ns::enum2>() == 2);
    CHECK(named_value_count<test_ns::enum3>() == 3);
    CHECK(named_value_count<global_enum1>() == 3);
    CHECK(named_value_count<range_test_enum>() == 2);

    ////////////////////////////////////////

    CHECK(min_named_value<test_ns::enum1>() == test_ns::enum1::value1);
    CHECK(max_named_value<test_ns::enum1>() == test_ns::enum1::value0);
    CHECK(min_named_value<test_ns::enum2>() == test_ns::enum2::y);
    CHECK(max_named_value<test_ns::enum2>() == test_ns::enum2::x);
    CHECK(min_named_value<global_enum1>() == global_enum1::c);
    CHECK(max_named_value<global_enum1>() == global_enum1::b);
    CHECK(min_named_value<shuffled>() == shuffled::z);
    CHECK(max_named_value<shuffled>() == shuffled::m);
    CHECK(min_named_value<range_test_enum>() == range_test_enum::b);
    CHECK(max_named_value<range_test_enum>() == range_test_enum::a);

    ////////////////////////////////////////

    TEST_CONSTEXPR enumerator const (&en1)[3] = named_values<test_ns::enum1>();
    CHECK_NAME(en1[0].value_name, "test_ns::enum1::value1");
    CHECK(en1[0].value == 0);
    CHECK_NAME(en1[1].value_name, "test_ns::enum1::value2");
    CHECK(en1[1].value == 1);
    CHECK_NAME(en1[2].value_name, "test_ns::enum1::value0");
    CHECK(en1[2].value == 2);

    TEST_CONSTEXPR enumerator const (&en2)[2] = named_values<test_ns::enum2>();
    CHECK_NAME(en2[0].value_name, "test_ns::enum2::y");
    CHECK(en2[0].value == 10);
    CHECK_NAME(en2[1].value_name, "test_ns::enum2::x");
    CHECK(en2[1].value == 20);

    TEST_CONSTEXPR enumerator const (&en3)[3] = named_values<test_ns::enum3>();
    CHECK_NAME(en3[0].value_name, "test_ns::enum3_value2");
    CHECK(en3[0].value == 0);
    CHECK_NAME(en3[1].value_name, "test_ns::enum3_value0");
    CHECK(en3[1].value == 1);
    CHECK_NAME(en3[2].value_name, "test_ns::enum3_value1");
    CHECK(en3[2].value == 2);

    TEST_CONSTEXPR enumerator const (&en4)[3] = named_values<global_enum1>();
    CHECK_NAME(en4[0].value_name, "global_enum1::c");
    CHECK(en4[0].value == 0);
    CHECK_NAME(en4[1].value_name, "global_enum1::a");
    CHECK(en4[1].value == 1);
    CHECK_NAME(en4[2].value_name, "global_enum1::b");
    CHECK(en4[2].value == 2);

    TEST_CONSTEXPR enumerator const (&en5)[2] = named_values<range_test_enum>();
    CHECK_NAME(en5[0].value_name, "range_test_enum::b");
    CHECK(en5[0].value == 0);
    CHECK_NAME(en5[1].value_name, "range_test_enum::a");
    CHECK(en5[1].value == 1);

    ////////////////////////////////////////

    TEST_CONSTEXPR enumerator const (&uen1)[3] = short_named_values<test_ns::enum1>();
    CHECK_NAME(uen1[0].value_name, "value1");
    CHECK(uen1[0].value == 0);
    CHECK_NAME(uen1[1].value_name, "value2");
    CHECK(uen1[1].value == 1);
    CHECK_NAME(uen1[2].value_name, "value0");
    CHECK(uen1[2].value == 2);

    TEST_CONSTEXPR enumerator const (&uen2)[2] = short_named_values<test_ns::enum2>();
    CHECK_NAME(uen2[0].value_name, "y");
    CHECK(uen2[0].value == 10);
    CHECK_NAME(uen2[1].value_name, "x");
    CHECK(uen2[1].value == 20);

    TEST_CONSTEXPR enumerator const (&uen3)[3] = short_named_values<global_enum1>();
    CHECK_NAME(uen3[0].value_name, "c");
    CHECK(uen3[0].value == 0);
    CHECK_NAME(uen3[1].value_name, "a");
    CHECK(uen3[1].value == 1);
    CHECK_NAME(uen3[2].value_name, "b");
    CHECK(uen3[2].value == 2);

    ////////////////////////////////////////

    TEST_CONSTEXPR enumerator const (&sen1)[3] = sorted_named_values<test_ns::enum1>();
    CHECK_NAME(sen1[0].value_name, "test_ns::enum1::value0");
    CHECK_NAME(sen1[1].value_name, "test_ns::enum1::value1");
    CHECK_NAME(sen1[2].value_name, "test_ns::enum1::value2");

    TEST_CONSTEXPR enumerator const (&sen2)[3] = sorted_named_values<shuffled>();
    CHECK_NAME(sen2[0].value_name, "shuffled::a");
    CHECK_NAME(sen2[1].value_name, "shuffled::m");
    CHECK_NAME(sen2[2].value_name, "shuffled::z");

    TEST_CONSTEXPR enumerator const (&suen1)[3] = sorted_short_named_values<test_ns::enum1>();
    CHECK_NAME(suen1[0].value_name, "value0");
    CHECK_NAME(suen1[1].value_name, "value1");
    CHECK_NAME(suen1[2].value_name, "value2");

    TEST_CONSTEXPR enumerator const (&suen2)[3] = sorted_short_named_values<shuffled>();
    CHECK_NAME(suen2[0].value_name, "a");
    CHECK_NAME(suen2[1].value_name, "m");
    CHECK_NAME(suen2[2].value_name, "z");

    ////////////////////////////////////////

    return errcount;
}
