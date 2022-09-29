/*
 *
 * Name:       c_budget_crud_operations.c
 *
 * Purpose:    Contains functions for adding, displaying, updating,
 *	       or removing a budget transaction.
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
#include "c_budget_crud_operations.h"
#include "boolean.h"
#include "c_budget_read_input.h"
#include "c_budget_validation.h"
#include "c_budget_menus.h"

char *build_transaction_string(const char *input, char *completed_transaction);
char *parse_transaction_string(char *transaction_field, char *complete_transaction_string);



int create_transaction(int *number_of_transactions, char complete_budget[MAX_TRANSACTION_LENGTH + 1])
{
   FILE *fp;
   int i, j;
   char complete_transaction_string[MAX_TRANSACTION_LENGTH + 1] = {0};
   char date_string[DATE_LENGTH + 1];
   char amount_string[AMOUNT_LENGTH + 1];
   char type_string[TYPE_LENGTH + 1];
   char description_string[DESCRIPTION_LENGTH + 1];
   BOOL valid_amount = FALSE, valid_description = FALSE;
   
   /*
    * Check for the existence of budget.txt
    * Terminate if can't open for appending.
    */
   fp = fopen(FILE_NAME, "a+");
   if(fp == NULL)
   {
      printf("\n   File error.\n\n");
      printf("   Please ensure %s exists, and try again.\n\n", FILE_NAME);
      exit(EXIT_FAILURE);
   }
   
   /* Prompt for and validate date */
   do
   {
      printf("\nEnter the date of the transaction (mm/dd/yyyy). Enter \"b\" to go back: ");
      read_date_input(date_string);
      
      if(*date_string == 'b' || *date_string == 'B')
      {
         printf("\nTransaction has been successfully discarded.\n");
         return *number_of_transactions;
      }
      
      if(!is_valid_date(date_string))
      {
         printf("\nThe date you entered was invalid. Please try again.\n");
      }
   } while(!is_valid_date(date_string));
   
   /* Prompt for and validate amount */
   do
   {
      printf("\nEnter the amount of the transaction. Enter \"b\" to go back: ");
      
      read_amount_input(amount_string);
      
      if(*amount_string == 'b' || *amount_string == 'B')
      {
         printf("\nTransaction has been successfully discarded.\n");
         return *number_of_transactions;
      }

      valid_amount = is_valid_amount(amount_string);
      
      if(!valid_amount)
      {
         printf("\nThe amount you entered was invalid. Please try again.\n");
      }
   } while(!valid_amount);
   
   /* Prompt for and validate type (credit or debit) */
   do
   {
      printf("\nEnter the type of the transaction (0 or 1): Enter \"b\" to go back: ");
      read_type_input(type_string);
      
      if(*type_string == 'b' || *type_string == 'B')
      {
         printf("\nTransaction has been successfully discarded.\n");
         return *number_of_transactions;
      }

      if(!is_valid_type(type_string))
      {
         printf("\nThe type you entered was invalid. Please try again.\n");
      }
   } while(!is_valid_type(type_string));
   
   /* Prompt for and validate description */
   do
   {
      printf("\nEnter the description of the transaction Enter \"b\" to go back: ");
      read_description_input(description_string);
      
      if(*description_string == 'b' || *description_string == 'B')
      {
         printf("\nTransaction has been successfully discarded.\n");
         return *number_of_transactions;
      }

      valid_description = is_valid_description(description_string);
      
      if(!valid_description)
      {
         printf("\nThe description you entered was invalid. Please try again.\n");
      }
   } while(!valid_description);
   
   strcpy(complete_transaction_string, date_string);
   strcat(complete_transaction_string, "|");
   strcat(complete_transaction_string, amount_string);
   strcat(complete_transaction_string, "|");
   strcat(complete_transaction_string, type_string);
   strcat(complete_transaction_string, "|");
   strcat(complete_transaction_string, description_string);
   strcat(complete_transaction_string, "|");
   
   /* Put the new transaction into the 2d array as the last element */
   strcpy(complete_budget + *number_of_transactions * (MAX_TRANSACTION_LENGTH + 1),
      complete_transaction_string);
   
   /* Hancy code for looping through our 2d array */
   /*
   for(j = 0, i = 0; i < (*number_of_transactions + 1) * (MAX_TRANSACTION_LENGTH + 1);)
   {
      printf("\nRecord %d: %s\n", *number_of_transactions, complete_budget + i);
      j++;
      i += (MAX_TRANSACTION_LENGTH + 1);
   }
   */
   
   /* Write record to budget.txt */
   fprintf(fp, "%s", complete_transaction_string);
   fclose(fp);
   
   printf("\nRecord was successfully added.\n");
   
   (*number_of_transactions)++;
   return *number_of_transactions;
}



int read_transactions(void)
{
   FILE *fp;
   char complete_transaction_string[MAX_TRANSACTION_LENGTH + 1];
   char date_string[DATE_LENGTH + 1];
   char amount_string[AMOUNT_LENGTH + 1];
   char type_string[TYPE_LENGTH + 1];
   char description_string[DESCRIPTION_LENGTH + 1];
   char *complete_transaction_string_index;
   int num_transactions_read = 0;
   
   /* Open file stream for budget data text file */
   fp = fopen(FILE_NAME, "r");
   if(fp == NULL) {
      printf("Can't open %s\n", FILE_NAME);
      return -1;
   }
   
   printf("%-10s\t%-11s\t%-10s\t%-5s\t%-50s\n", "Id", "Date", "Amount", "Type", "Description");
   printf("%10s\t%-11s\t%-10s\t%-5s\t%-50s\n", "----------", "-----------", "----------", "-----", "--------------------------------------------------");
   
   while(!feof(fp)) {
      
      
      if(fgets(complete_transaction_string, MAX_TRANSACTION_LENGTH + 1, fp) == NULL)
      {
         fclose(fp);
         return num_transactions_read;
      }
      
      num_transactions_read++;
      
      /* Too many records to display, stop */
      if(num_transactions_read > MAX_TRANSACTIONS)
      {
         fclose(fp);
         printf("\nToo many records were found in the file.\n");
         return num_transactions_read;
      }
      else
      {
         /* Keep track of our position as we read from the complete_transaction_string array */
         complete_transaction_string_index = complete_transaction_string;
   
         complete_transaction_string_index = parse_transaction_string(date_string, complete_transaction_string_index);
         complete_transaction_string_index = parse_transaction_string(amount_string, complete_transaction_string_index);
         complete_transaction_string_index = parse_transaction_string(type_string, complete_transaction_string_index);
         complete_transaction_string_index = parse_transaction_string(description_string, complete_transaction_string_index);
      
         printf("%10d\t%-11s\t%10s\t%5s\t%-50s\n", num_transactions_read, date_string, amount_string, type_string, description_string);
      }
      
      
   }
   
   fclose(fp);

   return num_transactions_read;
}



void update_transaction(void)
{
   FILE *fp;
   FILE* temp_pointer;
   
   char complete_transaction_string[MAX_TRANSACTION_LENGTH + 1];
   char update_complete_transaction_string[MAX_TRANSACTION_LENGTH + 1];
   char id_string[MENU_INPUT_LENGTH + 1];
   char menu_string[MENU_INPUT_LENGTH + 1];
   char date_string[DATE_LENGTH + 1];
   char amount_string[AMOUNT_LENGTH + 1];
   char type_string[TYPE_LENGTH + 1];
   char description_string[DESCRIPTION_LENGTH + 1];
   char *complete_transaction_string_index;
   
   BOOL valid_id = FALSE;
   BOOL valid_date= FALSE;
   BOOL valid_amount = FALSE;
   BOOL valid_description = FALSE;
   
   int num_transactions_read = 0;
   int id = 0;
   
   /* Open file stream for budget data text file */
   fp = fopen(FILE_NAME, "r");
   if(fp == NULL)
   {
      printf("Can't open %s\n", FILE_NAME);
      return;
   }
   
   do
   {
      /* Display the transactions so the user can select one to edit */
      num_transactions_read = read_transactions();
      
      /* Too many records to display, stop */
      if(num_transactions_read > MAX_TRANSACTIONS)
      {
         printf("\nCannot update record.\n");
         return;
      }
   
      printf("\nType the ID of the transaction you would like to edit. Enter \"b\" to go back: ");
      
      read_id_input(id_string);
      
      if(*id_string == 'b' || *id_string == 'B')
      {
         printf("\nTransaction has been successfully discarded.\n");
         return;
      }
      
      /* Convert the character Id entered by the user to int */
      id = atoi(id_string);
      printf("\nYou entered: %d\n", id);
   
      if(id > num_transactions_read || id < 1)
      {
         printf("\nThe id you entered is invalid. Please try again.\n\n");
      }
      else
      {
         valid_id = TRUE;
      }
   } while(!valid_id);
   
   /* Go through the file until we get to the transaction line
    * of the ID that the user gave. We will store this lilne
    * in the complete_transaction_string
    */
   
   /* Open file stream for budget data text file */
   fp = fopen(FILE_NAME, "r");
   if(fp == NULL)
   {
      printf("Can't open %s\n", FILE_NAME);
      return;
   }
   
   while(!feof(fp))
   {
      if(fgets(complete_transaction_string, MAX_TRANSACTION_LENGTH + 1, fp) == NULL)
      {
         printf("\n\n\n%s\n\n\n", complete_transaction_string);
         break;
      }
      
      if(num_transactions_read == id - 1)
      {
         break;
      }
   }

   fclose(fp);
   
   /* Keep track of our position as we read from the complete_transaction_string array */
   complete_transaction_string_index = complete_transaction_string;
   
   complete_transaction_string_index = parse_transaction_string(date_string, complete_transaction_string_index);
   complete_transaction_string_index = parse_transaction_string(amount_string, complete_transaction_string_index);
   complete_transaction_string_index = parse_transaction_string(type_string, complete_transaction_string_index);
   complete_transaction_string_index = parse_transaction_string(description_string, complete_transaction_string_index);
   
   /* Let the user choose which field they want to update */
   do
   {
      display_update_record_menu();
   
      read_menu_input(menu_string);
      
      if(!is_valid_update_menu_option(menu_string))
      {
         printf("\nYou entered an invalid menu option. Please try again.\n");
      }
   } while(!is_valid_update_menu_option(menu_string));
   
   if(*menu_string == '1')
   {
      /* Prompt for and validate date */
      do
      {
         printf("\nEnter the date of the transaction (mm/dd/yyyy). Enter \"b\" to go back: ");
         read_date_input(date_string);
      
         valid_date = is_valid_date(date_string);
      
         if(*date_string == 'b' || *date_string == 'B')
         {
            printf("\nTransaction has been successfully discarded.\n");
            return;
         }
      
         if(!valid_date)
         {
            printf("\nThe date you entered was invalid. Please try again.\n");
         }
         
      } while(!valid_date);
   }
   else if(*menu_string == '2')
   {
      /* Prompt for and validate amount */
      do
      {
         printf("\nEnter the amount of the transaction. Enter \"b\" to go back: ");
         read_amount_input(amount_string);
      
         if(*amount_string == 'b' || *amount_string == 'B')
         {
            printf("\nTransaction has been successfully discarded.\n");
            return;
         }
         
         valid_amount = is_valid_amount(amount_string);
      
         if(!valid_amount)
         {
            printf("\nThe amount you entered was invalid. Please try again.\n");
         }
      } while(!valid_amount);
   }
   else if(*menu_string == '3')
   {
      /* Prompt for and validate type (credit or debit) */
      do
      {
         printf("\nEnter the type of the transaction (0 or 1): Enter \"b\" to go back: ");
         (void) read_type_input(type_string);
      
         if(*type_string == 'b' || *type_string == 'B')
         {
            printf("\nTransaction has been successfully discarded.\n");
            return;
         }

         if(!is_valid_type(type_string))
         {
            printf("\nThe type you entered was invalid. Please try again.\n");
         }
      } while(!is_valid_type(type_string));
   }
   else if(*menu_string == '4')
   {
      /* Prompt for and validate description */
      do
      {
         printf("\nEnter the description of the transaction Enter \"b\" to go back: ");
         (void) read_description_input(description_string);
      
         if(*description_string == 'b' || *description_string == 'B')
         {
            printf("\nTransaction has been successfully discarded.\n");
            return;
         }
         
         valid_description = is_valid_description(description_string);

         if(!valid_description)
         {
            printf("\nThe description you entered was invalid. Please try again.\n");
         }
      } while(!valid_description);
   }
   else if(*menu_string == '5')
   {
      printf("\nChanges were successfully discarded.\n");
      return;
   }
   else
   {
         printf("\nInvalid option entered. Please try again.\n");
   }
   
   /* Rebuild the complete_transaction_string with any new data given
    * by the user
    */
    
   /* Keep track of our position as we fill the complete_transaction_string array */
   complete_transaction_string_index = update_complete_transaction_string;
   
   complete_transaction_string_index = build_transaction_string(date_string, complete_transaction_string_index);
   complete_transaction_string_index = build_transaction_string(amount_string, complete_transaction_string_index);
   complete_transaction_string_index = build_transaction_string(type_string, complete_transaction_string_index);
   complete_transaction_string_index = build_transaction_string(description_string, complete_transaction_string_index);
   
   *complete_transaction_string_index = '\n';
   complete_transaction_string_index++;
   *complete_transaction_string_index = '\0';
   
   /* Move the new data to a temp file
    * Remove the original file, and rename the temp file
    * containing the new data
    */
    
   /* Open temp file stream for budget data text file */
   temp_pointer = fopen(TEMP_FILE_NAME, "w");
   if(temp_pointer == NULL)
   {
      printf("Can't open %s\n", TEMP_FILE_NAME);
      return;
   }
   
   /* Open original file stream for budget data text file */
   fp = fopen(FILE_NAME, "r");
   if(fp == NULL)
   {
      printf("Can't open %s\n", FILE_NAME);
      return;
   }
   
   num_transactions_read = 0;
   
   while(!feof(fp)) {
      
      /* Too many records to display, stop */
      if(num_transactions_read > MAX_TRANSACTIONS)
      {
         printf("Too many records\n");
         break;
      }
      
      if(fgets(complete_transaction_string, MAX_TRANSACTION_LENGTH, fp) == NULL)
      {
         break;
      }
      
      if(num_transactions_read == id - 1)
      {
         fprintf(temp_pointer, "%s", update_complete_transaction_string);
      }
      else
      {
         fprintf(temp_pointer, "%s", complete_transaction_string);
      }
      
      num_transactions_read++;
   }
   
   fclose(temp_pointer);
   fclose(fp);
   remove(FILE_NAME);
   rename(TEMP_FILE_NAME, FILE_NAME);
   printf("\nRecord %d successfully updated!\n", id);
}



void delete_transaction(void)
{
   FILE *fp;
   FILE* temp_pointer;
   
   char complete_transaction_string[MAX_TRANSACTION_LENGTH + 1];
   
   char id_string[MENU_INPUT_LENGTH + 1];
   char menu_string[MENU_INPUT_LENGTH + 1];
   
   BOOL valid_id = FALSE;
   BOOL valid_yes_no = FALSE;
   
   int num_transactions_read = 0;
   int line_number = 0;
   int id = 0;
   
   /* Open file stream for budget data text file */
   fp = fopen(FILE_NAME, "r");
   
   if(fp == NULL)
   {
      printf("Can't open %s\n", FILE_NAME);
      return;
   }
   
   do
   {
      /* Display the transactions so the user can select one to edit */
      int num_transactions_read = read_transactions();
      
      /* Too many records to display, stop */
      if(num_transactions_read > MAX_TRANSACTIONS) {
         printf("\nCannot delete record.\n");
         return;
      }
   
      printf("\nType the ID of the transaction you would like to delete. Enter \"b\" to go back: ");
      
      read_id_input(id_string);
      
      if(*id_string == 'b' || *id_string == 'B')
      {
         fclose(fp);
         printf("\nTransaction has been successfully discarded.\n");
         return;
      }
      
      /* Convert the character Id entered by the user to int */
      id = atoi(id_string);
      printf("\nYou entered: %d\n", id);
   
      if(id > num_transactions_read || id < 1)
      {
         printf("\nThe id you entered is invalid. Please try again.\n\n");
      }
      else
      {
         valid_id = TRUE;
      }
   } while(!valid_id);
   
   do
   {
      printf("\nAre you sure you want to delete record %d (Y/y or N/n): ", id);
      
      read_menu_input(menu_string);
      
      if(
         (*menu_string != 'y' && *menu_string != 'Y')
            &&
         (*menu_string != 'n' && *menu_string != 'N')
        )
      {
         printf("\nYou entered an invalid option. Please try again.\n");
      }
      else
      {
         valid_yes_no = TRUE;
      }
      
   } while(!valid_yes_no);
   
   if(*menu_string == 'y' || *menu_string == 'Y')
   {
      /* Move the new data to a temp file
       * Remove the original file, and rename the temp file
       * containing the new data
       */
    
      /* Open temp file stream for budget data text file */
      temp_pointer = fopen(TEMP_FILE_NAME, "w");
      if(temp_pointer == NULL)
      {
         fclose(fp);
         printf("Can't open %s\n", TEMP_FILE_NAME);
         return;
      }
      
      while(!feof(fp)) {
      
         /* Too many records to display, stop */
         if(num_transactions_read > MAX_TRANSACTIONS)
         {
            printf("Too many records\n");
            break;
         }
      
         if(fgets(complete_transaction_string, MAX_TRANSACTION_LENGTH + 1, fp) == NULL)
         {
            break;
         }
         
         line_number++;
         
         /* Skipe the record we are deleting, so it isn't written to the temp file */
         if(line_number == id)
         {
            num_transactions_read++;
            continue;
         }
         else
         {
            fprintf(temp_pointer, "%s", complete_transaction_string);
         }
      }
      
      fclose(temp_pointer);
      fclose(fp);
      remove(FILE_NAME);
      rename(TEMP_FILE_NAME, FILE_NAME);
      printf("\nRecord %d successfully deleted!\n", id);
   }
   else
   {
      printf("\nTransaction will not be deleted.\n");
   }
}



/* Build a full transaction string from the parts (i.e., the date,
 * amount, type, and description
 */
char *build_transaction_string(const char *input, char *complete_transaction_string)
{
   char *c = complete_transaction_string;
   
   while(*input != '\0')
   {
      *c = *input++;
      c++;
   }
   
   /* Put a pipe after each field (date, amount, etc.) */
   *c = '|';
   c++;
   
   return c;
}



/* Separate a full transaction line from the budget file
 * into its component parts (i.e., date, amount, type,
 * and descirption
 */
char *parse_transaction_string(char *transaction_field, char *complete_transaction_string)
{
   char *p;
   p = transaction_field;
   
   while((*complete_transaction_string != '|') && (*complete_transaction_string))
   {
      *p = *complete_transaction_string++;
      p++;
   }
   
   *p = '\0';
   p = ++complete_transaction_string;
   
   return p;
}



