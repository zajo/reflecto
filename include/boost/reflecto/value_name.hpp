#ifndef BOOST_REFLECTO_VALUE_NAME_HPP_INCLUDED
#define BOOST_REFLECTO_VALUE_NAME_HPP_INCLUDED

// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/reflecto/config.hpp>
#include <boost/reflecto/bind_instance.hpp>
#include <boost/reflecto/name.hpp>
#include <utility>

#if defined(__clang__) && __clang_major__ >= 15 && __clang_major__ < 20
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wenum-constexpr-conversion"
#endif

namespace boost::reflecto {

template <class Enum>
using lookup_range = bind_instance<enum_lookup_range<resolve_for<Enum>>>;

namespace d
{
    constexpr t strip_enum_value_qualification(t x) noexcept
    {
        char const * b = x.begin;
        char const * e = x.begin + x.size;
        for( char const * p = e; p != b; --p )
        {
            if( p[-1] == ':' && p[-2] == ':' )
                return { p, static_cast<int>(e - p) };
        }
        return x;
    }

    template <int MaxSize>
    constexpr stripped<MaxSize> strip_enum_type_prefix_and_space_before_template_closing_bracket(char const * value, int value_len, int type_len) noexcept
    {
        BOOST_REFLECTO_ASSERT(value_len > 0);
        BOOST_REFLECTO_ASSERT(type_len > 0);
        if( value_len <= type_len + 2 )
            return strip_space_before_template_closing_bracket<MaxSize>(value, value_len);
        stripped<MaxSize> result{};
        int unqual_start = 0;
        for( int i = type_len - 1; i != 0; --i )
        {
            if( value[i] == ':' && value[i - 1] == ':' )
            {
                unqual_start = i + 1;
                break;
            }
        }
        int len = 0;
        std::uint64_t h = hash_start;
        for( int i = 0; i != unqual_start; ++i )
        {
            h = hash_step(h, value[i]);
            result.buf[len++] = value[i];
        }
        char const * src = value + type_len + 2;
        char const * end = value + value_len;
        while( src != end )
        {
            if( src[0] == ' ' && src != end - 1 && src[1] == '>' )
                ++src;
            else
            {
                h = hash_step(h, *src);
                result.buf[len++] = *src++;
            }
        }
        result.len = len;
        result.hash = h;
        return result;
    }

    template <class Enum, Enum Value>
    constexpr t BOOST_REFLECTO_CDECL g()
    {
        static_assert(std::is_enum<Enum>::value, "d::g requires an enum type");
        constexpr char const * pf = BOOST_REFLECTO_PRETTY_FUNCTION;
        constexpr int type_len = q<Enum>().size;
        constexpr int value_start = pf_traits::enum_prefix_size_constexpr + type_len + pf_traits::enum_separator_size;
        constexpr int end = sizeof(BOOST_REFLECTO_PRETTY_FUNCTION) - 1 - pf_traits::suffix_size;
        return { pf + value_start, end - value_start };
    }

    template <int MaxSize>
    constexpr stripped<MaxSize> strip_enum_value_qualification_to_buffer(char const * src, int size) noexcept
    {
        BOOST_REFLECTO_ASSERT(size > 0);
        int start = 0;
        for( int i = size; i != 1; --i )
        {
            if( src[i - 1] == ':' && src[i - 2] == ':' )
            {
                start = i;
                break;
            }
        }
        stripped<MaxSize> result{};
        int len = 0;
        std::uint64_t h = hash_start;
        for( int i = start; i != size; ++i )
        {
            h = hash_step(h, src[i]);
            result.buf[len++] = src[i];
        }
        result.len = len;
        result.hash = h;
        return result;
    }

    constexpr bool is_named_enum_value_name(char c) noexcept
    {
        return c != '(' && c != '-' && !(c >= '0' && c <= '9');
    }

    template <auto EnumValue, bool Unqualify, enum_value_processing_requirements>
    struct value_name_;

    template <auto EnumValue>
    struct value_name_<EnumValue, false, enum_value_processing_requirements::none>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = g<Enum, EnumValue>();
        static constexpr name n{x.begin, x.size, hash_sequence(x.begin, x.begin + x.size),
            is_named_enum_value_name(x.begin[0]) ? name_kind::value_name : name_kind::unnamed_value};
    };

    template <auto EnumValue>
    struct value_name_<EnumValue, false, enum_value_processing_requirements::strip_space_before_template_closing_bracket>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = g<Enum, EnumValue>();
        static constexpr stripped<x.size> s = strip_space_before_template_closing_bracket<x.size>(x.begin, x.size);
        static constexpr bool named = is_named_enum_value_name(x.begin[0]);
        static constexpr name n{
            named ? s.buf : x.begin,
            named ? s.len : x.size,
            named ? s.hash : hash_sequence(x.begin, x.begin + x.size),
            named ? name_kind::value_name : name_kind::unnamed_value};
    };

    template <auto EnumValue>
    struct value_name_<EnumValue, false, enum_value_processing_requirements::strip_type_prefix_and_space_before_template_closing_bracket>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = g<Enum, EnumValue>();
        static constexpr stripped<x.size> s = strip_enum_type_prefix_and_space_before_template_closing_bracket<x.size>(x.begin, x.size, q<Enum>().size);
        static constexpr bool named = is_named_enum_value_name(x.begin[0]);
        static constexpr name n{
            named ? s.buf : x.begin,
            named ? s.len : x.size,
            named ? s.hash : hash_sequence(x.begin, x.begin + x.size),
            named ? name_kind::value_name : name_kind::unnamed_value};
    };

    template <auto EnumValue>
    struct value_name_<EnumValue, true, enum_value_processing_requirements::none>
    {
        using Enum = decltype(EnumValue);
        static constexpr t raw = g<Enum, EnumValue>();
        static constexpr t x = strip_enum_value_qualification(raw);
        static constexpr bool named = is_named_enum_value_name(raw.begin[0]);
        static constexpr name n{
            named ? x.begin : raw.begin,
            named ? x.size : raw.size,
            named ? hash_sequence(x.begin, x.begin + x.size) : hash_sequence(raw.begin, raw.begin + raw.size),
            named ? name_kind::short_value_name : name_kind::unnamed_value};
    };

    template <auto EnumValue>
    struct value_name_<EnumValue, true, enum_value_processing_requirements::copy_pretty_function_string>
    {
        using Enum = decltype(EnumValue);
        static constexpr t x = g<Enum, EnumValue>();
        static constexpr stripped<x.size> s = strip_enum_value_qualification_to_buffer<x.size>(x.begin, x.size);
        static constexpr bool named = is_named_enum_value_name(x.begin[0]);
        static constexpr name n{
            named ? s.buf : x.begin,
            named ? s.len : x.size,
            named ? s.hash : hash_sequence(x.begin, x.begin + x.size),
            named ? name_kind::short_value_name : name_kind::unnamed_value};
    };
} // namespace d

template <auto EnumValue>
constexpr name const & value_name() noexcept
{
    using Enum = decltype(EnumValue);
    static_assert(std::is_enum_v<Enum>);
    using r = lookup_range<Enum>;
    static_assert(static_cast<int>(EnumValue) >= r::min_value, "enum value is below enum_lookup_range::min_value");
    static_assert(static_cast<int>(EnumValue) <= r::max_value, "enum value is above enum_lookup_range::max_value");
    constexpr auto s = std::is_convertible_v<Enum, int>
        ? d::pf_traits::unscoped_enum_value_processing
        : d::pf_traits::scoped_enum_value_processing;
    return d::value_name_<EnumValue, false, s>::n;
}

template <auto EnumValue>
constexpr name const & short_value_name() noexcept
{
    using Enum = decltype(EnumValue);
    static_assert(std::is_enum_v<Enum>);
    using r = lookup_range<Enum>;
    static_assert(static_cast<int>(EnumValue) >= r::min_value, "enum value is below enum_lookup_range::min_value");
    static_assert(static_cast<int>(EnumValue) <= r::max_value, "enum value is above enum_lookup_range::max_value");
    return d::value_name_<EnumValue, true, d::pf_traits::unqualified_enum_value_processing>::n;
}

////////////////////////////////////////

struct enumerator
{
    name const & value_name;
    int value;
};

////////////////////////////////////////

namespace d
{
    // In a constexpr context, some newer compilers do not allow casting int to an invalid enum value.
    // This isn't a check for validity, but a tool to avoid casting to prevent a compile error.
    template <class Enum, int I, class = void>
    struct check_enum_cast_sfinae : std::false_type {};

    template <class Enum, int I>
    struct check_enum_cast_sfinae<Enum, I, std::void_t<std::integral_constant<Enum, static_cast<Enum>(I)>>>
        : std::true_type {};

    template <class Enum, int I, bool = check_enum_cast_sfinae<Enum, I>::value>
    struct enum_cast_sfinae
    {
        static constexpr Enum value = Enum{};
    };

    template <class Enum, int I>
    struct enum_cast_sfinae<Enum, I, true>
    {
        static constexpr Enum value = static_cast<Enum>(I);
    };

    inline constexpr name out_of_lookup_range_name{"*unknown*", 9, 11775755009147575841ull, name_kind::value_out_of_lookup_range};

    template <class Enum, bool Unqualify,
        class = std::make_integer_sequence<int,
            lookup_range<Enum>::max_value -
            lookup_range<Enum>::min_value + 1>>
    struct value_lookup_table;

    template <class Enum, bool Unqualify, int... Is>
    struct value_lookup_table<Enum, Unqualify, std::integer_sequence<int, Is...>>
    {
        static constexpr int minv = lookup_range<Enum>::min_value;

        static constexpr auto s = Unqualify
            ? pf_traits::unqualified_enum_value_processing
            : std::is_convertible_v<Enum, int>
                ? pf_traits::unscoped_enum_value_processing
                : pf_traits::scoped_enum_value_processing;

        static constexpr name const * values[sizeof...(Is)] = { &value_name_<enum_cast_sfinae<Enum, minv + Is>::value, Unqualify, s>::n... };

        static constexpr name const & get(Enum value) noexcept
        {
            int i = static_cast<int>(value);
            if( i >= minv && i - minv < static_cast<int>(sizeof...(Is)) )
                return *values[i - minv];
            return out_of_lookup_range_name;
        }
    };
} // namespace d

template <class Enum>
constexpr name const & value_name(Enum value) noexcept
{
    return d::value_lookup_table<Enum, false>::get(value);
}

template <class Enum>
constexpr name const & short_value_name(Enum value) noexcept
{
    return d::value_lookup_table<Enum, true>::get(value);
}

////////////////////////////////////////

namespace d
{
    template <class Enum, int I, bool = check_enum_cast_sfinae<Enum, I>::value>
    struct is_named_enum_value : std::false_type {};

    template <class Enum, int I>
    struct is_named_enum_value<Enum, I, true>
    {
        static constexpr bool value = is_named_enum_value_name(g<Enum, static_cast<Enum>(I)>().begin[0]);
    };

    template <class Enum, int I, int Max, int... NamedIs>
    struct collect_named
    {
        using type = typename std::conditional_t<
            is_named_enum_value<Enum, I>::value,
            collect_named<Enum, I + 1, Max, NamedIs..., I>,
            collect_named<Enum, I + 1, Max, NamedIs...>
        >::type;
    };

    template <class Enum, int Max, int... NamedIs>
    struct collect_named<Enum, Max, Max, NamedIs...>
    {
        using type = std::integer_sequence<int, NamedIs...>;
    };

    template <class Enum>
    struct named_values_seq_
    {
        using r = lookup_range<Enum>;
        using type = typename collect_named<Enum, r::min_value, r::max_value + 1>::type;
    };

    template <class Enum>
    using named_values_seq = typename named_values_seq_<Enum>::type;

    template <class Enum, int I, int Max, bool = is_named_enum_value<Enum, I>::value>
    struct find_first_named
    {
        static constexpr int value = find_first_named<Enum, I + 1, Max>::value;
    };

    template <class Enum, int I, int Max>
    struct find_first_named<Enum, I, Max, true>
    {
        static constexpr int value = I;
    };

    template <class Enum, int I, int Min, bool = is_named_enum_value<Enum, I>::value>
    struct find_last_named
    {
        static constexpr int value = find_last_named<Enum, I - 1, Min>::value;
    };

    template <class Enum, int I, int Min>
    struct find_last_named<Enum, I, Min, true>
    {
        static constexpr int value = I;
    };

    template <class Enum, bool Unqualify, class NamedSeq>
    struct named_values_holder;

    template <class Enum, int... NamedIs>
    struct named_values_holder<Enum, false, std::integer_sequence<int, NamedIs...>>
    {
        static constexpr enumerator values[sizeof...(NamedIs)] = { { value_name<static_cast<Enum>(NamedIs)>(), NamedIs }... };
    };

    template <class Enum, int... NamedIs>
    struct named_values_holder<Enum, true, std::integer_sequence<int, NamedIs...>>
    {
        static constexpr enumerator values[sizeof...(NamedIs)] = { { short_value_name<static_cast<Enum>(NamedIs)>(), NamedIs }... };
    };
} // namespace d

template <class Enum>
constexpr int named_value_count() noexcept
{
    return int(d::named_values_seq<Enum>::size());
}

template <class Enum>
constexpr Enum min_named_value() noexcept
{
    using r = lookup_range<Enum>;
    return static_cast<Enum>(d::find_first_named<Enum, r::min_value, r::max_value + 1>::value);
}

template <class Enum>
constexpr Enum max_named_value() noexcept
{
    using r = lookup_range<Enum>;
    return static_cast<Enum>(d::find_last_named<Enum, r::max_value, r::min_value>::value);
}

template <class Enum>
constexpr enumerator const (&named_values() noexcept)[named_value_count<Enum>()]
{
    return d::named_values_holder<Enum, false, d::named_values_seq<Enum>>::values;
}

template <class Enum>
constexpr enumerator const (&short_named_values() noexcept)[named_value_count<Enum>()]
{
    return d::named_values_holder<Enum, true, d::named_values_seq<Enum>>::values;
}

////////////////////////////////////////

namespace d
{
    template <int N>
    struct idx_array
    {
        int v[N];
    };

    template <class Enum, bool Unqualify, class NamedSeq>
    struct sorted_indices;

    template <class Enum, bool Unqualify, int... NamedIs>
    struct sorted_indices<Enum, Unqualify, std::integer_sequence<int, NamedIs...>>
    {
        static constexpr int N = sizeof...(NamedIs);
        using holder = named_values_holder<Enum, Unqualify, std::integer_sequence<int, NamedIs...>>;

        static constexpr idx_array<N> sorted() noexcept
        {
            idx_array<N> r{};
            for( int i = 0; i != N; ++i )
                r.v[i] = i;
            for( int i = 1; i != N; ++i )
            {
                int key = r.v[i];
                int j = i;
                for( ; j && holder::values[key].value_name < holder::values[r.v[j - 1]].value_name; --j )
                    r.v[j] = r.v[j - 1];
                r.v[j] = key;
            }
            return r;
        }

        static constexpr idx_array<N> value = sorted();
    };

    template <class Enum, bool Unqualify, class NamedSeq, class IndexSeq>
    struct sorted_named_values_holder;

    template <class Enum, bool Unqualify, class NamedSeq, std::size_t... Js>
    struct sorted_named_values_holder<Enum, Unqualify, NamedSeq, std::index_sequence<Js...>>
    {
        using si = sorted_indices<Enum, Unqualify, NamedSeq>;
        using holder = named_values_holder<Enum, Unqualify, NamedSeq>;

        static constexpr enumerator values[sizeof...(Js)] = { holder::values[si::value.v[Js]]... };
    };
} // namespace d

template <class Enum>
constexpr enumerator const (&sorted_named_values() noexcept)[named_value_count<Enum>()]
{
    return d::sorted_named_values_holder<
        Enum, false,
        d::named_values_seq<Enum>,
        std::make_index_sequence<named_value_count<Enum>()>
    >::values;
}

template <class Enum>
constexpr enumerator const (&sorted_short_named_values() noexcept)[named_value_count<Enum>()]
{
    return d::sorted_named_values_holder<
        Enum, true,
        d::named_values_seq<Enum>,
        std::make_index_sequence<named_value_count<Enum>()>
    >::values;
}

} // namespace boost::reflecto

#if defined(__clang__) && __clang_major__ >= 15 && __clang_major__ < 20
#   pragma clang diagnostic pop
#endif

#endif // #ifndef BOOST_REFLECTO_VALUE_NAME_HPP_INCLUDED
