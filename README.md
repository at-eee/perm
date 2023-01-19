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
* cmake (version 3.25.0 or later)

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

__Note__: user takes resposibility of erroneous program results due to invalid input.

## Error codes
- 1: not enough permutations listed
- 2: too many permutations listed
- 3: inappriopriate character found in user_input.txt
- 4: user requested all permutations of the permutation of length greater than 9.
- 5: user requested permutation of length greater than 10 (too big for the defined buffer i.e: 10).
- 12: couldn't remove "result.tex" (the one created during the last time program was started).
- 13: couldn't create "result.tex" file.
- 14: couldn't change "result.tex" file permissions.
- 15: couldn't create "gen.log" file.
- 16: couldn't change "gen.log" file permissions.
- 17: couldn't remove "result.pdf" (the one created during the last time program was started).
- 18: couldn't create "result.pdf" file.
- 19: couldn't change "result.pdf" file permissions.
- 20: couldn't create "tex.log" file.
- 21: couldn't change "tex.log" file permissions.
- 22: coudln't create CBuild folder or user doesn't have permissions to do so.
- 23: couldn't change permission settings for CBuild folder (and its files/subfolders i.e: Recursively).
- 24: couldn't remove "result.aux" file. (not a critical error).
- 25: couldn't remove "data.txt" file. (not a critical error).
- 26: couldn't move "result.tex" file to "logs/" directory. (not a critical error).
- 27: couldn't create "logs/" directory.
- 28: couldn't remove "logs/" directory from the last program's session.
- 30: Error returned from the pdflatex program.
- 31: Error returned from the cmake program.
- 32: Error returned from the make program.
- 33: Error of the "perm_processing.out" subprogram.
- 34: Error of the "generator.out" subprogram.
- 35: Invalid arguments for the random data generator.
### Error codes related to (additional) testing package:
- 41: couldn't create "test/" directory.
- 42: unable to compile input_checker2.c - Error returned from gcc compiler.
- 43: couldn't copy "testing.sh" file to "test/" directory.
- 44: Amount of requested tests by user is not matching the amount of parameters needed/required.
- 45: User used inappriopriate/disallowed character somewhere in the "parameters.txt" file.
- 46: User requested for testing permutation of length greater than 9.
