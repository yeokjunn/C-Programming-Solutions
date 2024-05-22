#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int HashInsert(int key, HashSlot hashTable[])
{
    int hashIndex = hash(key); // Calculating hashIndex, insertIndex
    int insertIndex = hashIndex;
    int collisions, i = 0;

    while (hashTable[insertIndex].indicator == USED)
    { 
        insertIndex = (insertIndex+1) % TABLESIZE; // Wrap around end of hashTable
        collisions++;
        for (i = 0; i < TABLESIZE; i++)
        {
            if (hashTable[i].key == key)
            {
                return -1; // Check for duplicates
            }
        }
        if (insertIndex == hashIndex)
        {
            return TABLESIZE + 1; // Table is full
        }
    }
    while (hashTable[hashIndex].next != -1)
    {
        hashIndex = hashTable[hashIndex].next;
    }
    hashTable[hashIndex].next = insertIndex;
    // Inserting new index into HashTable
    hashTable[insertIndex].key = key;
    hashTable[insertIndex].next = -1;
    hashTable[insertIndex].indicator = USED;

    return insertIndex;
}

int HashFind(int key, HashSlot hashTable[])
{
    int hashIndex = hash(key);
    int collisions = 0;
    
    while (hashTable[hashIndex].key != key)
    {
        hashIndex = hashTable[hashIndex].next;
        collisions++;
        if (hashIndex == -1)
        {
            return -1; // Key not found
        }
    }
    return hashIndex;
    
}

/* Sample Input:
1 1 1 2 1 5 1 41 1 42 3 1 4 2 4 2 10 1 10 3 1 11 1 37 1 30 1
45 1 17 1 9 1 13 2 14 2 13 1 38 1 39 1 40 1 77 1 79 1 56 1 58
245
1

59 2 5 3 4
*/