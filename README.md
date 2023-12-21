# Huffman_Coding

## What does the project do?
We will create a text file compression program using Huffman Tree. The program will ask the user if they wish to encode or decode a file, then prompt the user for the file path of the file to open, then prompt the user for a filename to save the new file under. It should then open the file encode or decode the content and save it to the new file path entered. The program should be able to compress the larger text file to almost half their original size.

##Writing to a binary file
The Storage class will take binary string chunks and store them into a binary file. It will also open a binary file and return to you binary string chunks 8 bits at a time. It will also allow storing and reading header information that needed for rebuilding the huffman tree.
