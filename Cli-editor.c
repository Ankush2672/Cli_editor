#include<stdio.h>
#include<conio.h>
#include<string.h>


  ////   global variable


int loop = 1,total_input = 0;
char input[1000][1000];


//// undo stack

struct ustack
{
  char data[1000];
  int op;
  int index;
  struct ustack* next;
};

struct rstack
{
  char data[1000];
  int op;
  int index;
  struct rstack* next;
};

struct llog
{
    int op;
    int index;
    char data[1000];
    struct llog* next;
};

void insertEnd(struct llog** head, char* temp, int index ,int op )
{
  struct llog* node = (struct llog*) malloc(sizeof(struct llog));
  struct llog *last = *head;
  strcpy(node->data,temp);
  node->op = op;
  node->index = op;

  node->next = NULL;
  if (*head == NULL)
  {
    *head = node;
    return;
  }
  while (last->next != NULL)
    last = last->next;
  last->next = node;
  return;
}

struct ustack* newElement(int i, char* temp,int op )
{
  struct ustack* node = (struct ustack*) malloc(sizeof(struct ustack));
  if(!node){
    printf("OVERFLOW \n");
  }
  node->index = i;
  node->next = NULL;
  strcpy(node->data,temp);
  node->op = op;
  return node;
}

struct rstack* newElement2(int i, char* temp,int op )
{
  struct rstack* node = (struct rstack*) malloc(sizeof(struct rstack));
  if(!node){
    printf("OVERFLOW \n");
  }
  node->index = i;
  node->next = NULL;
  strcpy(node->data,temp);
  node->op = op;
  return node;
}
int isEmpty(struct ustack *root)
{
  return !root;
}

int isEmpty2(struct rstack *root)
{
  return !root;
}

int push(struct ustack** root, int data,char* temp,int op)
{
  struct ustack* StackLL = newElement(data,temp,op);
  StackLL->next = *root;
  *root = StackLL;
  return 1;
}

int rpush(struct rstack** root, int data,char* temp,int op)
{
  struct rstack* StackLL = newElement2(data,temp,op);
  StackLL->next = *root;
  *root = StackLL;
  return 1;
}
struct ustack* pop(struct ustack** root)
{
  if (isEmpty(*root)){
    printf("UNDERFLOW");
    return -1;
  }
   struct ustack* node = (struct ustack*) malloc(sizeof(struct ustack));
  struct ustack* temp = *root;

  *root = (*root)->next;
  node->index= temp->index;
  strcpy(node->data,temp->data);
  node->op = temp->op;
  free(temp);
  return node;
}

struct rstack* rpop(struct rstack** root)
{
  if (isEmpty2(*root)){
    printf("UNDERFLOW");
    return -1;
  }
   struct rstack* node = (struct rstack*) malloc(sizeof(struct rstack));
  struct rstack* temp = *root;

  *root = (*root)->next;
  node->index= temp->index;
  strcpy(node->data,temp->data);
  node->op = temp->op;
  free(temp);
  return node;
}

///// function declarations

struct ustack* main_Stack = NULL;
struct rstack* rmain_Stack = NULL;
struct llog* log_main = NULL;

void menu();
void insert();
void print();
void remov();
int strSub(char *str1, char* str2);
void search();
void logo();
void undo();
void redo();
void log();
void edit();

///// main function


int main()
{
    while(loop)
    {
        menu();
    }

    return 0;
}

/////  logo

void logo()
{
     printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tCLL-EDITOR\n\n\n");
}

//// menu

void menu()
{
    int choice;
    system("cls");
    logo();
    printf("press 1 ---> Insert Input\n");
    printf("press 2 ---> Delete Input\n");
    printf("Press 3 ---> Print All Inputs\n");
    printf("Press 4 ---> Undo\n");
    printf("press 5 ---> Redo\n");



    printf("press 6 ---> Searching\n");
    printf("press 7 ---> Log\n");
    printf("press 8 ---> Edit Input\n");
    printf("Press 0 ---> Exit\n\n");

    printf("\n\nEnter Your Choice : ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1 : insert(); break;
        case 2 : remov(); break;
        case 3: print(); break;
        case 4 : undo(); break;
        case 5 : redo(); break;
        case 6 : search(); break;
        case 7 : log(); break;
        case 8 : edit(); break;
        case 0 : loop = 0; break;
        default : printf("\n\n\t\t\t\t\t\t\t\t\t\t\t!!!! Invalid Entry, TRY AGAIN !!!!\n");
                    getch();
                     break;
    }

}


///// insert

void insert()
{
    int a;
    system("cls");
    logo();
    printf("Enter Input Here ::  ");
    fflush(stdin);
    gets(input[total_input++]);
    push(&main_Stack,total_input-1,input[total_input-1],1);
    insertEnd(&log_main,input[total_input-1],total_input-1,1);


     printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t !!!!!!!Input Recorded !!!!!");
     printf("\n\n\nPress any key to go back:::::\n");
     getch();

}

///// print input

void print()
{
 int i;
    system("cls");
    logo();
    printf("\n\n\n:::: All User Input List ::::\n\n\n");

    if(total_input == 0 || total_input == -1)
    {
        printf("\n\n \t\t\t !!!!!!!!!!!!!!!!!!! NO USER INPUT AVAILABLE TO PRINT !!!!!!!!!!!!!!!!\n\n\n");

    }

    for(i=0;i<total_input;i++)
    {

        printf("%d --> %s\n",i+1,input[i]);
    }
      insertEnd(&log_main,input[0],0,3);
  printf("\n\n\n\nPress Any Key to exit :::::::::\n");
  getch();
}


///// remove input

void remov()
{
    int n,i;
    char temp[1000];
    system("cls");
    logo();


    if(total_input == 0 || total_input == -1)
    {
        printf("\n\n \t\t\t !!!!!!!!!!!!!!!!!!! NO USER INPUT AVAILABLE TO Delete !!!!!!!!!!!!!!!!\n\n\n");
        printf("\n\n\n\n\nPress Any Key To Go Back!!!!!!!\n");
        getch();
        return;

    }
      printf("\n\n\n:::: All User Input List ::::\n\n\n");

    for(i=0;i<total_input;i++)
    {

        printf("%d --> %s\n",i+1,input[i]);
    }

    printf("\n\n\nEnter Input Number to delete :: ");
    scanf("%d",&n);

    if(n<=total_input)
    {


    for(i=n-1;i<total_input;i++)
    {
        strcpy(temp,input[i]);
        strcpy(input[i],input[i+1]);
        strcpy(input[i+1],temp);
    }
    total_input--;

    printf("\n\n\n\t\t\t\tInput Deleted Successfully!!!!!!");
    printf("\n\n::::::deleted input:::::\n\n");
    printf("At Position %d --- > %s\n\n",n,input[i]);
    push(&main_Stack,n-1,input[i],0);
     insertEnd(&log_main,input[i],n-1,0);

    }
    else
    {
        printf("\n\n\n\t\t\tSelected IndeX is Empty!!!!!\n");
    }
    printf("\n\n\n\n\t\t\t\t Press Any Key To Exit!!!!!!!\n");
    getch();

}

///// substring function


int strSub(char *str1, char* str2) {
  int a = strlen(str1);
  int b = strlen(str2);
  int i,j=0,k,count=0;
  for(i=0;i<a;i++)
  {
    if(str1[i] == str2[j])
    {
      count++;
      j++;
    }
  }
  if(count==b)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

///// search input


void search()
{
    char temp[50];
    int i,m=0;
    system("cls");
    logo();
     if(total_input == 0 || total_input == -1)
    {
        printf("\n\n \t\t\t !!!!!!!!!!!!!!!!!!! NO USER INPUT AVAILABLE TO Search !!!!!!!!!!!!!!!!\n\n\n");
        printf("\n\n\n\n\nPress Any Key To Go Back!!!!!!!\n");
        getch();
        return;

    }
    printf("Enter Input to Search : ");
    fflush(stdin);
    gets(temp);
     printf("\n\n");
    for(i=0;i<total_input;i++)
    {
        if(strSub(input[i],temp) == 1)
        {
            m++;
            printf("At pos. %d ---> %s\n",i+1,input[i]);
        }

    }
     insertEnd(&log_main,input[0],0,4);

    printf("\n\n\n\nTotal %d MATCH FOUND  !!!!!!!!!",m);
    printf("\n\n\n\n\n\n\nPress any key to exit !!!!!!!!!!\n");
    getch();
}



//////undo  operation


void undo()
{
    int i;
    int send;
    int rop;
    char temp[1000];
    system("cls");
    logo();
    if(main_Stack == NULL)
    {
        printf("\n\n\n\t\t\t\t\t\t\tNO INPUT AVAILABLE TO UNDO !!!!!!\n\n");
         printf("\n\n\n\nPress any key to exit !!!!!!!!!!\n");
        getch();
        return;

    }
    struct ustack* node = pop(&main_Stack);
      send = node->op + 6;


     rop = 3;
    if(node->op==0)
    {
        rop =1;
    }
    else if(node->op == 1)
    {
        rop = 0;
    }


    if(node->op == 0)
    {
        rpush(&rmain_Stack,node->index,node->data,rop);
    for(i=total_input;i>node->index;i--)
    {
        strcpy(temp,input[i]);
        strcpy(input[i],input[i-1]);
        strcpy(input[i-1],temp);
    }
    strcpy(input[i],node->data);
    total_input++;



    printf("\n\n\n\n\t\t\t\t\t\t\t\t\t UNDO OPERATION SUCCESSFULL!!!!!!\n\n\n\n\n");
    printf("At pos %d ---> %s\n",node->index+1,node->data);
    printf("\n#####RESTORED SUCCESSFULLY");
     printf("\n\n\n\nPress any key to exit !!!!!!!!!!\n");
    getch();
    }
    else if(node->op == 1)
    {
       rpush(&rmain_Stack,node->index,node->data,rop);
    for(i=node->index;i<total_input;i++)
    {
        strcpy(temp,input[i]);
        strcpy(input[i],input[i+1]);
        strcpy(input[i+1],temp);
    }
    total_input--;

         printf("\n\n\n\n\t\t\t\t\t\t\t\t\t UNDO OPERATION SUCCESSFULL!!!!!!\n\n\n\n\n");
    printf("At pos %d ---> %s\n",node->index+1,node->data);
    printf("\n#####Deleted SUCCESSFULLY");
     printf("\n\n\n\nPress any key to exit !!!!!!!!!!\n");
     getch();
    }
    else
    {
        strcpy(temp,input[node->index]);
        strcpy(input[node->index],node->data);
        rpush(&rmain_Stack,node->index,temp,rop);
         printf("\n\n\n\n\t\t\t\t\t\t\t\t\t UNDO OPERATION SUCCESSFULL!!!!!!\n\n\n\n\n");
         printf("\n\n\tInput at Position %d Changed !!!!!",node->index + 1);
          printf("\n\n\n\nPress any key to exit !!!!!!!!!!\n");
     getch();
    }
     if(rop==3)
    {
             insertEnd(&log_main,node->data,node->index,6+rop);
    }
    else
    {
             insertEnd(&log_main,node->data,node->index,send);
    }
}

/////// redo operation

void redo()
{
    int i;
    int send;
    int rop;
    char temp[1000];
    system("cls");
    logo();
    if(rmain_Stack == NULL)
    {
        printf("\n\n\n\t\t\t\t\t\t\tNO INPUT AVAILABLE TO REDO !!!!!!\n\n");
         printf("\n\n\n\nPress any key to exit !!!!!!!!!!\n");
        getch();
        return;
    }
     struct rstack* node = rpop(&rmain_Stack);
     send = node->op + 20;
     //insertEnd(&log_main,node->data,node->index,send);
     rop = 3;
      if(node->op==0)
    {
        rop =1;
    }
    else if(node->op == 1)
    {
        rop = 0;
    }



       if(node->op == 0)
    {
        push(&main_Stack,node->index,node->data,rop);
    for(i=total_input;i>node->index;i--)
    {
        strcpy(temp,input[i]);
        strcpy(input[i],input[i-1]);
        strcpy(input[i-1],temp);
    }
    strcpy(input[i],node->data);
    total_input++;

    printf("\n\n\n\n\t\t\t\t\t\t\t\t\t REDO OPERATION SUCCESSFULL!!!!!!\n\n\n\n\n");
    printf("At pos %d ---> %s\n",node->index+1,node->data);
    printf("\n#####RESTORED SUCCESSFULLY");
     printf("\n\n\n\nPress any key to exit !!!!!!!!!!\n");
    getch();
    }
    else if(node->op == 1)
    {
        push(&main_Stack,node->index,node->data,rop);
    for(i=node->index;i<total_input;i++)
    {
        strcpy(temp,input[i]);
        strcpy(input[i],input[i+1]);
        strcpy(input[i+1],temp);
    }
    total_input--;



       printf("\n\n\n\n\t\t\t\t\t\t\t\t\t REDO OPERATION SUCCESSFULL!!!!!!\n\n\n\n\n");
    printf("At pos %d ---> %s\n",node->index+1,node->data);
    printf("\n#####Deleted SUCCESSFULLY");
     printf("\n\n\n\n\t\t\t\t\t\t\t Press any key to exit !!!!!!!!!!\n");
     getch();
    }
    else
    {
         strcpy(temp,input[node->index]);
        strcpy(input[node->index],node->data);
        push(&main_Stack,node->index,temp,rop);

         printf("\n\n\n\n\t\t\t\t\t\t\t\t\t Redo OPERATION SUCCESSFULL!!!!!!\n\n\n\n\n");
           printf("\n\n\tInput at Position %d Changed !!!!!",node->index + 1);
          printf("\n\n\n\nPress any key to exit !!!!!!!!!!\n");
     getch();
    }

     if(rop==3)
    {
             insertEnd(&log_main,node->data,node->index,20+rop);
    }
    else
    {
             insertEnd(&log_main,node->data,node->index,send);
    }

}

void log()
{
    struct llog* temp;
    int i =0;
    int recieved;
    system("cls");
    logo();
    printf("\n\n\n\n\t\t\t\t\t\t\t\t\:::::LOG:::::\n\n\n\n\n\n");
     temp = log_main;

     while(temp!=NULL)
     {
         i++;

        if(temp->op ==1)
        {
            printf("%d Insert\t\t%s",i,temp->data);
        }
        else if(temp->op == 0)
        {
             printf("%d Delete\t\t%s",i,temp->data);
        }
        else if(temp->op == 3)
        {
             printf("%d Print\t\t",i);
        }
        else if(temp->op == 4)
        {
            printf("%d Search\t\t",i);
        }
        else if(temp->op ==5)
        {
             printf("%d Edit operation\t\t",i);
        }
        else if(temp->op <= 10)
        {
            recieved = temp->op - 6;
            if(recieved ==0)
            {
                printf("%d undo Restored\t%s",i,temp->data);
            }
            else if(recieved==1)
            {
                 printf("%d undo Deleted\t\t%s",i,temp->data);
            }
            else
            {
                 printf("%d undo Input Changed\t\t",i);
            }

        }
        else if(temp->op >=20)
        {
            recieved = temp->op - 10;
            if(recieved==0)
            {
                printf("%d Redo Restored\t%s",i,temp->data);
            }
            else if(recieved == 1)
            {
                 printf("%d Redo Deleted\t\t%s",i,temp->data);
            }
            else{
                printf("%d Redo Input Changed\t\t",i);
            }
        }
         temp = temp->next;
         printf("\n");

     }
     printf("\n\n\n\n\t\t\t\t\t\t\t Press any key to exit !!!!!!!!!!\n");
     getch();
}

void edit()
{
    int pos;
    char temp[100];
    char original[100];
    system("cls");
    logo();
    printf("\n\n\n");
     for(int i=0;i<total_input;i++)
    {

        printf("%d --> %s\n",i+1,input[i]);
    }
    printf("\n\nEnter Position to Edit : ");
    scanf("%d",&pos);
    if(pos<=total_input)
    {

    printf("Enter New Input : ");
    fflush(stdin);
    gets(temp);

    strcpy(original,input[pos-1]);
    strcpy(input[pos-1],temp);

      push(&main_Stack,pos-1,original,11);

      printf("\n\n\n\t\t\ Edit Successfull!!!!!!!!!\n\n\n");
      printf("%s changed to %s\n",original,input[pos-1]);
      insertEnd(&log_main,original,pos-1,5);
    }
    else
    {
         printf("\n\n\n\t\t\tSelected IndeX is Empty!!!!!\n");
    }

      printf("\n\n\n\n\t\t\t\t\t\t\t Press any key to exit !!!!!!!!!!\n");
     getch();

}
