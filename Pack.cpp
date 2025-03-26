#include "Pack.hpp"
#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

Pack::Pack(){
    std::array<Card, PACK_SIZE> cardsc;
    for (int s = 0; s < 4; ++s){
        for (int r = 0; r < 6; ++r){
            cardsc[s*6 + r] = Card(static_cast<Rank>(r+7), static_cast<Suit>(s));
        }
    }
    cards = cardsc;
    next = 0;
}

Pack::Pack(std::istream& pack_input){
    std::array<Card, PACK_SIZE> cardsc;
    for (int i = 0; i < PACK_SIZE; ++i){
      pack_input >> cardsc[i]; 
    }
    cards = cardsc;
    next = 0;
}

Card Pack::deal_one(){
  Card current =  cards[next];
  next = next + 1;
  return current;
}

void Pack::reset(){
  next = 0;
}

void Pack::shuffle(){
   std::array<Card, PACK_SIZE> temp; 

    for (int i = 0; i < 7; ++i) {  
        int l = 0;
        int r = PACK_SIZE / 2;
        
        for (int j = 0; j < PACK_SIZE; j += 2) {
            temp[j] = cards[r++]; 
            temp[j + 1] = cards[l++]; 
        }

        cards = temp;
    }
    
    next = 0;  
}

bool Pack::empty() const{
  if (next == PACK_SIZE){
    return true;
  }
  return false;
};
