#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *substring(char *dst,char *src,int start,int len)
{  
	char *p=dst;  
	char *q=src;  
	int length=strlen(src); 
	if(start>=length||start<0) 
		return NULL;  
	if(len>length) 
		len=length-start; 
	q+=start;
	while(len--)  
	{   
		*(p++)=*(q++); 
	}  
	*(p++)='\0';  
	return dst;
}
