
NODE* createBinBST(NODE *broot)
{
	broot=NULL;
	char phnum[20];
    	char name[20];
    	char sname[20];
    	FILE *fp,*fpn;
	    fp=fopen("rphonebook.txt","r");
    	while(1)  //Create BST from file phonebook.txt
			{		
				int flag;
				flag=fscanf(fp,"%s %s %s\n",name,sname,phnum);
       			if(flag==EOF)
	  				break;
        		nameInsert(&broot,name,sname,phnum);
			}
		fclose(fp);
		return broot;
}


void restoreBin(NODE *broot,NODE *root,NODE *nroot,NODE *sroot)
{
	char opt;
	char name[20],sname[20],phnum[20];
	FILE *fp,*fp1;
	printf("\nDo you want to restore entire bin ?(Y/N)\n");
	scanf(" %c",&opt);
	fp=fopen("rphonebook.txt","r");
	fp1=fopen("phonebook.txt","a");
	if(opt=='y' || opt=='Y')
	{
		while(1)
		{
			int rv=fscanf(fp,"%s %s %s\n",name,sname,phnum);
			if(rv==EOF)
				break;
			fprintf(fp1,"%s %s %s\n",name,sname,phnum);
			nameInsert(&nroot,name,sname,phnum);
			surnameInsert(&sroot,name,sname,phnum);
			numInsert(&root,name,sname,phnum);
		}
	deleteTree(broot);
	fclose(fp1);
	fclose(fp);
	fp=fopen("rphonebook.txt","w");
	fclose(fp1);
	}
	else
	{
		char fname[20],fsname[20],fphnum[20];
		printf("Enter name of contact to be restored: ");
		scanf(" %s",name);
		while(1)
		{
			int rv=fscanf(fp,"%s %s %s\n",fname,fsname,fphnum);
				if(rv==EOF)
				{
					printf("\nContact not found!");
					suggestionsN(broot,name);
					break;
				}
			if(strcmp(name,fname)==0)
				{
					fprintf(fp1,"%s %s %s\n",fname,fsname,fphnum);
					nameInsert(&nroot,fname,fsname,fphnum);
					surnameInsert(&sroot,fname,fsname,fphnum);
					numInsert(&root,fname,fsname,fphnum);
					broot=nameDeleteNode(broot,fname);
				}
		}
		fclose(fp1);
		fclose(fp);
		fp=fopen("rphonebook.txt","w");
		treeToFile(broot,fp);
		fclose(fp);
	}
	return;
}

void displayBin()
{
	FILE *fp;
	int flag=0;
	char name[20],sname[20],phnum[20];
	fp=fopen("rphonebook.txt","r");
	while(1)
	{
		int rv=fscanf(fp,"%s %s %s\n",name,sname,phnum);
		if(rv==EOF)
		{
			if(flag==0)
				printf("\nRecycle bin is empty!");
			break;
		}
		printf("\nName: %s %s\tPhone Number: %s",name,sname,phnum);
		flag=1;
	}
	return;
}
