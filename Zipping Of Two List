#include <stdio.h>
#include <stdlib.h>

/**
    Clear illustration of zipping

    Created by: Newton Shahi Thakuri
    Date: 2023 -05 - 10 

*/

#define MAXSIZE 100
#define STRINGSIZE 2

struct Node{
    char data;
    struct Node *next;
};

struct Result{
    char data[STRINGSIZE];
    struct Result *next;
};

struct Node* createNode(char data){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data; 
    newNode->next = NULL;
    return newNode;
};

struct Result* createZip(char data1,char data2){
    struct Result *newNode = (struct Result*)malloc(sizeof(struct Result));
    newNode->data[0] = data1;
    newNode->data[1] = data2;
    newNode->next = NULL;
    return newNode;
}

struct Node* InsertChar(struct Node* head,char ch){
    struct Node *temp = head;
    if(head->data == '\0'){ 
        head->data = ch;
        return temp;
    }
    
    while(head->next != NULL) head= head->next;
    head->next = createNode(ch);
    return temp;
}

struct Result* InsertResult(struct Result* head,char ch1,char ch2){
    struct Result *temp = head;
    if(head->data[0] == '\0'){  
        head->data[0] = ch1;
        head->data[1] = ch2;
        return temp;
    }
    
    while(head->next != NULL) head= head->next;
    head->next = createZip(ch1,ch2);
    return temp;
}

int getSize(char *u){
    int i =0;
    while(u[i] != '\0'){i++;}
    return i;
}

struct Node* convToLinked(char* input){
 
    int i=0;
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    head->data = '\0';
    //= (struct Node*)malloc(sizeof(struct Node)*MAXSIZE);
    int size2= getSize(input);

    while(i<size2){
        printf("%c is input[%d]\n",input[i],i);
        head = InsertChar(head,input[i]);
        //printf("%c is inserted\n",head->data);
        i++;
    }
    return head;
}

char* convToArray(struct Node* n){
    char* arr = (char *)malloc(sizeof(char)*MAXSIZE);
    return arr;
}

struct Result* ZIP(struct Node* n1, struct Node*n2){
    struct Result* head = (struct Result*)malloc(sizeof(struct Result));
    head->data[0] = '\0';
    //= (struct Node*)malloc(sizeof(struct Node)*MAXSIZE);
    
    struct Node* temp1 = n1;
    struct Node* temp2 = n2;
    while(temp1!= NULL && temp2 != NULL){
        printf("[%c] is input1 and [%c] is input2 \n",temp1->data,temp2->data);
        head = InsertResult(head,temp1->data,temp2->data);
        temp1=temp1->next;
        temp2=temp2->next;
    }
    return head;
}

struct Node* sub(struct Node* head,int start,int finish){
    struct Node* ToCut = head; //remove tocut and replace head in all tocut to change without return type
    struct Node* sub = (struct Node*)malloc(sizeof(struct Node));
    sub->data = '\0';
    int i=0;
    if(i>start){
        printf("Incorrent start input\n");
        return NULL;
    }
    // a, b, c , d, -> b,c
    while(i!=start){
        ToCut=ToCut->next;
        i++;
    }
    for(i=0;i<finish;i++){
        InsertChar(sub,ToCut->data);
        ToCut=ToCut->next;
    }
    return sub;
}

void printLinkedList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("[%c] -> ", current->data);
        current = current->next;
    }
    
    printf("[\\0]\n");
}

void printZip(struct Result* head){
    struct Result* current = head;
    while(current != NULL){
        printf("[%c%c] ->",current->data[0],current->data[1]);
        current= current ->next;
    }
    printf("[\\0]");
    printf("\n");
}


void cleanMem(struct Node* head){
    struct Node* another;
    while(head != NULL){
        another = head->next;
        free(head);
        head = another;
    }
}

void cleanMemZip(struct Result* head){
    struct Result* another;
    while(head != NULL){
        another = head->next;
        free(head);
        head = another;
    }
}


int main(){

    char input[]= "HOUSES";
    //struct Node *list1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *list1 = convToLinked(input);
    printLinkedList(list1);
    //cleanMem(list1);
    printf("\n");
    
    char input2[]= "TOADD";
    //struct Node *list2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *list2 = convToLinked(input2);
    printLinkedList(list2);
    //cleanMem(list2);
    printf("\n");
    
    struct Node *listcut1 = sub(list1,2,3);
    printf("sub string of %s\n",input);
    printLinkedList(listcut1);
    printf("\n");
    
    struct Result *listzip = ZIP(list1,list2);
    printf("The addition of given linked list by zipping is:\n");
    printLinkedList(list1);
    printLinkedList(list2);
    printZip(listzip);
    
    cleanMem(list1);
    cleanMem(list2);
    cleanMem(listcut1);
    cleanMemZip(listzip);
    return 0;
}

