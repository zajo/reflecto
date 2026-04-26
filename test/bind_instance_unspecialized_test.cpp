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
}


namespace ns_other
{
    struct this_namespace;

    struct other_type;
}


template <class>
struct setting: unspecialized
{
    static constexpr int value = -1;
};

template <>
struct setting<within_scope_of<ns_other::this_namespace>>
{
    static constexpr int value = 99;
};


int main()
{
    CHECK((bind_instance<setting<resolve_for<global_type>>>::value == -1));
    CHECK((bind_instance<setting<resolve_for<ns_a::a_type>>>::value == -1));
    CHECK((bind_instance<setting<resolve_for<ns_other::other_type>>>::value == 99));

    return errcount;
}
