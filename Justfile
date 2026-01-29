set positional-arguments
set shell := ["bash", "-uc"]



InfoPackage := `jq -Mr ".package" "./Info.json"`
InfoId := `jq -Mr ".id" "./Info.json"`
InfoArch := `jq -Mr ".architecture" "./Info.json"`
InfoVersion := `jq -Mr ".version" "./Info.json"`


PackagePackage := InfoPackage + "_" + InfoVersion + "_" + InfoArch
PackageLinux := PackagePackage + "_linux.tar.gz"
PackageDebian := PackagePackage + "_debian.deb"
PackageFlatpak := PackagePackage + "_linux.flatpak"



default:
	just --list


clean:
	#!/bin/bash
	set -euxo pipefail
	##
	declare -a "AsCmdGit"
	##
	AsCmdGit=(
		git clean -fxd
		-e "./worktree"
	)
	#
	"${AsCmdGit[@]}"


compile:
	#!/bin/bash
	set -euxo pipefail
	##
	declare -a "AsCmdMkdir"
	declare -a "AsCmdGlib"
	declare -a "AsCmdLib"
	declare -a "AsCmdGcc"
	##
	AsCmdMkdir=(
		mkdir -p -v
		"./build/compile/src"
		"./build/compile/bin"
	)
	#
	"${AsCmdMkdir[@]}"
	##
	AsCmdGlib=(
		glib-compile-resources
		"./src/xml/PartResource.xml"
		--generate-header --sourcedir="."
		--target="./build/compile/src/PartResource.h"
	)
	#
	"${AsCmdGlib[@]}"
	##
	AsCmdGlib=(
		glib-compile-resources
		"./src/xml/PartResource.xml"
		--generate-source --sourcedir="."
		--target="./build/compile/src/PartResource.c"
	)
	#
	"${AsCmdGlib[@]}"
	##
	AsCmdLib=(
		pkg-config --cflags --libs
		"gtk4"
		"libadwaita-1"
		"json-glib-1.0"
	)
	#
	IFS=" " read -r -a AsArgLib <<< "$("${AsCmdLib[@]}")"
	##
	AsCmdGcc=(
		gcc -g
		"./src/Main.c"
		"./build/compile/src/PartResource.c"
		-o "./build/compile/bin/menshen"
		"${AsArgLib[@]}"
	)
	#
	"${AsCmdGcc[@]}"


gdb:
	#!/bin/bash
	set -euxo pipefail
	##
	declare -a "AsCmdGdb"
	declare -x GTK_A11Y="none"
	##
	AsCmdGdb=(
		gdb -q
		"./build/compile/bin/menshen"
	)
	#
	"${AsCmdGdb[@]}"


run:
	#!/bin/bash
	set -euxo pipefail
	##
	declare -x GTK_A11Y="none"
	##
	"./build/compile/bin/menshen"


shasum arg1:
	#!/bin/bash
	set -euxo pipefail
	##
	declare -a "AsCmdShasum"
	##
	cd "{{parent_directory(arg1)}}"
	##
	AsCmdShasum=(
		shasum -a 512
		"{{file_name(arg1)}}"
	)
	#
	"${AsCmdShasum[@]}" > "{{file_name(arg1)}}.sha512"


linux:
	#!/bin/bash
	set -euxo pipefail
	##
	declare -a "AsCmdMkdir"
	declare -a "AsCmdCp"
	declare -a "AsCmdFdfind"
	declare -a "AsCmdChmod"
	##
	AsCmdMkdir=(
		mkdir -p -v
		"./build/package/linux/usr/bin"
	)
	#
	"${AsCmdMkdir[@]}"
	##
	AsCmdCp=(
		cp -r -v
		"./build/compile/bin/menshen"
		"./build/package/linux/usr/bin/"
	)
	#
	"${AsCmdCp[@]}"
	##
	AsCmdCp=(
		cp -r -v
		"./linux/usr/share"
		"./build/package/linux/usr/share"
	)
	#
	"${AsCmdCp[@]}"
	##
	AsCmdFdfind=(
		fdfind --type file .
		"./build/package/linux"
		--exec
		chmod -v 0644
	)
	#
	"${AsCmdFdfind[@]}"
	##
	AsCmdFdfind=(
		fdfind --type directory .
		"./build/package/linux"
		--exec
		chmod -v 0755
	)
	#
	"${AsCmdFdfind[@]}"
	##
	AsCmdChmod=(
		chmod -v 0755
		"./build/package/linux/usr/bin/menshen"
	)
	#
	"${AsCmdChmod[@]}"


targz:
	#!/bin/bash
	set -euxo pipefail
	##
	declare -a "AsCmdInstall"
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
	AsCmdInstall=(
		install -p -v -m 0644
		-t "./build/package/linux/DEBIAN/"
		"./package/debian/control"
	)
	#
	"${AsCmdInstall[@]}"
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


flatpakbuild:
	#!/bin/bash
	set -euxo pipefail
	##
	declare -a "AsCmdInstall"
	declare -a "AsCmdFlatpak"
	##
	AsCmdInstall=(
		install -d -v -m 0755
		"/app/bin"
		"/app/share/applications"
		"/app/share/icons/hicolor/512x512/apps"
	)
	#
	"${AsCmdInstall[@]}"
	##
	AsCmdInstall=(
		install -p -v -m 0755
		"./build/compile/bin/menshen"
		"/app/bin/"
	)
	#
	"${AsCmdInstall[@]}"
	##
	AsCmdInstall=(
		install -p -v -m 0644
		"./linux/usr/share/applications/menshen.desktop"
		"/app/share/applications/{{InfoId}}.desktop"
	)
	#
	"${AsCmdInstall[@]}"
	##
	AsCmdInstall=(
		install -p -v -m 0644
		"./resource/icon/menshen.png"
		"/app/share/icons/hicolor/512x512/apps/{{InfoId}}.png"
	)
	#
	"${AsCmdInstall[@]}"


flatpak:
	#!/bin/bash
	set -euxo pipefail
	##
	declare -a "AsCmdInstall"
	declare -a "AsCmdFlatpak"
	##
	AsCmdInstall=(
		install -d -v -m 0755
		"./build/package/flatpak/repo"
		"./build/package/flatpak/dir"
		"./build/release/flatpak/state"
		"./build/release/flatpak"
	)
	#
	"${AsCmdInstall[@]}"
	##
	AsCmdFlatpak=(
		flatpak-builder
		--repo="./build/package/flatpak/repo"
		--state-dir="./build/release/flatpak/state"
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



debug: clean compile gdb

test: clean compile run

package: clean compile linux targz debian

package-flatpak: clean compile linux flatpak
