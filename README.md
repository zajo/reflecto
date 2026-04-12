# Boost.Reflecto

Type name and enum value name reflection for C++17.

## Class `name`

`name` is a `constexpr` type derived from `std::string_view` with constant-time
equality comparison:

```cpp
class name:
    public std::string_view
{
    ....

public:

    constexpr name() noexcept;
    explicit constexpr name(name const &) noexcept;

    constexpr name_kind kind() const noexcept;

    constexpr std::uint64_t hash() const noexcept;

    friend constexpr bool operator==(name const & a, name const & b) noexcept;
    friend constexpr bool operator!=(name const & a, name const & b) noexcept;
};
```

where `name_kind` is:

```cpp
enum class name_kind
{
    empty,
    type_name,
    value_name,
    short_value_name,
    unnamed_value,
    value_out_of_lookup_range
};
```

## Type Reflection

### `type_name`

```cpp
#include <boost/reflecto/type_name.hpp>
#include <map>
#include <vector>

using namespace boost::reflecto;

namespace ns { struct point { int x, y; }; }

static_assert(type_name<int>() == "int");
static_assert(type_name<ns::point>() == "ns::point");
static_assert(type_name<std::vector<int>>() == "std::vector<int>");
static_assert(type_name<std::map<int, std::vector<float>>>() == "std::map<int, std::vector<float>>");
```

`type_name` is not supported for types enclosed in unnamed namespaces.

## Enumeration Value Names Reflection

All examples in this section assume:

```cpp
#include <boost/reflecto/value_name.hpp>

using namespace boost::reflecto;

enum class color
{
    red,
    green = 10,
    blue = 20
};
```

Enum value name reflection is not supported for enums enclosed in unnamed
namespaces.

### `value_name` / `short_value_name`

```cpp
static_assert(value_name<color::red>() == "color::red");
static_assert(short_value_name<color::red>() == "red");

int main()
{
    color c = color::green;

    // Run-time, from a variable:
    assert(value_name(c) == "color::green");
    assert(short_value_name(c) == "green");
}
```

The runtime overloads scan integer values in [-8, 63] by default, returning a
`name` with `kind() == name_kind::value_out_of_lookup_range` for values outside
the range (to help detect insufficient ranges, the compile-time `value_name` /
`short_value_name` force a compile error for values outside the range).

To customize the lookup range for a given enum, specialize `enum_lookup_range`
(see [namespace-dependent specialization](#namespace-dependent-specialization)):

```cpp
namespace boost::reflecto {
    template <>
    struct enum_lookup_range<color>
    {
        static constexpr int min_value = 0;
        static constexpr int max_value = 20;
    };
}
```

## Named Enumeration Values Reflection

The following `constexpr` functions operate by scanning the `enum_lookup_range`
for named enum values.

### `named_value_count`

```cpp
static_assert(named_value_count<color>() == 3);
```

### `min_named_value` / `max_named_value`

```cpp
static_assert(min_named_value<color>() == color::red);
static_assert(max_named_value<color>() == color::blue);
```

### `named_values` / `short_named_values`

Return a `const` reference to a static C array of `enumerator` objects for each
named enum value, in order of their integer values:

```cpp
auto const & entries = named_values<color>();
static_assert(std::is_same_v<decltype(entries), enumerator const (&)[3]>);

static_assert(entries[0].value_name == "color::red");
static_assert(entries[0].value == 0);
static_assert(entries[1].value_name == "color::green");
static_assert(entries[1].value == 10);
static_assert(entries[2].value_name == "color::blue");
static_assert(entries[2].value == 20);

auto const & uentries = short_named_values<color>();
static_assert(std::is_same_v<decltype(uentries), enumerator const (&)[3]>);

static_assert(uentries[0].value_name == "red");
static_assert(uentries[1].value_name == "green");
static_assert(uentries[2].value_name == "blue");
```

Iterating over named enum values:

```cpp
for (auto const & e : named_values<color>())
    std::cout << e.value_name << " = " << e.value << "\n";
```

### `sorted_named_values` / `sorted_short_named_values`

Same as above, but sorted lexicographically by name:

```cpp
auto const & sorted = sorted_named_values<color>();

static_assert(sorted[0].value_name == "color::blue");
static_assert(sorted[0].value == 20);
static_assert(sorted[1].value_name == "color::green");
static_assert(sorted[1].value == 10);
static_assert(sorted[2].value_name == "color::red");
static_assert(sorted[2].value == 0);

auto const & usorted = sorted_short_named_values<color>();

static_assert(usorted[0].value_name == "blue");
static_assert(usorted[1].value_name == "green");
static_assert(usorted[2].value_name == "red");
```

## Namespace-Dependent Specialization

Reflecto provides a mechanism for specializing class templates not just for a
specific type, but also for all types within a given namespace.

### Specializing `enum_lookup_range` for different namespaces

The `enum_lookup_range` template can be specialized for a specific enum or for
all enums in a given namespace, allowing independent libraries to configure
their own ranges without clashing.

To make a class template compatible with this system, use `unspecialized` as
the base of the primary template definition. For example, `enum_lookup_range` is
defined as:

```cpp
template <class>
struct enum_lookup_range: unspecialized
{
    static constexpr int min_value = -8;
    static constexpr int max_value = 63;
};
```

By convention, to define a specialization for all types from a given namespace,
use `in_namespace`:

```cpp
namespace lib_a
{
    struct this_namespace;

    enum class status
    {
        ok,
        fail
    };
}

namespace boost::reflecto
{
    template <>
    struct enum_lookup_range<in_namespace<lib_a::this_namespace>>
    {
        static constexpr int min_value = 0;
        static constexpr int max_value = 255;
    };
}
```

A different library can define its own specialization without clashing:

```cpp
namespace lib_b
{
    struct this_namespace;

    enum class mode
    {
        fast,
        slow
    };
}

namespace boost::reflecto
{
    template <>
    struct enum_lookup_range<in_namespace<lib_b::this_namespace>>
    {
        static constexpr int min_value = -100;
        static constexpr int max_value = 100;
    };
}
```

With this in place, use `ns_bind` to select the correct specialization based on
the namespace of the argument:

```cpp
using ra = ns_bind<enum_lookup_range<resolve_for<lib_a::status>>>;
static_assert(ra::min_value == 0 && ra::max_value == 255);

using rb = ns_bind<enum_lookup_range<resolve_for<lib_b::mode>>>;
static_assert(rb::min_value == -100 && rb::max_value == 100);
```

Type-specific specializations are supported as usual (as shown in the `color`
example earlier), and take precedence over namespace specializations.

### Multiple namespace-dependent arguments

Templates with multiple type parameters can use `resolve_for` in any position.
Specializations use `in_namespace` for namespace-dependent parameters and
concrete types for the rest:

```cpp
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
```

When resolving, `ns_bind` processes each `resolve_for` argument independently.
Type-specific matches take precedence over namespace matches at each position:

```cpp
// usd has a type-specific match, 10 bps:
static_assert(ns_bind<
    conversion_fee<
        resolve_for<americas::usd>,
        resolve_for<europe::eur>>
>::basis_points == 10);

// cad has no type-specific match, falls back to americas namespace, 50 bps:
static_assert(ns_bind<
    conversion_fee<
        resolve_for<americas::cad>,
        resolve_for<europe::gbp>>
>::basis_points == 50);

// americas -> asia has no specialization, falls back to the default:
static_assert(ns_bind<
    conversion_fee<
        resolve_for<americas::usd>,
        resolve_for<asia::jpy>>
>::basis_points == 100);

// same currency, no conversion fee:
static_assert(ns_bind<
    conversion_fee<
        resolve_for<europe::eur>,
        resolve_for<europe::eur>>
>::basis_points == 0);
```

## Limitations

Type aliases are resolved:

```cpp
#include <boost/reflecto/type_name.hpp>
#include <iostream>
#include <string>

using namespace boost::reflecto;

int main()
{
    std::cout << type_name<std::string>();
}
```

Possible output:

    std::__cxx11::basic_string<char>

## Compiler Support

GCC 9+, Clang 5+, MSVC 14.3+; requires C++17.

## License

Distributed under the
[Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).
