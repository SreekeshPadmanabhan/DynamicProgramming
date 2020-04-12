//Edit distance between string S1 and S2 is the minimum number of symbol deletions required to transform S1 and S2 
//into a common string

//clang++ -o EditDistance EditDistance.cpp
//Sreekeshs-MacBook-Pro:Dynamic Programming sree$ ./EditDistance

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
  string line;
  ifstream myfile ("data.txt");
  
  char *left=NULL;char *top=NULL;
  int *rone=NULL;int *rtwo=NULL;
  size_t length;size_t k;size_t n;size_t m;
  float nedit;

  if (myfile.is_open())
  {
    while (myfile.good())
    {
      getline (myfile,line);
      if (left==NULL){
      m=line.length()-1;
      left = (char *) malloc((m+1) * sizeof(char));
      //http://www.cplusplus.com/reference/string/string/copy/
      length=line.copy(left+1,m,0);memset(left,'-',sizeof(char));
      } else if (top==NULL){
      n=line.length();
      top = (char *) malloc((n+1) * sizeof(char));
      length=line.copy(top+1,n,0);memset(top,'-',sizeof(char));      
      }    
    }
    rone = (int *) malloc((n+1) * sizeof(int));               //define first row
    rtwo = (int *) malloc((n+1) * sizeof(int));              //define second row
    //storing entire table is not necessary; final edit distance computed by storing only two rows of table.
    int row;int col; 
    for (col = 0; col < n+1; col++)  
     *(rone+col)=col;                                     //initialize first row
    for (row = 1; row < m+1; row++)
    {
     *rtwo=row;                                       //initialize first element
     for (col = 1; col < n+1; col++)
     {
     if(*(top+col)== *(left+row)){
      *(rtwo+col) = *(rone+(col-1));                             //diagonal copy
     } else {
       if(*(rtwo+(col-1))< *(rone+col)){
        *(rtwo+col) = (*(rtwo+(col-1)))+1;              //(@prvs col,same row)+1 
       } else {
        *(rtwo+col) = (*(rone+col))+1;                  //(@prvs row,same col)+1     
       }
     }    
    }
  //https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm copies n characters from memory area src to memory area dest; final edit distance by storing only two rows of the table
    memcpy(rone,rtwo,sizeof(int)*(n+1));  //copy second row to first @ iteration
   }
    
    nedit = ((n+m)-(*(rtwo+n)));
    nedit = ((float) nedit/(float)(n+m));   //calculate normalized edit distance
    cout<<"Edit Distance:"<< *(rtwo+n)<<endl;
    cout<<"Normalized Edit Distance:"<<nedit;
    myfile.close();
  }
  else cout << "Unable to open file";
  return 0;
}
