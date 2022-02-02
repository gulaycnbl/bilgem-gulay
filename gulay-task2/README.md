# TASK2: Test for Reading File With Given Index


## What the Code Does:

This program reads a given text file and tests if the paragraphs in that file are read correctly. For this, paragraphs of the text file are predefined in the beginning. Then, the reading is done and the output paragraphs are compared with the predefined ones. If all the paragraphs are correct, the program outputs the paragraphs.


## Why? 

The aim is to test 
- whether the paragraphs starting at the specified indexes in a text file are read correctly and,
- whether the arbitrary letters between the paragraphs are omitted. 



# How the Code Works:

C programming language is used for this project. The reason for this choice is that it is a base project for the future multiprocess and multithread projects. 
In the code, paragraps are recorded as char arrays in the beginning. Reading is done according to the given index (see the explanations below) and all the paragraphs are compared with the prerecorded ones with assert() function. 


## Write to a file:

Two functions were implemented to add the given paragraphs according to the given line (1), or the given index (2). The file name can be specified, and different
text files for different test scenarios can be prepared by using customWriteToNewFile() function.

(1) 

![task2_func1](https://user-images.githubusercontent.com/60276129/152140666-2dfb5164-9563-4d47-bd1b-0aabfd169dd2.jpg)


(2)


![task2_func2](https://user-images.githubusercontent.com/60276129/152140826-111fa47a-282d-44bd-adb2-94a98c8a6108.jpg)


## Read from a file:

A function readAndAssertWithIndex(), which can be seen below, is used to read the text file, and assert the readings are correct.

![task2_func3](https://user-images.githubusercontent.com/60276129/152141954-40f55574-0977-44b6-924d-ece2567dbfcb.jpg)



# Demo

In this section, a step-by-step guide for usage of the code is presented to make understanding easier. You can also find a gif for compilation and run of the code using terminal below in the 'How to use?' section.


# How to Use?

Step-by-step guide for usage:

- Define your FILENAME. If you will write to it, it will be created/overwrited. If you want to read it only, you should comment out write function in main().

- Add your paragraphs to write, or assert.

- To write, you should modify customWriteToNewFile() function in any way you want Please see functions (1) and (2) above.

- To read, you should modify readTheParagraphs() function with the correct paragraphs and indexes to test.

- Compile and run it like the following gif.

![task2_terminal](https://user-images.githubusercontent.com/60276129/152143473-1f9b7cfd-87f2-4113-8303-8dc115190ac7.gif)
