
#include<stdio.h>
#include<ctype.h>
#include<string.h>

enum{INIT, SYMBOLE, DECIMAL, DIRECTIVE, VIRGULE, ZERO, HEXA, OCTA, DOLLAR, REGISTRE, POINT, DEUX_POINTS, PARENTHESE, ERREUR};

void aef(char* text, int ligne)//, Lexeme_t * list)
	{
	int c,i;
	int S=INIT;
	int longueur_phrase=strlen(text);
	for(c=0,i=0;c<=longueur_phrase;c++,i++) 
		{
		switch(S)
			{
			case INIT:
				i=0;
				char mot[100]="";
				if (isdigit(text[c]) && text[c]>'0')
					{ 
					mot[i]=text[c];
					S=DECIMAL;
					}
				else if (text[c]=='(' || text[c]==')')
					{
					mot[i]=text[c];
					S=PARENTHESE;
					}
				else if (text[c]==':')
					{
					mot[i]=text[c];
					S=DEUX_POINTS;
					}
				else if (isalpha(text[c])) 
					{
					mot[i]=text[c];
					S=SYMBOLE;
					}
				else if (text[c]=='.')
					{
					mot[i]=text[c];
					S=POINT;
					}
				else if (text[c]==',')
					{
					mot[i]=text[c];
					S=VIRGULE;
					}
				else if (text[c]=='$')
					{
					mot[i]=text[c];
					S=DOLLAR;
					}
				else if (text[c]=='0')
					{
					mot[i]=text[c];
					S=ZERO;
					}
				else if (isspace(text[c])) 
					{
					S=INIT;
					}
				else if (text[c]=='\0') 
					{
					printf("ligne %d \n",ligne);
				break;
			case POINT:
				if (isalpha(text[c]))
					{
					mot[i]=text[i];
					S=DIRECTIVE;
					}
				else if (isspace(text[c]))
					{
					//push(list,mot,S,ligne);
					printf("%s ==> ERREUR \n",mot);
					S=INIT;
					}
				else 
					{
					mot[i]=text[c];
					S=ERREUR;
					}
			case DOLLAR:
				if (isalpha(text[c]) || isdigit(text[c]))
					{
					mot[i]=text[c];
					S=REGISTRE;
					}
				else if (isspace(text[c]))
					{
					//push(list,mot,S,ligne);
					printf("%s ==> ERREUR \n",mot);
					S=INIT;
					}
				else
					{
					mot[i]=text[c];
					S=ERREUR;
					}
			case PARENTHESE:
				//push(list,mot,S,ligne);
				printf("%s ==> PARENTHESE \n",mot);
				S=INIT;
				break;
			case DEUX_POINTS:
				//push(list,mot,S,ligne);
				printf("%s ==> DEUX_POINTS \n",mot);
				S=INIT;
				break;
			case VIRGULE:
				//push(list,mot,S,ligne);
				printf("%s ==> VIRGULE \n",mot);
				S=INIT;
				break;
			case ZERO:
				if (text[c]=='x' || text[c]=='X')
					{
					mot[i]=text[c];
					S=HEXA;
					}
				else if (isdigit(text[c]) && text[c]<'8')
					{
					mot[i]=text[c];
					S=OCTA;
					}
				else if (isalpha(text[c]) || text[c]>='8')
					{
					mot[i]=text[c];
					S=SYMBOLE;
					}
				else if (isspace(text[c]) || text[c]=='\0')
					{
					//push(list,mot,S,ligne);
					printf("%s ==> ZERO \n",mot);
					S=INIT;
					}
				break;
			case HEXA:
				if (isdigit(text[c]))
					{
					mot[i]=text[c];
					S=HEXA;
					}
				else if (isalpha(text[c]) && text[c]<'g')
					{
					mot[i]=text[c];
					S=HEXA;
					}
				else if (isalpha(text[c]) && text[c]>'g')
					{
					mot[i]=text[c];
					S=ERREUR;
					}
				else if (isspace(text[c]))
					{
					//push(list,mot,S,ligne);
					printf("%s ==> HEXA \n",mot);
					S=INIT;
					}
				break;
			case OCTA:
				if (isdigit(text[c]) && text[c]<'9')
					{
					mot[i]=text[c];
					S=OCTA;
					}
				else if (isdigit(text[c]) || text[c]=='9')
					{
					mot[i]=text[c];
					S=ERREUR;
					}
				else if (isspace(text[c]))
					{
					//push(list,mot,S,ligne);
					printf("%s ==> OCTA \n",mot);
					S=INIT;
					}
				break;
			case REGISTRE:
				if (isdigit(text[c]) || isalpha(text[c]))
					{
					mot[i]=text[c];
					S=REGISTRE;
					}
				else if (isspace(text[c]) || text[c]=='\0')
					{
					//push(list,mot,S,ligne);
					printf("%s ==> REGISTRE \n",mot);
					S=INIT;
					}
				break;
			case DIRECTIVE:
				if (isalpha(text[c]) || isdigit(text[c]))
					{
					mot[i]=text[c];
					S=DIRECTIVE;
					}
				else if	(isspace(text[c]) || text[c]=='\0')
					{
					//push(list,mot,S,ligne);
					printf("%s ==> DIRECTIVE \n",mot);
					S=INIT;
					}
				break;
			case DECIMAL:
				if (isdigit(text[c]))
					{
					mot[i]=text[c];
					S=DECIMAL;
					}
				else  if (isalpha(text[c]))
					{
					mot[i]=text[c];
					S=ERREUR;
					}
				else if (isspace(text[c]) || text[c]=='\0') 
					{
					//push(list,mot,S,ligne);
					printf("%s ==> DECIMAL \n",mot);
					S=INIT;
					}
				break;
			case SYMBOLE:
				if (isalpha(text[c])) 
					{
					mot[i]=text[c];
					S=SYMBOLE;
					}
				else if (isdigit(text[c])) 
					{
					mot[i]=text[c];
					S=SYMBOLE;
					}
				else if (isspace(text[c]) || text[c]=='\0') 
					{
					//push(list,mot,S,ligne);
					printf("%s ==> SYMBOLE \n",mot);
					S=INIT;
					}
				break;
			case ERREUR:
				if (isspace(text[c]))
					{
					//push(list,mot,S,ligne);
					printf("%s ==> ERREUR \n",mot);
					S=INIT;
					}
				else
					{
					mot[i]=text[c];
					S=ERREUR;
					}
			}
		}
	}	
	}
