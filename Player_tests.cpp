#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>
#include <cassert>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_add_card){
    Player * alice = Player_factory("Alice", "Simple");
    Card c(ACE, HEARTS);
    alice->add_card(c);
    ASSERT_EQUAL(alice->play_card(Card(NINE, HEARTS), CLUBS), c);

    delete alice;
}

TEST(test_make_trump){
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(NINE, CLUBS));
    alice->add_card(Card(JACK, DIAMONDS));
    alice->add_card(Card(QUEEN, HEARTS));
    alice->add_card(Card(QUEEN, SPADES));
    Card up1(KING, HEARTS);
    Card up2(ACE, CLUBS);
    Card up3(NINE, DIAMONDS);
    Card up4(ACE, CLUBS);
    Suit ordered_up = SPADES;

    ASSERT_TRUE(alice->make_trump(up1, false, 1, ordered_up));
    ASSERT_EQUAL(HEARTS, ordered_up);
    ASSERT_FALSE(alice->make_trump(up2, false, 1, ordered_up));
    ASSERT_EQUAL(HEARTS, ordered_up);
    ASSERT_TRUE(alice->make_trump(up3, false, 2, ordered_up));
    ASSERT_EQUAL(DIAMONDS, ordered_up);
    ASSERT_TRUE(alice->make_trump(up4, false, 2, ordered_up));
    ASSERT_EQUAL(DIAMONDS, ordered_up);

    delete alice;
}

TEST(test_add_and_discard){
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(KING, HEARTS));
    alice->add_card(Card(NINE, CLUBS));
    alice->add_card(Card(JACK, DIAMONDS));
    alice->add_card(Card(QUEEN, HEARTS));
    alice->add_card(Card(QUEEN, SPADES));
    vector<Card> v;
    v.push_back(Card(KING, HEARTS));
    v.push_back(Card(JACK, DIAMONDS));
    v.push_back(Card(QUEEN, HEARTS));
    v.push_back(Card(NINE, SPADES));
    v.push_back(Card(ACE, HEARTS));
    Card up1(ACE, HEARTS);
    Card up2(QUEEN, SPADES);

    alice->add_and_discard(up1);
    ASSERT_EQUAL(v[4], alice->play_card(up1, CLUBS));
    v.push_back(Card(NINE, SPADES));
    alice->add_and_discard(up2);
    ASSERT_EQUAL(Card(QUEEN, SPADES), alice->play_card(up2, CLUBS));  // Might have to come back and write a person with all trump cards

    delete alice;
}

TEST(test_lead_card){
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(QUEEN, HEARTS));
    alice->add_card(Card(QUEEN, SPADES));

    ASSERT_EQUAL(alice->lead_card(HEARTS), Card(QUEEN, SPADES));

    delete alice;
}

TEST(test_play_card){
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(QUEEN, HEARTS));
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(NINE, SPADES));
    Card up1(KING, HEARTS);
    Card up2(KING, CLUBS);

    ASSERT_EQUAL(alice->play_card(up1, HEARTS), Card(ACE, HEARTS));
    ASSERT_EQUAL(alice->play_card(up2, HEARTS), Card(NINE, SPADES));
    
    delete alice;
}

TEST_MAIN()
