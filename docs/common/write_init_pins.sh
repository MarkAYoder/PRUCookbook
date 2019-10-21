#!/bin/bash
init_pins=$(readelf -x .init_pins $1 | grep 0x000 | cut -d' ' -f4-7 | xxd -r -p | tr '\0' '\n' | paste - -)
while read -a line; do
    if [ ${#line[@]} == 2 ]; then
        echo writing \"${line[1]}\" to \"${line[0]}\"
        echo ${line[1]} > ${line[0]}
        sleep 0.1
    fi
done <<< "$init_pins"
