/*  
 *  Open Addressing Hashtable
 *
 *  Rudimentary open addressing hashtable implementation with
 *  an extremely dubious hash function and elementary error handling and
 *  optimization.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person {
    char name[MAX_NAME];
    int age;
    struct person* next;
} person;

person* hash_table[TABLE_SIZE];

unsigned int hash(char* name) {
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

void print_table() {
    printf("START\n"); 
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            person* current = hash_table[i];
            printf("\t%i\t", i);
            while (current != NULL) {
                printf("[ %s ]", current->name);
                current = current->next;
            }
            printf("\n");
        }
    }
    printf("END\n");
}

bool hash_table_insert(person* p) {
    if (p == NULL) return false;
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

person* hash_table_lookup(char* name) {
    int index = hash(name);
    person* current = hash_table[index];
    while (current != NULL && strncmp(current->name, name, TABLE_SIZE) != 0) {
        current = current->next;
    }
    return current;
}

person* hash_table_delete(char* name) {
    int index = hash(name);
    person* current = hash_table[index];
    person* prev = NULL;
    while (current != NULL && strncmp(current->name, name, TABLE_SIZE) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) return NULL;
    if (prev == NULL) {
        hash_table[index] = current->next;
    } else {
        prev->next = current->next;
    }
    return current;
}


int main() {
    printf("Jacob => %u\n", hash("Jacob"));
    printf("Natalie => %u\n", hash("Natalie"));
    printf("Sara => %u\n", hash("Sara"));
    printf("Mpho => %u\n", hash("Mpho"));
    printf("Tebogo => %u\n", hash("Tebogo"));
    printf("Ron => %u\n", hash("Ron"));
    printf("Jane => %u\n", hash("Jane"));
    printf("Maren => %u\n", hash("Maren"));
    printf("Bill => %u\n", hash("Bill"));

    init_hash_table();
    print_table();

    person jacob = { .name="Jacob", .age=256 };
    person kate = { .name="Kate", .age=27 };
    person mpho = { .name="Mpho", .age=14 };
    person sarah = { .name="Sarah", .age=54 };
    person edna = { .name="Edna", .age=15 };
    person maren = { .name="Maren", .age=25 };
    person eliza = { .name="Eliza", .age=34 };
    person robert = { .name="Robert", .age=1 };
    person jane = { .name="Jane", .age=75 };

    hash_table_insert(&jacob);
    hash_table_insert(&kate);
    hash_table_insert(&mpho);
    hash_table_insert(&sarah);
    hash_table_insert(&edna);
    hash_table_insert(&maren);
    hash_table_insert(&eliza);
    hash_table_insert(&robert);
    hash_table_insert(&jane);
    print_table();

    person *tmp = hash_table_lookup("Mpho");
    if (tmp == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s.\n", tmp->name);
    }

    person *tmp2 = hash_table_lookup("George");
    if (tmp2 == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s.\n", tmp2->name);
    }

    hash_table_delete("Mpho");
    person *tmp3 = hash_table_lookup("Mpho");
    if (tmp3 == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s.\n", tmp3->name);
    }

    print_table();

    return 0;
}
