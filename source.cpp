// This Program is basic implementation of B-Tree.
//	* Program includes following facilities:
//	* Insertion: Before insertion process, program ask question to capacity order.
//	             To load given input (lab7.txt) file, press [1].
//				 For given input, you should select the capacity order at least 20.
//					else processing is being too long.
//  * Printing:  Program prints all the key as formatting.
//  * Searching: Program searches the primary key according to plate number.
//               You can understand that where is the key because of the formatted print.
//  * Inserting New Node: It should also allow the user to insert new records to the B-Tree.
//  Copyright © Hakan Kayakoku
//  11290284


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <windows.h>

#define MAX 50
using namespace std;

int maxSize;
string splitStr( string str ){return str.substr(0,9);}
bool menu();

class node;

typedef struct pair
{
	string key;
	node *next;
}pairx;

class node
{
	public:
	node *father;
	int noofkeys;
	pairx data[MAX];
	node *first;
	node();
	void insert_in_node(pairx x);
	pairx splitnode(pairx x);
	int leaf_node();
	node *nextindex(string x);
	bool display(int search = 0 , string value = " ");
};

bool node::display(int search , string value)
{
	int i;
	if (search == 0)
	{
		cout<<"( ";
		for(i=0;i<noofkeys;i++)
			cout<<splitStr(data[i].key)<<" | ";
		for(i;i<maxSize;i++)
			cout<<". | ";
		cout<<" )";
		return false;
	}
	else
	{
		for(i=0;i<noofkeys;i++)
		{
			if (search == 1)
			{
				if( splitStr(data[i].key) == value )
				{
					cout<<"--------- FOUNDED!!! --------"<<endl;
					cout<<data[i].key<<endl;
					return true;
				}
			}
		}

		return false;
	}

}
node* node::nextindex(string x)
{
	int i;
	if(x<data[0].key)
		return first;
	for(i=0 ; i<noofkeys;i++)
	{
		if(x<=data[i].key)
			return (data[i-1].next);
	}
	return (data[i-1].next);
	
}
int node::leaf_node()
{
	if(data[0].next==NULL)
		return 1;
	return 0;
}


 void node::insert_in_node(pairx mypair)
   {
	int i;
	for(i=noofkeys-1;i>=0 && data[i].key>mypair.key;i--)
		data[i+1]=data[i];
	data[i+1]=mypair;
	noofkeys++;
   }
pairx node::splitnode(pairx x)
{
	node *T;
	pairx mypair;
	int i,j,centre;
	centre=(noofkeys-1)/2;
	T=new node;
	if(x.key>data[centre].key)  //Divide the node in two parts(original and T)
		{
		for(i=centre+1,j=0;i<=noofkeys;i++,j++)
			T->data[j]=data[i];
		 T->noofkeys=noofkeys-centre-1;
		 noofkeys=noofkeys-T->noofkeys;
		 T->insert_in_node(x);
		 T->first=T->data[0].next;
		 T->father=father;
		 mypair.key=T->data[0].key;
		 mypair.next=T;
		 //Delete the first key from node T
		 for(i=1;i<T->noofkeys;i++)
			T->data[i-1]=T->data[i];
		 T->noofkeys--;
		}
	 else
		{
		 for(i=centre,j=0;i<noofkeys;i++,j++)
			T->data[j]=data[i];
		 T->noofkeys=noofkeys-centre;
		 noofkeys=noofkeys-T->noofkeys;
		 insert_in_node(x);
		 T->father=father;
		 mypair.key=T->data[0].key;
		 mypair.next=T;
		 //Delete the first key from node T
		 for(i=1;i<T->noofkeys;i++)
			T->data[i-1]=T->data[i];
		 T->noofkeys--;
		}
   return(mypair);
}
node::node()
	{
		  for(int i=0;i<=MAX;i++)
		   data[i].next=NULL;
		  noofkeys=0;
		  father=NULL;
		  first=NULL;
	 }



class btree
{
	int mkeys;
	node *root;
	public:
		btree(int n)
		   {
			mkeys=n;
			root=NULL;
		   }
	void insert(string x);
	void displaytree(int search = 0 , string str = " ");
};



void btree::insert(string x)
  {
	int index;
	pairx mypair;
	node *p,*q;
	mypair.key=x;
	mypair.next=NULL;
	if(root==NULL)
	{
		 root = new node;
		 root->insert_in_node(mypair);
	}
	else
	{
		p=root;
		while(!(p->leaf_node()))
		  p=p->nextindex(x);
		if(p->noofkeys < mkeys-1)
			 p->insert_in_node(mypair);

	  else
		{
			 mypair=p->splitnode(mypair);
			 while(1)
			   {
			 if(p==root)
				{
				   q=new node;
				   q->data[0]=mypair;
				   q->first=root;
				   q->father=NULL;
				   q->noofkeys=1;
				   root=q;
				   q->first->father=q;
				   q->data[0].next->father=q;
				   return;

				 }
			  else
				 {
				p=p->father;
				if(p->noofkeys < mkeys)
				   {
					p->insert_in_node(mypair);
					return;
					}
				 else
					mypair=p->splitnode(mypair);
				  }

			 }
		  }

	}
  }

  class Q 
  {
	node *data[60];
	int R,F;
	public:
		Q()
		  {
			R=F=0;
		  }
		int empty()
		  {
			if(R==F)
				return 1;
			else
				return 0;
		  }
		node *deque()
		  {
			return data[F++];
		  }
		void  enque(node *x)
			{
			data[R++]=x;
			}
		void makeempty()
		   {
			R=F=0;
		   }
   };

void btree::displaytree(int search,string str)
{
	Q q1,q2;
	node *p;
	q1.enque(root);
	while(!q1.empty())
	  {
		q2.makeempty();
		cout<<"\n";
		while(!q1.empty())
		  {
			p=q1.deque();
			if( p->display(search,str) )
				return;

			//cout<<"  ";
			if(!p->leaf_node())
			   {
				q2.enque(p->first);
				for(int i=0;i<p->noofkeys;i++)
					q2.enque(p->data[i].next);

			   }
		   }
		q1=q2;
	   }
		if (search == 1)
		{
			cout<<"--------- NOTHING FOUND!!! --------"<<endl;
		}	
}

int main()
{
		ifstream inf("lab7.txt");    
        int n,i,key;
        string x;
        node *p;
        cout<<"\nEnter the Capacity Order: ";
        cin>>n;
        btree b(n*2);
        maxSize = n*2;
		system("CLS");
		while(menu() && cin>>key)
		{
			if(key == 1)
			{
				string line;
				getline(inf,line);
				int counter = 1;
				while(!inf.eof())
				{
					b.insert(line);
					getline(inf,line);
					counter++;
				}
			cout<<"--------- LOADED! --------- "<<endl;
			Sleep(2000);
			system("CLS");
			}

			if(key == 2)
			{
				b.displaytree();
			}
			
			if(key == 3)
			{
				string str;
				cout<<"Enter Searching Plate:"<<endl;
				getline(cin,str);
				getline(cin,str);
				b.displaytree(1,str);
			}
			
			if(key == 4)
			{
				string str;
				cout<<"Enter Value:"<<endl;
				getline(cin,str);
				getline(cin,str);
				b.insert(str);
				cout<<"Inserted!: "<<str<<endl;
			}

			if(key == -1)
			{
				cout<<"PROGRAM TERMINATED BY USER!!!"<<endl;
				return 0;
			}
		}
}



bool menu()
{
	cout<<"\n"<<endl;
	cout<<setfill('-')<<setw(33)<<"-"<<endl;
	cout<<"|\t[1] Load .txt File\t|"<<endl;
	cout<<"|\t[2] Print Tree\t\t|"<<endl;
	cout<<"|\t[3] Searching\t\t|"<<endl;
	cout<<"|\t[4] Insert New\t\t|"<<endl;
	cout<<"|\t[-1] Exit\t\t|"<<endl;
	cout<<setfill('-')<<setw(33)<<"-"<<endl;
	cout<<":/>  ";
	return true;
}
