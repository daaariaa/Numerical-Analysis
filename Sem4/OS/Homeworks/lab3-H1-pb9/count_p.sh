#!/bin/bash

#verificare daca a fost furnizat un username
if [ $# -ne 1 ]; then #verifica daca nr de argumente este diferit de 1
	echo "utilizare:  $0 <username>" #daca nu este furnizat un argument
	exit 1
fi

#obtine usernameul, se salveaza primul arfument in variabila USERNAME
USERNAME=$1

#numarare procese user
#pgrep cauta procesele care sunt rualte de user
#wc -l numara liniile de iesire, adica procesele
PROCESS_COUNT=$(pgrep -u $USERNAME | wc -l)

#afisare
echo "Utilizatorul $USERNAME are $PROCESS_COUNT procese in executie"

exit 0
