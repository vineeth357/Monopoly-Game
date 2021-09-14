#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main() {
  while(true){
    cout<<"Enter 'r' to roll the dice : ";
    char dice;
    cin>>dice;
    if(dice == 'r'){
      srand((unsigned) time(0));
      int randomNumber;
      randomNumber = (rand() % 6) + 1;
      cout << "Dice number : " << randomNumber << endl;
    }
  }
}
