set positional-arguments
set shell := ["bash", "-uc"]



InfoPackage := `jq -Mr ".package" "./resource/info/Info.json"`
InfoId := `jq -Mr ".id" "./resource/info/Info.json"`
InfoArch := `jq -Mr ".architecture" "./resource/info/Info.json"`
InfoVersion := `jq -Mr ".version" "./resource/info/Info.json"`


PackagePackage := InfoPackage + "_" + InfoVersion + "_" + InfoArch
PackageLinux := PackagePackage + "_linux.tar.gz"
PackageDebian := PackagePackage + "_debian.deb"
PackageFlatpak := PackagePackage + "_linux.flatpak"



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
        shasum -a 512 "{{file_name(arg1)}}" > "{{file_name(arg1)}}.sha512"


linux:
        #!/bin/bash
        set -euxo pipefail
        ##
        declare -a "AsCmdInstall"
        declare -a "AsCmdRsync"
        ##
        AsCmdInstall=(
                install -d -v -m 0755
                "./build/package/linux/usr/bin"
        )
        #
        "${AsCmdInstall[@]}"
        ##
        AsCmdRsync=(
                rsync -a -v --chmod=D0755,F0755
                "./build/compile/bin/menshen"
                "./build/package/linux/usr/bin/"
        )
        #
        "${AsCmdRsync[@]}"
        ##
        AsCmdRsync=(
                rsync -a -v --chmod=D0755,F0644
                "./package/debian/usr/share"
                "./build/package/linux/usr/"
        )
        #
        "${AsCmdRsync[@]}"


targz:
        #!/bin/bash
        set -euxo pipefail
        ##
        declare -a "AsCmdInstall"
        declare -a "AsCmdRsync"
        declare -a "AsCmdTar"
        ##
        AsCmdInstall=(
                install -d -v -m 0755
                "./build/release/linux"
        )
        #
        "${AsCmdInstall[@]}"
        ##
        AsCmdTar=(
                tar -czvf
                "./build/release/linux/{{PackageLinux}}"
                -C "./build/package/linux" "usr"
        )
        #
        "${AsCmdTar[@]}"
        ##
        just shasum "./build/release/linux/{{PackageLinux}}"


debian:
        #!/bin/bash
        set -euxo pipefail
        ##
        declare -a "AsCmdInstall"
        declare -a "AsCmdRsync"
        declare -a "AsCmdDpkg"
        ##
        AsCmdInstall=(
                install -d -v -m 0755
                "./build/package/linux/DEBIAN"
                "./build/release/debian"
        )
        #
        "${AsCmdInstall[@]}"
        ##
        AsCmdRsync=(
                rsync -a -v --chmod=D0755,F0644
                "./package/debian/DEBIAN"
                "./build/package/linux/"
        )
        #
        "${AsCmdRsync[@]}"
        ##
        echo "Version: {{InfoVersion}}" >> "./build/package/linux/DEBIAN/control"
        ##
        AsCmdDpkg=(
                dpkg-deb --root-owner-group --build
                "./build/package/linux"
                "./build/release/debian/{{PackageDebian}}"
        )
        #
        "${AsCmdDpkg[@]}"
        ##
        just shasum "./build/release/debian/{{PackageDebian}}"


flatpak:
        #!/bin/bash
        set -euxo pipefail
        ##
        declare -a "AsCmdInstall"
        declare -a "AsCmdRsync"
        declare -a "AsCmdFlatpak"
        ##
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
        ##
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
                "./build/release/flatpak/{{PackageFlatpak}}"
                "{{InfoId}}"
        )
        #
        "${AsCmdFlatpak[@]}"
        ##
        just shasum "./build/release/flatpak/{{PackageFlatpak}}"



debug-run: clean compile run

debug-gdb: clean compile gdb


package-all: clean compile linux targz debian flatpak

package-debian: clean compile linux targz debian

package-flatpak: clean compile linux flatpak
