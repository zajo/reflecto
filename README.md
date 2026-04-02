# Boost.Reflecto

Compile-time type and enum value name extraction for C++17.

## Class `name`

`name` is a `constexpr` type derived from `std::string_view` with constant-time
equality comparison:

```cpp
class name:
    public std::string_view
{
    explicit name(name const &) = default;
    name & operator=(name const &) = delete;

public:
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
    enum_name,
    enum_value_name,
    unqualified_enum_value_name,
    unnamed_enum_value,
    enum_value_out_of_lookup_range
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

## Enumeration Reflection

All examples in this section assume:

```cpp
#include <boost/reflecto/enum_value_name.hpp>

using namespace boost::reflecto;

enum class color { red, green, blue };
```

### `enum_value_name` / `unqualified_enum_value_name`

```cpp
static_assert(enum_value_name<color::red>() == "color::red");
static_assert(unqualified_enum_value_name<color::red>() == "red");

int main()
{
    color c = color::green;

    // Run-time, from a variable:
    assert(enum_value_name(c) == "color::green");
    assert(unqualified_enum_value_name(c) == "green");
}
```

The runtime overloads scan integer values in [-8, 63] by default, returning a
`name` with `kind() == name_kind::enum_value_out_of_lookup_range` for
values outside the range (to help detect incomplete ranges, the compile-time
`enum_value_name` / `unqualified_enum_value_name` force a compile error for values
outside the range).

To customize the lookup range for a given enum, specialize `enum_lookup_range`:

```cpp
template <>
struct boost::reflecto::enum_lookup_range<color>
{
    static constexpr int min_value = 0;
    static constexpr int max_value = 2;
};
```

The default range in lieu of specialization is defined by
`BOOST_REFLECTO_DEFAULT_ENUM_MIN_VALUE` and
`BOOST_REFLECTO_DEFAULT_ENUM_MAX_VALUE`.

> NOTE: The following `constexpr` functions operate by scanning the `enum_lookup_range`
for named enum values:

#### `named_enum_value_count`

```cpp
static_assert(named_enum_value_count<color>() == 3);
```

#### `min_named_enum_value` / `max_named_enum_value`

```cpp
static_assert(min_named_enum_value<color>() == color::red);
static_assert(max_named_enum_value<color>() == color::blue);
```

#### `enum_value_names` / `unqualified_enum_value_names`

Return a `const` reference to a static C array of `name` objects for each named
enum value, in order of their integer values:

```cpp
auto const & names = enum_value_names<color>();
static_assert(std::is_same_v<decltype(names), name const (&)[3]>);

static_assert(names[0] == "color::red");
static_assert(names[1] == "color::green");
static_assert(names[2] == "color::blue");

auto const & unames = unqualified_enum_value_names<color>();
static_assert(std::is_same_v<decltype(unames), name const (&)[3]>);

static_assert(unames[0] == "red");
static_assert(unames[1] == "green");
static_assert(unames[2] == "blue");
```

#### `sorted_enum_value_names` / `sorted_unqualified_enum_value_names`

Same as above, but sorted lexicographically:

```cpp
auto const & sorted = sorted_enum_value_names<color>();

static_assert(sorted[0] == "color::blue");
static_assert(sorted[1] == "color::green");
static_assert(sorted[2] == "color::red");

auto const & usorted = sorted_unqualified_enum_value_names<color>();

static_assert(usorted[0] == "blue");
static_assert(usorted[1] == "green");
static_assert(usorted[2] == "red");
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

Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).
