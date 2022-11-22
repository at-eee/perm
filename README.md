# perm

Sketch of way how the program works:

1. User enters desired permutations to generate to user_input.txt in the following (command) format:
   - "x" Number of permutations to generate.
   - "n A" (All permutations of length equal to n (max 8))
   - "n m" (m random permutations of length equal to n).
   - ! "x" command must be entered in the first line of user_input.txt file !
   - ! Every command input must be split by newline character (i.e: "enter") !
2. perm.sh starts and user_input.txt is passed to it.
3. Subprogram generator1 (Olek and Paweł) generates permutations.
4. Output from generator1 is passed to another subprogram perm_processing (Jakub M).
5. Subprogram perm_processing processes permutations to extracts additional paramaters of these permutations and prepares draft version of the final ".tex" file to output (result.out).
6. result.out is passed to perm.sh.
7. perm.sh finally processes result.out to be appropriate for LaTeX.
8. .tex file is created.
