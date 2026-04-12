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

namespace americas
{
    struct this_namespace;

    struct usd;
    struct cad;
}

namespace europe
{
    struct this_namespace;

    struct eur;
    struct gbp;
}

namespace asia
{
    struct this_namespace;

    struct jpy;
}

template <class From, class To>
struct conversion_fee: unspecialized
{
    static constexpr int basis_points = 100;
};

template <>
struct conversion_fee<
    in_namespace<americas::this_namespace>,
    in_namespace<europe::this_namespace>>
{
    static constexpr int basis_points = 50;
};

template <>
struct conversion_fee<
    americas::usd,
    in_namespace<europe::this_namespace>>
{
    static constexpr int basis_points = 10;
};

template <class T>
struct conversion_fee<T, T>
{
    static constexpr int basis_points = 0;
};

int main()
{
    CHECK((ns_bind<conversion_fee<
        resolve_for<americas::usd>,
        resolve_for<europe::eur>>
    >::basis_points == 10));

    CHECK((ns_bind<conversion_fee<
        resolve_for<americas::cad>,
        resolve_for<europe::gbp>>
    >::basis_points == 50));

    CHECK((ns_bind<conversion_fee<
        resolve_for<americas::usd>,
        resolve_for<asia::jpy>>
    >::basis_points == 100));

    CHECK((ns_bind<conversion_fee<
        resolve_for<europe::eur>,
        resolve_for<europe::eur>>
    >::basis_points == 0));

    return errcount;
}
