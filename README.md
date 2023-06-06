# perm

## Download
Download the project by entering this command to the terminal:
```bash
git clone https://github.com/at-eee/perm.git
```
or use the "Download ZIP" option from the [Github](https://github.com/at-eee/perm) page.

## Quick Setup
Required packages:
* pdflatex
* gcc
* g++
* cmake (version 3.10.2 or later)

Make sure to install them by entering those commands to the terminal:
```bash
sudo apt update
sudo apt upgrade
sudo apt install pdflatex gcc g++ cmake
```

Install the program by typing this command to the terminal:
```bash
./install.sh
```

## Usage
Open the __user_input.txt__ and enter the number of data samples to generate followed by permutation details in "n m" format, where:\
&nbsp;&nbsp;&nbsp;&nbsp;n - number of permutation elements (max value of 9 due to O(n!) time complexity)\
&nbsp;&nbsp;&nbsp;&nbsp;m - number of permutations ('A' for all permutations)

<br/>

Sample __user_input.txt__ file:
```txt
5
4 A
3 5
6 2
7 7
5 2
```

### Running the script:
```bash
./perm.sh 
```

## Testing
Testing package allows you to quickly generate many pdf files at the same time, measure the generation time and display the results in a form of a chart.\
To start testing, open the __parameters.txt__ file and enter the number of test samples followed by test details.\
&nbsp;&nbsp;&nbsp;&nbsp;A - number of permutation elements (max value of 9 due to O(n!) time complexity)\
&nbsp;&nbsp;&nbsp;&nbsp;B - many random permutations

<br/>

Sample __parameters.txt__ file:
```txt
3
A
4 5 6
B 6
100 200 300 400 500
B 7
10 50 250 1250
```

__Note__: user takes resposibility of erroneous program results due to invalid input.

## Error codes
- 1: not enough permutations listed
- 2: too many permutations listed
- 3: inappriopriate character found in user_input.txt
- 4: user requested all permutations of the permutation of length greater than 9.
- 5: user requested permutation of length greater than 10 (too big for the defined buffer i.e: 10).
- 11: couldn't remove "result$i.tex" (the temporary one created during the last time program was started).
- 12: couldn't remove "logs/result$i.tex" (the one created during the last time program was started).
- 13: couldn't create "result$i.tex" file.
- 14: couldn't change "result$i.tex" file permissions.
- 15: couldn't create "gen.log" file.
- 16: couldn't change "gen.log" file permissions.
- 17: couldn't remove "pdfs/result$i.pdf" file (the one created during the last time program was started).
- 18: couldn't create "pdfs/result$i.pdf" file.
- 19: couldn't change "pdfs/result$i.pdf" file permissions.
- 20: couldn't create "tex$i.log" file.
- 21: couldn't change "tex$i.log" file permissions.
- 23: couldn't move "result$i.log" file to "logs/logs$i" subdirectory (not a critical error).
- 24: couldn't remove "result.aux" file. (not a critical error).
- 25: couldn't remove "data.txt" file. (not a critical error).
- 26: couldn't move "result$i.tex" file to "logs/logs$i" subdirectory. (not a critical error).
- 27: couldn't create "logs/" directory (or for some reason "mkdir -p directory_name" didn't work properly).
- 28: couldn't remove "logs/logs$i" subdirectory from the last program's session.
- 29: couldn't create "logs/logs$i" subdirectory.
- 30: Error returned from the pdflatex program during creation of "result$i.pdf" file.
- 31: Error returned from the cmake program.
- 32: Error returned from the make program.
- 33: Error of the "perm_processing.out" subprogram.
- 34: Error of the "generator.out" subprogram.
- 35: Invalid arguments for the random data generator or error of random data generator itself.
- 37: couldn't move "result$i.pdf" file to "pdfs/" directory (not a critical error).
- 38: couldn't create "pdfs/" directory (or for some reason "mkdir -p directory_name" didn't work properly).
- 39: unable to change "pdfs/" directory permission settings.
### Error codes related to (additional) testing package:
- 41: couldn't create "test/" directory.
- 42: unable to compile input_checker2.c - Error returned from the gcc compiler.
- 43: couldn't copy "testing.sh" file into "test/" directory.
- 44: Amount of requested tests by user is not matching the amount of parameters needed/required.
- 45: User used inappriopriate/disallowed character somewhere in the "parameters.txt" file.
- 46: User requested for testing permutation of length greater than 9.
- 47: unable to overwrite the "user_input.txt" file during one of the iterations in "testing.sh"
- 48: couldn't move "parameters.txt" file to "test/" directory (not a critical error).
- 49: couldn't perform head or tail function on "parameters.txt" file
- 50: couldn't change directory permissions for "test/" directory.
- 51: couldn't create "stat.tex" file inside the "test/" directory.
- 52: couldn't change file permissions for "test/stat.tex" file.
- 53: couldn't create "time.txt" file (in the perm-main folder).
- 53: Error returned from the pdflatex program during creation of "stat.pdf" file.
- 54: couldn't create "for_chart.txt" file inside the "test/" directory.
- 55: couldn't change file permissions for "test/for_chart.txt" file.
- 56: couldn't copy "instructions_for_gnuplot.p" file to "test/" directory.
- 57: couldn't move stat.pdf from the main directory to the "test/" directory.
- 58: User didn't write size of subtests in "parameters.txt" in increasing (and non-equal) order!
- 59: couldn't pass an argument (file name ("test/parameters.txt")) to "input_checker2.out" or other unspecified error has occured.
- 60: couldn't remove "stat.aux" and/or "stat.log" files (not a critical error).

## Notes:
To anyone ever checking this repository in the future: our teacher was very strict in terms of error-handling (almost obsessive we could say) hence, the amount of error codes :) .
Not that it is something bad - in the end, it is good actually good that it is very bug-proof.
Just felt some sense of responsibility to explain the reason behind the enormous amount of program's error codes to anyone reading this in the future.
