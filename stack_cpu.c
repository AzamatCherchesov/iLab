#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

int Stack_cpu_construct(Stack_cpu* cpu_p)
{
    cpu_p->commands_to_execute = (double*)calloc(MAX_SIZE,  sizeof(*(cpu_p->commands_to_execute)));
    assert(cpu_p->commands_to_execute);
    cpu_p->cpu_data = (Stack_t*)calloc(1, sizeof(*cpu_p->cpu_data));
    assert(cpu_p->cpu_data);
	stack_construct(cpu_p->cpu_data);
    
    cpu_p->a_register = 0;
	cpu_p->b_register = 0;
	cpu_p->c_register = 0;
    return 0;
}

int Stack_cpu_destruct(Stack_cpu* cpu_p)
{
	cpu_p->a_register = 0;
	cpu_p->b_register = 0;
	cpu_p->c_register = 0;
    free(cpu_p->commands_to_execute);
    cpu_p->commands_to_execute = NULL;
    stack_destruct(cpu_p->cpu_data);
    free(cpu_p->cpu_data);
    cpu_p->cpu_data = NULL;
    return 0;
}

int Stack_cpu_ok(Stack_cpu* cpu_p)
{
    if(!cpu_p)
    {
        Stack_cpu_err_num = null_cpu_p;
        return 1;
    }
    else if (!(cpu_p->cpu_data))
    {
        Stack_cpu_err_num = null_data_p;
        return 1;
    }
    else if (!(cpu_p->commands_to_execute))
    {
        Stack_cpu_err_num = no commands;
        return 1;
    }
    else if (stack_ok(cpu_p->cpu_data))
    {
        Stack_cpu_err_num = inv_cpu_data_stack;
        return 1;
    }
    Stack_cpu_err_num = stack_cpu_is_ok;
    return 0;
}

int Stack_cpu_dump(Stack_cpu* cpu_p)
{
    printf("[0x%lx]\n", (unsigned long)cpu_p);;
    printf("REGISTER A:% lg\n", cpu_p->a_register);
    printf("REGISTER B:% lg\n", cpu_p->b_register);
    printf("REGISTER C:% lg\n", cpu_p->c_register);
    stack_dump(cpu_p->cpu_data);
    return 0;
}

void Stack_cpu_check(Stack_cpu* cpu)
{
    if (Stack_cpu_ok(cpu))
    {
        Stack_cpu_dump(cpu);
        assert(0);
    }
}

int Stack_cpu_read_comands(Stack_cpu* cpu_p, FILE* cmd_file)
{
    fseek(cmds_file, 0, SEEK_END);
    long file_length = ftell(cmds_file);
    fseek(cmds_file, 0, SEEK_SET);
    fread((cpu_p->commands_to_execute), sizeof(*(cpu_p->commands_to_execute)),file_length/sizeof(*(cpu_p->commands_to_execute)), cmds_file);
    return 0;
}

void Commands(Stack_cpu* cpu_p)
{
    long i = 0;
    int new_code = 0;
    for (i = 0;cpu_p->commands_to_execute[i] != END; i++)
    {
            new_code = cpu_p->commands_to_execute[i];
            if (new_code == PUSH)
            {
                i++;
                push(cpu_p->cpu_data, cpu_p->commands_to_execute[i]);
                continue;
            }
            else if (new_code == JA || new_code == JAE || new_code == JB || new_code == JBE || new_code == JE || new_code == JNE)
            {
                i++;
                double next = pop(cpu_p->cpu_data);
                double prev = pop(cpu_p->cpu_data);
                if ( (next > prev && new_code == JA) ||
                    (next >= prev && new_code == JAE) ||
                    (next < prev && new_code == JB) ||
                    (next <= prev && new_code == JBE) ||
                    (next == prev && new_code == JE) ||
                    (next != prev && new_code == JNE))
                {
                    i = cpu_p->commands_to_execute[i] - 1;                                      
                }
                push(cpu_p->cpu_data, prev);
                push(cpu_p->cpu_data, next);
                continue;
            }
            else if (new_code == JMP)
            {
                i++;
                i = cpu_p->commands_to_execute[i] - 1;                                       
                continue;
            }
            else if (new_code == ADD || new_code == SUB || new_code == MUL || new_code == DIV)
            {
                double temp1 = pop(cpu_p->cpu_data);
                double temp2 = pop(cpu_p->cpu_data);
                if(new_code==ADD)
                    push(cpu_p->cpu_data, temp1+temp2);
                if(new_code==SUB_)
                    push(cpu_p->cpu_data, temp1-temp2);
                if(new_code==MUL)
                    push(cpu_p->cpu_data, temp1*temp2);
                if(new_code==DIV)
                {
                    if (temp2 == 0)
                    {
                        printf( "Division by 0\n");
                        assert(temp2);
                    }
                    else
                    {
                        push(cpu_p->cpu_data, temp1/temp2);
                    }
                }
            }
            else  if(new_code == POP)
            {
                printf("%lg\n", pop(cpu_p->cpu_data));
            }
            else if(new_code >= PUSHA && new_code <= PUSHC)
            {
                if(new_code == PUSHA)
                    push(cpu_p->cpu_data,cpu_p->a_register);
                if(cmd_code == PUSHB_CODE)
                    push(cpu_p->cpu_data,cpu_p->b_register);
                if(cmd_code == PUSHC_CODE)
                    push(cpu_p->cpu_data,cpu_p->c_register);

            }
            else if(new_code >= POPA && new_code <= POPC)
            {
                if(new_code == POPA)
                    cpu_p->a_register = pop(cpu_p->cpu_data);
                if(new_code == POPB)
                    cpu_p->b_register = pop(cpu_p->cpu_data);
                if(new_code == POPC)
                    cpu_p->c_register = pop(cpu_p->cpu_data);
                
            }
        }
    }

