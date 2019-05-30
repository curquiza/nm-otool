#!/usr/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
DEF="\033[0m"

nm_bin="/Users/curquizar/Documents/nm-otool/ft_nm"


for folder in "$@"
do
    echo "FOLDER : $folder"
    for file in $folder/*; do
        $("$nm_bin" $file > /dev/null 2>&1)
        if [[ "$?" -eq "139" ]]; then
            printf "%-80s $RED%s$DEF\n" "$file" "SEGFAULT"
            continue
        fi
        test="$(diff <(nm $file 2>&1) <("$nm_bin" $file 2>&1))"
        if [[ -z "$test" ]]; then
            printf "%-80s $GREEN%s$DEF\n" "$file" "OK"
        else
            printf "%-80s $RED%s$DEF\n" "$file" "KO"
        fi
    done
done
