
#include<stdio.h>
#include<ctype.h>
#include<string.h>

enum{INIT, SYMBOLE, DECIMAL, DIRECTIVE, VIRGULE, ZERO, HEXA, OCTA, REGISTRE};

void aef(char* text)
{
	int c;
	int S=INIT;
	int longueur_phrase=strlen(text);
	for(c=0;c<=longueur_phrase+1;c=c+1) 
	{
		switch(S)
		{
		case INIT:
			if (isdigit(text[c]) && text[c]>'0')
				{ 
				printf("%c",text[c]);
				S=DECIMAL;
				}
			else if (isalpha(text[c])) 
				{
				printf("%c",text[c]);
				S=SYMBOLE;
				}
			else if (text[c]=='.')
				{
				printf("%c",text[c]);
				S=DIRECTIVE;
				}
			else if (text[c]==',')
				{
				printf("%c",text[c]);
				S=VIRGULE;
				}
			else if (text[c]=='$')
				{
				printf("%c",text[c]);
				S=REGISTRE;
				}
			else if (text[c]=='0')
				{
				printf("%c",text[c]);
				S=ZERO;
				}
			else if (isspace(text[c])) 
				{
				S=INIT;
				}
			else if (text[c]=='\0') printf("Fin \n");
			break;
		case ZERO:
			if (text[c]=='x' || text[c]=='X')
				{
				printf("%c",text[c]);
				S=HEXA;
				}
			else if (isdigit(text[c]) && text[c]<'8')
				{
				printf("%c",text[c]);
				S=OCTA;
				}
			else if (isalpha(text[c]) || text[c]>='8')
				{
				printf("%c",text[c]);
				S=SYMBOLE;
				}
			else if (isspace(text[c]) || text[c]=='\0')
				{
				printf(" ZERO \n");
				S=INIT;
				}
			break;
		case HEXA:
			if (isdigit(text[c]))
				{
				printf("%c",text[c]);
				S=HEXA;
				}
			else if (isalpha(text[c]) && text[c]<'g')
				{
				printf("%c",text[c]);
				S=HEXA;
				}
			else if (isalpha(text[c]) && text[c]>'g')
				{
				printf("%c",text[c]);
				S=SYMBOLE;
				}
			else if (text[c]=='$')
				{
				printf("%c",text[c]);
				S=REGISTRE;
				}
			else if (isspace(text[c]))
				{
				printf(" HEXA \n");
				S=INIT;
				}
			break;
		case OCTA:
			if (isdigit(text[c]) && text[c]<'9')
				{
				printf("%c",text[c]);
				S=OCTA;
				}
			else if (isdigit(text[c]) || text[c]=='9')
				{
				printf("%c",text[c]);
				S=SYMBOLE;
				}
			else if (isspace(text[c]))
				{
				printf(" OCTA \n");
				S=INIT;
				}
			break;
		case REGISTRE:
			if (isdigit(text[c]) || isalpha(text[c]))
				{
				printf("%c",text[c]);
				S=REGISTRE;
				}
			else if (isspace(text[c]) || text[c]=='\0')
				{
				printf(" REGISTRE \n");
				S=INIT;
				}
			break;
		case VIRGULE:
			printf(" VIRGULE \n");
			S=INIT;
			break;
		case DIRECTIVE:
			if (isalpha(text[c]) || isdigit(text[c]))
				{
				S=DIRECTIVE;
				printf("%c",text[c]);
				}
			else if	(isspace(text[c]) || text[c]=='\0')
				{
				printf(" DIRECTIVE \n");
				S=INIT;
				}
			break;
		case DECIMAL:
			if (isdigit(text[c]))
				{
				printf("%c",text[c]);
				S=DECIMAL;
				}
			else  if (isalpha(text[c]))
				{
				printf("%c",text[c]);
				S=SYMBOLE;
				}
			else if (isspace(text[c]) || text[c]=='\0') 
				{
				printf(" DECIMAL \n");
				S=INIT;
				}
			break;
		case SYMBOLE:
			if (isalpha(text[c])) 
				{
				printf("%c",text[c]);
				S=SYMBOLE;
				}
			else if (isdigit(text[c])) 
				{
				printf("%c",text[c]);
				S=SYMBOLE;
				}
			else if (isspace(text[c]) || text[c]=='\0') 
				{
				printf(" SYMBOLE \n");
				S=INIT;
				}
			break;
		}
	}
}
	


	


