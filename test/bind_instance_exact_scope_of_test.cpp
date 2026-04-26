// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_REFLECTO_TEST_SINGLE_HEADER
#   include "reflecto.hpp"
#else
#   include <boost/reflecto/bind_instance.hpp>
#endif

#include "test_helpers.hpp"
#include <type_traits>

using namespace boost::reflecto;


struct global_type;


namespace ns_a
{
    struct this_namespace;

    struct a_type;

    namespace ns_b
    {
        struct this_namespace;

        struct b_type;
    }
}


namespace ns_other
{
    struct this_namespace;

    struct other_type;
}


template <class>
struct setting: unspecialized
{
    static constexpr int value = 0;
};

template <>
struct setting<exact_scope_of<ns_a::this_namespace>>
{
    static constexpr int value = 10;
};

template <>
struct setting<exact_scope_of<ns_a::ns_b::this_namespace>>
{
    static constexpr int value = 20;
};

template <>
struct setting<exact_scope_of<global_type>>
{
    static constexpr int value = 99;
};


int main()
{
    CHECK((bind_instance<setting<resolve_for<ns_a::a_type>>>::value == 10));
    CHECK((!std::is_base_of_v<unspecialized, bind_instance<setting<resolve_for<ns_a::a_type>>>>));

    CHECK((bind_instance<setting<resolve_for<ns_a::ns_b::b_type>>>::value == 20));
    CHECK((!std::is_base_of_v<unspecialized, bind_instance<setting<resolve_for<ns_a::ns_b::b_type>>>>));

    CHECK((bind_instance<setting<resolve_for<ns_other::other_type>>>::value == 0));
    CHECK((std::is_base_of_v<unspecialized, bind_instance<setting<resolve_for<ns_other::other_type>>>>));

    CHECK((bind_instance<setting<resolve_for<global_type>>>::value == 99));
    CHECK((!std::is_base_of_v<unspecialized, bind_instance<setting<resolve_for<global_type>>>>));

    CHECK((bind_instance<setting<resolve_for<int>>>::value == 99));

    return errcount;
}
