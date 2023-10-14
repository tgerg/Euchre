#include "Pack.hpp"

Pack::Pack(){
  int i = 0;
  for (int s = SPADES; s <= DIAMONDS; ++s) {
    for (int r = NINE; r <= ACE; ++r){
        Suit suit = static_cast<Suit>(s);
        Rank rank = static_cast<Rank>(r);
        Card c(rank, suit);
        cards[i] = c;
        ++i;
    }
  }
  next = 0;
}

Pack::Pack(std::istream& pack_input){
    Card c;
    int i = 0;
    while (pack_input >> c){
        cards[i] = c;
        ++i;
    }
    next = 0;
}

Card Pack::deal_one(){
    Card c = cards[next];
    ++next;
    return c;
}

void Pack::reset(){
    next = 0;
}

void Pack::shuffle(){
    for (int j = 0; j < 7; ++j){
        std::array<Card, PACK_SIZE> orig = cards;
        int k = 12;
        int x = 0;
        for (int i = 0; i < 23; ++i){
            cards[i] = cards[k];
            ++i;
            cards[i] = orig[x];
            ++k;
            ++x;
        }
    }
    reset();
}

bool Pack::empty() const{
    if (next >= PACK_SIZE){
        return true;
    }
    return false;
}