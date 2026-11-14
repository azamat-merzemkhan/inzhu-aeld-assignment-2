#!/bin/sh
set -eu
if [ "$#" -ne 2 ] || [ ! -d "$1" ]; then
    echo "Usage: $0 filesdir searchstr (filesdir must be a directory)" >&2
    exit 1
fi
files=$(find "$1" -type f -exec sh -c 'for file do printf "x\n"; done' sh {} + | wc -l | tr -d ' ')
lines=$(find "$1" -type f -exec grep -F -h -- "$2" {} + | wc -l | tr -d ' ')
printf 'The number of files are %s and the number of matching lines are %s\n' "$files" "$lines"
