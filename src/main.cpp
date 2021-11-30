#include "global.hpp"
#include "PlaceClass.hpp"
#include "HelperFunctions.hpp"
#include "GameFunctions.hpp"

int main(){

    // Dice generator to be opened in another terminal
    int new_terminal = system("x-terminal-emulator -e \"./dicegenerator\"");
    PrintInstructions();

    string N;
    int n = getNumberOfPlayers(N);

    vector<string>players;
    //FINAL BOARD which is printed in the terminal.
    vector<vector<string>> AJ(70);      //  (it's AJ coz, I am AJAY :o)
    vector<place> board;
    unordered_map<string, int> position;              //positions of players
    unordered_map<int, string> Chance;
    unordered_map<int, string> CommunityChest;
    unordered_map<string, unordered_map<string, int>> colorsowned;
    unordered_map<string, vector<int>> placesowned;
    unordered_map<string, long> moneyowned;
    unordered_map<string, int> hotelsowned;
    unordered_map<string, int> housesowned;

    // get players' info
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
    cout << "\n\n";
    
    initializeChance(Chance);
    initializeCommunityChest(CommunityChest);
    
    // initialization of the game board
    initializePlaces(board);
    constructBoard(AJ, board, players, moneyowned, n, Chance, CommunityChest);

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
            cout<<"Hey "<<players[playerturn]<<"! Your are out of the Game! Bye Bye...\n";
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

        cout<<"Hey "<<players[playerturn]<<"! It's your turn. You are currently in <";
        cout<<board[position[players[playerturn]]].name<<">. Throw the dice and enter the number on it. Number : ";
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
            
            ///// CONDITION CHECK ////////

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
                cout<<"Hey "<<players[playerturn]<<"! pay the rent of "<<totalrent<<"/- to "<<board[currentpos].owner<<" for coming to his place ["<<board[currentpos].name<<"]\n";
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