/*
 *
 * Name:       c_budget
 *
 * Purpose:    Keep track of a simple budget in a text file.
 *
 *	       You can create new transactions, display your
 *	       transactions, edit transactions, or delete
 *             transactions.
 *
 *             Each budget record will have the following:
 *
 *             Date, Amount, Type (Credit or Debit), and Description
 *
 * Author:     jjones4
 *
 * Copyright (c) 2022 Jerad Jones
 * This file is part of c_budget_2d_array.  c_budget_2d_array may be
 * freely distributed under the MIT license.  For all details and
 * documentation, see
 *
 * https://github.com/jjones4/c_budget_2d_array
 *
 */



/*
 *
 * Preprocessing directives
 *
 */
#include "c_budget_menus.h"
#include "c_budget_validation.h"
#include "c_budget_read_input.h"
#include "c_budget_crud_operations.h"



/*
 *
 * Main function
 *
 */
int main(void)
{
   FILE *fp;
   char complete_budget[MAX_TRANSACTIONS][MAX_TRANSACTION_LENGTH + 1] = {0};
   char complete_transaction_string[MAX_TRANSACTION_LENGTH + 1] = {0};
   char main_menu_input_string[MENU_INPUT_LENGTH + 1];
   int num_transactions_read = 0;
   int menu_option_to_int;
   int read_input_return_code;
   
   /*
    * Check for the existence of budget.txt
    * Terminate if can't open for reading.
    */
   fp = fopen(FILE_NAME, "r");
   if(fp == NULL)
   {
      printf("\n   File error.\n\n");
      printf("Please ensure %s exists, and try again.\n\n", FILE_NAME);
      return EXIT_FAILURE;
   }
   
   /*
    * Read the transactions from file. Stop filling the 2d array after we
    * reach the max number of transactions. If we can read another transaction,
    * above the max, the file is too large, and we will exit.
    */
   while(
      fgets
         (complete_transaction_string, MAX_TRANSACTION_LENGTH + 1, fp) != NULL
      && num_transactions_read < MAX_TRANSACTIONS + 1)
   {
      /*
       * If we are able to read one transaction above the max, then the file
       * is too big. I'm defining this as a critical error since the program
       * deletes the original file in the Create(), Delete(), and Update()
       * functions and replaces the file data up to (only) the maximum number
       * of transactions defined in THIS application. I don't want to allow
       * the possibility for the user to run this program on a large budget
       * file and possibly lose their data.
       */
      if(num_transactions_read > MAX_TRANSACTIONS - 1)
      {
         printf("\n   There is too much data in the file to read.\n\n");
         printf("   The program will exit.\n\n");
         return EXIT_FAILURE;
      }
      
      /* Put the current line of the text file into our 2d array */
      strcpy(complete_budget[num_transactions_read],
         complete_transaction_string);
         
      num_transactions_read++;
   }
   
   fclose(fp);
   
   for( ;; )
   {
      display_main_menu();
      
      read_input_return_code = read_menu_input(main_menu_input_string);
      
      /* Check to make sure there wasn't an input read error. */
      if(read_input_return_code == -10)
      {
         printf("\nThere was an error reading your input.\n\n");
         printf("Please try again.\n\n");
         continue;
      }
      
      printf("\n");
      
      /* Main menu options */
      if(is_valid_main_menu_option(main_menu_input_string))
      {
         menu_option_to_int = atoi(main_menu_input_string);
         
         if(menu_option_to_int == 1)
         {
            printf("\n\nCreate\n\n");
            /* TODO - test to make sure we can open the file for writing before
            calling Create()
            create_transaction();  */
         }
         else if(menu_option_to_int == 2)
         {
            printf("\n\nRead\n\n");
            /* TODO - test to make sure we can open the file for reading before
            calling Read()
            (void) read_transactions(); */
         }
         else if(menu_option_to_int == 3)
         {
            printf("\n\nUpdate\n\n");
            /* TODO - test to make sure we can open the file for writing before
            calling Update()
            update_transaction(); */
         }
         else if(menu_option_to_int == 4)
         {
            printf("\n\nDelete\n\n");
            /* TODO - test to make sure we can open the file for writing before
            calling Delete()
            delete_transaction(); */
         }
         else if(menu_option_to_int == 5)
         {
            printf("\nOption 5: Save and Quit\n\n");
            return EXIT_SUCCESS;
         }
         else
         {
            printf("Invalid option entered. Please try again.\n");
         }
      }
      else
      {
         printf("Invalid option entered. Please try again.\n");
      }
   }
}



