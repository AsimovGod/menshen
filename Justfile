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


compile-default arg1:
        meson setup -Dpackage="{{arg1}}" "build/{{arg1}}"
        meson compile -C "build/{{arg1}}"


compile-flatpak arg1 arg2:
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
        if [[ ! -e "/dev/fuse" ]] ; then
        AsCmdFlatpak+=(
                --disable-rofiles-fuse
        )
        fi
        #
        "${AsCmdFlatpak[@]}"


test-linux arg1 arg2:
        meson test "run" --setup "{{arg1}}" -C "build/{{arg2}}"


test-flatpak arg1 arg2:
        #!/bin/bash
        set -euxo pipefail
        # declaration
        declare -a "AsCmdFlatpak"
        # flatpak
        AsCmdFlatpak=(
                flatpak-builder --run
                "build/{{arg1}}/builder/dir"
                "{{arg2}}/io.AsimovGod.menshen.json"
        )
        #
        "${AsCmdFlatpak[@]}"


install-linux arg1:
        meson install -C "build/{{arg1}}" --destdir="install"


package-debian:
        #!/bin/bash
        set -euxo pipefail
        # declaration
        declare -a "AsCmdInstall"
        declare -a "AsCmdDpkg"
        # install
        AsCmdInstall=(
                install -v -d -m 0755
                "release/debian"
        )
        #
        "${AsCmdInstall[@]}"
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


package-flatpak arg1:
        #!/bin/bash
        set -euxo pipefail
        # declaration
        declare -a "AsCmdInstall"
        declare -a "AsCmdFlatpak"
        # install
        AsCmdInstall=(
                install -v -d -m 0755
                "release/{{arg1}}"
        )
        #
        "${AsCmdInstall[@]}"
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


debug-linux arg1 arg2:
        just remove "{{arg2}}"
        just compile-default "{{arg2}}"
        just test-linux "{{arg1}}" "{{arg2}}"


debug-flatpak:
        just remove "flatpak"
        just compile-flatpak "flatpak" "package/flatpak"
        just test-flatpak "flatpak" "package/flatpak"


work-debian:
        just remove "debian"
        just compile-default "debian"
        just install-linux "debian"
        just package-debian


work-flatpak:
        just remove "flatpak"
        just compile-flatpak "flatpak" "package/flatpak"
        just package-flatpak "flatpak"


work-flathub:
        just remove "flathub"
        just compile-flatpak "flathub" "package/flatpak/flathub"
        just package-flatpak "flathub"

