#!/usr/bin/bash

#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Usage: make_img.sh 1010 1001 10011"
    exit 1
fi

MAX_LENGTH=0
for var in "$@"; do
    LENGTH=${#var}
    MAX_LENGTH=$(($LENGTH > $MAX_LENGTH ? $LENGTH : $MAX_LENGTH))
done

rm img.txt
touch img.txt
for var in "$@"; do
    LENGTH=${#var}
    TO_APPEND_COUNT=$(($MAX_LENGTH-$LENGTH))
    
    for (( i=1; i<=$TO_APPEND_COUNT; i++ )); do
        var="_"$var
    done
    
    IMG_TEXT=$var
    IMG_TEXT_CHARS=($(echo $IMG_TEXT | fold -w 1))

    IMGS=()
    for c in ${IMG_TEXT_CHARS[@]}; do
        IMGS+=($c.txt)
    done

    paste -d " " $(echo ${IMGS[@]}) | sed -e '1,1d' > img_.txt
    cat img.txt img_.txt > tmp.txt
    mv tmp.txt img.txt
done

FIRST_LINE=$(head -n 1 img.txt)
HIGHT=$(wc -l img.txt | cut -d " " -f1)
WIDTH=$(echo $FIRST_LINE | wc -w)

echo $HIGHT $WIDTH | cat - img.txt > tmp.txt
mv tmp.txt img.txt

cat img.txt
