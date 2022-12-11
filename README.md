# perm

## Download
Download the project by entering this command to the terminal:
```bash
git clone https://github.com/at-eee/perm.git
```
or use the "Download ZIP" option from the [Github](https://github.com/at-eee/perm) page.

## Usage
Open the __user_input.txt__ and enter the number of data samples to generate followed by permutation details in "n m" format, where:\
&nbsp;&nbsp;&nbsp;&nbsp;n - number of permutation elements (max value of 8 due to O(n!) time complexity)\
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

## Error codes:
- 1: not enough permutations listed
- 2: too many permutations listed
- 3: inappriopriate character found in user_input.txt
- 10: couldn't create "make.log" file.
- 11: couldn't change "make.log" file permissions.
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
- 30: Error returned from the pdflatex program.
- 31: Error returned from the cmake program
- 32: Error returned from the make program

