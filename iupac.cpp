#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
#include <termios.h>
#include <cstring>
//using namespace std;


char cp[20];

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

int dbc=0, tbc=0, brc=0;// The number of double, triple bonds and branches
int usv = 0;//The number to subtract from everything
int len=0, i=0, bri=0, brlen=0;

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
  void duplicates(){

  }
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


void reset(){
    for(int i = 0; i < 5; i++){
        db[i].loc = 0;
        db[i].stat = 0;
        tb[i].loc = 0;
        tb[i].stat = 0;
        br[i].len = 0;
        br[i].loc = 0;
    }
    len = 0;
    dbc = tbc = 0;
    i = 0;
    usv = 0;
    tbc = 0;
    dbc = 0;
    bri = 0;
    brc = 0;
    strcpy(cp, "");
}


int display(){
    if(len == 0){
        return 0;
    }
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
  tbc != 0?cout<<"-en":cout<<"-ene";
  }

  if(dbc==1){
  if(db[0].loc>1){cout<<"-"<<db[0].loc<<"-";}
  tbc != 0?cout<<"en":cout<<"ene";
  
  }

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

  return 0;
}



void update_usv(){
  usv = dbc + tbc;
  for(int i = 0; i<bri; i++){
    usv += br[i].len + 2;
  }
}

void name(const char* cp){
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
}

int main(int argc, char **argv){
   char inp; 
    
 if(argc > 1){
     if(!strcmp(argv[1], "-c")){
     	strcpy(cp, argv[2]);
     	name(cp);
     	display();
     return 0;
     }
     if(!strcmp(argv[1], "-f")){
	    system("clear");
	    char file[10];
	    strcpy(file, argv[2]);
	    ifstream infile;
	    infile.open(file);

	    if(!infile){
		cout<<"Unable to open file.\n";
		return 1;
	    }

	    else{
	    cout<<"Opening "<<file<<endl<<endl;
	    }

	    while(!infile.eof()){
		infile >> cp;
		cout<<cp<<"\n";
		name(cp); 
		display();
		cout<<endl;
		reset();
	       }

    
	  }
     return 0;
     }

  else{
    system("clear");
    cout<<"Enter a method of input:\n";
    cout<<"1 - Manually enter compound.\n";
    cout<<"2 - Choose a text file.\n";
    inp = getch();
  }
  if(inp == '1'){
    system("clear");
    cout<<"Enter the organic compound: "<<endl;
    cout<<"use = for double bonds."<<endl;
    cout<<"C for carbon atoms."<<endl;
    cout<<"() to add the branch."<<endl;
    cout<<"Use # for triple bond."<<endl<<endl;
    fgets(cp, 20, stdin);
    name(cp);
    display();
  }
  else if(inp == '2'){
    system("clear");
    char file[10];
    cout<<"Enter file name:\n";
    cin>>file;
    ifstream infile;
    infile.open(file);

    if(!infile){
        cout<<"Unable to open file.\n";
        return 1;
    }

    else{
    cout<<"Opening "<<file<<endl<<endl;
    }

    while(!infile.eof()){
        infile >> cp;
        cout<<cp<<"\n";
        name(cp); 
        display();
        cout<<endl;
        reset();
       }

    
  }

  return 0;
}
