#ifndef __CONSOLE__H
#define __CONSOLE__H


char* readline();
void writeline(char*);
void SIO_ISR(void) __interrupt (4);
void SetVector(unsigned char xdata *, void*);

#endif
