# dependency
DepPlatform = [
    dependency('gtk4'),
    dependency('libadwaita-1'),
    dependency('json-glib-1.0'),
    dependency('libportal')
    ]


# src
FileMain = files(
    'src' / 'Main.cpp'
    )


# app
install_emptydir(
    'app',
    install_mode : 'rwxr-xr-x'
    )


# bin
DirInstallExec = 'app/bin'

install_emptydir(
    DirInstallExec,
    install_mode : 'rwxr-xr-x'
    )


# share
install_emptydir(
    'app/share',
    install_mode : 'rwxr-xr-x'
    )


# applications
ConfigDesktop = configuration_data()
ConfigDesktop.set('icon', InfoId)

install_emptydir(
    'app/share/applications',
    install_mode : 'rwxr-xr-x'
    )

configure_file(
    input : '../../resource/desktop/menshen.desktop.in',
    output : 'menshen.desktop',
    configuration : ConfigDesktop,
    install_dir : 'app/share/applications',
    install_mode : 'rw-r--r--'
    )


# icons
install_emptydir(
    'app/share/icons',
    install_mode : 'rwxr-xr-x'
    )

install_emptydir(
    'app/share/icons/hicolor',
    install_mode : 'rwxr-xr-x'
    )

install_emptydir(
    'app/share/icons/hicolor/512x512',
    install_mode : 'rwxr-xr-x'
    )

install_emptydir(
    'app/share/icons/hicolor/512x512/apps',
    install_mode : 'rwxr-xr-x'
    )

install_data(
    '../../resource/icon/menshen.png',
    rename : 'io.AsimovGod.menshen.png',
    install_dir : 'app/share/icons/hicolor/512x512/apps',
    install_mode : 'rw-r--r--'
    )

