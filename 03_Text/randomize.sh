#!/bin/bash

raw=`hexdump -e '16/1 "%02x\n" "\n"'`

col=0
row=0

while IFS= read -r line
do
    # echo $line
    case "$line" in 
        "0a")
            row=$((++row))
            col=0
            ;;
        "20")
            col=$((++col))
            ;;
        "  ")
            ;;
        *)
            data+="$row $col $line"$'\n'
            col=$((++col))
            ;;
    esac
done < <(printf  "%s\n" "$raw")

data=`echo "$data" | head -n -1 | shuf`
default=0.05

tput reset
while IFS= read -r line; do
    line=($line)
    row=${line[0]}
    col=${line[1]}
    symbol=${line[2]}

    tput cup $row $col
    sleep ${1:-$default}

    echo -e "\u$symbol"

done < <(printf '%s\n' "$data")


tput cup $LINES 0