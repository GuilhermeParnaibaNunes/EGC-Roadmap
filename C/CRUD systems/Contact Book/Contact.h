#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CONTACT_H_
#define CONTACT_H_

#define MAX_STRING      50
#define NUMBER_SIZE     12

/*t_Contact structure*/
    // - Name field: contact name;
    // - Number field: contact number;
typedef struct Contact{
  char name[MAX_STRING];
  char number[NUMBER_SIZE];
} t_Contact;

/* Null contact constant */
extern const t_Contact NULL_CONTACT;

/*Set a contact:*/
    // - Returns the contact if successful setting;
    // - Returns null contact if failed setting;
    // - Receives contact name;
    // - Receives contact number.
t_Contact setContact(const char *, const char *);

/*Set contact's name:*/
    // - Without return;
    // - Receives contact name;
    // - Sets contact's name.
void setName(t_Contact *, const char *);

/*Set contact's number:*/
    // - Without return;
    // - Receives contact name;
    // - Receives contact number.
void setNumber(t_Contact *, const char *);

/*Transforms Contact info into a String:*/
    // - Returns a String with Contact info;
    // - Receives contact;
char * toString(t_Contact);

/*Format given number into String:*/
    // - Returns a String with formated number;
    // - Receives number;
char * numberToString(const char *);

/*Checks if a contact is null:*/
    // - Returns 1 if the contact is empty (null contact);
    // - Returns 0 if the contact contains valid information;
    // - Receives a Contact object to be analyzed;
    // - A null contact is identified by an empty name field, an empty number field, or both.
int isNullContact(t_Contact);

#endif // CONTACT_H_
