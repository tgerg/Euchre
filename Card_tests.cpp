#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_get_suit_trump){
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(DIAMONDS, c.get_suit(DIAMONDS));
}

TEST(test_is_face_or_ace){
    Card c(KING, SPADES);
    Card d(ACE, HEARTS);
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_TRUE(d.is_face_or_ace());
}

TEST(test_is_right_and_left_bower){
    Card c(JACK, HEARTS);
    Card d(JACK, DIAMONDS);
    ASSERT_TRUE(c.is_right_bower(HEARTS));
    ASSERT_FALSE(d.is_right_bower(HEARTS));
    ASSERT_TRUE(d.is_left_bower(HEARTS));
    ASSERT_FALSE(c.is_left_bower(HEARTS));
}

TEST(test_is_trump){
    Card c(ACE, DIAMONDS);
    ASSERT_TRUE(c.is_trump(DIAMONDS));
}

TEST(test_suit_next){
    Card c(NINE, SPADES);
    ASSERT_EQUAL(CLUBS, Suit_next(c.get_suit()));
}

TEST(test_card_less){
    Card a(NINE, SPADES);
    Card b(KING, SPADES);
    Card c(QUEEN, HEARTS);
    Card d(ACE, HEARTS);
    ASSERT_TRUE(Card_less(a, b, DIAMONDS));
    ASSERT_TRUE(Card_less(c, a, SPADES));
    ASSERT_TRUE(Card_less(a, d, c, DIAMONDS));
    ASSERT_TRUE(Card_less(d, a, c, SPADES));
}

TEST_MAIN()
