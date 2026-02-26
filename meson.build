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
InfoPackage = run_command(
    'jq', '-Mr', '.package', 'resource/info/Info.json',
    check : true
    ).stdout().strip()

InfoId = run_command(
    'jq', '-Mr', '.id', 'resource/info/Info.json',
    check : true
    ).stdout().strip()

InfoVersion = run_command(
    'jq', '-Mr', '.version', 'resource/info/Info.json',
    check : true
    ).stdout().strip()


# platform
OptionPlatform = get_option('platform')

subdir('platform' / OptionPlatform)


# src
subdir('src')


# test
test(
    'exec',
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

