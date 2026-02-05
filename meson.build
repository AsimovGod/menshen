project(
    'menshen', 'c',
    license : 'GPL-3.0-or-later',
    license_files : 'LICENSE',
    version : run_command(
        'jq', '-Mr', '.version', 'resource/info/Info.json',
        check : true
        ).stdout().strip(),
    meson_version : '>=1.7.0'
    )

subdir('src')

test(
    'test',
    ExecMenshen
    )

