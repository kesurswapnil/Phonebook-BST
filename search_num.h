
NODE* numDeleteNode(NODE *root, char *phnum)
{
    // base case
    if (root == NULL) return root;

	//If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if (strcmp(phnum,root->phnumber)==-1)
        root->left = numDeleteNode(root->left,phnum);

    // If the key to be deleted is greater than the root's key,then it lies in right subtree
    else if (strcmp(phnum,root->phnumber)==1)
        root->right = numDeleteNode(root->right,phnum);

    // if key is same as root's key, then This is the node to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            NODE *temp = root->right;
            
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            NODE *temp = root->left;
            
            free(root);
            return temp;
        }

        //Node with two children: Get the inorder successor (smallest in the right subtree)
        NODE *temp=(NODE*)malloc(sizeof(NODE)) ;
		temp= (NODE*)minValueNode(root->right);

        //Copy the inorder successor's content to this node
        strcpy(root->phnumber,temp->phnumber);

        //Delete the inorder successor
        root->right = numDeleteNode(root->right,temp->phnumber);
    }
    return root;
}

//Inserts the phone number in BST
void numInsert(NODE** root,char *name,char *sname,char *phnum)
{
	NODE *a;
    if(*root==NULL)
    {
	    a=createNode(name,sname,phnum);
        *root=a;
        return;
    }
    else
    {
    	if(strcmp((phnum),((*root)->phnumber))==-1)
    		numInsert(&((*root)->left),name,sname,phnum);
    	else
    		numInsert(&((*root)->right),name,sname,phnum);
	}
}
NODE *searchNumber(NODE *root,char *phnum)
{
    if (root==NULL || strcmp(root->phnumber,phnum)==0)
       return root;
    
    if (strcmp(root->phnumber,phnum)==-1)
       return searchNumber(root->right, phnum);
    
    return searchNumber(root->left, phnum);
}



void numEditContact(NODE **root,NODE **sroot,NODE **nroot)
	{
		FILE *fp;
		int flag;
		fp=fopen("phonebook.txt","r");
		char fname[20],fsname[20],name[20],sname[20],fnum[20],num[20],newnum[20];
		printf("\nEnter phone number whose details are to be edited: ");
		scanf(" %s",num);
		while(1)
		{
		flag=fscanf(fp,"%s %s %s\n",fname,fsname,fnum);
		if(flag==EOF)
		{	
			printf("\nNumber not found.");
			fclose(fp);
			break;
		}
		if(strcmp(fnum,num)==0)
		{   
			fclose(fp);
			printf("\nEnter new name of contact: ");
			scanf(" %s",name);
			printf("\nEnter new surname of contact: ");
			scanf(" %s",sname);
			printf("\nEnter new number of contact: ");
			scanf(" %s",newnum);
			NODE *k=searchNumber(*root,newnum);
				if(k!=NULL)
				{
					printf("Contact with same phone number already exists!");
					printf("\n\tName: %s %s\tPhone number: %s",k->name,k->sname,k->phnumber);
					return;
				}
			
			*root=numDeleteNode(*root,fnum);
			*nroot=nameDeleteNode(*nroot,fname);
			*sroot=surnameDeleteNode(*sroot,fsname);
			
			numInsert(root,name,sname,newnum);
			nameInsert(nroot,name,sname,newnum);
			surnameInsert(sroot,name,sname,newnum);
			
			fp=fopen("phonebook.txt","w");
			treeToFile(*root,fp);
			fclose(fp);
			break;
		} 
		
	}
	return;
}
void suggestions(NODE *root,char *searchnQuery)
{
	NODE *a=root;
    	if(a==NULL)
        	return;
    	
    	if(strncmp(a->phnumber,searchnQuery,strlen(searchnQuery))==0)
    		{
    			printf("\nDid you mean:");
				printf("\n\tName: %s %s\t\tPhone Number: %s\n",(a->name),(a->sname),(a->phnumber));
				suggestions(a->right,searchnQuery);
    		}
    	if(strncmp(a->phnumber,searchnQuery,strlen(searchnQuery))==-1)
			suggestions(a->right,searchnQuery);
		else
			suggestions(a->left,searchnQuery);
}

//void addContact(NODE **root,char *name,char *sname,char *phnum)

NODE* createNumBST(NODE *root)
{
	root=NULL;
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
        		numInsert(&root,name,sname,phnum);
			}
		fclose(fp);
		return root;
}

void numDeleteContact(NODE **root,NODE **sroot,NODE **nroot)
{
	char phnum[20],name[20],sname[20],opt;
	printf("\nEnter phone number to be deleted: ");
	scanf(" %s",phnum);
	NODE *a=searchNumber(*root,phnum);
	if(a==NULL)
	{
		printf("\n %s not found.",phnum);
		suggestions(*root,phnum);
		return;
	}
	else
	{
		strcpy(name,a->name); strcpy(sname,a->sname);
		printf("\nName: %s %s\tPhone Number: %s",a->name,a->sname,a->phnumber);
		printf("\nAre you sure you want to delete this contact (Y/N): \n");
		scanf(" %c",&opt);
		if(opt=='y' || opt=='Y')
		{
			FILE *fpr=fopen("rphonebook.txt","a");
			fprintf(fpr,"%s %s %s\n",a->name,a->sname,a->phnumber);
			fclose(fpr);
			*root=numDeleteNode(*root,phnum);
			*sroot=surnameDeleteNode(*sroot,sname);
			*nroot=nameDeleteNode(*nroot,name);
			FILE *fp;
			fp=fopen("phonebook.txt","w");
			treeToFile(*nroot,fp);
			fclose(fp);
		}
		return;
	}
	
}

void numMenu(NODE *root,NODE *sroot,NODE *nroot)
{		
		NODE *searchedNode=NULL;
    	//NODE *root=NULL;
    	int opt;
		char searchData[20];
    	char phnum[20];
    	char name[20];
    	char sname[20];
    	while(1)
    	{
    	printf("\n________________________________________________________________________________________________________________________________");
        printf("\n\t\t\t\t\t\t\tPHONEBOOK\n");
        printf("\t\t\t\t\t\t\t``````````");
		printf("\n\t\t\t1.Display Phonebook.\n\t\t\t2.Search Using Phone Number.\n\t\t\t3.Edit Contact.\n\t\t\t4.Delete Contact.\n\t\t\t5.Back\n\tYour Option: ");
        scanf("%d",&opt);
        if(opt==5)
            break;
        switch(opt)
        {
            case 1:
                	if(root==NULL)
                	{
                     		printf("\nPhonebook is empty.");
                     		break;
                	}
	                inorder(root);
	                break;
          
			case 2:
					printf("\nEnter phone number to be serched: ");
					scanf(" %s",searchData);
					//searchNum(root,searchData);
					searchedNode=searchNumber(root,searchData);
					
					if(searchedNode==NULL)
					{
						suggestions(root,searchData);
						printf("\n%s not found. Do you want to add this number to phonebook?(Y/N) \n",searchData);
						char opt1;
						scanf(" %c",&opt1);
						if(opt1=='Y'||opt1=='y')
						{
							printf("Enter name of contact: ");
							scanf(" %s",name);
							printf("Enter surname of contact: ");
							scanf(" %s",sname);
							FILE *fp;
							fp=fopen("phonebook.txt","a");
							fprintf(fp,"%s %s %s\n",name,sname,searchData);
							numInsert(&root,name,sname,searchData);
							fclose(fp);
						}
						break;
					}
					printf("\n\tName: %s %s\t\tNumber: %s\n",searchedNode->name,searchedNode->sname,searchedNode->phnumber);
					break;
			case 3:
				numEditContact(&root,&sroot,&nroot);
				break;
				
			case 4:
				numDeleteContact(&root,&sroot,&nroot);
				break;
			
			default:
				printf("\tWrong option. Kindly input the correct option.\n");
    	}
	}
    return;
}
