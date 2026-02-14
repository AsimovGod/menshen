install_emptydir(
    'DEBIAN',
    install_mode : 'rwxr-xr-x'
    )

subdir('DEBIAN')


install_emptydir(
    'usr',
    install_mode : 'rwxr-xr-x'
    )


DirInstallExec = 'usr/bin'

install_emptydir(
    DirInstallExec,
    install_mode : 'rwxr-xr-x'
    )


install_emptydir(
    'usr/share',
    install_mode : 'rwxr-xr-x'
    )


install_emptydir(
    'usr/share/applications',
    install_mode : 'rwxr-xr-x'
    )

install_data(
    'usr/share/applications/menshen.desktop',
    install_dir : 'usr/share/applications',
    install_mode : 'rw-r--r--'
    )


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
