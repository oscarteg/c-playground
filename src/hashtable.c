#include <stdio.h>
#define CAPACITY 1000

unsigned long hash_function(char *str) {
  unsigned long i = 0;

  for (int j = 0; str[j] != '\0'; j++) {
    i += str[j];
  }

  return i % CAPACITY;
}

typedef struct HT_Item {
  char *key;
  char *value;
} HT_Item;

typedef struct HashTable {
  HT_Item **items;
  int size;
  int count;
} HashTable;

// HT_Item *create_item(char *key, char *value) {}

int main() { printf("hi"); }
