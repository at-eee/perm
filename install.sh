#!/bin/bash

location=$(pwd)

bug_check(){
#gdzie: $1 to komunikat wypisywany dla uzytkownika, $2 to error exit code, a $3 to flaga, ktora "mowi" w ktory if nalezy wejsc.
	if (($? != 0 && $3 == 1))
	then 
		echo $1
		echo "badz program jest juz zainstalowany w tym (obecnym) folderze ($location)."
		echo 'Przerywam dzialanie instalatora.'
		exit $2
	fi
	if (($? != 0))
	then
		echo $1
		echo 'Przerywam dzialanie instalatora.'
		exit $2
	fi

}

mkdir build
bug_check 'Nie udalo sie utworzyc folderu build,' 22 1

chmod u+rwx -R build
bug_check 'Nie udalo sie zmienic uprawnien dla Folderu build,' 23 1

cd build/

cmake ..
bug_check 'Blad programu cmake. Przerywam dzialanie instalatora.' 31 0

make
bug_check 'Blad programu make podczas kompilacji perm. Przerywam dzialanie instalatora.' 32 0

cd ..
chmod u+rwx -R build
bug_check 'Nie udalo sie zmienic uprawnien dla Folderu build.' 23 0

echo 'Czy chcesz dodac do programu pakiet do testowania?'
echo 'Wpisz "tak" aby zainstalowac, wpisz cokolwiek innego aby nie instalowac.'
read input
if [ $input = "tak" ]
then
	echo 'instaluje pakiet do testowania...'
fi

mkdir test 
#bug_check 'Nie udalo sie utworzyc folderu build,' ?? 1
#?? - trzeba omowic jakie error code'sy beda dla niego (zwiazane z programem testing.sh) dawane.

cp ./src/testing.sh ./test/
#bug_check 'Nie udalo sie skopiowac programu testing.sh z folderu src/ do folderu test/,' ?? 1

