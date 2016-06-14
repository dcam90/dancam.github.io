Dan Cambitsis

This project is broken down into two segments: hash tables and heaps (binomial queue in our case). 

TO RUN:
make all
HASH: CreateAndTestHash words.txt query_words.txt <flag> (flag is either quadratic, linear, chaining, or double).
HEAP: TestBinomialQueue ##_numbers.txt <flag> (## -> 5, 20, 100, 1000, or 10000, flag is either 0 or 1).

For the hash assignment:
- read words from a text file and insert them into a hash table
- said hash table can be linear, quadratic, double (all probes) or separate chaining
- the program would then print the total # of elements in the table, the size of the table, the load factor,
and the average number of collisions
- compare the hash table with another file (query_words.txt) and if a word in query_words matches with 
a bucket in our hash table, the program would display FOUND and the number of probes used to find the word; if the 
word could not be found, the program would display NOT FOUND and the number of probes used in the process

MY RESULTS:
Linear probing -> elements: 25,143, size of table: 55,609, load factor: .452139, # of collisions: 19,595, average # of collisions: .779
Quadratic probing -> elements: 25,143, size of table: 55,609, load factor: .452139, # of collisions: 16,738, average # of collisions: .666
Double hashing -> elements: 25,143, size of table: 55,609, load factor: .452139, # of collisions: 20,456, average # of collisions: .813

R value used: 3 (a prime number less than 101 [the original size of the table]). 3 yielded the best results in my program. 

Separate chaining -> elements: 25,143, size of table: 27,803, load factor: .904327, no collisions

Overall, I found separate chaining to be the most efficient of the bunch simply because the table size did not grow that large and there
were no collisions (all collisions were chained to its particular bucket). Chaining also used the least amount of probes. Double hashing, 
however, yielded the worst results. 

For the heap assignment: 
PART A:
- if flag is 0:
 - insert integers from a file containing a list of numbers
 - the insert method is timed (in nanoseconds)
 - the DeleteMin() function is then invoked and all minimum values within the heap are deleted 
 until the queue empties (minimum value would display in the console)
- if flag is 1:
 - insert the first quarter of the numbers file into a binomial queue bq1
 - insert the remaining three quarters of the numbers file into a binomial queue bq2
 - time the insert (in nanoseconds)
 - merge bq2 into bq1 and time the merge (in nanoseconds)
 - call DeleteMin() 10 times (minimum value would display in the console)
PART B (NewInsert()):
- similar to A, but instead NewInsert() is called, which is a modified version of Insert() that DOES NOT USE MERGE
- we expect this insert to be more efficient
PART C(NewMerge() and NewInsert()):
- similar to A and B, but instead NewMerge() is called, which is a modified version of Merge()
- we expect this merge to be more efficient 

BUGS/MISHAPS/COMMENTS:
- for the hash implementation, I know that we were told to use public inheritance. I, however, did not. When I attempted to use public inheritance,
my linear and double hashing programs were only reading up to 101 elements. 

For example, my linear.h:
- I included "QuadraticProbing.h" 
- my linear probing class was class LinearHashTable: public HashTable<HashedObj> { ... };
- I made the FindPos() in my quadratic probing class virtual. When I didn't make it virtual, linear/double hashing were calling quadratic probing's
FindPos() function as opposed to their own. I'm assuming that I did something wrong to prevent me from using public inheritance. 

- I was unsure about the last part of the heap implementation. 

For "terminate merging if there are no trees left in H2 and the carry tree is nullptr ...",
my implementation was that if i (the index that is incremented) is larger than rhs' 
tree vector, it means that we have no more trees to read and thus break the for loop. When
debugging this with a cout << "break break break" << endl, nothing ever printed. I then
also tried if (t2 == nullptr && carry == nullptr), break the for loop (I did this based on
the declaration of BinomialNode *t2 in the previous line). This worked but it yielded
weird results. 

Also, merging a smaller tree into a larger tree confused me. I know that we discussed this
in our lecture about union merge so I attempted to implement something similar to that.
Were we supposed to implement a function to find the height of each tree? I based the
size of a tree on its element (i.e. if t2 -> element_ > t1 -> element, swap them). I'm
not entirely sure if I did this correctly.  