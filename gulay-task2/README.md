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


![task2_writeLine](https://user-images.githubusercontent.com/60276129/152296087-544ab5af-aa95-41ae-866a-96fdf3c9b1cf.jpg)


(2)

For this function, a helper function was needed to fill the gaps between the paragraphs. See the function write_dummy_string_from_n_character() below.

![task2_writeFileIndex](https://user-images.githubusercontent.com/60276129/152296133-ad831b89-0905-4d11-81ee-5f75df6a4025.jpg)

![task2_dummy_str](https://user-images.githubusercontent.com/60276129/152296589-6ded1cad-75b2-4d93-8ca7-0fc5c7134e66.jpg)




## Read from a file:

A function to read the file indexes and assert their content are correct is used here.


![task2_readAssert](https://user-images.githubusercontent.com/60276129/152296695-bc114ab1-ec1b-4106-a2b1-4be214de771c.jpg)



# Demo

In this section, a step-by-step guide for usage of the code is presented to make understanding easier. You can also find a gif for compilation and run of the code using terminal below in the 'How to use?' section.


# How to Use?

Step-by-step guide for usage:

- Define your FILENAME. If you will write to it, it will be created/overwrited. If you want to read it only, you should comment out write function in main().

- Add your paragraphs to write, or assert.

- To write, you should modify customWriteToNewFile() function in any way you want Please see functions (1) and (2) above.

- To read, you should modify readTheParagraphs() function with the correct paragraphs and indexes to test.

- Compile and run it like the following gif.

![task2](https://user-images.githubusercontent.com/60276129/152297198-d52c6f60-a894-4783-8383-360778dd6c2f.gif)


