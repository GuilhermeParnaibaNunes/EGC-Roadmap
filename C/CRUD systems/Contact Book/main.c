#include "ContactBook.h"

#define ERR_NULL_INPUT      -9
#define ERR_EXCESSIVE_INPUT -10

void clearBuffer(){
  char c;
  while((c = getchar()) != '\n' && c != EOF);
}

int getCleanString(char *string, int size){
  if(fgets(string, size, stdin) == NULL)
        return ERR_NULL_INPUT;

  string[strcspn(string, "\n")] = '\0';

  if(string[0] == '\0')
        return ERR_NULL_INPUT;

  clearBuffer();
  return 1;
}

int isOnlyDigits(char *string){
    for(int i = 0; string[i]; i++)
        if(!isdigit(string[i])){
          printf("\n\t***DEBUG %c\n", string[i]);
          return 0;
        }
    return 1;
}

int main(){
  char inputName[MAX_STRING], upName[MAX_STRING], inputNumber[NUMBER_SIZE], upNumber[NUMBER_SIZE];
  t_Contact auxContact;
  t_ContactBook cBook = InitializeCB();
  t_ContactBook *pCBook = &cBook;
  int sel = 1, pos, validation;

  while(sel){
    printf("\n\t************\n\tSELECTION:\n"
           "\t(1) - Insert new contact;\n"
           "\t(2) - Display contact list;\n"
           "\t(3) - Search a contact;\n"
           "\t\t(3.1) - By position;\n"
           "\t\t(3.2) - By number;\n"
           "\t\t(3.3) - By name;\n"
           "\t\t(3.0) - Exit sub-menu;\n"
           "\t(4) - Update a contact info\n" //STILL TO IMPLEMENT
           "\t\t(4.1) - By position;\n"
           "\t\t(4.2) - By number;\n"
           "\t\t(4.3) - By name;\n"
           "\t\t(4.0) - Exit sub-menu;\n"
           "\t(5) - Delete a contact;\n"
           "\t\t(5.1) - By position;\n"
           "\t\t(5.2) - By number;\n"
           "\t\t(5.3) - By name;\n"
           "\t\t(5.0) - Exit sub-menu;\n"
           "\t(6) - How many contacts do I have in my address book?;\n"
           "\t(7) - How many new contacts can I add to my address book?;\n"
           "\t(0) - Exit\n\n\t");
    scanf("%d", &sel);
    clearBuffer();
    if(!sel)
      continue;
    switch(sel){
      case 1:
        while(1){
          printf("\n\tInsert the new contact name (MAX: %d)\n\t", MAX_STRING-1);
          if(getCleanString(inputName, MAX_STRING)!=1)
            printf("\t*** Please, insert a valid name (MAX NUMBER OF CHARACTERS: %d) ***\n\n"
                   "", MAX_STRING-1);
          else
            break;
        }
        while(1){
          printf("\tInsert the new contact number (%d DIGITS)\n\t", NUMBER_SIZE-1);
          if(getCleanString(inputNumber, NUMBER_SIZE)!=1)
            printf("\t*** Please, insert a valid non null number ***\n\n");
          else if(strlen(inputNumber) != NUMBER_SIZE-1)
            printf("\t*** The number must contain exactly %d digits ***\n\n", NUMBER_SIZE-1);
          else if(!isOnlyDigits(inputNumber))
            printf("\t*** Please, insert a valid only digits number ***\n\n"
                   "", NUMBER_SIZE-1);
          else{
              auxContact = setContact(inputName, inputNumber);
              break;
          }
        }
        validation = insertContactGiven(pCBook, auxContact, pCBook->currentSize);
        if(validation == 1)
          printf("\n\t*** CONTACT INSERTED SUCCESSFULLY! ***\n");
        else
          printInsertError(pCBook->currentSize, validation, pCBook->currentSize);
        break;
      case 2:
        displayList(pCBook);
        break;
      case 3:
        while(sel){ //Sub-menu
          printf("\n\tHow do you want to search for this contact?\n"
               "\t\t(1) - By position;\n"
               "\t\t(2) - By number;\n"
               "\t\t(3) - By name;\n"
               "\t\t(0) - Exit sub-menu\n\n\t");
          scanf("%d", &sel);
          clearBuffer();
          switch(sel){
            case 1:
              printf("\n\tInsert the position of the contact to be searched\n\t");
              scanf("%d", &pos);
              puts("");
              displayContactByPosition(pCBook, pos-1);
              break;
            case 2:
              printf("\n\tInsert the number of the contact to be searched (ONLY THE 11 NUMERIC DIGITS)\n\t");
              getCleanString(inputNumber, NUMBER_SIZE);
              puts("");
              displayContactByNumber(pCBook, inputNumber);
              break;
            case 3:
              printf("\n\tInsert the name of the contact to be searched (MAX: %d)\n\t", MAX_STRING-1);
              getCleanString(inputName, MAX_STRING);
              puts("");
              displayContactByName(pCBook, inputName);
              break;
            case 0:
              printf("\n\t*** EXITING SUB-MENU... ***\n");
              break;
            default:
              printf("\n\t*** INVALID SELECTION ***\n");
          }
        }
        sel = 3;
        break;
      case 4: //ADD OPTIONS "(1) - Change name; (2) - Change number; (3) - Change both; (0) - Exit sub-sub-menu;"
        while(sel){ //Sub-menu
          printf("\n\tHow do you want to search for this contact to be updated?\n"
               "\t\t(1) - By position;\n"
               "\t\t(2) - By number;\n"
               "\t\t(3) - By name;\n"
               "\t\t(0) - Exit sub-menu\n\n\t");
          scanf("%d", &sel);
          clearBuffer();
          switch(sel){
            case 1:
              printf("\n\tInsert the position of the contact to be updated\n\t");
              scanf("%d", &pos);
              puts("");
              while(1){
                printf("\n\tInsert the new contact name (MAX: %d)\n\t", MAX_STRING-1);
                if(getCleanString(inputName, MAX_STRING)!=1)
                  printf("\t*** Please, insert a valid name (MAX NUMBER OF CHARACTERS: %d) ***\n\n"
                         "", MAX_STRING-1);
                else
              break;
              }
              while(1){
                printf("\tInsert the new contact number (%d DIGITS)\n\t", NUMBER_SIZE-1);
                if(getCleanString(inputNumber, NUMBER_SIZE)!=1)
                  printf("\t*** Please, insert a valid non null number ***\n\n");
                else if(strlen(inputNumber) != NUMBER_SIZE-1)
                  printf("\t*** The number must contain exactly %d digits ***\n\n", NUMBER_SIZE-1);
                else if(!isOnlyDigits(inputNumber))
                  printf("\t*** Please, insert a valid only digits number ***\n\n"
                         "", NUMBER_SIZE-1);
                else{
                  auxContact = setContact(inputName, inputNumber);
                  break;
                }
              }
              printf("\n\t*** DEBUG: PRE validation = updateByPosition(pCBook, pos, auxContact);"); ////////////
              validation = updateByPosition(pCBook, pos, auxContact);
              printf("\n\t*** DEBUG: POS validation = updateByPosition(pCBook, pos, auxContact);"); ////////////
              if(validation == 1)
                printf("\n\t*** CONTACT UPDATED SUCCESSFULLY! ***\n");
              else
                printUpdateError(pos, validation, pCBook->currentSize);
              break;
            case 2:
              while(1){
                printf("\tInsert the contact number to be updated (%d DIGITS)\n\t", NUMBER_SIZE-1);
                if(getCleanString(upNumber, NUMBER_SIZE)!=1)
                  printf("\t*** Please, insert a valid non null number ***\n\n");
                else if(strlen(upNumber) != NUMBER_SIZE-1)
                  printf("\t*** The number must contain exactly %d digits ***\n\n", NUMBER_SIZE-1);
                else if(!isOnlyDigits(upNumber))
                  printf("\t*** Please, insert a valid only digits number ***\n\n"
                         "", NUMBER_SIZE-1);
                else{
                  puts("");
                  break;
                }
              }
              while(1){
                printf("\n\tInsert the new contact name (MAX: %d)\n\t", MAX_STRING-1);
                if(getCleanString(inputName, MAX_STRING)!=1)
                  printf("\t*** Please, insert a valid name (MAX NUMBER OF CHARACTERS: %d) ***\n\n"
                         "", MAX_STRING-1);
                else
              break;
              }
              while(1){
                printf("\tInsert the new contact number (%d DIGITS)\n\t", NUMBER_SIZE-1);
                if(getCleanString(inputNumber, NUMBER_SIZE)!=1)
                  printf("\t*** Please, insert a valid non null number ***\n\n");
                else if(strlen(inputNumber) != NUMBER_SIZE-1)
                  printf("\t*** The number must contain exactly %d digits ***\n\n", NUMBER_SIZE-1);
                else if(!isOnlyDigits(inputNumber))
                  printf("\t*** Please, insert a valid only digits number ***\n\n"
                         "", NUMBER_SIZE-1);
                else{
                  auxContact = setContact(inputName, inputNumber);
                  break;
                }
              }
              validation = updateByNumber(pCBook, upNumber, auxContact);
              if(validation == 1)
                printf("\n\t*** CONTACT UPDATED SUCCESSFULLY! ***\n");
              else
                printUpdateError(pos, validation, pCBook->currentSize);
              break;
            case 3:
              while(1){
                printf("\n\tInsert the name of the contact to be updated (MAX: %d)\n\t", MAX_STRING-1);
                if(getCleanString(upName, MAX_STRING)!=1)
                  printf("\t*** Please, insert a valid name (MAX NUMBER OF CHARACTERS: %d) ***\n\n"
                         "", MAX_STRING-1);
                else
                  break;
              }
              puts("");
              while(1){
                printf("\n\tInsert the new contact name (MAX: %d)\n\t", MAX_STRING-1);
                if(getCleanString(inputName, MAX_STRING)!=1)
                  printf("\t*** Please, insert a valid name (MAX NUMBER OF CHARACTERS: %d) ***\n\n"
                         "", MAX_STRING-1);
                else
              break;
              }
              while(1){
                printf("\tInsert the new contact number (%d DIGITS)\n\t", NUMBER_SIZE-1);
                if(getCleanString(inputNumber, NUMBER_SIZE)!=1)
                  printf("\t*** Please, insert a valid non null number ***\n\n");
                else if(strlen(inputNumber) != NUMBER_SIZE-1)
                  printf("\t*** The number must contain exactly %d digits ***\n\n", NUMBER_SIZE-1);
                else if(!isOnlyDigits(inputNumber))
                  printf("\t*** Please, insert a valid only digits number ***\n\n"
                         "", NUMBER_SIZE-1);
                else{
                  auxContact = setContact(inputName, inputNumber);
                  break;
                }
              }
              validation = updateByName(pCBook, upName, auxContact);
              if(validation == 1)
                printf("\n\t*** CONTACT UPDATED SUCCESSFULLY! ***\n");
              else
                printUpdateError(pos, validation, pCBook->currentSize);
              break;
            case 0:
              printf("\n\t*** EXITING SUB-MENU... ***\n");
              break;
            default:
              printf("\n\t*** INVALID SELECTION ***\n");
          }
        }
        sel = 5;
        break;
      case 5:
        while(sel){ //Sub-menu
          printf("\n\tHow do you want to search for this contact to be removed?\n"
               "\t\t(1) - By position;\n"
               "\t\t(2) - By number;\n"
               "\t\t(3) - By name;\n"
               "\t\t(0) - Exit sub-menu\n\n\t");
          scanf("%d", &sel);
          clearBuffer();
          switch(sel){
            case 1:
              printf("\n\tInsert the position of the contact to be removed\n\t");
              scanf("%d", &pos);
              puts("");
              validation = removeByPosition(pCBook, pos-1);
              if(validation == 1)
                printf("\n\t*** CONTACT REMOVED SUCCESSFULLY! ***\n");
              else
                printRemoveError(pos, validation, pCBook->currentSize);
              break;
            case 2:
              printf("\n\tInsert the number of the contact to be removed (ONLY THE 11 NUMERIC DIGITS)\n\t");
              getCleanString(inputNumber, NUMBER_SIZE);
              puts("");
              validation = removeByNumber(pCBook, inputNumber);
              if(validation == 1)
                printf("\n\t*** CONTACT REMOVED SUCCESSFULLY! ***\n");
              else
                printRemoveError(validation, validation, pCBook->currentSize);
              break;
            case 3:
              printf("\n\tInsert the name of the contact to be removed (MAX: %d)\n\t", MAX_STRING-1);
              getCleanString(inputName, MAX_STRING);
              puts("");
              validation = removeByName(pCBook, inputName);
              if(validation == 1)
                printf("\n\t*** CONTACT REMOVED SUCCESSFULLY! ***\n");
              else
                printRemoveError(validation, validation, pCBook->currentSize);
              break;
            case 0:
              printf("\n\t*** EXITING SUB-MENU... ***\n");
              break;
            default:
              printf("\n\t*** INVALID SELECTION ***\n");
          }
        }
        sel = 5;
        break;
      case 6:
        printf("\n\t*--------------------------------*\n"
               "\tYour address book has %d contact(s)\n"
               "\t*--------------------------------*\n", contactCount(pCBook));
        break;
      case 7:
        printf("\n\t*----------------------------------------*\n"
               "\tYour address book has %d contact(s) slot(s)\n"
               "\t*----------------------------------------*\n", remainingSpace(pCBook));
        break;
      default:
        printf("\n\t*** INVALID SELECTION ***\n");
    }
  }

  printf("\n\t*** EXITING SYSTEM... ***\n"
         "\n\tSee you later!\n");

  return 0;
}


/*
1 - Insert new contact
2 - Show all contacts
3 - Search a contact (By name && By number)
4 - Delete a contact (By name && By number)
5 - How many contacts do I have in my address book?
6 - How many new contacts can I add to my address book?
0 - Exit
.*/

//NOT HANDLING ERRORS RIGHT NOW
//HOW SHOULD I HANDLE ERRORS
//GETCLEANSTRING DOES NOT RETURN ANY ERROR
