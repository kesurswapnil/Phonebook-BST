
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"utilityFunctions.h"
#include"search_name.h"
#include"search_surname.h"
#include"search_num.h"
#include"recycleBin.h"
#include"common.h"

int main()
{
	NODE *root=NULL,*nroot=NULL,*sroot=NULL,*broot=NULL;
	int opt,nsflag=0;
	root=createNumBST(root);
	nroot=createNBST(nroot);
	sroot=createSBST(sroot);
	broot=createBinBST(broot);
	while(1)
    	{
    	printf("\n________________________________________________________________________________________________________________________________");
        printf("\n\t\t\t\t\t\t\tPHONEBOOK MAIN MENU\n");
        printf("\t\t\t\t\t\t       `````````````````````");
        printf("\n\t\t\t1.Explore Phonebook Using Name.\n\t\t\t2.Explore Phonebook Using Phone Number.\n\t\t\t3.Explore Recycle Bin.\n\t\t\t4.Exit Application.\n");
        printf("\tYour option: ");
        scanf("%d",&opt);
        if(opt==4)
        	break;
        switch(opt)
        {
			case 1:
        	while(1)
    		{
    		opt=0;
    		printf("\n________________________________________________________________________________________________________________________________");
        	printf("\n\t\t\t\t\t\t\tPHONEBOOK\n");
        	printf("\t\t\t\t\t\t\t``````````");
        	printf("\n\t\t\t1.Explore Using Name.\n\t\t\t2.Explore Using Surname.\n\t\t\t3.Search Using Full Name.\n\t\t\t4.Delete Contact.(Case-Sensitive)\n\t\t\t5.Add Contact.\n\t\t\t6.Edit Contact (Case-Sensitive)\n\t\t\t7.Back\n\tYour option: ");
			int opt1,nsflag=0;
			scanf("%d",&opt1);
			if(opt1==7)
				break;
			switch(opt1)
			{
			case 1:
					//deleteTree(nroot);//deleteTree(sroot);deleteTree(root);
					//nroot=createNBST(nroot);
					nameMenu(nroot);
					break;
			case 2:

				//deleteTree(sroot);
				//sroot=createSBST(sroot);
				surnameMenu(sroot);
				break;
			case 3:
				//deleteTree(nroot);deleteTree(sroot);
				//nroot=createNBST(nroot);sroot=createSBST(sroot);
				if(1);
				char name[20],sname[20],phnum[20];
				printf("\nEnter name of contact: ");
				scanf(" %s",name);
				printf("\nEnter surname of contact: ");
				scanf(" %s",sname);
				char tname[20],tsname[20];
				strcpy(tname,name); strlwr(tname);
				strcpy(tsname,sname); strlwr(tsname);
				
				searchNameSurnameN(nroot,tname,tsname,&nsflag);
				if(nsflag==0)
				{
					int temp;
					printf("\n%s %s not found.");
					//printf("\nDid you mean: \n");
					//searchName(nroot,tname,&temp);
					{
						
						if(temp==0)
							{
							printf("\nResults closer to %s : ",name);
							suggestionsN(nroot,tname);
							}
					}
					temp=0;
					//searchSurname(nroot,tsname,&temp);
					{
						if(temp==0)
							{
							printf("\nResults closer to %s :",sname);
							suggestionsS(sroot,tsname);
							}
					}
				
				}
				nsflag=0;
					//printf("\nName: %s %s\tPhone Number: %s\n",l->name,l->sname,l->phnumber);
				break;
			
				case 4:
					DeleteContact(&root,&nroot,&sroot,&broot);
					break;
				
				case 5:
					AddContact(&root,&nroot,&sroot);
					break;
				
				case 6:
					EditContact(&root,&nroot,&sroot);
					break;
					
				
			default:
				printf("\nWrong option entered. Please try again.");
			}
		
		}
		break;
	
        case 2:
        
        	//deleteTree(root);
        	//root=createNumBST(root);
        	numMenu(root,sroot,nroot);
        	break;
        	
        case 3:
        	while(1)
        	{
        	int opt2;	
        	printf("\n________________________________________________________________________________________________________________________________");
        	printf("\n\t\t\t\t\t\t\tPHONEBOOK - Recycle Bin\n");
        	printf("\t\t\t\t\t\t\t```````````````````````");
        	printf("\n\t\t\t1.Display Recycle Bin.\n\t\t\t2.Restore Recycle Bin.\n\t\t\t3.Empty Recycle Bin.\n\t\t\t4.Back\n\tYour Option: ");
			scanf("%d",&opt2);
			if(opt2==4)
				break;
			switch(opt2)
        	{
        	case 1:
				//broot=createBinBST(broot);
        		displayBin();
        		break;
        	case 2:
        		deleteTree(broot); 
				broot=createBinBST(broot);
				restoreBin(broot,root,nroot,sroot);
				break;        	
        	case 3:
        		if(broot==NULL)
        		{
        			printf("\nRecyle bin is empty!\n");
        			break;
				}
				else
        		{
					deleteTree(broot);
        			FILE *fp=fopen("rphonebook.txt","w");
        			fclose(fp);
        		break;
    			}
    		default: 
    			printf("\nWrong option entered. Please enter again.");
    		}
    	}
		default:
			printf("\nWrong option entered. Please enter again.");
		}
	
	}
return 0;
}
