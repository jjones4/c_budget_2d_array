## c_budget_2d_array

c_budget_2d_array is a simple command line budget app. With c_budget_2d_array, you can create a new transaction, read all transactions, update a transaction, or delete a transaction. The app stores transactions in a file called budget.txt. Take a look at the budget.txt file to see the structure of the data storage system.

To compile and link c_budget_2d_array's source files, I am using GCC and Make. You can compile the app using the following steps:

1. Download all the source files and the makefile into your chosen directory.
2. Point your terminal to the directory.
3. Use the makefile included with c_budget_2d_array to compile and link the source files.
4. If you have installed Make, run the following command: make c_budget_2d_array

Also, you can compile c_budget on Windows using the following command:

- cl -W4 c_budget_2d_array c_budget_2d_array.c crud_operations.c menus.c read_input.c validation.c -link -out:c_budget_2d_array.exe
