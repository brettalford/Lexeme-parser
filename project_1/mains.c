/*
=============================================================================
Title : lexeme parser
Description : This program determines lexemes and their respective tokens
Author : Brett Alford 
Date : 10/30/2023
Version : 1.0
Usage : Compile and run this program using the GNU C compiler
Notes : program requires second argument
C Version : default
=============================================================================
*/




#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]) {


    FILE *fptr;




    if(argc==1){
        printf("Argument not found\n");
    }
    //if the file is not found
    if ((fptr=fopen(argv[1],"r"))==NULL){
        printf("File not found\n");
    }
    //if the file exists Open a file in read mode
    fptr = fopen(argv[1], "r");



    //create string variables
    char myString[100];
    char instring[]={""};
    char string2[]={""};

//array values
    char *lexsymbol[]={"==","<=",">=","++","--","!=","=","<",">",";","+","-","*","/","(",")","{","}","read","write","while","do",};
    char *lextoken[]={"EQUAL_OP","LEQUAL_OP","GEQUAL_OP","INC_OP","DEC_OP","NEQUAL_OP","ASSIGN_OP","LESSER_OP","GREATER_OP","SEMICOLON","ADD_OP","SUB_OP","MULTI_OP","DIV_OP","LEFT_PAREN"
            ,"RIGHT_PAREN","LEFT_CBRACE","RIGHT_CBRACE","KEY_READ","KEY_WRITE","KEY_WHILE","KEY_DO","IDENT","INT_LIT","UNKNOWN"};
    char num[]={'0','1','2','3','4','5','6','7','8','9'};
    char alphabet[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M',
                     'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

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
            length++;
            int isknown=0;
            //value of current character
            char currentchar=instring[stringlocation];
            //value of next character
            char nextchar=instring[stringlocation+1];



            //this section determines if the current character is in the alphabet and if the next character is in the alphabet
            int j=0;
            int alphaflag1=0;
            int alphaflag2=0;
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
                strncat(string2,&currentchar,1);
                isknown=1;
                multip=1;
            }


            //if just the current character is a member of the alphabet
            if(alphaflag1==1&&alphaflag2==0){
                isknown=1;
                //add the current character to the string
                strncat(string2,&currentchar,1);
                //and check to see if the current string2 is a key word
                int k=0;
                int istoken=0;
                for(k;k<=21;k++) {
                    //if current string is a keyword
                    if (strcmp(string2, lexsymbol[k]) == 0) {
                        isknown=1;
                        istoken=1;
                        //print out the symbol and token
                        printf(lexsymbol[k]);
                        printf("    ");
                        printf(lextoken[k]);
                        printf("\n");

                        //setting string2 to empty
                        strcpy(string2, "");
                        length=0;
                    }
                }


                //if it isnt then check the length and if the string length is 1, its an identifier
                if((length==1)&&istoken==0){
                    isknown=1;
                    printf(string2);
                    printf("    ");
                    printf((lextoken[22]));
                    printf("\n");
                    //setting string2 to empty
                    strcpy(string2,"");
                    length=0;
                }
                    //if its more than 1 long,the string is finished, and its not eof its unknown
                else if(istoken==0&&(length>1)&&strcmp(string2,"EOF")!=0){
                    isknown=1;

                    printf(string2);
                    printf("    ");
                    printf(lextoken[24]);
                    printf("\n");
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
                printf(string2);
                printf("    ");
                printf(lextoken[23]);
                printf("\n");
                //setting string2 to empty
                strcpy(string2,"");
                length=0;
            }
                //if theyre both numbers
            else if(numflag1==1&&numflag2==1){
                //add the current number to the string
                strncat(string2,&currentchar,1);
                multip=1;
            }





            //this section is for the symbols
            //if current character is a singular non multiple parter type of lexeme
            if(currentchar=='/'||currentchar=='*'||currentchar==';'||currentchar=='('||currentchar==')'||currentchar=='{'||currentchar=='}') {
                isknown=1;
                strncat(string2, &currentchar, 1);
                //find and print its token
                int k = 0;
                for (k; k <= 21; k++) {
                    //if current string is a keyword
                    if (strcmp(string2, lexsymbol[k]) == 0) {
                        //print out the symbol and token
                        printf(lexsymbol[k]);
                        printf("    ");
                        printf(lextoken[k]);
                        printf("\n");
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
                    strncat(string2, &nextchar, 1);
                    stringlocation++;
                    //find and print its token
                    int k = 0;
                    for (k; k <= 21; k++) {
                        //if current string is a keyword
                        if (strcmp(string2, lexsymbol[k]) == 0) {
                            //print out the symbol and token
                            printf(lexsymbol[k]);
                            printf("    ");
                            printf(lextoken[k]);
                            printf("\n");
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
                int k = 0;
                for (k; k <= 21; k++) {
                    //if current string is a keyword
                    if (strcmp(string2, lexsymbol[k]) == 0) {
                        //print out the symbol and token
                        printf(lexsymbol[k]);
                        printf("    ");
                        printf(lextoken[k]);
                        printf("\n");
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
                strncat(string2, &nextchar, 1);
                stringlocation++;
                //print out the symbol and token
                printf(lexsymbol[3]);
                printf("    ");
                printf(lextoken[3]);
                printf("\n");
                //setting string2 to empty
                strcpy(string2, "");
                length=0;
            }


            //if current is + and next is not
            if(currentchar=='+'&&nextchar!='+'){
                isknown=1;
                strncat(string2, &currentchar, 1);
                //print out the symbol and token
                printf(lexsymbol[10]);
                printf("    ");
                printf(lextoken[10]);
                printf("\n");
                //setting string2 to empty
                strcpy(string2, "");
                length=0;
            }


            //if the current character is - and the next one is -
            if(currentchar=='-'&&nextchar=='-'){
                isknown=1;
                strncat(string2, &currentchar, 1);
                strncat(string2, &nextchar, 1);
                stringlocation++;
                //print out the symbol and token
                printf(lexsymbol[4]);
                printf("    ");
                printf(lextoken[4]);
                printf("\n");
                //setting string2 to empty
                strcpy(string2, "");
                length=0;
            }


            //if current is + and next is not
            if(currentchar=='-'&&nextchar!='-'){
                isknown=1;
                strncat(string2, &currentchar, 1);
                //print out the symbol and token
                printf(lexsymbol[11]);
                printf("    ");
                printf(lextoken[11]);
                printf("\n");
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
                    printf("%c",currentchar);

                    //print unknown token
                    printf("    ");
                    printf(lextoken[24]);
                    printf("\n");
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
    }
    fclose(fptr);
    return 0;
}
