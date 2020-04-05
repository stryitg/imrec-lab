#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: make_img.sh LALALLA"
    exit 1
fi

IMG_TEXT=$1
IMG_TEXT_CHARS=($(echo $IMG_TEXT | fold -w 1))

IMGS=()
for c in ${IMG_TEXT_CHARS[@]}; do
    IMGS+=($c.txt)
done

paste -d " " $(echo ${IMGS[@]}) | sed -e '1,2d' > img.txt

FIRST_LINE=$(head -n 1 img.txt)
HIGHT=$(wc -l img.txt | cut -d " " -f1)
WIDTH=$(echo $FIRST_LINE | wc -w)

TEMP_FILE=$(echo temp_43t3g3g43gtempgrg)
echo $HIGHT $WIDTH | cat - img.txt > $TEMP_FILE 
mv $TEMP_FILE img.txt
cat img.txt
