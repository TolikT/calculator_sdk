#include<stdlib.h>
#include<expr2str.h>
#include"console.h"

char* expr2str(char* expr)
{
	structure* stackopers = NULL;
	//char outstring[80];
	char* outstring;
	int i,j;
	outstring = (char*)malloc(80);
	i=j=0;
	//writeline(expr);// writeline("\n ");
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
	//writeline(outstring);//writeline("\nstroka");
	return outstring;
}

//push character(operation) to the operation-stack
structure* Push(structure* head, char a)
{
	structure* ptr = (structure*)malloc(sizeof(structure)); // ???check empty memory???  
	ptr ->operation = a;
	ptr ->nextmem = head;
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
