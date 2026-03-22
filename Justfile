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
        rm -rfv "package/{{arg1}}"


setup arg1:
        meson setup -Dplatform="{{arg1}}" "build/{{arg1}}"


compile-default arg1:
        meson setup -Dplatform="{{arg1}}" "build/{{arg1}}"
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
                flatpak-builder --force-clean --ccache
                --repo="build/{{arg1}}/builder/repo"
                --state-dir="build/{{arg1}}/builder/state"
                "build/{{arg1}}/builder/dir"
                "{{arg2}}/io.AsimovGod.menshen.json"
        )
        #
        if [[ ! -e "/dev/fuse" ]] ; then
        AsCmdFlatpak=(
                "${AsCmdFlatpak[@]}"
                --disable-rofiles-fuse
        )
        fi
        #
        "${AsCmdFlatpak[@]}"


test-linux arg1 arg2:
        meson test "exec" --setup "{{arg2}}" -C "build/{{arg1}}"


test-flatpak arg1 arg2:
        #!/bin/bash
        set -euxo pipefail
        # declaration
        declare -a "AsCmdFlatpak"
        ##
        AsCmdFlatpak=(
                flatpak --user remote-add
                --no-gpg-verify --if-not-exists
                "AsimovGod" "build/{{arg1}}/builder/repo"
        )
        #
        "${AsCmdFlatpak[@]}"
        ##
        if [[ "$(stat --printf="%u" "/var/tmp")" != "0" ]] ; then
        AsCmdFlatpak=(
                fakeroot --
        )
        fi
        #
        AsCmdFlatpak=(
                "${AsCmdFlatpak[@]}"
                flatpak --user install --reinstall -y
                "AsimovGod" "{{InfoId}}"
        )
        #
        "${AsCmdFlatpak[@]}"
        ##
        AsCmdFlatpak=(
                flatpak --user run --devel
                --command="{{arg2}}" "{{InfoId}}"
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
                "package/debian"
        )
        #
        "${AsCmdInstall[@]}"
        # deb
        AsCmdDpkg=(
                dpkg-deb --root-owner-group --build
                "build/debian/install"
                "package/debian/{{PackageName}}_debian.deb"
        )
        #
        "${AsCmdDpkg[@]}"
        ##
        just shasum "package/debian/{{PackageName}}_debian.deb"


package-flatpak arg1:
        #!/bin/bash
        set -euxo pipefail
        # declaration
        declare -a "AsCmdInstall"
        declare -a "AsCmdFlatpak"
        # install
        AsCmdInstall=(
                install -v -d -m 0755
                "package/{{arg1}}"
        )
        #
        "${AsCmdInstall[@]}"
        ##
        AsCmdFlatpak=(
                flatpak build-bundle
                "build/{{arg1}}/builder/repo"
                "package/{{arg1}}/{{PackageName}}_{{arg1}}.flatpak"
                "{{InfoId}}"
        )
        #
        "${AsCmdFlatpak[@]}"
        ##
        just shasum "package/{{arg1}}/{{PackageName}}_{{arg1}}.flatpak"


debug-linux arg1 arg2:
        just compile-default "{{arg2}}"
        just test-linux "{{arg1}}" "{{arg2}}"


debug-flatpak:
        just compile-flatpak "flatpak" "platform/flatpak"
        just test-flatpak "flatpak" "bash"


debug-flathub:
        just compile-flatpak "flathub" "platform/flatpak/flathub"
        just test-flatpak "flathub" "bash"


work-debian:
        just remove "debian"
        just compile-default "debian"
        just install-linux "debian"
        just package-debian


work-flatpak:
        just remove "flatpak"
        just compile-flatpak "flatpak" "platform/flatpak"
        just package-flatpak "flatpak"


work-flathub:
        just remove "flathub"
        just compile-flatpak "flathub" "platform/flatpak/flathub"
        just package-flatpak "flathub"

