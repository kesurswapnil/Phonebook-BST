void AddContact(NODE **root,NODE **nroot,NODE **sroot)
{
	// Take details from user.
	char name[20],sname[20],phnum[20];
	printf("Enter name of contact: ");
	scanf(" %s",name);
	printf("Enter surname of contact: ");
	scanf(" %s",sname);
	printf("Enter phone number of contact: ");
	scanf(" %s",phnum);
	NODE *k=searchNumber(*root,phnum);
				if(k!=NULL)
				{
					printf("Contact with same phone number already exists!");
					printf("\n\tName: %s %s\tPhone number: %s",k->name,k->sname,k->phnumber);
					return;
				}
	//Write the  new contact to phonebook.txt
	FILE *fp;
	fp=fopen("phonebook.txt","a");
	fprintf(fp,"%s %s %s\n",name,sname,phnum);
	fclose(fp);
    //Add the contact's phone number to BST
	NODE *a,*b,*c;
    if(*nroot==NULL)
    {
	    a=createNode(name,sname,phnum);
        *nroot=a;
        return;
    }
    else
    {
    	if(strcmp((name),((*nroot)->name))==-1)
    		nameInsert(&((*nroot)->left),name,sname,phnum);
    	else
    		nameInsert(&((*nroot)->right),name,sname,phnum);
	}
	
	if(*sroot==NULL)
    {
	    b=createNode(name,sname,phnum);
        *sroot=b;
        return;
    }
    else
    {
    	if(strcmp((sname),((*sroot)->sname))==-1)
    		surnameInsert(&((*sroot)->left),name,sname,phnum);
    	else
    		surnameInsert(&((*sroot)->right),name,sname,phnum);
	}
	
	if(*root==NULL)
    {
	    c=createNode(name,sname,phnum);
        *root=c;
        return;
    }
    else
    {
    	if(strcmp((phnum),((*root)->phnumber))==-1)
    		numInsert(&((*root)->left),name,sname,phnum);
    	else
    		numInsert(&((*root)->right),name,sname,phnum);
	}
	
	return;
}



void EditContact(NODE **root,NODE **nroot,NODE **sroot)
	{
		FILE *fp;
		int flag;
		fp=fopen("phonebook.txt","r");
		char fname[20],fsname[20],name[20],sname[20],fnum[20],num[20],newname[20];
		printf("\nEnter name and surname whose details are to be edited: ");
		scanf(" %s %s",name,sname);
		//char tname[20];
		//strcpy(tname,name); strlwr(tname);
		while(1)
		{
		flag=fscanf(fp,"%s %s %s\n",fname,fsname,fnum);
		if(flag==EOF)
		{	
			printf("\nContact not found.");
			suggestionsN(*nroot,name);
			suggestionsS(*sroot,sname);
			fclose(fp);
			break;
	 	}
		if(strcmp(fname,name)==0 && strcmp(fsname,sname)==0)
		{   
			fclose(fp);
			printf("\nEnter new name of contact: ");
			scanf(" %s",newname);
			printf("\nEnter new surname of contact: ");
			scanf(" %s",sname);
			printf("\nEnter new number of contact: ");
			scanf(" %s",num);
			
			NODE *k=searchNumber(*root,num);
				if(k!=NULL)
				{
					printf("Contact with same phone number already exists!");
					printf("\n\tName: %s %s\tPhone number: %s",k->name,k->sname,k->phnumber);
					return;
				}
			
			*nroot=nameDeleteNode(*nroot,fname);
			*sroot=surnameDeleteNode(*sroot,fsname);
			*root=numDeleteNode(*root,fnum);
			
			nameInsert(nroot,newname,sname,num);
			surnameInsert(sroot,newname,sname,num);
			numInsert(root,newname,sname,num);
			
			fp=fopen("phonebook.txt","w");
			treeToFile(*nroot,fp);
			fclose(fp);
			break;
		} 
		
	}
	return;
}


void DeleteContact(NODE **root,NODE **nroot,NODE **sroot,NODE **broot)
{
				int tflg=0; char topt;
				char name[20],sname[20],fname[20],fsname[20],fphnum[20];
				printf("\nEnter name and surname whose contact is to be deleted: ");
				scanf(" %s %s",name,sname);
				FILE *fpr;
				fpr=fopen("phonebook.txt","r");
				while(1)
				{
					int rv=fscanf(fpr,"%s %s %s\n",fname,fsname,fphnum);
					if(rv==EOF)
						break;
					if((strcmp(fname,name)==0) && (strcmp(fsname,sname)==0))
						{
							tflg=1;
							break;
						}
				}
				fclose(fpr);
				if(tflg==1)
				{
					printf("\nName:%s %s\tPhone Number: %s ",fname,fsname,fphnum);
					printf("\nAre you sure to delete this contact ?(Y/N)\n");
					scanf(" %c",&topt);
					if(topt=='y' || topt=='Y')
					{
					*nroot=nameDeleteNode(*nroot,fname);
					*sroot=surnameDeleteNode(*sroot,fsname);
					*root=numDeleteNode(*root,fphnum);
				
					FILE*fp=fopen("rphonebook.txt","a");
            		fprintf(fp,"%s %s %s\n",fname,fsname,fphnum);
            		fclose(fp);
					nameInsert(broot,fname,fsname,fphnum);
					
					FILE *fp1;
					fp1=fopen("phonebook.txt","w");
					treeToFile(*nroot,fp1);
					fclose(fp1);
					}
					return;
				}
				else
				{
					printf("\nContact not found. ");
					suggestionsN(*nroot,name);
					suggestionsS(*sroot,sname);
					return;
				}
}
