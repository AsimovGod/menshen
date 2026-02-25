# dependency
DepGtk = [
    dependency('gtk4'),
    dependency('libadwaita-1'),
    dependency('json-glib-1.0')
    ]

if OptionPackage == 'flatpak'
    DepPackage = [
        dependency('libportal')
        ]
else
    DepPackage = [
        ]
endif


# resource
ImportGnome = import('gnome')

FileResource = ImportGnome.compile_resources(
    'PartResource',
    'PartResource.xml',
    source_dir : '../resource'
    )


# main
FileSource = files(
    OptionPackage / 'Main.c'
    )


# executable
ExecMenshen = executable(
    'menshen',
    FileResource,
    FileSource,
    dependencies : [
        DepGtk,
        DepPackage
        ],
    install : BoolInstallExec,
    install_dir : DirInstallExec,
    install_mode : 'rwxr-xr-x'
    )
