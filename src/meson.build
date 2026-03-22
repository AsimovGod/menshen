# src
FilePart = files(
    'PartDefault.cpp'
)


# resource
ImportGnome = import('gnome')

FileResource = ImportGnome.compile_resources(
    'PartResource',
    'xml/PartResource.xml',
    source_dir : '../resource'
    )


# executable
ExecMenshen = executable(
    'menshen',
    FilePart,
    FileMain,
    FileResource,
    dependencies : [
        DepPlatform
        ],
    install : true,
    install_dir : DirInstallExec,
    install_mode : 'rwxr-xr-x'
    )
