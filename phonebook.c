#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>

void gotoxy(int x,int y)
{
 	 COORD CRD ;     //set the coordinates of x and y.
	 CRD.X=x;
	 CRD.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CRD); //setting the position of cursor.1 to show & 0 to hide.
}
struct person
{
    char f_name[40];
    char m_name[40];
    char l_name[40];
    char country_code[4];
    long int mble_no;
    char gender[8];
    char mail[100];
};

// Defining person data type.
typedef struct person person;


void remove_all();
void print_menu();
void add_person();
void list_record();
void search_person();
void remove_person();
void update_person();
void take_input(person *p);



int main()
{
    start();
    return 0;
}


void start()
{
    int choice;
    while(1)
    {
        print_menu();
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                //list_record();
                add_person();
                getchar();
                getchar();
                break;
            case 2:
                list_record();
                getchar();
                getchar();
                break;
            case 3:
                search_person();
                getchar();
                getchar();
                break;
            case 4:
                remove_person();
                getchar();
                getchar();
                break;
            case 5:
                update_person();
                getchar();
                getchar();
                break;
            case 6:
                remove_all();
                getchar();
                getchar();
                break;
            default :
                system("cls");
                printf("Thanks for using phonebook visit again : )\n");
                getchar();
                getchar();
                exit(1);
        }
    }
}

void print_menu()
{
    system("cls");
    printf("\t\t****************************************************************\n");
    printf("\t\t*                         Phone Book                    *\n");
    printf("\t\t****************************************************************\n\n");
    printf("\t\t\t1) Add contact\n\n");
    printf("\t\t\t2) View Contact list\n\n");
    printf("\t\t\t3) Search Contact\n\n");
    printf("\t\t\t4) Remove Contact\n\n");
    printf("\t\t\t5) Update Contact\n\n");
    printf("\t\t\t6) Delete all Contacts\n\n");
    printf("\t\t\t7) Exit Phonebook\n\n\n");

    printf("\t\t\t\tEnter your Choice : ");
}


void add_person()
{
    system("cls");
    FILE *fp;
    fp = fopen("phonebook_db", "ab+");
    if (fp == NULL)
    {
        printf("Error in file opening, Please try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        person p;
        take_input(&p);
        fwrite(&p, sizeof(p), 1, fp);
        fflush(stdin);
        fclose(fp);
        system("cls");
        printf("Record added Successfully\n");
        printf("Press any key to continue ....\n");

    }
}

//  contact information.
void take_input(person *p)
{
    system("cls");
    getchar();
    printf("Enter First name : ");

    scanf("%s",p->f_name);

    printf("Enter Middle name : ");

    scanf("%s",p->m_name);

    printf("Enter Last name : ");

    scanf("%s",p->l_name);

    printf("Enter country code : ");
    scanf("%s",p->country_code);

    printf("Enter phone no : ");
    scanf("%ld",&p->mble_no);

    printf("Enter gender : ");
    scanf("%s",p->gender);

    printf("Enter email : ");
    scanf("%s",p->mail);
}

void list_record()
{   int row = 5;
    system("cls");
    FILE *fp;
    fp = fopen("phonebook_db", "rb");
    if (fp == NULL)
    {
        printf("Error in file opening, Please try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        person p;
        printf("\t\t\t\t*   Here is all records listed in phonebook                   *\n");
        printf("FIRST NAME\tMIDDLE NAME\tLAST NAME\tCOUNTRY CODE\tPHONE NO\t GENDER\t EMAIL\n");

        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            gotoxy(1,row);
			printf("%s",p.f_name);
			gotoxy(17,row);
			printf("%s",p.m_name);
			gotoxy(33,row);
			printf("%s",p.l_name);
			gotoxy(50,row);
			printf("%s",p.country_code);
			gotoxy(65,row);
			printf("%ld",p.mble_no);
			gotoxy(85,row);
			printf("%s",p.gender);
			gotoxy(90,row);
			printf("%s",p.mail);
            row++;
            printf("\n");
            fflush(stdin);
        }
        fflush(stdin);
        fclose(fp);
        printf("\n\nPress any key to continue....\n");

    }
}


void search_person()
{
    system("cls");
    long int phone;
    printf("Enter Phone number of the person you want to search : ");
    scanf("%ld",&phone);

    FILE *fp;
    fp = fopen("phonebook_db", "rb");
    if (fp == NULL)
    {
        printf("Error in file opening, Please try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        int flag = 0;
        person p;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(p.mble_no == phone)
            {
                printf("\nFIRST NAME\tMIDDLE NAME\tLAST NAME\tCOUNTRY CODE\tPHONE NO\tGENDER\t EMAIL\n");
                int row = 5;

            gotoxy(1,row);
			printf("%s",p.f_name);
			gotoxy(17,row);
			printf("%s",p.m_name);
			gotoxy(33,row);
			printf("%s",p.l_name);
			gotoxy(50,row);
			printf("%s",p.country_code);
			gotoxy(65,row);
			printf("%ld",p.mble_no);
			gotoxy(85,row);
			printf("%s",p.gender);
			gotoxy(90,row);
			printf("%s",p.mail);
            row++;
            printf("\n");

                flag = 1;
                break;
            }
            else continue;

        }
        if(flag == 0)
        {
            system("cls");
            printf("Person is not in the Phonebook\n");
        }
        fflush(stdin);
        fclose(fp);
        printf("\n\nPress any key to continue....\n");
    }

}


void remove_person()
{
    system("cls");
    long int phone;
    printf("Enter Phone number you want to remove from phonebook : ");
    scanf("%ld",&phone);

    FILE *fp,*temp;
    fp = fopen("phonebook_db", "rb");
    temp = fopen("temp","wb+");
    if (fp == NULL)
    {
        printf("Error in file opening, Please try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        person p;
        int flag = 0;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(p.mble_no == phone)
            {
                system("cls");
                printf("Person removed successfully\n");
                flag = 1;
            }
            else fwrite(&p,sizeof(p),1,temp);
            fflush(stdin);
        }
        if(flag == 0)
        {
            system("cls");
            printf("No record found for %d number\n",phone);
        }
        fclose(fp);
        fclose(temp);
        remove("phonebook_db");
        rename("temp","phonebook_db");
        fflush(stdin);
        printf("Press any key to continue....\n");

    }

}


void update_person()
{
    system("cls");
    long int phone;
    printf("Enter the Phone number you want to update & details : ");
    scanf("%ld",&phone);

    FILE *fp,*temp;
    fp = fopen("phonebook_db", "rb");
    temp = fopen("temp","wb+");
    if (fp == NULL)
    {
        printf("Error in file opening, Please try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        int flag = 0;
        person p;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(p.mble_no == phone)
            {
                take_input(&p);
                fwrite(&p, sizeof(p), 1, temp);
                system("cls");
                printf("Data updated successfully\n");
                flag = 1;
            }
            else fwrite(&p,sizeof(p),1,temp);
            fflush(stdin);
        }
        if(flag == 0)
        {
            system("cls");
            printf("No record found for %d number\n",phone);
        }
        fclose(fp);
        fclose(temp);
        remove("phonebook_db");
        rename("temp","phonebook_db");
        fflush(stdin);
        printf("Press any key to continue....\n");
    }
}



void remove_all()
{
    char choice;
    system("cls");
    remove("./phonebook_db");
    printf("All data in the phonebook deleted successfully\n");
    printf("Press any key to continue ... \n");
}

