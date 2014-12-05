#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <heshhesh1.h>


int main()
{
  struct T_list ** ht = htCreate();
  char buffer[10 + NUMBER_LENGTH + NAME_LENGTH] = { 0 };
  char command[10] = { 0 };
  char name[NAME_LENGTH] = { 0 };
  char number[NUMBER_LENGTH] = { 0 };
  char c = 0;
  int i = 0;

  printf("Hash table phone book. Available commands: INSERT, FIND, EXIT.\n");
  while (1)
  {
    int i = 0;
    for (c = getchar(); isupper(c) && (i < 9); c = getchar())
      command[i++] = c;
    command[i++] = '\0';
    if (c == '\n')
    {
       if (strcmp("EXIT", command) == 0)
       {
          return 0;
       }
    else
    {
        printf("Wrong command or syntax\n");
    }
    }
   else if (c == ' ')
   {
      i = 0;
      for (c = getchar(); isalpha(c) && (i < NAME_LENGTH - 1); c = getchar())
         name[i++] = c;
      name[i++] = '\0';
      if (c == '\n')
      {
         if ((strcmp("FIND", command) == 0) && (i > 1))
         {
            htFind(ht, name);
         }
         else
         {
             printf("Wrong command or syntax\n");
          }
       }
       else
       {
              if ((c == ' ') && (i > 1))
              {
                i = 0;
                for (c = getchar(); isdigit(c) && (i < NUMBER_LENGTH - 1); c = getchar())
                   number[i++] = c;
                number[i++] = '\0';
                if (c == '\n')
                {
                     if ((strcmp("INSERT", command) == 0) && (i > 1))
                     {
                       htInsert(ht, name, number);
                      }
                else
                {
                    printf("Wrong command or syntax\n");
                 }
      }
      else
      {
          printf("Wrong command or syntax\n");
       }
  }
  else
  {
      printf("Wrong command or syntax\n");
   }
   }
   }
   else
   {
      printf("Wrong command or syntax\n");
    }
   while (c != '\n')
       c = getchar();
   }

   return -1;
}
