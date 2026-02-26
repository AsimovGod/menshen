# dependency
DepPlatform = [
    dependency('gtk4'),
    dependency('libadwaita-1'),
    dependency('json-glib-1.0')
    ]


# src
FileSource = files(
    'src' / 'Main.c'
    )


# debian
ConfigDebian = configuration_data()
ConfigDebian.set('version', InfoVersion)

install_emptydir(
    'DEBIAN',
    install_mode : 'rwxr-xr-x'
    )

configure_file(
    input : 'DEBIAN/control.in',
    configuration : ConfigDebian,
    output : 'control',
    install_dir : 'DEBIAN',
    install_mode : 'rw-r--r--'
    )


# usr
install_emptydir(
    'usr',
    install_mode : 'rwxr-xr-x'
    )


# bin
DirInstallExec = 'usr/bin'

install_emptydir(
    DirInstallExec,
    install_mode : 'rwxr-xr-x'
    )


# share
install_emptydir(
    'usr/share',
    install_mode : 'rwxr-xr-x'
    )


# applications
ConfigDesktop = configuration_data()
ConfigDesktop.set('icon', InfoPackage)

install_emptydir(
    'usr/share/applications',
    install_mode : 'rwxr-xr-x'
    )

configure_file(
    input : '../../resource/desktop/menshen.desktop.in',
    output : 'menshen.desktop',
    configuration : ConfigDesktop,
    install_dir : 'usr/share/applications',
    install_mode : 'rw-r--r--'
    )


# icons
install_emptydir(
    'usr/share/icons',
    install_mode : 'rwxr-xr-x'
    )

install_emptydir(
    'usr/share/icons/hicolor',
    install_mode : 'rwxr-xr-x'
    )

install_emptydir(
    'usr/share/icons/hicolor/512x512',
    install_mode : 'rwxr-xr-x'
    )

install_emptydir(
    'usr/share/icons/hicolor/512x512/apps',
    install_mode : 'rwxr-xr-x'
    )

install_data(
    '../../resource/icon/menshen.png',
    install_dir : 'usr/share/icons/hicolor/512x512/apps',
    install_mode : 'rw-r--r--'
    )

