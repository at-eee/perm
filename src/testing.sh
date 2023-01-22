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

#rysuje i zapisuje wykresu do chart$chart_count.png
rysuj_wykres(){

	cd test/
	gnuplot instructions_for_gnuplot.p
	mv chart.png chart$chart_count.png
	((chart_count++))
	cd ..
}

#wstawia wykres do pliku test/stat.tex
wstaw_wykres(){

#gdzie $1 to parametr przekazywany funkcji i mowiacy o tym z jakim typem testu mamy do czynienia.

	echo '\begin{figure}[h]' >> test/stat.tex
	echo '\centering' >> test/stat.tex
	echo "\\includegraphics[width=0.60\\textwidth]{chart$(($chart_count-1)).png}" >> test/stat.tex
	echo "\\caption{wykres dla podtestow, testu typu $1.}" >> test/stat.tex
	echo '\end{figure}' >> test/stat.tex

}

#Procedura rozpoczynania tabeli jest taka sama, dla kazdego rodzaju testu.
#Dlatego, w celu "odchudzenia" i zrobienia kodu bardziej czytelnym umieszczono te instrukcje w jednej funkcji.
rozpocznij_rysowanie_tabeli(){

	echo '\begin{table}[h]' >> test/stat.tex
	echo '\centering' >> test/stat.tex
	echo '\begin{tabularx}{0.65\textwidth}{|X|X|}' >> test/stat.tex
	echo '\hline' >> test/stat.tex
	echo 'wielkosc podtestu & czas wykonywania (s) \\' >> test/stat.tex
	echo '\hline' >> test/stat.tex

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
if (($return_value == 1)); then exit 45; fi #napisane w taki sposob (bez uzycia bug_check), bo komunikat bledu jest wypisywany przez input_checker.out sam z siebie.
if (($return_value == 2)); then exit 46; fi

i=0
export i #bedzie sluzylo (zmienna) do zliczania kolejnych pdf'ow (export i - jest to tak zwana funkcja do przekazania zmiennej procesom podrzednym).
line=2 #sluzy do wskazywania na ktorej linii w parameters.txt obecnie sie znajdujemy.

chmod -R u+rwx test/
bug_check 'Nie udalo sie zmienic uprawnien dla folderu "test/"' 50

touch test/stat.tex
bug_check 'Nie udalo sie utworzyc pliku "stat.tex" w folderze "test/"' 51

chmod u+rwx test/stat.tex
bug_check 'Nie udalo sie zmienic uprawnien dla pliku "stat.tex"' 52

echo '\documentclass{article}' > test/stat.tex
echo '\usepackage{graphicx}' >> test/stat.tex
echo '\usepackage{tabularx}' >> test/stat.tex
echo '' >> test/stat.tex
echo '\title{My Document}' >> test/stat.tex
echo '' >> test/stat.tex
echo '\setlength{\intextsep}{10pt}' >> test/stat.tex
echo '\setlength{\textfloatsep}{5pt}' >> test/stat.tex
echo '' >> test/stat.tex
echo '\begin{document}' >> test/stat.tex
echo '' >> test/stat.tex
echo '\maketitle' >> test/stat.tex
echo '' >> test/stat.tex

touch test/for_chart.txt #plik uzywany w celu przechowywania wspolrzednych do wykresu gnuplot'a
bug_check 'Nie udalo sie utworzyc pliku "for_chart.txt" w folderze "test/"' 54

chmod u+rw test/for_chart.txt
bug_check 'Nie udalo sie zmienic uprawnien dla pliku "for_chart.txt"' 55

chart_count=0 #liczba wykresow w naszym folderze "test/" (potrzebnych do generowania pliku .pdf).

while (($i < $amount))
do
	if [ $(head -$line ./test/parameters.txt | tail -1 | cut -d ' ' -f1) = 'A' ]
	then
		((i++))
		((line++))
		echo '\section{Test typu A}' >> test/stat.tex
		#rozpoczyna tabele w pliku test/stat.tex
		rozpocznij_rysowanie_tabeli
		echo '' > test/for_chart.txt #for_chart.txt!
		in1=$(head -$(($line)) ./test/parameters.txt | tail -1) #in1 to skrot od input (in.)
		bug_check 'Blad odczytu z pliku parameters.txt' 49
		#powysza linia wczytuje caly tekst (wszystkie liczby) z danej linii w "parameters.txt" do zmiennej in1 w teorii bedaca tablica liczb (w rzeczywistosci bedacej po prostu tekstem (jak wiele rzeczy w bashu)).
		for var2 in $in1 #tutaj "var2" - jest dlugoscia permutacji (odowiednik dlugosc_permutacji dla 'B' (nie potrzeba nam dodatkowej zmiennej)).
		do
			echo "1" > user_input.txt
			bug_check 'Nie udalo sie nadpisac pliku user_input.txt' 47
			echo "$var2 A" >> user_input.txt
			bug_check 'Nie udalo sie nadpisac pliku user_input.txt' 47
			touch time.txt
			bug_check 'Nie udalo sie utworzyc pliku "time.txt"' 53

			(time ./perm.sh) 2> time.txt
			czas=$(tail -3 time.txt | head -1 | cut -f2)
			echo $czas > time.txt

			milisec=$(grep -o "[0-9][0-9][0-9]" time.txt)
			sec=$(grep -E -o "[0-9]+" time.txt | tail -2 | head -1)
			min=$(grep -E -o "[0-9]+" time.txt | head -1)
			((sec=sec+min*60))
			echo "$var2 $sec.$milisec" >> test/for_chart.txt

			echo "$var2 & $sec.$milisec \\\\" >> test/stat.tex
			echo '\hline' >> test/stat.tex

			echo $i
			((i++)) #ta operacja dzieje sie dodatkowo (by orientowac sie przy ktorym parametrze w pliku parameters.txt jestesmy), poniewaz i tak odwolujmy sie do perm za pomoca liczby var2 (z liczb w in1).
		done
		((line++))
		#zakancza dana tabele
		echo '\end{tabularx}' >> test/stat.tex
		echo '\end{table}' >> test/stat.tex
		#rysowanie i zapisywanie wykresu do chart$chart_count.png
		rysuj_wykres
		#umieszczanie wykresu w pliku test/stat.tex
		wstaw_wykres 'A'

	elif [ $(head -$line ./test/parameters.txt | tail -1 | cut -d ' ' -f 1) = 'B' ]
	then
		echo '\section{Test typu B}' >> test/stat.tex
		#rozpoczyna tabele w pliku test/stat.tex
		rozpocznij_rysowanie_tabeli
		echo '' > test/for_chart.txt #for_chart.txt!
		dlugosc_permutacji=$(head -$(($line)) ./test/parameters.txt | tail -1 | cut -d ' ' -f2)
		bug_check 'Blad odczytu z pliku parameters.txt' 49
		((i+=2))
		((line++))
		in1=$(head -$(($line)) ./test/parameters.txt | tail -1) #in1 to skrot od input (in.)
		#powysza linia wczytuje caly tekst (wszystkie liczby) z danej linijki "parameters.txt" do zmiennej in1 w teorii bedaca tablica liczb (w rzeczywistosci bedacej po prostu tekstem (jak wiele rzeczy w bashu)).
		for var3 in $in1
		do
			echo "1" > user_input.txt
			bug_check 'Nie udalo sie nadpisac pliku user_input.txt' 47
			echo "$dlugosc_permutacji $var3" >> user_input.txt
			bug_check 'Nie udalo sie nadpisac pliku user_input.txt' 47
			touch time.txt
			bug_check 'Nie udalo sie utworzyc pliku "time.txt"' 53

			(time ./perm.sh) 2> time.txt
			czas=$(tail -3 time.txt | head -1 | cut -f2)
			echo $czas > time.txt

			milisec=$(grep -o "[0-9][0-9][0-9]" time.txt)
			sec=$(grep -E -o "[0-9]+" time.txt | tail -2 | head -1)
			min=$(grep -E -o "[0-9]+" time.txt | head -1)
			((sec=sec+min*60))
			echo "$var3 $sec.$milisec" >> test/for_chart.txt

			echo "$var3 & $sec.$milisec \\\\" >> test/stat.tex
			echo '\hline' >> test/stat.tex

			echo $i
			((i++)) #ta operacja dzieje sie dodatkowo (by orientowac sie przy ktorym parametrze w pliku parameters.txt jestesmy), poniewaz i tak odwolujmy sie do perm za pomoca var3.
		done
		((line++))
		#zakancza dana tabele
		echo '\end{tabularx}' >> test/stat.tex
		echo '\end{table}' >> test/stat.tex
		#rysowanie i zapisywanie wykresu do chart$chart_count.png
		rysuj_wykres
		#umieszczanie wykresu w pliku test/stat.tex
		wstaw_wykres 'B'

	fi
	
done

echo '' >> test/stat.tex 
echo '\end{document}' >> test/stat.tex

cd test/

pdflatex stat.tex > tex.log
bug_check 'Blad programu pdflatex.' 53

