#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int main() {
  cout<<"Press 'Enter' to roll the dice :\n";
  while(true){
    while(cin.get() == '\n'){
      srand((unsigned) time(0));
      int randomNumber;
      randomNumber = (rand() % 12) + 1;
      cout << "Dice number : " << randomNumber;
	  cout<<"\n\nPress 'Enter' to roll the dice :\n";
    }
  }
}
