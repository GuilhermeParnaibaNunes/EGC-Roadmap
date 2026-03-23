#include "ContactBook.h"

t_ContactBook InitializeCB(void){
  t_ContactBook CB;
  CB.currentSize = 0;
  CB.maxSize = MAX_CONTACTS;
  return CB;
}

int validateContactBook(t_ContactBook *CB){
  if(CB == NULL)
    return CB_NULL_POINTER;

  return isElementNumberValid(CB);
}

int isElementNumberValid(t_ContactBook *CB){
  if(CB->currentSize > CB->maxSize)
    return CB_INVALID_SIZE_OVERFLOW;
  if(CB->currentSize < 0)
    return CB_INVALID_SIZE_NEGATIVE;

  return 1;
}


int isEmpty(t_ContactBook *CB){
  int validation = validateContactBook(CB);

  if(validation != 1)
    return validation;

  return(CB->currentSize == 0);
}

int isFull(t_ContactBook *CB){
  int validation = validateContactBook(CB);

  if(validation != 1)
    return validation;

  return (CB->currentSize == CB->maxSize);
}

int isValidPosition(t_ContactBook *CB, int position){
    if(position < 0 || position > CB->currentSize)
        return 0;

    return 1;
}

int contactCount(t_ContactBook *CB){
  int validation = validateContactBook(CB);

  if(validation == CB_NULL_POINTER){
    printf("\t*** CONTACT BOOK POINTER IS NULL ***\n");
    return validation;
  }else if(validation == CB_INVALID_SIZE_NEGATIVE){
    printf("\t*** CONTACT BOOK INVALID: NEGATIVE SIZE ***\n");
    return validation;
  }else if(validation == CB_INVALID_SIZE_OVERFLOW){
    printf("\t*** CONTACT BOOK INVALID: ELEMENTS OVERFLOW ***\n");
    return validation;
  }

  return CB->currentSize;
}

int remainingSpace(t_ContactBook *CB){
  int cCount = contactCount(CB);

  if(cCount == CB_NULL_POINTER || cCount == CB_INVALID_SIZE_NEGATIVE
     || cCount == CB_INVALID_SIZE_OVERFLOW)
    return cCount;

  return (CB->maxSize) - cCount;
}

int insertContactGiven(t_ContactBook *CB, t_Contact contact, int position){
  int validation = validateContactBook(CB);

  if(validateContactBook(CB) != 1)
    return validation;

  if(isFull(CB))
    return FULL_CB;

  if(!isValidPosition(CB, position))
    return INVALID_POSITION_CB;

  if(searchByNumber(CB, contact.number) >= 0)
    return NUMBER_ALREADY_EXISTS;

  if(position < CB->currentSize)
    rightShift(CB, position);

  CB->contacts[position] = contact;
  CB->currentSize++;

  return 1;
}

int insertContact(t_ContactBook *CB, char *name, char *number, int position){
  return insertContactGiven(CB, setContact(name, number), position);
}

void printInsertError(int position, int errorCode, int currentSize){
    printf("\n\t*** COULD NOT INSERT CONTACT ***\n");

    if(errorCode == CB_NULL_POINTER){
        printf("\t*** CONTACT BOOK POINTER IS NULL ***\n");
    }else if(errorCode == CB_INVALID_SIZE_NEGATIVE){
        printf("\t*** CONTACT BOOK INVALID: NEGATIVE SIZE ***\n");
    }else if(errorCode == CB_INVALID_SIZE_OVERFLOW){
        printf("\t*** CONTACT BOOK INVALID: ELEMENTS OVERFLOW ***\n");
    }else if(errorCode == FULL_CB){
        printf("\t*** CONTACT BOOK IS FULL ***\n");
    }else if(errorCode == NUMBER_ALREADY_EXISTS){
        printf("\t*** NUMBER ALREADY EXISTS ON CONTACT LIST ***\n");
    }else if(errorCode == INVALID_POSITION_CB){
        printf("\t*** POSITION GIVEN IS INVALID [%02d/%02d] ***\n"
               "\t*** POSITION MUST BE %s ***\n",
               position + 1,
               currentSize,
               position < 0 ?
               "A POSITIVE NUMBER" :
               "EITHER EQUAL OR LOWER THAN THE NUMBER OF SLOTS");
    }
}

int updateByPosition(t_ContactBook *CB, int position, t_Contact updatedContact){
  printf("\n\t***DEBUG: PRE validation = searchByName(CB, position)\n");
  int validation = searchByPosition(CB, position);
  printf("\n\t***DEBUG: POS validation = searchByName(CB, position)\n");

  if(validation < 0)
    return validation;

  printf("\n\t*** UPDATING... ***\n\nBEFORE");
  displayContact(CB->contacts[position]);

  CB->contacts[position] = updatedContact;

  printf("\n\t*** UPDATED... ***\n\nAFTER");
  displayContact(CB->contacts[position]);

  return 1;
}

int updateByName(t_ContactBook *CB, char *newName, t_Contact updatedContact){
  int position = searchByName(CB, newName);

  if(position < 0)
    return position;

  printf("\n\t*** UPDATING... ***\n\nBEFORE");
  displayContact(CB->contacts[position]);

  CB->contacts[position] = updatedContact;

  printf("\n\t*** UPDATED... ***\n\nAFTER");
  displayContact(CB->contacts[position]);

  return 1;
}

int updateByNumber(t_ContactBook *CB, char *newNumber, t_Contact updatedContact){
  int position = searchByNumber(CB, newNumber);

  if(position < 0)
    return position;

  printf("\n\t*** UPDATING... ***\n\nBEFORE");
  displayContact(CB->contacts[position]);

  CB->contacts[position] = updatedContact;

  printf("\n\t*** UPDATED... ***\n\nAFTER");
  displayContact(CB->contacts[position]);

  return 1;
}

void printUpdateError(int position, int errorCode, int currentSize){
    printf("\n\t*** COULD NOT UPDATE CONTACT ***\n");

    if(errorCode == CB_NULL_POINTER){
        printf("\t*** CONTACT BOOK POINTER IS NULL ***\n");
    }else if(errorCode == CB_INVALID_SIZE_NEGATIVE){
        printf("\t*** CONTACT BOOK INVALID: NEGATIVE SIZE ***\n");
    }else if(errorCode == CB_INVALID_SIZE_OVERFLOW){
        printf("\t*** CONTACT BOOK INVALID: ELEMENTS OVERFLOW ***\n");
    }else if(errorCode == EMPTY_CB){
        printf("\t*** CONTACT BOOK IS EMPTY ***\n");
    }else if(errorCode == INVALID_POSITION_CB){
        printf("\t*** POSITION GIVEN IS INVALID [%02d/%02d] ***\n"
               "\t*** POSITION MUST BE %s ***\n",
               position,
               currentSize,
               position < 0 ?
               "A POSITIVE NUMBER" :
               "EITHER EQUAL OR LOWER THAN THE NUMBER OF SLOTS");
    }else if(errorCode == CONTACT_NOT_FOUND){
      printf("\t*** CONTACT NOT FOUND ***\n");
    }
}

int removeByPosition(t_ContactBook *CB, int position){
  int validation = searchByPosition(CB, position);

  if(validation < 0)
    return validation;

  printf("\n\t*** REMOVING... ***\n");
  displayContact(CB->contacts[position]);
  leftShift(CB, position);

  CB->contacts[CB->currentSize-1] = NULL_CONTACT; //Clears last slot
  CB->currentSize--;
  return 1;
}

int removeByName(t_ContactBook *CB, char *name){
  int position = searchByName(CB, name);

  if(position < 0)
    return position;

  return removeByPosition(CB, position);
}

int removeByNumber(t_ContactBook *CB, char *number){
  int position = searchByNumber(CB, number);

  if(position < 0)
    return position;

  return removeByPosition(CB, position);
}

void printRemoveError(int position, int errorCode, int currentSize){
  printf("\n\t*** COULD NOT REMOVE CONTACT ***\n");

  if(errorCode == CB_NULL_POINTER){
      printf("\t*** CONTACT BOOK POINTER IS NULL ***\n");
  }else if(errorCode == CB_INVALID_SIZE_NEGATIVE){
      printf("\t*** CONTACT BOOK INVALID: NEGATIVE SIZE ***\n");
  }else if(errorCode == CB_INVALID_SIZE_OVERFLOW){
    printf("\t*** CONTACT BOOK INVALID: ELEMENTS OVERFLOW ***\n");
  }else if(errorCode == EMPTY_CB){
    printf("\t*** CONTACT BOOK IS EMPTY ***\n");
  }else if(errorCode == INVALID_POSITION_CB){
    printf("\t*** POSITION GIVEN IS INVALID [%02d/%02d] ***\n"
           "\t*** POSITION MUST BE %s ***\n",
           position, currentSize, position < 0 ? "A POSITIVE NUMBER" :
               "EITHER EQUAL OR LOWER THAN THE NUMBER OF SLOTS");
  }else if(errorCode == CONTACT_NOT_FOUND){
    printf("\t*** CONTACT NOT FOUND ***\n");
  }
}

void rightShift(t_ContactBook *CB, int position){
  for(int i = CB->currentSize; i > position; i--){
    CB->contacts[i] = CB->contacts[i-1];
  }
}

void leftShift(t_ContactBook *CB, int position){
  for(int i = position; i < CB->currentSize-1; i++){
    CB->contacts[i] = CB->contacts[i+1];
  }
}

int searchByPosition(t_ContactBook *CB, int position){
  int validation = validateContactBook(CB);

  if(validation != 1)
    return validation;

  if(isEmpty(CB))
    return EMPTY_CB;

  if(!isValidPosition(CB, position) || CB->currentSize == position)
    return INVALID_POSITION_CB;

  return position;
}

int searchByName(t_ContactBook *CB, char *name){
  int validation = validateContactBook(CB);

  if(validation != 1)
    return validation;

  for(int i = 0; i < CB->currentSize; i++)
    if(!strcmp(CB->contacts[i].name, name))
      return i;

  return CONTACT_NOT_FOUND;
}

int searchByNumber(t_ContactBook *CB, char *number){
  int validation = validateContactBook(CB);

  if(validation != 1)
    return validation;

  for(int i = 0; i < CB->currentSize; i++)
    if(!strcmp(CB->contacts[i].number, number))
      return i;

  return CONTACT_NOT_FOUND;
}

void displayList(t_ContactBook *CB){
  int validation = validateContactBook(CB);

  if(validation == CB_NULL_POINTER){
    printf("\n\t*** COULD NOT DISPLAY CONTACT LIST ***\n"
           "\t*** CONTACT BOOK POINTER IS NULL ***\n");
    return ;
  }

  if(validation == CB_INVALID_SIZE_NEGATIVE){
    printf("\n\t*** COULD NOT DISPLAY CONTACT LIST ***\n"
           "\t*** CONTACT BOOK INVALID: NEGATIVE SIZE ***\n");
    return ;
  }

  if(validation == CB_INVALID_SIZE_OVERFLOW){
    printf("\n\t*** COULD NOT DISPLAY CONTACT LIST ***\n"
           "\t*** CONTACT BOOK INVALID: ELEMENTS OVERFLOW ***\n");
    return;
  }

  printf("\n\t*** CONTACT BOOK LIST ***\n\n");
  for(int i = 0; i < CB->currentSize; i++){
    printf("[%02d]", i+1);
    displayContact(CB->contacts[i]);
  }

  if(!CB->currentSize)
    printf("\t--- EMPTY LIST ---\n");

  printf("\n\t*** THE END ***\n\n");
}

void displayContact(t_Contact contact){
  printf("\t---------------------\n"
         "%s\n"
         "\t---------------------\n", toString(contact));
}

void displayContactByPosition(t_ContactBook *CB, int position){
  int pos = searchByPosition(CB, position);

  if(pos == CB_NULL_POINTER){
    printf("\n\t*** COULD NOT DISPLAY CONTACT ***\n"
           "\t*** CONTACT BOOK POINTER IS NULL ***\n");
    return ;
  }

  if(pos == CB_INVALID_SIZE_NEGATIVE){
    printf("\n\t*** COULD NOT DISPLAY CONTACT ***\n"
           "\t*** CONTACT BOOK INVALID: NEGATIVE SIZE ***\n");
    return ;
  }

  if(pos == CB_INVALID_SIZE_OVERFLOW){
    printf("\n\t*** COULD NOT DISPLAY CONTACT ***\n"
           "\t*** CONTACT BOOK INVALID: ELEMENTS OVERFLOW ***\n");
    return;
  }

  if(pos == INVALID_POSITION_CB){
    printf("\n\t*** COULD NOT DISPLAY CONTACT ***\n"
           "\t*** POSITION GIVEN IS INVALID ***\n");
    return;
  }

  displayContact(CB->contacts[pos]);
}

void displayContactByName(t_ContactBook *CB, char *name){
  int pos = searchByName(CB, name);

  if(pos == CONTACT_NOT_FOUND){
    printf("\t*** COULD NOT DISPLAY CONTACT ***\n"
           "\t*** CONTACT [%s] NOT FOUND ***\n", name);
    return ;
  }

  displayContact(CB->contacts[pos]);
}

void displayContactByNumber(t_ContactBook *CB, char *number){
  int pos = searchByNumber(CB, number);

  if(pos == CONTACT_NOT_FOUND){
    printf("\n\t*** COULD NOT DISPLAY CONTACT ***\n"
           "\t*** CONTACT [%s] NOT FOUND ***\n", number);
    return ;
  }

  displayContact(CB->contacts[pos]);
}
