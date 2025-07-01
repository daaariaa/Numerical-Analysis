#!/bin/bash

for file in "$@"
do
	if [[ -f "$file" ]]; then
		awk '{
			for(i=1; i <= length($0); i++) {
				c = substr($0, i, 1)
				#se extrage pe rand fiecare caracter
				if (c ~ /[a-z]/) l++
				#se verifica daca este litera mica sau mare
				else if (c ~ /[A-Z]/) u++
			}
		}
		END {
			if (l == 0 && u == 0) {
				print FILENAME, "contains no letters"
			} else if (u == 0) {
				print FILENAME, "has ratio: l/u =", l "/0 (only lowercase)"
			} else if (l == 0) {
				print FILENAME, "has ratio: l/u = 0/" u " (only uppercase)"
			} else {
				print FILENAME, "has ratio: l/u =", l "/" u
			}
		}' "$file"
	else
		echo "No such file"
	fi
done
