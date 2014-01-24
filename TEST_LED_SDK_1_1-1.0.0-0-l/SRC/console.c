#include "aduc812.h"
//#include "max.h"
//#include "print.h"
//#include <string.h>
#include <stdlib.h>

char expr[80];
char* result;
int if_state = 0; // \n-flag
int count = 1;
int result_state = 0;
int end_state = 0;
char x;


char* readline()
{
	char* buffer; 
	count = 1;
	while(!if_state);
	if_state = 0;
	buffer = expr;
	return buffer;
}

void writeline(char* number)
{
	result = number;
	result_state = 1;
	TI = 1;
	while (!end_state);
	end_state = 0;
}

void SIO_ISR(void) __interrupt (4)
{
	char* newstr;
	if (RI & !result_state)
	{
		RI=0;
		if_state = SBUF=='\n';end_state = result_state=0;
		if(!if_state)
		{
			expr[count - 1]=SBUF;
			expr[count++]='\0';			
		}
		x=SBUF;
		TI=1;
	}
	if (TI)
	{
		if (!result_state)
		{
			TI=0;
			SBUF=x;
			while(!TI);
			TI=0;
		}
		if (result_state)
		{
			if (result[0]!='\0')
			{
				TI = 0;
				SBUF = result[0];
				while (!TI);
				result = &result[1];
				TI = 1;
			}
		}
		if (result[0] == '\0')
			end_state = 1;		
	}
}

void SetVector(unsigned char xdata * Address, void * Vector)
{
	unsigned char xdata * TmpVector;
	*Address=0x02;
	TmpVector = (unsigned char xdata *) (Address + 1);
	*TmpVector = (unsigned char) ((unsigned short)Vector >> 8);
	++TmpVector;
	*TmpVector = (unsigned char) Vector;
}

/*void main(void)
{
	int j = 0;
	int i = 0;
	char* y;
	Clear();
	TMOD = 0x20; // Таймер 1 в режиме autoreload
	TCON=0x40; // Запуск таймера 1
	SCON=0x50;
	TH1 = 0xFD;
	SetVector(0x2023, (void*) SIO_ISR);
	EA=1;
	ES=1;	
	y = readline();
	for(i = 0; i < strlen(y); i++)
		PrintChar(y[i]);
	writeline("result");	
}*/
