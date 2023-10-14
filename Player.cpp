#include "Player.hpp"
#include <cassert>
using std::cout, std::endl, std::cin, std::string, std::vector;

class SimplePlayer : public Player {
    public:
        SimplePlayer(const std::string name);

                ///EFFECTS returns player's name
        const std::string & get_name() const;

        //REQUIRES player has less than MAX_HAND_SIZE cards
        //EFFECTS  adds Card c to Player's hand
        void add_card(const Card &c);

        //REQUIRES round is 1 or 2
        //MODIFIES order_up_suit
        //EFFECTS If Player wishes to order up a trump suit then return true and
        //  change order_up_suit to desired suit.  If Player wishes to pass, then do
        //  not modify order_up_suit and return false.
        bool make_trump(const Card &upcard, bool is_dealer,
                                int round, Suit &order_up_suit) const;

        //REQUIRES Player has at least one card
        //EFFECTS  Player adds one card to hand and removes one card from hand.
        void add_and_discard(const Card &upcard);

        //REQUIRES Player has at least one card
        //EFFECTS  Leads one Card from Player's hand according to their strategy
        //  "Lead" means to play the first Card in a trick.  The card
        //  is removed the player's hand.
        Card lead_card(Suit trump);

        //REQUIRES Player has at least one card
        //EFFECTS  Plays one Card from Player's hand according to their strategy.
        //  The card is removed from the player's hand.
        Card play_card(const Card &led_card, Suit trump);

        // Maximum number of cards in a player's hand
        static const int MAX_HAND_SIZE = 5;

        // Needed to avoid some compiler errors
        ~SimplePlayer() {}

        private:
            void print_hand() const {
                for (size_t i=0; i < hand.size(); ++i)
                    cout << "Human player " << name << "'s hand: "
                        << "[" << i << "] " << hand[i] << "\n";
            }
            std::string name;
            int hand_size = 0;
            std::vector<Card> hand;
};

SimplePlayer::SimplePlayer(const std::string n){
    name  = n;
}

const std::string & SimplePlayer::get_name() const{
    return name;
}

void SimplePlayer::add_card(const Card &c){
    assert(hand_size < MAX_HAND_SIZE);
    ++hand_size;
    hand.push_back(c);
}

bool SimplePlayer::make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const{
    assert(round == 1 || round == 2);
    if (round == 1){
        int count = 0;
        for (int i = 0; i < hand_size; ++i){
            if (hand[i].is_face_or_ace() && hand[i].is_trump(upcard.get_suit())){
                ++count;
            }   
        }
        if (count >= 2){
            order_up_suit = upcard.get_suit();
            return true;
        }else{
            return false;
        }
    }else {
        int count = 0;
        Card c;
        int rank = 0;
        for (int i = 0; i < hand_size; ++i){
            if (hand[i].is_face_or_ace() && hand[i].get_suit() == DIAMONDS){
                if (hand[i].get_rank() > rank){
                    rank = hand[i].get_rank();
                    c = hand[i];
                }
                ++count;
            }   
        }
        if (count >= 1){
            order_up_suit = c.get_suit();
            return true;
        }else{
            return false;
        }
    }
}

void SimplePlayer::add_and_discard(const Card &upcard){
    assert(hand_size > 0);
    Card c = hand[0];
    hand.push_back(upcard);
    int count = 0;
    for (int i = 1; i < hand_size + 1; ++i){
        if (Card_less(hand[i], c, upcard.get_suit())){
            c = hand[i];
            count = i;
        }
    }
    hand.erase(hand.begin() + count);
}

Card SimplePlayer::lead_card(Suit trump){
    assert(hand_size > 0);
    Card c(EIGHT, SPADES);
    int count = 0;
    bool all_trump = true;
    for (int i = 1; i < hand_size; ++i){
        if (hand[i].get_suit() != trump && Card_less(c, hand[i], trump)){
            c = hand[i];
            all_trump = false;
            count  = i;
        }
    }
    if (all_trump){
        for (int i = 0; i < hand_size; ++i){
            if (Card_less(c, hand[i], trump)){
                c = hand[i];
                count = i;
            }
        }   
    }
    hand.erase(hand.begin() + count);
    return c;
}

Card SimplePlayer::play_card(const Card &led_card, Suit trump){
    assert(hand_size > 0);
    bool no_led_suit = true;
    Card c;
    int count = 0;
    for (int i = 0; i < hand_size; ++i){
        if (hand[i].get_suit() == led_card.get_suit()){
            c = hand[i];
            no_led_suit = false;
        }
    }
    if (no_led_suit){
        c = hand[0];
        for (int i = 0; i < hand_size; ++i){
            if (Card_less(hand[i], c, trump)){
                c = hand[i];
                count = i;
            }
        }
    }else{
        for (int i = 0; i < hand_size; ++i){
            if (hand[i].get_suit() == led_card.get_suit() && Card_less(c, hand[i], led_card, trump)){
                c = hand[i];
                count = i;
            }
        }
    }
    hand.erase(hand.begin() + count);
    --hand_size;
    return c;
}


class HumanPlayer : public Player {
    public:
        HumanPlayer(const std::string name);

                ///EFFECTS returns player's name
        const std::string & get_name() const;

        //REQUIRES player has less than MAX_HAND_SIZE cards
        //EFFECTS  adds Card c to Player's hand
        void add_card(const Card &c);

        //REQUIRES round is 1 or 2
        //MODIFIES order_up_suit
        //EFFECTS If Player wishes to order up a trump suit then return true and
        //  change order_up_suit to desired suit.  If Player wishes to pass, then do
        //  not modify order_up_suit and return false.
        bool make_trump(const Card &upcard, bool is_dealer,
                                int round, Suit &order_up_suit) const;

        //REQUIRES Player has at least one card
        //EFFECTS  Player adds one card to hand and removes one card from hand.
        void add_and_discard(const Card &upcard);

        //REQUIRES Player has at least one card
        //EFFECTS  Leads one Card from Player's hand according to their strategy
        //  "Lead" means to play the first Card in a trick.  The card
        //  is removed the player's hand.
        Card lead_card(Suit trump);

        //REQUIRES Player has at least one card
        //EFFECTS  Plays one Card from Player's hand according to their strategy.
        //  The card is removed from the player's hand.
        Card play_card(const Card &led_card, Suit trump);

        // Maximum number of cards in a player's hand
        static const int MAX_HAND_SIZE = 5;

        // Needed to avoid some compiler errors
        ~HumanPlayer() {}

        private:
            void print_hand() const {
                for (size_t i=0; i < hand.size(); ++i)
                    cout << "Human player " << name << "'s hand: "
                        << "[" << i << "] " << hand[i] << "\n";
            }
            std::string name;
            int hand_size = 0;
            std::vector<Card> hand;
};

HumanPlayer::HumanPlayer(const std::string n){
    name  = n;
}

const std::string & HumanPlayer::get_name() const{
    return name;
}

void HumanPlayer::add_card(const Card &c){
    assert(hand_size < MAX_HAND_SIZE);
    ++hand_size;
    hand.push_back(c);
}

 bool HumanPlayer::make_trump(const Card &upcard, bool is_dealer,
                                int round, Suit &order_up_suit) const{
    print_hand();
    string decision;
    cin >> decision;

    if (decision != "pass") {
        order_up_suit = string_to_suit(decision);
        return true;
    }
    else {
        return false;
    }
}

void HumanPlayer::add_and_discard(const Card &upcard){
    assert(hand_size > 0);
    Card c = hand[0];
    hand.push_back(upcard);
    int count = 0;
    for (int i = 1; i < MAX_HAND_SIZE + 1; ++i){
        if (Card_less(hand[i], c, upcard.get_suit())){
            c = hand[i];
            count = i;
        }
    }
    hand.erase(hand.begin() + count);
}

Card HumanPlayer::lead_card(Suit trump){
    assert(hand_size > 0);
    Card c(EIGHT, SPADES);
    int count = 0;
    bool all_trump = true;
    for (int i = 1; i < MAX_HAND_SIZE; ++i){
        if (hand[i].get_suit() != trump && Card_less(c, hand[i], trump)){
            c = hand[i];
            all_trump = false;
            count  = i;
        }
    }
    if (all_trump){
        for (int i = 0; i < MAX_HAND_SIZE; ++i){
            if (Card_less(c, hand[i], trump)){
                c = hand[i];
                count = i;
            }
        }   
    }
    hand.erase(hand.begin() + count);
    return c;
}

Card HumanPlayer::play_card(const Card &led_card, Suit trump){
    assert(hand_size > 0);
    Card c(EIGHT, SPADES);
    bool no_led_suit = true;
    int count = 0;
    for (int i = 0; i < MAX_HAND_SIZE; ++i){
        if (hand[i].get_suit() != trump && Card_less(c, hand[i], led_card, trump)){
            c = hand[i];
            no_led_suit = false;
            count = i;
        }
    }
    if (no_led_suit){
        for (int i = 0; i < MAX_HAND_SIZE; ++i){
            if (Card_less(hand[i], c, trump)){
                c = hand[i];
                count = i;
            }
        }
    }
    hand.erase(hand.begin() + count);
    return c;
}


Player * Player_factory(const std::string &name, const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }else if (strategy == "Human"){
    return new HumanPlayer(name);
  }
  // Repeat for each other type of Player
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}

