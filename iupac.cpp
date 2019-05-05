#include<iostream>
#include<cstring>
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

class branchClass{
public:
  int len;
  int loc;
  int fGroup;
}br[5];
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


int branch(int a){
  br[bri].loc = a - usv;//because ( is also a character that takes up a position
  for(int i = a; cp[i] != ')'; i++){
    if(cp[i] == 'C'){
      br[bri].len += 1;
    }
  }

  //cout<<br[bri].loc<<" "<<br[bri].len<<endl;
  bri++;
  return a + br[bri].len + 2;
}






void display(){
  //checking for branches and printing their names
  if(bri){
    for(int i = 0; i < bri; i++){
      if(i>0){
        cout<<"-";
      }
      cout<<br[i].loc<<"-"<<dict[br[i].len - 1]<<"yl";
    }
  }
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
  for(int i = 0; i<bri; i++){
    usv += br[i].len + 2;
  }
}



int main(int argc, char **argv){
  if (argc == 1){
    system("clear");
    cout<<"Enter the organic compound: "<<endl;
    cout<<"use = for double bonds."<<endl;
    cout<<"C for carbon atoms."<<endl;
    cout<<"() to add the branch."<<endl;
    cout<<"Use # for triple bond."<<endl<<endl;
    fgets(cp, 20, stdin);
  }

  else{
    strcpy(cp, argv[1]);
  }

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
      i = branch(i);
    }
    update_usv();

  }


  //numcorr();
  display();


  return 0;
}
