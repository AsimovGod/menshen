set positional-arguments
set shell := ["bash", "-uc"]



default:
	just --list


clean:
	#!/bin/bash
	declare -a "AsCmdGit"
	AsCmdGit=(
		git
		clean
		-fxd
		-e "./worktree"
	)
	#
	"${AsCmdGit[@]}"


mkdir-build:
	#!/bin/bash
	declare -a "AsCmdInstall"
	AsCmdInstall=(
		'/usr/bin/install'
		-v
		-d
		-m 0755
		"./build/bin"
	)
	#
	"${AsCmdInstall[@]}"


mkdir-pack:
	#!/bin/bash
	declare -a "AsCmdInstall"
	AsCmdInstall=(
		'/usr/bin/install'
		-v
		-d
		-m 0755
		"./pack/deb"
	)
	#
	"${AsCmdInstall[@]}"

build:
	#!/bin/bash
	just clean
	just mkdir-build
	#
	declare -a "AsCmdLib"
	AsCmdLib=(
		pkg-config
		--cflags
		--libs
		"gtk4"
		"libadwaita-1"
	)
	#
	IFS=" " read -r -a AsArgLib <<< "$("${AsCmdLib[@]}")"
	#
	declare -a "AsCmdGcc"
	AsCmdGcc=(
		gcc
		-g
		"./src/Main.c"
		-o
		"./build/bin/menshen"
		"${AsArgLib[@]}"
	)
	#
	"${AsCmdGcc[@]}"


gdb:
	#!/bin/bash
	declare -a "AsCmdGdb"
	AsCmdGdb=(
		gdb
		-q
		"./build/bin/menshen"
		"${@}"
	)
	#
	declare -x GTK_A11Y="none"
	#
	"${AsCmdGdb[@]}"


build-gdb:
	just build
	just gdb


valgrind:
	#!/bin/bash
	declare -a "AsCmdValgrind"
	AsCmdValgrind=(
		valgrind
		--tool=memcheck
		--leak-check=full
		--show-leak-kinds=all
		--num-callers=20
		"./build/bin/menshen"
	)
	#
	"${AsCmdValgrind[@]}"


build-valgrind:
	just build
	just valgrind


run:
	#!/bin/bash
	declare -x GTK_A11Y="none"
	#
	"./build/bin/menshen" "${@}"


build-run:
	just build
	just run

