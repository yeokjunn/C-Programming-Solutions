#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR 3

typedef struct _listnode{
    int key;
    struct _listnode *next;
    struct _listnode *pre;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} HashTableNode;

typedef struct _hashTable{
   int hSize;
   int nSize;
   HashTableNode *Table;
} HashTable;

int Hash(int key,int hSize);

ListNode* HashSearch(HashTable, int);
int HashInsert(HashTable *, int);
int HashDelete(HashTable *, int);

//In Practice, we will not do it
void HashPrint(HashTable);

int main()
{
    int opt;
    int size;

    int i;
    int key;

    //Create a HashTable
    HashTable Q1;

    printf("============= Hash Table ============\n");
    printf("|1. Create a hash table             |\n");
    printf("|2. Insert a key to the hash table  |\n");
    printf("|3. Search a key in the hash table  |\n");
    printf("|4. Delete a key from the hash table|\n");
    printf("|5. Print the hash table            |\n");
    printf("|6. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=5){
        switch(opt){
        case 1:
            printf("Enter number of data to be inserted:\n");
            scanf("%d",&size);

            Q1.hSize = (int)size/ LOAD_FACTOR;
            Q1.nSize = 0;

            Q1.Table = (HashTableNode *) malloc(sizeof(HashTableNode)*(Q1.hSize));

            for(i=0;i<Q1.hSize;i++){
                Q1.Table[i].head = NULL;
                Q1.Table[i].size = 0;
            }
            printf("HashTable is created.\n");
            break;
        case 2: //Insertion
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            if(HashInsert(&Q1,key))
                printf("%d is inserted.\n",key);
            else
                printf("%d is a duplicate. No key is inserted.\n",key);
            break;
        case 3: //Search
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            ListNode* node = HashSearch(Q1, key);

            if(node!=NULL)
                printf("%d is found.\n",key);
            else
                printf("%d is not found.\n",key);
            break;
        case 4: //Deletion
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            if(HashDelete(&Q1,key))
                printf("%d is deleted.\n",key);
            else
                printf("%d is not existing.\n",key);
            break;
        case 5:
            HashPrint(Q1);
            break;
        }

    printf("Enter selection: ");
    scanf("%d",&opt);
    }

    for(i=0;i<Q1.hSize;i++)
    {
        while(Q1.Table[i].head)
        {
            ListNode *temp;
            temp = Q1.Table[i].head;
            Q1.Table[i].head = Q1.Table[i].head->next;
            free(temp);
        }
    }
    free(Q1.Table);

    return 0;
}



int HashInsert(HashTable* Q1Ptr, int key)
{
    // Calculating hashIndex
    int hashIndex = Hash(key, Q1Ptr->hSize);

    // Check for duplicates in HashTable
    ListNode* checkDuplicate = HashSearch(*Q1Ptr, key);
    if (checkDuplicate != NULL) {
        return 0; // Insertion unsuccessful
    }
    
    // Create, initialise newNode to insert into HashTable array
    ListNode* newNode = (ListNode* )malloc(sizeof(ListNode));
    newNode->key = key;
    newNode->next, newNode->pre = NULL;

    // Inserting node into linked list of HashSlot
    newNode->next = Q1Ptr->Table[hashIndex].head;
    if (Q1Ptr->Table[hashIndex].head != NULL)
    {
        Q1Ptr->Table[hashIndex].head->pre = newNode;
    }
    Q1Ptr->Table[hashIndex].head = newNode;

    // Updating size of list
    Q1Ptr->Table[hashIndex].size++; // Updating size of HashSlot
    Q1Ptr->nSize++; // Updating total size of HashTable
    // hSize already updated in main function
}

int HashDelete(HashTable* Q1Ptr, int key)
{
    // Calculating hashIndex
    int hashIndex = Hash(key, Q1Ptr->hSize);
    // Check if node to be deleted exists
    ListNode* deleteNode = HashSearch(*Q1Ptr, key);
    if (deleteNode == NULL)
    {
        return 0; // Node does not exist, deletion failed
    }
    //Deletion of node from doubly linked list
    if (deleteNode->pre == NULL) // 1st node in list
    {
        Q1Ptr->Table[hashIndex].head = deleteNode->next;
    }
    else
    {
        deleteNode->pre->next = deleteNode->next;
    }
    if (deleteNode->next != NULL)
    {
        deleteNode->next->pre = deleteNode->pre;
    }
    free(deleteNode);

    // Updating size
    Q1Ptr->Table[hashIndex].size--;
    Q1Ptr->nSize--;
    // hSize already updated in main function
    return 1;
}

// hSize = size of HashTable (no. of linked lists)
// nSize = total no. of nodes in all linked lists in HashTable

/* For HashInsert:

1. Get hashIndex
2. Check if there is duplicate key, by using HashSearch
3. Create, initialise new node to insert into HashTable array
4. Code out function to insert node into linked list
Note: Remember that first node to be inserted is not inserted
      directly into the HashSlot; it is inserted into the
      pointer of the HashSlot.
5. Update size of list, return 1 for successful insertion

*//////////////////////////////////////////////////////////////////////////////////////////////

/* For HashDelete:

1. Get hashIndex
2. Check that node to be deleted exists
3. Code out deletion of node from doubly linked list
4. Decrement size of linked list and total no. of nodes
*/


int Hash(int key,int hSize)
{
    return key%hSize;
}

ListNode* HashSearch(HashTable Q1, int key)
{
    int index;

    ListNode *temp;

    if(Q1.hSize != 0)
      index = Hash(key,Q1.hSize);
    else
      return NULL;

    temp = Q1.Table[index].head;
    while(temp !=NULL){
        if(temp->key == key)
            return temp;
        temp = temp->next;
    }

    return NULL;
}

void HashPrint(HashTable Q1)
{
    int i;
    ListNode *temp;
    for(i=0;i<Q1.hSize;i++)
    {
        temp =Q1.Table[i].head;
        printf("%d:  ",i);
        while(temp !=NULL)
        {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}