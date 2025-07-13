
#include <iostream>


using namespace std;



void haha(char * target){
    int col =  1 + (target[0] -'a');
    int row = (target[1] -'0');

    int index = (((row-1)*8)+(col -1));
    cout << col <<endl << row << endl; 
    cout << index;
}

int main (){
  char hoe[2] = {'h', '8'};
  haha(hoe);
  return 0;
}