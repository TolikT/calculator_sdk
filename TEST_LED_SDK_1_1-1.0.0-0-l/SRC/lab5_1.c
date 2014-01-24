//#include <stdio.h>
#include <stdlib.h>
#include "aduc812.h"
#include "console.h"
#include "print.h"
#include <string.h>

//element of the operation-stack
typedef struct member
{
	char operation;
	struct member* nextmem;
} structure;

//element of the operand-stack
typedef struct number
{
	int operand;
	struct number* nextnum;
} num_struct;

structure* Push(structure*, char);
char Pop(structure**);
int Priority(char);
num_struct* push_Num(num_struct*, int);
int pop_Num(num_struct**);
void itoa(int, char*);
void reverse(char*);

int main(void)
{
	structure* stackopers = NULL;
	num_struct* stackoperands = NULL;
	char /*expr[80],*/ outstring[80], res[80];
	int i, j, k, result, a, b, c, d;
	char* expr/*, res*/;
	Clear();
	TMOD = 0x20; // Таймер 1 в режиме autoreload
	TCON=0x40; // Запуск таймера 1
	SCON=0x50;
	TH1 = 0xFD;
	SetVector(0x2023, (void*) SIO_ISR);
	EA=1;
	ES=1;	
	//puts("Enter expression");
	//fflush(stdin);
	//gets(expr);
	expr = (char*)malloc(80*sizeof(char));
	//res = (char*)malloc(80*sizeof(char));
	expr = readline();
	//writeline(y);
	for(c = 0; c < strlen(expr); c++)
		PrintChar(expr[c]);
	i=j=k=result=a=b=0;
	while (expr[i]!='\0')
	{
		if (expr[i] == ')') //if the clothing bracket
		{
			while ((stackopers -> operation)!='(') //obtain operations from the stack
				outstring[j++] = Pop(&stackopers); //and write them to the outstring	
				outstring[j++] = ' ';
			Pop(&stackopers); //remove the opening bracket
		}
		if (expr[i] >= '0' && expr[i]<='9') //if the digit
		{
			//writeline("digit");
			if (expr[i+1] >= '0' && expr[i+1] <= '9')
				outstring[j++] = expr[i]; //write it to outstring
			else 
			{
				outstring[j++] = expr[i];
				outstring[j++] = ' '; //write ' ' after the number
			}
		}
		if (expr[i] == '(') //if the opening bracket
			stackopers = Push(stackopers, '('); //push it
		//if operation
		if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || 
			(expr[i] == '='&& expr[i+1] == '=') || (expr[i] == '!'&& expr[i+1] == '='))
		{ //if the stack is empty or trololo
			if ((stackopers == NULL) || (Priority(stackopers -> operation) < Priority(expr[i]))) 
				stackopers = Push(stackopers, expr[i]); //push operation
			else
			{   //while priority of the current operation <= priority of operations in the stack
				while ((stackopers!=NULL)&&(Priority(stackopers -> operation) >= Priority(expr[i])))
					outstring[j++] = Pop(&stackopers); //obtain it to outstring
					outstring[j++] = ' '; 
				stackopers = Push(stackopers, expr[i]);
			}
		}
		i++;
	}
	while (stackopers != NULL)
		outstring[j++] = Pop(&stackopers); //obtain last operations
		outstring[j++] = ' ';
	outstring[j] = '\0';
	//printf("\n%s\n", outstring);
	writeline(outstring);
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
	writeline(res);
	//getchar();
	//fflush(stdin);
	return 0;
}

//push character(operation) to the operation-stack
structure* Push(structure* head, char a)
{
	structure* ptr = (structure*)malloc(sizeof(structure)); // ???check empty memory???  
	ptr ->operation = a;
	ptr ->nextmem = head;
	return ptr;
}

//push operand to the operand-stack
num_struct* push_Num(num_struct* head, int a)
{
	num_struct* ptr = (num_struct*)malloc(sizeof(num_struct));
	ptr ->operand = a;
	ptr ->nextnum = head;
	return ptr;
}

//obtain operation from the stack
//and return it like a character
char Pop(structure** head)
{
	structure* ptr;
	char a;
	if (*head == NULL) return '\0';
	ptr = *head;
	a = ptr->operation;
	*head = ptr ->nextmem;
	free(ptr);
	return a;
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

//processing priority
int Priority(char a)
{
	switch (a)
	{
		case '*':
		case '/':
			return 4;
		case '-':
		case '+':
			return 3;
		case '=':
		case '!':
			return 2;
		case '(':
			return 1;
	}
}

void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

 void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* записываем знак */
         n = -n;          /* делаем n положительным числом */
     i = 0;
     do {       /* генерируем цифры в обратном порядке */
         s[i++] = n % 10 + '0';   /* берем следующую цифру */
     } while ((n /= 10) > 0);     /* удаляем */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }
