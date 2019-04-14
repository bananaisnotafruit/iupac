#include<iostream>
#include<strings.h>
using namespace std;

char dict[10][5]={"meth","eth","prop","but","pent","hex","hept","oct","non","dec"};

class db{
public:
  int stat;
  int loc;
}x;

class tb{
public:
  int stat;
  int loc;
}y;

class branch{
public:
  int len;
  int loc;
}z;

int main(){
  char cp[20];
  int len=0, i=0, dbi=0, tbi=0, bri=0, brlen=0, temp=0;

  fgets(cp, 20, stdin);

  for(i = 0; cp[i] != '\0'; i++){

    if(cp[i] == 'C'){
      len++;
    }

    if(cp[i] == '='){
      x.stat=1;
      x.loc=i;
    }

    if(cp[i] == '('){
      z.loc = i;
      for(bri=i; cp[bri]!=')'; bri++){
        if(cp[bri] == 'C'){
          z.len++;
        }
      }
      i=bri-1;
      temp = i;
    }

  }

  if(x.loc > len/2)// Changes the position to the lowest possible
  {
    x.loc = len - x.loc;
      if(z.loc) {z.loc = len - z.loc + 1;}
  }
  if(z.loc > len/2 && x.stat == 0){
    z.loc = len - z.loc + 1;
  }

  //cout<<"The length of the compound is "<<len<<endl;

  if(z.loc)cout<<z.loc<<"-"<<dict[z.len-1]<<"yl";


  cout<<dict[len-1]; // prints the base name


  if(x.stat){cout<<"-"<<x.loc<<"-";}

  if(x.stat){cout<<"ene";}
  //else if(){cout<<"yne";}
  else{cout<<"ane";}


  cout<<endl;
  return 0;
}
