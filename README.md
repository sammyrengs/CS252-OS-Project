# CS252-OS-Project

Project for the CS252 Operating Systems Course (Minors).

## Question: Multithreaded Sorting Application 

This project consists of the solution to Project 2 of Chapter 4 in 
Operating System Concepts, 10th Edition by Abraham Silberschatz, Greg Gagne, Peter B. Galvin

> Write a multithreaded sorting program that works as follows: A list of integers is divided into two smaller lists of equal size. Two separate threads (which we will 
> term sorting threads) sort each sublist using a sorting algorithm of your choice. The two sublists are then merged by a third thread—a merging thread —which merges the 
> two sublists into a single sorted list.

## Solution: 
The solution is in the ch4-project2.cpp file. The pthread library was used to create and manage threads. Two sorting threads sort the first and second half of an array 
respectively using bubble sort. A third thread then merges the two sorted halves into a new array. Parameters were passed to each thread as per the instructions mentioned 
in the question. All the code files have been tested on Ubuntu.

## Execution:
The file can be executed on Linux by entering the following commands:  
      ```
      g++ ch4-project2.cpp -o ch4-project2 -lpthread    
      ./ch4-project2`
      ```
## Screenshots from my terminal:
![Terminal Image](/images/terminal-img.jpeg)
## References:
The code in ch4-project2.cpp is not taken from anywhere. 
I referred to [this link](https://github.com/SLynne/CSc4320_OperatingSystems/blob/master/Assignment_2_SourceCode.c) and the textbook itself to understand the pthread
functions and syntax.



