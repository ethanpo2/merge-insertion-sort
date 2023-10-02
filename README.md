# merge-insertion-sort
## Correctness Test
  ***Usage:** intro.exe k #...
  Where k is the array length the progam will switch from merge to insertion
  and #... is a list of space-separated integer(s)*

  This mode takes is used to make sure that the program is sorting accurately.
  It prints your list of numbers (#... in ***Usage***) to the screen in ascending order.

## Time Test
  ***Usage:** intro.exe t*

  Tests an assortment of k-values (the list-length where the algorithm switches from merge sort to insertion sort).
  Outputs a csv called "introStats.csv" that enumerates the following stats:
  - n, the length of the randomly generated lists.
  - all tested k-values, their 3 recorded runtimes, and their average runtimes
  - the k-value with the best average runtime
  - four sanity tests
    - time taken to sort an ordered list with merge sort
    - time taken to sort an ordered list with insertion sort
    - time taken to sort an unordered list with merge sort
    - time taken to sort an unordered list with insertion sort (bug: this is recorded in csv as an ordered sort, this is wrong)
