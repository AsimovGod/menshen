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


module arg1:
        #!/bin/bash
        set -euxo pipefail
        ##
        cd "{{arg1}}"
        git submodule init
        git submodule update --recursive


shasum arg1:
        #!/bin/bash
        set -euxo pipefail
        ##
        cd "{{parent_directory(arg1)}}"
        shasum -a 256 "{{file_name(arg1)}}" > "{{file_name(arg1)}}.sha256"


remove arg1:
        rm -rfv "build/{{arg1}}"
        rm -rfv "release/{{arg1}}"


compile arg1:
        meson setup -Dpackage="{{arg1}}" "build/{{arg1}}"
        meson compile -C "build/{{arg1}}"


test arg1 arg2:
        meson test "run" --setup "{{arg1}}" -C "build/{{arg2}}"


install arg1:
        meson install -C "build/{{arg1}}" --destdir="install"


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


flatpak arg1 arg2:
        #!/bin/bash
        set -euxo pipefail
        # declaration
        declare -a "AsCmdInstall"
        declare -a "AsCmdFlatpak"
        # install
        AsCmdInstall=(
                install -v -d -m 0755
                "build/{{arg1}}/builder/repo"
                "build/{{arg1}}/builder/state"
                "build/{{arg1}}/builder/dir"
                "release/{{arg1}}"
        )
        #
        "${AsCmdInstall[@]}"
        # flatpak
        AsCmdFlatpak=(
                flatpak-builder --force-clean
                --repo="build/{{arg1}}/builder/repo"
                --state-dir="build/{{arg1}}/builder/state"
                "build/{{arg1}}/builder/dir"
                "{{arg2}}/io.AsimovGod.menshen.json"
        )
        #
        "${AsCmdFlatpak[@]}"
        ##
        AsCmdFlatpak=(
                flatpak build-bundle
                "build/{{arg1}}/builder/repo"
                "release/{{arg1}}/{{PackageName}}_{{arg1}}.flatpak"
                "{{InfoId}}"
        )
        #
        "${AsCmdFlatpak[@]}"
        ##
        just shasum "release/{{arg1}}/{{PackageName}}_{{arg1}}.flatpak"


task-test arg1 arg2:
        just remove "{{arg2}}"
        just compile "{{arg2}}"
        just test "{{arg1}}" "{{arg2}}"


work-debian:
        just remove "debian"
        just compile "debian"
        just install "debian"
        just "debian"


work-flatpak:
        just remove "flatpak"
        just flatpak "flatpak" "package/flatpak"


work-flathub:
        just remove "flathub"
        just flatpak "flathub" "package/flatpak/flathub"

