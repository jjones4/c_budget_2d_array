/*
 *
 * Name:       c_budget_2d_array
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
#include "crud_operations.h"
#include "menus.h"
#include "read_input.h"
#include "validation.h"



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
   int number_of_transactions = 0;
   int menu_option_to_int;
   int read_input_return_code;
   
   fp = fopen(FILE_NAME, "r");
   if(fp == NULL)
   {
      printf("\nFile error.\n\n");
      printf("Please ensure %s exists, and try again.\n\n", FILE_NAME);
      return EXIT_FAILURE;
   }
   
   /*
    * Read the transactions from file. Stop filling the 2d array after we
    * reach the max number of transactions. If we can read another transaction,
    * above the max, the file is too large, and we will exit.
    */
   while(fgets(complete_transaction_string, MAX_TRANSACTION_LENGTH + 1, fp) 
      != NULL && number_of_transactions < MAX_TRANSACTIONS + 1)
   {
      /*
       * If we are able to read one transaction above the max, then the file
       * is too big. I'm defining this as a critical error since the program
       * deletes the original file in the Create(), Delete(), and Update()
       * functions and replaces the file's data up to (only) the maximum number
       * of transactions defined in THIS application. I don't want to allow
       * the possibility for the user to run this program on a large budget
       * file and possibly lose their data.
       */
      if(number_of_transactions > MAX_TRANSACTIONS - 1)
      {
         printf("\nThere is too much data in the file to read.\n\n");
         printf("The program will exit.\n\n");
         return EXIT_FAILURE;
      }
      
      /* Put the current line of the text file into our 2d array */
      strcpy(complete_budget[number_of_transactions],
         complete_transaction_string);
         
      number_of_transactions++;
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
            /* 
             * Make sure the number of transactions in our file is LESS
             * than the total number of allowed transactions; otherwise,
             * we can't add a transaction if the file is maxed out.
             */
            if(number_of_transactions < MAX_TRANSACTIONS)
            {
               number_of_transactions = create_transaction(&number_of_transactions,
                  *complete_budget);
            }
            else
            {
               printf("\n\nThe file contains the max number of transactions.\n");
               printf("\nWe cannot add any more transactions.\n");
            }
         }
         else if(menu_option_to_int == 2)
         {
            number_of_transactions =
                  read_transactions(&number_of_transactions, *complete_budget);
         }
         else if(menu_option_to_int == 3)
         {
            /* Check to make sure we have transactions to edit in the file */
            if(number_of_transactions < 1)
            {
               printf("\nNo transactions were found in the file to edit.\n");
               printf("\nPlease create a transaction first.\n");
            }
            else
            {
               number_of_transactions =
                  update_transaction(&number_of_transactions, *complete_budget);
            }
         }
         else if(menu_option_to_int == 4)
         {
            /* Check to make sure we have transactions to delete in the file */
            if(number_of_transactions < 1)
            {
               printf("\nNo transactions were found in the file to delete.\n");
               printf("\nPlease create a transaction first.\n");
            }
            else
            {
               number_of_transactions =
                  delete_transaction(&number_of_transactions, *complete_budget);
            }
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



