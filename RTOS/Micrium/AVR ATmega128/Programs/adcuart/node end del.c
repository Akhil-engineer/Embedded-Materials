#include<stdio.h>
#include<stdlib.h>
struct node
{
	int no;
	struct node *next;
}*head=NULL,*temp,*last,*p,*ins;

void create()
{
	if(head==NULL)
	{
		head=(struct node*)malloc(sizeof(struct node));
		printf("Enter head no:");
		scanf("%d",&head->no);
		head->next=NULL;
		last=head;
	}
	else
	{
		temp=(struct node*)malloc(sizeof(struct node));
		printf("\nEnter last no:");
		scanf("%d",&temp->no);
		
		last->next=temp;
		temp->next=NULL;
		last=temp;
	}
}
	void insert()
	{
		int i,pos;
		printf("\nEnter the position:");
		scanf("%d",&pos);
		
		ins=(struct node*)malloc(sizeof(struct node));
		printf("\nEnter inserting no:");
		scanf("%d",&ins->no);
		
		if(pos==1)
		{
			ins->next=head;
			head=ins;
		}
		else
		{ 
		   temp=head;
		   for(i=1;i<pos-1;i++)
		   {
		   	temp=temp->next;
		   }
		   if(temp->next==NULL)
		   {
		   	last->next=ins;
		   	ins->next=NULL;
		   	last=ins;
		   }
		   else
		   {
		   	temp=head;
		    for(i=1;i<pos-1;i++)
		    {
			temp=temp->next;
		    }
		    ins->next=temp->next;
		    temp->next=ins;
		   }
		}
	}
	void deletion()
	{
		for(p=head;p->next->next!=NULL;p=p->next);
		
			p->next=NULL;
			last=p;
			
	}
	void display()
	{
		for(p=head;p!=NULL;p=p->next)
		{
			printf("\n%d",p->no);
		}
	}
 
 void main()
 {
 	int x,n;
 	while(1)
 	{
 		printf("\nEnter the choice \n1.Create\n2.Display\n3.Insert\n4.Delete\n");
 		scanf("%d",&n);
 		switch(n)
 		{
 			case 1: create();
 			        break;
 			case 2: display();
			        break;
			case 3: insert();
			        break;
		    case 4: deletion();
			        break;
	    }
	  printf("\nPress 1 to continue\n");
	  scanf("%d",&x);
		if(x!=1)
		{
			break;
		}					       
	 }
}
