#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#define KNRM  "\x1B[0m"//this are color code for particular color as in ubuntu graphics.h not able to deal with colors
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void insert_record(FILE *fp);//declaring functions prototype
void del(FILE * fp);
void update(FILE * fp);
void search_and_print(FILE *fp);
int search(FILE *fp,char name_1[]);
void display(FILE * fp);
void sort(FILE * fp);
void backup(FILE * fp);
void deleteall(FILE * fp);
void clean_stdin();
char filename[20];
int count(FILE *fp);
void aboutus();

struct//definig own datatypes
{
   char name[40];
   long long  int mobile_num;
   long long int mobile_num_2;
   char email[30];
   char profession[30];
   char relationship[40];
}contact,sorte[200],temp;
int main()
{
system("cls");
        FILE *fp;
        int choice;

        printf("%sEnter the file name:",KYEL);
        gets(filename);
        fp=fopen(filename,"rb+");//open file in read and write binary form
        if(fp==NULL)
        {
             fp=fopen(filename,"wb+");//if file is null then open it in write binary form
             if(fp==NULL)
             {
                printf("Error in opening File\n");
                exit(1);
             }
        }

        while(1)//defining menu
        {
            system("cls");//clearing the console
            printf("*********************************************PHONEBOOK APPLICATION***********************************************\n\n");
            printf("\t\t1.Enter the New contact details");
            printf("\t\t\t2.Update the contact details\n\n");
            printf("\t\t3.Delete the record");
            printf("\t\t\t\t4.Display the list of records\n\n");
            printf("\t\t5.Search particular record");
            printf("\t\t\t6.count number of records in phonebook\n\n");
            printf("\t\t7.Delete all the record");
            printf("\t\t\t\t8.Take backup of record\n\n");
            printf("****************************************************9.About us*******************************************************\n\n");
            printf("****************************************************10.Exit*******************************************************\n\n");
            printf("Enter the choice\n");
            scanf("%d",&choice);
            switch(choice)
            {
            case 1:insert_record(fp);
                    break;
            case 2:update(fp);
                    break;
            case 3:del(fp);
                    break;
            case 4:sort(fp);
                    break;
            case 5:search_and_print(fp);
                    break;
            case 6:printf("Number of Contact:%d\n",count(fp));
                    break;
            case 10:fclose(fp);
                    exit(0);
                    break;
            case 7:deleteall(fp);
                    break;
            case 8:backup(fp);
                    break;
            case 9:aboutus();
                    break;
            default:printf("Please Enter the choice correctly");

            }

           _getch();

        }



}
void insert_record(FILE *fp)//function for inputing the record from user
{
    char check[50];
    clean_stdin();
    fseek(fp,0,2);//take pointer to the top position
    printf("Enter the contact name:");
    scanf("%[^\n]s",&contact.name);
    printf("Enter the mobile number:");
    scanf("%lld",&contact.mobile_num);
    printf("Want to enter Second mobile number:\n");
    printf("Enter yes or no\n");
    scanf("%s",&check);
    if(strcmp(check,"yes")==0 || strcmp(check,"Yes")==0 || strcmp(check,"YES")==0  )//prompt user whether they want to enter the second mobile num
    {
    printf("Enter the Second mobile number:");
    scanf("%lld",&contact.mobile_num_2);
    }
    else
    {
        contact.mobile_num_2=NULL;
    }
    printf("Want to enter email id:\n");
    printf("Enter yes or no\n");
    scanf("%s",&check);
    if(strcmp(check,"yes")==0 || strcmp(check,"Yes")==0 || strcmp(check,"YES")==0 )
    {
     printf("Enter the email:");
    scanf("%s",&contact.email);
    }
    else
    {
        strcpy(contact.email,"NULL");
    }
     printf("Want to enter profession :\n");
    printf("Enter yes or no\n");
    scanf("%s",&check);
    if(strcmp(check,"yes")==0 || strcmp(check,"Yes")==0 || strcmp(check,"YES")==0 )
    {
   printf("Enter the profession:");
   clean_stdin();
    scanf("%[^\n]s",&contact.profession);
    }
    else
    {
        strcpy(contact.profession, "NULL");
    }
    printf("Want to enter Relationship :\n");
    printf("Enter yes or no\n");
    scanf("%s",&check);
    if(strcmp(check,"yes")==0 || strcmp(check,"Yes")==0 || strcmp(check,"YES")==0 )
    {
       clean_stdin();
       printf("Enter the Relationship:");
       scanf("%[^\n]s",&contact.relationship);
    }
    else
    {
        strcpy(contact.relationship, "NULL");
    }
    fwrite(&contact,sizeof(contact),1,fp);//writing the data into file

}
void del(FILE *fp)//function for deleting the record
{


    FILE *tmp;
    char name_1[50];
    clean_stdin();
    printf("Enter the name whose contact details to be deleted:");
    scanf("%[^\n]s",&name_1);
    if(search(fp,name_1)==0)
    {
        return;
    }
    tmp=fopen("tmp.txt","wb");//creating the temp file for deleting the record
    if(tmp==NULL)
    {
        printf("Error in opening file\n");
        exit(0);
    }
    rewind(fp);//take pointer to the top

    while(fread(&contact,sizeof(contact),1,fp)==1)
    {
        if(strcmp(name_1,contact.name)!=0)
        {
            fwrite(&contact,sizeof(contact),1,tmp);//writing the data on temp file;
        }

    }
    fclose(fp);//closing the file
    fclose(tmp);
    fp=fopen(filename,"wb");//open file in write binary form
    rename("tmp.txt",filename);//renaming the temp file with original file
    printf("Record deleted successfully\n");
    fp=fopen(filename,"rb+");


}
void update(FILE *fp)//function for updating the record
{
    char check[50];
    char name_1[50];
    long size=sizeof(contact);
    clean_stdin();//clearing the buffer
    printf("Enter the name of the contact want to modify:");
    scanf("%[^\n]s",&name_1);
    if(search(fp,name_1)==1)
    {
    clean_stdin();
   printf("Enter the New contact name:");
    scanf("%[^\n]s",&contact.name);
    printf("Enter the mobile number:");
    scanf("%lld",&contact.mobile_num);
    printf("Want to enter Second mobile number:\n");
    printf("Enter yes or no\n");
    scanf("%s",&check);
       if(strcmp(check,"yes")==0)
       {
            printf("Enter the Second mobile number:");
            scanf("%lld",&contact.mobile_num_2);
       }
       else
        {
            contact.mobile_num_2=NULL;
        }
    printf("Want to enter email id:\n");
    printf("Enter yes or no\n");
    scanf("%s",&check);
    if(strcmp(check,"yes")==0)
    {
     printf("Enter the email:");
    scanf("%s",&contact.email);
    }
    else
    {
       strcpy(contact.email,"NULL");
    }
    printf("Want to enter profession :\n");
    printf("Enter yes or no\n");
    scanf("%s",&check);
    if(strcmp(check,"yes")==0)
    {
    clean_stdin();
   printf("Enter the profession:");
    scanf("%[^\n]s",&contact.profession);
    }
    else
    {
        strcpy(contact.profession,"NULL");
    }
    printf("Want to enter Relationship :\n");
    printf("Enter yes or no\n");
    scanf("%s",&check);
    if(strcmp(check,"yes")==0)
    {
    clean_stdin();
    printf("Enter the Relationship:");
    scanf("%[^\n]s",&contact.relationship);
    }
    else
    {
        strcpy(contact.relationship,"NULL");
    }
    }
    else
    {
    printf("No match found");
    }
    fseek(fp,-size,1);//deleting the previous record
    fwrite(&contact,sizeof(contact),1,fp);//writing the new record
    printf("Record modified\n");
}
void search_and_print(FILE *fp)//search the record of particular person
{
    char name_1[50];
    int flag=0;
    int choice_1;
    printf("1.Search on the basis of Name\n");
    printf("2.Search on the basis of Phone number\n");
    printf("Enter the choice:");
    scanf("%d",&choice_1);
    if(choice_1==1)
    {
           printf("Enter the name whose contact details want to know:");
           clean_stdin();
           scanf("%[^\n]s",name_1);
           rewind(fp);//take pointer to the top of file
           while(fread(&contact,sizeof(contact),1,fp)==1)
           {
                 if(strcmp(name_1,contact.name)==0)
                 {
                         printf("***********************************\n");
                         printf("NAME:%s\n",contact.name);
                         printf("FIRST MOBILE NUMBER:%lld\n",contact.mobile_num);
                         printf("SECOND MOBILE NUMBER:%lld\n",contact.mobile_num_2);
                         printf("EMAIL ID:%s\n",contact.email);
                         printf("PROFESSION:%s\n",contact.profession);
                          printf("RELATION:%s\n",contact.relationship);
                        printf("***********************************\n");
                        flag=1;
                         break;
                  }
            }
    if(flag==0)
    {
        printf("Match not found\n");
    }
    }
    else if(choice_1==2)
    {
           long long int temp_con;
            clean_stdin();
           printf("Enter the contact no whose contact details want to know:");
           scanf("%lld",&temp_con);
           rewind(fp);//take pointer to the top of file
           while(fread(&contact,sizeof(contact),1,fp)==1)
           {
                 if((contact.mobile_num==temp_con) || (contact.mobile_num_2==temp_con))
                 {
                         printf("***********************************\n");
                         printf("NAME:%s\n",contact.name);
                         printf("FIRST MOBILE NUMBER:%lld\n",contact.mobile_num);
                         printf("SECOND MOBILE NUMBER:%lld\n",contact.mobile_num_2);
                         printf("EMAIL ID:%s\n",contact.email);
                         printf("PROFESSION:%s\n",contact.profession);
                          printf("RELATION:%s\n",contact.relationship);
                        printf("***********************************\n");
                        flag=1;
                         break;
                  }
            }
    if(flag==0)
    {
        printf("Match not found\n");
    }
    }
}
void sort(FILE *fp)//sort record according to the alphabetical record
{

    int i,j,k;
     k=0;
    rewind(fp);

    while(fread(&contact,sizeof(contact),1,fp)==1)//bubble sort
    {
        sorte[k++]=contact;
    }
        for(i=1;i<=k;i++)
        {
            for(j=0;j<k-i;j++)
            {
                if(strcmp(sorte[j].name,sorte[j+1].name)>0)
                {
                    temp=sorte[j];
                    sorte[j]=sorte[j+1];
                    sorte[j+1]=temp;

                }
            }
        }
        for(i=0;i<k;i++)
    {
          printf("***********************************\n");
         printf("NAME:%s\n",sorte[i].name);
         printf("FIRST MOBILE NUMBER:%lld\n",sorte[i].mobile_num);
         printf("SECOND MOBILE NUMBER:%lld\n",sorte[i].mobile_num_2);
         printf("EMAIL ID:%s\n",sorte[i].email);
         printf("PROFESSION:%s\n",sorte[i].profession);
         printf("RELATION:%s\n",sorte[i].relationship);
         printf("***********************************\n");

    }
    if(count(fp)==0)
    {
    printf("\nContact list is Empty\n");
    }



}
void display(FILE *fp)//function for displaying the record
{
    sort(fp);
    rewind(fp);

    while(fread(&contact,sizeof(contact),1,fp)==1)
    {
         printf("***********************************\n");
         printf("NAME:%s\n",contact.name);
         printf("FIRST MOBILE NUMBER:%lld\n",contact.mobile_num);
         printf("SECOND MOBILE NUMBER:%lld\n",contact.mobile_num_2);
         printf("EMAIL ID:%s\n",contact.email);
         printf("PROFESSION:%s\n",contact.profession);
         printf("RELATION:%s\n",contact.relationship);
         printf("***********************************\n");

    }

}
int search(FILE *fp,char name_1[])//search function
{
    int flag=0;

    rewind(fp);
    while(fread(&contact,sizeof(contact),1,fp)==1)
    {
        if(strcmp(name_1,contact.name)==0)
        {
            flag=1;
            break;
        }

    }
    if(flag==0)
    {
        printf("Match not found\n");
    }

    return flag;
}
int count(FILE * fp)//count the number of records
{
    rewind(fp);
    int res;
     int count=0;
    while(fread(&contact,sizeof(contact),1,fp)==1)
    {
        count++;
    }
    return count;

    printf("Number of Contact:%d\n",count);
}
void backup(FILE *fp)//functionn for copying file into another file
{
    FILE *bp;
    char bpfile[40];
    printf("Enter the file name for copying the record\n");
    clean_stdin();
    gets(bpfile);
    bp=fopen(bpfile,"wb");
    if(bp==NULL)
    {
        printf("Error in opening file\n");
    }
    rewind(fp);

    while(fread(&contact,sizeof(contact),1,fp)==1)
    {
            fwrite(&contact,sizeof(contact),1,bp);
    }
    printf("Backup successful\n");
    fclose(fp);
    fclose(bp);

}
void deleteall(FILE *fp)//delete all the record
{
    fp=fopen(filename,"wb");
    printf("All the contact deleted successfully\n");
}
void clean_stdin(void)//for clearing the buffer memory
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
void aboutus()
{
printf("\n");
printf("               PHONE BOOK APPLICATION \n 1.This Application used for keeping the record of the people contact.\n2.It is programmed in c language.It based on the concept of file handling in c.\n3.In file handling the file has written in binary format  So less memory use in storing data and anyone cannot directly access that file.\nDeveloped by Vaibhav Yadav");
printf("\n");
}



