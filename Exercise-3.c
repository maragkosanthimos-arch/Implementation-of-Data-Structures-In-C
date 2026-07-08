#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Node{
    int data;
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
    enqueue(root);   //ξεκινάμε από τη ρίζα και προσθέτουμε τους κόμβους στην ουρά με τη σειρά που τους επισκεπτόμαστε
    int level=0;
    while(head<tail){
        int size=tail-head;
        printf("\nLevel %d: \n",level++);
        for(int i=0;i<size;i++){
        Node* temp=dequeue();       //ελέγχουμε τους κόμβους που βγαίνουν, τυπώνουμε και προσθέτουμε τα παιδιά στην ουρά
        printf("%d ",temp->data);
        enqueue(temp->left);
        enqueue(temp->right);
        
        }
    }
}

void preorder(Node* root){          //μεσω αναδρομης επισκεπτομαστε τον τρεχοντα κομβο και μετα τα παιδια του
    if(root!=NULL){        
        printf("%d ",root->data);
        preorder(root->left);       //βαζουμε πρωτα το αριστερο παιδι για να επισκεφτουμε πρωτα το αριστερο υποδεντρο και μετα το δεξι
        preorder(root->right);
    }
    else return;
}

void postorder(Node* root){     //μεσω αναδρομης επισκεπτομαστε τα παιδια του τρεχοντα κομβου και μετα τον τρεχοντα κομβο
    if(root!=NULL){        
        postorder(root->left);         //ξεκιναμε με το αριστερο παιδί και βάλαμε print τελευταία ωστε να τυπώσει το φυλλο
        postorder(root->right);       //και επειτα να καλει τις υπολοιπες μεσω return
        printf("%d ",root->data);   
        }
    else return;
}

int main(){
    Node* root=NULL;
    int n=0;
    printf("Enter the number of nodes you want to insert: \n");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int data;
        printf("Enter the data of node %d: \n",i+1);
        scanf("%d",&data);
        root=insert(root,data);
    }
    printf("Level order traversal of the tree is: \n"); 
    levelorder(root);
    printf("\n");
    printf("Preorder traversal of the tree is: \n");
    preorder(root);
    printf("\n");
    printf("Postorder traversal of the tree is: \n");
    postorder(root);
    printf("\n");
    return 0;
}