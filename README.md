# Boost.Reflecto

Compile-time type and enum value name extraction for C++17.

## Class `name`

All functions return `name const &`, a `constexpr` type derived from
`std::string_view` with constant-time equality comparison:

```cpp
class name:
    public std::string_view
{
    name(name const &) = delete;
    name & operator=(name const &) = delete;

public:
    constexpr name_kind kind() const noexcept;
    constexpr std::uint64_t hash() const noexcept;

    friend constexpr bool operator==(name const & a, name const & b) noexcept;
    friend constexpr bool operator!=(name const & a, name const & b) noexcept;
};
```

## `type_name`

```cpp
#include <boost/reflecto/type_name.hpp>
#include <map>
#include <vector>

namespace reflecto = boost::reflecto;

namespace ns { struct point { int x, y; }; }

static_assert(reflecto::type_name<int>() == "int");
static_assert(reflecto::type_name<ns::point>() == "ns::point");
static_assert(reflecto::type_name<std::vector<int>>() == "std::vector<int>");
static_assert(reflecto::type_name<std::map<int, std::vector<float>>>() == "std::map<int, std::vector<float>>");
```

## `enum_value_name` / `unqualified_enum_value_name`

```cpp
#include <boost/reflecto/enum_value_name.hpp>
#include <cassert>

namespace reflecto = boost::reflecto;

enum class color { red, green, blue };

static_assert(reflecto::enum_value_name<color::red>() == "color::red");
static_assert(reflecto::unqualified_enum_value_name<color::red>() == "red");

int main()
{
    color c = color::green;

    // Run-time, from a variable:
    assert(reflecto::enum_value_name(c) == "color::green");
    assert(reflecto::unqualified_enum_value_name(c) == "green");
}
```

Runtime enum value lookup scans integer values in [-32, 127] by default. To
customize the search range, specialize `enum_lookup_range` for your enum:

```cpp
template <>
struct reflecto::enum_lookup_range<color>
{
    static constexpr int min_value = 0;
    static constexpr int max_value = 2;
};
```

## Limitations

Type aliases are resolved:

```cpp
#include <boost/reflecto/type_name.hpp>
#include <iostream>
#include <string>

namespace reflecto = boost::reflecto;

int main()
{
    std::cout << reflecto::type_name<std::string>();
}
```

Possible output:

    std::__cxx11::basic_string<char>

## Compiler Support

GCC 9+, Clang 5+, MSVC 14.3+; requires C++17.

## License

Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).
