#ifndef BOOST_REFLECTO_NS_BIND_HPP_INCLUDED
#define BOOST_REFLECTO_NS_BIND_HPP_INCLUDED

// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/reflecto/config.hpp>
#include <boost/reflecto/detail/pretty_function_traits.hpp>
#include <boost/reflecto/detail/mp11.hpp>
#include <type_traits>

namespace boost::reflecto {

template <class>
struct resolve_for {};

template <class T>
struct is_specialization
{
    static constexpr bool value = !std::is_base_of_v<unspecialized, T>;
};

namespace d
{
    using mp11_reflecto::mp_list;
    using mp11_reflecto::mp_front;
    using mp11_reflecto::mp_push_front;
    using mp11_reflecto::mp_product;

    template <std::uint64_t>
    struct k {};

    constexpr int find_parent_ns_end(char const * s, int end) noexcept
    {
        for( int i = end; i != 1; --i )
            if( s[i - 1] == ':' && s[i - 2] == ':' )
                return i - 2;
        return 0;
    }

    template <class T>
    constexpr t BOOST_REFLECTO_CDECL n()
    {
        constexpr char const * pf = BOOST_REFLECTO_PRETTY_FUNCTION;
        constexpr int b = pf_traits::type_prefix_size_constexpr;
        constexpr int total = sizeof(BOOST_REFLECTO_PRETTY_FUNCTION) - 1 - pf_traits::suffix_size - b;
        static_assert(total >= 1);
        return { pf + b, find_parent_ns_end(pf + b, total) };
    }

    template <class T>
    constexpr std::uint64_t ns_hash() noexcept
    {
        constexpr auto info = n<T>();
        static_assert(info.size != 0, "in_namespace cannot be used with the global namespace");
        return hash_sequence(info.begin, info.begin + info.size);
    }

    ////////////////////////////////////////

    template <class T>
    struct is_rf: std::false_type {};

    template <class T>
    struct is_rf<resolve_for<T>>: std::true_type {};

    template <class Inst>
    struct has_rf;

    template <template <class...> class S, class... Args>
    struct has_rf<S<Args...>>
    {
        static constexpr bool value = (is_rf<Args>::value || ...);
    };

    ////////////////////////////////////////

    template <class... Levels>
    struct chain;

    template <class Lv>
    struct chain<Lv> {};

    template <class Lv, class... Rest>
    struct chain<Lv, Rest...>: chain<Rest...> {};

    template <class Chain>
    struct suffixes;

    template <class Lv>
    struct suffixes<chain<Lv>>
    {
        using type = mp_list<chain<Lv>>;
    };

    template <class Lv, class... Rest>
    struct suffixes<chain<Lv, Rest...>>
    {
        using type = mp_push_front<typename suffixes<chain<Rest...>>::type, chain<Lv, Rest...>>;
    };

    ////////////////////////////////////////

    template <class T, int End, class... Levels>
    struct build_chain_impl
    {
        static constexpr char const * begin = n<T>().begin;
        static constexpr std::uint64_t h = hash_sequence(begin, begin + End);
        static constexpr int pe = find_parent_ns_end(begin, End);
        using type = typename build_chain_impl<T, pe, Levels..., k<h>>::type;
    };

    template <class T, class... Levels>
    struct build_chain_impl<T, 0, Levels...>
    {
        using type = chain<Levels...>;
    };

    template <class T>
    struct make_chain
    {
        static constexpr auto info = n<T>();
        using type = typename build_chain_impl<T, info.size, T>::type;
    };

    ////////////////////////////////////////

    template <class... Args>
    struct collect_rf_suffixes;

    template <>
    struct collect_rf_suffixes<>
    {
        using type = mp_list<>;
    };

    template <class T, class... Rest>
    struct collect_rf_suffixes<resolve_for<T>, Rest...>
    {
        using chain_t = typename make_chain<T>::type;
        using sfx = typename suffixes<chain_t>::type;
        using type = mp_push_front<typename collect_rf_suffixes<Rest...>::type, sfx>;
    };

    template <class Arg, class... Rest>
    struct collect_rf_suffixes<Arg, Rest...>
    {
        using type = typename collect_rf_suffixes<Rest...>::type;
    };

    template <class Inst>
    struct collect_rf_suffixes_from;

    template <template <class...> class S, class... Args>
    struct collect_rf_suffixes_from<S<Args...>>
    {
        using type = typename collect_rf_suffixes<Args...>::type;
    };

    template <class... Args>
    struct collect_full_chains;

    template <>
    struct collect_full_chains<>
    {
        using type = mp_list<>;
    };

    template <class T, class... Rest>
    struct collect_full_chains<resolve_for<T>, Rest...>
    {
        using chain_t = typename make_chain<T>::type;
        using type = mp_push_front<typename collect_full_chains<Rest...>::type, chain_t>;
    };

    template <class Arg, class... Rest>
    struct collect_full_chains<Arg, Rest...>
    {
        using type = typename collect_full_chains<Rest...>::type;
    };

    template <class Inst>
    struct collect_full_chains_from;

    template <template <class...> class S, class... Args>
    struct collect_full_chains_from<S<Args...>>
    {
        using type = typename collect_full_chains<Args...>::type;
    };

    ////////////////////////////////////////

    template <class SuffixLists>
    struct product_from_list;

    template <class... SLs>
    struct product_from_list<mp_list<SLs...>>
    {
        using type = mp_product<mp_list, SLs...>;
    };

    ////////////////////////////////////////

    template <template <class...> class S, class Prefix, class Replacements, class... Suffix>
    struct subst_all_rf;

    template <template <class...> class S, class... Prefix, class... Rs>
    struct subst_all_rf<S, mp_list<Prefix...>, mp_list<Rs...>>
    {
        using type = S<Prefix...>;
    };

    template <template <class...> class S, class... Prefix, class R, class... Rs, class T, class... Suffix>
    struct subst_all_rf<S, mp_list<Prefix...>, mp_list<R, Rs...>, resolve_for<T>, Suffix...>
    {
        using type = typename subst_all_rf<S, mp_list<Prefix..., R>, mp_list<Rs...>, Suffix...>::type;
    };

    template <template <class...> class S, class... Prefix, class Replacements, class Arg, class... Suffix>
    struct subst_all_rf<S, mp_list<Prefix...>, Replacements, Arg, Suffix...>
    {
        using type = typename subst_all_rf<S, mp_list<Prefix..., Arg>, Replacements, Suffix...>::type;
    };

    template <class Inst, class Replacements>
    struct apply_subst;

    template <template <class...> class S, class... Args, class Replacements>
    struct apply_subst<S<Args...>, Replacements>
    {
        using type = typename subst_all_rf<S, mp_list<>, Replacements, Args...>::type;
    };

    template <class T>
    struct strip_rf { using type = T; };

    template <class T>
    struct strip_rf<resolve_for<T>> { using type = T; };

    template <class Inst>
    struct default_subst;

    template <template <class...> class S, class... Args>
    struct default_subst<S<Args...>>
    {
        using type = S<typename strip_rf<Args>::type...>;
    };

    ////////////////////////////////////////

    template <class Inst, class ChainSuffixTuple, class = void>
    struct one_overload
    {
        struct no_match;
        static void call(no_match);
    };

    template <class Inst, class... Suffixes>
    struct one_overload<Inst, mp_list<Suffixes...>,
        std::enable_if_t<is_specialization<
            typename apply_subst<Inst, mp_list<mp_front<Suffixes>...>>::type>::value>>
    {
        static typename apply_subst<Inst, mp_list<mp_front<Suffixes>...>>::type
        call(Suffixes...);
    };

    template <class Inst, class CrossProduct>
    struct overload_set_impl;

    template <class Inst, class... Tuples>
    struct overload_set_impl<Inst, mp_list<Tuples...>>: one_overload<Inst, Tuples>...
    {
        using one_overload<Inst, Tuples>::call...;
    };

    template <class Inst, class CrossProduct>
    struct overload_set: overload_set_impl<Inst, CrossProduct>
    {
        using overload_set_impl<Inst, CrossProduct>::call;
        static typename default_subst<Inst>::type call(...);
    };

    template <class OverloadSet, class FullChains>
    struct resolve_call;

    template <class OverloadSet, class... Chains>
    struct resolve_call<OverloadSet, mp_list<Chains...>>
    {
        using type = decltype(OverloadSet::call(Chains{}...));
    };

    ////////////////////////////////////////

    template <class Inst, bool = has_rf<Inst>::value>
    struct ns_bind_;

    template <class Inst>
    struct ns_bind_<Inst, false>
    {
        using type = Inst;
    };

    template <class Inst>
    struct ns_bind_<Inst, true>
    {
        using suffix_lists = typename collect_rf_suffixes_from<Inst>::type;
        using cp = typename product_from_list<suffix_lists>::type;
        using full_chains = typename collect_full_chains_from<Inst>::type;
        using type = typename resolve_call<overload_set<Inst, cp>, full_chains>::type;
    };
} // namespace d

template <class T>
using in_namespace = d::k<d::ns_hash<T>()>;

template <class Inst>
using ns_bind = typename d::ns_bind_<Inst>::type;

} // namespace boost::reflecto

#endif // #ifndef BOOST_REFLECTO_NS_BIND_HPP_INCLUDED
