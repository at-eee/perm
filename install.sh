#!/bin/bash

bug_check(){
#gdzie: $1 to komunikat wypisywany dla uzytkownika, a $2 to error exit code.
	if (($? != 0))
	then 
		echo $1
		exit $2
	fi

}

mkdir CBuild
bug_check 'Nie udalo sie utworzyc folderu CBuild lub uzytkownik nie posiada do tego uprawnien!!!' 22

chmod u+rwx -R CBuild
bug_check 'Nie udalo sie zmienic uprawnien dla Folderu CBuild. Przerywam dzialanie instalatora.' 23

cd CBuild/

cmake ..
bug_check 'Blad programu cmake. Przerywam dzialanie instalatora.' 31

make
bug_check 'Blad programu make podczas kompilacji perm. Przerywam dzialanie instalatora.' 32

cd ..
chmod u+rwx -R CBuild
bug_check 'Nie udalo sie zmienic uprawnien dla Folderu CBuild.' 23