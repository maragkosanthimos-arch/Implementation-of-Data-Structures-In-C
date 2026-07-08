#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STCK_SIZE 50
#define MAX 1000

typedef struct{
    char data[STCK_SIZE];       //δεδομενα της στοίβας
    int pointer;           //sp=stack pointer
} Stack;

void Initialization(Stack* pntr){       //αρχικοποίηση της στοίβας 
    pntr->pointer = -1;
}

void push(Stack* pntr, char c){          //υλοποίση εντολής push
    if(pntr->pointer==STCK_SIZE-1){
        printf("The stack is full. Stack Overflow \n");
        return ;
    }
    pntr->data[++(pntr->pointer)]=c;        /*ανάθεσε το γράμμα c στη θέση που δειχνει ο sp ώστε να αναλύεται 1-1 για 
                                                να ειναι πιο εύκολη η αναγνωριση των παρενθέσεων*/
}

char pop(Stack* pntr){
    if (pntr->pointer == -1){
        printf("The stack is empty. Error. \n");
        return '\0';
    }
    return pntr->data[(pntr->pointer)--];   //μετα απο καθε pop μειωνει τον sp κατα ενα για να δειχνει στο νεο πανω-πανω στοιχειο
}                                           // επιστρέφει τον χαρακτήρα

void readString(char *str, int size) {
    printf("Give string: ");
    fgets(str, size, stdin);
}

int check(Stack *pntr, char *str,int size){
    int numofbrackets=0;
    str = (char *)malloc(size * sizeof(char));      //δυναμικη δεσμευση πίνακα
    if (str == NULL) {
        printf("Memory Error\n");
        return 1;
    }

    readString(str, size);

    for(int i=0;i<strlen(str);i++){
        char c=str[i];                
        if(c=='['||c=='{'||c=='('){     
        push(pntr,str[i]);          // σε καθε επανάληψη βάλε όποιο αριστερό μέλος βλέπεις 
        numofbrackets++;
        }
        else if(c==']'||c=='}'||c==')'){    // κάθε φορα που βρίσκεις ολοκληρωμένη παρένθεση κανει numofbrackets++
            numofbrackets++;

            if(pntr->pointer==-1){
                free(str);
                return 0;
            }

            char top = pop(pntr);       //top = πάνω πάνω στοιχείο στοίβας
            if(c==']' && top!='['||c=='}'&& top!='{'||c==')'&& top!='('){   //διασφάλιση σωστής σειράς. αν διαβάσεις δεξί μέλος
                free(str);                                              //και ειναι ίδιου είδους με το top, ταίριαξες ζευγάρι παρενθέσεων  
                return 0;
            }
        }
    }
        if(numofbrackets==0 ){
            printf("No brackets in this sentence\n");
            free(str);
            return 0;
        } else if(pntr->pointer!=-1){
            free(str);
            return 0;
        }
        free(str);
        return 1;
}

int main() {
    Stack s;
    Initialization(&s);
    char* str;
    int result=check(&s,str,70);
    printf("Output: %d\n",result);
    return 0;
}