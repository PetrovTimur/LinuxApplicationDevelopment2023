#!/bin/bash
set -eu

FILE="rhasher"

ans=($(echo -ne test | md5sum))
if echo "MD5 \"test\"" | ./${FILE} | grep -q ${ans}; then
	exit 0
else
	exit 1
fi