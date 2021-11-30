#include "global.hpp"
#include "GameFunctions.hpp"
#include "HelperFunctions.hpp"

int getNumberOfPlayers(string N){
    int n;
    cout<<"Enter the number of players(atleast 2 & not more than 4) : ";
    No_of_Players:  cin>>N;
    while(!(isNumber(N))){
        cout<<"Please enter a number : ";
        cin>>N;
    }
    n = stoi(N);
    if(n<2){
        cout<<"Enter atleast 2 : ";
        goto No_of_Players;
    }
    if(n>4){
        n=4;
        cout<<"Since you have entered a number greater than 4, only first four players are assumed to be in the game.\n";
    }

    return n;
}

void initializeChance(unordered_map<int, string> &Chance){
    // chance statements
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
}
void initializeCommunityChest(unordered_map<int, string> &CommunityChest){
    // CommunityChest statements:
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
}

void initializePlaces(vector<place> &board){
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
}

void constructBoard(vector<vector<string>> &AJ, vector<place> &board, vector<string> &players, unordered_map<string, long> &moneyowned,
        int n, unordered_map<int, string> &Chance, unordered_map<int, string> &CommunityChest){

    // top most border(0th line)
    string border="";
    for(int i=0; i<211; i++) border += "#";
    AJ[0].push_back(border);
    
    //1st line
    for(int i=0; i<10; i++){
        string onecell = "* ";
        onecell += board[i].name;
        if(board[i].ifplace) onecell += "(" + board[i].color + ")";
        for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
        if(i==9)onecell += "*";
        AJ[1].push_back(onecell);
    }
    
    //2nd line
    for(int i=0; i<10; i++){
        string onecell = "* ";
        if(board[i].ifplace)onecell += "     " + to_string(board[i].price);
        for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
        if(i==9)onecell += "*";
        AJ[2].push_back(onecell);
    }
    
    //3rd line
    for(int i=0; i<10; i++){
        string onecell = "* ";
        if(board[i].ifplace)onecell += " owner: " + board[i].owner;
        for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
        if(i==9)onecell += "*";
        AJ[3].push_back(onecell);
    }
    
    //4th , 5th lines
    for(int i=0; i<10; i++){
        string onecell = "* ";
        for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
        if(i==9)onecell += "*";
        AJ[4].push_back(onecell);
        AJ[5].push_back(onecell);
    }
    
    //6th line and player names goes here
    for(int i=0; i<10; i++){
        string onecell = "* ";
        for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
        if(i==9)onecell += "*";
        AJ[6].push_back(onecell);
    }
    
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
    
    //update values to move to next place
    level += 7;
    leftmost--;
    rightmost++;
    }
    AJ[level+7].push_back(border);
    level+=7;
    int LEFTMOST = leftmost;
    
    //the bottom most places in the game
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
    
    // 4th, 5th lines
        for(int i=0; i<10; i++){
        string onecell = "* ";
        for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
        if(i==9)onecell += "*";
        AJ[4+level].push_back(onecell);
        AJ[5+level].push_back(onecell);
        // AJ[7].push_back(onecell);
        }
    
    // 6th line and player names goes here
        for(int i=0; i<10; i++){
        string onecell = "* ";
        for(int extend=onecell.size(); extend<21; extend++) onecell += " ";
        if(i==9)onecell += "*";
        AJ[6+level].push_back(onecell);
        }
    
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
}