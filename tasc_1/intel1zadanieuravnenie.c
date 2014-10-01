#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MISTAKE 10 
//-------------------------------------- stucts

struct Solution // структура хранит информацию наличия корней ,их количества и численные результаты
{
  int number;
  float solution_1;
  float solution_2;
};#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MISTAKE 10 

// eta programma reshaet kvadratnoe uravnenie , i vivodit kolichestvo korney  , uchitivaet oshibku vvoda bukv 

//-------------------------------------- structs
struct Solution // structura hranit information o kornyah i ih kolichestvo
{
   int number;
   float solution_1;
   float solution_2;
};

int Kvadratnoe_uravnenie(); // Kvadratnoe uravnenie - function , return ukazatel na structuri, gde korni uravneniya

int main()
{ 
   if( Kvadratnoe_uravnenie() == MISTAKE ) printf ( " Pri Vvode proizoshla oshibka!"); 
   system( "PAUSE" );
   return 0;
}

int Kvadratnoe_uravnenie()
{
 
   const char *rptr;                              /*-------pointer for STRTOD-------------------*/
   char a [ 100 ] , b [ 100 ] , c [ 100 ] ;       /*-------input strigs-------------------------*/
   double rate_1 = 0 , rate_2 = 0 , rate_3 = 0;   /*-------coefficents for quadric square-------*/
   struct Solution Result;                        /*-------struct for results-------------------*/
   float diskrim = 0;                             /*-------disrriminant-------------------------*/

   //input
   printf ("Vvedite znachenie vhodnih parametrov a,b,c.\n V sluchae vvoda nevernih simvolov , programma vidast oshibku\n");
   scanf ("%s%s%s",a,b,c);
   //input
   rate_1 = strtod ( a , &rptr );
   if ( *rptr != NULL ) return MISTAKE; 
       rate_2 = strtod ( b , &rptr );
   if ( *rptr != NULL) return MISTAKE; 
       rate_3 = strtod ( c , &rptr );
   if ( *rptr != NULL) return MISTAKE; 
  
   diskrim = rate_2 * rate_2 - 4*rate_1 * rate_3;

   
   
/*------------------------solution------------------*/
   if (rate_1 == 0) 
   {
       if (rate_2 == 0)
       {
           if (rate_3 == 0) 
               Result.number = 3;
           else 
               Result.number = 0;
      }
        else 
        {
            Result.number = 1;
            Result.solution_1 = (-rate_3/rate_2);
         }
    }
    else 
    { 
        if (diskrim < 0) 
            Result.number = 0;
        else
        {
            Result.number = 2;
            Result.solution_1 = (-rate_2 - sqrt(diskrim)) / (2 * rate_1);
            Result.solution_2 = (-rate_2 + sqrt(diskrim)) / (2 * rate_1);
        }
     }
/*------------------------solution------------------*/



/*------------------------printing------------------*/
     if (Result.number == 0) 
     printf("Korney net");

     if (Result.number == 3) 
     printf("Korney beskonechno mnogo");

     if (Result.number == 1) 
     printf("the number of solutions is 1 \n solution = %f", Result.solution_1);

     if (Result.number == 2) 
     printf("the number of solutions is 2 \n first solution = %f \n second solution = %f", Result.solution_1, Result.solution_2);

/*------------------------printing------------------*/     
     
//     printf("\n diskrimimnant =  %f \n ", diskrim);
     
     return 0;
}

//------------------------------------ prototypes

int Kvadratnoe_uravnenie();    //   квадратное уравнение- функция ,возвращающая указатель на стэк, где хранится решение квадратного уравнения

//-------------------------------------  main

int main()
{	
	if( Kvadratnoe_uravnenie() == MISTAKE ) printf ( " Pri Vvode proizoshla oshibka!"); 
	printf("\n");
	system("PAUSE");
	return 0;
}

//----------------------------------- fnctions

int Kvadratnoe_uravnenie()
{/*
	char *rptr;
	char a [ 100 ] , b [ 100 ] , c [ 100 ] ;
	double rate_1 = 0 , rate_2 = 0 , rate_3 = 0; 
	struct Solution Result;
	float diskrim = rate_2*rate_2 - 4*rate_1*rate_3;


	printf ("Vvedite znachenie vhodnih parametrov a,b,c.\n V sluchae vvoda nevernih simvolov , programma vidast oshibku\n");
	scanf ("%s%s%s",a,b,c);
	//место для проверки на числа


	 rate_1 = strtod ( a , &rptr );
	 if( *rptr != NULL ) return MISTAKE; 
	 rate_2 = strtod ( b , &rptr );
	 if( *rptr != NULL) return MISTAKE; 
	 rate_3 = strtod ( c , &rptr );
	 if( *rptr != NULL) return MISTAKE; 


	//------------------solution
	if (rate_1 == 0) 
	   {
		if (rate_2 == 0)
           {
			if (rate_3 == 0) 
		        Result.number = 3;
			else    
				Result.number = 0;
			}
		else      
		    {
			 Result.number = 1;
			 Result.solution_1 = (-rate_3/rate_2);
		     }
		}
	 else	
	    { 
	     if (diskrim < 0)    
			 Result.number = 0;
		 else
		    {
			  Result.number = 2;
		      Result.solution_1     = (-rate_2 - sqrt(diskrim)) / (2 * rate_1);
			  Result.solution_2     = (-rate_2 + sqrt(diskrim)) / (2 * rate_1);
			}
	      }
	//-------------------solution

	//------------------printing
	if (Result.number == 0) 
       printf("Korney net");

	if (Result.number == 3) 
       printf("Korney beskonechno mnogo");
	
	if (Result.number == 1) 
       printf("the number of solutions is 1 \n solution = %f", Result.solution_1);
	
	if (Result.number == 2) 
       printf("the number of solutions is 2 \n first solution = %f \n second solution = %f", Result.solution_1, Result.solution_2);
	*/
	return 0;
}





