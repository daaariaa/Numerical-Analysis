#!/bin/bash

if [ $# -ne 1 ]; then
	echo "trebuie furnizat un argument"
	exit 1
fi

#salvam primul argument
input_file="$1"
#salvam numele directorului unde vom pune toate fisierele
dir_name="dictionary"

#creeaza un director nou cu numele dictionary
#-p daca folderul exista nu da eroare
mkdir -p "$dir_name"

for letter in {A..Z}
do
	#grep cauta cuvinte in fisier
	#-o - only matching - ia doar cuvantul care incepe cu letter, adica litera curenta
	#-i - ignore case
	#\b inceput de cuvant - border
	#/b sfarsit de cuvant
	#sort -f sorteaza alfabetic, ignorand daca sunt litere mari sau mici
	grep -o -i "\b$letter[a-zA-Z]*\b" "$input_file" | sort -f > "$dir_name/$letter.txt"
done


