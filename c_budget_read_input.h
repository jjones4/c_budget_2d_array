/*
 *
 * Function Prototypes
 *
 */



#ifndef READ_INPUT_H
#define READ_INPUT_H



#include <stdio.h>
#include <string.h>



#define FILE_NAME "budget.txt"
#define TEMP_FILE_NAME "temp_budget.txt"

#define MAX_TRANSACTIONS 10

/* Set lengths for a transaction and for each part of a transaction */
#define MAX_TRANSACTION_LENGTH 250
#define DATE_LENGTH 10
#define AMOUNT_LENGTH 10
#define TYPE_LENGTH 2
#define DESCRIPTION_LENGTH 220

/* Don't allow Ids greater than 999,999 (six digits) */
#define ID_INPUT_LENGTH 6
#define MENU_INPUT_LENGTH 3

/* Define an integer for file operation errors */
#define FILE_OPS_ERROR -10

void read_menu_input(char *menu_string);
void read_id_input(char *id_string);
void read_date_input(char *date_string);
void read_amount_input(char *amount_string);
void read_type_input(char *type_string);
void read_description_input(char *description_string);



#endif



