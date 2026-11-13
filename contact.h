#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook,int match[]);
void editContact(AddressBook *addressBook,int match[]);
void deleteContact(AddressBook *addressBook,int match[]);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
int validate_name(char name[]);
int validate_phone(char phone[],AddressBook *AddressBook);
int validate_email(char email[],AddressBook *AddressBook);
int search_name(AddressBook *addressBook,int match[]);
int search_phone(AddressBook *addressBook,int match[]);
int search_email(AddressBook *addressBook,int match[]);

#endif
