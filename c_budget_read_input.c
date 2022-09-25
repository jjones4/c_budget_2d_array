/*
 *
 * Name:       c_budget_read_input.c
 *
 * Purpose:    Contains functions for reading user input.
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
#include "c_budget_read_input.h"



/*
 *
 * I'm declaring clear_buffer here instead of in a
 * header file because it is only used here (for now)
 *
 */
void clear_buffer(char *buff);



/*
 *
 * IMPORTANT NOTE:
 *
 * I have created separate functions for
 * each type of user input (main menu, date, amount,
 * type of transaction, and description).
 *
 * This is because I want a different buffer size for each
 * function, and c89 does not allow variable length arrays.
 *
 */
 


/*
 *
 * Reads the main menu input
 *
 */
void read_menu_input(char *input_string)
{
   char buff[MENU_INPUT_LENGTH + 1];
   
   if (fgets(buff, MENU_INPUT_LENGTH + 1, stdin))
   {
      strcpy(input_string, buff);
      
      input_string[MENU_INPUT_LENGTH] = '\0';
      
      clear_buffer(buff);
   }
   else
   {
      printf("\nAn error occurred while attempting to read the input.\n");
      
      clear_buffer(buff);
   }
}



/*
 *
 * Reads input for the ID of a transaction
 *
 */
void read_id_input(char *input_string)
{
   char buff[ID_INPUT_LENGTH + 1];
   
   if (fgets(buff, ID_INPUT_LENGTH + 1, stdin))
   {
      strcpy(input_string, buff);
      
      input_string[ID_INPUT_LENGTH] = '\0';
      
      clear_buffer(buff);
   }
   else
   {
      printf("\nAn error occurred while attempting to read the input.\n");
      
      clear_buffer(buff);
   }
}



/*
 *
 * Reads input for the date
 *
 */
void read_date_input(char *input_string)
{
   char buff[DATE_LENGTH + 1];
   
   if (fgets(buff, DATE_LENGTH + 1, stdin))
   {
      strcpy(input_string, buff);
      
      input_string[DATE_LENGTH] = '\0';
      
      clear_buffer(buff);
   }
   else
   {
      printf("\nAn error occurred while attempting to read the input.\n");
      
      clear_buffer(buff);
   }
}



/*
 *
 * Reads input for the amount
 *
 */
void read_amount_input(char *amount_input_string)
{
   char buff[AMOUNT_LENGTH + 1];
   
   if (fgets(buff, AMOUNT_LENGTH + 1, stdin))
   {
      strcpy(amount_input_string, buff);
      
      amount_input_string[AMOUNT_LENGTH] = '\0';
      
      clear_buffer(buff);
   }
   else
   {
      printf("\nAn error occurred while attempting to read the input.\n");
      
      clear_buffer(buff);
   }
}



/*
 *
 * Reads input for the type (credit or debit)
 *
 */
void read_type_input(char *input_string)
{
   char buff[TYPE_LENGTH + 1];
   
   if (fgets(buff, TYPE_LENGTH + 1, stdin))
   {
      strcpy(input_string, buff);
      
      input_string[TYPE_LENGTH] = '\0';
      
      clear_buffer(buff);
   }
   else
   {
      printf("\nAn error occurred while attempting to read the input.\n");
      
      clear_buffer(buff);
   }
}



/*
 *
 * Reads input for the description
 *
 */
void read_description_input(char *input_string)
{
   char buff[DESCRIPTION_LENGTH + 1];
   
   if (fgets(buff, DESCRIPTION_LENGTH + 1, stdin))
   {
      strcpy(input_string, buff);
      
      input_string[DESCRIPTION_LENGTH] = '\0';
      
      clear_buffer(buff);
   }
   else
   {
      printf("\nAn error occurred while attempting to read the input.\n");
      
      clear_buffer(buff);
   }
}



void clear_buffer(char *buff)
{
   char ch;
   char *p = &ch;
   /* Clear the input buffer */
   if((p = strchr(buff, '\n')))
   {
      /* Check if new line exists */
      *p = 0;
   }
   else
   {
      /* Clear up to new line */
      scanf("%*[^\n]");
      scanf("%*c");
   }
}



