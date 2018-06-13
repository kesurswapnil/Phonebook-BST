#include<stdio.h>
#include<stdlib.h>
typedef struct contact
{
	char phnumber[20];
	char name[20];
	char sname[20];
}Contact;

int main()
{
	FILE *fp;
	Contact *c;
	char opt;
	fp=fopen("phonebook.txt","w");
	while(1)
	{
		c=(Contact*)malloc(sizeof(Contact));
		printf("\nEnter name: ");
		scanf(" %s",(c->name));
		printf("\nEnter surname: ");
		scanf(" %s",(c->sname));
		printf("\nEnter phone number: ");
		scanf("%s",(c->phnumber));
		fprintf(fp,"%s %s %s\n",(c->name),(c->sname),(c->phnumber));
		printf("\nAdd another contact(Y/N)? \n");
		fflush(stdin);
		scanf(" %c",&opt);
		if(opt=='y'||opt=='Y')
			continue;
		else
			break;
	}
	fclose(fp);
	return 0;
}
