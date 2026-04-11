// Copyright 2026 Emil Dotchevski

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/reflecto/type_name.hpp>

namespace { struct tag; }

constexpr auto const & n = boost::reflecto::type_name<tag>();
