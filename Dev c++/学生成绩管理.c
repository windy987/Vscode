#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct student{
	char name[10];
	char id[20];
	double scores;
	struct student *next;
}student; //姓名，学号，分数 

student* createnode() {//创建链表节点 
    student *newnode = (student*)malloc(sizeof(student));
    if (newnode == NULL) {
        printf("节点内存空间分配失败！\n"); 
    }
    newnode->next=NULL;
    return newnode;
}

void addstudent(student **head){
	student *node=createnode();	
	
	printf("请输入姓名:");
	scanf("%s",node->name);//输入姓名 
	while(getchar()!='\n');//清除缓冲区残留字符
	printf("请输入学号:"); 
	scanf("%s",node->id);//输入学号 
	while(getchar()!='\n');
	printf("请输入成绩:");
	scanf("%lf",&node->scores);//输入成绩 
	printf("\n");
	while(getchar()!='\n');
	//链接链表 
	if(*head==NULL){
		*head=node;	
	}
	else{
		student *cur=*head;
		while(cur->next!=NULL){
			cur=cur->next;
		}
		cur->next=node;
	}
	printf("成功添加信息\n\n");
}

void list(student *head){
	student *cur=head;
	printf("学生信息\n");
	while(cur!=NULL){
		printf("学生姓名:%s  学号:%s  成绩:%.2lf\n",cur->name,cur->id,cur->scores);
		cur=cur->next;
	}	
	printf("\n");
}

void freelist(student *head){
	student *p;
	while(p!=NULL){
		p=head;
		head=head->next;
		free(p);
	}
}

//修改学生信息 
void change(student *head, char a[])
{
	student *cur = head;
	while (cur!=NULL)
	{
		if (strcmp(cur->name,a) == 0)
		{
			printf("成功找到该学生\n");
			printf("请重新录入信息\n");
			printf("请输入姓名:");
			scanf("%s",cur->name);//输入姓名 
			while(getchar()!='\n');//清除缓冲区残留字符
			printf("请输入学号:"); 
			scanf("%s",cur->id);//输入学号 
			while(getchar()!='\n');
			printf("请输入成绩:");
			scanf("%lf",&cur->scores);//输入成绩 
			printf("成功修改信息\n\n");
			break;
		}
		cur=cur->next;
	}
	if (cur == NULL)
		printf("未找到该学生\n\n");
}

//删除学生信息
void delete(student **head, char a[]) 
{
	student *cur = *head;
	student *prev = cur;
	while (cur!=NULL)
	{
		if(strcmp(cur->name,a) == 0)
		{
			if (cur == *head) //特殊处理头节点 
			{
				*head = cur->next;
				free(cur);
				printf("成功找到该学生并已删除其信息\n\n");
				break;
			}
			else
			{
				prev->next = cur->next;
				free(cur);
				printf("成功找到该学生并已删除其信息\n\n");
				break;
			}
		}
		prev = cur;
		cur = cur->next;
	}
	if (cur == NULL)
		printf("未找到该学生\n\n");
}

int main(){
	student *head=NULL;
	int a; 
	while(1){
		printf("添加学生信息，输入1\n");
		printf("修改学生信息，输入2\n");
		printf("删除学生信息，输入3\n");
	    printf("显示所有学生信息，输入4\n");
	    printf("退出，输5\n\n");
	    scanf("%d", &a);
		    switch(a){
		    	case 1:
		    		addstudent(&head);
		    		break;
		    	case 2:
		    		printf("请输入要修改信息的学生的姓名\n");
		    		char name[20];
		    		scanf("%s",name);
		    		while(getchar()!='\n');
		    		change(head,name);
		    		break;
		    	case 3:
		    		printf("请输入要删除信息的学生的姓名\n");
		    		scanf("%s",name);
		    		while(getchar()!='\n');
		    		delete(&head,name);
		    		break;
		    	case 4:
		    		if(head==NULL){
		    			printf("无学生信息\n");
					}
					else{
						list(head);
					}
					break;
		    	case 5:
		    		freelist(head);
		    		printf("程序已退出\n");
		    		return 0;
			}
		}
	return 0;	
}
	

