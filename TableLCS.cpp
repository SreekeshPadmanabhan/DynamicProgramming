#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
  string line;
  ifstream myfile ("data4.txt");
  
  char *left=NULL;char *top=NULL;
  int *rone=NULL;int *rtwo=NULL;
  size_t length;int k;int n;int m;
  int *dpptr;int **rptr;
  vector <char> Stack;

  if (myfile.is_open())
  {
    while (myfile.good())
    {
      getline (myfile,line);
      if (left==NULL){
      m=line.length()-1;
      left = (char *) malloc((line.length()+1) * sizeof(char));
      length=line.copy(left+1,line.length(),0);memset(left,'-',sizeof(char));
      } else if (top==NULL){
      n=line.length();cout << line<<endl;
      top = (char *) malloc((line.length()+1) * sizeof(char));
      length=line.copy(top+1,line.length(),0);memset(top,'-',sizeof(char));      
      }
    }
    
    dpptr = (int *) malloc((n+1) * (m+1) * sizeof(int));        //matrix pointer
    rptr =  (int **) malloc((m+1) * sizeof(int *));    //pointer to row pointers
    
    for (k = 0; k < m+1; k++){
     rptr[k] = dpptr + (k * (n+1));      //define each row pointers wrt 2D array
    }
    
   int row;int col=0;  
   for (col = 0; col < n+1; col++)
   {rptr[0][col] = col;}                                  //initialize first row
   for (row = 1; row < m; row++)
    {      
     rptr[row][0] = row;
     for (col = 1; col < n+1; col++)
     {              
     if(*(top+col)== *(left+row)){
      rptr[row][col] = rptr[row-1][col-1];                       //diagonal copy
     } else {
       if(rptr[row-1][col]<rptr[row][col-1]){
        rptr[row][col] = rptr[row-1][col]+1;            //(@prvs row,same col)+1   
       } else {
        rptr[row][col] = rptr[row][col-1]+1;            //(@prvs col,same row)+1                  
       }
     }
    }     
    cout<<endl; 
   } 
   
  int column=n; int index=7;char bktrc[8];
  for (row = m; row >= 0; row--){ 
   for (col = column; col >= 0; col--){
    if(*(top+col)== *(left+row)){
     Stack.push_back(*(top+col));
     column = col-1;break;            //break out of inner loop @ [row-1][col-1]
    } else {
     if(rptr[row-1][col]<rptr[row][col-1]){
       column = col;break;          //break out of inner loop @ [row-1][col] top 
     } else if(rptr[row][col-1]<=rptr[row-1][col]){
       continue;          //continue to next inner iteration @ [row][col-1] LEFT         
     }      
    }
   }
  } 
  
 ofstream stck ("stacklcs.txt");
 if (stck.is_open()){
  while (!Stack.empty())
   {
    stck<<Stack.back();                                           //final stack
    Stack.pop_back();
   }  
  }
 }
 else cout << "Unable to open file"; 
 return 0;
}