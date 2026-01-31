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


compile:
        #!/bin/bash
        set -euxo pipefail
        ##
        declare -a "AsCmdInstall"
        declare -a "AsCmdGlib"
        declare -a "AsCmdLib"
        declare -a "AsCmdGcc"
        ##
        AsCmdInstall=(
                install -d -v -m 0755
                "./build/compile/src"
                "./build/compile/bin"
        )
        #
        "${AsCmdInstall[@]}"
        ##
        AsCmdGlib=(
                glib-compile-resources --generate-header
                "./src/xml/PartResource.xml" --sourcedir="./resource"
                --target="./build/compile/src/PartResource.h"
        )
        #
        "${AsCmdGlib[@]}"
        ##
        AsCmdGlib=(
                glib-compile-resources --generate-source
                "./src/xml/PartResource.xml" --sourcedir="./resource"
                --target="./build/compile/src/PartResource.c"
        )
        #
        "${AsCmdGlib[@]}"
        ##
        AsCmdLib=(
                pkg-config --cflags --libs
                "gtk4" "libadwaita-1" "json-glib-1.0"
        )
        #
        IFS=" " read -r -a AsArgLib <<< "$("${AsCmdLib[@]}")"
        ##
        AsCmdGcc=(
                gcc -g
                "./src/Main.c" "./build/compile/src/PartResource.c"
                -o "./build/compile/bin/menshen" "${AsArgLib[@]}"
        )
        #
        "${AsCmdGcc[@]}"


gdb:
        #!/bin/bash
        set -euxo pipefail
        ##
        declare -x GTK_A11Y="none"
        ##
        gdb -q "./build/compile/bin/menshen"


run:
        #!/bin/bash
        set -euxo pipefail
        ##
        declare -x GTK_A11Y="none"
        ##
        exec "./build/compile/bin/menshen"


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
        declare -a "AsCmdRsync"
        declare -a "AsCmdTar"
        declare -a "AsCmdDpkg"
        # base
        AsCmdInstall=(
                install -d -v -m 0755
                "./build/package/debian/usr/bin"
                "./build/package/debian/DEBIAN"
                "./build/release/debian"
        )
        #
        "${AsCmdInstall[@]}"
        ##
        AsCmdRsync=(
                rsync -a -v --chmod=D0755,F0755
                "./build/compile/bin/menshen"
                "./build/package/debian/usr/bin/"
        )
        #
        "${AsCmdRsync[@]}"
        ##
        AsCmdRsync=(
                rsync -a -v --chmod=D0755,F0644
                "./package/debian/usr"
                "./package/debian/DEBIAN"
                "./build/package/debian/"
        )
        #
        "${AsCmdRsync[@]}"
        # tar.gz
        AsCmdTar=(
                tar -czvf
                "./build/release/debian/{{PackageName}}_debian.tar.gz"
                -C "./build/package/debian" "usr"
        )
        #
        "${AsCmdTar[@]}"
        ##
        just shasum "./build/release/debian/{{PackageName}}_debian.tar.gz"
        # deb
        echo "Version: {{InfoVersion}}" >> "./build/package/debian/DEBIAN/control"
        ##
        AsCmdDpkg=(
                dpkg-deb --root-owner-group --build
                "./build/package/debian"
                "./build/release/debian/{{PackageName}}_debian.deb"
        )
        #
        "${AsCmdDpkg[@]}"
        ##
        just shasum "./build/release/debian/{{PackageName}}_debian.deb"


flatpak:
        #!/bin/bash
        set -euxo pipefail
        # declaration
        declare -a "AsCmdInstall"
        declare -a "AsCmdRsync"
        declare -a "AsCmdTar"
        declare -a "AsCmdFlatpak"
        # base
        AsCmdInstall=(
                install -d -v -m 0755
                "./build/package/flatpak/app/bin"
                "./build/package/flatpak/dir"
                "./build/package/flatpak/repo"
                "./build/package/flatpak/state"
                "./build/release/flatpak"
        )
        #
        "${AsCmdInstall[@]}"
        ##
        AsCmdRsync=(
                rsync -a -v --chmod=D0755,F0755
                "./build/compile/bin/menshen"
                "./build/package/flatpak/app/bin/"
        )
        #
        "${AsCmdRsync[@]}"
        ##
        AsCmdRsync=(
                rsync -a -v --chmod=D0755,F0644
                "./package/flatpak/app/share"
                "./build/package/flatpak/app/"
        )
        #
        "${AsCmdRsync[@]}"
        # tar.gz
        AsCmdTar=(
                tar -czvf
                "./build/release/flatpak/{{PackageName}}_flatpak.tar.gz"
                -C "./build/package/flatpak" "app"
        )
        #
        "${AsCmdTar[@]}"
        ##
        just shasum "./build/release/flatpak/{{PackageName}}_flatpak.tar.gz"
        # flatpak
        AsCmdFlatpak=(
                flatpak-builder
                --repo="./build/package/flatpak/repo"
                --state-dir="./build/package/flatpak/state"
                --force-clean "./build/package/flatpak/dir"
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



debug-run: clean compile run

debug-gdb: clean compile gdb


package-all: clean compile debian flatpak

package-debian: clean compile debian

package-flatpak: clean compile flatpak
