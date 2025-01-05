This library provides following operations:
 - create a set of integers
 - given two sets A,B return
   - their union: A \cup B
   - their intersection: A \cap B
   - A set minus B: A \setminus B

To store set, I use the smallest collection of pairwise disjoint arithmetic sequences of the same difference between consecutive elements. Because of that, each operation is proportional to the sizes of these collections. This greatly reduces time complexity.
