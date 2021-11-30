#include "global.hpp"
#include "HelperFunctions.hpp"

vector<string> split(string &str, char delimiter) {   //split a string into vector of strings
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  return internal;
}

string chanceorcchest(string &ccc){        //returns modified chance & CommunityChest statements as a perfect fit for the board
  vector<string> parts = split(ccc, ':');
  string tobereturned = parts[2];
  for(int ext=tobereturned.size(); ext<60; ext++) tobereturned += " ";
  return tobereturned;
}

string playersandmoney(string &ccc){        //returns modified chance & CommunityChest statements as a perfect fit for the board
  vector<string> parts = split(ccc, ':');
  string tobereturned = parts[2];
  for(int ext=tobereturned.size(); ext<100; ext++) tobereturned += " ";
  return tobereturned;
}

bool isNumber(string s){            // to check if a string is a number
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;
    return true;
}


void PrintInstructions(){
    cout<<"NOTE: PLEASE REDUCE THE FONT SIZE/ ZOOM OUT THE TERMINAL SO THAT ATLEAST 200 CHARACTERS FIT IN EACH LINE.\n\n";
    cout<<"READ THE FOLLOWING RULES AND CONVENTIONS.\nGAME RULES:\n";
    cout<<"1. Players initially is given 100000/- start from 'START' and each one has only one turn to throw the dice.\n";
    cout<<"2. Initially since no place is owned by anyone, 'owner' of all places are kept as 'none'.\n";
    cout<<"3. If a player lands on any place whose owner is 'none' and the player is willing to buy it, the owner name is changed thereafter.\n";
    cout<<"4. If that player also wishes to build house/hotel a question will be asked then. Answer accordingly.\n";
    cout<<"5. Maximum number of houses/hotels per each player are 8.\n";
    cout<<"6. If a player lands on a place which is owned by another one, the total rent";
    cout<<"\n(including rent with hotel/house if it has one) is also displayed for reference.\n";
    cout<<"7. The houses are represented by '[^]' and hotels as '[H]' beside the owner name.\n";
    cout<<"8. When a player lands on JAIL, he have to pay a fine of 250/- in total and don't have next turn.\n";
    cout<<"9. For that player, to skip his next turn, just enter 99 when his just next turn comes.(Other players, take care of this guy :p)\n";
    cout<<"10. Also, you can use 99 to skip a person's turn when ever needed.\n";
    cout<<"11. When a player lands on INCOMETAX/WEALTHTAX/CLUB/RESTHOUSE, 100/- is taken from him.\n";
    cout<<"12. You dont worry about the money calculations. Everything is taken care of.\n";
    cout<<"13. Whenever a player's money goes less than 0, it will display negative amount. But, that player is asked in his later turn to sell his places.\n";
    cout<<"13. The Bank Mortgage value is exactly half of the price of the place. If it has hotel/house, the same amount as the price of them is also returned.\n";
    cout<<"14. When a player's money goes negative and also, he don't own any place anymore, that player is eliminated out of game.\n";
    cout<<"15. This elimination is done till only one player is left and he/she would be the winner.\n";
    cout<<"Before we start the game, here are the conventions to be followed while giving input.\n";
    cout<<"1. The number of players is atleast 2 STRICTLY less than or equal to 4.(If you try more than 5, first 4 only are considered)\n";
    cout<<"2. When asked for dice number, enter only a number in range 1-12.(If you don't, I'll make you do :])\n";
    cout<<"3. Try to keep the player name within 3 characters for best appearence.(If you keep more than 3 characters, only first 3 are considered.)\n";
    cout<<"4. Do not enter whatever you wish other than what is asked. Sometimes doing so may lead into trouble that you have to restart afresh.\n\n";
    
}
