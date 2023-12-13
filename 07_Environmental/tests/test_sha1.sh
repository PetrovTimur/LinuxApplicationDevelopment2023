#!/bin/bash
set -eu

FILE="rhasher"

echo -ne test > temp
ans=($(sha1sum temp))

if echo "SHA1 temp" | ./${FILE} | grep -q ${ans}; then
	exit 0
else
	exit 1
fi