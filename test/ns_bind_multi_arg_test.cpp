// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_REFLECTO_TEST_SINGLE_HEADER
#   include "reflecto.hpp"
#else
#   include <boost/reflecto/ns_bind.hpp>
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

        struct b_type1;
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


template <class, class, class>
struct setting: unspecialized
{
    static constexpr int value = 0;
};

template <class T, class U>
struct setting<in_namespace<ns_a::this_namespace>, T, U>
{
    static constexpr int value = 10;
};

template <class T, class U>
struct setting<ns_a::ns_b::b_type1, T, U>
{
    static constexpr int value = 20;
};


int main()
{
    CHECK((ns_bind<setting<resolve_for<global_type>, int, float>>::value == 0));
    CHECK((std::is_base_of_v<unspecialized, ns_bind<setting<resolve_for<global_type>, int, float>>>));

    CHECK((ns_bind<setting<resolve_for<ns_a::a_type>, int, float>>::value == 10));
    CHECK((!std::is_base_of_v<unspecialized, ns_bind<setting<resolve_for<ns_a::a_type>, int, float>>>));

    CHECK((ns_bind<setting<resolve_for<ns_a::ns_b::b_type1>, int, float>>::value == 20));
    CHECK((!std::is_base_of_v<unspecialized, ns_bind<setting<resolve_for<ns_a::ns_b::b_type1>, int, float>>>));

    CHECK((ns_bind<setting<resolve_for<ns_a::ns_b::b_type2>, int, float>>::value == 10));

    CHECK((ns_bind<setting<resolve_for<ns_a::ns_b::ns_c::c_type>, int, float>>::value == 10));

    CHECK((ns_bind<setting<resolve_for<ns_other::other_type>, int, float>>::value == 0));
    CHECK((std::is_base_of_v<unspecialized, ns_bind<setting<resolve_for<ns_other::other_type>, int, float>>>));

    return errcount;
}
