project(
    'menshen', 'c',
    license : 'GPL-3.0-or-later',
    license_files : 'LICENSE',
    meson_version : '>=1.7.0',
    default_options : [
        'prefix=/'
        ]
    )


InfoVersion = run_command(
    'jq', '-Mr', '.version', 'resource/info/Info.json',
    check : true
).stdout().strip()


OptionPackage = get_option('package')


if OptionPackage != 'none'
    subdir('package' / OptionPackage)
endif


if is_variable('DirInstallExec')
    BoolInstallExec = true
else
    BoolInstallExec = false
    DirInstallExec = ''
endif


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
