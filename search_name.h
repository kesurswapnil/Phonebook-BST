
NODE* nameDeleteNode(NODE *nroot, char *name)
{
    // base case
    if (nroot == NULL) return nroot;

	//If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if (strcmp(name,nroot->name)==-1)
        nroot->left = nameDeleteNode(nroot->left,name);

    // If the key to be deleted is greater than the root's key,then it lies in right subtree
    else if (strcmp(name,nroot->name)==1)
        nroot->right = nameDeleteNode(nroot->right,name);

    // if key is same as root's key, then This is the node to be deleted
    else
    {
        // node with only one child or no child
        if (nroot->left == NULL)
        {
            NODE *temp = nroot->right;
            
            free(nroot);
            return temp;
        }
        else if (nroot->right == NULL)
        {
            NODE *temp = nroot->left;
            
            free(nroot);
            return temp;
        }

        //Node with two children: Get the inorder successor (smallest in the right subtree)
        NODE *temp=(NODE*)malloc(sizeof(NODE)) ;
		temp= (NODE*)minValueNode(nroot->right);

        //Copy the inorder successor's content to this node
        strcpy(nroot->name,temp->name);

        //Delete the inorder successor
        nroot->right = nameDeleteNode(nroot->right,temp->name);
    }
    return nroot;
}

//Inserts a node in BST according to name
void nameInsert(NODE** nroot,char *name,char *sname,char *phnum)
{
	NODE *a;
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
}


void searchName(NODE *nroot,char *nm,int *flg)
{
	if(nroot==NULL) //base case  
     {
     	 return;
	 }
	
	char tmp[20];
	strcpy(tmp,(nroot->name));
	strlwr(tmp);
	
	if (strcmp(tmp,nm)==0)
	{
		printf("\n\tName: %s %s\tPhone Number: %s",nroot->name,nroot->sname,nroot->phnumber);
		*flg=1;
		searchName(nroot->right,nm,flg);
	}
    if (strcmp(tmp,nm)==-1)
    	searchName(nroot->right,nm,flg);
	else
    	searchName(nroot->left,nm,flg);
}

void searchNameSurnameN(NODE *nroot,char *nm,char *snm,int *nsflg)
{
    if (nroot==NULL)
    	return;
    
    char ttname[20],ttsname[20];
    strcpy(ttname,nroot->name); strlwr(ttname);
    strcpy(ttsname,nroot->sname); strlwr(ttsname);
	
	if(strcmp(ttname,nm)==0 && strcmp (ttsname,snm)==0)
    {
    	printf("\n\tName: %s %s\tPhone Number: %s",nroot->name,nroot->sname,nroot->phnumber);
    	*nsflg=1;
	}
    
    if (strcmp(ttname,nm)==-1)
        searchNameSurnameN(nroot->right, nm,snm,nsflg);

	 searchNameSurnameN(nroot->left, nm,snm,nsflg);
}

void suggestionsN(NODE *nroot,char *searchQuery)
{
    	if(nroot==NULL)
        	return;
        
		char tmp[20];
        strcpy(tmp,nroot->name);
        strlwr(tmp);
    
    	if(strncmp(tmp,searchQuery,strlen(searchQuery)-1)==0)
    		{
    			printf("\nResults closer to name entered: \n");
				printf("\tName: %s %s\t\tPhone Number: %s\n",(nroot->name),(nroot->sname),(nroot->phnumber));
    			suggestionsN(nroot->right,searchQuery);		
			}
		if(strncmp(tmp,searchQuery,strlen(searchQuery)-1)==-1)
			suggestionsN(nroot->right,searchQuery);
		else
			suggestionsN(nroot->left,searchQuery);
}


NODE* createNBST(NODE *nroot)
{
	nroot=NULL;
	char phnum[20];
    	char name[20];
    	char sname[20];
    	FILE *fp,*fpn;
	    fp=fopen("phonebook.txt","r");
    	while(1)  //Create BST from file phonebook.txt
			{		
				int flag;
				flag=fscanf(fp,"%s %s %s\n",name,sname,phnum);
       			if(flag==EOF)
	  				break;
        		nameInsert(&nroot,name,sname,phnum);
			}
		fclose(fp);
		return nroot;
}


void nameMenu(NODE* nroot)
{		
		NODE *searchedNode=NULL;
    	int opt;
    	int flag=0;
		char searchData[20],searchSdata[20];
    	char phnum[20];
    	char name[20];
    	char sname[20];
		while(1)
    	{
    	printf("\n________________________________________________________________________________________________________________________________");
        printf("\n\t\t\t\t\t\t\tPHONEBOOK\n");
        printf("\t\t\t\t\t\t\t``````````");
		printf("\n\t\t\t1.Display Phonebook.\n\t\t\t2.Search Using Name.\n\t\t\t3.Back\n\tYour Option: ");
        scanf("%d",&opt);
        if(opt==3)
            break;
        switch(opt)
        {
            case 1:
                	if(nroot==NULL)
                	{
                     		printf("\nPhonebook is empty.");
                     		break;
                	}
	                inorder(nroot);
	                break;
          
			case 2:
					printf("\nEnter name to be searched: ");
					scanf(" %s",searchData);
					char temp[20];
					strcpy(temp,searchData);
					strlwr(temp);
					searchName(nroot,temp,&flag);
					if(flag==0)
					{
						suggestionsN(nroot,temp);
						printf("\n %s not found. Do you want to add this name to phonebook?(Y/N) \n",searchData);
						char opt1;
						scanf(" %c",&opt1);
						if(opt1=='Y'||opt1=='y')
						{
							printf("Enter surname of contact: ");
							scanf(" %s",sname);
							printf("Enter phone number of contact: ");
							scanf(" %s",phnum);
							FILE *fp;
							fp=fopen("phonebook.txt","a");
							fprintf(fp,"%s %s %s\n",searchData,sname,phnum);
							nameInsert(&nroot,searchData,sname,phnum);
							fclose(fp);
						}
						break;
					}
					flag=0; 
					break;
			//case 4:
			//	nameEditContact(&nroot);
			//	break;
			
			default:
				printf("\tWrong option. Kindly input the correct option.\n");
    	}
	}
    return;
}
