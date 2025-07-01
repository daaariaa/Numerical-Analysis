#!/bin/bash

#se intereaza prin lista de fisiere primite ca argument
for file in "$@"; do
	if [[ -f "$file" ]]; then
#se verifica daca fisierul exista
		sed -i 's/^..//' "$file"
#sed elimina primele 2 caractere de pe fiecare linie
#s/ face switch intre ^.. primele 2 caractere cu // adica nimic, se sterg
#-i modifica fisierul, fara a face o copie
	else
		echo "File $file not found"
	fi
done

