// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_REFLECTO_TEST_SINGLE_HEADER
#   include "reflecto.hpp"
#else
#   include <boost/reflecto/meta_specialization.hpp>
#endif

#include "test_helpers.hpp"
#include <type_traits>

using namespace boost::reflecto;

////////////////////////////////////////

template <meta_key>
struct test_setting: unspecialized
{
    static constexpr int value = 0;
};

////////////////////////////////////////

struct global_type;

namespace ns_a
{
    struct this_namespace;
    struct a_type;

    namespace ns_b
    {
        struct this_namespace;
        struct b_type;
        struct b_type2;

        namespace ns_c
        {
            struct this_namespace;
            struct c_type;
        }
    }
}

namespace ns_other
{
    struct this_namespace;
    struct other_type;
}

////////////////////////////////////////

template <>
struct test_setting<specialize_for_namespace<ns_a::this_namespace>>
{
    static constexpr int value = 10;
};

template <>
struct test_setting<specialize_for_namespace<ns_a::ns_b::ns_c::this_namespace>>
{
    static constexpr int value = 30;
};

template <>
struct test_setting<specialize_for_type<ns_a::ns_b::b_type>>
{
    static constexpr int value = 20;
};

////////////////////////////////////////

template <meta_key>
struct test_setting2: unspecialized
{
    static constexpr int value = -1;
};

template <>
struct test_setting2<specialize_for_namespace<ns_other::this_namespace>>
{
    static constexpr int value = 99;
};

////////////////////////////////////////

template <meta_key, class, class>
struct multi_setting: unspecialized
{
    static constexpr int value = 0;
};

template <class T, class U>
struct multi_setting<specialize_for_namespace<ns_a::this_namespace>, T, U>
{
    static constexpr int value = 10;
};

template <class T, class U>
struct multi_setting<specialize_for_type<ns_a::ns_b::b_type>, T, U>
{
    static constexpr int value = 20;
};

////////////////////////////////////////

int main()
{
    CHECK((meta_select_t<test_setting, global_type>::value == 0));
    CHECK((std::is_base_of_v<unspecialized, meta_select_t<test_setting, global_type>>));

    CHECK((meta_select_t<test_setting, ns_a::a_type>::value == 10));
    CHECK((!std::is_base_of_v<unspecialized, meta_select_t<test_setting, ns_a::a_type>>));

    CHECK((meta_select_t<test_setting, ns_a::ns_b::b_type>::value == 20));
    CHECK((!std::is_base_of_v<unspecialized, meta_select_t<test_setting, ns_a::ns_b::b_type>>));

    CHECK((meta_select_t<test_setting, ns_a::ns_b::b_type2>::value == 10));

    CHECK((meta_select_t<test_setting, ns_a::ns_b::ns_c::c_type>::value == 30));

    CHECK((meta_select_t<test_setting, ns_other::other_type>::value == 0));
    CHECK((std::is_base_of_v<unspecialized, meta_select_t<test_setting, ns_other::other_type>>));

    ////////////////////////////////////////

    CHECK((meta_select_t<test_setting2, global_type>::value == -1));
    CHECK((meta_select_t<test_setting2, ns_a::a_type>::value == -1));
    CHECK((meta_select_t<test_setting2, ns_other::other_type>::value == 99));

    ////////////////////////////////////////

    CHECK((meta_select_t<multi_setting, global_type, int, float>::value == 0));
    CHECK((std::is_base_of_v<unspecialized, meta_select_t<multi_setting, global_type, int, float>>));

    CHECK((meta_select_t<multi_setting, ns_a::a_type, int, float>::value == 10));
    CHECK((!std::is_base_of_v<unspecialized, meta_select_t<multi_setting, ns_a::a_type, int, float>>));

    CHECK((meta_select_t<multi_setting, ns_a::ns_b::b_type, int, float>::value == 20));
    CHECK((!std::is_base_of_v<unspecialized, meta_select_t<multi_setting, ns_a::ns_b::b_type, int, float>>));

    CHECK((meta_select_t<multi_setting, ns_a::ns_b::b_type2, int, float>::value == 10));

    CHECK((meta_select_t<multi_setting, ns_a::ns_b::ns_c::c_type, int, float>::value == 10));

    CHECK((meta_select_t<multi_setting, ns_other::other_type, int, float>::value == 0));
    CHECK((std::is_base_of_v<unspecialized, meta_select_t<multi_setting, ns_other::other_type, int, float>>));

    ////////////////////////////////////////

    return errcount;
}
