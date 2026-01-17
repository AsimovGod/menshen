#!/bin/bash

set -e

function FrBuildSh () {
        declare -a "AsCmdBash"
        AsCmdBash=(
                bash
                "${BASH_SOURCE[0]}"
                "${@}"
        )

        "${AsCmdBash[@]}"
}

declare -fr "FrBuildSh"

declare VsCase="${1}"

if [[ -n "${1}" ]] ; then
        shift "1"
fi

case "${VsCase}" in
        "clean")
                declare -a "AsCmdGit"
                AsCmdGit=(
                        git
                        clean
                        -fxd
                        -e "./worktree/"
                )

                "${AsCmdGit[@]}"
                ;;

        "mkdir")
                declare -a "AsCmdInstall"
                AsCmdInstall=(
                        '/usr/bin/install'
                        -v
                        -d
                        -m 0755
                )

                case "${1}" in
                        "build")
                                AsCmdInstall=(
                                        "${AsCmdInstall[@]}"
                                        "./build/bin"
                                )
                                ;;
                        "pack-deb")
                                AsCmdInstall=(
                                        "${AsCmdInstall[@]}"
                                        "./pack/deb"
                                )
                                ;;
                esac

                "${AsCmdInstall[@]}" ;
                ;;

        "build")
                'FrBuildSh' "clean"
                'FrBuildSh' "mkdir" "build"

                declare -a "AsCmdLib"
                AsCmdLib=(
                        pkg-config
                        --cflags
                        --libs
                        "gtk4"
                        "libadwaita-1"
                        "argtable2"
                )

                IFS=" " read -r -a AsArgLib <<< "$("${AsCmdLib[@]}")"

                declare -a "AsCmdGcc"
                AsCmdGcc=(
                        gcc
                        -g
                        -O0
                        "./src/main.c"
                        -o
                        "./build/bin/menshen"
                        "${AsArgLib[@]}"
                )

                "${AsCmdGcc[@]}"
                ;;

        "gdb")
                declare -a "AsCmdGdb"
                AsCmdGdb=(
                        gdb
                        -q
                        "./build/bin/menshen"
                        "${@}"
                )

                declare -x GTK_A11Y="none"

                "${AsCmdGdb[@]}"
                ;;

        "build-gdb")
                'FrBuildSh' "build"
                'FrBuildSh' "gdb" "${@}"
                ;;

        "valgrind")
                declare -a "AsCmdValgrind"
                AsCmdValgrind=(
                        valgrind
                        --tool=memcheck
                        --leak-check=full
                        --show-leak-kinds=all
                        --num-callers=20
                        "./build/bin/menshen"
                )

                "${AsCmdValgrind[@]}"
                ;;

        "build-valgrind")
                'FrBuildSh' "build"
                'FrBuildSh' "valgrind" "${@}"
                ;;

        "run")
                declare -x GTK_A11Y="none"

                "./build/bin/menshen" "${@}"
                ;;

        "build-run")
                'FrBuildSh' "build"
                'FrBuildSh' "run" "${@}"
                ;;

        *)
                echo -e "\n\033[031m Error: Unknown Case. \033[0m"
                exit "1"
                ;;
esac