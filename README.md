# perm

Sketch of way how the program works:

1. Subprogram generator1 (Olka) generates permutations.
2. Output from generator1 is passed to another subprogram perm_processing.
3. Subprogram perm_processing processes permutations to extract additional paramaters of these permutations.
4. result.out is passed to bash_script1.sh
5. bash_script1.sh converts and processes result.out for LaTeX and then creates final LaTeX file.
