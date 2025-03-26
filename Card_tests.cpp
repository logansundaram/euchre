#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());

    Card c1(KING, SPADES);
    ASSERT_EQUAL(KING, c1.get_rank());
    ASSERT_EQUAL(SPADES, c1.get_suit());

    Card c2(QUEEN, CLUBS);
    ASSERT_EQUAL(QUEEN, c2.get_rank());
    ASSERT_EQUAL(CLUBS, c2.get_suit());
}

TEST(card_less1){
    Card c(ACE, HEARTS);
    Card c2(ACE, SPADES);
    Card c3(JACK, SPADES);
    Card c4(NINE, SPADES);
    Card c5(ACE, HEARTS);

    Card c6(JACK, DIAMONDS);
    Card c7(ACE, CLUBS);
    

    Card c8(TEN, DIAMONDS);
    Card c9(TEN, CLUBS);

    ASSERT_TRUE(Card_less(c9, c8, SPADES));

    Card rightbow(JACK, SPADES);
    Card leftbow(JACK, CLUBS);

    ASSERT_TRUE(Card_less(leftbow, rightbow, SPADES));

    Card highrank(TEN, SPADES);
    Card lowrank(NINE, SPADES);

    ASSERT_TRUE(Card_less(lowrank, highrank, HEARTS));
    ASSERT_TRUE(Card_less(lowrank, highrank, SPADES));

    ASSERT_TRUE(Card_less(c, c2, SPADES));
    ASSERT_FALSE(Card_less(c, c2, HEARTS));
    ASSERT_TRUE(Card_less(c, c3, CLUBS));
    ASSERT_TRUE(Card_less(c, c3, SPADES));
    ASSERT_TRUE(Card_less(c5, c4, SPADES));
    ASSERT_TRUE(Card_less(c7, c6, HEARTS));

}


TEST(stringto){
    string str = "Hearts";
    ASSERT_EQUAL(HEARTS, string_to_suit(str));
    string str1 = "Ace";
    ASSERT_EQUAL(ACE, string_to_rank(str1));
}

TEST(ca){
    Card c(ACE, HEARTS);
    Card c1(JACK, HEARTS);
    ASSERT_TRUE(Card_less(c, c1, HEARTS));
}

TEST(trump){
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(DIAMONDS, c.get_suit(DIAMONDS));
    ASSERT_EQUAL(true, c.is_face_or_ace());
    ASSERT_EQUAL(true, c.is_left_bower(DIAMONDS));
    ASSERT_EQUAL(true, c.is_right_bower(HEARTS));
    ASSERT_EQUAL(true, c.is_trump(DIAMONDS));
    ASSERT_EQUAL(DIAMONDS, c.get_suit(DIAMONDS));
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
}

TEST(comparison){
    Card c1(JACK, HEARTS);
    Card c2(JACK, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(c1, c2, DIAMONDS));
    ASSERT_EQUAL(false, Card_less(c1, c2, c2, HEARTS));
    ASSERT_EQUAL(true, c1 != c2);
    ASSERT_EQUAL(false, c1 == c2);
    ASSERT_EQUAL(true, c2 >= c1);
}

TEST(comparison2){
    Card c1(JACK, HEARTS);
    Card c2(JACK, DIAMONDS);
    ASSERT_EQUAL(false, c2 < c1);
    ASSERT_EQUAL(false, c2 <= c1);
    ASSERT_EQUAL(true, c2 > c1);
}

TEST(comparison3){
    Card c1(JACK, HEARTS);
    Card c2(JACK, DIAMONDS);
    ASSERT_EQUAL(true, c1 != c2);
    ASSERT_EQUAL(false, c1 == c2);
    ASSERT_EQUAL(true, c2 >= c1);
}

TEST(comparison4){
    Card c1(JACK, HEARTS);
    Card c2(JACK, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(c1, c2, DIAMONDS));
}

TEST(comparison5){
    Card c1(JACK, HEARTS);
    Card c2(JACK, DIAMONDS);

    ASSERT_EQUAL(false, Card_less(c1, c2, c2, HEARTS));
}

TEST(comparison7){
    Card c1(JACK, HEARTS);
    Card c2(JACK, DIAMONDS);
    ASSERT_EQUAL(true, c1 != c2);
}

TEST(comparison8){
    Card c1(JACK, HEARTS);
    Card c2(JACK, DIAMONDS);
    ASSERT_EQUAL(true, c2 >= c1);
    Card c3(TEN, HEARTS);
    ASSERT_EQUAL(false, c3.is_face_or_ace());
}

TEST(faceorace){
    Card c1(JACK, HEARTS);
    Card c2(KING, HEARTS);
    Card c3(QUEEN, HEARTS);
    Card c4(ACE, HEARTS);
    Card c5(NINE, HEARTS);
    Card c6(TEN, HEARTS);
    ASSERT_FALSE(c6.is_face_or_ace());
    ASSERT_FALSE(c5.is_face_or_ace());
    ASSERT_TRUE(c4.is_face_or_ace());
    ASSERT_TRUE(c3.is_face_or_ace());
    ASSERT_TRUE(c2.is_face_or_ace());
    ASSERT_TRUE(c1.is_face_or_ace());
}

TEST(comparison9){
    Card c1(JACK, HEARTS);
    Card c2(JACK, DIAMONDS);
    ASSERT_EQUAL(false, c1 == c2);
}

TEST(comparison10){
    Card c1(JACK, HEARTS);
    Card c2(JACK, HEARTS);
    Card c3(ACE, SPADES);
    ASSERT_FALSE(Card_less(c1, c2, HEARTS));
    ASSERT_TRUE(Card_less(c3, c2, HEARTS));
    ASSERT_FALSE(Card_less(c2, c3, HEARTS));
}

/*TEST(in_const){
    std::string input_data = 
        "P3\n"
        "2 2\n"
        "255\n"
        "255 0 0  0 255 0\n"
        "0 0 255  255 255 255\n"; 

    std::istringstream fin(input_data);

    Image_init(&img, fin);


}*/
// Add more test cases here

TEST_MAIN()
