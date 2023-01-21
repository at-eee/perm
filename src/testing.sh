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
((x=x*2+1))

amount=$(wc -w parameters.txt | cut -d' ' -f1)-1 #jest to zmienna przechowujaca laczna ilosc "wyrazow" z parameters.txt "-1" (odjac 1).
#amount of subtests - zrobić taką zmienną?

if (($(wc -l parameters.txt | cut -d' ' -f1) != $x))
then
	echo 'Podana przez uzytkownika liczba typow testow w "parameters.txt", nie zgadza sie z iloscia potrzebnych do nich wykonania argumentow.'
	echo 'Przerywam dzialanie programu.'
	exit 44
fi

#$1 (dla programu input_checker2.out to nazwa inputu uzytkownika/pliku konfiguracyjnego).
cd .. #powrot do katologu glownego perm-main
./bin/input_checker2.out ./test/parameters.txt #<- sprawdzic potem czy to w ogole dziala (taki rodzaj zapisu argumentu).
return_value=$? #value returned by the input_checker2.out subprogram.
if (($return_value == 1)); then exit 45; fi #napisane w taki sposob (bez uzycia bug_check), bo komunikat bledu jest wypisywany przez input_checker.out
if (($return_value == 2)); then exit 46; fi

i=0
export i #bedzie sluzylo (zmienna) do zliczania kolejnych pdf'ow (export i - jest to tak zwana funkcja do przekazania zmiennej procesom podrzednym).
line=2 #sluzy do wskazywania na ktorej linii w parameters.txt obecnie sie znajdujemy.

while (($i < $amount))
do
	if [ $(head -$line ./test/parameters.txt | tail -1 | cut -d ' ' -f1) = 'A' ]
	then
		((line++))
		((i++))
		in1=$(head -$(($line)) ./test/parameters.txt | tail -1) #in1 to skrot od input (in.)
		bug_check 'Blad odczytu z pliku parameters.txt' 49
		#powysza linia wczytuje caly tekst (wszystkie liczby) z danej linijki "parameters.txt" do zmiennej in1 w teorii bedaca tablica liczb (w rzeczywistosci bedacej po prostu tekstem (jak wiele rzeczy w bashu)).
		for var2 in $in1 #tutaj "var2" - jest dlugoscia permutacji (odowiednik dlugosc_permutacji dla 'B' (nie potrzeba nam dodatkowej zmiennej)).
		do
			#cd ..
			echo "1" > user_input.txt
			bug_check 'Nie udalo sie nadpisac pliku user_input.txt' 47
			echo "$var2 A" >> user_input.txt
			#echo "var2:$var2" - ok
			#cat user_input.txt - ok
			time ./perm.sh
			#bug_check 'Nie udalo sie nadpisac pliku user_input.txt' 47
			#wrzuc do user_input.txt potem wykonaj perm i tak dalej
			echo $i
			((i++)) #ta operacja dzieje sie dodatkowo, poniewaz i tak odwolujmy sie do perm za pomoca liczby var2 (z liczb w in1).
		done
		((line++))
	elif [ $(head -$line ./test/parameters.txt | tail -1 | cut -d ' ' -f 1) = 'B' ]
	then
		dlugosc_permutacji=$(head -$(($line)) ./test/parameters.txt | tail -1 | cut -d ' ' -f2)
		((line++))
		in1=$(head -$(($line)) ./test/parameters.txt | tail -1) #in1 to skrot od input (in.)
		#powysza linia wczytuje caly tekst (wszystkie liczby) z danej linijki "parameters.txt" do zmiennej in1 w teorii bedaca tablica liczb (w rzeczywistosci bedacej po prostu tekstem (jak wiele rzeczy w bashu)).
		for var3 in $in1
		do
			echo 'nothing'
			#cos tam, rob rdg, wrzuc do perm cos tam.
			((i++)) #ta operacja dzieje sie dodatkowo, poniewaz i tak odwolujmy sie do perm za pomoca var3.
		done
		((line++))
	fi

	#echo $i
	
	((i++))
done
