#ifndef BOOST_REFLECTO_DETAIL_MP11_HPP_INCLUDED
#define BOOST_REFLECTO_DETAIL_MP11_HPP_INCLUDED

// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// The following are based on Boost.Mp11 by Peter Dimov.
// Copyright 2015-2023 Peter Dimov.

namespace boost::reflecto::d {
namespace mp11_reflecto {

    template<class... T> struct mp_list
    {
    };

    ////////////////////////////////////////

    template<class L> struct mp_front_impl
    {
    };

    template<template<class...> class L, class T1, class... T> struct mp_front_impl<L<T1, T...>>
    {
        using type = T1;
    };

    template<class L> using mp_front = typename mp_front_impl<L>::type;

    ////////////////////////////////////////

    template<class L, class... T> struct mp_push_front_impl
    {
    };

    template<template<class...> class L, class... U, class... T> struct mp_push_front_impl<L<U...>, T...>
    {
        using type = L<T..., U...>;
    };

    template<class L, class... T> using mp_push_front = typename mp_push_front_impl<L, T...>::type;

    ////////////////////////////////////////

    template<class L, class... T> struct mp_push_back_impl
    {
    };

    template<template<class...> class L, class... U, class... T> struct mp_push_back_impl<L<U...>, T...>
    {
        using type = L<U..., T...>;
    };

    template<class L, class... T> using mp_push_back = typename mp_push_back_impl<L, T...>::type;

    ////////////////////////////////////////

    template<
        class L1 = mp_list<>, class L2 = mp_list<>, class L3 = mp_list<>,
        class L4 = mp_list<>, class L5 = mp_list<>, class L6 = mp_list<>,
        class L7 = mp_list<>, class L8 = mp_list<>, class L9 = mp_list<>,
        class L10 = mp_list<>, class L11 = mp_list<>>
    struct append_11_impl
    {
    };

    template<
        template<class...> class L1, class... T1,
        template<class...> class L2, class... T2,
        template<class...> class L3, class... T3,
        template<class...> class L4, class... T4,
        template<class...> class L5, class... T5,
        template<class...> class L6, class... T6,
        template<class...> class L7, class... T7,
        template<class...> class L8, class... T8,
        template<class...> class L9, class... T9,
        template<class...> class L10, class... T10,
        template<class...> class L11, class... T11>
    struct append_11_impl<
        L1<T1...>, L2<T2...>, L3<T3...>, L4<T4...>, L5<T5...>, L6<T6...>,
        L7<T7...>, L8<T8...>, L9<T9...>, L10<T10...>, L11<T11...>>
    {
        using type = L1<T1..., T2..., T3..., T4..., T5..., T6..., T7..., T8..., T9..., T10..., T11...>;
    };

    template<class... L> using mp_append = typename append_11_impl<L...>::type;

    ////////////////////////////////////////

    template<class L, template<class...> class B> struct mp_rename_impl
    {
    };

    template<template<class...> class L, class... T, template<class...> class B> struct mp_rename_impl<L<T...>, B>
    {
        using type = B<T...>;
    };

    template<class L, template<class...> class B> using mp_rename = typename mp_rename_impl<L, B>::type;

    ////////////////////////////////////////

    template<class L1, class L2> struct mp_assign_impl
    {
    };

    template<template<class...> class L1, class... T, template<class...> class L2, class... U> struct mp_assign_impl<L1<T...>, L2<U...>>
    {
        using type = L1<U...>;
    };

    template<class L1, class L2> using mp_assign = typename mp_assign_impl<L1, L2>::type;

    ////////////////////////////////////////

    template<template<class...> class F, class P, class... L> struct mp_product_impl_2
    {
    };

    template<template<class...> class F, class P> struct mp_product_impl_2<F, P>
    {
        using type = mp_list<mp_rename<P, F>>;
    };

    template<template<class...> class F, class P, template<class...> class L1, class... T1, class... L>
    struct mp_product_impl_2<F, P, L1<T1...>, L...>
    {
        using type = mp_append<typename mp_product_impl_2<F, mp_push_back<P, T1>, L...>::type...>;
    };

    template<template<class...> class F, class... L> struct mp_product_impl
    {
    };

    template<template<class...> class F> struct mp_product_impl<F>
    {
        using type = mp_list< F<> >;
    };

    template<template<class...> class F, class L1, class... L> struct mp_product_impl<F, L1, L...>
    {
        using type = mp_assign<L1, typename mp_product_impl_2<F, mp_list<>, L1, L...>::type>;
    };

    template<template<class...> class F, class... L> using mp_product = typename mp_product_impl<F, L...>::type;

} // namespace mp11_reflecto
} // namespace boost::reflecto::d

#endif // #ifndef BOOST_REFLECTO_DETAIL_MP11_HPP_INCLUDED
