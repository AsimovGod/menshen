project(
        'menshen',
        'c',
        version : '0.1',
        default_options : [
                'warning_level=2',
                'c_std=c17'
                ]
        )

gtk_dep = dependency(
        'gtk4'
        )

adw_dep = dependency(
        'libadwaita-1'
        )

exe = executable(
        'menshen',
        'src/main.c',
        dependencies : [
                gtk_dep,
                adw_dep
                ],
        install : true,
        install_dir : 'bin'
        )

test(
        'run',
        exe,
        args : ['-m 0'],
        env : ['GTK_A11Y=none'],
        timeout : 10
        )

custom_target(
        'gdb',
        output : 'gdb',
        command : [
                'gdb',
                '-q',
                '',
                exe.full_path()
        ],
        build_by_default : false
)

