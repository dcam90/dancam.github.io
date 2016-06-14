Dan Cambitsis

This project involves reading .txt files, inputting the information from the files into either a BST or an AVL tree,
and manipulating the data. 

For all cases:
- make all to create all files (or make QueryTrees/TestTrees/TestRangeQuery)
- the first 9 lines of the rebase210.txt file are ignored (the header of the file)
- each line is made into a SequenceMap object (each SequenceMap object contains an enzyme acronym and a sequence)
- IF there are duplicates (i.e. two enzymes of the same name) or identical sequences, the enzyme acronyms are merged
- an error prompts if the file doesn't exist or is misspelled 
- an error prompts if the user doesn't provide AVL or BST

The project is broken down into three parts:
PART I
QueryTrees
- in the command prompt, the user enters ./QueryTrees rebase210.txt (the database file) and either AVL or BST
- the program then prompts the user to enter a sequence to searched within the tree
- if the passed by reference "theAcros" returns empty, the sequence could not be found
- otherwise, the program prints all enzymes related to the sequence

PART II 
TestTrees
- in the command prompt, the user enters ./TestTrees rebase210.txt sequences.txt and either AVL or BST
- each line of sequences.txt is processed and if said line is found in the tree, increment successQuery
- afterwards, every other found sequence in the tree is removed from the tree; successRemove is incremented
- in the end, information about each tree is printed (successRemove count, successFind count, node count, sum depth, etc.)

PART III
TestRangeQuery
- in the command prompt, the user enters ./TestTrees rebase210.txt "sequence1" "sequence2"
- "sequence1" and "sequence2" are sequences (ex: ACGT' and ACGGG)
- the program then displays all sequences + their associated enzyme acronyms found in between "sequence1" and "sequence2", including the two entered sequences

BUGS
I am not sure if these results are intended or not but for TestTrees, I am getting 4 more successful queries
in my AVL tree as well as 2 more removals. I'm assuming both trees should have similar success and remove queries? 
  