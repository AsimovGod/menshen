gtkdep = [
    dependency('gtk4'),
    dependency('libadwaita-1'),
    dependency('json-glib-1.0')
    ]

subdir('xml')

sourcefiles = files(
    'Main.c'
    )

executable(
    'menshen',
    resources,
    sourcefiles,
    dependencies : gtkdep,
    install : false
    )
