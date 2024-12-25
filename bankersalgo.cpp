#include<iostream>
using namespace std;

//Banker's Algorithm

int main(){
    int n ,m ,k,i,j; //i,j,k loop variables
    n=5;//no of processes
    m=3;//types of resources

    // Allocation Matrix
    int alloc[n][m]= { { 0, 1, 0 }, // P0 
                     { 2, 0, 0 }, // P1
                     { 3, 0, 2 }, // P2
                     { 2, 1, 1 }, // P3
                     { 0, 0, 2 } }; // P4

    int max[n][m]= { { 7, 5, 3 }, // P0 // MAX Matrix
                   { 3, 2, 2 }, // P1
                   { 9, 0, 2 }, // P2
                   { 2, 2, 2 }, // P3
                   { 4, 3, 3 } }; // P4

    int avail[3] = { 3, 3, 2 }; // Available Resources

    int f[n]; //finish array
    for(k=0;k<n;k++){
        f[k]=0;  //firstly all process are declared as not finished =0
    }
    int need[n][m];
     for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
     }

int y=0;//alloc to avail add ke liye like m traverse rows
int ans[n];//safe sequence arr
int index=0;// ans[n] index
     for(k=0;k<n;k++){  //every process check
           for(i=0;i<n;i++){//every i check column
              if(f[i]==0){ //check if process is not finished
                    int flag=0;
                    for(j=0;j<m;j++){
                        if(need[i][j]>avail[j]){
                            flag=1;
                            break;
                        }
                    }
                 if(flag==0){
                    ans[index++]=i;
                     for(y=0;y<m;y++){
                        avail[y]+=alloc[i][y];
                        f[i]=1;
                     }

                 } 
              }
           }
     }
     int flag=1;
     for(int i=0;i<n;i++){
        if (f[i]==0){
            flag=0;
            cout<<"the given sequence is not safe ";
            break;
        }
     }
     if(flag==1){
        cout<<"following sequence is safe "<<endl;
        for(int i=0;i<n-1;i++){
            cout<<'p'<<ans[i] <<"->";
           

        }
         cout<<'p'<<ans[n-1];
     }

    return 0;
}