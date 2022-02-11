# Multi Thread File Read Test

Program to test read operation for a multi thread scenario. 

## Scenario Description

The scenario includes six paragraphs written in a file with indexes as powers of 100 starting from 1. 
Because 1 and 100 are too close, series is violated only for the 2nd paragraph by making its index 1000
instead of 100. In other words, the indexes of paragraphs becomes like this: 

(100^0 = 1), (exception = 1000), (100^2 = 10000), (100^3 = 1000000), ...

Half of the paragraphs is read by one thread and the remaining is by another. The division of the paragraphs
is done according to their order in the file. One thread reads even ordered paragraphs in file: 2nd, 
4th and 6th, while the other thread reads odd ordered ones: 1st, 3rd and 5th. There are meaningless
dummy words between the paragraphs in the file which should be omitted while reading.

## Goal

The aim is to test

 * whether the paragraphs starting at the specified indexes in a text file are read correctly and,
 * whether the arbitrary letters between the paragraphs are omitted by both of the threads.



# Implementation Details

This section explains the details of the code and how it works. 

## The Code

In the code, paragraphs are recorded as char arrays in the beginning, and an array containing all of them is created 
for the sake of ease of use. For the file operations, the program has two functionalities: write to an index and read
from an index in the file. Moreover, the ultimate goal is to check if the reads are correct. That is why, the main 
functionality is to test of read operation in multithreading. Posix threads are used and two different function are created 
to test the correctness of the read operation for two threads. For this tests, see the screen shots of the thread functions below.


![task4-even](https://user-images.githubusercontent.com/60276129/153547859-a010e9f0-bb44-4c9e-9141-e3934c123fff.jpg)



![task4-odd](https://user-images.githubusercontent.com/60276129/153547886-c90a0c5d-13dc-4b08-b3d3-fc301de1c09d.jpg)





# Demo

A step-by-step guide for the usage:
(You can directly jump to step 6 if you want to test the given text)

  1. Define your file name and specify the number of paragraphs.
  2. Add your paragraphs as char arrays in the correct order.
  3. Fill the paragraphs array.
  4. If you want to write your paragraphs to file, use custom_write_to_new_file() function once.
  5. If your file is already written, be sure that paragraph indexes follow the index series (see the series above in the Scenario Description section). 
  6. Compile and run the code as demonstrated in the gif below.
 

![task4](https://user-images.githubusercontent.com/60276129/153550368-35812522-f5a5-45b9-b9ea-e0ccb76052cc.gif)

