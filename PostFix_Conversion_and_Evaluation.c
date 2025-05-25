/**
    Development of arithmetic expressions evaluation system
    
    Created by: Newton Shahi Thakuri
    Date: 2023 -05 - 2 

*/

#include <stdio.h>
#include <stdlib.h>

//bool defined since not present in C
#define FALSE 0
#define TRUE 1
#define EMPTYS -1
#define EMPTYC '\0'

#define PLUS '+'
#define MINUS '-'
#define MULTIPLY '*'
#define DIVIDE '/'
#define EXPONENT '$'
#define leftParanthesis '('
#define rightParanthesis ')'

const int noprecedence = 0;
const int precedenceLeft = 1;
const int precedencePlus = 2;
const int precedenceMinus = 2;
const int precedenceMultiply = 3;
const int precedenceDivide = 3;
const int precedenceExponent = 4;

#define result1 'z'
#define result2 'y'
#define result3 'x'
#define result4 'w'
#define result5 'v'
#define result6 'u'
#define MAXSIZE 100

int size;


struct Stack{
    char input[MAXSIZE];
    int num[MAXSIZE];
    int top;
};

struct Stack arithmetic;

int push(char data){
    if(isStackFull()) return FALSE;
    arithmetic.top++;
    arithmetic.input[arithmetic.top]=data;
    return TRUE;
}

char pop(){
    if(isStackEmpty()) return EMPTYS;
    char temp = {arithmetic.input[arithmetic.top]};
    arithmetic.top--;
    return temp;
}

int isStackFull(){
    if((arithmetic.top) +1 ==MAXSIZE) return TRUE;
    else return FALSE;
}

int isStackEmpty(){
    if(arithmetic.top == EMPTYS) return TRUE;
    else return FALSE;
}

void displayStack(){
    for(int i =arithmetic.top;i>EMPTYS;i--){
        printf("%c ",arithmetic.input[i]);
    }
}

int isOperator(char ch){
    if(ch==PLUS) return TRUE;
    if(ch==MINUS) return TRUE;
    if(ch==MULTIPLY) return TRUE;
    if(ch==DIVIDE) return TRUE;
    if(ch==EXPONENT) return TRUE;
    return FALSE;
}

int isOperand(char ch){
    //alphabets
    
    if((int)ch > 96 && (int)ch < 122) return TRUE;
    return FALSE; 
}

void getSize(char *exp){
    for(int i=0;exp[i]!= EMPTYC ;i++){
    size = i;
    }
    size++;
}


int countSize(char *exp){
    int size2;
    for(int i=0;exp[i]!= EMPTYC ;i++){
    size2 = i;
    }
    size2++;
    return size2;
}

char* initialize(){
    int temp;
    char *exp = (char *)malloc(sizeof(char)*MAXSIZE);
    printf("Enter the expression :\n");
    scanf("%s",exp);

    return exp;
}

int givePrecedence(char ch){
    if(ch==PLUS) return precedencePlus;
    if(ch==MINUS) return precedenceMinus;
    if(ch==MULTIPLY) return precedenceMultiply;
    if(ch==DIVIDE) return precedenceDivide;
    if(ch==EXPONENT) return precedenceExponent;
    if(ch==leftParanthesis) return precedenceLeft;
    return noprecedence;
}

int checkPrecedence(int p1,int p2){
    if((p1-p2)>0) return TRUE;
    else return FALSE;
}

void display(char ch,char *p){
    static int a;
    char tempOperator[MAXSIZE];
    char tempPost[MAXSIZE];
    a++;
    if(a==1){
    printf("|S.N. |Scanned Symbol |Operator Stack |PostFix Expression|\n");
    }
    
    int opi=0;
    
    for(opi;opi<=arithmetic.top;opi++){
        tempOperator[opi] = arithmetic.input[opi]; 
    }
    tempOperator[opi]='\0';
    

    int sizetemp = countSize(p);
    int poi=0;
    for(poi; poi<sizetemp;poi++){
        tempPost[poi]=p[poi];
    }
    tempPost[poi] ='\0';
    printf("| %2d  | %7c       | %7s       |  %7s         |",a,ch,tempOperator,tempPost);
    printf(" |\n");
}

char* postFix(char *exp){
    int temp;
    char *post = (char *)malloc(sizeof(char)*MAXSIZE);
    
    int iterator=0;
    char bin;
    
    for(int i=0;i<size;i++){
        if(exp[i] == leftParanthesis) push(exp[i]);
        if(exp[i] == rightParanthesis) {
            while(arithmetic.input[arithmetic.top]!=leftParanthesis) post[iterator++] = pop();
            pop(); //to pop the left paranthesis also.
        } 
        if(isOperand(exp[i])) post[iterator++] = exp[i];
        if(isOperator(exp[i])){
                if(checkPrecedence(givePrecedence(exp[i]),givePrecedence(arithmetic.input[arithmetic.top]))) push(exp[i]);
                else {
                    for(int counter=arithmetic.top;counter>-1;counter--){
                    if(checkPrecedence(givePrecedence(exp[i]),givePrecedence(arithmetic.input[counter]))) break;
                    post[iterator++] = pop();
                    }
                    push(exp[i]);
                }
                
         }
        display(exp[i],post);
    }
    while(arithmetic.input[arithmetic.top]!=EMPTYC) post[iterator++] = pop();
    return post;
}

//function to display the expression i.e. postfix or prefix according to the requirement

void displayExpression(char *expression){
    printf("POSTFIX EXPRESSION\n");
    printf("[");
    for(int i=0;i<size;i++) printf("%c",expression[i]);
    printf("]\n");
}

int valid(char* exp){
    int Paranthesis=0;
    int numLeftParanthesis=0;
    int numRightParanthesis=0;
    int sequenceOperands=0;
    int sequenceOperator=0;
    int validity = TRUE;
    int wrongSOpn = FALSE; //SEQUENCE OPERANDS 
    int wrongSOpe = FALSE;
    int wrongtotParanthesis = FALSE;
    int wrongformatParanthesis = FALSE; 
    int wrongFirst = FALSE;
    int wrongLast = FALSE;
    int checkFirst = TRUE;
    int checkLast= TRUE;
    int lastope=0;
    int lastopn=0;
    //check all errors
    
    for(int i = 0; i<size ; i++){
        if(checkFirst){
            if(isOperator(exp[i])){
                checkFirst= FALSE;
                wrongFirst= TRUE;
            }
            if(isOperand(exp[i])){
                checkFirst = FALSE;
            }
        }
        
        if(checkLast){
            if(isOperator(exp[i])) lastope=i;
            if(isOperand(exp[i])) lastopn=i;
        }

        
        if(exp[i] == leftParanthesis) Paranthesis++;
        if(exp[i] == rightParanthesis) Paranthesis--;
        
        if(Paranthesis<0) wrongformatParanthesis=TRUE;
        if(isOperator(exp[i])) {
            sequenceOperator++;
            if(sequenceOperator>1) wrongSOpe = TRUE;
            sequenceOperands=0;
        }
        if(isOperand(exp[i])){
            sequenceOperands++;
            if(sequenceOperands>1) wrongSOpn = TRUE;
            sequenceOperator=0;
        }
    }
    
    if(lastope>=lastopn) wrongLast=TRUE;
    if(Paranthesis!=0) wrongtotParanthesis=TRUE;
    
    
    //conditions

    if(wrongFirst){
        printf("FIRST EXPRESSION MUST START WITH OPERAND OR PARANTHESIS. MUST BE IN INFIX FORMAT.\n");
        validity=FALSE;
    }
    
    if(wrongLast){
        printf("LAST EXPRESSION MUST END WITH OPERAND OR PARANTHESIS. MUST BE IN INFIX FORMAT.\n");
        validity=FALSE;
    }
    
    if(wrongSOpn){
        printf("WRONG OPERAND SEQUENCING, ONLY ALPHABETIC LETTERS. NO WORDS.\n");
        validity=FALSE;
    }
    
    if(wrongSOpe){
        printf("WRONG OPERATOR SEQUENCING, ONLY BINARY OPERATORS IN INFIX FORMATTING. \n");
        validity=FALSE;
    }
    
    
    if(wrongtotParanthesis){
        printf("MISSING PARANTHESIS\n");
        validity=FALSE;
    }
    
    if(wrongformatParanthesis){
        printf("FOUND WRONG FORMATTING OF PARANTHESIS. USE '(' BEFORE  ')'\n");
        validity=FALSE;
    }
    
    
    return validity;
}

double add(double x,double y){
    return x+y;
}

double minus(double x,double y){
    return y-x;
}   

double multiply(double x,double y){
    return x*y;
}

double divide(double x,double y){
    return y/x;
}

double exponent(double x,double y){
    double result=y;
    if(x==0 && y==0){
        printf("\n EXCEPTION OCCURED, 0 POWER 0 IS INDETERMINATE\n");
        return 0;
    }
    if(x==0) return 1;
    for(int i =0;i<(x-1);i++) result = result*y;
    return result;
}

double giveArrVal(char *operands,double *num,char exp){
    int sizetemp = countSize(operands);
    double val=0;
    int j=0;
    for(int i=0;i<sizetemp;i++){
        val = exp == operands[i] ? num[i] : 0;
        if(val){
        break;
        }
    }
    
    return val;
}

double evaluatePost(char *expressionPost){
    double val=0;
    int size2=countSize(expressionPost);
    double numPost[MAXSIZE];
    char operands[MAXSIZE];
    char operator[MAXSIZE];
    int iterator=0;
    int repeat =FALSE;
    int countRepeat=0;
    int opI=0;      //iterator for operator array
    for(int i =0;i<size2;i++){
        if(isOperand(expressionPost[i])){
            for(int j=0;operands[j]!=EMPTYC;j++){
                if(operands[j] == expressionPost[i]) {
                    countRepeat++;
                }
                if(countRepeat==2) {
                    repeat=TRUE;
                    break;
                }
            }
            if(!repeat){
                //printf("| %c |\n",expressionPost[i]);
                operands[iterator++]=expressionPost[i];//make repeat false when repeat
                repeat=FALSE;
            }
        }else{
            operator[opI++]=expressionPost[i];
        }
        countRepeat=0;
    }
    
    printf("OPERANDS :\n");
    
    for(int looper=0;looper<iterator;looper++)
        printf("| %c |\n",operands[looper]);
    
    printf("\nOPERATORS :\n");
    
    
    for(int looper=0;looper<opI;looper++)
        printf("| %c |\n",operator[looper]);
    
    
    printf("\n ENTER VALUES FOR OPERANDS\n");
    //ask for the values of the operands
    for(int i=0;i<iterator;i++){
        printf("Enter the value of %c : ",operands[i]);
        scanf("%lf",&numPost[i]);
    }
    
    char result[size2];
    //initialization of result
    result[0] = result1;
    result[1] = result2;
    result[2] = result3;
    result[3] = result4;
    result[4] = result5;
    result[5] = result6;
    
    
    
    int riterator=0;
    int sizetemp =size2;
    int osize= countSize(operands);
    int oIterator = osize;
    double val1,val2;
    
    for(int i=0;i<size2;i++){
        if(isOperator(expressionPost[i])){
            val1 = giveArrVal(operands,numPost,expressionPost[i-1]);
            val2 = giveArrVal(operands,numPost,expressionPost[i-2]);
            switch (expressionPost[i]){
                case PLUS:
                    val=add(val1,val2);
                break;
                case MINUS:
                    val=minus(val1,val2);
                break;
                case MULTIPLY:
                    val=multiply(val1,val2);
                break;
                case DIVIDE:
                    val=divide(val1,val2);
                break;
                case EXPONENT:
                    val=exponent(val1,val2);
                
                default:
                break;
            }
            expressionPost[i-2]=result[riterator];
            operands[oIterator]=result[riterator];
            numPost[oIterator] = val;
            riterator++;
            oIterator++;
            sizetemp=sizetemp-2;
            for(int j=i-1;j<=sizetemp;j++){ //Update the obtained result in the expression
                expressionPost[j] = expressionPost[j+2];
            }
            expressionPost[sizetemp+1] = EMPTYC;
            i=i-2;
        }
        
    }
    
    return val;
}

int main(){
    //INITIALIZING
    arithmetic.top = EMPTYS;
    char *expression=initialize();
    getSize(expression);
    
    //CHECKING IF THE EXPRESSION IS IN INFIX OR NOT.
    int validity = valid(expression);
    if(!validity) return 0;

    //CONVERTING INTO POSTFIX EXPRESSION
    char *expressionPost = postFix(expression);
    displayExpression(expressionPost);
    
    //EVALUATION OF POSTFIX EXPRESSION
    double valPost = evaluatePost(expressionPost);
    printf("%lf is the value of the postfix when evaluated.\n",valPost);
        
    free(expression);
    free(expressionPost);
    return 0;       
    
}

