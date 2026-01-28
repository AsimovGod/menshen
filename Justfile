set positional-arguments
set shell := ["bash", "-uc"]



default:
	just --list


clean:
	#!/bin/bash
	declare -a "AsCmdGit"
	##
	AsCmdGit=(
		git
		clean
		-fxd
		-e "./worktree"
	)
	#
	"${AsCmdGit[@]}"


compile:
	#!/bin/bash
	just clean
	##
	declare -a "AsCmdMkdir"
	declare -a "AsCmdLib"
	declare -a "AsCmdGcc"
	##
	AsCmdMkdir=(
		mkdir
		-p -v
		--
		"./build/compile/bin"
	)
	#
	"${AsCmdMkdir[@]}"
	##
	AsCmdLib=(
		pkg-config
		--cflags
		--libs
		"gtk4"
		"libadwaita-1"
	)
	#
	IFS=" " read -r -a AsArgLib <<< "$("${AsCmdLib[@]}")"
	##
	AsCmdGcc=(
		gcc
		-g
		"./src/Main.c"
		-o
		"./build/compile/bin/menshen"
		"${AsArgLib[@]}"
	)
	#
	"${AsCmdGcc[@]}"


gdb:
	#!/bin/bash
	declare -a "AsCmdGdb"
	declare -x GTK_A11Y="none"
	##
	AsCmdGdb=(
		gdb
		-q
		"./build/compile/bin/menshen"
		"${@}"
	)
	#
	"${AsCmdGdb[@]}"


valgrind:
	#!/bin/bash
	declare -a "AsCmdValgrind"
	##
	AsCmdValgrind=(
		valgrind
		--tool=memcheck
		--leak-check=full
		--show-leak-kinds=all
		--num-callers=20
		"./build/compile/bin/menshen"
	)
	#
	"${AsCmdValgrind[@]}"


run:
	#!/bin/bash
	declare -x GTK_A11Y="none"
	##
	"./build/compile/bin/menshen" "${@}"


debian:
	#!/bin/bash
	declare -a "AsCmdMkdir"
	declare -a "AsCmdCp"
	declare -a "AsCmdFdfind"
	declare -a "AsCmdChmod"
	declare -a "AsCmdDpkg"
	declare -a "AsCmdShasum"
	##
	AsCmdMkdir=(
		mkdir
		-p -v
		--
		"./build/package/debian/DEBIAN"
		"./build/package/debian/usr/bin"
		"./build/release/debian"
	)
	#
	"${AsCmdMkdir[@]}"
	##
	AsCmdCp=(
		cp
		-r -v
		"./package/debian/control"
		--
		"./build/package/debian/DEBIAN/"
	)
	#
	"${AsCmdCp[@]}"
	##
	AsCmdCp=(
		cp
		-r -v
		"./build/compile/bin/menshen"
		--
		"./build/package/debian/usr/bin/"
	)
	#
	"${AsCmdCp[@]}"
	##
	AsCmdCp=(
		cp
		-r -v
		"./linux/usr/share"
		--
		"./build/package/debian/usr/share"
	)
	#
	"${AsCmdCp[@]}"
	##
	AsCmdFdfind=(
		fdfind
		--type file
		.
		"./build/package/debian"
		--exec
		chmod
		-v
		0644
	)
	#
	"${AsCmdFdfind[@]}"
	##
	AsCmdFdfind=(
		fdfind
		--type directory
		.
		"./build/package/debian"
		--exec
		chmod
		-v
		0755
	)
	#
	"${AsCmdFdfind[@]}"
	##
	AsCmdChmod=(
		chmod
		-v
		0755
		"./build/package/debian/usr/bin/menshen"
	)
	#
	"${AsCmdChmod[@]}"
	##
	AsCmdDpkg=(
		dpkg-deb
		--root-owner-group
		--build
		"./build/package/debian"
		"./build/release/debian/menshen_0.4.0_amd64.deb"
	)
	#
	"${AsCmdDpkg[@]}"
	##
	(
		cd "./build/release/debian"
		#
		AsCmdShasum=(
			shasum
			-a 512
			"menshen_0.4.0_amd64.deb"
		)
		#
		"${AsCmdShasum[@]}" > "menshen_0.4.0_amd64.deb.sha512"
	)


