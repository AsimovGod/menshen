# dependency
DepGtk = [
    dependency('gtk4'),
    dependency('libadwaita-1'),
    dependency('json-glib-1.0')
    ]


# resource
ImportGnome = import('gnome')

FileResource = ImportGnome.compile_resources(
    'PartResource',
    'xml/PartResource.xml',
    source_dir : '../resource'
    )


# main
FileSource = files(
    'Main.c'
    )


# executable
ExecMenshen = executable(
    'menshen',
    FileResource,
    FileSource,
    dependencies : DepGtk,
    install : BoolInstallExec,
    install_dir : DirInstallExec,
    install_mode : 'rwxr-xr-x'
    )
