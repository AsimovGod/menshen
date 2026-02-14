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


package arg1:
        meson install -C "build/{{arg1}}" --destdir="package/{{arg1}}"


shasum arg1:
        #!/bin/bash
        set -euxo pipefail
        ##
        cd "{{parent_directory(arg1)}}"
        ##
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
                -C "build/debian/package/debian" "usr"
        )
        #
        "${AsCmdTar[@]}"
        ##
        just shasum "release/debian/{{PackageName}}_debian.tar.gz"
        # deb
        AsCmdDpkg=(
                dpkg-deb --root-owner-group --build
                "build/debian/package/debian"
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
        declare -a "AsCmdFlatpak"
        # flatpak
        AsCmdFlatpak=(
                flatpak-builder --force-clean
                --repo="./build/package/flatpak/repo"
                --state-dir="./build/package/flatpak/state"
                "./build/package/flatpak/dir"
                "./package/flatpak/io.AsimovGod.menshen.json"
        )
        #
        "${AsCmdFlatpak[@]}"
        ##
        AsCmdFlatpak=(
                flatpak build-bundle
                "./build/package/flatpak/repo"
                "./build/release/flatpak/{{PackageName}}_flatpak.flatpak"
                "{{InfoId}}"
        )
        #
        "${AsCmdFlatpak[@]}"
        ##
        just shasum "./build/release/flatpak/{{PackageName}}_flatpak.flatpak"


work arg1:
        just clean
        just compile "{{arg1}}"
        just package "{{arg1}}"
        just "{{arg1}}"


test arg1 arg2:
        just clean
        just compile "{{arg2}}"
        just "{{arg1}}" "{{arg2}}"

