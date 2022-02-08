# TASK2: Test for Reading File With Given Index in a Multiprocess Program


## What the Code Does:

This program creates two process reading different sections from a given text file and tests if the paragraphs in that file are read correctly in parallel. 
For this, paragraphs of the text file are predefined in the beginning. Then, the reading is done by two process in parallel and the output 
paragraphs are compared with the predefined ones. Finally, the program outputs the results of assertions.


## Why? 

The aim is to test 
- whether the paragraphs starting at the specified indexes in a text file are read correctly and,
- whether the arbitrary letters between the paragraphs are omitted
by both of the processes. 



# How the Code Works:

C programming language is used for this project. The reason for this choice is that it is a convenient language for multiprocess and multithread projects. 
In the code, paragraps are recorded as char arrays in the beginning. Reading is done according to the given index (see the explanations below) and 
all the paragraphs are compared with the prerecorded ones with assert() function inside the processes. 


## Write to a file:

Two functions were implemented to add the given paragraphs according to the given index (1). The file name can be specified, and different
text files for different test scenarios can be prepared by using customWriteToNewFile() function below (2).

(1) 
For this function, a helper function was needed to fill the gaps between the paragraphs, see the function write_random_n_character() below.

![task3_write](https://user-images.githubusercontent.com/60276129/152981382-971f529f-5152-46a7-8d9f-5d15bd267f4d.jpg)


(2)
The text file is prepared here inside the following function. Paragraphs are placed in the indexes as it can be seen in the picture below.

![task3_customWrite](https://user-images.githubusercontent.com/60276129/152981669-b080abbe-ee85-4eea-8844-486df48eb11c.jpg)






## Read from a file:

A function to read the file indexes and assert their content are correct is given here.


![task3_read](https://user-images.githubusercontent.com/60276129/152982560-8b9db456-4cf0-4489-99ae-6a19c0ad2fbe.jpg)



# Processes with fork() system call

Inside the main(), a child process is created with the fork() system call. Since fork() returns 0 when in the child process, the function execute_child_process() 
is called if it returns 0, and the parent function is called otherwise. See the following second picture for the details of functions.


![task3_main](https://user-images.githubusercontent.com/60276129/152983401-771f3a5d-9745-46cf-b336-6012ad25000a.jpg)


![task3_processes](https://user-images.githubusercontent.com/60276129/152983321-d27b6f6c-08e3-4cf7-bb7f-9e10a48865d6.jpg)



# Demo

In this section, a step-by-step guide for usage of the code is presented to make understanding easier. You can also find a gif for compilation and 
run of the code using terminal below in the 'How to use?' section.


## How to Use?

Step-by-step guide for usage:

- Define your FILENAME.

- Add your paragraphs in the beginning, to write, or assert.

- To write, you should modify custom_write_to_new_file() function in any way you want. Please see functions (1) and (2) above.

- To read, you should modify the paragraphs and indexes of read_and_assert_with_index() functions inside execute functions for processes. 
Replace them with the correct paragraphs and indexes to test.

- Compile and run it either using terminal or the run button like in the following gif:

![task3](https://user-images.githubusercontent.com/60276129/152986905-8d10a725-f393-43d2-bdb6-1d69bc4d37fb.gif)



