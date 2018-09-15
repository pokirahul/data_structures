#include<stdio.h>
#include<stdlib.h>

struct node  	//node for tree
{
	int data;
	struct node* left;
	struct node* right;
};

struct queueNode	//node for queue
{
	struct node* ptr;		// instead of data, pointer to tree node
	struct queueNode* next;
};

struct node* newNode(int item)	//for adding node to tree
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->data = item;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
};

void inorder(struct node* root)
{
	if(root == NULL)
		return;

	inorder(root->left);
	printf("%d ",root->data);
	inorder(root->right);
}

int isQueueEmpty(struct queueNode* front)
{
	return (front == NULL);
}

struct node* deQueue(struct queueNode** front_ref)
{
	if(isQueueEmpty(*front_ref))
	{
		printf("ERROR: Queue is empty\n");
		return NULL;
	}
	else
	{
		struct node* temp = (struct node*)malloc(sizeof(struct node));
		temp = (*front_ref)->ptr;
		(*front_ref) = (*front_ref)->next;
		return temp;
	}
}

void enQueue(struct queueNode** front_ref,struct queueNode** rear_ref, struct node* aNode)
{
	struct queueNode* temp = (struct queueNode*)malloc(sizeof(struct queueNode));
	temp->ptr = aNode;
	temp->next = NULL;

	if(isQueueEmpty(*front_ref))
	{
		*front_ref = temp;
		*rear_ref = *front_ref;
		return;
	}
	else
	{
		(*rear_ref)->next = temp;
		(*rear_ref) = (*rear_ref)->next;
		return;
	}
}

void insertion(struct node** root_ref,int item)
{
	struct queueNode* front = (struct queueNode*)malloc(sizeof(struct queueNode));
	struct queueNode* rear = (struct queueNode*)malloc(sizeof(struct queueNode));
	rear = front = NULL;

	enQueue(&front,&rear,*root_ref);

	while(front != NULL)
	{
		struct node* temp = deQueue(&front);
		
		if(temp->left == NULL)
		{
			temp->left = newNode(item);
			return;
		}
		else if(temp->right == NULL)
		{
			temp->right = newNode(item);
			return;
		}

		enQueue(&front,&rear,temp->left);
		enQueue(&front,&rear,temp->right);
	}
}

int main()
{
	struct node* root = newNode(10);

	root->left = newNode(11);
	root->right = newNode(9);

	root->left->left = newNode(7);
	//root->left->right = newNode();
	root->right->left = newNode(15);
	root->right->right = newNode(8);

	//tree created

	printf("before insertion inorder\n");
	inorder(root);

	insertion(&root,12);

	printf("after insertion inorder\n");
	inorder(root);
}
