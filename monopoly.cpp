#include<bits/stdc++.h>
using namespace std;
const string emptystring = "                    ";
class place {       //contains all attributes of a place
  public:
    bool ifplace;
    bool hotel;
    string name;
    string color;
    int price;
    string owner;
    bool house;
    int hotelprice;  //same value goes to house price.
    int rent;
    int hotelrent;
    int houserent;
    //parametrised constructor
    place(bool ifp, bool ih, string n, string co, int p, string o, bool h, int hotcos, int ren, int hotrent, int hourent);
};
place::place(bool ifp, bool ih, string n, string co, int p, string o, bool h, int hotcos, int ren, int hotrent, int hourent){
    ifplace = ifp;
    hotel = ih;
    name = n;
    color = co;
    price = p;
    owner = o;
    house = h;
    hotelprice = hotcos;
    rent = ren;
    hotelrent = hotrent;
    houserent = hourent;
};
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
int main(){
  cout<<"NOTE: PLEASE REDUCE THE FONT SIZE/ ZOOM OUT THE TERMINAL SO THAT ATLEAST 200 CHARACTERS FIT IN EACH LINE.\n\n";
  cout<<"READ THE FOLLOWING RULES AND CONVENTIONS.\nGAME RULES:\n";
  cout<<"1. Players initially are given 100000/- start from 'START' and each one has only one turn to throw the dice.\n";
  cout<<"2. Initially since no place is owned by anyone, 'owner' of all places are kept as 'none'.\n";
  cout<<"3. If a player lands on any place whose owner is 'none' and the player is willing to buy it, the owner name is changed thereafter.\n";
  cout<<"4. If that player also wishes to build house/hotel a question will be asked then. Answer accordingly.\n";
  cout<<"5. Maximum number of houses/hotels per each player are 8.\n";
  cout<<"6. If a player lands on a place which is owned by another one, the total rent";
  cout<<"\n(including rent with hotel/house if it has one) is also displayed for reference.\n";
  cout<<"7. The houses are represented by '[^]' and hotels as '[H]' beside the owner name.\n";
  cout<<"8. When a player lands on JAIL, he have to pay a fine of 500/- in total and don't have next turn.\n";
  cout<<"9. For that player, to skip his next turn, just enter 99 when his just next turn comes.(Other players, take care of this guy :p)\n";
  cout<<"10. Total fine collected in two sets of 250/- each; first is when he arrives and next is when he don't play next turn(when 99 is entered).\n";
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
  int n;
  cout<<"Enter the number of players(atleast 2 & not more than 4) : ";
  cin>>n;
  while(n<2){
     cout<<"Enter atleast 2 : ";
     cin>>n;
   }
  if(n>4) n=4;

  vector<string>players;
  //FINAL BOARD which is printed in the terminal.
  vector<vector<string>> AJ(70);      //  (it's AJ coz, I am AJAY :o)
  unordered_map<string, int> position;              //positions of players
  unordered_map<int, string> Chance;
  unordered_map<int, string> CommunityChest;
  unordered_map<string, unordered_map<string, int>> colorsowned;
  unordered_map<string, vector<int>> placesowned;
  unordered_map<string, long> moneyowned;
  unordered_map<string, int> hotelsowned;
  unordered_map<string, int> housesowned;

  for(int i=0; i<n; i++){
    string playeri;
    cout<<"Name of player"<<i+1<<" (3 characters are suggested) : ";
    cin>>playeri;
    playeri = playeri.size()>=3 ? playeri.substr(0,3) : playeri;
    players.push_back(playeri);
    position[playeri] = 0;
    colorsowned[playeri]["red"] = 0;
    colorsowned[playeri]["green"] = 0;
    colorsowned[playeri]["pink"] = 0;
    vector<int> forplacesowned;
    placesowned[playeri] = forplacesowned;
    moneyowned[playeri] = 100000;
    hotelsowned[playeri] = 0;
    housesowned[playeri] = 0;
  }
  cout<<"\n\n";
  //chance statements:
  Chance[1] = "CHANCE 1 :: Pay each player 50/-.";
  Chance[2] = "CHANCE 2 :: Loss in Share Market. Pay 850/- to Bank.";
  Chance[3] = "CHANCE 3 :: Won Lottry Prize of 800/-.";
  Chance[4] = "CHANCE 4 :: Drink & Drive case. Pay a Fine of 250/-.";
  Chance[5] = "CHANCE 5 :: Won CrossWord Game. Prize money-1350/-.";
  Chance[6] = "CHANCE 6 :: Loss in Business. Pay 750/-.";
  Chance[7] = "CHANCE 7 :: Won JackPot. Get 2000/-.";
  Chance[8] = "CHANCE 8 :: Renovating houses and hotels. Pay 200/- for each.";
  Chance[9] = "CHANCE 9 :: Get Diwali Bonus of 2200/-.";
  Chance[10] = "CHANCE 10 :: Go to JAIL.";
  Chance[11] = "CHANCE 11 :: Best employee of the year. Get 1250/-.";
  Chance[12] = "CHANCE 12 :: Go to RESTHOUSE.";
  //CommunityChest statements:
  CommunityChest[1] = "COMMUNITY CHEST 1 :: Go to CLUB. Pay 100/- to each player.";
  CommunityChest[2] = "COMMUNITY CHEST 2 :: Collect 250/- as Birthday gift from every player.";
  CommunityChest[3] = "COMMUNITY CHEST 3 :: Go to JAIL.";
  CommunityChest[4] = "COMMUNITY CHEST 4 :: Beauty Contest winner. Get 850/-.";
  CommunityChest[5] = "COMMUNITY CHEST 5 :: School fees. pay 1000/-.";
  CommunityChest[6] = "COMMUNITY CHEST 6 :: Income Tax refund. Collect 1250/-.";
  CommunityChest[7] = "COMMUNITY CHEST 7 :: Marriage Celebrations. Pay 2000/- to bank.";
  CommunityChest[8] = "COMMUNITY CHEST 8 :: Sold old scrape. Get 1200/-.";
  CommunityChest[9] = "COMMUNITY CHEST 9 :: Pay Insurance Premium of 1500/-.";
  CommunityChest[10] = "COMMUNITY CHEST 10 :: Profit in share Market. Get 750/-.";
  CommunityChest[11] = "COMMUNITY CHEST 11 :: Renovating all hotels. Pay 200/- for each.";
  CommunityChest[12] = "COMMUNITY CHEST 12 :: Profit in RealEstate deal. Get 700/-.";

  vector<place> board;          //defining each place in the game and to be stored in `board`
  place b0 = place(false, false, "START", "black", 0, "none", false, 0, 0 ,0, 0);
  place b1 = place(true, false, "MUMBAI", "pink", 8500, "none", false, 7500, 1200, 9000, 4000);
  place b2 = place(true, false, "WATERWORKS", "white", 3200, "none", false, 0, 500, 0, 0);
  place b3 = place(true, false, "RAILWAYS", "white", 9000, "none", false, 0, 1000, 0, 0);
  place b4 = place(true, false, "AHMEDABAD", "red", 4000, "none", false, 4500, 400, 5000, 1500);
  place b5 = place(false, false, "INCOMETAX", "black", 0, "none", false, 0, 0, 0, 0);
  place b6 = place(true, false, "MARGOA", "green", 4000, "none", false, 4500, 400, 6500, 2200);
  place b7 = place(false, false, "CHANCE", "black", 0, "none", false, 0, 0, 0, 0);
  place b8 = place(true, false, "JAIPUR", "green", 3000, "none", false, 4000, 300, 5500, 1500);
  place b9 = place(false, false, "JAIL", "black", 0, "none", false, 0, 0, 0, 0);
  place b10= place(true, false, "CHANDIGARH", "red", 2500, "none", false, 3000, 200, 3500, 900);
  place b11= place(true, false, "NEW DELHI", "red", 6000, "none", false, 5000, 750, 7500, 3000);
  place b12= place(true, false, "BEST", "white", 3500, "none", false, 0, 600, 0, 0);
  place b13= place(true, false, "E.COMPANY", "white", 2500, "none", false, 0, 300, 0, 0);
  place b14= place(true, false, "AMRITSAR", "red", 3300, "none", false, 4500, 300, 5000, 1400);
  place b15= place(false, false, "C.CHEST", "black", 0, "none", false, 0, 0, 0, 0);
  place b16= place(true, false, "SRINAGAR", "pink", 5000, "none", false, 6000, 550, 8500, 3500);
  place b17= place(false, false, "CLUB", "black", 0, "none", false, 0, 0, 0, 0);
  place b18= place(true, false, "AGRA", "green", 2500, "none", false, 3000, 200, 3500, 900);
  place b19= place(false, false, "CHANCE", "black", 0, "none", false, 0, 0, 0, 0);
  place b20= place(true, false, "PATNA", "green", 2000, "none", false, 2500, 150, 4500, 800);
  place b21= place(true, false, "SIMLA", "green", 2200, "none", false, 3500, 200, 6000, 1000);
  place b22= place(true, false, "DARJEELING", "red", 2500, "none", false, 3000, 200, 5000, 1200);
  place b23= place(true, false, "KOLKATA", "green", 6500, "none", false, 6000, 800, 8000, 3200);
  place b24= place(true, false, "AIRINDIA", "white", 10500, "none", false, 0, 1200, 0, 0);
  place b25= place(true, false, "HYDERABAD", "pink", 3500, "none", false, 5000, 350, 6000, 1200);
  place b26= place(false, false, "RESTHOUSE", "black", 0, "none", false, 0, 0, 0, 0);
  place b27= place(true, false, "MADRAS", "pink", 7000, "none", false, 6500, 950, 8500, 3500);
  place b28= place(false, false, "C.CHEST", "black", 0, "none", false, 0, 0, 0, 0);
  place b29= place(true, false, "BANGALORE", "red", 4000, "none", false, 4500, 400, 5500, 1500);
  place b30= place(false, false, "WEALTHTAX", "black", 0, "none", false, 0, 0, 0, 0);
  place b31= place(true, false, "BANARAS", "pink", 4000, "none", false, 4500, 400, 5500, 1500);
  place b32= place(true, false, "OOTACAMUND", "pink", 2500, "none", false, 3000, 200, 4500, 1000);
  place b33= place(true, false, "MOTOR BOAT", "white", 5500, "none", false, 0, 700, 0, 0);
  //push every place to `board` vector.
  board.push_back(b0);
  board.push_back(b1);
  board.push_back(b2);
  board.push_back(b3);
  board.push_back(b4);
  board.push_back(b5);
  board.push_back(b6);
  board.push_back(b7);
  board.push_back(b8);
  board.push_back(b9);
  board.push_back(b10);
  board.push_back(b11);
  board.push_back(b12);
  board.push_back(b13);
  board.push_back(b14);
  board.push_back(b15);
  board.push_back(b16);
  board.push_back(b17);
  board.push_back(b18);
  board.push_back(b19);
  board.push_back(b20);
  board.push_back(b21);
  board.push_back(b22);
  board.push_back(b23);
  board.push_back(b24);
  board.push_back(b25);
  board.push_back(b26);
  board.push_back(b27);
  board.push_back(b28);
  board.push_back(b29);
  board.push_back(b30);
  board.push_back(b31);
  board.push_back(b32);
  board.push_back(b33);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                   BUILD START!                                                           //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// top most border(0th line)
  string border="";
  for(int i=0; i<211; i++) border += "#";
  AJ[0].push_back(border);
////////////////////////////////////////////////////////////////////////////////
//1st line
  for(int i=0; i<10; i++){
    string onecell = "* ";
    onecell += board[i].name;
    if(board[i].ifplace) onecell += "(" + board[i].color + ")";
    for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
    if(i==9)onecell += "*";
    AJ[1].push_back(onecell);
  }
////////////////////////////////////////////////////////////////////////////////
//2nd line
  for(int i=0; i<10; i++){
    string onecell = "* ";
    if(board[i].ifplace)onecell += "     " + to_string(board[i].price);
    for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
    if(i==9)onecell += "*";
    AJ[2].push_back(onecell);
  }
////////////////////////////////////////////////////////////////////////////////
//3rd line
  for(int i=0; i<10; i++){
    string onecell = "* ";
    if(board[i].ifplace)onecell += " owner: " + board[i].owner;
    for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
    if(i==9)onecell += "*";
    AJ[3].push_back(onecell);
  }
////////////////////////////////////////////////////////////////////////////////
//4th , 5th lines
  for(int i=0; i<10; i++){
    string onecell = "* ";
    for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
    if(i==9)onecell += "*";
    AJ[4].push_back(onecell);
    AJ[5].push_back(onecell);
  }
////////////////////////////////////////////////////////////////////////////////
//6th line and player names goes here
  for(int i=0; i<10; i++){
    string onecell = "* ";
    for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
    if(i==9)onecell += "*";
    AJ[6].push_back(onecell);
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int leftmost = 33, rightmost = 10, level = 0;
while(rightmost < 17){      //the left most ans rightmost places to be inserted into the AJ
    if(level==0)AJ[7+level].push_back(border);        //the bottom border of the first row of places
    //0th line of each place
    else{
      for(int i=0; i<10; i++){
        if(i==0 or i==9){
          AJ[7+level].push_back("#####################");
        }
        else{
          AJ[7+level].push_back(emptystring+" ");
        }
      }
    }
////////////////////////////////////////////////////////////////////////////////
//1st line of each place
    for(int i=0; i<10; i++){
      if(i==0){
        string onecell = "* ";
        onecell += board[leftmost].name;
        if(board[leftmost].ifplace) onecell += "(" + board[leftmost].color + ")";
        for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
        onecell += "#";
        AJ[8+level].push_back(onecell);

      }
      else if(i==9){
        string onecell = "       # ";
        onecell += board[rightmost].name;
        if(board[rightmost].ifplace) onecell += "(" + board[rightmost].color + ")";
        for(int extend=onecell.size(); extend<28; extend++) onecell += " ";
        onecell += "*";
        AJ[8+level].push_back(onecell);
      }
      else{
        AJ[8+level].push_back(emptystring);
      }
    }
////////////////////////////////////////////////////////////////////////////////
//2nd line of each place
    for(int i=0; i<10; i++){
      if(i==0){
        string onecell = "* ";
        if(board[leftmost].ifplace)onecell += "     " + to_string(board[leftmost].price);
        for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
        onecell+="#";
        AJ[9+level].push_back(onecell);
      }
      else if(i==9){
        string onecell = "       # ";
        if(board[rightmost].ifplace)onecell += "     " + to_string(board[rightmost].price);
        for(int extend=onecell.size(); extend<28; extend++) onecell += " ";
        onecell += "*";
        AJ[9+level].push_back(onecell);
      }
      else{
        AJ[9+level].push_back(emptystring);
      }
    }
////////////////////////////////////////////////////////////////////////////////
//3rd line of each place
    for(int i=0; i<10; i++){
      if(i==0){
        string onecell = "* ";
        if(board[leftmost].ifplace)onecell += " owner: " + board[leftmost].owner;
        for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
        onecell+="#";
        AJ[10+level].push_back(onecell);
      }
      //to insert chance and CommunityChest inside the AJ
      else if(i==2){
        if(level==0) AJ[10+level].push_back("              CHANCE");
        else AJ[10+level].push_back(emptystring);
      }
      else if(i==6){
        if(level==0) AJ[10+level].push_back("   COMMUNIY CHEST   ");
        else AJ[10+level].push_back(emptystring);
      }

      else if(i==9){
        string onecell = "       # ";
        if(board[rightmost].ifplace)onecell += " owner: " + board[rightmost].owner;
        for(int extend=onecell.size(); extend<28; extend++) onecell += " ";
        onecell += "*";
        AJ[10+level].push_back(onecell);
      }
      else{
        AJ[10+level].push_back(emptystring);
      }
    }
////////////////////////////////////////////////////////////////////////////////
//4th, 5th lines of each place
    for(int i=0; i<10; i++){
      if(i==0){
        string onecell = "* ";
        for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
        onecell+="#";
        AJ[11+level].push_back(onecell);
        AJ[12+level].push_back(onecell);
      }
      else if(i==9){
        string onecell = "       # ";
        for(int extend=onecell.size(); extend<28; extend++) onecell += " ";
        onecell += "*";
        AJ[11+level].push_back(onecell);
        AJ[12+level].push_back(onecell);
      }
      else{
        AJ[11+level].push_back(emptystring);
        AJ[12+level].push_back(emptystring);
      }
    }
////////////////////////////////////////////////////////////////////////////////
//6th line of each place and player names goes here
    for(int i=0; i<10; i++){
      if(i==0){
        string onecell = "* ";
        for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
        onecell+="#";
        AJ[13+level].push_back(onecell);
      }
      else if(i==9){
        string onecell = "       # ";
        for(int extend=onecell.size(); extend<28; extend++) onecell += " ";
        onecell += "*";
        AJ[13+level].push_back(onecell);
      }
      else{
        AJ[13+level].push_back(emptystring);
      }
    }
////////////////////////////////////////////////////////////////////////////////
//update values to move to next place
  level += 7;
  leftmost--;
  rightmost++;
}
  AJ[level+7].push_back(border);
  level+=7;
  int LEFTMOST = leftmost;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//the bottom most places in the game(in AJ :P)
//1st line
    for(int i=0; i<10; i++){
      string onecell = "* ";
      onecell += board[leftmost].name;
      if(board[leftmost].ifplace) onecell += "(" + board[leftmost].color + ")";
      for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
      if(i==9)onecell += "*";
      leftmost--;
      AJ[1+level].push_back(onecell);
    }
    leftmost = LEFTMOST;
  ////////////////////////////////////////////////////////////////////////////////
  //2nd line
    for(int i=0; i<10; i++){
      string onecell = "* ";
      if(board[leftmost].ifplace)onecell += "     " + to_string(board[leftmost].price);
      for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
      if(i==9)onecell += "*";
      leftmost--;
      AJ[2+level].push_back(onecell);
    }
    leftmost = LEFTMOST;
  ////////////////////////////////////////////////////////////////////////////////
  //3rd line
    for(int i=0; i<10; i++){
      string onecell = "* ";
      if(board[leftmost].ifplace)onecell += " owner: " + board[leftmost].owner;
      for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
      if(i==9)onecell += "*";
      leftmost--;
      AJ[3+level].push_back(onecell);
    }
    leftmost = LEFTMOST;
  ////////////////////////////////////////////////////////////////////////////////
  // 4th, 5th lines
    for(int i=0; i<10; i++){
      string onecell = "* ";
      for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
      if(i==9)onecell += "*";
      AJ[4+level].push_back(onecell);
      AJ[5+level].push_back(onecell);
      // AJ[7].push_back(onecell);
    }
  ////////////////////////////////////////////////////////////////////////////////
  // 6th line and player names goes here
    for(int i=0; i<10; i++){
      string onecell = "* ";
      for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
      if(i==9)onecell += "*";
      AJ[6+level].push_back(onecell);
    }
//////////////////////////////////////////////////////////////////////////////////
    AJ[7+level].push_back(border);        //last border in AJ

//  insert chance and CommunityChest statements in the middle.
    int middle_=1;
    for(int middle = 15; middle<42; middle+=2){
      if(middle % 7 == 0)continue;
      string thischance = to_string(middle_) + chanceorcchest(Chance[middle_]);
      string thiscchest = to_string(middle_) + chanceorcchest(CommunityChest[middle_]);

      AJ[middle][2] = thischance.substr(0,20);
      AJ[middle][3] = thischance.substr(20,20);
      AJ[middle][4] = thischance.substr(40,20);

      AJ[middle][6] = thiscchest.substr(0,20);
      AJ[middle][7] = thiscchest.substr(20,20);
      AJ[middle][8] = thiscchest.substr(40,20);
       middle_++;
    }
//  insert money owned by each player in the middle.
  for(int eachplayer=0; eachplayer<n; eachplayer++){
    string thisplayer = players[eachplayer] + " : " + to_string(moneyowned[players[eachplayer]]);
    for(int extend=thisplayer.size(); extend<20; extend++) thisplayer += " ";
    AJ[52][eachplayer+2] = thisplayer;
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                   BUILD COMPLETE!                                                        //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//initially, every player is in the START.
  string startgame = "* ";
  for(int pla=0; pla<n; pla++){
    startgame += players[pla] + " ";
  }
  for(int extend=startgame.size(); extend<21; extend++) startgame += " ";
  AJ[6][0] = startgame;
  for(int i=0; i<66; i++){
    for(int j=0; j<AJ[i].size(); j++){
      cout<<AJ[i][j];
    }
    cout<<endl;
  }
  // The actual game...:)
  int playerturn  = 0;
  while(true){
    playerturn = playerturn % n;
    while(moneyowned[players[playerturn]] < 0){
      int valonboard, toberemoved;
      if(placesowned[players[playerturn]].size() > 0){
        vector<int>::iterator rem;
        cout<<"Hey "<<players[playerturn]<<"! You have negative balance. You must sell any of the places you own.\n";
        cout<<"Your places are : \n";
        for(auto & it : placesowned[players[playerturn]]){
          cout<<board[it].name<<"---"<<it<<endl;
        }
        cout<<"Enter a number corresponding to place that you are gonna sell : ";
        int tobesold, checkifvalid=0;
    reentertobesold :  cin>>tobesold;
        for(int noofplaces=0; noofplaces<placesowned[players[playerturn]].size(); noofplaces++){
          if(tobesold == placesowned[players[playerturn]][noofplaces]) {
            checkifvalid++;
            toberemoved = tobesold;
            rem = placesowned[players[playerturn]].begin()+noofplaces;
            break;
          }
        }
        if(checkifvalid == 0) {
          cout<<"Enter only the place's number which you own : ";
          goto reentertobesold;
        }
        else{
          valonboard = toberemoved;
          // cout<<"\n##test## valonboard="<<valonboard<<", toberemoved="<<toberemoved<<endl;
          board[valonboard].owner = "none";
          if(board[valonboard].hotel) {
            board[valonboard].hotel = false;
            hotelsowned[players[playerturn]]--;
          }
          if(board[valonboard].house){
            board[valonboard].house = false;
            housesowned[players[playerturn]]--;
          }
          if(board[valonboard].color != "white"){
            colorsowned[players[playerturn]][board[valonboard].color]--;
            if(board[valonboard].hotel or board[valonboard].house)
              moneyowned[players[playerturn]] += board[valonboard].hotelprice;
          }
          moneyowned[players[playerturn]] += board[valonboard].price / 2;

          string changeowner;
          if(valonboard>=10 and valonboard<17)changeowner = "       # ";
          else changeowner = "* ";
          changeowner += " owner: none";
          if(valonboard>=10 and valonboard<17) {
            for(int extend=changeowner.size(); extend<28; extend++) changeowner += " ";
            changeowner += "*";
          }
          else if(valonboard>26 and valonboard<34) {
            for(int extend=changeowner.size(); extend<21; extend++) changeowner += " ";
            changeowner += "#";
          }
          else for(int extend=changeowner.size(); extend<21; extend++) changeowner += " ";
          int remx, remy;
          // remx = toberemoved; cout<<"\ntest#1 : toberemoved : "<<toberemoved<<endl;
          remy = 6;
          if(toberemoved>26 and toberemoved<34) {remx = 0; remy = 7 * (1 + 34 - toberemoved) + 1 -2;}
          if(toberemoved>=17 and toberemoved<=26) {remx = 26 - toberemoved; remy = 62; }
          if(toberemoved>=10 and toberemoved<17) {remx = 9; remy = 7 * (toberemoved - 8) + 1-2;}
          if(toberemoved<10 and toberemoved>=0) {remx = toberemoved; remy = 6;}

          AJ[remy-3][remx] = changeowner;
          for(int eachplayer=0; eachplayer<n; eachplayer++){
            string thisplayer = players[eachplayer] + " : " + to_string(moneyowned[players[eachplayer]]);
            for(int extend=thisplayer.size(); extend<20; extend++) thisplayer += " ";
            AJ[52][eachplayer+2] = thisplayer;
          }
          for(int i=0; i<65; i++){
            for(int j=0; j<AJ[i].size(); j++){
              cout<<AJ[i][j];
            }
            cout<<endl;
          }
        }
        placesowned[players[playerturn]].erase(rem);
      }
      else{
        vector<string>::iterator rmplayer;
        rmplayer = players.begin() + playerturn;
        cout<<"Hey "<<players[playerturn]<<"! Your are out of the Game!\n";
        colorsowned.erase(players[playerturn]);
        placesowned.erase(players[playerturn]);
        hotelsowned.erase(players[playerturn]);
        housesowned.erase(players[playerturn]);
        moneyowned.erase(players[playerturn]);

        string removehim;
        int remx, remy;
        toberemoved = position[players[playerturn]];
        remx = toberemoved;
        // cout<<"\ntoberemoved = "<<toberemoved<<endl;
        remy = 6;
        if(toberemoved>26 and toberemoved<34) {remx = 0; remy = 7 * (1 + 34 - toberemoved) + 1 -2;}
        if(toberemoved>=17 and toberemoved<=26) {remx = 26 - toberemoved; remy = 62; }
        if(toberemoved>=10 and toberemoved<17) {remx = 9; remy = 7 * (toberemoved - 8) + 1-2;}
        if(toberemoved<10 and toberemoved>=0) {remx = toberemoved; remy = 6;}
        if(toberemoved>=10 and toberemoved<17)removehim = "       # ";
        else removehim = "* ";
        vector<string> previplayers = split(AJ[remy][remy], ' ');
        for(auto &prevpl : previplayers){
          if(prevpl!=players[playerturn] and prevpl!="*" and prevpl!="#") removehim += prevpl + " ";
        }
        if(valonboard>=10 and valonboard<17) {
          for(int extend=removehim.size(); extend<28; extend++) removehim += " ";
          removehim += "*";
        }
        else if(valonboard>26 and valonboard<34) {
          for(int extend=removehim.size(); extend<21; extend++) removehim += " ";
          removehim += "#";
        }
        else for(int extend=removehim.size(); extend<21; extend++) removehim += " ";

        AJ[remy][remx] = removehim;
        position.erase(players[playerturn]);
        players.erase(rmplayer);

        if(players.size() == 1){
          cout<<"\n\nHOLA! "<<players[0]<<" IS THE WINNER.\n\n";
          return 0;
        }
        else {
          // playerturn++;
          n--;
          AJ[52][2+n] = emptystring;
          for(int eachplayer=0; eachplayer<n; eachplayer++){
            string thisplayer = players[eachplayer] + " : " + to_string(moneyowned[players[eachplayer]]);
            for(int extend=thisplayer.size(); extend<20; extend++) thisplayer += " ";
            AJ[52][eachplayer+2] = thisplayer;
          }
          for(int i=0; i<65; i++){
            for(int j=0; j<AJ[i].size(); j++){
              cout<<AJ[i][j];
            }
            cout<<endl;
          }
        }
      }
    }

    string diceval;

    cout<<"Hey "<<players[playerturn]<<"! It's your turn. Throw the dice and enter the number on it. Number : ";
    cin>>diceval;
    int onethrow = isNumber(diceval) ? stoi(diceval) : 0;
    if(onethrow == 99){
      for(int i=0; i<66; i++){
        for(int j=0; j<AJ[i].size(); j++){
          cout<<AJ[i][j];
        }
        cout<<endl;
      }
      playerturn++;
    }
    else if(onethrow>12 or onethrow<=0) cout<<"ENTER A VALID NUMBER! {1-12}\n";
    else{

        int prevposition = position[players[playerturn]];
        int prevx, prevy;
        prevx = prevposition;
        prevy = 6;
        if(prevposition>26 and prevposition<34) {prevx = 0; prevy = 7 * (1 + 34 - prevposition) + 1 - 2;}
        if(prevposition>=17 and prevposition<=26) {prevx = 26 - prevposition; prevy = 62;}
        if(prevposition>=10 and prevposition<17) {prevx = 9; prevy = 7 * (prevposition - 8) + 1 - 2;}
        if(prevposition<10 and prevposition>=0) {prevx = prevposition; prevy = 6;}
        ////////////////////////////////////////////////////////////////////////

        position[players[playerturn]] += onethrow;
        int ifcrossedstart = position[players[playerturn]];   //to check if a player crossed the START later
        position[players[playerturn]] = (position[players[playerturn]]) % 34;
        int currentpos = position[players[playerturn]];
        ///////////////////////////////////////////////////////////////////
        //if a player crosses START//
        if(ifcrossedstart>33){
           cout<<"Hey "<<players[playerturn]<<"! collect 1500/- from bank as you crossed start.\n";
           moneyowned[players[playerturn]] += 1500;
        }
        if(!(board[currentpos].ifplace)){
          if(board[currentpos].name == "INCOMETAX"){
            cout<<"Hey "<<players[playerturn]<<"! pay the income tax."<<endl;
            moneyowned[players[playerturn]] -= 100;
           }
          if(board[currentpos].name == "WEALTHTAX"){
            cout<<"Hey "<<players[playerturn]<<"! pay the wealth tax."<<endl;
             moneyowned[players[playerturn]] -= 100;
           }
          if(board[currentpos].name == "CLUB"){
            cout<<"Hey "<<players[playerturn]<<"! pay the bill in the club before going out."<<endl;
            moneyowned[players[playerturn]] -= 100;
          }
          if(board[currentpos].name == "RESTHOUSE"){
            cout<<"Hey "<<players[playerturn]<<"! pay the rent for resthouse before going out."<<endl;
            moneyowned[players[playerturn]] -= 100;
          }
          if(board[currentpos].name == "JAIL"){
            cout<<"Hey "<<players[playerturn]<<"! pay the fine of 250/- for your crime."<<endl;
            moneyowned[players[playerturn]] -= 250;
          }
          if(board[currentpos].name == "CHANCE") {
            cout<<Chance[onethrow]<<endl;
            switch (onethrow) {
              case 1 : {for(int chance1=0; chance1<n; chance1++){
                          if(chance1 != playerturn) moneyowned[players[chance1]] += 50;
                        }
                        moneyowned[players[playerturn]] -= 50*(n-1);
                        break;
                      }
              case 2 : moneyowned[players[playerturn]] -= 850; break;
              case 3 : moneyowned[players[playerturn]] += 800; break;
              case 4 : moneyowned[players[playerturn]] -= 250; break;
              case 5 : moneyowned[players[playerturn]] += 1350; break;
              case 6 : moneyowned[players[playerturn]] -= 700; break;
              case 7 : moneyowned[players[playerturn]] += 2000; break;
              case 8 : moneyowned[players[playerturn]] -= 200 * (hotelsowned[players[playerturn]] + housesowned[players[playerturn]]);
                       break;
              case 9 : moneyowned[players[playerturn]] += 2200; break;
              case 10 : { currentpos = 9;
                          position[players[playerturn]] = 9;
                          moneyowned[players[playerturn]] += 800;
                          break;
                        }
              case 11 : moneyowned[players[playerturn]] += 1250; break;
              case 12 : { currentpos = 26;
                          position[players[playerturn]] = 26;
                          moneyowned[players[playerturn]] -= 100;
                          break;
                        }
            }
          }
          if(board[currentpos].name == "C.CHEST") {
            cout<<CommunityChest[onethrow]<<endl;
            switch (onethrow) {
              case 1 : {  for(int chance1=0; chance1<n; chance1++){
                            if(chance1 != playerturn) moneyowned[players[chance1]] += 100;
                          }
                          moneyowned[players[playerturn]] -= 100*(n-1);
                          currentpos = 17;
                          position[players[playerturn]] = 17;
                          break;
                        }
              case 2 : {  moneyowned[players[playerturn]] += 250*(n-1);
                          for(int chance1=0; chance1<n; chance1++){
                              if(chance1 != playerturn) moneyowned[players[chance1]] -= 250;
                            }
                            break;
                        }
              case 3 : {  currentpos = 9;
                          position[players[playerturn]] = 9;
                          moneyowned[players[playerturn]] -= 500;
                          break;
                      }
              case 4 : moneyowned[players[playerturn]] += 850; break;
              case 5 : moneyowned[players[playerturn]] -= 1000; break;
              case 6 : moneyowned[players[playerturn]] += 1250; break;
              case 7 : moneyowned[players[playerturn]] -= 2000; break;
              case 8 : moneyowned[players[playerturn]] += 1200; break;
              case 9 : moneyowned[players[playerturn]] -= 1500; break;
              case 10 : moneyowned[players[playerturn]] += 750; break;
              case 11 : moneyowned[players[playerturn]] -= 200*(hotelsowned[players[playerturn]]); break;
              case 12 : moneyowned[players[playerturn]] += 700; break;
            }
          }
        }
          ////////////////////////////////////////////////////////////////////////
          int presx, presy;
          presx = currentpos;
          presy = 6;
          if(currentpos>26 and currentpos<34) {presx = 0; presy = 7 * (1 + 34 - currentpos) + 1 -2;}
          if(currentpos>=17 and currentpos<=26) {presx = 26 - currentpos; presy = 62; }
          if(currentpos>=10 and currentpos<17) {presx = 9; presy = 7 * (currentpos - 8) + 1-2;}
          if(currentpos<10 and currentpos>=0) {presx = currentpos; presy = 6;}

        /////////////////////////////////////////////////////////////////////////
       ///                   FOR MOVING THE NAMES                             //
      /////////////////////////////////////////////////////////////////////////
      ////  updating previous position  ////
      string previousstring = AJ[prevy][prevx], previous;
      vector<string> prevplayers, actualprevplayers;
      prevplayers = split(previousstring,' ');
        if(prevposition>=10 and prevposition<17) previous = "       # ";
        else previous = "* ";
        int numberofplayers = 0;
        for(auto forcounting=0; forcounting<prevplayers.size(); forcounting++){
          for(auto ifaplayer =0; ifaplayer<n; ifaplayer++){
            if(prevplayers[forcounting] == players[ifaplayer]) {
              numberofplayers++;
              actualprevplayers.push_back(prevplayers[forcounting]);
            }
          }
        }
        for(int inserting=0; inserting<numberofplayers; inserting++){
          if(actualprevplayers[inserting] != players[playerturn]) previous += actualprevplayers[inserting] + " ";
        }

        if(prevposition>9 and prevposition<17) {
          for(int extend=previous.size(); extend<28; extend++) previous += " ";
          previous += "*";
        }
        else if(prevposition>26 and prevposition<34){
          for(int extend=previous.size(); extend<21; extend++) previous += " ";
          previous += "#";
        }
        else{
        for(int extend=previous.size(); extend<21; extend++) previous += " ";
        if(prevposition == 9 or prevposition == 17) previous += "*";
      }
        AJ[prevy][prevx] = previous;
        ////  updated previous cell  ////
        ////  updating present cell ////
        string presentstring = AJ[presy][presx], present;
        vector<string> presentplayers, actualpresentplayers;
        presentplayers = split(presentstring,' ');

        if(currentpos>=10 and currentpos<17) present = "       # ";
        else present = "* ";
        numberofplayers = 0;
        for(auto forcounting=0; forcounting<prevplayers.size(); forcounting++){
          for(auto ifaplayer =0; ifaplayer<n; ifaplayer++){
            if(presentplayers[forcounting] == players[ifaplayer]) {
              numberofplayers++;
              actualpresentplayers.push_back(players[ifaplayer]);
            }
          }
        }
        for(int inserting=0; inserting<numberofplayers; inserting++){
          present += actualpresentplayers[inserting] + " ";
        }
        present += players[playerturn];
        if(currentpos>9 and currentpos<17) {
          for(int extend=present.size(); extend<28; extend++) present += " ";
          present += "*";
        }
        else if(currentpos>26 and currentpos<34){
          for(int extend=present.size(); extend<21; extend++) present += " ";
          present += "#";
        }
        else {
          for(int extend=present.size(); extend<21; extend++) present += " ";
          if(currentpos == 9 or currentpos == 17) present += "*";
        }

        AJ[presy][presx] = present;
        ////  present position updated ////
    //////////////////////////////////////////// CONDITION CHECK //////////////////////////////////////////////

        //print the AJ(the monopoly board)
        //update money status of players if they fall on any non place cells
        for(int eachplayer=0; eachplayer<n; eachplayer++){
          string thisplayer = players[eachplayer] + " : " + to_string(moneyowned[players[eachplayer]]);
          for(int extend=thisplayer.size(); extend<20; extend++) thisplayer += " ";
          AJ[52][eachplayer+2] = thisplayer;
        }
          if(board[currentpos].ifplace){
            //if a place is unbought
          if(board[currentpos].owner == "none"){
              for(int i=0; i<65; i++){
                for(int j=0; j<AJ[i].size(); j++){
                  cout<<AJ[i][j];
                }
                cout<<endl;
              }

            if(moneyowned[players[playerturn]] < board[currentpos].price){
              cout<<"YOU DO NOT HAVE ENOUGH FUNDS TO BUY THIS PLACE.\n";
            }
            else{
              cout<<"Hey "<<players[playerturn]<<"! Would you like to buy this?["<<board[currentpos].name<<"] enter y or n : ";
              string willingtobuy;
              cin>>willingtobuy;
              if(willingtobuy == "y"){
                placesowned[players[playerturn]].push_back(currentpos);
                board[currentpos].owner = players[playerturn];    //update the owner
                moneyowned[players[playerturn]] -= board[currentpos].price;
                if(board[currentpos].color != "white"){
                  if(moneyowned[players[playerturn]] < board[currentpos].hotelprice){
                    cout<<"YOU DO NOT HAVE ENOUGH FUNDS TO BUILD A HOTEL/HOUSE.\n";
                  }
                  else{
                    if(hotelsowned[players[playerturn]] > 8 and housesowned[players[playerturn]] > 8){
                      cout<<"As you have 8 hotels and 8 houses already, no more are allowed to be built.\n";
                    }
                    else{
                      cout<<"Hey "<<players[playerturn]<<"! Would you like to build a HOTEL(enter h) or a HOUSE(enter x) in this?[";
                      cout<<board[currentpos].name<<"]. Price:"<<board[currentpos].hotelprice<<" (enter s to skip): ";
                      string ishotel;

              re_enter:   cin>>ishotel;

                      if(ishotel=="h") {
                        if(hotelsowned[players[playerturn]] > 8){
                          cout<<"You have 8 hotels already. Try house or skip. Enter your choice : ";
                          goto re_enter;
                        }
                        else{
                          board[currentpos].hotel = true;
                          moneyowned[players[playerturn]] -= board[currentpos].hotelprice;
                          hotelsowned[players[playerturn]] ++;
                        }
                      }
                      if(ishotel=="x") {
                        if(housesowned[players[playerturn]] > 8){
                          cout<<"You have 8 houses already. Try hotel or skip. Enter your choice : ";
                          goto re_enter;
                        }
                        else{
                        board[currentpos].house = true;
                        moneyowned[players[playerturn]] -= board[currentpos].hotelprice;
                        housesowned[players[playerturn]] ++;
                      }
                    }
                    colorsowned[players[playerturn]][board[currentpos].color] ++;
                  }
                }
              }
                // update the owner string in the AJ
                string changeowner;
                if(currentpos>=10 and currentpos<17)changeowner = "       # ";
                else changeowner = "* ";
                changeowner += " owner: " + players[playerturn];
                if(board[currentpos].hotel)changeowner += "[H]";
                if(board[currentpos].house)changeowner += "[^]";
                if(currentpos>=10 and currentpos<17) {
                  for(int extend=changeowner.size(); extend<28; extend++) changeowner += " ";
                  changeowner += "*";
                }
                else if(currentpos>26 and currentpos<34) {
                  for(int extend=changeowner.size(); extend<21; extend++) changeowner += " ";
                  changeowner += "#";
                }
                else for(int extend=changeowner.size(); extend<21; extend++) changeowner += " ";
                AJ[presy-3][presx] = changeowner;
            }
          }
        }
          //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          // if a place is bought by another player
          else{
            //if the player lands on a place whose owner is another player
            if(players[playerturn] != board[currentpos].owner){
              int totalrent;
              //white cards are different apart from the non white ones.
              // Having a specific pair of white cards doubles the rent
              if(board[currentpos].color == "white"){   //evaluate rent for the hite cards
                if(currentpos == 2 or currentpos == 24){
                  totalrent = (board[2].owner == board[24].owner) ? 2*(board[currentpos].rent) : board[currentpos].rent;
                }
                if(currentpos == 13 or currentpos == 33){
                  totalrent = (board[13].owner == board[33].owner) ? 2*(board[currentpos].rent) : board[currentpos].rent;
                }
                if(currentpos == 3 or currentpos == 12){
                  totalrent = (board[3].owner == board[12].owner) ? 2*(board[currentpos].rent) : board[currentpos].rent;
                }
              }
              //evaluate rent for non white cards
              else{
                totalrent = (board[currentpos].hotel or board[currentpos].house) ? 0 : board[currentpos].rent;
                totalrent += (board[currentpos].hotel ? board[currentpos].hotelrent : 0) + (board[currentpos].house ? board[currentpos].houserent : 0);
                //if a player has 3 or more places(cards) of same color, the rent doubles
                if(colorsowned[board[currentpos].owner][board[currentpos].color] >= 3) totalrent *= 2;
              }
              // output the total rent of the current place
              cout<<"Hey "<<players[playerturn]<<"! pay the rent of "<<totalrent<<"/- to "<<board[currentpos].owner<<" for coming to his place"<<endl;
              moneyowned[players[playerturn]] -= totalrent;
              moneyowned[board[currentpos].owner] += totalrent;
            }
            //if the player lands on a place whose owner is the same player
            else{
              cout<<"Welcome "<<players[playerturn]<<" to your place["<<board[currentpos].name<<"]. Have a nice stay!\n";
              //if a player already bought this place but not any hotels and houses,
              if(!(board[currentpos].house or board[currentpos].hotel)){
                if(board[currentpos].color != "white"){
                  cout<<"Hey "<<players[playerturn]<<"! Would you like to build a HOTEL(enter h) or a HOUSE(enter x) in this?["<<board[currentpos].name<<"] (enter s to skip): ";
                  string ishotel;
                  cin>>ishotel;
                  if(ishotel=="h") {
                    board[currentpos].hotel = true;
                    moneyowned[players[playerturn]] -= board[currentpos].hotelprice;
                    hotelsowned[players[playerturn]] ++;
                  }
                  if(ishotel=="x") {
                    board[currentpos].house = true;
                    moneyowned[players[playerturn]] -= board[currentpos].hotelprice;
                    housesowned[players[playerturn]] ++;
                  }
                }
              }
            }
          }
        }
    cout<<endl;
//////////////////////////calculations done/////////////////////////////
//  insert money owned by each player in the middle.
  for(int eachplayer=0; eachplayer<n; eachplayer++){
    string thisplayer = players[eachplayer] + " : " + to_string(moneyowned[players[eachplayer]]);
    for(int extend=thisplayer.size(); extend<20; extend++) thisplayer += " ";
    AJ[52][eachplayer+2] = thisplayer;
  }
////////////////////////////////////////// PRINT FINAL ONE ////////////////////////////////////
    for(int i=0; i<65; i++){
      for(int j=0; j<AJ[i].size(); j++){
        cout<<AJ[i][j];
      }
      cout<<endl;
    }
    playerturn++;   //this increment gives the chance to next player.
  }
}
  return 0;
}
