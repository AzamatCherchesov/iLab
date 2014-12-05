// Here is a programm ASM . You need to have a code , the programm will make new 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
struct Element  // struckt have name and the number of string ,where it was
{
	char name[10];
	int  adress;
}
struct Element * matrix [ 20 ];
int ASSSM(); // making new code
int Ffind(); // is looking the element with the only info "name" 
int Ffind( char stroka[ ])
{
	int i = 0;
	while ( strcmp(stroka,matrix[i]->name) )
	{
		i++;
	}
	return matrix[i]->adress;
}

int ASSSM()
{
  char a[10] = { "0" };     //here I am reading the new comand
  char aa[10] = { "0" };    // this is just a massive for the Ffind function
  int count = 0; // this 
  int b = 0;     // this is just a count
  FILE *f;
  FILE *g;
  
  f = fopen("input.txt","r");
  g = fopen("output.txt","w");

  fscanf(f, "%s" ,a);
  while ( strcmp(a,"END") )
  {
     if( !strcmp(a,"PUSH") ) 
     {
        fscanf(f,"%d",&count);
        fprintf(g,"1 %d",count);
		fprintf(g,"\n");
         fscanf(f, "%s" ,a);
		 b++;
		 b++;
	 continue ;
     }
     if( !strcmp(a,"ADD") ) 
     {
		fprintf(g,"2");
		fprintf(g,"\n");
        fscanf(f, "%s" ,a);
		b++;
	 continue ;
     }
	 if( !strcmp(a,"MUL") ) 
     { 
		fprintf(g,"3");
		fprintf(g,"\n");
        fscanf(f, "%s" ,a);
		b++;
	 continue ;
     }
	 if( !strcmp(a,"SUB") ) 
     {
		fprintf(g,"4");
		fprintf(g,"\n");
        fscanf(f, "%s" ,a);
		b++;
	 continue ;
     }
	 if( !strcmp(a,"DIV") ) 
     {
		fprintf(g,"5");
		fprintf(g,"\n");
        fscanf(f, "%s" ,a);
		b++;
	 continue ;
     }
	 if( !strcmp(a,"JMP") ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"7 %s",aa);
		fprintf(g,"\n");
        fscanf(f, "%s" ,a);
		b++;
		b++;
	 continue ;
     }
	 if( !strcmp(a,"JA") ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"8 %s",aa);
		fprintf(g,"\n");
         fscanf(f, "%s" ,a);
		 b++;
		 b++;
	 continue ;
     }
	 if( !strcmp(a,"JAE") ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"9 %s",aa);
		fprintf(g,"\n");
         fscanf(f, "%s" ,a);
		 b++;
		 b++;
	 continue ;
     }
	 if( !strcmp(a,"JB") ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"10 %s",aa);
		fprintf(g,"\n");
         fscanf(f, "%s" ,a);
		 b++;
		 b++;
	 continue ;
     }
	 if( !strcmp(a,"JBE") ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"11 %s",aa);
		fprintf(g,"\n");
         fscanf(f, "%s" ,a);
		 b++;
		 b++;
	 continue ;
     }
	 if( !strcmp(a,"JE") ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"12 %s",aa);
		fprintf(g,"\n");
         fscanf(f, "%s" ,a);
		 b++;
		 b++;
	 continue ;
     }
	 if( !strcmp(a,"JNE") ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"13 %s",aa);
		fprintf(g,"\n");
         fscanf(f, "%s" ,a);
		 b++;
		 b++;
	 continue ;
     }
	
	 if( !strcmp(a,"PUSHA") ) 
     {
		fprintf(g,"15\n");
         fscanf(f, "%s" ,a);
		 b++;
	 continue ;
     }
	 if( !strcmp(a,"PUSHB") ) 
     {
		fprintf(g,"16\n");
         fscanf(f, "%s" ,a);
		 b++;
	 continue ;
     }
	 if( !strcmp(a,"PUSHC") ) 
     {
		fprintf(g,"17\n");
         fscanf(f, "%s" ,a);
		 b++;
	 continue ;
     }
	 if( !strcmp(a,"POPA") ) 
     {
		fprintf(g,"18\n");
         fscanf(f, "%s" ,a);
		 b++;
	 continue ;
     }
	 if( !strcmp(a,"POPB") ) 
     {
		fprintf(g,"19\n");
         fscanf(f, "%s" ,a);
		 b++;
	 continue ;
     }
	 if( !strcmp(a,"POPC") ) 
     {
		fprintf(g,"20\n");
         fscanf(f, "%s" ,a);
		 b++;
	 continue ;
     }
	 strcpy(matrix[ i ] -> name , a);
     (matrix[ i ] -> adress) = (b + 1);
	 fscanf(f, "%s" ,a);
  }
 
  fprintf(g,"6");
  fclose(f);
  fclose(g);



  // now we have a massive with only digit and names near the jump


  g = fopen("output2.txt","w");
  f = fopen("output.txt","r");
  fscanf(f, "%d" ,&count);
  while ( a != 6 )
  {
	 if( a == 7 ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"7 %d",Ffind(aa););
		fprintf(g,"\n");
        fscanf(f, "%s" ,a);
	 continue ;
     }
	 if( a == 8 ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"8 %d",Ffind(aa););
		fprintf(g,"\n");
        fscanf(f, "%s" ,a);
	 continue ;
     }
	 if( a == 9 ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"9 %d",Ffind(aa););
		fprintf(g,"\n");
        fscanf(f, "%s" ,a);
	 continue ;
     }
	 if( a == 10 ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"10 %d",Ffind(aa););
		fprintf(g,"\n");
        fscanf(f, "%s" ,a);
	 continue ;
     }
	 if( a == 11 ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"11 %d",Ffind(aa););
		fprintf(g,"\n");
        fscanf(f, "%s" ,a);
	 continue ;
     }
	 if( a == 12 ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"12 %d",Ffind(aa););
		fprintf(g,"\n");
        fscanf(f, "%s" ,a);
	 continue ;
     }
	 if( a == 13 ) 
     {
        fscanf(f,"%s",aa);
        fprintf(g,"13 %d",Ffind(aa););
		fprintf(g,"\n");
        fscanf(f, "%s" ,a);
	 continue ;
     }
	 
   }
  
   fprintf(g,"6");
   fclose(f);
   fclose(g);
  
  
  
  return 0;
};





