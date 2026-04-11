// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/reflecto/value_name.hpp>

namespace { enum class color { red }; }

constexpr auto const & n = boost::reflecto::value_name<color::red>();
