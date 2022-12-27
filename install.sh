#!/bin/bash

bug_check(){
#gdzie: $1 to komunikat wypisywany dla uzytkownika, a $2 to error exit code.
	if (($? != 0))
	then 
		echo $1
		exit $2
	fi

}

mkdir build
bug_check 'Nie udalo sie utworzyc folderu build lub uzytkownik nie posiada do tego uprawnien!!!' 22

chmod u+rwx -R build
bug_check 'Nie udalo sie zmienic uprawnien dla Folderu build. Przerywam dzialanie instalatora.' 23

cd build/

cmake ..
bug_check 'Blad programu cmake. Przerywam dzialanie instalatora.' 31

make
bug_check 'Blad programu make podczas kompilacji perm. Przerywam dzialanie instalatora.' 32

cd ..
chmod u+rwx -R build
bug_check 'Nie udalo sie zmienic uprawnien dla Folderu build.' 23