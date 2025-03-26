#include <iostream>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"
#include <string>
#include <fstream>

//need to implement printing the dealers hand 
using namespace std;


class Game {
 public:
  Game(int ptstowin, bool shuffle, std::istream &is, string names[]) 
  : ptstowin(ptstowin), shuffl(shuffle){
    pack = Pack(is);

    std::vector<Player*> playrs;
    for (size_t i = 0; i < numplayers; ++i){
        playrs.push_back(Player_factory(names[i], names[i+4]));
    }
    players = playrs;

    hand = 0;
    scoret1 = 0;
    scoret2 = 0;
    dealer = 0;

    Card c(TWO, DIAMONDS);
    upcard = c;

    Suit s = DIAMONDS;
    trump = s;

    orderupteam = -1;
  };


  void play(){
    while (scoret1 < ptstowin && scoret2 < ptstowin){//loops every hand
        cout << "Hand " << hand << endl;
        shuffle();
        deal();//this breaks
        make_trump();
        cout << "\n" << endl;
        play_hand();
        dealer = (dealer + 1) % 4;
        ++hand;
    }
    if (scoret1 > scoret2){
      cout << players[0]->get_name() << 
      " and " << players[2]->get_name() << " win!" << endl;
    }
    else {
      cout << players[1]->get_name() << 
      " and " << players[3]->get_name() << " win!" << endl;
    }
    

    for (size_t i = 0; i < numplayers; ++i) {
      delete players[i];
    }
  };

 private:
  std::vector<Player*> players;
  static const int numplayers = 4;
  Pack pack;
  int ptstowin;
  bool shuffl;
  int hand; 
  int scoret1;
  int scoret2;
  int dealer;
  Card upcard;
  Suit trump;
  int orderupteam;


  // ...

  void shuffle(){
    if (shuffl){
      pack.shuffle();
    }
    else {
        pack.reset();
    }
  };



  void deal(){
    cout << players[dealer]->get_name() << " deals" << endl;
    for (size_t i = 0; i < numplayers; ++i){
        for (int j = 0; j < (i+1) % 2 + 2; j ++){
            players[(dealer + 1 + i) % 4]->add_card(pack.deal_one());       
        }
    }

    for (size_t i = 0; i < numplayers; ++i){
        for (int j = 0; j < (i) % 2 + 2; j ++){
            players[(dealer + 1 + i) % 4]->add_card(pack.deal_one());       
        }
    }
    upcard = pack.deal_one(); 
    cout << upcard << " turned up" << endl;  
  };

  void trump_helper(size_t i, int round){
    cout <<  players[(dealer + 1 + i) % 4]->get_name()
    << " orders up " << trump << endl;
    if (round == 1){
      players[(dealer) % 4] -> add_and_discard(upcard);
    }
    orderupteam =(dealer + 1 + i) % 4;
  };
  //double check this is ok
  void make_trump(){
    bool madetrump = false;
    int round = 1;
    bool isdealer = false;
    for (size_t i = 0; i < numplayers * 2; ++i){
      if (i > 3){
        round = 2;
      }
      if ((i % 4) == dealer){
        isdealer = true;
      }
      else {
        isdealer = false;
      }
      madetrump = 
          players[(dealer + 1 + i) % 4]->make_trump(upcard, isdealer, round, trump);
          if (madetrump){
              trump_helper(i, round);
              break;
          }
          else {
             cout << players[(dealer + 1 + i) % 4]->get_name()
              << " passes" << endl;
          }

    }
  };

  




void hand_helper(int t1, int t2){
  if (orderupteam % 2 == 0){//t1 made trump
      if (t1 == 5){
          scoret1 = scoret1 + 2;
          cout << players[0]->get_name() << " and " << 
          players[2]->get_name() << " win the hand" << endl;
          cout << "march!" << endl;
      }
      else if (t1 == 3 || t1 == 4){
          scoret1 = scoret1 + 1;
          cout << players[0]->get_name() << " and " << 
          players[2]->get_name() << " win the hand" << endl;
      }
      else {
          scoret2 = scoret2 + 2;
          cout << players[1]->get_name() << " and " << 
          players[3]->get_name() << " win the hand" << endl;
          cout << "euchred!" << endl;;
      }
  }
  else{//t2 made trump
      if (t2 == 5){
          scoret2 = scoret2 + 2;
          cout << players[1]->get_name() << " and " << 
          players[3]->get_name() << " win the hand" << endl;
          cout << "march!" << endl;
      }
      else if (t2 == 3 || t2 == 4){
          scoret2 = scoret2 + 1;
          cout << players[1]->get_name() << " and " << 
          players[3]->get_name() << " win the hand" << endl;
      }
      else {
          scoret1 = scoret1 + 2;
          cout << players[0]->get_name() << " and " << 
          players[2]->get_name() << " win the hand" << endl;
          cout << "euchred!" << endl;
      }
  }
};

  void play_hand(){
    int t1 = 0;
    int t2 = 0;
    int leader = (dealer + 1) % 4;
    for (size_t t = 0; t < 5; ++t){
        Card led0 = players[leader % 4]->lead_card(trump);
        cout << led0 << " led by " << 
        players[leader % 4]->get_name() << endl;
        Card led1 = players[(leader + 1) % 4]->play_card(led0, trump);
        cout << led1 << " played by " << 
        players[(leader + 1) % 4]->get_name() << endl;
        Card led2 = players[(leader + 2) % 4]->play_card(led0, trump);
        cout << led2 << " played by " << 
        players[(leader + 2) % 4]->get_name() << endl;        
        Card led3 = players[(leader + 3) % 4]->play_card(led0, trump);
        cout << led3 << " played by " << 
        players[(leader + 3) % 4]->get_name() << endl;
        

        Card pile[4] = {led0, led1, led2, led3};

        int largest = 0;

        for (size_t i = 0; i < 4; ++i){
            if (Card_less(pile[largest], pile[i], led0, trump)){
                largest = i;
            }
        }
        cout << players[(leader + largest) % 4]->get_name() 
        << " takes the trick" << endl;

        leader = (leader + largest) % 4;

        if (leader % 2 == 0){
            ++t1;
        }
        else {
            ++t2;
        }
        cout << "\n" << endl;
    }



    /*if (orderupteam % 2 == 0){//t1 made trump
        if (t1 == 5){
            scoret1 = scoret1 + 2;
            cout << players[0]->get_name() << " and " << 
            players[2]->get_name() << " win the hand" << endl;
            cout << "march!" << endl;
        }
        else if (t1 == 3 || t1 == 4){
            scoret1 = scoret1 + 1;
            cout << players[0]->get_name() << " and " << 
            players[2]->get_name() << " win the hand" << endl;
        }
        else {
            scoret2 = scoret2 + 2;
            cout << players[1]->get_name() << " and " << 
            players[3]->get_name() << " win the hand" << endl;
            cout << "euchred!" << endl;;
        }
    }
    else{//t2 made trump
        if (t2 == 5){
            scoret2 = scoret2 + 2;
            cout << players[1]->get_name() << " and " << 
            players[3]->get_name() << " win the hand" << endl;
            cout << "marched!" << endl;
        }
        else if (t2 == 3 || t2 == 4){
            scoret2 = scoret2 + 1;
            cout << players[1]->get_name() << " and " << 
            players[3]->get_name() << " win the hand" << endl;
        }
        else {
            scoret1 = scoret1 + 2;
            cout << players[0]->get_name() << " and " << 
            players[2]->get_name() << " win the hand" << endl;
            cout << "euchred!" << endl;
        }
    }*/
   hand_helper(t1, t2);

  /*cout << players[0]->get_name() << " and " << 
  players[2]->get_name() << " have " << scoret1 << " points" << endl;
  cout << players[1]->get_name() << " and " << 
  players[3]->get_name() << " have " << scoret2 << " points" << endl;
  cout << "\n" << endl;*/
  print_score();
  };

void print_score(){
  cout << players[0]->get_name() << " and " << 
  players[2]->get_name() << " have " << scoret1 << " points" << endl;
  cout << players[1]->get_name() << " and " << 
  players[3]->get_name() << " have " << scoret2 << " points" << endl;
  cout << "\n" << endl;
};

};



void print_err(){
  cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
}

int main(int argc, char** argv) {
  if (argc != 12){
    print_err();
    return -1;
  }

  if (stoi(argv[3]) > 100 || stoi(argv[3]) < 1){
    print_err();
    return -2;
  }

  string shuffle_option = argv[2];
  if (shuffle_option != "shuffle" && shuffle_option != "noshuffle"){
    print_err();
    return -3;
  }

  for (int i = 0; i < 4; ++i){
    std::string playeroption = argv[i*2 +5];
    if (playeroption != "Simple" && playeroption != "Human"){
      print_err();
      return -3;
    }
  }

  std::ifstream file(argv[1]);
    if (!file) {
        cout << "Error opening " << argv[1] << endl;
        return -4;
    }

    bool shuff = false;

    if (shuffle_option == "shuffle"){
        shuff = true;
    }

  string info[] = {argv[4], argv[6], argv[8], 
  argv[10], argv[5], argv[7], argv[9], argv[11]};

  for (int i = 0; i < 12; ++i){
    cout << argv[i] << " ";
  }
  cout << endl;

  Game game(stoi(argv[3]), shuff, file, info);
  game.play();

  return 0;

}