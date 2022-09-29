/*
 *
 * Function Prototypes
 *
 */



#ifndef CRUD_OPERATIONS_H
#define CRUD_OPERATIONS_H
#include <stdio.h>
#include "c_budget_read_input.h"

int create_transaction(int *number_of_transactions, char complete_budget[MAX_TRANSACTION_LENGTH + 1]);
int read_transactions(void);
void update_transaction(void);
void delete_transaction(void);

#endif



