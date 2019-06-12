# Triangle-Counting-Algorithm
This is an triangle counting algorithm based on C. 
Considering that input the graph is too slow and limited. We proposed out algorithm design.   
 0	1
 
 0	2
 
 0	3
 
 1	0
 
 1 	2
 
 2	0
 
 2	1
 
 3	0
 
 Table 1

Fig.2 shows a sample graph that we would use, there is one triangle in it. Table 1 shows the format of the graph file with the Stanford Network Analysis Project. 
The first step is using the int main(int argc, char const *argv[]) function to read the file. 
After opening the file, the second step is to make triangle counting more efficient, we use the mmap() function to build a reflection of the file in the memory. The mmap() function is a C function. By building the reflection in the memory, to modify the data need not read or write operation any more. It is very efficient if there are a bunch of data. 


0	1

0	2

0	3

0	1

1	2

0	2

1	2

0	3

Table 2

Third, sorting the row of table one to make sure that the small one is in the first column. To sort the row, using a for loop and 2 variables. What’s more, we use the OpenMP in the for loop. Table 2 shows the consequence after sorting. 


0	1

0	2

0	3

0	1

1	2

0	2

1	2

0	3

Table 3

Fourth, after sorting, we could count the number of triangle. Before counting, we use the if  first[i]=first[i+1] to make sure the first node of the triangle is same. Then we find the number that two elements of the second column are same as 2 elements of the row. Table 3 shows an example, the italic bold number are the elements we want. 
Fifth, because the repetition, the finding number will be twice. For example, in table 3, the same triangle is found twice time. Therefore, the number of findings need to divide 2 to get the final consequence. 
