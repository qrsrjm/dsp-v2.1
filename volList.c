#include "volList.h"


Clinklist* create_list()
{	
    Clinklist *head = (Clinklist*)malloc(sizeof(Clinklist));	
    if(head != NULL)	{		
        head->next = head;      
        return head;    
    }   
    return NULL;
}

bool insert_list(Clinklist *head, elemType data)
{
	Clinklist *new = (Clinklist*)malloc(sizeof(Clinklist));
	if(new == NULL) return false;
	new->data = data;
	new->next = new;

	Clinklist *p = head;
	while(p->next != head)
	{
		p = p->next;
	}

	new->next = p->next;
	p->next = new;
	return true;
}


Clinklist* delete_list(Clinklist *head, elemType data)
{
	Clinklist *p = head;
	while(p->data != data && p->next != NULL)
	{
		p = p->next;
	}

	if(p->next == NULL && p->data != data) return head;

	Clinklist *q = head;
	while(q->next != p)
	{
		q = q->next;
	}

	q->next = p->next;
	free(p);
	return head;
}

void show_list(Clinklist *head)
{
	head = head->next;
	Clinklist *p = head;
	while(p->next != head)	
	{
		printf("%d\t", p->data);
		p = p->next;
	}
//	printf("%d\t", p->data);
	printf("\n");

	p=p->next;
	while(p->next != head)	
	{
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");

}

int get_random(int mode)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	srandom(now.tv_usec);
	return random()%mode;
}






