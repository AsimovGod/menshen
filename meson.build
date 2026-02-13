project(
    'menshen', 'c',
    license : 'GPL-3.0-or-later',
    license_files : 'LICENSE',
    meson_version : '>=1.7.0'
    )


subdir('src')


test(
    'run',
    ExecMenshen,
    env : [
        'GTK_A11Y=none'
        ]
    )


add_test_setup(
    'gdb',
    gdb : true
)
