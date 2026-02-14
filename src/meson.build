DepGtk = [
    dependency('gtk4'),
    dependency('libadwaita-1'),
    dependency('json-glib-1.0')
    ]


subdir('xml')


FileSource = files(
    'Main.c'
    )


ExecMenshen = executable(
    'menshen',
    FileResource,
    FileSource,
    dependencies : DepGtk,
    install : BoolInstallExec,
    install_dir : DirInstallExec,
    install_mode : 'rwxr-xr-x'
    )
