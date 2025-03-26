#include "Player.hpp"
#include <cassert>
#include <algorithm>

using namespace std;

class Simple: public Player{
    private:
      const string name;
      vector<Card> hand;

    public:
        Simple(std::string name) : name(name){
            vector<Card> cards;
            hand = cards;
        }
        
        const std::string &get_name() const override{
            return name;
        }

        void add_card(const Card &c) override{
            hand.push_back(c);
        }
        //old version
        /*bool make_trump(const Card &upcard, bool is_dealer, int round, 
        Suit &order_up_suit) const override{
            int counter = 0 ;
            if (round == 1){
                for (size_t i = 0; i < hand.size(); ++i){
                    if (hand[i].is_trump(upcard.get_suit()) && hand[i].is_face_or_ace()){
                        ++counter;
                    }
                }
            }
            if (counter >= 2){
                order_up_suit = upcard.get_suit();
                return true;
            }
            if (round == 2){
                for (size_t i = 0; i < hand.size(); ++i){
                    if ((hand[i].is_trump(upcard.get_suit()) &&
                     hand[i].is_face_or_ace()) || 
                    (hand[i].is_face_or_ace() && 
                    hand[i].get_suit() == Suit_next(upcard.get_suit()))){
                        order_up_suit = hand[i].get_suit();
                        return true;
                    }
                }
            }
            if (round ==2 && is_dealer == true){
                for (size_t i = 0; i < hand.size(); ++i){
                    if (hand[i].get_suit() == upcard.get_suit() || 
                    hand[i].get_suit() == Suit_next(upcard.get_suit())){
                        order_up_suit = hand[i].get_suit();
                        return true;
                    }
                }
            }
        return false;
        }*/
       //correct but bad style code
       /*bool make_trump(const Card &upcard, bool is_dealer, int round, 
                Suit &order_up_suit) const override {
            if (round == 1) {
                Suit prop = upcard.get_suit(); 
                int count = 0;
                for (size_t i = 0; i < hand.size(); ++i) {
                    if (hand[i].get_suit(prop) == prop && hand[i].is_face_or_ace()) {
                        ++count;
                    }
                }
                if (count >= 2) {
                    order_up_suit = prop;
                    return true;
                }
                return false;
            }
            else if (round == 2) {
                Suit propnext = Suit_next(upcard.get_suit());
                if (!is_dealer) {
                    for (size_t i = 0; i < hand.size(); ++i) {
                        if (hand[i].get_suit(propnext) == propnext 
                        && hand[i].is_face_or_ace()) {
                            order_up_suit = propnext;
                            return true;
                        }
                    }
                    return false;
                } 
                else {
                    order_up_suit = propnext;
                    return true;
                }
            }
            return false;
        }*/

    //stylistically good but incorrect function
       bool make_trump(const Card &upcard, bool is_dealer, int round, 
                Suit &order_up_suit) const override {
            if (round == 1) {
                int count = 0;
                Suit prop = upcard.get_suit();
                for (size_t i = 0; i < hand.size(); ++i) {
                    if (hand[i].get_suit(prop) == prop 
                    && hand[i].is_face_or_ace()) {
                        ++count;
                    }
                }
                if (count >= 2) {
                    order_up_suit = prop;
                    return true;
                } else {
                    return false;
                }
            }
            else if (round == 2) {
                Suit candidate = Suit_next(upcard.get_suit());
                if (is_dealer) {
                    order_up_suit = candidate;
                    return true;
                }
                int count = 0;
                for (size_t i = 0; i < hand.size(); ++i) {
                    if (hand[i].get_suit(candidate) == candidate 
                    && hand[i].is_face_or_ace()) {
                        ++count;
                    }
                }
                if (count >= 1) {
                    //should not have print statements here
                    order_up_suit = candidate;
                    return true;
                } else {
                    return false;
                }
            }
            return false; 
        }

        void add_and_discard(const Card &upcard) override{
            int min = 0;
            Suit trump = upcard.get_suit();
            hand.push_back(upcard);
            for (size_t i = 0; i < hand.size(); ++i){
                if (Card_less(hand[i], hand[min], trump)){
                    min = i;
                }
            }
            hand.erase(hand.begin() + min); 
        }

        Card lead_card(Suit trump) override {
            int location = -1;
            for (size_t i = 0; i < hand.size(); ++i){
                if (location == -1 && !hand[i].is_trump(trump)){
                    location = i;
                }
                if (!hand[i].is_trump(trump) && location != -1
                && Card_less(hand[location], hand[i], trump)){
                    location = i;
                }
            }
            if (location != -1){
                Card ans = hand[location];
                hand.erase(hand.begin() + location);  // Remove card i
                return ans;
            }
            else {   
                for (size_t i = 0; i < hand.size(); ++i){
                    if (location == -1){
                        location = i;
                    }
                    if (Card_less(hand[location], hand[i], trump) && location != -1){
                        location = i;
                    }
                }
            }
            Card ans = hand[location];
            hand.erase(hand.begin() + location);  // Remove card i
            return ans;
        }

        Card play_card(const Card &led_card, Suit trump) override{
            bool canfollowsuit = false;
            int location = -1;
            for (size_t i = 0; i < hand.size(); ++i){
                if (led_card.get_suit(trump) == hand[i].get_suit(trump)){
                    canfollowsuit = true;
                }
            }
            if (canfollowsuit){//highestcardthat follows suit
                for (size_t i = 0; i < hand.size(); ++i){
                    if (location == -1 && 
                    hand[i].get_suit(trump) == led_card.get_suit(trump)){
                        location = i;
                    }
                    if (location != -1 
                    && Card_less(hand[location], hand[i], led_card, trump) && 
                    hand[i].get_suit(trump) == led_card.get_suit(trump)){
                        location = i;
                    }
                }
            }
            else {//lowest card 
                for (size_t i = 0; i < hand.size(); ++i){
                    if (location == -1){
                        location = i;
                    }
                    if (location != -1 
                    && Card_less(hand[i], hand[location], led_card, trump)){
                        location = i;
                    }
                }
            }

            Card ans = hand[location];
            hand.erase(hand.begin() + location);  // Remove card i
            return ans;
        }

};




class Human: public Player{
    private:
      string name;
      vector<Card> hand;

      void print_hand() const {
        for (size_t j = 0; j < hand.size(); ++j){
        cout << "Human player " << name << "'s hand: "
         << "[" << j << "] " << hand[j] << "\n";
        }
      }

    public:
        Human(std::string name) : name(name){
            vector<Card> cards;
            hand = cards;
        }
        
        const std::string &get_name() const override{
            return name;
        }

        bool make_trump(const Card &upcard, 
        bool is_dealer, int round, Suit &order_up_suit) 
        const override{
            print_hand();
            cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
            string ans;
            cin >> ans;
            //prob should not have print statment s here
            if (ans != "pass") {
                order_up_suit = string_to_suit(ans);
                return true;
            }
            else {
                return false;
            }
        }
        
        void add_card(const Card &c) override{
            std::sort(hand.begin(), hand.end());
            hand.push_back(c);
            std::sort(hand.begin(), hand.end());
        }
        
        void add_and_discard(const Card &upcard) override{
            print_hand();
            cout << "Discard upcard: [-1]\n";
            cout << "Human player " << name << ", please select a card to discard:\n";
            string location;
            cin >> location;
            if (stoi(location) == -1){
                return;
            }
            else{
                hand[stoi(location)] = upcard;
                //hand.erase(hand.begin() + stoi(location));
                //hand.push_back(upcard);
            }
        }

        //IN PORGRESS
        Card lead_card(Suit trump) override {       
            print_hand();
            cout << "Human player " << name << ", please select a card:\n";
            string location;
            cin >> location;
            Card lead = hand[stoi(location)];
            hand.erase(hand.begin() + stoi(location)); 
            return lead;
        }
        //IN PORGRESS
        Card play_card(const Card &led_card, Suit trump) override{
            print_hand();
            cout << "Human player " << name << ", please select a card:\n";
            string location;
            cin >> location;
            Card play = hand[stoi(location)];
            hand.erase(hand.begin() + stoi(location)); 
            return play;
        }

};




Player * Player_factory(const std::string &name, const std::string &strategy) {
  if (strategy == "Simple"){
    return new Simple(name);
  }
  if (strategy == "Human"){
    return new Human(name);
  }
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}
