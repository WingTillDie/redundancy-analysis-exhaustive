#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdint>
#include "subsequence.hh"
#define debug

/*
void mem_print(int rdim, int cdim; bool mem[rdim][cdim], int rdim, int cdim){
	for(int i=0; i<rdim; i++){
		for(int j=0; j<cdim; j++)
			printf("%d ", mem[i][j]);
		printf("\n");
	}
}
void mem_init(int rdim, int cdim; bool mem[rdim][cdim], int rdim, int cdim){
	for(int i=0; i<rdim; i++){
		for(int j=0; j<cdim; j++)
			mem[i][j]=0;
	}
}
*/

/*
void giveup_test(int rdim, int cdim){//Give up lowest numbers but harder to create r and c of point
	int r=(RAND_MAX+1U)%(rdim*cdim);
	if(random()<r)
		printf("%d ", 1);//giveup
	else
		printf("%d ", 0);
}
*/

struct Point{
	int r;
	int c;
	Point(){};
	Point(int rIn, int cIn) : r(rIn), c(cIn){
	}
	int operator==(Point p){
		if(r==p.r && c==p.c)
			return 1;
		else
			return 0;
	}
	int operator>(Point p){//Just sort by r
		return r>p.r;
	}
};

ostream& operator<<(ostream& os, Point p){
	cout << '(' << p.r << ',' << p.c << ")";
	return os;
}

template <typename T>
struct List{
	T data;//What is default value
	struct List *next=NULL;
};

struct cList{//Column list
	int c=-1;
	struct cList *next=NULL;
};

	struct cStack;
struct rList{//Row list///TODO Need c size?
	int r=-1;
	struct rList *next=NULL;
	cStack *child=NULL;
};

//Templatelize? data as struct? Only insertion is somewaht different?
//Check data type to determine action? Inheritance with override?
//Just overloading with single and 2 parameters?
/*
struct Tree_old{//More like stack for cList
	rList *head=NULL;
	int size=0;
	//Print tree, insert, free
	~Tree_old(){//TODO implement free c
		clear();
	}
	void clear(){//TODO implement free c
		rList *current=head;
		for(int i=0; i<size; i++){
			rList *next=current->next;
			delete current;
			current=next;
		}
		head=NULL;
		size=0;
	}
	int insert(Point p){//Return if there's duplication then higher function call again
		int r=p.r;
		int c=p.c;//Related features not implemented
		if(head==NULL){
			head=new rList;//Lack destructor
			head->r=r;
			//Lack c
			size++;
			return 0;//Success
		}else{//TODO: Duplication is determined by both r and c//Insert c datas
			rList *previous=NULL;
			rList *current=head;
			while(current && (r > current->r)){
				//Check if next is NULL
				previous=current;
				current=current->next;
			}
			if(!current){//Is largest
				rList *newNode=new rList;
				newNode->r=r;
				//TODO: implement c
				previous->next=newNode;
				size++;
				return 0;
			}
			if(current->r == r){
#ifdef debug
				printf("Duplicate!\n");
#endif
				return 1;//TODO: also check for c
			} else {
				rList *newNode=new rList;
				newNode->r=r;
				//TODO: implement c
				previous->next=newNode;
				newNode->next=current;
				size++;
				return 0;
			}
		}
	}
	void print_rList(){
		rList *current=head;
		if(current==NULL){
			printf("rList is empty.\n");
			return;
		}
		for(int i=0; i<size; i++){
			printf("%d ", current->r);
			current=current->next;
		}
		printf("\n");
	}
};
*/

template <typename T>
struct Stack{
	List<T> *head=NULL;
	int size=0;
	//Print tree, insert, free
	Stack(){}
	Stack(T c){
		insert(c);
	}
	~Stack(){//TODO implement free c
		clear();
	}
	void clear(){//TODO implement free c
		List<T> *current=head;
		for(int i=0; i<size; i++){
			List<T> *next=current->next;
			delete current;
			current=next;
		}
		head=NULL;
		size=0;
	}
	//TODO data type T
	int insert(T data){//Return if there's duplication then higher function call again
		//c Related features not implemented
		if(head==NULL){
			head=new List<T>;//Lack destructor
			head->data=data;
			//Lack c
			
			size++;
			return 0;//Success
		}else{//TODO: Duplication is determined by both r and c//Insert c datas
			List<T> *previous=NULL;
			List<T> *current=head;
			while(current && (data > current->data)){
				//Check if next is NULL
				previous=current;
				current=current->next;
			}
			if(!current){//Is largest
				List<T> *newNode=new List<T>;
				newNode->data=data;
				//TODO: implement c
				previous->next=newNode;
				size++;
				return 0;
			}
			if(current->data == data){
#ifdef debug
				printf("Duplicate!\n");
#endif
				return 1;//TODO: also check for c
			}else if(previous == NULL){//Is smallest
				List<T> *newNode=new List<T>;
				newNode->data=data;
				newNode->next=head;
				head=newNode;
				size++;
				return 0;
			} else {
				List<T> *newNode=new List<T>;
				newNode->data=data;
				//TODO: implement c
				previous->next=newNode;
				newNode->next=current;
				size++;
				return 0;
			}
		}
	}
	void print_List(){
		List<T> *current=head;
		if(current==NULL){
			cout << typeid(this).name() << " is empty.\n";
			//printf("List<T> is empty.\n");
			return;
		}
		for(int i=0; i<size; i++){
			//printf("%d ", current->data);
			cout << current->data << ' ';
			current=current->next;
		}
		printf("\n");
	}
};

struct cStack{
	cList *head=NULL;
	int size=0;
	//Print tree, insert, free
	cStack(){}
	cStack(int c){
		insert(c);
	}
	~cStack(){//TODO implement free c
		clear();
	}
	void clear(){//TODO implement free c
		cList *current=head;
		for(int i=0; i<size; i++){
			cList *next=current->next;
			delete current;
			current=next;
		}
		head=NULL;
		size=0;
	}
	int insert(int c){//Return if there's duplication then higher function call again
		//c Related features not implemented
		if(head==NULL){
			head=new cList;//Lack destructor
			head->c=c;
			//Lack c
			
			size++;
			return 0;//Success
		}else{//TODO: Duplication is determined by both r and c//Insert c datas
			cList *previous=NULL;
			cList *current=head;
			while(current && (c > current->c)){
				//Check if next is NULL
				previous=current;
				current=current->next;
			}
			if(!current){//Is largest
				cList *newNode=new cList;
				newNode->c=c;
				//TODO: implement c
				previous->next=newNode;
				size++;
				return 0;
			}
			if(current->c == c){
#ifdef debug
				printf("Duplicate!\n");
#endif
				return 1;//TODO: also check for c
			}else if(previous == NULL){//Is smallest
				cList *newNode=new cList;
				newNode->c=c;
				newNode->next=head;
				head=newNode;
				size++;
				return 0;
			} else {
				cList *newNode=new cList;
				newNode->c=c;
				//TODO: implement c
				previous->next=newNode;
				newNode->next=current;
				size++;
				return 0;
			}
		}
	}
	void print_cList(){
		cList *current=head;
		if(current==NULL){
			printf("cList is empty.\n");
			return;
		}
		for(int i=0; i<size; i++){
			printf("%d ", current->c);
			current=current->next;
		}
		printf("\n");
	}
};


struct Tree{
	//TODO Should be child rather than new cStk
	rList *head=NULL;
	int size=0;
	//Print tree, insert, free
	virtual ~Tree(){//TODO implement free c
		clear();
	}
	void clear(){//TODO implement free c
		rList *current=head;
		for(int i=0; i<size; i++){
			rList *next=current->next;
			delete current->child;
			delete current;
			current=next;
		}
		head=NULL;
		size=0;
	}
	virtual int insert(Point p){//Return if there's duplication then higher function call again
		int r=p.r;
		int c=p.c;//Related features not implemented
		if(head==NULL){
			head=new rList;//Lack destructor
			head->r=r;
			//Lack c
			head->child=new cStack;//Lack destructor
			size++;
			head->child->insert(c);
			return 0;//Success
		}else{//TODO: Duplication is determined by both r and c//Insert c datas
			rList *previous=NULL;
			rList *current=head;
			while(current && (r > current->r)){
				//Check if next is NULL
				previous=current;
				current=current->next;
			}
			if(!current){//Is largest
				rList *newNode=new rList;
				newNode->r=r;
				//TODO: implement c
				previous->next=newNode;
				size++;
				newNode->child=new cStack;
				newNode->child->insert(c);
				return 0;
			}
			if(current->r == r){
				if(!current->child)
					current->child=new cStack;
				if(current->child->insert(c)){
					return 1;
				} else {
					return 0;
				}//Also check for c
			} else if(previous == NULL){//Is smallest
				rList *newNode=new rList;
				newNode->r=r;
				newNode->next=head;
				head=newNode;
				size++;
				newNode->child=new cStack;
				newNode->child->insert(c);
				return 0;
			} else {
				rList *newNode=new rList;
				newNode->r=r;
				//TODO: implement c
				previous->next=newNode;
				newNode->next=current;
				size++;
				newNode->child=new cStack;
				newNode->child->insert(c);
				return 0;
			}
		}
	}
	void print_rList(){
		rList *current=head;
		if(current==NULL){
			printf("rList is empty.\n");
			return;
		}
		for(int i=0; i<size; i++){
			printf("%d ", current->r);
			current=current->next;
		}
		printf("\n");
	}
	void print_tree(){
		rList *current=head;
		if(current==NULL){
			printf("Tree is empty.\n");
			return;
		}
		for(int i=0; i<size; i++){
			printf("%d: ", current->r);
			current->child->print_cList();
			current=current->next;
		}
		cout << '\n'; 
	}
};

struct STree : Tree{//Solution list//Don't insert if larger
	int insert(Point p) override{//Return if there's duplication then higher function call again
		int r=p.r;
		int c=p.c;//Related features not implemented
		if(head==NULL){
			head=new rList;//Lack destructor
			head->r=r;
			//Lack c
			head->child=new cStack;//Lack destructor
			size++;
			head->child->insert(c);
			return 0;//Success
		}else{//TODO: Duplication is determined by both r and c//Insert c datas
			rList *previous=NULL;
			rList *current=head;
			while(current && (r > current->r)){
				//Check if next is NULL
				previous=current;
				current=current->next;
			}
			if(!current){//Is largest
				rList *newNode=new rList;
				newNode->r=r;
				//TODO: implement c
				previous->next=newNode;
				size++;
				newNode->child=new cStack;
				newNode->child->insert(c);
				return 0;
			}
			if(current->r == r){
				if(!current->child)
					current->child=new cStack;
				if(current->child->insert(c)){
					return 1;
				} else {
					return 0;
				}//Also check for c
			} else if(previous == NULL){//Is smallest
				rList *newNode=new rList;
				newNode->r=r;
				newNode->next=head;
				head=newNode;
				size++;
				newNode->child=new cStack;
				newNode->child->insert(c);
				return 0;
			} else {
				rList *newNode=new rList;
				newNode->r=r;
				//TODO: implement c
				previous->next=newNode;
				newNode->next=current;
				size++;
				newNode->child=new cStack;
				newNode->child->insert(c);
				return 0;
			}
		}
	}
};

Point point_gen(int rdim, int cdim){
	int r/*remainder*/=(RAND_MAX+1U)%(rdim*cdim);
	int tmp=random();
	while(tmp>RAND_MAX-r){
		tmp=random();
	}
	tmp%=rdim*cdim;
	Point p;
	p.c=tmp%cdim;
	p.r=tmp/cdim;
	return p;
}

Tree points_gen(int n, int rdim, int cdim){//n: faults //Retry if repeat//TODO Multiple faults
	Tree a;
	for(int i=0; i<n; i++){
		int r;
		do {
			r=a.insert(point_gen(rdim, cdim));
		} while (r);
	}
	return a;
}


//TODO A function that return solution list(multiple (nRow, nCol))
/*
solution_list(){//Don't insert if used is larger than previous record//Need tree?

}
*/
int main(){
	int common_dim=10;//Change to 1024
	int rdim=common_dim, cdim=common_dim;
	//bool mem[rdim][cdim];
	srandom(time(NULL));
	/*
	for(int i=0; i<50; i++)
		points_gen(4, 20, 20).print_tree();
	*/
	///*
	Stack<Point> a; a.print_List();
	a.insert(Point(3,4)); a.print_List();
	a.insert(Point(4,4)); a.print_List();
	//*/
	/*
	List<Point> a;
	a.data={3,7};
	cout << a.data;
	*/
	//mem_init(mem, rdim, cdim);
	//mem_print(mem, rdim, cdim);
	//printf("%u", RAND_MAX+1U);
	//2**30
	/*
	for(int i=0; i<1000; i++)
		point_gen(812825, 1321);//812825 and 1321
	*/
	/*
	Tree_new a;
	a.print_rList();
	a.insert({3,7}); a.print_rList();
	a.insert({3,7}); a.print_rList();
	a.insert({5,7}); a.print_rList();
	a.insert({4,7}); a.print_rList();
	a.insert({4,7}); a.print_rList();
	a.insert({4,8}); a.print_rList();
	a.print_tree();
	a.~Tree_new(); a.print_rList();
	a.insert({4,7}); a.print_rList();
	*/
	/*
	Tree a;
	a.print_tree();
	a.insert({3,7}); a.print_tree();
	a.insert({3,7}); a.print_tree();
	a.insert({3,8}); a.print_tree();
	a.insert({2,4}); a.print_tree();
	a.insert({0,4}); a.print_tree();
	a.insert({0,9}); a.print_tree();
	a.insert({26,-3}); a.print_tree();
	*/
	/*
	cStack b;
	b.print_cList();
	b.insert(3); b.print_cList();
	b.insert(3); b.print_cList();
	b.insert(5); b.print_cList();
	b.insert(4); b.print_cList();
	b.insert(4); b.print_cList();
	b.insert(1); b.print_cList();
	b.~cStack(); b.print_cList();
	b.insert(4); b.print_cList();
	*/
}
