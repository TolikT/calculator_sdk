//#include <stdio.h>
#include <stdlib.h>
#include "aduc812.h"
#include "console.h"
#include "print.h"
#include "str.h"
#include <string.h>
#include "expr2str.h"


//element of the operand-stack
typedef struct number
{
	int operand;
	struct number* nextnum;
} num_struct;

//structure* Push(structure*, char);
//char Pop(structure**);
num_struct* push_Num(num_struct*, int);
int pop_Num(num_struct**);
//void itoa(int, char*);
//void reverse(char*);

char* calc(char* outstring)
{
	char* res;
	int k, result, a, b;
	num_struct* stackoperands = NULL;
	k=result=a=b=0;	
	res = (char*)malloc(80*sizeof(char));
	while (outstring[k] != '\0')
	{
		switch(outstring[k])
		{
			case '+':
				result = pop_Num(&stackoperands) + pop_Num(&stackoperands);
				stackoperands = push_Num(stackoperands, result);
				k++;
				result = 0;
				break;
			case '-':
				result = -pop_Num(&stackoperands) + pop_Num(&stackoperands);
				stackoperands = push_Num(stackoperands, result);
				k++;
				result = 0;
				break;
			case '*':
				result = pop_Num(&stackoperands) * pop_Num(&stackoperands);
				stackoperands = push_Num(stackoperands, result);
				k++;
				result = 0;
				break;
			case '/':
				b = pop_Num(&stackoperands);

				a = pop_Num(&stackoperands);
				result = a/b;
				stackoperands = push_Num(stackoperands, result);
				k++;
				result = 0;
				break;
			case '=':
				b = pop_Num(&stackoperands);
				a = pop_Num(&stackoperands);
				result = a==b;
				stackoperands = push_Num(stackoperands, result);
				k++;
				result = 0;
				break;
			case '!':
				b = pop_Num(&stackoperands);
				a = pop_Num(&stackoperands);
				result = a!=b;
				stackoperands = push_Num(stackoperands, result);
				k++;
				result = 0;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				while ((outstring[k] >= '0') && (outstring[k] <='9'))
				{
					result = result*10 ;
					result = result	+ (outstring[k] - 48);
					k++;
				}
				stackoperands = push_Num(stackoperands, result);
				result = 0;
				break;
			default: 
				k++;
		}		
	}
	//printf("\n%d\n", stackoperands->operand);
	itoa(stackoperands->operand, res);
	return res;
} 

int main(void)
{	
	
	
	char* outstring;
	int c;
	char* expr;
	Clear();
	TMOD = 0x20; // Таймер 1 в режиме autoreload
	TCON=0x40; // Запуск таймера 1
	SCON=0x50;
	TH1 = 0xFD;
	SetVector(0x2023, (void*) SIO_ISR);
	EA=1;
	ES=1;	
	expr = (char*)malloc(80*sizeof(char));
	outstring = (char*)malloc(80*sizeof(char));
	
	expr = readline();
	for(c = 0; c < strlen(expr); c++)
		PrintChar(expr[c]);
	
	outstring = expr2str(expr);
	writeline(outstring);//writeline("\nstroka"); 
	writeline(calc(outstring));
	//getchar();
	//fflush(stdin);
	return 0;
}



//push operand to the operand-stack
num_struct* push_Num(num_struct* head, int a)
{
	num_struct* ptr = (num_struct*)malloc(sizeof(num_struct));
	ptr ->operand = a;
	ptr ->nextnum = head;
	return ptr;
}



//obtain operand from the stack
//and return it like a number
int pop_Num(num_struct** head)
{
	num_struct* ptr;
	int a;
	ptr = *head;
	a = ptr->operand;
	*head = ptr->nextnum;
	free(ptr);
	return a;
}


