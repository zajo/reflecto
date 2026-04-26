// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_REFLECTO_TEST_SINGLE_HEADER
#   include "reflecto.hpp"
#else
#   include <boost/reflecto/scope_traits.hpp>
#endif

#include "test_helpers.hpp"
#include <type_traits>

using namespace boost::reflecto;


struct global_a;
struct global_b;


namespace ns_a
{
    struct a_type1;
    struct a_type2;

    namespace ns_b
    {
        struct b_type1;
        struct b_type2;

        namespace ns_c
        {
            struct c_type;
        }
    }
}


namespace ns_other
{
    struct other_type;
}


int main()
{
    CHECK((std::is_base_of_v<std::true_type, same_scope<ns_a::a_type1, ns_a::a_type2>>));
    CHECK((std::is_base_of_v<std::false_type, same_scope<ns_a::a_type1, ns_a::ns_b::b_type1>>));

    CHECK((same_scope_v<ns_a::a_type1, ns_a::a_type2>));
    CHECK((!same_scope_v<ns_a::a_type1, ns_a::ns_b::b_type1>));
    CHECK((same_scope_v<ns_a::ns_b::b_type1, ns_a::ns_b::b_type2>));
    CHECK((!same_scope_v<ns_a::ns_b::b_type1, ns_a::ns_b::ns_c::c_type>));
    CHECK((!same_scope_v<ns_a::a_type1, ns_other::other_type>));

    CHECK((same_scope_v<global_a, global_b>));
    CHECK((same_scope_v<global_a, int>));
    CHECK((!same_scope_v<global_a, ns_a::a_type1>));

    CHECK((same_scope_v<int, long>));

    CHECK((std::is_base_of_v<std::true_type, in_scope_of<ns_a::a_type1, ns_a::a_type2>>));
    CHECK((std::is_base_of_v<std::false_type, in_scope_of<ns_a::a_type1, ns_other::other_type>>));

    CHECK((in_scope_of_v<ns_a::a_type1, ns_a::a_type2>));
    CHECK((in_scope_of_v<ns_a::ns_b::b_type1, ns_a::a_type1>));
    CHECK((in_scope_of_v<ns_a::ns_b::ns_c::c_type, ns_a::a_type1>));
    CHECK((in_scope_of_v<ns_a::ns_b::ns_c::c_type, ns_a::ns_b::b_type1>));

    CHECK((!in_scope_of_v<ns_a::a_type1, ns_a::ns_b::b_type1>));
    CHECK((!in_scope_of_v<ns_a::a_type1, ns_other::other_type>));
    CHECK((!in_scope_of_v<ns_other::other_type, ns_a::a_type1>));

    CHECK((in_scope_of_v<global_a, global_b>));
    CHECK((in_scope_of_v<ns_a::a_type1, global_a>));
    CHECK((in_scope_of_v<ns_a::ns_b::ns_c::c_type, global_a>));
    CHECK((in_scope_of_v<int, global_a>));
    CHECK((!in_scope_of_v<global_a, ns_a::a_type1>));

    return errcount;
}
