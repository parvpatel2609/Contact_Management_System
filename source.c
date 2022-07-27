//Parv Patel 

//CONTACT MANAGEMENT SYSTEM

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

//Declaration of all functions

void main_screen();
void add_contact();
void list_contact();
void delete_contact();
void search_contact(); 
void list_contact_names();
void edit_contact();

//Struct Contact containing name,phone,email and address

struct contact
{
    char name[30];
    char phone[10];
    char email[30];
    char address[50];
};

struct contact c;

//Function to display main screen after password entered is correct

void main_screen(){
    int ch;
    system("cls");
    while (ch!=6){
        system("cls");
        printf("\n\t\t >>>>>>>>>>>>>>>>>Contact Management System<<<<<<<<<<<<<<<<<<");
        printf("\n\n\n\t\t\tMAIN MENU\n\t\t---------------------------\n\t\t----->[1] Add a new Contact\n\n\t\t----->[2] List all Contacts\n\n\t\t----->[3] Search for contact\n\n\t\t----->[4] Edit a Contact\n\n\t\t----->[5] Delete a Contact\n\n\t\t----->[0] Exit\n\t\t---------------------------\n\t\t");
        printf("Enter your choice of operation:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: system("cls");
                    add_contact();
                    break;
            case 2: system("cls");
                    list_contact();
                    break;
            case 3: system("cls");
                    search_contact();
                    break;
            case 4: system("cls");
                    edit_contact();
                    break;
            case 5: system("cls");
                    delete_contact();
                    break;
            case 0: exit(1);
            default:
                    printf("\n\t Choice entered is invalid!!!!!! "); 
                    break;
                }
        
                printf("\nPress any key to continue   ");
                getch();
        }
}

//Function to add contact

void add_contact()
{
	int totChar = 0,i=0;
    FILE *fp;
    fp=fopen("contact.txt","ab+");
    if(fp==NULL)
	{
        printf("\n\t!!!!!Cannot Open the File!!!!!");
        return;
    }
    printf("\t---EXISTING LIST OF CONTACTS---");
    list_contact_names();
    printf("\n\n\n\t\t---ENTER NEW CONTACT---");
    fflush(stdin);
    printf("\n\n\t\tEnter Name:-");
    gets(c.name);
    printf("\n\n\t\tEnter Phone Number:-");
    gets(c.phone);
    printf("\n\n\t\tEnter Email:-");
    gets(c.email);
    printf("\n\n\t\tEnter Address:-");
    gets(c.address);
       
	fwrite(&c,sizeof(c),1,fp);
	fprintf(fp , "\n" , c);
	
    {
        printf("\n\n\t\t---Contact Added Successfully---\n");
    }
    fclose(fp);
    printf("\n\t\tUpdated Contact List!!\n");
    list_contact_names();
	
}
    
//Function to list all details of contact

void list_contact()
{
    FILE *fp;
    fp=fopen("contact.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t!!!!!Cannot Open the File!!!!!");
        return;
    }
    printf("\n\n\t\t---LIST OF CONTACTS---");
    printf("\n\n\t----------------------------------------------------");
 
    while(fread(&c,sizeof(c),1,fp)==1)
	{
        printf("\n\tName        \t\t");
        printf("\t%s",c.name);
        printf("\n\tPhone number\t\t");
        printf("\t%s",c.phone);
        printf("\n\tEmail       \t\t");
        printf("\t%s",c.email);
        printf("\n\tAddress     \t\t");
        printf("\t%s",c.address);
        printf("\n\n");
    }
    printf("\n\n\t----------------------------------------------------\n");
	fclose(fp);
}

//Function to display only the contact's name and number

void list_contact_names()
{
    FILE *fp;
    fp=fopen("contact.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t!!!!!Cannot Open the File!!!!!");
        return;
    }
    printf("\n\n\t\t---LIST OF CONTACTS---");
    printf("\n\n\t----------------------------------------------------");
 
    while(fread(&c,sizeof(c),1,fp)==1)
	{
        printf("\n\t%s",c.name);
        printf("\t\t\t\t%s",c.phone);
    }
    fclose(fp);
}

//Function to delete an existing contact

void delete_contact()
{
	char name[30];
	unsigned flag = 0;
	FILE *fp,*ft;
	fp = fopen("contact.txt","rb");
	if (fp == NULL)
	{
		printf("\n\t!!!!!Cannot Open the File!!!!!\n");
		return;
	}
	printf("-------Stored contact is below-------\n");
	list_contact_names();
    fflush(stdin);
	printf("\n\nEnter the name which can you delete the contact of that name : ");
	gets(name);
	ft = fopen("contact1.txt","ab+");
	while (fread(&c,sizeof(c),1,fp) == 1)
	{
		if (strcasecmp(name,c.name) !=0)
		{			
			fwrite(&c,sizeof(c),1,ft);
		}
		else
		{
			flag = 1;
		}
	}
	if (flag == 0)
	{
		printf("\nContact Not Found.");
	}
    else{
        printf("\nContact successfully deleted.");
    }
	fclose(fp);
	fclose(ft);
	remove("contact.txt");
	rename("contact1.txt","contact.txt");
	printf("\nNow Contact is sucessfully updated.\n");
	printf("\n\t\t   UPDATED CONTACT LIST.\n");
	list_contact_names();
}

//Function to search contact

void search_contact()
{
	char name[30];
    int flag=0;
    list_contact_names();
	FILE *fp;
	fp=fopen("contact.txt","rb");
	if(fp==NULL)
	{
		printf("\n\t!!!!!Cannot Open the File!!!!!");
		return;
	}
    fflush(stdin);
	printf("\n\nEnter the name which you want to search : ");
    gets(name);
    
	while((fread(&c,sizeof(c),1,fp)==1))
	{
        char *ret;
 		ret=strstr(strlwr(c.name),strlwr(name));
		if(ret)
		{
			flag = 1;
			printf("\n\tSearched record is displayed below\n'");
            printf("\n\n\t----------------------------------------------------\n");
			printf("\tName : %s\n",c.name);
			printf("\tPhone Number : %s\n",c.phone);
			printf("\tEmail Id : %s\n",c.email);
			printf("\tAddress : %s\n",c.address);
		}
    }
	if(flag==0)
	{
		printf("\ncontact is not found in this contact system.\n");
	}
	fclose(fp);
	
}

//Function to edit all the details of the entered contact name

void edit_contact()
{
	char name[30];
	int i=0,flag=0;
	FILE *fp;
	fp=fopen("contact.txt","rb+");
	if(fp==NULL)
	{
		printf("\n\t!!!!!Cannot Open the File!!!!!");
		return;
	}
	printf("\n\t\t   Existing list of contacts.");
	list_contact_names();
	fflush(stdin);
	printf("\n\tPlease enter the name of the contact which you want to edit : ");
	gets(name);
	while(fread(&c,sizeof(c),1,fp)>0 && flag==0)
	{
		if(strcasecmp(c.name,name)==0)
		{
			flag=1;
			system("cls");
			printf("\t\tYour details about this contact : \n");
			printf("\t\t___________\n");
			printf("\tName : %s\n",c.name);
			printf("\tPhone Number : %s\n",c.phone);
			printf("\tEmail Id : %s\n",c.email);
			printf("\tAddress : %s\n",c.address);
			fflush(stdin);
			printf("\n\t\tNow enter the choice which can you update : \n");
			printf("\n\t1.Edit name:-");
			gets(c.name);
			printf("\n\t2.Edit phone number:-");
			gets(c.phone);
			printf("\n\t3.Edit the email id :-");
			gets(c.email);
			printf("\n\t4.Edit the address:-");
			gets(c.address);
			fflush(stdin);
			fseek(fp,-(long)sizeof(c),1);
			fwrite(&c,sizeof(c),1,fp);
			
			printf("\n\t\tEntered details are stored in the corresponding contact.\n");
			break;
		}
	}
	if(flag==0)
	{
		printf("\n\t\tPlease enter the correct name of the contact to edit.\n");
	}

	fclose(fp);
	printf("\n\t\t   UPDATED CONTACT LIST\n");
	list_contact();

}

//Main Function with "GUEST" as password. 	

void main()
{
	int i;
	char ch1, password[10];
	char pass[10]="contact";
	printf("\n\t\t >>>>>>>>>>>>>>>>>Contact Management System<<<<<<<<<<<<<<<<<<\n\t\tEnter Password:-");
	for(i=0; i<10; i++)
    {
	    ch1=getch();
	    password[i]=ch1;
	    if(ch1!=13)
	        printf("*");
	    if(ch1 == 13)
	        break;
    }
  	password[i]='\0';
  	if (strcmp(password,pass)==0)
	{
  		main_screen();
	}
    else
	{
		printf("\n\t\tWrong Password\n\t\tPress any key to try again.");
	    getch();
	    system("cls");
	    main();
    }
}
