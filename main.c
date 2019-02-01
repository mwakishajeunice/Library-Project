//This is the librarian area(acting as the admin)
/*duties are :1)issue books
              2)delete books in the library
              3)edit books in the library
              4)add books in the library
              5)search books in the library
              6)view books in the library*/
//This is the list of all the header files used in this section
#include <windows.h>
#include<stdio.h>//this holds functions like printf,scanf
#include<conio.h>//contain delay(),getch(),gotoxy
#include <stdlib.h>
#include<string.h>//contain strcmp(),strcpy(),strlen(),
#include<ctype.h>//contain functions like toupper(),tolower()
#include<dos.h>//contain the dos_getdate function
#include<time.h>
//#include<bios.h>//contain the show_mouse function

//constant definition
#define RETURNTIME 15

//List of all the function prototype used in this section
char catagories[][15]={"Computer","Electronics","Programing","Novels","Mathematics","Architecture"};
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
//void show_mouse(void);
void Password();
void issuerecord();
void loaderanim();

COORD coord = {0, 0};//This sets the coordinates of the course to 0,0
COORD max_res,cursor_size;
void gotoxy (int x, int y)
{
    //x and y coordinates
        coord.X = x; coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
//list of global files that can be acceed form anywhere in program
FILE *fp,*ft,*fs;

//list of global variable
int option;
char findbook;
char password[10]={"sammy"};


struct meroDate
{
    int month,day,year;
};
struct books
{
    int id;
    char stname[20];
    char name[20];
    char Author[20];
    int quantity;
    int count;
    int rackno;
    char *category;
    struct meroDate issued;
    struct meroDate duedate;
};
struct books a;
int main()

{
      Password();
      getch();
   return 0;

}
//some of the in-build functions used in this application
/*1.system("CLS"),,->used to clear screen before displaying the next output or action on the screen
2.gotoxy(),,->this is used set the x and y axis
3.getch(),,->used to get an input from the used that is to be used as part of his/her choice
*/

//this is the main menu area with the following options an admin can perform
//Add books,Delete books,Search books,Issue books,Edit books recored(eg,number of books available,change the location of the book in the library etc)

//the mainmenu() function will help do all this
void mainmenu()
{
 loaderanim();//behaves like  a loading action on process
 system("CLS");
 int i;
 gotoxy(20,5);
 printf("1. Add Books");
 gotoxy(20,7);
 printf("2. Delete books");
 gotoxy(20,9);
 printf("3. Search Books");
 gotoxy(20,11);
 printf("4. Issue Books");
 gotoxy(20,13);
 printf("5. View Book list");
 gotoxy(20,15);
 printf("6. Edit Book's Record");
 gotoxy(20,17);
 printf("7. Close Application");
 gotoxy(20,20);
 t();
 gotoxy(20,21);
 printf("Enter your choice:");
 switch(getch())
 {
  case '1':
  addbooks();
  break;
 case '2':
  deletebooks();
  break;
  case '3':
  searchbooks();
     break;
 case '4':
  issuebooks();
     break;
     case '5':
  viewbooks();
  break;
     case '6':
  editbooks();
  break;
     case '7':
     {
  system("CLS");
  printf("Exiting in 3 second...........>");

  delay(3000);//To delay the exit in about 3000 secs
  exit(0);//exits the application after the 3000 secs are over
     }
     default:
  {
  gotoxy(10,23);
  printf("\aWrong Entry!Please Enter again");
  if(getch())
  mainmenu();
  }

    }
}
//this will help the user to add books in the system
void addbooks(void)
{
 system("CLS");
 gotoxy(20,7);
 //a list of books the user can input in to the system
 printf("1. Computer");
 gotoxy(20,9);
 printf("2. Mechanics");
 gotoxy(20,11);
 printf("3. Electrical");
 gotoxy(20,13);
 printf("4. Mathematics");
 gotoxy(20,15);
 printf("5. Medicine");
 gotoxy(20,17);
 printf("6. Statistics");
 gotoxy(20,19);
 printf("7. Back to main menu");
 gotoxy(20,22);
 printf("Enter your option:");
 scanf("%d",&option);
 if(option == 7)
{
 mainmenu() ;
}
 system("cls");
 fp = fopen("books.dat","ab+");
 if(getdata() == 1)
 {
 a.category = catagories[option-1];
 fseek(fp,0,SEEK_END);//moves the file pointer at the end of the file to allow appending the next book to be entered
 fwrite(&a,sizeof(a),1,fp);
 fclose(fp);
 gotoxy(21,14);
 printf("The record is sucessfully saved");
 gotoxy(21,15);
 printf("Save any more?(Y / N):");
 //if user does not need to save more books
 if(getch() == 'N')
     mainmenu();
 else
    //if the user chooses to add another book by pressing Y
     system("cls");
     addbooks();
 }
}
//function that delete items from file books.dat
void deletebooks()
{
    system("CLS");
    int bookID;
    char another = 'y';
    while(another == 'y')  //infinite loop because another will always have the value y
    {
 system("CLS");
 gotoxy(10,5);
 printf("Enter the Book ID to  delete:");
 scanf("%d",&bookID);
 fp=fopen("books.dat","rb+");
 rewind(fp);//this function will take the file pointer to the begging of the file(remember the fseek function took the pointer to the end during our adding of books)
 while(fread(&a,sizeof(a),1,fp) == 1)
 {
     if(a.id == bookID)//finds if what is input by the user as the boookID murches the ID of the book stored in the file books.dat
      {
  gotoxy(10,7);
  printf("The book record is available");
  gotoxy(10,8);
  printf("Book name is %s",a.name);
  gotoxy(10,9);
  printf("Rack No. is %d",a.rackno);
  findbook = 't';
     }
 }
 //if no book with such bookID was found
 if(findbook != 't')
 {
     gotoxy(10,10);
     printf("No Book with search an ID was found");
     if(getch())
     mainmenu();
 }
 if(findbook == 't' )
 {
     gotoxy(10,9);
     printf("Do you want to delete it?(Y/N):");
     if(getch() == 'y')
     {
  ft=fopen("test.dat","wb+");  //temporary file for delete the book
  rewind(fp);//file pointer at the begging of the file
  while(fread(&a,sizeof(a),1,fp) == 1)
  {
      if(a.id != bookID)
      {
   fseek(ft,0,SEEK_CUR);
   fwrite(&a,sizeof(a),1,ft); //write all in tempory file except that
      }                              //we want to delete
  }
  fclose(ft);
  fclose(fp);
  remove("books.dat");
  rename("test.dat","books.dat"); //copy all item from temporary file to fp except that
  fp=fopen("books.dat","rb+");    //we want to delete
  if(findbook == 't')
  {
      gotoxy(10,10);
      printf("The record is sucessfully deleted");
      gotoxy(10,11);
      printf("Delete another record?(Y/N)");
  }
     }
 else
 mainmenu();
 fflush(stdin);
 another=getch();
 }
 }
    gotoxy(10,15);
    mainmenu();
}
void searchbooks()
{
    system("cls");
    int d;
    printf("***Search Books***");
    gotoxy(20,10);
    printf("1. Search By ID");
    gotoxy(20,14);
    printf("2. Search By Name");
    gotoxy( 15,20);
    printf("Enter Your Choice");
    fp=fopen("books.dat","rb+"); //open file for reading propose
    rewind(fp);   //move pointer at the begining of file
    switch(getch())
    {
   case '1':
 {
     system("cls");
     gotoxy(25,4);
     printf("***Search Books By Id***");
     gotoxy(20,5);
     printf("Enter the book id:");
     scanf("%d",&d);
     gotoxy(20,7);
     printf("Searching........");
     while(fread(&a,sizeof(a),1,fp)==1)
     {
  if(a.id==d)
  {
      delay(2);
      gotoxy(20,7);
      printf("The Book is available");
      gotoxy(20,9);
      printf("ID:%d",a.id);
      gotoxy(20,10);
      printf("Name:%s",a.name);
      gotoxy(20,11);
      printf("Author:%s ",a.Author);
      gotoxy(20,12);
      printf("Qantity:%d ",a.quantity);
      gotoxy(20,14);
      printf("Rack No:%d ",a.rackno);
      findbook='t';
  }

     }
     if(findbook!='t')  //checks whether conditiion enters inside loop or not
     {
     gotoxy(22,9);
     printf("\aNo Record Found");
     }
     gotoxy(20,17);
     printf("Try another search?(Y/N)");
     if(getch()=='y')
     searchbooks();
     else
     mainmenu();
     break;
 }
 case '2':
 {
     char s[15];
     system("cls");
     gotoxy(25,4);
     printf("***Search Books By Name***");
     gotoxy(20,5);
     printf("Enter Book Name:");
     scanf("%s",s);
     int d=0;
     while(fread(&a,sizeof(a),1,fp)==1)
     {
  if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
  {
      gotoxy(20,7);
      printf("The Book is available");
      gotoxy(20,9);
      printf("ID:%d",a.id);
      gotoxy(20,10);
      printf("Name:%s",a.name);
      gotoxy(20,11);
      printf("Author:%s",a.Author);
      gotoxy(20,12);
      printf("Qantity:%d",a.quantity);
      gotoxy(20,14);
      printf("Rack No:%d ",a.rackno);
      d++;
  }

     }
     if(d == 0)
     {
     gotoxy(22,9);
     printf("\aNo Record Found");
     }
     gotoxy(20,17);
     printf("Try another search?(Y/N)");
     if(getch()=='y')
     searchbooks();
     else
     mainmenu();
     break;
 }
 default :
 getch();
 searchbooks();
    }
    fclose(fp);
}
 //function that issue books from library
void issuebooks(void)
{
    int t;
    system("cls");
    printf("***ISSUE SECTION***");
    gotoxy(10,5);
    printf("1. Issue a Book");
    gotoxy(10,7);
    printf("2. View Issued Book");
    gotoxy(10,9);
    printf("3. Search Issued Book");
    gotoxy(10,11);
    printf("4. Remove Issued Book");
    gotoxy(10,14);
    printf("Enter a Choice:");
    switch(getch())
    {
 case '1':  //issue book
 {
  system("cls");
  int c = 0;
  char another = 'y';
  while(another == 'y')
  {
   system("cls");
   gotoxy(15,4);
   printf("***Issue Book section***");
   gotoxy(10,6);
   printf("Enter the Book Id:");
   scanf("%d",&t);
   fp=fopen("books.dat","rb");
   fs=fopen("Issue.dat","ab+");
   if(checkid(t)==0) //issues those which are present in library
   {
        gotoxy(10,8);
        printf("The book record is available");
        gotoxy(10,9);
        printf("There are %d unissued books in library ",a.quantity);
        gotoxy(10,10);
        printf("The name of book is %s",a.name);
        gotoxy(10,11);
        printf("Enter student name:");
        scanf("%s",a.stname);
        gotoxy(10,12);
        printf("Issued date=%d-%d-%d",a.issued.day,a.issued.month,a.issued.year);
        gotoxy(10,13);
        printf("The BOOK of ID %d is issued",a.id);
        a.duedate.day = a.issued.day + RETURNTIME;   //for return date
        a.duedate.month = a.issued.month;
        a.duedate.year = a.issued.year;
        if(a.duedate.day>30)
        {
     a.duedate.month += a.duedate.day / 30;
     a.duedate.day -= 30;

        }
        if(a.duedate.month > 12)
        {
    a.duedate.year += a.duedate.month / 12;
    a.duedate.month -= 12;

        }
        gotoxy(10,14);
        printf("To be return:%d-%d-%d",a.duedate.day,a.duedate.month,a.duedate.year);
        fseek(fs,sizeof(a),SEEK_END);
        fwrite(&a,sizeof(a),1,fs);
        fclose(fs);
        c=1;
   }
   if(c == 0)
   {
   gotoxy(10,11);
   printf("No record found");
   }
   gotoxy(10,15);
   printf("Issue any more(Y/N):");
   fflush(stdin);
   another=getche();
   fclose(fp);
  }

  break;
 }
 case '2':  //show issued book list
 {
  system("cls");
  int j=4;
  printf("***Issued book list***\n");
  gotoxy(2,2);
  printf("STUDENT NAME    CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE");
        fs=fopen("Issue.dat","rb");
  while(fread(&a,sizeof(a),1,fs)==1)
  {

   gotoxy(2,j);
   printf("%s",a.stname);
   gotoxy(18,j);
   printf("%s",a.category);
   gotoxy(30,j);
   printf("%d",a.id);
   gotoxy(36,j);
   printf("%s",a.name);
   gotoxy(51,j);
   printf("%d-%d-%d",a.issued.day,a.issued.month,a.issued.year );
   gotoxy(65,j);
   printf("%d-%d-%d",a.duedate.day,a.duedate.month,a.duedate.year);
   j++;
  }
  fclose(fs);
  gotoxy(1,25);
  returnfunc();
 }
 break;
 case '3':   //search issued books by id
 {
  system("cls");
  gotoxy(10,6);
  printf("Enter Book ID:");
  int p,c = 0;
  char another = 'y';
  while(another == 'y')
  {

   scanf("%d",&p);
   fs=fopen("Issue.dat","rb");
   while(fread(&a,sizeof(a),1,fs)==1)
   {
    if(a.id==p)
    {
     issuerecord();
     gotoxy(10,12);
     printf("Press any key.......");
     getch();
     issuerecord();
     c=1;
    }

   }
   fflush(stdin);
   fclose(fs);
   if(c==0)
   {
    gotoxy(10,8);
    printf("No Record Found");
   }
   gotoxy(10,13);
   printf("Try Another Search?(Y/N)");
   another=getch();
  }
 }
 break;
 case '4':  //remove issued books from list
 {
  system("cls");
  int b;
  FILE *fg;  //declaration of temporary file for delete
  char another='y';
  while(another=='y')
  {
   gotoxy(10,5);
   printf("Enter book id to remove:");
   scanf("%d",&b);
   fs=fopen("Issue.dat","rb+");
   while(fread(&a,sizeof(a),1,fs)==1)
   {
    if(a.id==b)
    {
     issuerecord();
     findbook='t';
    }
    if(findbook=='t')
    {
     gotoxy(10,12);
     printf("Do You Want to Remove it?(Y/N)");
     if(getch()=='y')
     {
      fg=fopen("record.dat","wb+");
      rewind(fs);
      while(fread(&a,sizeof(a),1,fs)==1)
      {
       if(a.id!=b)
       {
       fseek(fs,0,SEEK_CUR);
       fwrite(&a,sizeof(a),1,fg);
       }
      }
      fclose(fs);
      fclose(fg);
      remove("Issue.dat");
      rename("record.dat","Issue.dat");
      gotoxy(10,14);
      printf("The issued book is removed from list");

           }

    }
    if(findbook!='t')
    {
     gotoxy(10,15);
     printf("No Record Found");
    }
   }
   gotoxy(10,16);
   printf("Delete any more?(Y/N)");
   another=getch();
  }
 }
 default:
 gotoxy(10,18);
 printf("\aWrong Entry!!");
    getch();
 issuebooks();
 break;
      }
      gotoxy(1,30);
      returnfunc();
}
//show the list of book persists in library
void viewbooks(void)
{
    int i=0,j;
    system("cls");
    gotoxy(1,1);
    printf("***Book List***");
    gotoxy(2,2);
    printf(" CATEGORY     ID    BOOK NAME     AUTHOR       QTY     PRICE     RackNo ");
    j=4;
    fp=fopen("Bibek.dat","rb");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
 gotoxy(3,j);
 printf("%s",a.category);
 gotoxy(16,j);
 printf("%d",a.id);
 gotoxy(22,j);
 printf("%s",a.name);
 gotoxy(36,j);
 printf("%s",a.Author);
 gotoxy(50,j);
 printf("%d",a.quantity);
 gotoxy(69,j);
 printf("%d",a.rackno);
 printf("\n\n");
 j++;
 i=i+a.quantity;
      }
      gotoxy(3,25);
      printf("Total Books =%d",i);
      fclose(fp);
      gotoxy(35,25);
      returnfunc();
}
//edit information about book
void editbooks(void)
{
 system("cls");
 int c=0;
 int d,e;
 gotoxy(20,4);
 printf("***Edit Books Section***");
 char another = 'y';
 while(another == 'y')
 {
  system("cls");
  gotoxy(15,6);
  printf("Enter Book Id to be edited:");
  scanf("%d",&d);
  fp=fopen("books.dat","rb+");
  while(fread(&a,sizeof(a),1,fp)==1)
  {
   if(checkid(d)==0)
   {
    gotoxy(15,7);
    printf("The book is available");
    gotoxy(15,8);
    printf("The Book ID:%d",a.id);
    gotoxy(15,9);
    printf("Enter new name:");scanf("%s",a.name);
    gotoxy(15,10);
    printf("Enter new Author:");scanf("%s",a.Author);
    gotoxy(15,11);
    printf("Enter new quantity:");scanf("%d",&a.quantity);
    gotoxy(15,13);
    printf("Enter new rackno:");scanf("%d",&a.rackno);
    gotoxy(15,14);
    printf("The record is modified");
    fseek(fp,ftell(fp)-sizeof(a),0);
    fwrite(&a,sizeof(a),1,fp);
    fclose(fp);
    c=1;
   }
   if(c==0)
   {
    gotoxy(15,9);
    printf("No record found");
   }
  }
  gotoxy(15,16);
  printf("Modify another Record?(Y/N)");
  fflush(stdin);
  another=getch() ;
 }
  returnfunc();
}
void returnfunc(void)
{
    {
 printf(" Press ENTER to return to main menu");
    }
    a:
    if(getch() == 13) //allow only use of enter
    mainmenu();
    else
    goto a;
}
int getdata()
{
 int t;
 gotoxy(20,3);
 printf("Enter the Information Below");
 gotoxy(21,5);
 printf("Category:");
 gotoxy(31,5);
 printf("%option",catagories[option-1]);
 gotoxy(21,6);
 printf("Book ID:\t");
 gotoxy(30,6);
 scanf("%d",&t);
 if(checkid(t) == 0)
 {
  gotoxy(21,13);
  printf("\aThe book id already exists\a");
  getch();
  mainmenu();
  return 0;
 }
 a.id=t;
 gotoxy(21,7);
 printf("Book Name:");gotoxy(33,7);
 scanf("%s",a.name);
 gotoxy(21,8);
 printf("Author:");gotoxy(30,8);
 scanf("%s",a.Author);
 gotoxy(21,9);
 printf("Quantity:");gotoxy(31,9);
 scanf("%d",&a.quantity);
 gotoxy(21,11);
 printf("Rack No:");gotoxy(30,11);
 scanf("%d",&a.rackno);
 return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
 rewind(fp);
 while(fread(&a,sizeof(a),1,fp)==1)
 if(a.id==t)
 return 0;  //returns 0 if book exits
      return 1; //return 1 if it not
}
int t(void) //for time
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}
//for password option
void Password(void)
{
   system("cls");
   char d[25]="Password Protected";
   char ch,pass[10];
   int i=0,j;
    gotoxy(10,4);
    for(j=0;j<20;j++)
    {
    delay(20);
    printf("*");
    }
    for(j=0;j<20;j++)
   {
   delay(50);
   printf("%c",d[j]);
   }
   for(j=0;j<20;j++)
   {
   delay(20);
   printf("*");
   }
   gotoxy(10,10);
   gotoxy(15,7);
   printf("Enter Password:");

   while(ch!=13)
   {
 ch=getch();

 if(ch!=13 && ch!=8){
 putch('*');
 pass[i] = ch;
 i++;
 }
   }
   pass[i] = '\0';
   if(strcmp(pass,password)==0)
   {

 gotoxy(15,9);
 printf("Password match");
 gotoxy(17,10);
 printf("Press any key to continue.....");
 getch();
 mainmenu();
   }
   else
   {
  gotoxy(15,16);
  printf("\aWarning!! Incorrect Password");
  getch();
  Password();
   }
}
//display issued book's information
void issuerecord()
{
   system("cls");
   gotoxy(10,8);
   printf("The Book has taken by Mr. %s",a.stname);
   gotoxy(10,9);
   printf("Issued Date:%d-%d-%d",a.issued.day,a.issued.month,a.issued.year);
   gotoxy(10,10);
   printf("Returning Date:%d-%d-%d",a.duedate.day,a.duedate.month,a.duedate.year);
}
//its used to delay the display time...ie behave like a loading time
void loaderanim()
{
int loader;
system("cls");
gotoxy(20,10);
printf("LOADING........");
printf("\n\n");
gotoxy(22,11);
for(loader=1;loader < 20;loader++)
{
delay(100);printf("%c",219);}
}
//End of program
