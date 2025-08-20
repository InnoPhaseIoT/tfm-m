#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Function: build tfm + apu
build_default() {
    # build tfm
    make -C ../ clean
    make -C ../
    # build apu
    make -C ../../../../
}

# Function: clean all + rebuild
clean_all() {
    rm -rf build/
    mkdir build/
    cd build/
    cp -v ../lib.zip ./
    unzip lib.zip
    cd ../
    make -C ../ clean
    make -C ../
    make -C ../../../../ clean
    make -C ../../../../
}

# Function: interactive help menu
show_help() {
    while true; do
        echo ""
        echo ""
        echo ""
        echo ""
        echo "============= Available Options ============="
        echo "1. ./script.sh build"
        echo "   → Cleans tfm, builds tfm, builds apu"
        echo ""
        echo "2. ./script.sh clean_build_all"
        echo "   → Removes tfm-m/build/, creates tfm-m/build/, extracts lib.zip"
        echo "     Cleans apu, builds apu"
        echo ""
        echo "3. Exit"
        echo "============================================="
        echo ""

        # Prompt user
        read -p "Enter the number of the option you want to execute [default=1]: " choice
        choice=${choice:-1}   # default to 1

        case "$choice" in
            1) build_default ;;
            2) clean_all ;;
            3) echo "Exiting..."; exit 0 ;;
            *) echo "Invalid choice";;
        esac

        #echo ""
        #echo "Press Enter to return to menu..."
        #read
    done
}

# Main script logic
case "$1" in
    "")
        show_help
        ;;
    "build")
        build_default
        ;;
    "clean_build_all")
        clean_all
        ;;
    "help")
        show_help
        ;;
    *)
        show_help
        exit 1
        ;;
esac

exit 0
