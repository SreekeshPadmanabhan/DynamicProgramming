# DynamicProgramming
DynamicProgramming
Given two strings, Y (with n symbols) and X (with m symbols), let us define T[i][j] to be the edit distance between the substrings Y[1,...,j] and X[1,...,i]. If either of these strings is of length 0, the edit distance is simply the length of the longer string. The optimal substructure of the edit distance problem gives the following recursive formula:

T[i][j] =  min(T[i−1][j],T[i][j−1])+1 ifi,j>0andX[i]̸=Y[j]

The table values should be computed row by row starting from the first row and moving down to the bottom row. The purpose of the entire table is to arrive at the value T[m][n] in the bottom right corner, which represents the edit distance between the two strings.
Dynamic programming saves an incredible amount of computation by recording the edit distance between the prefixes of the strings, rather than recomputing them as needed. The brute-force algorithm implicitly recomputes this information over and over again. One problem, however, is that the table requires a lot of memory. Given two input strings of length n and m, the size of the table would be (n+1)(m+1). This can become problematic when the string contain millions of symbols (common in computational biology).
However, storing the entire table is not necessary; we can compute the final edit distance by storing only two rows of the table. If we align a string of length n along the top of the table, the amount of memory required is 2(n+1). This is described as a linear memory algorithm because the amount of memory is linearly proportional to the length of the input strings.
