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
    enum class enum1 { value0, value1, value2 };
    enum class enum2 { x = 10, y = 20 };
    enum enum3 { enum3_value0, enum3_value1, enum3_value2 };
    enum enum4 { enum4_x = 10, enum4_y = 20 };
}

enum class global_enum1 { a, b, c };
enum global_enum2 { global_enum2_a, global_enum2_b, global_enum2_c };

enum class range_test_enum { a, b, c };

namespace boost::reflecto {
template <>
struct enum_lookup_range<specialize_for_type<range_test_enum>>
{
    static constexpr int min_value = 0;
    static constexpr int max_value = 1;
};
}

int main()
{
    CHECK_VALUE_NAME(test_ns::enum1::value0, "test_ns::enum1::value0");
    CHECK_VALUE_NAME(test_ns::enum1::value1, "test_ns::enum1::value1");
    CHECK_VALUE_NAME(test_ns::enum1::value2, "test_ns::enum1::value2");

    CHECK_VALUE_NAME(test_ns::enum2::x, "test_ns::enum2::x");
    CHECK_VALUE_NAME(test_ns::enum2::y, "test_ns::enum2::y");

    CHECK_VALUE_NAME(test_ns::enum3_value0, "test_ns::enum3_value0");
    CHECK_VALUE_NAME(test_ns::enum3_value1, "test_ns::enum3_value1");
    CHECK_VALUE_NAME(test_ns::enum3_value2, "test_ns::enum3_value2");

    CHECK_VALUE_NAME(test_ns::enum4_x, "test_ns::enum4_x");
    CHECK_VALUE_NAME(test_ns::enum4_y, "test_ns::enum4_y");

    CHECK_VALUE_NAME(global_enum1::a, "global_enum1::a");
    CHECK_VALUE_NAME(global_enum1::b, "global_enum1::b");
    CHECK_VALUE_NAME(global_enum1::c, "global_enum1::c");

    CHECK_VALUE_NAME(global_enum2_a, "global_enum2_a");
    CHECK_VALUE_NAME(global_enum2_b, "global_enum2_b");
    CHECK_VALUE_NAME(global_enum2_c, "global_enum2_c");

    ////////////////////////////////////////

    CHECK_NAME(value_name(test_ns::enum1::value0), "test_ns::enum1::value0");
    CHECK_NAME(value_name(test_ns::enum1::value1), "test_ns::enum1::value1");
    CHECK_NAME(value_name(test_ns::enum1::value2), "test_ns::enum1::value2");

    CHECK_NAME(value_name(test_ns::enum2::x), "test_ns::enum2::x");
    CHECK_NAME(value_name(test_ns::enum2::y), "test_ns::enum2::y");

    CHECK_NAME(value_name(test_ns::enum3_value0), "test_ns::enum3_value0");
    CHECK_NAME(value_name(test_ns::enum3_value1), "test_ns::enum3_value1");
    CHECK_NAME(value_name(test_ns::enum3_value2), "test_ns::enum3_value2");

    CHECK_NAME(value_name(test_ns::enum4_x), "test_ns::enum4_x");
    CHECK_NAME(value_name(test_ns::enum4_y), "test_ns::enum4_y");

    CHECK_NAME(value_name(global_enum1::a), "global_enum1::a");
    CHECK_NAME(value_name(global_enum1::b), "global_enum1::b");
    CHECK_NAME(value_name(global_enum1::c), "global_enum1::c");

    CHECK_NAME(value_name(global_enum2_a), "global_enum2_a");
    CHECK_NAME(value_name(global_enum2_b), "global_enum2_b");
    CHECK_NAME(value_name(global_enum2_c), "global_enum2_c");

    ////////////////////////////////////////

    CHECK_SHORT_VALUE_NAME(test_ns::enum1::value0, "value0");
    CHECK_SHORT_VALUE_NAME(test_ns::enum1::value1, "value1");
    CHECK_SHORT_VALUE_NAME(test_ns::enum1::value2, "value2");

    CHECK_SHORT_VALUE_NAME(test_ns::enum2::x, "x");
    CHECK_SHORT_VALUE_NAME(test_ns::enum2::y, "y");

    CHECK_SHORT_VALUE_NAME(test_ns::enum3_value0, "enum3_value0");
    CHECK_SHORT_VALUE_NAME(test_ns::enum3_value1, "enum3_value1");
    CHECK_SHORT_VALUE_NAME(test_ns::enum3_value2, "enum3_value2");

    CHECK_SHORT_VALUE_NAME(test_ns::enum4_x, "enum4_x");
    CHECK_SHORT_VALUE_NAME(test_ns::enum4_y, "enum4_y");

    CHECK_SHORT_VALUE_NAME(global_enum1::a, "a");
    CHECK_SHORT_VALUE_NAME(global_enum1::b, "b");
    CHECK_SHORT_VALUE_NAME(global_enum1::c, "c");

    CHECK_SHORT_VALUE_NAME(global_enum2_a, "global_enum2_a");
    CHECK_SHORT_VALUE_NAME(global_enum2_b, "global_enum2_b");
    CHECK_SHORT_VALUE_NAME(global_enum2_c, "global_enum2_c");

    ////////////////////////////////////////

    CHECK_NAME(short_value_name(test_ns::enum1::value0), "value0");
    CHECK_NAME(short_value_name(test_ns::enum1::value1), "value1");
    CHECK_NAME(short_value_name(test_ns::enum1::value2), "value2");

    CHECK_NAME(short_value_name(test_ns::enum2::x), "x");
    CHECK_NAME(short_value_name(test_ns::enum2::y), "y");

    CHECK_NAME(short_value_name(test_ns::enum3_value0), "enum3_value0");
    CHECK_NAME(short_value_name(test_ns::enum3_value1), "enum3_value1");
    CHECK_NAME(short_value_name(test_ns::enum3_value2), "enum3_value2");

    CHECK_NAME(short_value_name(test_ns::enum4_x), "enum4_x");
    CHECK_NAME(short_value_name(test_ns::enum4_y), "enum4_y");

    CHECK_NAME(short_value_name(global_enum1::a), "a");
    CHECK_NAME(short_value_name(global_enum1::b), "b");
    CHECK_NAME(short_value_name(global_enum1::c), "c");

    CHECK_NAME(short_value_name(global_enum2_a), "global_enum2_a");
    CHECK_NAME(short_value_name(global_enum2_b), "global_enum2_b");
    CHECK_NAME(short_value_name(global_enum2_c), "global_enum2_c");

    ////////////////////////////////////////

    CHECK_NAME(value_name(range_test_enum::a), "range_test_enum::a");
    CHECK_NAME(value_name(range_test_enum::b), "range_test_enum::b");
    CHECK_NAME(value_name(range_test_enum::c), "*unknown*");
    CHECK(value_name(range_test_enum::c).kind() == name_kind::value_out_of_lookup_range);

    ////////////////////////////////////////

    return errcount;
}
