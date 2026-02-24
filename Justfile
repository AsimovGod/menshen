set positional-arguments
set shell := ["bash", "-uc"]



InfoPackage := `jq -Mr ".package" "./resource/info/Info.json"`
InfoId := `jq -Mr ".id" "./resource/info/Info.json"`
InfoArch := `jq -Mr ".architecture" "./resource/info/Info.json"`
InfoVersion := `jq -Mr ".version" "./resource/info/Info.json"`

PackageName := InfoPackage + "_" + InfoVersion + "_" + InfoArch



default:
        just --list --unsorted


clean:
        git clean -fxd


compile arg1:
        meson setup "build/{{arg1}}"
        meson configure -Dpackage="{{arg1}}" "build/{{arg1}}"
        meson compile -C "build/{{arg1}}"


run arg1:
        meson test "run" -C "build/{{arg1}}"


gdb arg1:
        meson test "run" --setup "gdb" -C "build/{{arg1}}"


install arg1:
        meson install -C "build/{{arg1}}" --destdir="install"


shasum arg1:
        #!/bin/bash
        set -euxo pipefail
        ##
        cd "{{parent_directory(arg1)}}"
        shasum -a 256 "{{file_name(arg1)}}" > "{{file_name(arg1)}}.sha256"


debian:
        #!/bin/bash
        set -euxo pipefail
        # declaration
        declare -a "AsCmdInstall"
        declare -a "AsCmdTar"
        declare -a "AsCmdDpkg"
        # install
        AsCmdInstall=(
                install -v -d -m 0755
                "release/debian"
        )
        #
        "${AsCmdInstall[@]}"
        # tar.gz
        AsCmdTar=(
                tar -cvf
                "release/debian/{{PackageName}}_debian.tar.gz"
                -C "build/debian/install" "usr"
        )
        #
        "${AsCmdTar[@]}"
        ##
        just shasum "release/debian/{{PackageName}}_debian.tar.gz"
        # deb
        AsCmdDpkg=(
                dpkg-deb --root-owner-group --build
                "build/debian/install"
                "release/debian/{{PackageName}}_debian.deb"
        )
        #
        "${AsCmdDpkg[@]}"
        ##
        just shasum "release/debian/{{PackageName}}_debian.deb"


flatpak:
        #!/bin/bash
        set -euxo pipefail
        # declaration
        declare -a "AsCmdInstall"
        declare -a "AsCmdFlatpak"
        # install
        AsCmdInstall=(
                install -v -d -m 0755
                "build/flatpak/builder/repo"
                "build/flatpak/builder/state"
                "build/flatpak/builder/dir"
                "release/flatpak"
        )
        #
        "${AsCmdInstall[@]}"
        # flatpak
        AsCmdFlatpak=(
                flatpak-builder --force-clean
                --repo="build/flatpak/builder/repo"
                --state-dir="build/flatpak/builder/state"
                "build/flatpak/builder/dir"
                "package/flatpak/io.AsimovGod.menshen.json"
        )
        #
        "${AsCmdFlatpak[@]}"
        ##
        AsCmdFlatpak=(
                flatpak build-bundle
                "build/flatpak/builder/repo"
                "release/flatpak/{{PackageName}}_flatpak.flatpak"
                "{{InfoId}}"
        )
        #
        "${AsCmdFlatpak[@]}"
        ##
        just shasum "release/flatpak/{{PackageName}}_flatpak.flatpak"


work arg1:
        just clean
        just compile "{{arg1}}"
        just install "{{arg1}}"
        just "{{arg1}}"


test arg1 arg2:
        just clean
        just compile "{{arg2}}"
        just "{{arg1}}" "{{arg2}}"

