#!/bin/bash

bug_check(){
#gdzie: $1 to komunikat wypisywany dla uzytkownika, a $2 to error exit code.
	if (($? != 0))
	then 
		echo $1
		echo 'Przerywam dzialanie programu.'
		exit $2
	fi

}

x=$(head -1 parameters.txt)

if (($(wc -l parameters.txt | cut -d' ' -f1) != $x*2))
then
	echo 'Podana przez uzytkownika liczba typow testow w "parameters.txt", nie zgadza sie z iloscia potrzebnych do nich wykonania argumentow.'
	echo 'Przerywam dzialanie programu.'
	exit 44
fi

#$1 (dla programu input_checker2.out to nazwa inputu uzytkownika/pliku konfiguracyjnego).
cd ..
./bin/input_checker2.out ./test/parameters.txt #<- sprawdzic potem czy to w ogole dziala (taki rodzaj zapisu argumentu).
return_value=$? #value returned by the input_checker2.out subprogram.
if (($return_value == 1)); then exit 45; fi #napisane w taki sposob (bez uzycia bug_check), bo komunikat bledu jest wypisywany przez input_checker.out
if (($return_value == 2)); then exit 46; fi
