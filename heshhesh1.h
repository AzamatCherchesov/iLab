#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#define NAME_LENGTH 30   // max lenght of name
#define NUMBER_LENGTH 15 // max lenght of number
#define TABLE_SIZE 257    // max lenght of table of pointers

/* struct which contant name and telefon number. Also there is a pointer on the nex elem in the hesh table*/
struct T_list
{
  char name[ NAME_LENGTH ];
  char number[ NUMBER_LENGTH ];
  struct T_list * next;
};

struct T_list * htInsert(struct T_list ** ht, char name[NAME_LENGTH], char number[NUMBER_LENGTH]); // function of making new element in heshtable
struct T_list * htFind(struct T_list ** ht, char name[NAME_LENGTH]);                               // function of finding 
struct T_list ** htCreate();                                                                       // create first find elem
struct T_list ** htDestruct(struct T_list *** ht);                                                 // function of delete the heshtable
int htDelete(struct T_list ** ht, char name[NAME_LENGTH]);                                         // function of delete the elem
unsigned int hash(char name[NAME_LENGTH]);                                                         // function which make a hash for every elem


/* function insert the elem*/
struct T_list * htInsert(struct T_list ** ht, char name[NAME_LENGTH], char number[NUMBER_LENGTH])
{
   assert( ht );
   unsigned int key = hash(name);
   struct T_list ** cur = &(ht[key]);
   while (*cur != NULL)
   {
     if (strcmp(name, (*cur)->name) == 0)
     {
        printf("Changed. Old value = %s\n", (*cur)->number);
        memcpy((*cur)->number, number, NUMBER_LENGTH);
        return *cur;
      }
     cur = &((*cur)->next);
    }
    *cur = (struct T_list *) malloc(sizeof(struct T_list));
    if (*cur == NULL)
       return NULL;
    (*cur)->next = NULL;
    memcpy((*cur)->name, name, NAME_LENGTH);
    memcpy((*cur)->number, number, NUMBER_LENGTH);
    printf("OK\n");
    return *cur;
}



/* function find the elem in the table*/
struct T_list * htFind(struct T_list ** ht, char name[NAME_LENGTH])
{
	assert( ht );
   unsigned int key = hash(name);
   struct T_list * cur = ht[key];
   while (cur != NULL)
   {
     if (strcmp(name, cur->name) == 0)
     {
       printf("%s\n", cur->number);
       return cur;
     }
     cur = cur->next;
    }
   printf("NO\n");
   return NULL;
}\


/* Creating*/
struct T_list ** htCreate()
{
	
    struct T_list ** table = (struct T_list **) malloc(TABLE_SIZE*sizeof(struct T_list *));
	assert ( **table );
    unsigned int i;
    if (table == NULL)
    return NULL;
    for (i = 0; i < TABLE_SIZE; i++)
      table[i] = NULL;
    return table;
}


struct T_list ** htDestruct(struct T_list *** ht)
{
	assert( ht );
    struct T_list * tmp = NULL;
    int i =0;
    if (ht == NULL)
    {
       return NULL;
    }
    for (i = 0; i < TABLE_SIZE; i++)
    {
       while ((*ht)[i] != NULL)
       {
          tmp = (*ht)[i];
          (*ht)[i] = (*ht)[i]->next;
          free(tmp);
       }
     }
    free(*ht);
    *ht = NULL;
    return NULL;
}


/* Function delete one of the elems */
int htDelete(struct T_list ** ht, char name[NAME_LENGTH])
{
	assert( ht );
    unsigned int key = hash(name);
    struct T_list * cur = ht[key];
    struct T_list ** prev = &ht[key];
    while (cur != NULL)
    {
      if (!(strcmp(name, cur->name) == 0))
      {
         prev = &(cur->next);
         cur = cur->next;
       }
      else
      {
         break;
       }
     }
    if (cur == NULL)
    {
      return NULL;
    }
    *prev = cur->next;
    free(cur);
    return 1;
}

/* Function Hash */
unsigned int hash(char name[NAME_LENGTH])
{
    unsigned int i = 0;
    unsigned int result = 0;
    for (i = 0; (i < NAME_LENGTH) && (name[i] != '\0'); i++)
      result = (result + name[i]) % TABLE_SIZE;
    return result;
}