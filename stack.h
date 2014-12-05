#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TData double
#define BASESIZE 5
#define MULTBASE 2
#define DUMPSPEC "%x"			//Example: "%d" for int, "%c" for char

#pragma region Define checks
#ifndef TData
#define TData int
#endif

#ifndef DUMPSPEC
#define DUMPSPEC "%x"
#endif

#ifdef BASESIZE
#if !(BASESIZE>0 && BASESIZE<=INT_MAX) 
#define BASESIZE 1
#endif
#endif
#ifndef BASESIZE
#define BASESIZE 1
#endif

#ifdef MULTBASE
#if !(MULTBASE>1 && MULTBASE<=SHRT_MAX)
#define MULTBASE 2
#endif
#endif
#ifndef MULTBASE
#define MULTBASE 2
#endif
#pragma endregion Checks defines validity

typedef enum {
	ERROR_OK = 0,
	ERROR_UNKNOWN,				//Unknown error
	ERROR_INVALID_SIZE,			//Size != BASESIZE * 2^(n-1)
	ERROR_OVERFLOW,				//Stack size not within (0 - SIZE) range
	ERROR_EMPTY,				//Popping empty stack
	ERROR_NULL_DATA_POINTER,	//Data == NULL
	ERROR_NULL_STACK_POINTER	//NULL stack pointer
} TError;

enum {
	ERROR_CPU_OK = 0, 
	ERROR_null_cpu_p = 1,           // null pointer  
	ERROR_null_cmds_p = 2,          // no comands
	ERROR_inv_cpu_data_stack = 3,   // problems with stack
	ERROR_cpu_null_data_p = 4
};


typedef struct TStack
{
	int count;
	int size;
	TData* data;
} TStack;

/*Stack CPU*/
typedef struct
{
    double* commands_to_execute;
    TStack * cpu_data;
    double a_reg;
    double b_reg;
    double c_reg;
} Stack_cpu;

TError stack_push(TStack* const stack, const TData value);
TError stack_pop(TStack* const stack, TData* const var);
TError stack_ok(const TStack* const stack);
TError stack_construct(TStack** const stack);
TError stack_destruct(TStack** const stack);
void stack_dump(const TStack* const stack);
void stack_error(const TStack* const stack, const TError error);


TError stack_pop(TStack* const stack, TData* const var)
{
	int i = 0;

	stack_error(stack, stack_ok(stack));

	if (stack->size == 0)
	{
		stack_error(stack, ERROR_EMPTY);
	}

	*var = stack->data[0];

	for (i = 0; i < stack->count - 1; i++)
	{
		stack->data[i] = stack->data[i + 1];
	}

	stack->count--;

	if ((stack->count) >= BASESIZE)
	{
		if ((stack->size / stack->count == MULTBASE) && (stack->size % stack->count == 0))
		{
			stack->size = stack->size / MULTBASE;
			stack->data = (TData*)realloc(stack->data, sizeof(TData)*(stack->size));
		}
	}

	return ERROR_OK;
}
TError stack_push(TStack* const stack, const TData value)
{
	stack_error(stack, stack_ok(stack));
	if (stack->size == stack->count)
	{
		stack->size = (stack->size) * MULTBASE;
		stack->data = (TData*)realloc(stack->data, sizeof(TData)*(stack->size));
	}
	if (stack->data != NULL)
	{
		stack->data[stack->count++] = value;
	}
	stack_error(stack, stack_ok(stack));
	return ERROR_OK;
}
TError stack_destruct(TStack** const stack)
{
	stack_error(*stack, stack_ok(*stack));
	free((*stack)->data);
	free((*stack));
	*stack = NULL;
	return ERROR_OK;
}
TError stack_construct(TStack** const stack)
{
	*stack = (TStack*)malloc(sizeof(TStack));
	if (*stack != NULL)
	{
		(*stack)->count = 0;
		(*stack)->size = BASESIZE;
		(*stack)->data = (TData*)malloc(sizeof(TData)*BASESIZE);
	}
	stack_error((*stack), stack_ok(*stack));
	return ERROR_OK;
}
void stack_error(const TStack* const stack, const TError error)
{
	switch (error)
	{
	case ERROR_OK: return; break;
	case ERROR_UNKNOWN: printf("\nERROR: Unknown error\n"); break;
	case ERROR_INVALID_SIZE: printf("\nERROR: Size != BASESIZE * 2^(n-1)\n"); break;
	case ERROR_OVERFLOW: printf("\nERROR: Stack size not within (0 - SIZE) range\n"); break;
	case ERROR_NULL_DATA_POINTER: printf("\nERROR: Data == NULL\n"); break;
	case ERROR_EMPTY: printf("\nERROR: Popping empty stack\n"); break;
	case ERROR_NULL_STACK_POINTER: printf("\nERROR: NULL stack pointer\n"); assert(0); break;
	default: printf("\nERROR: Unknown error\n"); break;
	};
	stack_dump(stack);
	assert(0);
}
TError stack_ok(const TStack* stack)
{
	if (stack == NULL)
	{
		return ERROR_NULL_STACK_POINTER;
	}
	else
	{
		if (stack->size < BASESIZE)
		{
			return ERROR_INVALID_SIZE;
		}
		else
		{
			if (stack->size % BASESIZE == 0)
			{
				int i;
				for (i = (stack->size / BASESIZE); (i % 2 == 0); i = i / 2)
				{
				}
				if (i == 1)
				{
					if ((stack->count < 0) || (stack->count > stack->size))
					{
						return ERROR_OVERFLOW;
					}
					else
					{
						if (stack->data == NULL)
						{
							return ERROR_NULL_DATA_POINTER;
						}
						else
						{
							return ERROR_OK;
						}
					}
				}
				else
				{
					return ERROR_INVALID_SIZE;
				}
			}
			else
			{
				return ERROR_INVALID_SIZE;
			}
		}
	}
	return ERROR_UNKNOWN;
}
void stack_dump(const TStack* const stack)
{
	int i = 0;
	printf("------STACK DUMP-------\nSize: %d\nCount: %d\nData pointer: %p\n", stack->size, stack->count, stack->data);
	for (i = 0; i < stack->size; i++)
	{
		printf("%10i: "DUMPSPEC"\n", i, stack->data[i]);
	}
	printf("------END OF DUMP------\n");
}

int Stack_cpu_constructor(Stack_cpu* cpu_p);
int Stack_cpu_destruct(Stack_cpu* cpu_p);
int Stack_cpu_read_comands(Stack_cpu* cpu_p, FILE* cmds_file);
void Comands(Stack_cpu* cpu_p);
int Stack_cpu_ok(Stack_cpu* cpu_p);
int Stack_cpu_dump(Stack_cpu* cpu_p);
void Stack_cpu_check(Stack_cpu* cpu);

int Stack_cpu_err_num = 0;


enum {
     PUSH = 1,
     ADD = 2,
     MUL = 3,
     SUB = 4,
     DIV = 5,
     END = 6,

     JMP = 7,
     JA = 8,
     JAE = 9,
     JB = 10,
     JBE = 11,
     JE = 12,
     JNE = 13,

     

     
     PUSHA = 15,
     PUSHB = 16,
     PUSHC = 17,
     POPA = 18,
     POPB = 19,
     POPC = 20
};

