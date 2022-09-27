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
 * This file is part of c_budget.  c_budget may be freely distributed
 * under the MIT license.  For all details and documentation, see
 
 * https://github.com/jjones4/c_budget
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
   int num_transactions_read = 0;
   int i;
   
   /* Check for the existence of budget.txt */
   /* Terminate if can't open for reading */
   fp = fopen(FILE_NAME, "r");
   if(fp == NULL)
   {
      printf("\n   File error.\n\n   Please ensure %s exists, and try again.\n\n", FILE_NAME);
      return EXIT_FAILURE;
   }
   
   /* If we can open the file for reading, then we can get a count of
    * the number of transactions in the file */
   while(fgets(complete_transaction_string, MAX_TRANSACTION_LENGTH + 1, fp) != NULL && num_transactions_read < MAX_TRANSACTIONS)
   {
      strcpy(complete_budget[num_transactions_read], complete_transaction_string);
      num_transactions_read++;
   }
   
   for(i = 0; i < num_transactions_read; i++)
   {
      printf("\nComplete transaction string: %s\n", complete_budget[i]);
   }
      
   fclose(fp);
   
   /*
   for( ;; )
   {
      
      char main_menu_input_string[MENU_INPUT_LENGTH + 1];
      int menu_option_to_int;
      
      display_main_menu();
      
      read_menu_input(main_menu_input_string);
      
      printf("\n");
      
      Main menu options
      if(is_valid_main_menu_option(main_menu_input_string))
      {
         menu_option_to_int = atoi(main_menu_input_string);
         
         if(menu_option_to_int == 1)
         {
            TODO - test to make sure we can open the file for writing before
            calling Create()
            create_transaction();
         }
         else if(menu_option_to_int == 2)
         {
            TODO - test to make sure we can open the file for reading before
            calling Create()
            (void) read_transactions();
         }
         else if(menu_option_to_int == 3)
         {
            TODO - test to make sure we can open the file for writing before
            calling Create()
            update_transaction();
         }
         else if(menu_option_to_int == 4)
         {
            TODO - test to make sure we can open the file for writing before
            calling Create()
            delete_transaction();
         }
         else if(menu_option_to_int == 5)
         {
            printf("Option 5: Quit\n\n");
            break;
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
   */
   
   return 0;
}



