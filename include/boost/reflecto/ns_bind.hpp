#ifndef BOOST_REFLECTO_NS_BIND_HPP_INCLUDED
#define BOOST_REFLECTO_NS_BIND_HPP_INCLUDED

// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/reflecto/config.hpp>
#include <boost/reflecto/detail/pretty_function_traits.hpp>
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
    constexpr t BOOST_REFLECTO_CDECL m()
    {
        constexpr char const * pf = BOOST_REFLECTO_PRETTY_FUNCTION;
        constexpr int b = pf_traits::type_prefix_size_constexpr;
        constexpr int total = sizeof(BOOST_REFLECTO_PRETTY_FUNCTION) - 1 - pf_traits::suffix_size - b;
        static_assert(total >= 1);
        return { pf + b, total };
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

    template <class... Args>
    struct first_rf;

    template <class T, class... Rest>
    struct first_rf<resolve_for<T>, Rest...>
    {
        using type = T;
    };

    template <class Arg, class... Rest>
    struct first_rf<Arg, Rest...>
    {
        using type = typename first_rf<Rest...>::type;
    };

    template <class Inst>
    struct first_rf_of;

    template <template <class...> class S, class... Args>
    struct first_rf_of<S<Args...>>
    {
        using type = typename first_rf<Args...>::type;
    };

    ////////////////////////////////////////

    template <class... Ts>
    struct L {};

    template <template <class...> class S, class Prefix, class Replacement, class... Suffix>
    struct subst_rf;

    template <template <class...> class S, class... Prefix, class Replacement>
    struct subst_rf<S, L<Prefix...>, Replacement>
    {
        using type = S<Prefix...>;
    };

    template <template <class...> class S, class... Prefix, class Replacement, class T, class... Suffix>
    struct subst_rf<S, L<Prefix...>, Replacement, resolve_for<T>, Suffix...>
    {
        using type = S<Prefix..., Replacement, Suffix...>;
    };

    template <template <class...> class S, class... Prefix, class Replacement, class Arg, class... Suffix>
    struct subst_rf<S, L<Prefix...>, Replacement, Arg, Suffix...>
    {
        using type = typename subst_rf<S, L<Prefix..., Arg>, Replacement, Suffix...>::type;
    };

    template <class Inst, class Replacement>
    struct subst_first_rf;

    template <template <class...> class S, class... Args, class Replacement>
    struct subst_first_rf<S<Args...>, Replacement>
    {
        using type = typename subst_rf<S, L<>, Replacement, Args...>::type;
    };

    ////////////////////////////////////////

    template <class Inst, class T, bool TypeOk>
    struct resolve_rf;

    template <class Inst, bool = has_rf<Inst>::value>
    struct resolve;

    template <class Inst>
    struct resolve<Inst, true>
    {
        using T = typename first_rf_of<Inst>::type;
        using try_type = typename resolve<typename subst_first_rf<Inst, T>::type>::type;
        static constexpr bool type_ok = is_specialization<try_type>::value;
        using type = typename resolve_rf<Inst, T, type_ok>::type;
    };

    template <class Inst>
    struct resolve<Inst, false>
    {
        using type = Inst;
    };

    template <class Inst, class T, int End>
    struct try_ns_level;

    template <class Inst, class T, int End>
    struct try_ns_level
    {
        static constexpr char const * begin = n<T>().begin;
        static constexpr std::uint64_t nh = hash_sequence(begin, begin + End);
        using resolved = typename resolve<typename subst_first_rf<Inst, k<nh>>::type>::type;
        static constexpr bool ok = is_specialization<resolved>::value;
    };

    template <class Inst, class T, int End, bool Ok>
    struct ns_walk;

    template <class Inst, class T, int End>
    struct ns_walk<Inst, T, End, true>
    {
        using type = typename try_ns_level<Inst, T, End>::resolved;
    };

    template <class Inst, class T>
    struct ns_walk<Inst, T, 0, false>
    {
        using type = typename resolve<typename subst_first_rf<Inst, T>::type>::type;
    };

    template <class Inst, class T, int End>
    struct ns_walk<Inst, T, End, false>
    {
        static constexpr int pe = find_parent_ns_end(n<T>().begin, End);
        using level = try_ns_level<Inst, T, pe>;
        static constexpr bool ok = pe > 0 && level::ok;
        using type = typename ns_walk<Inst, T, pe, ok>::type;
    };

    template <class Inst, class T>
    struct resolve_rf<Inst, T, true>
    {
        using type = typename resolve<typename subst_first_rf<Inst, T>::type>::type;
    };

    template <class Inst, class T>
    struct resolve_rf<Inst, T, false>
    {
        static constexpr auto info = n<T>();
        using level = try_ns_level<Inst, T, info.size>;
        static constexpr bool ok = info.size > 0 && level::ok;
        using type = typename ns_walk<Inst, T, info.size, ok>::type;
    };

    ////////////////////////////////////////

    template <class Inst>
    struct ns_bind_
    {
        using type = typename resolve<Inst>::type;
    };
} // namespace d

template <class T>
using in_namespace = d::k<d::ns_hash<T>()>;

template <class Inst>
using ns_bind = typename d::ns_bind_<Inst>::type;

} // namespace boost::reflecto

#endif // #ifndef BOOST_REFLECTO_NS_BIND_HPP_INCLUDED
