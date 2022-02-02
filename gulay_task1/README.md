
# Task 1: Test for Reading File

## What the Code Does:

This program reads a given text file and tests if the paragraphs in that file are read correctly. For this, paragraphs of the text file are predefined in the beginning. Then, the reading is done and the output paragraphs are compared with the predefined ones. If all the paragraphs are correct, the program outputs the paragraphs with their line indexes.

## Why?

The aim of this code is to test if the paragraphs in the given text file are read correctly.

## How the Code Works:

C programming language is used for this project. The reason for this choice is that it is a base project for the future multiprocess and multithread projects. 
In the code, the array of all the predefined paragraphs is created to be able to iterate the tests. Reading is done through the whole text and all the paragraphs are compared with the prerecorded ones with assert() function. 



# Demo

In this section, a gif displaying the whole code is presented to make understanding easier. You can also find a gif for compilation and run of the code using terminal below in the 'How to use?' section.

## Code

The code includes an array called arrayForAssert to record the paragraphs and iterate all of them while testing. In main(), a buffer to load the lines got from the reading of the text file is created. After opening the file, reading starts in a while loop to cover the whole text file. Two different counter are placed to track both the line index (from file) and the array (arrayForAssert) index. In the if/else part, blank lines are passed and the lines containing paragraphs are tested. Finally the paragraps are printed with the line number that they have in the text file.


![task1_code](https://user-images.githubusercontent.com/60276129/152134780-331b5a7f-d5b5-4c46-9b30-451049971c31.gif)



## How to use?

Step by step guide for usage:

- Define the paragraphs of your text in the beginning.
- Change the defined FILENAME as your file name.
- You can change MAXLEN, if your paragraphs are too long.
- Add your defined paragraphs to arrayForAssert.
- Compile and run the code as demonstrated by the gif below.

That's it, the code will test if your file is read correctly.

![task1_terminal](https://user-images.githubusercontent.com/60276129/152134830-38228804-2d40-4192-a32e-cc2f9bb96218.gif)



