#!/bin/bash

bug_check(){
#gdzie: $1 to komunikat wypisywany dla uzytkownika, a $2 to error exit code.
	if (($? != 0))
	then 
		echo $1
		exit $2
	fi

}

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

./build/input_checker.out user_input.txt
if (($? != 0)); then exit 3; fi #napisane w taki sposob (bez uzycia bug_check), bo komunikat bledu jest wypisywany przez input_checker.out

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

rm -rf logs
bug_check 'Nie udalo sie usunac folderu "logs/" z poprzedniej iteracji programu. Koncze dzialanie programu.' 28

mkdir logs
bug_check 'Nie udalo sie utworzyc folderu "logs/". Koncze dzialanie programu.' 27

touch ./logs/gen.log
bug_check 'Nie udalo sie utworzyc pliku "gen.log". Koncze dzialanie programu.' 15

chmod u+rw ./logs/gen.log
bug_check 'Nie udalo sie zmienic uprawnien dla pliku "gen.log". Koncze dzialanie programu.' 16

var1=1
while (($var1 <= $x))
do
	if (($(head -$(($var1+1)) user_input.txt | tail -1 | cut -d ' ' -f 1) > 10))
	then 
		echo 'Uzytkownik zazadal wypisania permutacji o dlugosci wiekszej niz 10!!! Koncze dzialanie programu.' 
		exit 5
	fi
	head -$(($var1+1)) user_input.txt | tail -1 |./build/generator.out > ./logs/gen.log
	if (($? == 7)) 
	then 
		echo 'Uzytkownik zazadal wypisania wszystkich permutacji, permutacji o dlugosci wiekszej niz 9! Koncze dzialanie programu.' 
		exit 4
	fi
	bug_check 'Blad podprogramu generator.out' 34
	./build/perm_processing.out $var1
	bug_check 'Blad podprogramu perm_processing.out' 33
	((var1++))
done

echo '\end{document}' >> result.tex

rm -f result.pdf
bug_check 'Nie udalo sie usunac pliku "result.pdf" z poprzedniego wykonania programu.' 17

touch result.pdf
bug_check 'Nie udalo sie utworzyc pliku "result.pdf". Koncze dzialanie programu.' 18

chmod u+rwx result.pdf
bug_check 'Nie udalo sie zmienic uprawnien dla pliku "result.pdf". Koncze dzialanie programu.' 19

touch ./logs/tex.log
bug_check 'Nie udalo sie utworzyc pliku "tex.log". Koncze dzialanie programu.' 20

chmod u+rw ./logs/tex.log
bug_check 'Nie udalo sie zmienic uprawnien dla pliku "tex.log". Koncze dzialanie programu.' 21

pdflatex result.tex > ./logs/tex.log

bug_check 'Blad programu pdflatex.' 30

rm -f result.aux
bug_check 'Nie udalo sie usunac pliku "result.aux". Koncze dzialanie programu.' 24

rm -f data.txt
bug_check 'Nie udalo sie usunac pliku "data.txt". Koncze dzialanie programu.' 25

mv result.tex logs/
bug_check 'Nie udalo sie przeniesc pliku "result.tex" do folderu "logs/". Koncze dzialanie programu.' 26
