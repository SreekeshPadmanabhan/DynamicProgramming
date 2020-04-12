#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;

vector <char> lcs_recursive(char *,size_t,char *,size_t,vector <char>);

int main(int argc, char** argv) {
 string line;ifstream dpfile ("lcs.txt"); 
 char *left=NULL;char *top=NULL;string *str=NULL;
 size_t length;size_t n;size_t m;
 vector <char> LCS;

  if (dpfile.is_open())
  {
    while (dpfile.good())
    {
      getline(dpfile,line);
      if (left==NULL){
      m=line.length()-1;cout<<m<<line<<endl;                //length-1 due to \n
      left = (char *) malloc((m)*sizeof(char));              //allocate for left
      length=line.copy(left,m,0);                                 //copy to left

      } else if (top==NULL){
      n=line.length();cout<<n<<line<<endl;                              //length
      top = (char *) malloc((n)*sizeof(char));                 //allocate to top
      length=line.copy(top,n,0);                                   //copy to top
      }      
    }  
  LCS=lcs_recursive(top,n,left,m,LCS);   
   
  while (!LCS.empty())
  {
    printf("%c ",LCS.back());                             //print final stack
    LCS.pop_back();
  }    
  dpfile.close(); 
 } 
 else cout << "Unable to open file"; 
 return 0;
}
    
vector <char> lcs_recursive(char *topn,size_t n,char *leftm,size_t m,vector <char> LCS){
 int *base=NULL;int *rfwd=NULL;int *rrvs=NULL;
 char *ytemp=NULL;char *xtemp=NULL;int *edist=NULL;
 int row;int col;int x;int y;
 //char *top = (char*) realloc (topn, (n+1) * sizeof(char));
 //char *left = (char*) realloc (leftm, (m+1) * sizeof(char));
 char *top = (char*) malloc ((n+1)*sizeof(char));      //allocate memory for top
 char *left = (char*) malloc ((m+1)*sizeof(char));    //allocate memory for left
 memcpy(top+1,topn,sizeof(char)*(n));              //copy top parameter off by 1
 memcpy(left+1,leftm,sizeof(char)*(m));           //copy left parameter off by 1
 memset(left,'-',sizeof(char));memset(top,'-',sizeof(char));            //@debug
    
  if (n==1){
   for (row = 0; row < m+1; row++)
   {
    if(*(top+1)== *(left+row)) {
    LCS.push_back(*(top+1));cout<<*(top+1);
    }
   }   
   return LCS;
  } else if (m == 1){
   for (col = 0; col < n+1; col++)
   {
    if(*(left+1)== *(top+col)) {
    LCS.push_back(*(left+1));cout<<*(left+1);
    }
   } 
   return LCS;   
  } else {
/*----------------------------------------------------------------------------*/      
  base = (int *) malloc((n+1)*sizeof(int));                   //initial base row
  for (col = 0; col < n+1; col++){*(base+col)=col;}            //initialize base
  rfwd=(int *) malloc((n+1) * sizeof(int));                            //fwd row
  for (row = 1; row <= floor((m)/2); row++)            // row 1 to floor(rows/2)
  {
   *rfwd=row;                                         //initialize first element
   for (col = 1; col < n+1; col++)                           //col 1 to n,excl 0
   {
    if(*(top+col)== *(left+row)){
     *(rfwd+col) = *(base+(col-1));                              //diagonal copy
    } else {
     if(*(rfwd+(col-1))< *(base+col)){
     *(rfwd+col) = (*(rfwd+(col-1)))+1;                 //(@prvs col,same row)+1   
     } else {
     *(rfwd+col) = (*(base+col))+1;                     //(@prvs row,same col)+1
     }
    }    
   } 
  memcpy(base,rfwd,sizeof(int)*(n+1));     //copy rfwd to base for nxt iteration
  }  
  cout <<"F:";for (col = 0; col < n+1; col++){cout<<*(rfwd+col);}x=floor((m)/2);
/*-left shift top & left by 1-------------------------------------------------*/  
  memcpy(top,top+1,sizeof(char)*(n));memset(top+n,'-',sizeof(char));   //<<shift
  memcpy(left,left+1,sizeof(char)*(m));memset(left+m,'-',sizeof(char));//<<shift
/*----------------------------------------------------------------------------*/    
  for (col = n;col>=0;col--){*(base+col)=(n-col);}cout<<endl;  //initialize base
  rrvs=(int *) malloc((n+1) * sizeof(int));                            //rvs row
  for (row=m-1;row>=(floor((m)/2));row--)    //NOT floor(m/2)+1@ shift(top/left)
  {
    *(rrvs+n)=m-row;                                  //initialize first element   
    for (col=n-1; col>= 0; col--)                          //col n-1 to 0,excl n
    {
    if(*(top+col)== *(left+row)){       
    *(rrvs+col) = *(base+(col+1));                               //diagonal copy
    } else {
    if(*(rrvs+(col+1))< *(base+col)){
    *(rrvs+col)=(*(rrvs+(col+1)))+1;                    //(@next col,same row)+1 
    } else {
    *(rrvs+col)=(*(base+col))+1;                        //(@next row,same col)+1             
    }
    }  
  }      
  memcpy(base,rrvs,sizeof(int)*(n+1));     //copy rrvs to base for nxt iteration
  }  
  cout <<"R:";for (col = 0; col <n+1; col++){cout<<*(rrvs+col);}
/*-calculate last location of the minimum edit distance-----------------------*/           
  int edistmin=0;
  edist=(int *) malloc((n+1) * sizeof(int)); cout <<endl;
  for (col = 0; col <n+1; col++)
  {      
   *(edist+col)=*(rfwd+col) + *(rrvs+col);
   if (edistmin == 0){
   edistmin = *(edist+col);
   } else if (*(edist+col) < edistmin) {
    y=col;                                        //NOT y-1 as per program logic
    edistmin = *(edist+col); 
   }
  }
/*-y::top x::left-------------------------------------------------------------*/
  cout<<"x:"<<x<<"y:"<<y; 
  char *x_front=NULL;char *x_back=NULL;char *y_front=NULL;char *y_back=NULL;
  
  x_front=(char *) malloc(sizeof(char)*x);
  memcpy(x_front,leftm,sizeof(char)*(x));
  y_front=(char *) malloc((sizeof(char)*(y)));
  memcpy(y_front,topn,sizeof(char)*(y));

  x_back=(char *) malloc((m-x) * sizeof(char));
  memcpy(x_back,leftm+x,sizeof(char)*(m-x));
  y_back=(char *) malloc( sizeof(char)*(n-y));
  memcpy(y_back,topn+y,sizeof(char)*(n-y));
  
  LCS = lcs_recursive(y_front,y,x_front,x,LCS);                   
  LCS = lcs_recursive(y_back,n-y,x_back,m-x,LCS);  
  free;
  } 
 }