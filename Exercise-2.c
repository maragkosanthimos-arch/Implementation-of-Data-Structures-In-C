#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* right;
    struct Node* left;
}Node;

Node* binaryTreeSearch(Node* root,int key){   //βάλε ρίζα με το κλειδί της. όσο ο κόμβος δεν ειναι null 
    Node* child=root;                         //αν το κλειδί είναι ίδιο με την τιμή του κόμβου τη βρήκες. αλλιώς αν είναι μικρότερο
    while(child!=NULL){                    //πήγαινε αριστερά και συνέχισε ψάξιμο(για ενδοδιατεταγμένο δέντρο)
        if(key==child->data)
            return child;
        else if(key<child->data)
            child=child->left;
        else child=child->right;
    }
    return NULL;
}

Node* insert(Node* root, int key){
    Node* newNode=(Node*)malloc(sizeof(Node));    //δημιούργησε δυναμικό κόμβο 
    newNode->data=key;                          //ανάθεσε του τιμή που έδωσε ο χρήστης
    newNode->left=NULL;     //αρχικοποίηση παιδιών σε null
    newNode->right=NULL;
    if(root==NULL)      //αν δεντρο κενό, ο νεός κόμβος γίνεται ρίζα
        return newNode;                 

    Node* parent=NULL;
    Node* child=root;           //θέτουμε παιδί και γονιό για την εύρεση θέσης μέσω ενδοδιατεταγμένης διάταξης

    while(child!=NULL){      
        parent=child;   //όσο ο κομβος δεν ειναι null, συγκρινε την τιμή του με την τιμή χρήστη. αν κλειδι μικρότερο
        if(key <= child->data)
        child = child->left;
    else
        child = child->right;
    }
    if(key<parent->data){       //όταν παιδί null βρέθηκε η θέση εισαγωγής 
        parent->left=newNode;   //αν κόμβος μεγαλύτερος απο γονιό, βαλτον δεξία αλλιώς αριστερά
    } else
        parent->right=newNode;

    return root;
}

Node* delete(Node* root,int key){
    Node* current=NULL;
    Node* result=binaryTreeSearch(root,key);        //βρίσκω τον κόμβο που ψάχνω και τον αναθέτω σε μεταβλητή
    if(result==NULL){
        printf("Root you're looking to delete doesn't exist\n");        //μηνυμα αν δεν υπάρχει
        return root;
    }
    if(result->left==NULL && result->right!=NULL){      //αν κόμβος έχει μόνο δεξί υπόδεντρο 
        result->data=(result->right)->data;         //επέλεξε την τιμη του παιδιού του κομβου που διαγράφεις και
        result->right=current;                      //ανάθεσε την σε αυτόν. 
        free(result->right);            //σβήσε το παιδί το οποίο ειναι πλεον ο νέος κόμβος
        return root;
    }
    if(result->left == NULL && result->right == NULL){      //αν κόμβος είναι φύλλο, σβήστον χωρις αλλαγή δεικτών 
        free(result);
        return root;
    }
    if(result->left!=NULL && result->right==NULL){      //αν κόμβος έχει μονο αριστερό υπόδεντρο 
        result->data=(result->left)->data;      //λειτούργησε όπως πάνω απλά για το αριστερό παιδί 
        result->left=current;
        free(result->left);
        return root;
    }
    Node* child=result->left;       // αν κόμβος έχει και δεξί και αριστερό υπόδεντρο ανάθεσε παιδί στο αριστερό
    Node* parent=NULL;              // ακολουθάμε την μέθοδο αντικατάστασης όπου αντικαθιστούμε με το δεξιότερο φύλλο του αριστερού υπόδεντρου
    while(child->right!=NULL){  //κατεβαίνουμε στο δεξιότερο φυλλο μέσω επαναλήψεων
        parent=child;
        child=child->right;
        }
    result->data=child->data;   //βάζω στον κόμβο που θέλω να διαγράψω την τιμήτου δεξιότερου φύλλου
    if(parent->right==result)      //αν τιμη παιδιου ίση με του κομβου που θα διαγραφεί, θέσε παιδί null και αποδεύσμευσε το
        parent->right=child->left;
    else parent->right=child->left;
    free(child);
    return root; 
}



int main(){
    Node* root=NULL;
    root=insert(root,56);
    root=insert(root,48);
    root=insert(root,16);
    root=insert(root,6);
    root=insert(root,50);
    root=insert(root,60);
    root=delete(root,56);
    Node* result=binaryTreeSearch(root,56);
    if(result==NULL){
        printf("Not found\n");
    } else printf("Found\n");
    
    return 0;
}

