#!/bin/bash

bug_check(){
#gdzie: $1 to komunikat wypisywany dla uzytkownika, $2 to error exit code.
	if (($? != 0))
	then 
		echo $1
		echo 'Przerywam dzialanie instalatora.'
		exit $2
	fi

}

#$1 (dla programu testing.sh to nazwa inputu uzytkownika/pliku konfiguracyjnego).

./test/input_checker2.out parameters.txt
if (($? != 0)); then exit 53; fi #napisane w taki sposob (bez uzycia bug_check), bo komunikat bledu jest wypisywany przez input_checker.out