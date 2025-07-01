#!/bin/bash
for file in "$@"; do
	if [[ -f "$file" ]]; then
		grep -E '^[^a-zA-Z0-9]*$' "$file"
	# se verifica sa nu fie litere mici intre a si z, litere mari intre A si Z si cifre 0-9
	# se afiseaza doar liniile goale, cu spatiu sau cu caractere speciale
	# -E extended
	# se aplica de la inceput ^ pana la sfarsit $
	# * oricate
	else
	 	echo "File $file not found"
	fi
done
