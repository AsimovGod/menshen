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
install_emptydir(
    'app/share/applications',
    install_mode : 'rwxr-xr-x'
    )

install_data(
    'app/share/applications/io.AsimovGod.menshen.desktop',
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

