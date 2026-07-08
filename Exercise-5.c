#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct Node{
    char data;
    struct Node* right;
    struct Node* left;
}Node;

Node* queue[MAX];
int tail=0;
int head=0;

Node* newNode(int data){
    Node* newnode = (Node*)malloc(sizeof(Node));   
    newnode->data=data;         //αναθέτουμε την τιμή του κόμβου
    newnode->left=NULL;     //αρχικοποιούμε τα παιδιά του κόμβου σε NULL
    newnode->right=NULL;
    return newnode;
}


void enqueue(Node* newnode){
    if(newnode!=NULL){      //ελέγχουμε αν ο κόμβος που θέλουμε να προσθέσουμε είναι NULL
        if(tail==MAX-1){        //έλεγχος υπερχείλησης
            printf("Queue is full\n");
        }
        else{
            queue[tail++]=newnode;  //εισαγωγή του κόμβου στην ουρά και αύξηση του δείκτη tail
        }
    }   
}

Node* dequeue(){
    if(head==tail){     //έλεγχος αν η ουρά είναι άδεια
        return NULL;
    }else {
        return queue[head++];       //επιστροφή στοιχείου και αύξηση του δείκτη head γιατί το head μεχρι το dequeue είναι πάντα 0
    }                               //και σβήνουμε πάντα απο το head άρα όσο σβήνουμε αυξάνεται
}

Node* insert(Node* root,int data){   
    if(root==NULL){            //έλεγχος αν το δεντρο ειναι κενό
        return newNode(data);
    }
    head=tail=0;        //αρχικοποιούμε την ουρά για την εισαγωγή του νέου κόμβου
    enqueue(root);          //εισαγωγή της ρίζας στην ουρά 
    while(head<tail){       //από τον δεύτερο κόμβο και μετά, ελέγχουμε κάθε κόμβο που βγαίνει από την ουρά για να βρούμε το πρώτο κενό παιδί και να τον τοποθετήσουμε εκεί
        Node* temp=dequeue();    
        if(temp->left==NULL){
            temp->left=newNode(data);
            break;   
        }else {
            enqueue(temp->left);
        }
        if(temp->right==NULL){
            temp->right=newNode(data);
            break;
        }else{ 
            enqueue(temp->right);  
        }
    }
    return root;
}

void levelorder(Node* root){
    head=tail=0;    //αρχικοποίηση ουράς
    enqueue(root);      //ξεκινάμε από τη ρίζα και προσθέτουμε τους κόμβους στην ουρά με τη σειρά που τους επισκεπτόμαστε
    while(head<tail){
        Node* temp=dequeue();       //ελέγχουμε τους κόμβους που βγαίνουν, τυπώνουμε και προσθέτουμε τα παιδιά στην ουρά
        printf("%c ",temp->data);
        enqueue(temp->left);
        enqueue(temp->right);
        
    }
}

void preorder(Node* root){          //μεσω αναδρομης επισκεπτομαστε τον τρεχοντα κομβο και μετα τα παιδια του
    if(root!=NULL){        
        printf("%c ",root->data);
        preorder(root->left);       //βαζουμε πρωτα το αριστερο παιδι για να επισκεφτουμε πρωτα το αριστερο υποδεντρο και μετα το δεξι
        preorder(root->right);
    }
    else return;
}

void postorder(Node* root){     //μεσω αναδρομης επισκεπτομαστε τα παιδια του τρεχοντα κομβου και μετα τον τρεχοντα κομβο
    if(root!=NULL){        
        postorder(root->left);         //ξεκιναμε με το αριστερο παιδί και βάλαμε print τελευταία ωστε να τυπώσει το φυλλο
        postorder(root->right);       //και επειτα να καλει τις υπολοιπες μεσω return
        printf("%c ",root->data);   
        }
    else return;
}

Node* buildTreePost(char inorder[], char postorder[], int inStart, int inEnd, int* postIndex){
    if(inStart>inEnd){          //αν δεν υπαρχουν στοιχεια στο υποδεντρο επιστρεφουμε NULL για να σταματησει η αναδρομη
        return NULL;
    }
    char rootData=postorder[(*postIndex)--];        //ο τελευταίος κόμβος του postorder είναι η ρίζα του δέντρου, οπότε τον παίρνουμε και μειώνουμε το postIndex για να πάρουμε τον επόμενο κόμβο στην επόμενη κλήση
    
    Node* root=newNode(rootData);

    if(inStart==inEnd){     //αν το υποδεντρο έχει μόνο ένα κομβο, είναι φυλλο και τον επιστρέφουμε
        return root;
    }

    int InsideIndex=-1;

    for(int i=inStart;i<=inEnd;i++){        //εντοπίζουμε τη θέση της ρίζας στο inorder για να χωρίσουμε το δέντρο σε αριστερό και δεξιό υποδέντρο
        if(inorder[i]==rootData){
            InsideIndex=i;
            break;
        }
    }

    //κατασκευάζουμε πρωτα το δεξι υπόδεντρο γιατι η postorder διαβάζεται από κάτω προς τα πάνω
    root->right=buildTreePost(inorder, postorder, InsideIndex+1, inEnd, postIndex);
    //έπειτα αναπλάθουμε το αριστερό με την ίδια λογική
    root->left=buildTreePost(inorder, postorder, inStart, InsideIndex-1, postIndex);
    return root;
}

Node* buildTreePre(char inorder[], char preorder[],int Start, int End, int* preIndex){
    if(Start>End){      //ίδια με την buildTreePost
        return NULL;
    }
    char rootData=preorder[(*preIndex)++];    //ο πρώτος κόμβος του preorder είναι η ρίζα του δέντρου
    
    Node* root=newNode(rootData);

    if(Start==End){     //ίδια με την buildTreePost
        return root;
    }
    int InsideIndex=-1;
    for(int i=Start;i<=End;i++){            //ίδια με την buildTreePost
        if(inorder[i]==rootData){
            InsideIndex=i;
            break;
        }
    }
    root->left=buildTreePre(inorder, preorder, Start, InsideIndex-1, preIndex);    //κατασκευάζουμε πρωτα το αριστερό υποδέντρο γιατι η preorder διαβάζεται από πάνω προς τα κάτω
    root->right=buildTreePre(inorder, preorder, InsideIndex+1, End, preIndex);      //έπειτα αναπλάθουμε το δεξιό με την ίδια λογική
    return root;
}


void freeTree(Node* root){     //μεσω αναδρομης απελευθερωνουμε τη μνήμη που καταλαμβάνει το δέντρο
    if(root!=NULL){
        freeTree(root->left);      //απελευθερώνουμε πρώτα τα παιδιά του κόμβου και μετά τον ίδιο τον κόμβο
        freeTree(root->right);
        free(root);
    }
    else return;
}

int main(){
    char inorder1[100];
    char postorderarray[100];
    char inorder2[100];
    char preorderarray[100];
    int preIndex=0;
    Node* root1=NULL;
    Node* root2=NULL;
    int n1=0;
    printf("Enter the number of nodes you want to insert: \n");
    scanf("%d",&n1); 

    printf("Enter the postorder traversal of the first tree: \n");
    scanf("%s",postorderarray);

    printf("Enter the inorder traversal of the first tree: \n");
    scanf("%s",inorder1);
    
    int n=strlen(inorder1);     //πληθος κόμβων π´ρωτου δέντρου
    int postIndex=n-1;          //η postorder διαβάζεται από κάτω προς τα πάνω, οπότε ξεκινάμε από το τέλος του πίνακα
    root1=buildTreePost(inorder1, postorderarray, 0, n-1, &postIndex);      //ανάπλαση πρώτου δέντρου

    printf("]\n");
    printf("Level order traversal of the first tree is: \n");       //ελεγχουμε την ορθότητα της ανάπλασης με τις τρεις διαπεράσεις
    levelorder(root1);
    printf("\n");
    printf("Preorder traversal of the first tree is: \n");
    preorder(root1);
    printf("\n");
    printf("Postorder traversal of the first tree is: \n");
    postorder(root1);
    printf("\n");

    printf("Enter the preorder traversal of the second tree: \n");
    scanf("%s",preorderarray);

    printf("Enter the inorder traversal of the second tree: \n");
    scanf("%s",inorder2);
    int n2 = strlen(inorder2);      //πληθος κόμβων δεύτερου δέντρου
    root2 = buildTreePre(inorder2, preorderarray, 0, n2-1, &preIndex);    //ανάπλαση δεύτερου δέντρου
    
    printf("Level order traversal of the second tree is: \n");      //ελεγχουμε την ορθότητα της ανάπλασης με τρεις διαφορετικές διατάξεις
    levelorder(root2);
    printf("\n");
    printf("Preorder traversal of the second tree is: \n");
    preorder(root2);
    printf("\n");
    printf("Postorder traversal of the second tree is: \n");
    postorder(root2 );
    printf("\n");

    freeTree(root1);        //απελευθερωση μνημης για τα δυο δεντρα
    freeTree(root2);
    return 0;
}