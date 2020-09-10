Valeria Frolova, University of Victoria
Spring 2020

Part 1 - the DoublyLinkedList.c:
No collaboration, written from scratch.
Contains pre-defined node values (as in assignment sample code, as Yvonne told to do)
User input works too, but commented out.

DLL implemented functions:
- swap
- distance
- shift left
- find data
- list content
- user input

Faulty behaviour:
- swap works by swapping pointers. Afterwards displays odd way, 
either not fully or infinite print-out. Must terminate, or disable in the 
code completely.

Other functions work correctly.
--------------------------------------------------------------
Part 2 - The SHELL implementation in C- SEEshrc.c:
read_line() somewhat taken from brennan.io sample tutorial.
Only reads manual user input.

.SEEshrc file reads but incorrectly, this part is commented out.

Reads normally from manual user input for built-in, and not built-in commands.
Displays Process-id for not built-in.

(Simple test path: help --> pwd --> cd .. --> pwd --> ls -al --> exit)