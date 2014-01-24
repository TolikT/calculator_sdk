#include "aduc812.h"
#include "max.h"

char* hello = "Hello, world!";

int GetBf()
{
unsigned char x;
write_max(C_IND, 0x03);
x=read_max(DATA_IND);
write_max(C_IND, 0x02);
if (x>0x7f)
return 1;
else
return 0;
}

void Clear()
{
while(1){if (GetBf()==0) break;}
write_max(DATA_IND, 0x01);
write_max(C_IND, 0x01);
write_max(C_IND, 0x00);
}

void Home()
{
while(1){if (GetBf()==0) break;}
write_max(DATA_IND, 0x02);
write_max(C_IND, 0x01);
write_max(C_IND, 0x00);
}

void SetDdram(int n)
{
while(1){if (GetBf()==0) break;}
n=(n|0x80);
write_max(DATA_IND, n);
}

void PrintChar(unsigned char x)
{
while(1){if (GetBf()==0) break;}
write_max(DATA_IND, x);
write_max(C_IND, 0x05);
write_max(C_IND, 0x00);
}
