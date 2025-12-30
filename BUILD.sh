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
                )

                IFS=" " read -r -a AsArgLib <<< "$("${AsCmdLib[@]}")"

                declare -a "AsCmdGcc"
                AsCmdGcc=(
                        gcc
                        "./src/main.c"
                        -o
                        "./build/bin/menshen"
                        "${AsArgLib[@]}"
                )

                "${AsCmdGcc[@]}"
                ;;

        "exec")
                "./build/bin/menshen" "${@}"
                ;;

        "build-exec")
                'FrBuildSh' "build"
                'FrBuildSh' "exec" "${@}"
                ;;

        *)
                echo -e "\n\033[031m Error: Unknown Case. \033[0m"
                exit "1"
                ;;
esac