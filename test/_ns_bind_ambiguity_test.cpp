// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/reflecto/ns_bind.hpp>

using namespace boost::reflecto;


namespace ns_a
{
    struct this_namespace;

    struct a_type;
}


namespace ns_b
{
    struct this_namespace;

    struct b_type;
}


template <class, class>
struct setting: unspecialized
{
};

template <class T>
struct setting<in_namespace<ns_a::this_namespace>, T>
{
    static constexpr int value = 1;
};

template <class T>
struct setting<T, in_namespace<ns_b::this_namespace>>
{
    static constexpr int value = 2;
};

using result = ns_bind<setting<resolve_for<ns_a::a_type>, resolve_for<ns_b::b_type>>>;

constexpr int v = result::value;
