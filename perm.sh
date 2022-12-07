#!/bin/bash

bug_check(){
#gdzie: $1 to komunikat wypisywany dla uzytkownika, a $2 to error exit code.
	if (($? != 0))
	then 
		echo $1
		exit $2
	fi

}

cd CBuild/

touch make.log
bug_check 'Nie udalo sie utworzyc pliku "make.log".' 10

chmod 766 make.log
bug_check 'Nie udalo sie zmienic uprawnien dla pliku "make.log".' 11

make 2> make.log
cd ..

x=$(head -1 user_input.txt) #pobiera liczbę permutacji do wygenerowania, podaną przez użytkownika.

rm -f result.tex
bug_check 'Nie udalo sie usunac pliku "result.tex" z poprzedniego wykonania programu.' 12

touch result.tex
bug_check 'Nie udalo sie utworzyc pliku "result.tex". Koncze dzialanie programu.' 13

chmod u+rwx result.tex
bug_check 'Nie udalo sie zmienic uprawnien dla pliku "result.tex". Koncze dzialanie programu.' 14

if (($(wc -l user_input.txt | cut -d" " -f1)-1 > $x))
then
	echo 'Podano zbyt wiele polecen/permutacji!!!'
	exit 2
elif (($(wc -l user_input.txt | cut -d" " -f1)-1 < $x))
then
	echo 'Podano zbyt malo permutacji w stosunku do ich podanej ilosci!!!'
	exit 1
fi

./CBuild/input_checker.out user_input.txt
if (($? != 0)); then exit; fi

echo '\documentclass[12pt]{article}' >> result.tex
echo '\usepackage{amsmath}' >> result.tex
echo '\usepackage[T1]{fontenc}' >> result.tex
echo '\usepackage[utf8]{inputenc}' >> result.tex
echo '\usepackage{array}' >> result.tex
echo '\begin{document}' >> result.tex
echo " " >> result.tex
echo '\begin{flushleft}' >> result.tex
echo 'Informacje początkowe:\\[\baselineskip]' >> result.tex
echo "Zażądana ilość osobnych rodzajów permutacji do wygenerowania: $x" >> result.tex
echo '\end{flushleft}' >> result.tex
echo '\hfill' >> result.tex

touch gen.log
bug_check 'Nie udalo sie utworzyc pliku "gen.log". Koncze dzialanie programu.' 15

chmod u+rw gen.log
bug_check 'Nie udalo sie zmienic uprawnien dla pliku "gen.log". Koncze dzialanie programu.' 16

var1=1
while (($var1 <= $x))
do
	head -$(($var1+1)) user_input.txt | tail -1 |./CBuild/generator.out > gen.log
	./CBuild/perm_processing.out $var1
	((var1++))
done

echo '\end{document}' >> result.tex

rm -f result.pdf
bug_check 'Nie udalo sie usunac pliku "result.tex" z poprzedniego wykonania programu.' 17

touch result.pdf
bug_check 'Nie udalo sie usunac pliku "result.tex" z poprzedniego wykonania programu.' 18

chmod u+rwx result.pdf
bug_check 'Nie udalo sie zmienic uprawnien dla pliku "result.tex". Koncze dzialanie programu.' 19

touch tex.log
bug_check 'Nie udalo sie utworzyc pliku "gen.log". Koncze dzialanie programu.' 20

chmod u+rw tex.log
bug_check 'Nie udalo sie zmienic uprawnien dla pliku "gen.log". Koncze dzialanie programu.' 21

pdflatex result.tex > tex.log

bug_check 'Blad programu pdflatex.' 30
