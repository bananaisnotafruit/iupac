#include<iostream>
#include<strings.h>
#include<stdlib.h>
using namespace std;

char cp[20];



int dbc=0, tbc=0, brc=0;// The number of double, triple bonds and branches
int usv = 0;//The number to subtract from everything
int len=0, i=0, dbi=0, tbi=0, bri=0, brlen=0;


char dict[23][9]={"meth","eth","prop","but","pent","hex","hept","oct","non","dec",
                  "undec","dodec","tridec","tetradec","pentadec","hexadec","heptadec",
                  "octadec","nonadec","eicos","heneicos","docos","tricos"};


class doubleBond{
public:
  int stat;
  int loc;
}db[5];

class tripleBond{
public:
  int stat;
  int loc;
}tb[5];

class branch{
public:
  int len;
  int loc;
}z;
/*
void numcorr(){
  if(db.loc > len/2)// Changes the position to the lowest possible for double bonds
  {
    db.loc = len - db.loc;
      if(z.loc) {z.loc = len - z.loc + 1;}
  }

  if(tb.loc > len/2)// Changes the position to the lowest possible for triple bonds
  {
    tb.loc = len - tb.loc;
      if(z.loc) {tb.loc = len - tb.loc + 1;}
  }

  if(z.loc > len/2 && db.stat == 0 && tb.stat == 0){
    z.loc = len - z.loc + 1;}
}
*/

void display(){
  if(z.loc)cout<<z.loc<<"-"<<dict[z.len-1]<<"yl";
  cout<<dict[len-1]; // prints the base name

  //  Double bonds
  if(dbc > 1){
  cout<<"-";
  for(int k=0; k<dbc; k++){
    cout<<db[k].loc;
    if(db[k+1].stat!=0){
      cout<<",";
      }
    }
  cout<<"-ene";
  }

  if(dbc==1){
  if(db[0].loc>1){cout<<"-"<<db[0].loc<<"-";}
  cout<<"ene";}

  //  Triple bonds
  if(tbc > 1){
  cout<<"-";
  for(int k=0; k<tbc; k++){
    cout<<tb[k].loc;
    if(tb[k+1].stat!=0){
      cout<<",";
      }
    }
  cout<<"-yne";
  }

  if(tbc==1){
  if(tb[0].loc>1){cout<<"-"<<tb[0].loc<<"-";}
  cout<<"yne";}

  //  Single bonds only
  if(dbc==0 && tbc==0){cout<<"ane";}
  cout<<endl;
}



void update_usv(){
  usv = dbc + tbc;
}



int main(){
  system("clear");
  cout<<"Enter the organic compound: "<<endl;
  cout<<"use = for double bonds."<<endl;
  cout<<"C for carbon atoms."<<endl;
  cout<<"() to add the branch."<<endl;
  cout<<"Use # for triple bond."<<endl<<endl;
  fgets(cp, 20, stdin);

  for(i = 0; cp[i] != '\0'; i++){

    if(cp[i] == 'C'){
      len++;
    }

    if(cp[i] == '='){
      db[dbc].stat = 1;//sets the double bond element to active
      db[dbc].loc = i - usv;
      dbc++;
    }

    if(cp[i] == '#'){
      tb[tbc].stat=1;
      tb[tbc].loc=i - usv;
      tbc++;
    }

    if(cp[i] == '('){
      z.loc = i;
      for(bri=i; cp[bri]!=')'; bri++){
        if(cp[bri] == 'C'){
          z.len++;
        }
      }
      i=bri-1;
      if(dbc){z.loc = z.loc - dbc;}//checks if double bonds or
      if(tbc){z.loc = z.loc - tbc;}//triple bonds exist
    }
    update_usv();

  }


  //numcorr();
  display();


  return 0;
}
