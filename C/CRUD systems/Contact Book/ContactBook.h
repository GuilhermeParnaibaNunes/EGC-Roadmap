#include "Contact.h"

/* Validation results */
#define CB_OK                        1
#define CB_NULL_POINTER             -1
#define CB_INVALID_SIZE_OVERFLOW    -2
#define CB_INVALID_SIZE_NEGATIVE    -3

/* CB conditions */
#define FULL_CB                     -4
#define EMPTY_CB                    -5
#define INVALID_POSITION_CB         -6
#define CONTACT_NOT_FOUND           -7
#define NUMBER_ALREADY_EXISTS       -8

#define MAX_CONTACTS                99

/*t_ContactBook structure*/
    // - Contacts field: array of contacts;
    // - CurrentSize field: current number of contacts added;
    // - MaxSize field: max number of contacts it support;
typedef struct ContactBook{
  t_Contact contacts[MAX_CONTACTS];
  int currentSize;
  int maxSize;
} t_ContactBook;

/*Creates an empty Contact Book:*/
    // - Returns a pointer to the ContactBook object;
    // - Takes no parameters.
t_ContactBook InitializeCB(void);

/*Validates the integrity of a contact book:*/
    // - Returns 1 if the contact book is valid;
    // - Returns -1 if the contact book pointer is NULL;
    // - Returns -2 if size is greater than the maximum;
    // - Returns -3 if size is less than zero;
    // - Receives a pointer to the contact book under analysis.
int validateContactBook(t_ContactBook *);

/*Checks if the list has a valid number of elements:*/
    // - Returns 1 if true;
    // - Returns -2 if size is greater than the maximum;
    // - Returns -3 if size is less than zero;
    // - Receives a pointer to the list under analysis.
int isElementNumberValid(t_ContactBook *);

/*Checks if the list is empty:*/
    // - Returns 1 if true;
    // - Returns 0 if false;
    // - Returns VALIDATION RESULTS for invalid element count;
    // - Receives a pointer to the list under analysis.
int isEmpty(t_ContactBook *);

/*Checks if the list is full:*/
    // - Returns 1 if true;
    // - Returns 0 if false;
    // - Returns VALIDATION RESULTS for invalid element count;
    // - Receives a pointer to the list under analysis.
int isFull(t_ContactBook *);

/*Checks if a given position is valid within the contact book:*/
    // - Returns 1 if the position is valid;
    // - Returns 0 if the position is outside the valid range;
    // - Receives a pointer to the contact book under analysis;
    // - Receives the position to be validated.
int isValidPosition(t_ContactBook *, int);

/*Returns total number of saved contacts:*/
    // - Returns VALIDATION RESULTS for invalid element count;
    // - Receives a pointer to the list under analysis.
int contactCount(t_ContactBook *);

/*Returns the number of remaining slots:*/
    // - Returns VALIDATION RESULTS for invalid element count;
    // - Receives a pointer to the list under analysis.
int remainingSpace(t_ContactBook *);

/*Inserts a contact into the contact book using a Contact object:*/
    // - Returns 1 if the procedure was successful;
    // - Returns VALIDATION RESULTS for invalid object;
    // - Returns -4 if the contact book is full;
    // - Returns -6 if the position given is invalid;
    // - Receives a pointer to the contact book under analysis;
    // - Receives a Contact object to be inserted;
    // - Receives the insertion position in the list.
int insertContactGiven(t_ContactBook *, t_Contact, int);

/*Inserts a contact into the contact book using contact information:*/
    // - Returns 1 if the procedure was successful;
    // - Returns VALIDATION RESULTS for invalid object;
    // - Returns -4 if the contact book is full;
    // - Returns -6 if the position given is invalid;
    // - Receives a pointer to the contact book under analysis;
    // - Receives the name of the contact to be inserted;
    // - Receives the phone number of the contact to be inserted;
    // - Receives the insertion position in the list.
int insertContact(t_ContactBook *, char *, char *, int);

/*Displays an error message related to contact insertion:*/
    // - No return value;
    // - Prints a descriptive error message explaining why the insertion failed;
    // - Receives the position used;
    // - Receives the error code returned by the insertion procedure;
    // - Receives the current size of contact list;
    // - Used internally to centralize and standardize error reporting
    //   for insertContact and insertContactGiven operations.
void printInsertError(int, int, int);

/*Updates a contact by position:*/
    // - Returns 1 if the procedure was successful;
    // - Returns VALIDATION RESULTS for invalid object;
    // - Returns -5 if the contact book is empty;
    // - Returns -6 if the position given is invalid;
    // - Receives a pointer to the list under analysis;
    // - Receives the position of the contact to be updated;
    // - Receives the new Contact object to replace the existing one.
int updateByPosition(t_ContactBook *, int, t_Contact);

/*Updates a contact by name:*/
    // - Returns 1 if the procedure was successful;
    // - Returns VALIDATION RESULTS for invalid object;
    // - Returns -5 if the contact book is empty;
    // - Returns -6 if the contact is not found;
    // - Receives a pointer to the list under analysis;
    // - Receives the name of the contact to be updated;
    // - Receives the new Contact object to replace the existing one.
int updateByName(t_ContactBook *, char *, t_Contact);

/*Updates a contact by number:*/
    // - Returns 1 if the procedure was successful;
    // - Returns VALIDATION RESULTS for invalid object;
    // - Returns -5 if the contact book is empty;
    // - Returns -6 if the contact is not found;
    // - Receives a pointer to the list under analysis;
    // - Receives the phone number of the contact to be updated;
    // - Receives the new Contact object to replace the existing one.
int updateByNumber(t_ContactBook *, char *, t_Contact);

/*Displays an error message related to contact updating:*/
    // - No return value;
    // - Prints a descriptive error message explaining why the update failed;
    // - Receives the position used;
    // - Receives the error code returned by the update procedure;
    // - Receives the current size of contact list;
    // - Used internally to centralize and standardize error reporting
    //   for updateByPosition, updateByName and updateByNumber operations.
void printUpdateError(int, int, int);

/*Removes an element from the list by position:*/
    // - Returns 1 if the procedure was successful;
    // - Returns VALIDATION RESULTS for invalid object;
    // - Returns -5 if the contact book is empty;
    // - Returns -6 if the position given is invalid;
    // - Receives a pointer to the list under analysis;
    // - Receives the removal position.
int removeByPosition(t_ContactBook *, int);

/*Removes an element from the list by name:*/
    // - Returns 1 if the procedure was successful;
    // - Returns VALIDATION RESULTS for invalid object;
    // - Returns -5 if the contact book is empty;
    // - Returns -6 if the position given is invalid;
    // - Receives a pointer to the list under analysis;
    // - Receives the name of the contact to be removed.
int removeByName(t_ContactBook *, char *);

/*Removes an element from the list by number:*/
    // - Returns 1 if the procedure was successful;
    // - Returns VALIDATION RESULTS for invalid object;
    // - Returns -5 if the contact book is empty;
    // - Returns -6 if the position given is invalid;
    // - Receives a pointer to the list under analysis;
    // - Receives the phone number of the contact to be removed.
int removeByNumber(t_ContactBook *, char *);

/*Displays an error message related to contact removing:*/
    // - No return value;
    // - Prints a descriptive error message explaining why the remove failed;
    // - Receives the position used;
    // - Receives the error code returned by the remove procedure;
    // - Receives the current size of contact list;
    // - Used internally to centralize and standardize error reporting
    //   for removeByPosition, removeByName and removeByNumber operations.
void printRemoveError(int, int, int);

/*Shifts contacts one position to the right starting from a given position:*/
    // - No return value;
    // - Receives a pointer to the contact book under analysis;
    // - Receives the starting position of the shift;
    // - Moves all contacts from the given position to the end one position to the right;
    // - Used to open space for inserting a new contact.
void rightShift(t_ContactBook *, int);

/*Shifts contacts one position to the left starting from a given position:*/
    // - No return value;
    // - Receives a pointer to the contact book under analysis;
    // - Receives the starting position of the shift;
    // - Moves all contacts after the given position one position to the left;
    // - Used to fill the gap created after removing a contact.
void leftShift(t_ContactBook *, int);

/*Searches for a contact by position:*/
    // - Returns the position of the contact if found;
    // - Returns VALIDATION RESULTS for invalid object;
    // - Returns -6 if the position given is invalid;
    // - Receives a pointer to the contact book under analysis;
    // - Receives the position of the contact to search.
int searchByPosition(t_ContactBook *, int);

/*Searches for a contact by name:*/
    // - Returns the position of the contact if found;
    // - Returns VALIDATION RESULTS for invalid object;
    // - Returns -7 for contact not found;
    // - Receives a pointer to the contact book under analysis;
    // - Receives the name of the contact to search.
int searchByName(t_ContactBook *, char *);

/*Searches for a contact by phone number:*/
    // - Returns the position of the contact if found;
    // - Returns VALIDATION RESULTS for invalid object;
    // - Returns -7 for contact not found;
    // - Receives a pointer to the contact book under analysis;
    // - Receives the phone number of the contact to search.
int searchByNumber(t_ContactBook *, char *);

/*Displays the entire list:*/
    // - No return value;
    // - Receives a pointer to the list.
void displayList(t_ContactBook *);

/*Displays a single contact:*/
    // - No return value;
    // - Receives a Contact object to be displayed;
    // - Prints the contact's information (name and number);
    // - Used internally by displayContactByPosition, displayContactByName,
    //   and displayContactByNumber functions.
void displayContact(t_Contact);

/*Displays a contact by position:*/
    // - No return value;
    // - Receives a pointer to the contact book;
    // - Receives the position of the contact to display.
void displayContactByPosition(t_ContactBook *, int);

/*Displays a contact by name:*/
    // - No return value;
    // - Receives a pointer to the contact book;
    // - Receives the name of the contact to display.
void displayContactByName(t_ContactBook *, char *);

/*Displays a contact by number:*/
    // - No return value;
    // - Receives a pointer to the contact book;
    // - Receives the phone number of the contact to display.
void displayContactByNumber(t_ContactBook *, char *);
