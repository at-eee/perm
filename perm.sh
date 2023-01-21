#!/bin/bash

bug_check(){
#gdzie: $1 to komunikat wypisywany dla uzytkownika, a $2 to error exit code.
	if (($? != 0))
	then 
		echo $1
		exit $2
	fi

}
if [ -z $i ]
then
	i=0 #sluzy do przypisywania wartosci do nazw kolejnych pdf'ow.
fi

x=$(head -1 user_input.txt) #pobiera liczbę permutacji do wygenerowania, podaną przez użytkownika.

rm -f result$i.tex
bug_check "Nie udalo sie usunac pliku \"result$i.tex\" z poprzedniego wykonania programu." 11

rm -f logs/result$i.tex
bug_check "Nie udalo sie usunac pliku \"logs/result$i.tex\" z poprzedniego wykonania programu." 12

touch result$i.tex
bug_check "Nie udalo sie utworzyc pliku \"result$i.tex\". Koncze dzialanie programu." 13

chmod u+rwx result$i.tex
bug_check "Nie udalo sie zmienic uprawnien dla pliku \"result$i.tex\". Koncze dzialanie programu." 14

if (($(wc -l user_input.txt | cut -d" " -f1)-1 > $x))
then
	echo 'Podano zbyt wiele polecen/permutacji!!!'
	exit 2
elif (($(wc -l user_input.txt | cut -d" " -f1)-1 < $x))
then
	echo 'Podano zbyt malo permutacji w stosunku do ich podanej ilosci!!!'
	exit 1
fi

./bin/input_checker.out user_input.txt
if (($? != 0)); then exit 3; fi #napisane w taki sposob (bez uzycia bug_check), bo komunikat bledu jest wypisywany przez input_checker.out

echo '\documentclass[12pt]{article}' >> result$i.tex
echo '\usepackage{amsmath}' >> result$i.tex
echo '\usepackage[T1]{fontenc}' >> result$i.tex
echo '\usepackage[utf8]{inputenc}' >> result$i.tex
echo '\usepackage{array}' >> result$i.tex
echo '\begin{document}' >> result$i.tex
echo " " >> result$i.tex
echo '\begin{flushleft}' >> result$i.tex
echo 'Informacje początkowe:\\[\baselineskip]' >> result$i.tex
echo "Zażądana ilość osobnych rodzajów permutacji do wygenerowania: $x" >> result$i.tex
echo '\end{flushleft}' >> result$i.tex
echo '\hfill' >> result$i.tex

mkdir -p logs/
bug_check 'Nie udalo sie utworzyc folderu "logs/". Koncze dzialanie programu.' 27

rm -rf logs/logs$i
bug_check "Nie udalo sie usunac podfolderu \"logs/logs$i\" z poprzedniej iteracji programu. Koncze dzialanie programu." 28

mkdir logs/logs$i
bug_check "Nie udalo sie utworzyc podfolderu \"logs/logs$i\". Koncze dzialanie programu." 29

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
	head -$(($var1+1)) user_input.txt | tail -1 | ./bin/generator.out >> ./logs/gen.log
	if (($? == 7)) 
	then 
		echo 'Uzytkownik zazadal wypisania wszystkich permutacji, permutacji o dlugosci wiekszej niz 9! Koncze dzialanie programu.' 
		exit 4
	fi
	bug_check 'Blad podprogramu generator.out' 34
	./bin/perm_processing.out $var1 "result$i.tex"
	bug_check 'Blad podprogramu perm_processing.out' 33
	((var1++))
done

echo '\end{document}' >> result$i.tex

mkdir -p pdfs/
bug_check 'Nie udalo sie utworzyc folderu "pdfs/". Koncze dzialanie programu.' 38

chmod -R 744 pdfs/
bug_check 'Nie udalo sie zmienic uprawnien dla folderu "pdfs/". Koncze dzialanie programu.' 39

rm -f pdfs/result$i.pdf
bug_check "Nie udalo sie usunac pliku \"pdfs/result$i.pdf\" z poprzedniego wykonania programu." 17

touch pdfs/result$i.pdf
bug_check "Nie udalo sie utworzyc pliku \"pdfs/result$i.pdf\". Koncze dzialanie programu." 18

chmod u+rwx pdfs/result$i.pdf
bug_check "Nie udalo sie zmienic uprawnien dla pliku \"pdfs/result$i.pdf\". Koncze dzialanie programu." 19

touch logs/tex$i.log
bug_check "Nie udalo sie utworzyc pliku \"logs/tex.log\". Koncze dzialanie programu." 20

chmod u+rw logs/tex$i.log
bug_check 'Nie udalo sie zmienic uprawnien dla pliku "tex.log". Koncze dzialanie programu.' 21

pdflatex result$i.tex > ./logs/tex$i.log

bug_check 'Blad programu pdflatex.' 30

mv result$i.pdf pdfs/
bug_check "Nie udalo sie przeneisc pliku \"result$i.pdf\" do folderu \"pdfs/\"" 37

rm -f result$i.aux
bug_check 'Nie udalo sie usunac pliku "result.aux".' 24

rm -f data.txt
bug_check 'Nie udalo sie usunac pliku "data.txt".' 25

mv result$i.tex logs/logs$i/
bug_check "Nie udalo sie przeniesc pliku \"result$i.tex\" do folderu \"logs/log$i\"." 26
