# Some Interesting C code

Here are some interesting C codes that I wrote. Among them are:

- `Calendar` :This is a small program that can generate a perpetual calendar, you only need to enter the year, and you will be able to generate a txt file, which is the calendar of that year.

- `factorial` :This is a program for calculating factorials of very large numbers. We used not only C but also C++ and Python programs to solve the problem. We can find that Python runs the fastest, and its special functions are really better than our own implementation.But don't be discouraged! We implement our own program calculation 20000! It didn't take long, and it was a small challenge for us. We're optimizing directly and step-by-step across a variety of different algorithms, which is a step forward. Isn't that interesting?

- `Card games`：This is a card game where customers can think of a number in their minds and look for it in the cards and tell the host the card that contains the number. The host can use these cards to get the number in the customer's mind. This program generates these cards.

- `Sudoku`: V1.0 Traversing all the grids,and this is the least efficient method.

  V2.0 will be more efficient.It find the the largest possibility to solve the puzzle.In this edition,V1.0 have been deleted.  

  **NOTICE: some times it can't solve the puzzle,you can just choose to run this program again.**  

  V2.1:  We also made a small program that automatically generates Sudoku. If you're going to compile, take note! We package the function into a single file, so you need to compile multiple files. For example, the program that compiles and solves Sudoku should be

  ```
  gcc sudoku_v2.c sudoku_func.c -o sudoku2
  gcc generate_sudoku.c sudoku_func.c -o sudoku3
  ```
  **about the "Ke/" part**

  Developed by Ke, a coding enthusiast and good friend of the project owner. And he has a competitive coding background but tends to write code with less-than-ideal clarity. The code may not be well-commented.
  
  *Notice all codes in Ke/ should be compiled into file Ke/, example:*
  ```
  g++ xxx.cpp -o sudoku/Ke/xxx
  ```

I want these programs to be elegant and efficient. Most of these programs (most of which were written by me (YinMo19, the developer of this repository)), have been fully annotated by me, and most of the functions are encapsulated as functions(This function and function are two different things, don't get confused~). A small percentage of the code will be uploaded by other contributors. Those codes may not be commented, and of course I hope they have (smiles).

All this seems so delightful,aren't they? Hope they can help you.

> Anyone who want to add a new program, please contact me :
>
>    QQ 2672690715 
>
>    QQ email 2672690715@qq.com 
>
>    email YinMo19@proton.me
