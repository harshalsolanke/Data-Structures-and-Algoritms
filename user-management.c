#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 200
#define order 4
#define maxsize 4
typedef struct BNode
{
    void **pointers;
    char **keys;
    struct BNode *parent;
    bool is_leaf;
    int num_keys;
    struct BNode *next;
    struct BNode* prev ;
} BNode;
typedef struct Lpg
{
    char lname[SIZE];
    char laccnumber[SIZE];
    bool takenLpgSubsidy;
} Lpg;


typedef struct BankAccount
{
    char bname[SIZE];
    char PANno[SIZE];
    char bankName[SIZE];
    char accountNumber[SIZE];
    int amountDeposited;
    
     Lpg *lpgnode;
    //struct BankAccount *bnext;
} BankAccount;
typedef struct PanNode
{
    char p_name[SIZE];
    char p_address[SIZE];
    char PanNo[SIZE];
    char p_adhar[SIZE];
    // struct PanNode *p_next;
    BankAccount **bankAccount;
    int noofaccounts ;
} PanNode;

typedef struct AadharNode
{
    char a_name[SIZE];
    char a_address[SIZE];
    char AadharNo[SIZE];
    PanNode **pannode;
    int numofpan;
} AadharNode;



typedef union NodeUnion
{
    AadharNode *aadharNode;
    PanNode *panNode;
    BankAccount *bankAccount ;
} NodeUnion;

typedef struct record
{
    NodeUnion node;
    enum
    {
        AADHAR,
        PAN ,
        BANK 
    } tag;
} record;
typedef struct QueueNode {
    BNode *bnode;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;



AadharNode *CreateAdharNode(char name[], char address[], char aadharno[]);
BNode *InitializeList();
BNode *CreateBNode(record *r, bool isleaf, char key[]);
BNode *SplitLeafNode(BNode *root, char keyval[], record *r);
BNode *InsertInParent(BNode *Parent, BNode *siblingNode, BNode *lptr, char key[]);
BNode *SplitParent(BNode *Parent, BNode *siblingNode, BNode *rootnode, char key[]);
BNode *Insert(BNode *root, char key[], record *r);
void Display(BNode *root);
PanNode *createPanNode(char name[], char address[], char panNo[], char Adharno[]);
 record* FindDataNode(char key[] , BNode* root);
BNode* InitializePanList();
void FirstQuestion(BNode *root);
Queue *createQueue();
BNode *dequeue(Queue *queue);
void levelOrderTraversal(BNode *root);
void enqueue(Queue *queue, BNode *bnode);
 void PrintTree(BNode* root);
void SecondQuestion(BNode* root);
void DisplayPanList(BNode* root );
void  LinkAadharWithPanTree(BNode* root , BNode* plist);
BNode* InitializeBankAccountList();
BankAccount*  appendToBankList( char name[], char Bankname[], char AccountNumber[], int amount, char Panno[]);
void InitializeLpg(BNode* root);
Lpg* appendToLpgList( char lname[], char accno[], char lpg[]);
void LinkPanWithBank(BNode* pantree , BNode* banktree);
void ThirdQuestion(BNode* root );
void Fourthquestion(BNode* root);
void printInconsistentData(BNode* root);
void FifthQuestion(BNode* root, int);
void RangeSearch(BNode* , char [], char []);
BNode* MergeTwoLists();
int main()
{
   
    BNode *root = NULL;
    BNode* plist =NULL ;
    BNode *blist = NULL;
    root = InitializeList();
    plist = InitializePanList();
    blist = InitializeBankAccountList();
    
   
   
    
    LinkAadharWithPanTree(root , plist);
    
    InitializeLpg(blist);
    
   LinkPanWithBank(plist ,blist);
   
   BNode* mergedlist = MergeTwoLists();
 
  
    int choice;
    do {
        printf("\nSelect an option:\n");
        printf("1. Print Tree\n");
        printf("2. Execute First Question\n");
        printf("3. Execute Second Question\n");
        printf("4. Execute Third Question\n");
        printf("5. Execute Fourth Question\n");
        printf("6. Execute Fifth Question\n");
        printf("7. Execute Sixth Question\n");
        printf("8. Execute Seventh Question\n");
        printf("9. Execute Eighth Question\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Printing Tree:\n");
                Display(root);
                break;
            case 2:
                printf("Executing First Question:\n");
                FirstQuestion(root);
                break;
            case 3:
                printf("Executing Second Question:\n");
                SecondQuestion(root);
                break;
            case 4:
                printf("Executing Third Question:\n");
                ThirdQuestion(root);
                break;
            case 5:
                printf("Executing Fourth Question:\n");
                Fourthquestion(root);
                break;
            case 6:
                printf("Executing Fifth Question:\n");
                int x;
                printf("Enter an Amount X: ");
                scanf("%d", &x);
                FifthQuestion(root, x);
                break;
            case 7:
                printf("Executing Sixth Question:\n");
                printInconsistentData(root);
                break;
            case 8:
                printf("Executing Seventh Question:\n");
                Display(mergedlist);
                break;
            case 9:
                printf("Executing Eighth Question:\n");
                char a1[13], a2[13];
                printf("Enter Aadhar numbers A1 and A2: ");
                scanf("%s %s", a1, a2);
                while (strlen(a1) != 12 || strlen(a2) != 12) {
                    printf("Please enter valid Aadhar numbers: ");
                    scanf("%s %s", a1, a2);
                }
                RangeSearch(root, a1, a2);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 0);

    
   
   
   return 0 ;
}
int StringCompare(char s1[], char s2[], int n)
{
    printf("%s \n", s1);
    printf("%s \n", s2);

    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (s1[i] != s2[i])
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

AadharNode *CreateAdharNode(char n[], char address[], char aadharno[])
{
    AadharNode *newNode = (AadharNode *)malloc(sizeof(AadharNode));
    strcpy(newNode->a_name, n);
    strcpy(newNode->a_address, address);
    strcpy(newNode->AadharNo, aadharno);
    
    newNode->pannode = (PanNode**)malloc(sizeof(PanNode*)*(maxsize));
    newNode->numofpan = 0;
    
    return newNode;
}

PanNode *createPanNode(char name[], char address[], char panNo[], char Adharno[])
{
    PanNode *newNode = (PanNode *)malloc(sizeof(PanNode));

    strcpy(newNode->PanNo, panNo);

    strcpy(newNode->p_name, name);
    strcpy(newNode->p_address, address);
    strcpy(newNode->p_adhar, Adharno);

   newNode->bankAccount = (BankAccount**)malloc(sizeof(BankAccount*)*(maxsize));
   newNode->noofaccounts = 0;

    return newNode;
}
BNode* InitializePanList()
{

    FILE *fp;
    fp = fopen("PANList.csv", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[SIZE];
    fgets(line, SIZE, fp);
    BNode *lptr = NULL;

    PanNode *pnode;
    record *r = NULL;
    BNode *Root = NULL;

    while (fgets(line, SIZE, fp) != NULL)
    {
        // lptr = root ;
        char name[SIZE];
        char address[SIZE];
        char aadharNo[SIZE], panNo[SIZE];

        sscanf(line, "%[^,],%[^,],%[^,],%[^,]",  address, panNo ,aadharNo,name);
        pnode = createPanNode(name, address, panNo, aadharNo);
       
        record *rec = (record *)malloc(sizeof(record));
        rec->node.panNode = pnode;

        rec->tag = PAN;
        char keyval[SIZE];
        strcpy(keyval, aadharNo);
        Root = Insert(Root,panNo ,rec);

    
  

    }

    fclose(fp);
   return Root ;
}

BNode *InitializeList()
{

    FILE *fp;
    fp = fopen("AadharList2.csv", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[SIZE];

    fgets(line, SIZE, fp);

    AadharNode *aadhar = NULL;
    BNode *root = NULL;

    while (fgets(line, SIZE, fp) != NULL)
    {
        char name[SIZE], address[SIZE], aadharNo[SIZE];
        sscanf(line, "%[^,],%[^,],%[^,]", aadharNo, address,name);
        aadhar = CreateAdharNode(name, address, aadharNo);
        record *rec = (record *)malloc(sizeof(record));
        rec->node.aadharNode = aadhar;

        rec->tag = AADHAR;

        // check .. it is working uptill here
        root = Insert(root, aadharNo, rec);
    }

    fclose(fp);

    return root;
}
void Display(BNode *root)
{

   
    BNode *Root = root;
    while (Root->is_leaf == false)
    {
        Root = Root->pointers[0];
    }
    int k = 0;
    while (Root != NULL)
    {
       // printf("Parent = %s\n",Root->parent->keys[0]);
        for (int i = 0; i < Root->num_keys; i++)
        {
            printf("(%d) %s\n", ++k ,Root->keys[i] );
           
        }
        // printf("(%d)End one root..........;....................................................\n", ++k);
        Root = Root->next;
    }
}
void DisplayPanList(BNode* root)
{
    BNode* lptr = root ;
    while(lptr->is_leaf == false)
    {
        lptr = lptr->pointers[0];
    }
    int k = 0 ;
    while(lptr!=NULL)
    {
        for(int i = 0 ; i<lptr->num_keys ; i++)
        {
            printf("%d %s\n",++k,((record*)lptr->pointers[i])->node.panNode->p_adhar);
        }
        lptr = lptr->next;
    }

}

void  LinkAadharWithPanTree(BNode* root , BNode* plist)
{
    BNode* aroot = root ;
    BNode* proot = plist ;
    BNode* temp  = NULL;
    while(aroot->is_leaf == false)
    {
        aroot = aroot->pointers[0];
    }
    while(proot->is_leaf == false)
    {
        proot = proot->pointers[0];
    }
     int l = 0 ;
     int flag ;
    while(aroot!=NULL)
    {
        for(int i = 0 ; i<aroot->num_keys ; i++)
        { 
            flag =0 ;
            temp = proot ;
           
             //printf("For anode ->%s\n",aroot->keys[i]);
            while(temp!=NULL)
            {
               for(int j =0 ; j<temp->num_keys;j++)
               {
               
                if(strcmp(aroot->keys[i],((record*)temp->pointers[j])->node.panNode->p_adhar)==0)
                {
                  ((record*)aroot->pointers[i])->node.aadharNode->pannode[(((record*)aroot->pointers[i])->node.aadharNode->numofpan)++] = ((record*)temp->pointers[j])->node.panNode ;
                 // printf("(%d)panno =%s \n",++l,temp->keys[j]);
                  flag++;
                }
               }
               temp = temp->next;
            }
            if(flag==0)
            {
                printf("Not linked -> %s\n ",aroot->keys[i]);
            }
        }
        aroot = aroot->next;
    }
}

record* FindDataNode(char key[], BNode* root) {
    BNode* lptr = root;
    record* r = NULL; // InitializeLpg(BNode* root) r to NULL

    while (lptr->is_leaf == false) {
        int i = lptr->num_keys - 1;
        while (i >= 0 && strcmp(lptr->keys[i], key) > 0) {
            i--;
        }
        i++;
        lptr = lptr->pointers[i];
    }

    int i = 0;
    while ((i < lptr->num_keys) && strcmp(lptr->keys[i], key) != 0) {
        i++;
    }

     r = lptr->pointers[i];

    return r;
}

BNode *CreateBNode(record *r, bool isleaf, char key[])
{
    BNode *newNode = (BNode *)malloc(sizeof(BNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // InitializeLpg(BNode* root) pointers
    newNode->pointers = (void **)malloc(sizeof(void *) * (order + 1));
    if (newNode->pointers == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < order; i++)
    {
        newNode->pointers[i] = NULL;
    }

    // InitializeLpg(BNode* root) keys
    newNode->keys = (char **)malloc(sizeof(char *) * (order));
    if (newNode->keys == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < order; i++)
    {
        newNode->keys[i] = (char *)malloc(sizeof(char) * SIZE); // Allocate memory for each key
        if (newNode->keys[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        if (i == 0 && key != NULL)
        {
            strcpy(newNode->keys[i], key);
        }
    }
      
    newNode->parent = NULL;
    newNode->is_leaf = isleaf;
    newNode->num_keys = 0;
    newNode->next = NULL;
    newNode->prev = NULL ;

    // Set record pointer
    if (r != NULL)
    {
        newNode->pointers[0] = r;
    }

    return newNode;
}

BankAccount*  appendToBankList( char name[], char Bankname[], char AccountNumber[], int amount, char Panno[])
{
    
    BankAccount *newAccount;
    newAccount = (BankAccount *)malloc(sizeof(BankAccount));
    strcpy(newAccount->bname, name);
    strcpy(newAccount->bankName, Bankname);
    strcpy(newAccount->accountNumber, AccountNumber);
    strcpy(newAccount->PANno, Panno);
    newAccount->amountDeposited = amount;

   
    newAccount->lpgnode = NULL;
return newAccount ;
  
}
BNode* InitializeBankAccountList()
{
    FILE *fp;
    BNode* root = NULL;
    BankAccount *bankNode ;
    fp = fopen("BankAcclist.csv", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char line[SIZE];
    fgets(line, SIZE, fp);
    
     int k = 0 ;
    while (fgets(line, SIZE, fp) != NULL)
    {
        char name[SIZE];
        char Bankname[SIZE];
        char AccountNumber[SIZE], Panno[SIZE];
        int amount;
        char LpgSubsidy[SIZE];
        sscanf(line, "%[^,],%[^,],%d ,%[^,],%[^,]",  Bankname, AccountNumber, &amount, Panno,name);

       bankNode =  appendToBankList(name, Bankname, AccountNumber, amount, Panno);
        record *rec = (record *)malloc(sizeof(record));
       rec->node.bankAccount = bankNode;
       rec->tag = BANK ;
       root = Insert(root ,AccountNumber ,rec);
      
     
       

    }
    fclose(fp);
    return root ;


}

Lpg* appendToLpgList( char lname[], char accno[], char lpg[])
{
    Lpg *l_node = (Lpg *)malloc(sizeof(Lpg));
    strcpy(l_node->lname, lname);
    strcpy(l_node->laccnumber, accno);
    if(strncmp(lpg, "true",4) == 0)
    {
       
    l_node->takenLpgSubsidy = true;
    }
    else
    {
        l_node->takenLpgSubsidy = false;
    }
    return l_node; 
    
    
}

void InitializeLpg(BNode* root)
{

     FILE *fp;
    fp = fopen("Lpg.csv", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char line[SIZE];
    fgets(line, SIZE, fp);
    BNode *Root =NULL ;
    Lpg* lnode = NULL ;
     int k=0;
    while (fgets(line, SIZE, fp) != NULL)
    {
        char name[SIZE];
        char accno[SIZE];
        char lpg[SIZE];

        sscanf(line, "%[^,],%[^,],%[^,]",  accno, lpg,name );
       
       Root = root ;

      lnode =  appendToLpgList( name, accno, lpg);
    //   printf("%s %d\n",lnode->laccnumber,strlen(lnode->laccnumber));
    //   printf("Root keys bnode =  %s %d\n",Root->keys[0],strlen(Root->keys[0]));
       while(Root->is_leaf ==  false)
       {
        
         int i = Root->num_keys - 1 ;
         while(i>=0 && strcmp(Root->keys[i],accno)>0)
         {
            
            i--;
         }
        
         Root = Root->pointers[i+1];
        
       }
       
       int flag = 0 ;
        if(Root->is_leaf == true)
        {
            int i = 0 ;
            while(flag == 0 && i<Root->num_keys)
            {
             if(strcmp(Root->keys[i],accno)==0)
            {
              //  printf("(%d)lpgggg %s\n",++k,Root->keys[i]);
                flag =1 ;
            }
            else{
                i++;
            }
            }
            ((record*)Root->pointers[i])->node.bankAccount->lpgnode  = lnode ;
            
        }

    }

    fclose(fp);
  

}

void LinkPanWithBank(BNode* pantree , BNode* banktree)
{
    
    BNode* ptree = pantree ;
    BNode* btree =banktree ;
    BNode *temp = NULL;
    while(ptree->is_leaf == false)
    {
        ptree = ptree->pointers[0];
    }
    while(btree->is_leaf == false)
    {
        btree = btree->pointers[0];
    }
    int l = 0;
    int k = 0 ;
    while(ptree!=NULL)
    {
        
        for(int i = 0 ; i<ptree->num_keys ; i++)
        {
           // printf("(%d) pansss %s\n",++k ,ptree->keys[i]);
           temp = btree;

        while(temp!=NULL)
        {
            for(int j = 0 ; j<temp->num_keys ; j++)
            {
              
                if(strcmp(ptree->keys[i] , ((record*)temp->pointers[j])->node.bankAccount->PANno)==0)
                {
                    ((record*)ptree->pointers[i])->node.panNode->bankAccount[ (((record*)ptree->pointers[i])->node.panNode->noofaccounts)++] = ((record*)temp->pointers[j])->node.bankAccount ;
                  //  printf("(%d)Bankaccount == %s %s \n",++l,temp->keys[j],ptree->keys[i]);
                }
            }
            temp = temp->next;
        }
        }
        ptree = ptree->next ;
    }

}

BNode *SplitLeafNode(BNode *root, char keyval[], record *r)
{
    // printf("In splitnode %s\n ",keyval);
    BNode *siblingNode = CreateBNode(NULL, true, NULL);
    if (root->num_keys == order - 1)
    {
        // insert and then split

        int i = root->num_keys - 1;
        while (i >= 0 && strcmp(root->keys[i], keyval) > 0)
        {
            strcpy(root->keys[i + 1], root->keys[i]);

            root->pointers[i + 1] = root->pointers[i];

            i--;
        }

        strcpy(root->keys[i + 1], keyval);
        root->pointers[i + 1] = r;
        root->num_keys++;

        // now splitting
        int k = 0;
        for (int j = order / 2; j < root->num_keys; j++)
        {
            strcpy(siblingNode->keys[k], root->keys[j]);

            siblingNode->pointers[k] = root->pointers[j];
            k++;
        }
        for (int i = order / 2; i < root->num_keys; i++)
        {

            siblingNode->pointers[i] = NULL;
        }
        root->num_keys = order / 2;
        if (order % 2 == 0)
        {
            siblingNode->num_keys = order / 2;
        }
        else
        {
            siblingNode->num_keys = order / 2 + 1;
        }
        // connection
        BNode *dptr;

        dptr = root->next;
        root->next = siblingNode;
        siblingNode->next = dptr;
        siblingNode->prev = root ;
    }
    return siblingNode;
}

BNode *InsertInParent(BNode *Parent, BNode *lptr, BNode *siblingNode, char keyval[])
{

    if (Parent->num_keys < order - 1)
    {
        int i = Parent->num_keys - 1;
        while (i >= 0 && strcmp(Parent->keys[i], keyval) > 0)
        {
            strcpy(Parent->keys[i + 1] ,Parent->keys[i]);
            
            Parent->pointers[i + 2] = Parent->pointers[i + 1];
            i--;
        }
         
        strcpy(Parent->keys[i + 1], keyval);
        Parent->pointers[i + 1] = lptr;
        Parent->pointers[i + 2] = siblingNode;
        Parent->num_keys++;
        // for(int i = 0 ; i<Parent->num_keys ;i++)
        // {
        //     printf("In sert parent %s \n",Parent->keys[i]);
        // }
    }

    return Parent;
}

BNode *SplitParent(BNode *Parent, BNode *siblingNode, BNode *rootnode, char key[])
{

    BNode *ans;
    if (Parent->num_keys == order - 1)
    {
        int i = Parent->num_keys - 1;
        while (i >= 0 && strcmp(Parent->keys[i], key) > 0)
        {
            strcpy(Parent->keys[i + 1] , Parent->keys[i]);
            
            Parent->pointers[i + 2] = Parent->pointers[i + 1];
            i--;
        }

        strcpy(Parent->keys[i + 1], key);
        Parent->pointers[i + 1] = rootnode;
        Parent->pointers[i + 2] = siblingNode;
       
    }
    Parent->num_keys++;
    
    BNode *newsibling = CreateBNode(NULL, false, NULL);
    int k = 0;
    for (int i = (order/2) + 1; i < order; i++)
    {
        strcpy(newsibling->keys[k], Parent->keys[i]);

        newsibling->pointers[k] = Parent->pointers[i];
        ((BNode*)newsibling->pointers[k])->parent = newsibling;
        k++;
    }
    
    newsibling->pointers[k] = Parent->pointers[Parent->num_keys];
    
     ((BNode*)newsibling->pointers[k])->parent = newsibling;
    // now remove the keyval
    char newkeyval[SIZE];
    strcpy(newkeyval,Parent->keys[order / 2] );
    
    for (int i = order / 2 + 1; i < order; i++)
    {
        Parent->pointers[i] = NULL;
    }
    Parent->num_keys = Parent->num_keys - k - 1;
    newsibling->num_keys = k;
    // for(int i = 0 ; i<newsibling->num_keys ; i++)
    // {
    //     printf("newsibling %s\n",newsibling->keys[i]);
    // }
    BNode *grandparent = (BNode *)Parent->parent;
    if (Parent->parent == NULL)
    {
        grandparent = CreateBNode(NULL, false, NULL);
        strcpy(grandparent->keys[0], newkeyval);
        // printf("Grandparent %s..\n", grandparent->keys[0]);
        grandparent->pointers[0] = Parent;
        grandparent->pointers[1] = newsibling;
        grandparent->num_keys++;
        ans = grandparent;
        Parent->parent = grandparent;
        newsibling->parent = grandparent;
    }
    else if (grandparent->num_keys < order - 1)
    {
       //  printf("Grandparent %s ,%s..\n", grandparent->keys[0],newkeyval);
        ans = InsertInParent(grandparent, Parent, newsibling, newkeyval);
        if (grandparent->parent != NULL)
        {
            while (grandparent->parent != NULL)
            {
                grandparent = grandparent->parent;
            }
            ans = grandparent;
        }
    }
    else
    {
        ans = SplitParent(grandparent, Parent, newsibling, newkeyval);
        if (grandparent->parent != NULL)
        {
            while (grandparent->parent != NULL)
            {
                grandparent = grandparent->parent;
            }
            ans = grandparent;
        }
    }

    return ans;
}

BNode *Insert(BNode *root, char key[], record *r)
{

    // case 1 : tree is null
    if (root == NULL)
    {
        root = CreateBNode(r, true, key);
        root->num_keys++;
    }
    else
    {
        char keyval[SIZE]; // got the key val
        if (r != NULL)
        {
            if (r->tag == AADHAR)
            {

                strcpy(keyval, r->node.aadharNode->AadharNo);
            }
            if (r->tag == PAN)
            {

                strcpy(keyval, r->node.panNode->PanNo);
            }
            if(r->tag == BANK)
            {
                strcpy(keyval ,r->node.bankAccount->accountNumber);
            }
        }

        // case 2 : tree is at root , data node
        if (root->is_leaf == true)
        {

            // if node is not full
            if (root->num_keys < order - 1)
            {

                int i = root->num_keys - 1;
                while (i >= 0 && strcmp(root->keys[i], keyval) > 0)
                {

                    strcpy(root->keys[i + 1], root->keys[i]);

                    root->pointers[i + 1] = root->pointers[i];

                    i--;
                }

                strcpy(root->keys[i + 1], keyval);

                root->pointers[i + 1] = r;

                root->num_keys++;

                // its working uptill here
            }
            else
            {

                // node is full
                if (root->num_keys == order - 1)
                {

                    // insert and then split
                    BNode *siblingNode = CreateBNode(NULL, true, NULL);
                    BNode *parenT = CreateBNode(NULL, false, NULL);
                    int i = root->num_keys - 1;
                    while (i >= 0 && strcmp(root->keys[i], keyval) > 0)
                    {
                        strcpy(root->keys[i + 1], root->keys[i]);

                        root->pointers[i + 1] = root->pointers[i];

                        i--;
                    }
                    strcpy(root->keys[i + 1], keyval);

                    root->pointers[i + 1] = r;
                    root->num_keys++;

                    // now splitting
                    int k = 0;
                    for (int j = order / 2; j < root->num_keys; j++)
                    {
                        strcpy(siblingNode->keys[k], root->keys[j]);

                        siblingNode->pointers[k] = root->pointers[j];
                        k++;
                    }
                    siblingNode->num_keys = k;
                    for (int i = order / 2; i < root->num_keys; i++)
                    {
                        // root->keys[i] = NULL;
                        root->pointers[i] = NULL;
                    }
                    root->num_keys = order / 2;
                    if (order % 2 == 0)
                    {
                        siblingNode->num_keys = order / 2;
                    }
                    else
                    {
                        siblingNode->num_keys = order / 2 + 1;
                    }

                    // connection
                    BNode *dptr;

                    dptr = root->next;
                    root->next = siblingNode;
                    siblingNode->next = dptr;
                    siblingNode->prev = root ;

                    // now parent
                    strcpy(parenT->keys[0], siblingNode->keys[0]);
                    parenT->num_keys++;

                    parenT->pointers[0] = root;
                    parenT->pointers[1] = siblingNode;
                    root->parent = parenT;
                    siblingNode->parent = (BNode *)parenT;
                    root = parenT;
                    // its working uptill here
                }
            }
        }
        else
        {

            // if it is not at root and root is not full // search uptill root
            BNode *lptr = (BNode *)root;
            // printf("%s\n",lptr->keys[0]);

            while (lptr->is_leaf == false)
            {
                //  printf("internal %s\n",lptr->keys[0]);
                int i = lptr->num_keys - 1;

                while (i >= 0 && strcmp(lptr->keys[i], keyval) > 0)
                {
                    i--;
                }
                i++;
                lptr = lptr->pointers[i];
            }
            // printf("Rootnode==%s\n",lptr->keys[0]);

            // now i got the leaf node
            //  cases : leaf node is full . leaf node is not full
            if (lptr->num_keys < order - 1)
            {

                int i = lptr->num_keys - 1;
                while (i >= 0 && strcmp(lptr->keys[i], keyval) > 0)
                {
                    // strcpy(lptr->keys[i+1],'\0');
                    strcpy(lptr->keys[i + 1], lptr->keys[i]);
                    // printf("Hello i am ");
                    lptr->pointers[i + 1] = lptr->pointers[i];
                    i--;
                }

                strcpy(lptr->keys[i + 1], keyval);

                lptr->pointers[i + 1] = r;
                lptr->num_keys++;
                // this is working
            }
            else
            {

                // now is the main part
                BNode *siblingNode = SplitLeafNode(lptr, keyval, r);
                // printf( "sibling node %s \n",siblingNode->keys[0]);
                siblingNode->parent = lptr->parent;
                BNode *Parent = (BNode *)lptr->parent;
               // printf("parent == %s\n",Parent->keys[0]);
                
                // only insert
                if (Parent->num_keys < order - 1)
                {
                    int i = Parent->num_keys - 1;
                    while (i >= 0 && strcmp(Parent->keys[i], siblingNode->keys[0]) > 0)
                    {
                        strcpy(Parent->keys[i + 1], Parent->keys[i]);

                        Parent->pointers[i + 2] = Parent->pointers[i + 1];
                        i--;
                    }

                    strcpy(Parent->keys[i + 1], siblingNode->keys[0]);

                    Parent->pointers[i + 1] = (BNode *)lptr;
                    Parent->pointers[i + 2] = (BNode *)siblingNode;
                    Parent->num_keys++;
                    lptr->parent = Parent ;
                    siblingNode->parent = Parent ;
                }
                // if parent is full  , split parent
                else
                {
                    if (Parent->num_keys == order - 1)
                    {
                        
                        // for(int i = 0 ; i<Parent->num_keys ; i++)
                        // {printf("PArentsss %s\n",Parent->keys[i]);

                        // }
                        // printf("keyval is %s\n",keyval);
                        root = SplitParent(Parent, siblingNode, lptr, siblingNode->keys[0]);
                    }
                }
            }
        }
    }
    return root;
}
void FirstQuestion(BNode* root)
{
    
    BNode *Root = root;
    while (Root->is_leaf == false)
    {
        Root = Root->pointers[0];
    }
    int k = 0;
    while (Root != NULL)
    {
        for (int i = 0; i < Root->num_keys; i++)
        {
           
            if ((((record *)(Root->pointers[i]))->node.aadharNode->numofpan == 0))
            {
                printf("%s ", ((record *)(Root->pointers[i]))->node.aadharNode->a_name);
                printf("%s\n ", ((record *)(Root->pointers[i]))->node.aadharNode->a_address);
                printf("%s\n", ((record *)(Root->pointers[i]))->node.aadharNode->AadharNo);
                printf("------------------------------------------------\n");
            }
        }
        
        Root = Root->next;
    }

}
void SecondQuestion(BNode* root)
{
    
    BNode *Root = root;
    while (Root->is_leaf == false)
    {
        Root = Root->pointers[0];
    }
    int k = 0;
    while (Root != NULL)
    {
        for (int i = 0; i < Root->num_keys; i++)
        {
           
            if ((((record *)(Root->pointers[i]))->node.aadharNode->numofpan > 1))
            {
                printf("%s\n ", ((record *)(Root->pointers[i]))->node.aadharNode->a_name);
                printf("%s", ((record *)(Root->pointers[i]))->node.aadharNode->a_address);
                printf("%s\n", ((record *)(Root->pointers[i]))->node.aadharNode->AadharNo);


                for(int j = 0 ; j<((record *)(Root->pointers[i]))->node.aadharNode->numofpan ; j++)
                {
                    printf("%s\n",((record *)(Root->pointers[i]))->node.aadharNode->pannode[j]->PanNo);
                }
                printf("__________________________________\n");
            }
        }
        
        Root = Root->next;
    }

}

void ThirdQuestion(BNode *atree)
{
   // printf("HEllo");
 BNode* aroot = atree;

 while(aroot->is_leaf == false)
 {
    aroot = aroot->pointers[0];
 }
 while(aroot!=NULL)
 {
    for(int i = 0 ; i<aroot->num_keys ; i++)
    {
        int sum = 0 ;
        for(int j = 0 ; j<((record*)aroot->pointers[i])->node.aadharNode->numofpan ;j++)
        {
            sum = sum +((record*)aroot->pointers[i])->node.aadharNode->pannode[j]->noofaccounts;
        }
      //  printf("Sum is :%d\n",sum);
       if(sum>1)
       {
        printf("AadharNo :%s\n",((record*)aroot->pointers[i])->node.aadharNode->AadharNo);
        printf("Name :%s",((record*)aroot->pointers[i])->node.aadharNode->a_name);
        printf("Address :%s\n\n",((record*)aroot->pointers[i])->node.aadharNode->a_address);

       }

    }
    aroot = aroot->next;
 }




}
void Fourthquestion(BNode* root)
{
    BNode* aroot = root ;
    while(aroot->is_leaf == false)
    {
        aroot = aroot->pointers[0];
    }
    int l =0;
    Lpg *lpg  = NULL;
    while(aroot!=NULL)
    {
        for(int i = 0 ; i<aroot->num_keys ; i++)
        {
            if(((record*)aroot->pointers[i])->node.aadharNode->numofpan>0)
            {
                 for(int j = 0 ; j<((record*)aroot->pointers[i])->node.aadharNode->numofpan ; j++)
            {
                
               for(int k = 0 ; k<((record*)aroot->pointers[i])->node.aadharNode->pannode[j]->noofaccounts;k++)
               {
                
                lpg = ((record*)aroot->pointers[i])->node.aadharNode->pannode[j]->bankAccount[k]->lpgnode ;
                 
                 if((lpg->takenLpgSubsidy)==1)
                 {
                   // printf("yessssssssss\n");
                    printf("Name: %s\n",((record*)aroot->pointers[i])->node.aadharNode->pannode[j]->bankAccount[k]->bname);
                    printf("AadharNo: %s\n",((record*)aroot->pointers[i])->node.aadharNode->pannode[j]->p_adhar);
                    printf("PanNo : %s\n",((record*)aroot->pointers[i])->node.aadharNode->pannode[j]->bankAccount[k]->PANno);
                    printf("BankName : %s\n",((record*)aroot->pointers[i])->node.aadharNode->pannode[j]->bankAccount[k]->bankName);
                    printf("AccountNumber: %s\n",((record*)aroot->pointers[i])->node.aadharNode->pannode[j]->bankAccount[k]->accountNumber);
                    printf("Amount deposited: %d\n",((record*)aroot->pointers[i])->node.aadharNode->pannode[j]->bankAccount[k]->amountDeposited);
                    printf("_________________________________________________________________________\n");


                 }
               }
            }

            }
           
        }
        aroot = aroot->next;
    }
}

void FifthQuestion(BNode* root , int num )
{
      BNode* aroot = root ;
    while(aroot->is_leaf == false)
    {
        aroot = aroot->pointers[0];
    }
    int l =0;
    Lpg *lpg  = NULL;
    while(aroot!=NULL)
    {
        for(int i = 0 ; i<aroot->num_keys ; i++)
        {
            if(((record*)aroot->pointers[i])->node.aadharNode->numofpan>0)
            {
                int sum =0;
                 for(int j = 0 ; j<((record*)aroot->pointers[i])->node.aadharNode->numofpan ; j++)
            {
                
               for(int k = 0 ; k<((record*)aroot->pointers[i])->node.aadharNode->pannode[j]->noofaccounts;k++)
               {
                
                lpg = ((record*)aroot->pointers[i])->node.aadharNode->pannode[j]->bankAccount[k]->lpgnode ;
                 
                 if((lpg->takenLpgSubsidy)==1)
                 {
                   sum = sum + ((record*)aroot->pointers[i])->node.aadharNode->pannode[j]->bankAccount[k]->amountDeposited ;


                 }
               }
            }
            if(sum>num )
            {
                 printf("AadharNo: %s\n",((record*)aroot->pointers[i])->node.aadharNode->AadharNo);
                  printf("Name: %s\n",((record*)aroot->pointers[i])->node.aadharNode->a_name);
                   printf("Address: %s\n",((record*)aroot->pointers[i])->node.aadharNode->a_address);

            }

            }
           
        }
        aroot = aroot->next;
    }
}
 
void printInconsistentData(BNode *root) {
    BNode *current_node = root;
    while (current_node->is_leaf == false) {
        current_node = current_node->pointers[0];
    }

    while (current_node != NULL) {
        for (int i = 0; i < current_node->num_keys; i++) {
            AadharNode *current_aadhar_node = ((record *) current_node->pointers[i])->node.aadharNode;
            for (int j = 0; j < current_aadhar_node->numofpan; j++) {
                PanNode *current_pan_node = current_aadhar_node->pannode[j];
                for (int k = 0; k < current_pan_node->noofaccounts; k++) {
                    BankAccount *current_bank_account = current_pan_node->bankAccount[k];
                    if (strcmp(current_aadhar_node->a_name, current_bank_account->bname) != 0 ||
                        strcmp(current_aadhar_node->a_name, current_pan_node->p_name) != 0 ||
                        strcmp(current_bank_account->bname,current_pan_node->p_name ) != 0 
                       ) {
                        // Inconsistent data found, print it
                        printf("Inconsistent Data:\n");
                        printf("AadharNo: %s\n", current_aadhar_node->AadharNo);
                        printf("Address: %s\n", current_aadhar_node->a_address);
                        printf("PAN: %s\n", current_bank_account->PANno);
                        printf("Bank Name: %s\n", current_bank_account->bankName);
                        printf("Name: %s\n", current_aadhar_node->a_name);
                        printf("LPG Name: %s\n", current_bank_account->lpgnode->lname);
                       printf(" Name in Bank: %s\n", current_bank_account->bname);
                        printf("----------------------------------------\n");
                    }
                }
            }
        }
        current_node = current_node->next;
    }
}
void RangeSearch(BNode* root, char a1[], char a2[]) {
    char key[SIZE];
    char stop[SIZE];
    
   
    if (strcmp(a1, a2) > 0) {
        strcpy(key, a2);
        strcpy(stop, a1);
    } else {
        strcpy(key, a1);
        strcpy(stop, a2);
    }

   
    BNode* aroot = root;
    while (!aroot->is_leaf) {
        int i = aroot->num_keys - 1;
        while (i >= 0 && strcmp(aroot->keys[i], key) > 0) {
            i--;
        }
        aroot = aroot->pointers[i + 1];
    }

   int l = 0 ;
    while (aroot != NULL) {
        for (int i = 0; i < aroot->num_keys; i++) {
            if (strcmp(aroot->keys[i], stop) > 0) {
              
                return;
            }
            if (strcmp(aroot->keys[i], key) >= 0) {
             
                printf("(%d) Aadhar No : %s\n",++l, aroot->keys[i]);
                printf("Name :%s\n",((record*)aroot->pointers[i])->node.aadharNode->a_name);
                printf("Name :%s\n",((record*)aroot->pointers[i])->node.aadharNode->a_address);
                printf("________________________________________________________________\n");
            }
        }
        aroot = aroot->next; 
    }
}
BNode* MergeTwoLists()
{
     FILE *fp1;
    BNode* root = NULL;
    BankAccount *bankNode ;
    fp1 = fopen("BankAcclist1.csv", "r");
    if (fp1 == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char line[SIZE];
    fgets(line, SIZE, fp1);
    
     int k = 0 ;
    while (fgets(line, SIZE, fp1) != NULL)
    {
        char name[SIZE];
        char Bankname[SIZE];
        char AccountNumber[SIZE], Panno[SIZE];
        int amount;
        char LpgSubsidy[SIZE];
        sscanf(line, "%[^,],%[^,],%[^,],%d ,%[^,]", name , Bankname, AccountNumber, &amount, Panno);

       bankNode =  appendToBankList(name, Bankname, AccountNumber, amount, Panno);
        record *rec = (record *)malloc(sizeof(record));
       rec->node.bankAccount = bankNode;
       rec->tag = BANK ;
       root = Insert(root ,AccountNumber ,rec);
      
    }
    fclose(fp1);
       FILE *fp2;
    
    
    fp2 = fopen("BankAcclist1.csv", "r");
    if (fp2 == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    
    fgets(line, SIZE, fp2);
   
    while (fgets(line, SIZE, fp2) != NULL)
    {
        char name[SIZE];
        char Bankname[SIZE];
        char AccountNumber[SIZE], Panno[SIZE];
        int amount;
        char LpgSubsidy[SIZE];
        sscanf(line, "%[^,],%[^,],%[^,],%d ,%[^,]", name , Bankname, AccountNumber, &amount, Panno);

       bankNode =  appendToBankList(name, Bankname, AccountNumber, amount, Panno);
        record *rec = (record *)malloc(sizeof(record));
       rec->node.bankAccount = bankNode;
       rec->tag = BANK ;
       root = Insert(root ,AccountNumber ,rec);
      
     
       

    }
    fclose(fp2);


    return root ;

}
Queue *createQueue() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue *queue, BNode *bnode) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->bnode = bnode;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}
BNode *dequeue(Queue *queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    QueueNode *temp = queue->front;
    BNode *bnode = temp->bnode;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return bnode;
}

void levelOrderTraversal(BNode *root) {
    if (root == NULL) {
        return;
    }
    Queue *queue = createQueue();
    enqueue(queue, root);

    while (queue->front != NULL) {
        BNode *current = dequeue(queue);
        for (int i = 0; i < current->num_keys; i++) {
            printf("%s ", current->keys[i]);
        }
        printf("\n");

        if (!current->is_leaf) {
            for (int i = 0; i <= current->num_keys; i++) {
                if (current->pointers[i] != NULL) {
                    enqueue(queue, (BNode *)current->pointers[i]);
                }
            }
        }
    }
    free(queue);
}
void PrintTree(BNode* root)
{
    BNode* lptr = root ;
    
    for(int i = 0 ; i<lptr->num_keys ; i++)
    {
        printf("%s ",lptr->keys[i]);
    }
    printf("..........\n");
    int flag = 0 ;
    int i = 0;
    while(flag = 0)
    {
    if(lptr->is_leaf != false)
    {
       PrintTree(lptr->pointers[i++]);
    }
    else
    {
        flag =1 ;
    }
    }
    


}
