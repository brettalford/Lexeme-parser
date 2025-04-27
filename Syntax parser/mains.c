/*
=============================================================================
Title : lexeme parser
Description : This program determines lexemes and their respective tokens
Author : Brett Alford (R#11700357)
Date : 10/30/2023
Version : 1.0
Usage : Compile and run this program using the GNU C compiler
Notes : program requires second argument
C Version : default
=============================================================================
*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//linked list to store all the symbols (for potential unknowns and integers because the pointers cant point to something thats always changing or it's...pointless
typedef struct symbollist {
    char symbols[30];
    struct symbollist * next;
} symboler;

//global values
char *lextoken[]={"EQUAL_OP","LEQUAL_OP","GEQUAL_OP","INC_OP","DEC_OP","NEQUAL_OP","ASSIGN_OP","LESSER_OP","GREATER_OP","SEMICOLON","ADD_OP","SUB_OP","MULTI_OP","DIV_OP","LEFT_PAREN"
        ,"RIGHT_PAREN","LEFT_CBRACE","RIGHT_CBRACE","KEY_READ","KEY_WRITE","KEY_WHILE","KEY_DO","IDENT","INT_LIT","UNKNOWN"};


int errorcode=0;
int numberoftokens=0;
int tokenplace=0;
int errors=0;



void S(int *tokenarray,char **symbolarray);
void VE(int *tokenarray,char **symbolarray);
void readwrite(int *tokenarray,char **symbolarray);
void dowhile(int *tokenarray,char **symbolarray);
void C(int *tokenarray,char **symbolarray);
void E(int *tokenarray,char **symbolarray);
void T(int *tokenarray,char **symbolarray);
void F(int *tokenarray,char **symbolarray);


int main(int argc, char* argv[]) {

    //setup for linked list
    symboler * head =NULL;
    head = (symboler *) malloc(sizeof(symboler));
    symboler *mover=head;




    FILE *fptr;

    //print out rnumber thing
    printf("DCooke Parser :: R11700357");
    printf("\n");



    //if file not given
    if(argc==1){
        printf("File not given\n");
        return 2;
    }
    //if the file is not found
    if ((fptr=fopen(argv[1],"r"))==NULL){
        printf("File not found\n");
        return 3;
    }



    //if the file exists Open a file in read mode
    fptr = fopen(argv[1], "r");



    //create string variables
    char myString[1000];
    char instring[]={""};
    char string2[]={""};

    //variables for token array
    int sizeval=5000;
    int *tokenarray = (int *) malloc(sizeval * sizeof(int));
    char **symbolarray = malloc(sizeval * sizeof(char*));



//array values
    char *lexsymbol[]={"==","<=",">=","++","--","!=","=","<",">",";","+","-","*","/","(",")","{","}","read","write","while","do",};



// Read the content and put it into instring
    while(fgets(myString, 100, fptr)) {

        //setting instring to empty
        strcpy(instring,"");
        //setting instring to mystring
        strcpy(instring,myString);


        //variables
        int count=0;
        int stringlocation=0;





        //getting length of the string
        while(instring[count]){
            count++;
        }
        int string1length=count;



        //first for loop, contains all operations basically
        int i= string1length+1;
        int length=0;
        for(i;i>0;i--){




            int multip=0;
            int isknown=0;
            //value of current character
            char currentchar=instring[stringlocation];
            //value of next character
            char nextchar=instring[stringlocation+1];


            //this section determines if the current character is in the alphabet and if the next character is in the alphabet
            int j=0;
            int alphaflag1=0;
            int alphaflag2=0;
            char alphabet[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M',
                             'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
            for ( j; j <51 ; j++) {
                if(currentchar==alphabet[j]&&(currentchar!=' '&&currentchar!='\t'&&currentchar!='\n'&&currentchar!=0&&currentchar!='\f'&&currentchar!='\v'&&currentchar!='\b')){
                    alphaflag1=1;
                    isknown=1;
                }
                if(nextchar==alphabet[j]&&(nextchar!=' '&&nextchar!='\t'&&nextchar!='\n'&&nextchar!=0&&nextchar!='\f'&&nextchar!='\v'&&nextchar!='\b')){
                    alphaflag2=1;
                }
            }


            //if the current and next characters are both part of the alphabet
            if((alphaflag1==1)&&(alphaflag2==1)){
                if(length>15){
                    strcpy(string2, "");
                    length=0;
                }
                strncat(string2,&currentchar,1);
                length++;
                isknown=1;
                multip=1;
            }


            //if just the current character is a member of the alphabet
            if(alphaflag1==1&&alphaflag2==0){
                isknown=1;
                //add the current character to the string
                strncat(string2,&currentchar,1);
                length++;
                //and check to see if the current string2 is a key word
                int k=0;
                int istoken=0;
                for(k;k<=21;k++) {
                    //if current string is a keyword
                    if (strcmp(string2, lexsymbol[k]) == 0) {
                        isknown=1;
                        istoken=1;
                        symbolarray[numberoftokens]=lexsymbol[k];
                        tokenarray[numberoftokens]=k;
                        numberoftokens++;

                        //setting string2 to empty
                        strcpy(string2, "");
                        length=0;
                    }
                }


                //if it isnt then check the length and if the string length is 1, its an identifier
                if((length==1)&&istoken==0){
                    isknown=1;
                    //adding string to linked list
                    mover->next = (symboler *) malloc(sizeof(symboler));
                    strcpy(mover->next->symbols,string2);
                    //adding string to array
                    symbolarray[numberoftokens]=mover->next->symbols;
                    tokenarray[numberoftokens]=22;
                    numberoftokens++;
                    //setting string2 to empty
                    strcpy(string2,"");
                    length=0;
                }
                    //if its more than 1 long,the string is finished, and its not eof its unknown
                else if(istoken==0&&(length>1)&&strcmp(string2,"EOF")!=0){
                    isknown=1;
                    //adding string to linked list
                    mover->next = (symboler *) malloc(sizeof(symboler));
                    strcpy(mover->next->symbols,string2);
                    //adding string to array
                    symbolarray[numberoftokens]=mover->next->symbols;
                    tokenarray[numberoftokens]=22;
                    numberoftokens++;
                    //setting string2 to empty
                    strcpy(string2,"");
                    length=0;
                    multip=1;
                }
            }




            //this section is to see if it's an integer value
            j=0;
            int numflag1=0;
            int numflag2=0;
            char num[]={'0','1','2','3','4','5','6','7','8','9'};
            //if the current character is a number
            for ( j; j <= 9; j++) {
                if(currentchar==num[j]){
                    isknown=1;
                    numflag1=1;
                }
                //if the next character is a number
                if(nextchar==num[j]){
                    numflag2=1;
                }
            }

            //if the next character isnt a number but the current one is it must be a number value
            if(numflag1==1&&numflag2!=1){
                strncat(string2,&currentchar,1);
                length++;
                //adding string to linked list
                mover->next = (symboler *) malloc(sizeof(symboler));
                strcpy(mover->next->symbols,string2);
                //adding string to array
                symbolarray[numberoftokens]=mover->next->symbols;
                tokenarray[numberoftokens]=23;
                numberoftokens++;
                //setting string2 to empty
                strcpy(string2,"");
                length=0;
            }
                //if theyre both numbers
            else if(numflag1==1&&numflag2==1){
                //add the current number to the string
                strncat(string2,&currentchar,1);
                length++;
                multip=1;
            }





            //this section is for the symbols
            //if current character is a singular non multiple parter type of lexeme
            if(currentchar=='/'||currentchar=='*'||currentchar==';'||currentchar=='('||currentchar==')'||currentchar=='{'||currentchar=='}') {
                isknown=1;
                strncat(string2, &currentchar, 1);
                length++;
                //find and print its token
                int k = 0;
                for (k; k <= 21; k++) {
                    //if current string is a keyword
                    if (strcmp(string2, lexsymbol[k]) == 0) {
                        symbolarray[numberoftokens]=lexsymbol[k];
                        tokenarray[numberoftokens]=k;
                        numberoftokens++;
                        //setting string2 to empty
                        strcpy(string2, "");
                        length=0;
                    }
                }
            }

            //if the next symbol is an =
            if(nextchar=='='){
                //and currentchar is start of a two parter
                if(currentchar=='='||currentchar=='<'||currentchar=='>'||currentchar=='!'){
                    isknown=1;
                    strncat(string2, &currentchar, 1);
                    length++;
                    strncat(string2, &nextchar, 1);
                    length++;
                    stringlocation++;
                    //find and print its token
                    int k = 0;
                    for (k; k <= 21; k++) {
                        //if current string is a keyword
                        if (strcmp(string2, lexsymbol[k]) == 0) {
                            symbolarray[numberoftokens]=lexsymbol[k];
                            tokenarray[numberoftokens]=k;
                            numberoftokens++;
                            //setting string2 to empty
                            strcpy(string2, "");
                            length=0;
                        }
                    }
                }
            }

                //if the current character is an =,<,>, and the next one isnt =
            else if(currentchar=='='||currentchar=='>'||currentchar=='<'){
                isknown=1;
                strncat(string2, &currentchar, 1);
                length++;
                int k = 0;
                for (k; k <= 21; k++) {
                    //if current string is a keyword
                    if (strcmp(string2, lexsymbol[k]) == 0) {
                        symbolarray[numberoftokens]=lexsymbol[k];
                        tokenarray[numberoftokens]=k;
                        numberoftokens++;
                        //setting string2 to empty
                        strcpy(string2, "");
                        length=0;
                    }
                }
                //setting string2 to empty
                strcpy(string2, "");
                length=0;
            }



            //if the current character is + and the next one is +
            if(currentchar=='+'&&nextchar=='+'){
                isknown=1;
                strncat(string2, &currentchar, 1);
                length++;
                strncat(string2, &nextchar, 1);
                length++;
                stringlocation++;
                symbolarray[numberoftokens]=lexsymbol[3];
                tokenarray[numberoftokens]=3;
                numberoftokens++;
                //setting string2 to empty
                strcpy(string2, "");
                length=0;
            }


            //if current is + and next is not
            if(currentchar=='+'&&nextchar!='+'){
                isknown=1;
                strncat(string2, &currentchar, 1);
                length++;
                symbolarray[numberoftokens]=lexsymbol[10];
                tokenarray[numberoftokens]=10;
                numberoftokens++;
                //setting string2 to empty
                strcpy(string2, "");
                length=0;
            }


            //if the current character is - and the next one is -
            if(currentchar=='-'&&nextchar=='-'){
                isknown=1;
                strncat(string2, &currentchar, 1);
                length++;
                strncat(string2, &nextchar, 1);
                length++;
                stringlocation++;
                //adding string to linked list
                mover->next = (symboler *) malloc(sizeof(symboler));
                strcpy(mover->next->symbols,string2);
                //adding string to array
                symbolarray[numberoftokens]=mover->next->symbols;
                tokenarray[numberoftokens]=4;
                numberoftokens++;
                //setting string2 to empty
                strcpy(string2, "");
                length=0;
            }


            //if current is + and next is not
            if(currentchar=='-'&&nextchar!='-'){
                isknown=1;
                strncat(string2, &currentchar, 1);
                length++;
                symbolarray[numberoftokens]=lexsymbol[11];
                tokenarray[numberoftokens]=11;
                numberoftokens++;
                //setting string2 to empty
                strcpy(string2, "");
                length=0;
            }

            //this section is for unknowns

            j=0;
            for ( j; j <=51 ; j++) {
                if (currentchar == alphabet[j]) {
                    isknown=1;
                }
            }
            j=0;
            for ( j; j <10 ; j++) {
                if (currentchar == num[j]) {
                    isknown=1;
                }
            }
            j=0;
            for (j; j <= 21; j++) {
                //if current string is a known symbol
                if (strcmp(string2, lexsymbol[j]) == 0) {
                    isknown=1;
                }
            }


            char stringcomp[]={""};
            char holderstring[]={""};
            strcpy(holderstring,string2);
            strncat(holderstring, &currentchar, 1);
            length++;
            if((isknown!=1)&&(currentchar==' '||currentchar=='\t'||currentchar=='\n'||currentchar==0||currentchar=='\f'||currentchar=='\v'||currentchar=='\b'||(strcmp(holderstring,stringcomp)==0)||currentchar=='\r'
                              ||currentchar=='\f')){
                isknown=1;
                //setting string2 to empty
                strcpy(string2,"");
                length=0;
            }


            //if the current character is not known it is unknown
            if(isknown==0) {
                {
                    strncat(string2, &currentchar, 1);
                    length++;
                    //adding string to linked list
                    mover->next = (symboler *) malloc(sizeof(symboler));
                    strcpy(mover->next->symbols,string2);
                    //adding string to array
                    symbolarray[numberoftokens]=mover->next->symbols;
                    tokenarray[numberoftokens]=24;
                    numberoftokens++;
                    //setting string2 to empty
                    strcpy(string2, "");
                    length = 0;
                }
            }

            //if the character is not one wipe the length;
            if(multip!=1){
                length=0;
            }



            stringlocation++;

        }


        //now that we have collected the tokens we enact the syntax parser


    }



    S(tokenarray, symbolarray);


    if(tokenplace!=numberoftokens){
        errorcode=1;
    }
//check for error
    if(errors==0&&errorcode==1){
        //error
       printf("\nError encounter: The next lexeme was %s and the next token was %s\n",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    }

    if(errorcode==0) {
        printf("\nSyntax Validated");
    }

    //closing the file
    fclose(fptr);
    //freeing memory
    free(tokenarray);
    free(symbolarray);
    free(head);


    return errorcode;
}



void S(int *tokenarray,char **symbolarray){
    //S ::= V=E | read(V) | write(V) | do { S } while (C) | S;S
    if(tokenarray[tokenplace]==24&&errorcode!=1){
        //error
        errors=1;
        errorcode=1;
        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    }
    switch (tokenarray[tokenplace]) {
        //V=E
        case 22:
            VE(tokenarray,symbolarray);
            break;
            //readwrite
        case 18:
        case 19:
            readwrite(tokenarray,symbolarray);
            break;
            //do
        case 21:
            dowhile(tokenarray,symbolarray);
            break;
        default:
            //error?
            if(tokenplace<numberoftokens&&errorcode!=1) {
                errorcode = 1;
                errors=1;
                printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
            }
            break;
    }
    if(tokenarray[tokenplace]==24&&errorcode!=1){
        //error
        errorcode=1;
        errors=1;
        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    }
    if(tokenarray[tokenplace]==9){
        //increment token
        tokenplace++;
        S(tokenarray,symbolarray);
    }
    if(tokenarray[tokenplace+1]==17&&tokenarray[tokenplace]==9&&errorcode!=1){
        //error
        errorcode=1;
        errors=1;
        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    }
}
void VE(int *tokenarray,char **symbolarray){
    if(tokenarray[tokenplace]==24&&errorcode!=1){
        //error
        errorcode=1;
        errors=1;
        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    }
    //increment token
    tokenplace++;
//check for error (if token isnt = sign)
    if(tokenarray[tokenplace]!=6&&errorcode!=1){
        //error
        errorcode=1;
        errors=1;

        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    } else{
        //increment token
        tokenplace++;
        //if it's all good go to E
        E(tokenarray,symbolarray);
    }


}
void readwrite(int *tokenarray,char **symbolarray){
    if(tokenarray[tokenplace]==24&&errorcode!=1){
        //error
        errorcode=1;
        errors=1;

        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    }
    //increment token
    tokenplace++;
//check for error (if token isn't left paren)
    if(tokenarray[tokenplace]!=14&&errorcode!=1){
        //error
        errorcode=1;
        errors=1;

        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    } else{
        //increment token
        tokenplace++;
        //check for error (if token isn't an identity)
        if(tokenarray[tokenplace]!=22&&errorcode!=1){
            //error
            errorcode=1;
            errors=1;

            printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
        } else
            //increment token
            tokenplace++;
        //check for error (if token isn't a right paren)
        if(tokenarray[tokenplace]!=15&&errorcode!=1){
            //error
            errorcode=1;
            errors=1;

            printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
        } else{
            tokenplace++;
        }
    }
}
void dowhile(int *tokenarray,char **symbolarray){
//increment token
    if(tokenarray[tokenplace]==24&&errorcode!=1){
        //error
        errorcode=1;
        errors=1;

        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    }
    tokenplace++;
    //check for error (if token isn't left brace)
    if(tokenarray[tokenplace]!=16&&errorcode!=1){
        //error
        errorcode=1;
        errors=1;

        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    } else{
        //increment token
        tokenplace++;
        S(tokenarray,symbolarray);
        //increment token
        //if token is do again call loop
        if(tokenarray[tokenplace]==21){
            dowhile(tokenarray,symbolarray);
        }
        //check for error (if token isn't right brace)
        if(tokenarray[tokenplace]!=17&&errorcode!=1){
            //error
            errorcode=1;
            errors=1;

            printf("\nError encounter: The next lexeme was %s and the next token was %s\n",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
        } else{
            //increment token
            tokenplace++;
            //check for error (if token isn't while)
            if(tokenarray[tokenplace]!=20&&errorcode!=1){
                //error
                errorcode=1;
                errors=1;

                printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
            } else{
                //increment token
                tokenplace++;
                //check for error (if token isn't left paren)
                if(tokenarray[tokenplace]!=14&&errorcode!=1){
                    //error
                    errorcode=1;
                    errors=1;
                    printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
                } else{
                    //increment token
                    tokenplace++;
                    C(tokenarray,symbolarray);
                    //increment token

                    tokenplace++;


                }
            }
        }
    }
}

void C(int *tokenarray,char **symbolarray){
    //C ::= E < E | E > E | E == E | E != E | E <= E | E >= E
    if(tokenarray[tokenplace]==24&&errorcode!=1){
        //error
        errorcode=1;
        errors=1;
        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    }
    E(tokenarray,symbolarray);
    //decide which to go in to
    switch (tokenarray[tokenplace]) {
        //equal
        case 0:
            //notequal
        case 1:
        case 2:
        case 5:
        case 7:
        case 8:
            //increment token
            tokenplace++;
            //go to E
            E(tokenarray,symbolarray);
            break;

        default:
            //error
            if(errorcode!=1){
        errorcode = 1;
        errors = 1;
        printf("Error encounter: The next lexeme was %s and the next token was %s", symbolarray[tokenplace],
               lextoken[tokenarray[tokenplace]]);
    }
            break;

    }

}

void E(int *tokenarray,char **symbolarray){
//E ::= T | E + T | E - T
    if(tokenarray[tokenplace]==24&&errorcode!=1){
        //error
        errorcode=1;
        errors=1;
        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    }
//go to T
    T(tokenarray,symbolarray);
//if next token is + or -
    if(tokenarray[tokenplace]==10||tokenarray[tokenplace]==11){
        //increment token
        tokenplace++;
        E(tokenarray,symbolarray);
    }
}

void T(int *tokenarray,char **symbolarray){
    if(tokenarray[tokenplace]==24&&errorcode!=1){
        //error
        errorcode=1;
        errors=1;

        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    }
//T ::= F | T * F | T / F
//go to F
    F(tokenarray,symbolarray);
//if next token is * or /
    if(tokenarray[tokenplace]==12||tokenarray[tokenplace]==13){
        //increment token
        tokenplace++;
        T(tokenarray,symbolarray);
    }
}

void F(int *tokenarray,char **symbolarray){
    if(tokenarray[tokenplace]==24&&errorcode!=1){
        //error
        errorcode=1;
        errors=1;

        printf("Error encounter: The next lexeme was %s and the next token was %s",symbolarray[tokenplace], lextoken[tokenarray[tokenplace]]);
    }
//F ::= (E) | O | N | V
    switch (tokenarray[tokenplace]){
        //parenthesis
        case 14:
            //increment token
            tokenplace++;
            //Go E
            E(tokenarray,symbolarray);
            //increment token
            tokenplace++;
            break;

            //integer
        case 23:
            //increment token
            tokenplace++;
            break;
            //variable(including O)
        case 22:
            //increment token
            tokenplace++;
            //if next token is ++ or --
            if(tokenarray[tokenplace]==3||tokenarray[tokenplace]==4){
                //increment token
                tokenplace++;
            }
            break;
        default:
            //error
            if(errorcode!=1){
        errorcode = 1;
        errors = 1;
        printf("Error encounter: The next lexeme was %s and the next token was %s", symbolarray[tokenplace],
               lextoken[tokenarray[tokenplace]]);
    }
            break;
    }
}

