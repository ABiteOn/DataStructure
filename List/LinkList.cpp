#include <cstdlib>
#include <cstdio>
#include <iostream> 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define NULLPOINTER -3
#define INDEXOUTOFBOUNDS -4
using namespace std;
typedef double ElemType;
typedef int Status;
typedef struct LNode{
    ElemType data;//头结点中的data存储当前链表的长度 
    struct LNode *next;
}LNode, *LinkList;
Status CreateList_L(LinkList &L){
	//初识化一个带头结点的单链表
	L = (LinkList)malloc(sizeof(LNode));
	if(!L){
		return OVERFLOW;
	} 
	L->data = 0; 
	L->next = NULL;
	return OK;
}
int ListLength(LinkList &L){
	if(!L){
		return ERROR;
	}
	return L->data;
}
Status ListInsert_L(LinkList &L,int i,ElemType e){
    //在带头结点的单链表L的第i个元素之前插入e
    if(!L){
    	return NULLPOINTER;
	}
	if(i<1||i>ListLength(L)+1) {
		return INDEXOUTOFBOUNDS;
	}
    LinkList p = L;
    int j = 0;
    while(p && j<i-1){
        p = p->next;
        j++;
    } //p指向第i-1个节点，j=i-1 
    /*if(!p||j>i-1){
        return ERROR; 
    } */
    LinkList s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    L->data++;
    return OK;
}
Status ListDelete_L(LinkList &L,int i,ElemType &e){
    //删除第i个元素
    if(!L){
    	return NULLPOINTER;
	}
	if(i<1||i>ListLength(L)) {
		return INDEXOUTOFBOUNDS;
	}
    LinkList p = L,q;
    int j = 0;
    while(p->next && j<i-1){
        p = p->next;
        j++;
    }//p指向第i-1个结点，j=i-1
    /*if(!(p->next)//链表长度<i
    || j>i-1)//i<=0
        return ERROR;*/
    q = p->next;
    e = q->data;
    printf("%.2f %.2f\n",p->data,q->data); 
    p->next = q->next;
    free(q);
    L->data--;
    return OK; 
}
void visit(LinkList p){
    printf("%.2f\n",p->data);
}
Status ListTraverse(LinkList L){
	if(!L){
    	return NULLPOINTER;
	}
    if(!(L->next)){
    	return ERROR;
	}
    LinkList p = L->next;
    while(p->next){
        visit(p);
        p = p->next;
    }
    visit(p);
    return OK;
}


/*
*	test code
*/
void showMenu(){
	cout<<"--------------------------"<<endl;
	cout<<"|          Menu          |"<<endl;
	cout<<"--------------------------"<<endl;
	cout<<"|[1]Init a LinkList      |"<<endl;
	cout<<"|[2]Insert a element     |"<<endl;
	cout<<"|[3]Delete a element     |"<<endl;
	cout<<"|[4]Show length          |"<<endl;
	cout<<"|[5]Show all elements    |"<<endl;
	cout<<"|[6]Show menu            |"<<endl;
	cout<<"|[7]Exit                 |"<<endl;
	cout<<"--------------------------"<<endl;
}
int init(LinkList &L){
	Status s=CreateList_L(L);
	if(s!=OK){
		cout<<"> Init failed."<<endl;
	}else{
		cout<<"> Init succeeded."<<endl;
	}
	return 0;
}
int insert(LinkList &L){
	int s,pos;
	ElemType elem;
	cout<<"> Please input the position to insert into."<<endl;
	cin>>pos;
	cout<<"> Please input the element to insert."<<endl;
	cin>>elem;
	s=ListInsert_L(L,pos,elem);
	if(s==NULLPOINTER){
		cout<<"> Failed! Please initialize the LinkList first."<<endl;
		return 0;
	}
	if(s==INDEXOUTOFBOUNDS) {
		cout<<"> Failed! The position should range from 1 to "<<(L->data+1)<<"."<<endl;
		return 0;
	}
	cout<<"> Succeeded!"<<endl;
	return 0;
}
int del(LinkList &L){
	int s,pos;
	ElemType elem;
	cout<<"> Please input the position to delete."<<endl;
	cin>>pos;
	s=ListDelete_L(L,pos,elem);
	if(s==NULLPOINTER){
		cout<<"> Failed! Please initialize the LinkList first."<<endl;
		return 0;
	}
	if(s==INDEXOUTOFBOUNDS) {
		cout<<"> Failed! The position should range from 1 to "<<(L->data)<<"."<<endl;
		return 0;
	}
	cout<<"> Succeeded! /'"<<elem<<"/' has been deleted."<<endl;
	return 0;
}
int length(LinkList &L){
	if(!L){
		cout<<"> Failed! Please initialize the LinkList first."<<endl;
	}
	cout<<"> The length of this LinkList is "<<(L->data)<<endl;
	return 0;
}
int traverse(LinkList &L){
	Status s;
	s = ListTraverse(L);
	if(s==NULLPOINTER) {
		cout<<"> Failed! Please initialize the LinkList first."<<endl;
	}
	if(s==ERROR){
		cout<<"> Failed! The LinkList is empty."<<endl;
	}
	cout<<"> Succeeded!"<<endl;
	return 0;
}
void test(){
	cout<<"> This program implement a link list."<<endl;
	cout<<"> The element type is initialized as \"double\"."<<endl;
	LinkList L;
	showMenu();
	char key;
	int exit=0;
	while(1){
		cin>>key;
		switch(key){
			case '1':
				cout<<"--------------------------"<<endl;
				init(L);
				cout<<"--------------------------"<<endl;
				break;
			case '2':
				cout<<"--------------------------"<<endl;
				insert(L);
				cout<<"--------------------------"<<endl;
				break;
			case '3':
				cout<<"--------------------------"<<endl;
				del(L);
				cout<<"--------------------------"<<endl;
				break;
			case '4':
				cout<<"--------------------------"<<endl;
				length(L);
				cout<<"--------------------------"<<endl;
				break;
			case '5':
				cout<<"--------------------------"<<endl;
				traverse(L);
				cout<<"--------------------------"<<endl;
				break;
			case '6':
				showMenu();
				break;
			case '7':
				cout<<"--------------------------"<<endl;
				cout<<"> Please press '6' again to confirm exit."<<endl;
				cin>>key;
				if(key=='7'){
					cout<<">Thank you for using."<<endl;
					exit=1;
				}
				else{
					cout<<"> You have cancelled the exit operation."<<endl;
				}
				cout<<"--------------------------"<<endl;
				break;
			default:
				cout<<"> If you want to exit, please press '6'."<<endl;
				cout<<"> If you want to see the menu, please press '5'."<<endl;
		}
		if(exit)
			break;
	}
	
} 
int main(){
    int cnt=0;
    test();
    system("PAUSE");
    return EXIT_SUCCESS;   
}
