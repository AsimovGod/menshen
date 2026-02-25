# project
project(
    'menshen', 'c',
    license : 'GPL-3.0-or-later',
    license_files : 'LICENSE',
    meson_version : '>=1.7.0',
    default_options : [
        'prefix=/'
        ]
    )


# info
InfoVersion = run_command(
    'jq', '-Mr', '.version', 'resource/info/Info.json',
    check : true
).stdout().strip()


# package
OptionPackage = get_option('package')


if OptionPackage != 'none'
    subdir('package' / OptionPackage)
endif


# install
if is_variable('DirInstallExec')
    BoolInstallExec = true
else
    BoolInstallExec = false
    DirInstallExec = ''
endif


# src
subdir('src')


# test
test(
    'run',
    ExecMenshen,
    env : [
        'GTK_A11Y=none'
        ]
    )

add_test_setup(
    'run',
    gdb : false
    )

add_test_setup(
    'gdb',
    gdb : true
    )

