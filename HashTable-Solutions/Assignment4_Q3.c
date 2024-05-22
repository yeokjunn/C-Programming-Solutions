#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int mutiplier;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(mutiplier=0;mutiplier<TABLESIZE;mutiplier++){
        hashTable[mutiplier].indicator = EMPTY;
        hashTable[mutiplier].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
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
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(mutiplier=0;mutiplier<TABLESIZE;mutiplier++) printf("%d: %d %c\n",mutiplier, hashTable[mutiplier].key,hashTable[mutiplier].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

int HashInsert(int key, HashSlot hashTable[])
{
    int mutiplier = 1;
    int hashIndex = hash1(key);
    int comparison, toInsert, comparisonCount = 0;

    if (key < 0) //  ERROR handling for negative number 
    {
        return 0;
    }

    while(hashTable[hashIndex].indicator == USED && hashTable[hashIndex].key != key) // Looking for EMPTY/ DELETED, IF USED increment
    {
        hashIndex = (hash1(key) + mutiplier * hash2(key)) % TABLESIZE;
        comparisonCount++;
        comparison++;
        mutiplier++;

        if(comparison >= TABLESIZE)
        {
            return comparisonCount; // Table is full
        }
    }

    toInsert = hashIndex; // 1st EMPTY/ DELETED slot to insert key

    while (hashTable[hashIndex].indicator != EMPTY && comparison < TABLESIZE)
    {
        if (hashTable[hashIndex].indicator == USED)
        {
            if (hashTable[hashIndex].key == key)
            {
                return -1; // Duplicate Check
            }
            comparisonCount++;
        }
        hashIndex = (hash1(key) + mutiplier * hash2(key)) % TABLESIZE;
        mutiplier++;
        comparison++;
    }

    hashTable[toInsert].key = key;
    hashTable[toInsert].indicator = USED;
    return comparisonCount;
}

int HashDelete(int key, HashSlot hashTable[])
{
    int mutiplier = 0;
    int hashIndex = hash1(key);
    int comparison = 0;
    int deletedIndex = -1;

    // Keep probing until an empty slot or the key is found, empty slot = no such key
    while (hashTable[hashIndex].indicator != EMPTY)
    {
        // Incremental double hashing
        hashIndex = (hash1(key) + mutiplier * hash2(key)) % TABLESIZE;
        comparison++;
        mutiplier++;

        // Check if the key is found
        if (hashTable[hashIndex].indicator == USED && hashTable[hashIndex].key == key)
        {
            // Mark the key as deleted
            hashTable[hashIndex].indicator = DELETED;
            deletedIndex = hashIndex;
            break;
        }

        // Check if the key doesn't exist
        if (comparison > TABLESIZE)
            return -1;
    }

    // If the key was deleted, return the number of comparisons
    if (deletedIndex != -1)
        return comparison;
    else
        return -1; // Key does not exist
}

// 1 5 1 41 1 42 3 1 9 1 72 1 73 1 42 1 79 2 42 3 2 42 1 43 1 37 1 36 1 27 1 //
// 22 1 15 1 77 1 66 1 22 1 45 1 79 1 23 1 5 1 38 1 39 1 40 //