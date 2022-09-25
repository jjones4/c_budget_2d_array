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
   for( ;; )
   {
      char main_menu_input_string[MENU_INPUT_LENGTH + 1];
      int menu_option_to_int;
      
      display_main_menu();
      
      read_menu_input(main_menu_input_string);
      
      printf("\n");
      
      /* Main menu option selected */
      if(is_valid_main_menu_option(main_menu_input_string))
      {
         menu_option_to_int = atoi(main_menu_input_string);
         
         if(menu_option_to_int == 1)
         {
            create_transaction();
         }
         else if(menu_option_to_int == 2)
         {
            read_transactions();
         }
         else if(menu_option_to_int == 3)
         {
            update_transaction();
         }
         else if(menu_option_to_int == 4)
         {
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
   
   return 0;
}



