#include "Contact.h"

const t_Contact NULL_CONTACT = {0};

t_Contact setContact(const char *name, const char *number){
  t_Contact contact = NULL_CONTACT; //If anything fails it already stores NULL

  setName(&contact, name);
  setNumber(&contact, number);

  return contact;
}

void setName(t_Contact *contact, const char *name){
  strcpy(contact->name, name);
}

void setNumber(t_Contact *contact, const char *number){
  strcpy(contact->number, number);
}

int isNullContact(t_Contact contact){
    return (contact.name[0] == '\0' || contact.number[0] == '\0');
}

char * toString(t_Contact contact){
  static char contactString[MAX_STRING+32];

  sprintf(contactString, "\t*** %s\n\t*** %s", contact.name, numberToString(contact.number));

  return contactString;
}

char * numberToString(const char *number){
  static char numberString[16];

  sprintf(numberString, "(%.2s) %.5s-%.4s\0", number, number + 2, number + 7);
  //(XX) XXXXX-XXXX
  return numberString;
}
