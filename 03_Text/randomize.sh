#!/bin/bash



default_sleeptime="0.02"
sleeptime="${1:-$default_sleeptime}"

arr=()
i=0
while read LINE; do
    for ((j = 0; j <${#LINE}; ++j)); do
        cur_char=${LINE:$j:1}
        if [[ $cur_char != " " ]]; then
            arr+=("$i,$j,$cur_char")
        fi
    done
    ((i++))
done

arr=( $(shuf -e "${arr[@]}") )

imax=$i
tput clear

for g in ${arr[@]}; do
    i="$(cut -d',' -f1 <<<"$g")"
    j="$(cut -d',' -f2 <<<"$g")"
    c="$(cut -d',' -f3 <<< "$g")"
    color_code=$(( 31 + $RANDOM % 7 ))
    color="\033[0;${color_code}m"
    tput cup $i $j
    printf "${color}${c}"
    sleep $sleeptime
done
tput cup $imax 0

: '
tput clear
for i in {1..10}; do
    for j in {1..10}; do
        tput cup $i $j
        echo a
    done
done
'
