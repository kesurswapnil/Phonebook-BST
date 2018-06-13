
NODE* surnameDeleteNode(NODE *sroot, char *sname)
{
    // base case
    if (sroot == NULL) 
		return sroot;

	//If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if (strcmp(sname,sroot->sname)==-1)
        sroot->left = surnameDeleteNode(sroot->left,sname);

    // If the key to be deleted is greater than the root's key,then it lies in right subtree
    else if (strcmp(sname,sroot->sname)==1)
        sroot->right = surnameDeleteNode(sroot->right,sname);

    // if key is same as root's key, then This is the node to be deleted
    else
    {
        // node with only one child or no child
        if (sroot->left == NULL)
        {
            NODE *temp = sroot->right;
            
            free(sroot);
            return temp;
        }
        else if (sroot->right == NULL)
        {
            NODE *temp = sroot->left;
            
            free(sroot);
            return temp;
        }

        //Node with two children: Get the inorder successor (smallest in the right subtree)
        NODE *temp=(NODE*)malloc(sizeof(NODE)) ;
		temp= (NODE*)minValueNode(sroot->right);

        //Copy the inorder successor's content to this node
        strcpy(sroot->sname,temp->sname);

        //Delete the inorder successor
        sroot->right = surnameDeleteNode(sroot->right,temp->sname);
    }
    return sroot;
}

//Inserts the node in BST sorted by surname
void surnameInsert(NODE** sroot,char *name,char *sname,char *phnum)
{
	NODE *a;
    if(*sroot==NULL)
    {
	    a=createNode(name,sname,phnum);
        *sroot=a;
        return;
    }
    else
    {
    	if(strcmp((sname),((*sroot)->sname))==-1)
    		surnameInsert(&((*sroot)->left),name,sname,phnum);
    	else
    		surnameInsert(&((*sroot)->right),name,sname,phnum);
	}
}






void searchSurname(NODE *sroot,char *temp,int *flg)
{
    if (sroot==NULL)
       return;
       
    char tsname[20];
    strcpy(tsname,sroot->sname); strlwr(tsname);
    if(strcmp(tsname,temp)==0)
    {
    	printf("\n\tName: %s %s\tPhone Number: %s",sroot->name,sroot->sname,sroot->phnumber);
		*flg=1;
		searchSurname(sroot->right,temp,flg);
	}
    if (strcmp(tsname,temp)==-1)
        searchSurname(sroot->right,temp,flg);
	else
     	searchSurname(sroot->left,temp,flg);
}

void suggestionsS(NODE *sroot,char *searchsQuery)
{
	
    	if(sroot==NULL)
        	return;
    	
    	char tsname[20];
    	strcpy(tsname,sroot->sname); strlwr(tsname);
    	
    	if(strncmp(tsname,searchsQuery,strlen(searchsQuery)-1)==0)
    		{
    			printf("\nResults closer to surname entered: \n");
				printf("\tName: %s %s\t\tPhone Number: %s\n",(sroot->name),(sroot->sname),(sroot->phnumber));
    			suggestionsS(sroot->right,searchsQuery);
			}
		if(strncmp(tsname,searchsQuery,strlen(searchsQuery)-1)==-1)
			suggestionsS(sroot->right,searchsQuery);
		else
			suggestionsS(sroot->left,searchsQuery);
}


NODE* createSBST(NODE *sroot)
{
	sroot=NULL;
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
        		surnameInsert(&sroot,name,sname,phnum);
			}
		fclose(fp);
		return sroot;
}



void surnameMenu(NODE *sroot)
{		
		NODE *searchedNode=NULL;
    	int opt;int sflag=0;
		char searchData[20],searchSdata[20];
    	char phnum[20];
    	char name[20];
    	char sname[20];
		while(1)
    	{
    	printf("\n________________________________________________________________________________________________________________________________");
        printf("\n\t\t\t\t\t\t\tPHONEBOOK\n");
        printf("\t\t\t\t\t\t\t``````````");
		printf("\n\t\t\t1.Display Phonebook.\n\t\t\t2.Search Using Surname.\n\t\t\t3.Back.\n\tYour Option: ");
        scanf("%d",&opt);
        if(opt==3)
            break;
        switch(opt)
        {
            case 1:
                	if(sroot==NULL)
                	{
                     		printf("\nPhonebook is empty.");
                     		break;
                	}
	                inorder(sroot);
	                break;
          	
			case 2:
					printf("\nEnter surname to be serched: ");
					scanf(" %s",searchData);
					char tsname[20];
					strcpy(tsname,searchData); strlwr(tsname);
					searchSurname(sroot,tsname,&sflag);
					
					if(sflag==0)
					{
						suggestionsS(sroot,tsname);
						printf("\n%s not found. Do you want to add this surname to phonebook?(Y/N) \n",searchData);
						char opt1;
						scanf(" %c",&opt1);
						if(opt1=='Y'||opt1=='y')
						{
							printf("Enter name of contact: ");
							scanf(" %s",name);
							printf("Enter phone number of contact: ");
							scanf(" %s",phnum);
							FILE *fp;
							fp=fopen("phonebook.txt","a");
							fprintf(fp,"%s %s %s\n",name,searchData,phnum);
							surnameInsert(&sroot,name,searchData,phnum);
							fclose(fp);
						}
						break;
					}
				
					break;
			//case 4:
			//	surnameEditContact(&sroot);
			//	break;
			
			default:
				printf("\tWrong option. Kindly input the correct option.\n");
    	}
	}
    return;
}
