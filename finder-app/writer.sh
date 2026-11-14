#!/bin/sh
set -eu
if [ "$#" -ne 2 ]; then echo "Usage: $0 writefile writestr" >&2; exit 1; fi
mkdir -p -- "$(dirname -- "$1")"
printf '%s' "$2" > "$1"
