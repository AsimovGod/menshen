project('menshen', 'c',
    version : '0.3.4-dev',
    default_options : ['warning_level=2', 'c_std=gnu11']
    )


gtk_dep = dependency('gtk4', required: true)
adwaita_dep = dependency('libadwaita-1', required: true)
json_glib_dep = dependency('json-glib-1.0', required: true)

resource_xml = 'src/xml/PartResource.xml'
resource_sourcedir = meson.source_root() / 'resource'
generated_header = meson.current_build_dir() / 'src' / 'PartResource.h'
generated_source = meson.current_build_dir() / 'src' / 'PartResource.c'


custom_target(
    'generate-partresource-hander',
    output : generated_header,
    command : [
        'glib-compile-resources',
        resource_xml,
        '--generate-header',
        '--sourcedir=' + resource_sourcedir,
        '--target=' + generated_header
        ],
    build_by_default : true
    )

custom_target(
    'generate-partresource-hander',
    output : generated_source,
    command : [
        'glib-compile-resources',
        resource_xml,
        '--generate-source',
        '--sourcedir=' + resource_sourcedir,
        '--target=' + generated_source
        ],
    build_by_default : true
    )


src_files = [
    'src/Main.c',
    generated_source
    ]


executable('menshen',
    src_files,
    include_directories : include_directories('src',
        meson.current_build_dir() / 'src'),
    dependencies : [gtk_dep, adwaita_dep, json_glib_dep],
    install : true,
    install_dir : get_option('bindir')
    )
