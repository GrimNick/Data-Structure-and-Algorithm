/**
    Clear illustration of union, structure, enumeration and arrays while writing a program.
    
    Created by: Newton Shahi Thakuri
    Date: 2023 -04 - 27 

*/
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int maxsize= 6;
const int maxKey=25;
int userNumber = 99;
const int adminTOT=1;

const char emptyc ='\0';
const int emptyi=99;    

enum UserType {CORPORATE=0, INDIVIDUAL,STOP};

struct Individual{
    int ID;
    char name[5];
    char key[5];
    int price;
};

struct Corporate{
    int ID;
    char name[5];
    char key[25][6];
    int price;
    int numOfLicense;
};

union Usertype{
    struct Individual i;
    struct Corporate c;
};

struct User{
    union Usertype userKind;
    enum UserType userType;
};

//Initializing the data by either documents or by files(changeable).

struct User* initialize(){
    struct User *u = (struct User*)malloc(maxsize*sizeof(struct User));
    
    //REPRESENTING 1 BY INDIVIDUAL AND 0 BY CORPORATE
    
    struct User ram;
    //ram.userType = INDIVIDUAL;
    ram.userKind.i= {
        1,"ram","aXz5",5
    };

    struct User eec;
    //eec.userType = CORPORATE;
    eec.userKind.c={
        2,"eec",{"by3K","66Y2","4Uee","oQ5r"},15,4
    };
    
    struct User pec;
    //pec.userType = CORPORATE;
    pec.userKind.c = {
        3,"pec",{"Lre4","re8K","22Y8"},10,3
    };
    
    
    struct User kec;
    //kec.userType = CORPORATE;
    kec.userKind.c = {
        4,"kec",{"8tW2","uU5e","pPoO","eR71","Tup4","v9Bg"},25,6
    };
    
    
    struct User sam;
    //sam.userType = INDIVIDUAL;
    sam.userKind.i = {
        5,"sam","bB39",5
    };
    
    
    struct User newt;
    //newt.userType = INDIVIDUAL;
    newt.userKind.i= {
        1,"new","newt",0
    };
    
    u[0] = ram;
    u[0].userType = INDIVIDUAL;
    
    u[1] = eec;
    u[1].userType = CORPORATE;
    
    u[2] = pec;
    u[2].userType = CORPORATE;
    
    u[3] = kec;
    u[3].userType = CORPORATE;
    
    u[4] = sam;
    u[4].userType = INDIVIDUAL;
    
    u[5] = newt;
    u[5].userType = INDIVIDUAL;
    
    u[6].userType = STOP;
    return u;
}
//Authenicates the user with the license. If not correct, they will not get acess to the information

bool login(struct User *u){
    char name[5];
    char key[5];
    printf("-----Enter your username-----\n");
    printf("------------------------------\n");
    printf("          =>");
    scanf("%s",name);   
    printf("------------------------------\n");
    printf("-----Enter your license key-----\n");
    printf("------------------------------\n");
    printf("          =>");
    scanf("%s",key);    
    bool flag=false;
    for(int i = 0 ; i<maxsize ; i++){
        if((strcmp(u[i].userKind.i.name,name))==0 || strcmp(u[i].userKind.c.name,name) ==0 ){
            flag = true;
            userNumber =i;
            break;
        }
    }
    bool verified = false;
    
    if(flag){
        if(u[userNumber].userType==1){
            verified = strcmp(u[userNumber].userKind.i.key,key) == 0 ? true : false;
        }
        else if(u[userNumber].userType==0){
            for(int j = 0; u[userNumber].userKind.c.key[j][0] != '\0';j++){
                verified = strcmp(u[userNumber].userKind.c.key[j],key) == 0 ? true : false;
                if(verified){
                 break;
                 }
            }
        
        }
    }
    return verified;        
}
//Clears the Screen

void clear(){
    system("clear");    //for linux and for windows use below:
    //system("CLS");    //use this for windows
}

//Displays the data of the user.

void displayData(struct User u){
    //enum UserType userType;
    printf("-----Details : -----\n");
    printf("---------------------\n");
    char name[5];
    char price[5];
    if(u.userType == INDIVIDUAL) {
    printf("Username : %s\n",u.userKind.i.name);
    printf("Price paid : $%dK\n",u.userKind.i.price);
    printf("User Type : INDIVIDUAL\n");
    }
    else {
    printf("Username : %s\n",u.userKind.c.name);
    printf("Price paid : $%dK\n",u.userKind.c.price);
    printf("User Type : CORPORATE\n");
    printf("Number of Licenses : %d\n",u.userKind.c.numOfLicense);
    }
}

//Gets the size of the array 

int getSize(struct User *u){
    int i =0;
    while(u[i].userType != STOP){i++;}
    return i;
}

//Gives the acess to the information of the entire user data base.

void admin(struct User *u){
    int num_of_users=0;
    int num_of_licenses_given=0;
    int total_amount_collected=0;
    int size1 = getSize(u);
    for(int i =0;i<size1;i++){
        num_of_users++;
        if((u[i].userType==CORPORATE)==0){
            num_of_licenses_given++;
            total_amount_collected+=u[i].userKind.i.price;
        }
        else if((u[i].userType==INDIVIDUAL)==0){
            num_of_licenses_given+=u[i].userKind.c.numOfLicense;
            total_amount_collected+=u[i].userKind.c.price;
        }
    }
    printf("*****WELCOME ADMIN*****\n");
    printf("------------------------\n");
    printf("Number of users :            [%4d]\n",num_of_users-adminTOT);
    printf("Number of Licenses Given :  [%4d]\n",num_of_licenses_given-adminTOT);
    printf("Total Amount collected :     [$%4dk]\n",total_amount_collected);

}

int main(){
    struct User *u = initialize();
    //username and license. Log in verification.
    bool verify=false;
    
    while(1){
        verify = login(u);
        clear();
        if(verify) {
            printf("+++++ACESS GRANTED:+++++  \n");
            break;
        }
        else{
            printf("xXxXxACESS DENIED:xXxXx   \n");
        }
    }
    
    displayData(u[userNumber]);
    
    if(userNumber==5) admin(u); 
    
    free(u);
    
    return 0;
}

