# Copyright 2026 Emil Dotchevski

# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

project('reflecto', 'cpp', default_options : ['cpp_std=c++17', 'b_pch=false'], license : 'boost')

option_single_header = get_option('reflecto_single_header')

compiler = meson.get_compiler('cpp')
compiler_id = compiler.get_id()
if not meson.is_subproject()
    if compiler_id=='msvc'
        add_global_arguments(
            '/FC',
            language:'cpp' )
    elif compiler_id=='clang'
        add_global_arguments(
            '-fdiagnostics-absolute-paths',
            language:'cpp' )
    endif
endif

reflecto = declare_dependency( include_directories: 'include' )

#################################

tests = [
    'ns_bind_ns_walk_test',
    'ns_bind_unspecialized_test',
    'ns_bind_multi_arg_test',
    'ns_bind_two_nsof_test',
    'ns_bind_currency_test',
    'name_test',
    'named_values_test',
    'type_name_test',
    'value_name_test'
]

dep_test_single_header = []
if option_single_header
    dep_test_single_header = declare_dependency(compile_args: ['-DBOOST_REFLECTO_TEST_SINGLE_HEADER'])
endif

dep_runtime_test = declare_dependency(compile_args: ['-DRUNTIME_TEST'])

foreach t : tests
    executable('constexpr_'+t, 'test/'+t+'.cpp', dependencies: [reflecto, dep_test_single_header])
    test(t, executable(t, 'test/'+t+'.cpp', dependencies: [reflecto, dep_test_single_header, dep_runtime_test]) )
endforeach
