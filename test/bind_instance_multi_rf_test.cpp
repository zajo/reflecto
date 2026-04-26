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

    struct other_type1;
    struct other_type2;
}

////////////////////////////////////////

template <class, class, class>
struct setting1: unspecialized
{
    static constexpr int value = 0;
};

template <class T>
struct setting1<within_scope_of<ns_a::this_namespace>, within_scope_of<ns_other::this_namespace>, T>
{
    static constexpr int value = 100;
};

template <class T>
struct setting1<within_scope_of<ns_a::this_namespace>, ns_other::other_type1, T>
{
    static constexpr int value = 200;
};

////////////////////////////////////////

template <class, class, class>
struct setting2: unspecialized
{
    static constexpr int value = 0;
};

template <class T>
struct setting2<within_scope_of<ns_other::this_namespace>, within_scope_of<ns_a::this_namespace>, T>
{
    static constexpr int value = 300;
};

////////////////////////////////////////

int main()
{
    CHECK((bind_instance<setting1<resolve_for<ns_a::a_type>, resolve_for<ns_other::other_type1>, int>>::value == 200));

    CHECK((bind_instance<setting1<resolve_for<ns_a::a_type>, resolve_for<ns_other::other_type2>, int>>::value == 100));

    CHECK((bind_instance<setting1<resolve_for<ns_a::a_type>, resolve_for<global_type>, int>>::value == 0));
    CHECK((std::is_base_of_v<unspecialized, bind_instance<setting1<resolve_for<ns_a::a_type>, resolve_for<global_type>, int>>>));

    CHECK((bind_instance<setting1<resolve_for<ns_other::other_type1>, resolve_for<ns_a::a_type>, int>>::value == 0));
    CHECK((std::is_base_of_v<unspecialized, bind_instance<setting1<resolve_for<ns_other::other_type1>, resolve_for<ns_a::a_type>, int>>>));

    ////////////////////////////////////////

    CHECK((bind_instance<setting2<resolve_for<ns_other::other_type1>, resolve_for<ns_a::a_type>, int>>::value == 300));

    CHECK((bind_instance<setting2<resolve_for<ns_a::a_type>, resolve_for<ns_other::other_type1>, int>>::value == 0));
    CHECK((std::is_base_of_v<unspecialized, bind_instance<setting2<resolve_for<ns_a::a_type>, resolve_for<ns_other::other_type1>, int>>>));

    CHECK((bind_instance<setting2<resolve_for<ns_a::a_type>, resolve_for<global_type>, int>>::value == 0));
    CHECK((std::is_base_of_v<unspecialized, bind_instance<setting2<resolve_for<ns_a::a_type>, resolve_for<global_type>, int>>>));

    return errcount;
}
