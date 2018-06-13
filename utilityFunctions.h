typedef struct node
{
    	struct node *left;
    	char name[20];
    	char sname[20];
    	char phnumber[20];
    	struct node *right;
}NODE;


NODE * minValueNode(NODE *node)
{
    NODE *current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

//Dynamically allocates new memory for contact.
NODE *createNode(char *name,char *sname, char *phnum)
{
        NODE *a=(NODE *)malloc(sizeof(NODE));
        strcpy(a->phnumber,phnum);
        strcpy(a->name,name);
        strcpy(a->sname,sname);
		a->left=a->right=NULL;
        return a;
}

void inorder(NODE *root)
{
    	NODE *a=root;
    	if(a==NULL)
        	return;
    	inorder(a->left);
    	printf("\n\tName: %s %s\t\tPhone Number: %s",(a->name),(a->sname),(a->phnumber));
    	inorder(a->right);
}

void treeToFile(NODE* root,FILE *fpn) //Writes the tree to file.
{
		NODE *a=root;
    	if(a==NULL)
        	return;
    	treeToFile(a->left,fpn);
    	fprintf(fpn,"%s %s %s\n",(a->name),(a->sname),(a->phnumber));
    	treeToFile(a->right,fpn);
}


void deleteTree(NODE* root) 
{
    if (root == NULL) 
		return;
 
    /* first delete both subtrees */
    deleteTree(root->left);
    deleteTree(root->right);
   
    /* then delete the node */
    //printf("\n Deleting node: %d", node->data);
    free(root);
} 


 
