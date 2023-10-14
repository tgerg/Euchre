#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////

Card::Card(){
  rank = TWO;
  suit = SPADES;
}

Card::Card(Rank rank_in, Suit suit_in){
    rank = rank_in;
    suit = suit_in;
}

Rank Card::get_rank() const{
  return rank;
}

Suit Card::get_suit() const{
  return suit;
}

Suit Card::get_suit(Suit trump) const{
  if (get_suit() == trump){
    return suit;
  }else if ((trump == 0 || trump == 2) && (get_suit() == 0 || get_suit() == 2)){
    if (get_rank() == JACK){
      return trump;
    }
  }else if ((trump == 1 || trump == 3) && (get_suit() == 1 || get_suit() == 3)){
    if (get_rank() == JACK){
      return trump;
    }
  }
  return suit;
}

bool Card::is_face_or_ace() const{
  if (get_rank() == JACK || get_rank() == QUEEN || get_rank() == KING || get_rank() == ACE){
    return true;
  }
  return false;
}

bool Card::is_right_bower(Suit trump) const{
  if (get_suit() == trump && get_rank() == JACK){
    return true;
  }
  return false;
}

bool Card::is_left_bower(Suit trump) const{
  if (get_suit(trump) == trump && get_rank() == JACK && !(is_right_bower(trump))){
    return true;
  }
  return false;
}

bool Card::is_trump(Suit trump) const{
  if (get_suit(trump) == trump){
    return true;
  }
  return false;
}

std::ostream & operator<<(std::ostream &os, const Card &card){
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

std::istream & operator>>(std::istream &is, Card &card){
  string junk;
  is >> card.rank >> junk >> card.suit;
  return is;
}

bool operator<(const Card &lhs, const Card &rhs){
  if (rhs.get_rank() > lhs.get_rank()){
    return true;
  }else if (rhs.get_rank() == lhs.get_rank() && rhs.get_suit() > lhs.get_suit()){
    return true;
  }
  return false;
}

bool operator<=(const Card &lhs, const Card &rhs){
  if (rhs.get_rank() > lhs.get_rank()){
    return true;
  }else if (rhs.get_rank() == lhs.get_rank() && rhs.get_suit() > lhs.get_suit()){
    return true;
  }else if (rhs.get_rank() == lhs.get_rank() && rhs.get_suit() == lhs.get_suit()){
    return true;
  }
  return false;
}

bool operator>(const Card &lhs, const Card &rhs){
  if (rhs.get_rank() < lhs.get_rank()){
    return true;
  }else if (rhs.get_rank() == lhs.get_rank() && rhs.get_suit() < lhs.get_suit()){
    return true;
  }
  return false;
}

bool operator>=(const Card &lhs, const Card &rhs){
  if (rhs.get_rank() < lhs.get_rank()){
    return true;
  }else if (rhs.get_rank() == lhs.get_rank() && rhs.get_suit() < lhs.get_suit()){
    return true;
  }else if (rhs.get_rank() == lhs.get_rank() && rhs.get_suit() == lhs.get_suit()){
    return true;
  }
  return false;
}

bool operator==(const Card &lhs, const Card &rhs){
  if (rhs.get_rank() == lhs.get_rank() && rhs.get_suit() == lhs.get_suit()){
    return true;
  }
  return false;
}

bool operator!=(const Card &lhs, const Card &rhs){
  if (rhs.get_rank() != lhs.get_rank() || rhs.get_suit() != lhs.get_suit()){
    return true;
  }
  return false;
}

Suit Suit_next(Suit suit){
  if (suit == 0){
    return CLUBS;
  }else if (suit == 1){
    return DIAMONDS;
  }else if (suit == 2){
    return SPADES;
  }else{
    return HEARTS;
  }
}

bool Card_less(const Card &a, const Card &b, Suit trump){
  if (b.is_right_bower(trump)){
    return true;
  }else if (a.is_right_bower(trump)){
    return false;
  }else if (b.is_left_bower(trump)){
    return true;
  }else if (a.is_left_bower(trump)){
    return false;
  }else if (a.get_suit() == trump && b.get_suit() != trump){
    return false;
  }else if (a.get_suit() != trump && b.get_suit() == trump){
    return true;
  }else if (a < b){
    return true;
  }
  return false;
}

bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump){
  Suit led = led_card.get_suit();
  if (b.is_right_bower(trump)){
    return true;
  }else if (a.is_right_bower(trump)){
    return false;
  }else if (b.is_left_bower(trump)){
    return true;
  }else if (a.is_left_bower(trump)){
    return false;
  }else if (a.get_suit() == trump && b.get_suit() != trump){
    return false;
  }else if (a.get_suit() != trump && b.get_suit() == trump){
    return true;
  }else if (a.get_suit() == led && b.get_suit() != led){
    return false;
  }else if (a.get_suit() != led && b.get_suit() == led){
    return true;
  }else if (a < b){
    return true;
  }
  return false;
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=


