# TASK2: Test for File Reading With Given Index

The aim is to test 
- whether the paragraphs starting at the specified indexes in a text file are read correctly and,
- whether the arbitrary letters between the paragraphs are omitted. 

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



# How to Use?

Step-by-step guide for usage:

- Define your FILENAME. If you will write to it, it will be created/overwrited. If you want to read it only, you should comment out write function in main().

- Add your paragraphs to write, or assert.

- To write, you should modify customWriteToNewFile() function in any way you want Please see functions (1) and (2) above.

- To read, you should modify readTheParagraphs() function with the correct paragraphs and indexes to test.

- Compile and run it like the following gif.

![task2_terminal](https://user-images.githubusercontent.com/60276129/152143473-1f9b7cfd-87f2-4113-8303-8dc115190ac7.gif)


## Code


![task2_code](https://user-images.githubusercontent.com/60276129/152143513-2aa36b55-6f12-4b94-acbc-69468339b33d.gif)


