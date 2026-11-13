#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include<ctype.h>
//#include "populate.h"

void listContacts(AddressBook *addressBook) 
{

    int choice;
    int i,j;
    Contact temp;
    do
    {
    printf("1. List by name\n");
    printf("2. List by phone number\n");
    printf("3. List by email id\n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    if(choice<1||choice>3)
    {
        printf("Invalid input!!\n");
    }
    }while(choice<1||choice>3);
        if(choice==1)
        {
          for(i=0;i<addressBook->contactCount-1;i++)
          {
            for(j=0;j<addressBook->contactCount - i - 1;j++)
            {
                if(strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;

                }
            }
           
           }
          printf("+--------------------+-----------------+---------------------------+\n");
          printf("| %-18s | %-15s | %-25s |\n", "Name", "Phone", "Email");
          printf("+--------------------+-----------------+---------------------------+\n");

          for(i = 0; i < addressBook->contactCount; i++)
         { 
           printf("| %-18s | %-15s | %-25s |\n",
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);
         }

         printf("+--------------------+-----------------+---------------------------+\n");
        }
        
        else if(choice==2)
        {
          for(i=0;i<addressBook->contactCount-1;i++)
          {
            for(j=0;j<addressBook->contactCount - i - 1;j++)
            {
                if(strcasecmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;

                }
            }
           }
            
            printf("+--------------------+-----------------+---------------------------+\n");
            printf("| %-18s | %-15s | %-25s |\n", "Name", "Phone", "Email");
            printf("+--------------------+-----------------+---------------------------+\n");

            for(i = 0; i < addressBook->contactCount; i++)
            {
            printf("| %-18s | %-15s | %-25s |\n",
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);
            }

            printf("+--------------------+-----------------+---------------------------+\n");
            }
          
        
        
        else if(choice==3)
        {
          for(i=0;i<addressBook->contactCount-1;i++)
          {
            for(j=0;j<addressBook->contactCount - i - 1;j++)
            {
                if(strcasecmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;

                }
            }
            
          }


          printf("+--------------------+-----------------+---------------------------+\n");
          printf("| %-18s | %-15s | %-25s |\n", "Name", "Phone", "Email");
          printf("+--------------------+-----------------+---------------------------+\n");

        for(i = 0; i < addressBook->contactCount; i++)
        {
            printf("| %-18s | %-15s | %-25s |\n",
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);
        }

        printf("+--------------------+-----------------+---------------------------+\n");

        }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    int result;
    do
    {
    printf("Enter the name:");
    scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
    result=validate_name(addressBook->contacts[addressBook->contactCount].name);
    }while(result !=0);



    do
    {
    printf("Enter the phone number:");
    scanf(" %s",addressBook->contacts[addressBook->contactCount].phone);
    result=validate_phone(addressBook->contacts[addressBook->contactCount].phone,addressBook);
    }while(result !=0);
    do
    {
    printf("Enter the email id:");
    scanf(" %s",addressBook->contacts[addressBook->contactCount].email);
    result=validate_email(addressBook->contacts[addressBook->contactCount].email,addressBook);
    }while(result!=0);
    addressBook->contactCount++;

    
}

int searchContact(AddressBook *addressBook,int match[]) 
{
    int choice;
    int result;
    printf("1. Search by name\n");
    printf("2. Search by phone number\n");
    printf("3. Search by email id\n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
        {
          result=search_name(addressBook,match);
        break;
        }
        case 2:
        {
            result=search_phone(addressBook,match);
            break;
        }
        case 3:
        {
            result=search_email(addressBook,match);
            break;
        }
        default:
        {
            printf("Invalid choice\n");
            break;
        }
    }
    return result;
}

void editContact(AddressBook *addressBook,int match[])
{
    printf("Search the contact you want to edit:\n");   
    searchContact(addressBook,match);
    int serial; 
    printf("Select the contact you want to edit:\n");
    scanf("%d",&serial);
    int choice;
    char new[100];
    int result;
    printf("1. Edit by name\n");
    printf("2. Edit by phone number\n");
    printf("3. Edit by email id\n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    switch (choice)
    {
        case 1:
        {
            do
            {
              printf("Enter the new name:");
              scanf(" %[^\n]",new);
              result=validate_name(new);

            } while (result!=0);
            strcpy(addressBook->contacts[match[serial-1]].name,new);
            break;

        }
        case 2:
        {
            do
            {
                 printf("Enter the new phone number:");
                 scanf(" %[^\n]",new);
                 result=validate_phone(new,addressBook);
            } while (result!=0);
            strcpy(addressBook->contacts[match[serial-1]].phone,new);
            break;
        }
        case 3:
        {
            do
            {
                
            printf("Enter the new email id:");
            scanf(" %[^\n]",new);
            result=validate_email(new,addressBook);
            } while (result!=0);
            strcpy(addressBook->contacts[match[serial-1]].email,new);
            break;
        }
    }
    
}

void deleteContact(AddressBook *addressBook,int match[])
{
    printf("Search the contact you want to delete:\n");   
    searchContact(addressBook,match);
    int serial;  
    printf("Select the contact you want to delete:\n");
    scanf("%d",&serial);
    int i;
    for(i=match[serial-1];i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];

    }
    addressBook->contactCount--;
    printf("Successfully deleted..\n");


    
   
}
int validate_name(char name[])
{
    int i;
    if(strlen(name)<2)
    { 
        printf("Invalid name!!name contains less than 2 letter\n");
        return 1; 
    }
    for(i=0;name[i]!='\0';i++)
    {
        if(!isalnum(name[i])&&name[i]!=' ')
        {
            printf("Invalid name!!name contains special characters\n");
            return 1;
        }
    }
    return 0;
}
int validate_phone(char phone[],AddressBook *addressBook)
{
    int i;
    if (strlen(phone)!=10)
    {
        printf("Invalid phone number!!phone number must contain 10 digits\n");
        return 1;
    }
    if(!(phone[0]>='6'&&phone[0]<='9'))
    {
        printf("Invalid phone number!!phone number should start with 6,7,8 or 9\n");
        return 1;
    }
    for(i=0;phone[i]!='\0';i++)
    {
    if(!(phone[i]>='0'&&phone[i]<='9'))
    {
        printf("Invalid phone number!!phone number should contain digits\n");
        return 1;
    } 
    }
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(phone,addressBook->contacts[i].phone)==0)
        {
            printf("Invalid phone number!!phone number already exists\n");
            return 1;
        }
    }
    
    return 0;


}
int validate_email(char email[],AddressBook *addressBook)
{
    int i;
    for(i=0;email[i]!='\0';i++)
    {
    if(email[i]>='A'&&email[i]<='Z')
    {
        printf("Invalid email id!!email id should not contain upper case letter\n");
        return 1;
    }
    }
    if(email[0]=='@')
    {
        printf("Invalid email id!!first character should not be @ \n");
        return 1;
    }
    if(email[0]=='.')
    {
        printf("Invalid email id!!first character should not be .\n");
        return 1;
    }
    char *com=strstr(email, ".com");
    if(com==NULL)
    {
        printf("Invalid email id!!.com not present\n");
        return 1;
    }
     if(*(com+4)!='\0')
     {
        printf("Invalid email id!!characters present after .com\n");
        return 1;
     }
    
     char *ptr=strchr(email,'@');
     if(ptr==NULL)
     {

        printf("Invalid email id!!email id must contain one @ character\n");
        return 1;
     }
     else
     {

     if((ptr+1)==com)
     {
        printf("Invalid email id!!it should contain at least one character between @ and .com\n");
        return 1;
     }
     if(*(ptr+1)=='.')
     {
        printf("Invalid email id!!domain name should not start with '.'\n");
        return 1;

     }
    }
     int count=0;
     for(i=0;email[i]!='\0';i++)
     {
        if('@'==email[i])
        count++;
     }
     if(count>1)
     {
        printf("Invalid email id!!contain more than one @\n");
        return 1;
     }
     if(!isalnum(email[0]))
     {
        printf("Invalid email!!Email start only with alphabet or digits\n");
        return 1;
     }
     for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(email,addressBook->contacts[i].email)==0)
        {
            printf("Invalid email id!!email already exists\n");
            return 1;
        }
    }

     return 0;
}
int search_name(AddressBook *addressBook,int match[])
{
    char name[100];
    printf("Enter the name want to search:");
    scanf(" %[^\n]",name);
    int i;
    int found=0;
    int matchcount=0;
    for(i=0;i<addressBook->contactCount;i++)
    {

    if(strcasestr(addressBook->contacts[i].name,name)!=NULL)
    {
        match[matchcount]=i;
        matchcount++;
        printf("%d. %s\n",matchcount,addressBook->contacts[i].name);
        printf("%s\n",addressBook->contacts[i].phone);
        printf("%s\n",addressBook->contacts[i].email);
        found=1;
    }
    }
    if(found==0)
    {
        printf("Contact not found!!\n");
    }
    return 0;
}
int search_phone(AddressBook *addressBook,int match[])
{
    char name[100];
    printf("Enter the phone number want to search:");
    scanf(" %[^\n]",name);
    int i;
    int found=0;
    int matchcount=0;
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strstr(addressBook->contacts[i].phone,name)!=NULL)
    {
        match[matchcount]=i;
        matchcount++;
        printf("%d. %s\n",matchcount,addressBook->contacts[i].name);
        printf("%s\n",addressBook->contacts[i].phone);
        printf("%s\n",addressBook->contacts[i].email);
        found=1;
        
    }
    }
    if(found==0)
    {
        printf("Contact not found!!");
    }
    return 0;
}
int search_email(AddressBook *addressBook,int match[])
{
    char name[100];
    printf("Enter the email id want to search:");
    scanf(" %[^\n]",name);
    int i;
    int found=0;
    int matchcount=0;
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strstr(addressBook->contacts[i].email,name)!=NULL)
    {
        match[matchcount]=i;
        matchcount++;
        printf("%d. %s\n",matchcount,addressBook->contacts[i].name);
        printf("%s\n",addressBook->contacts[i].phone);
        printf("%s\n",addressBook->contacts[i].email);
        found=1;
        
    }

    }
    if(found==0)
    {
        printf("Contact not found!!");
    }
    return 0;
}

