#!/bin/bash

cd CBuild/
make 2> make.log
cd ..

x=$(head -1 user_input.txt) #pobiera liczbę permutacji do wygenerowania, podaną przez użytkownika.

rm -f result.tex


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

var1=1
while (($var1 <= $x))
do
	head -$(($var1+1)) user_input.txt | tail -1 |./CBuild/generator.out > gen.log
	./CBuild/perm_processing.out $var1
	((var1++))
done

echo '\end{document}' >> result.tex

rm -f result.pdf

pdflatex result.tex > tex.log
