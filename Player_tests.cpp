#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_add_discard1){
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(TEN, SPADES));
    alice->add_card(Card(JACK, SPADES));
    alice->add_card(Card(ACE, SPADES));
    alice->add_card(Card(KING, SPADES));
    Card c1(NINE, HEARTS);
    alice->add_and_discard(c1);

    Player * example = Player_factory("Example", "Simple");
    example->add_card(Card(NINE, HEARTS));
    example->add_card(Card(QUEEN, SPADES));
    example->add_card(Card(JACK, SPADES));
    example->add_card(Card(ACE, SPADES));
    example->add_card(Card(KING, SPADES));
    Card c2(TEN, HEARTS);
    ASSERT_EQUAL(alice->play_card(c2, HEARTS), example->play_card(c2, HEARTS));
    ASSERT_EQUAL(alice->play_card(c2, HEARTS), example->play_card(c2, HEARTS));
    ASSERT_EQUAL(alice->play_card(c2, HEARTS), example->play_card(c2, HEARTS));
    ASSERT_EQUAL(alice->play_card(c2, HEARTS), example->play_card(c2, HEARTS));
    ASSERT_EQUAL(alice->play_card(c2, HEARTS), example->play_card(c2, HEARTS));//implement play card and check playcard
    delete alice;
    delete example;
}

TEST(test_add_discard){
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(TEN, SPADES));
    alice->add_card(Card(JACK, SPADES));
    alice->add_card(Card(ACE, SPADES));
    alice->add_card(Card(KING, SPADES));
    Card c1(NINE, SPADES);
    alice->add_and_discard(c1);
    Player * example = Player_factory("Example", "Simple");
    example->add_card(Card(TEN, SPADES));
    example->add_card(Card(QUEEN, SPADES));
    example->add_card(Card(JACK, SPADES));
    example->add_card(Card(ACE, SPADES));
    example->add_card(Card(KING, SPADES));
    Card c2(TEN, HEARTS);
    ASSERT_EQUAL(alice->play_card(c2, HEARTS), example->play_card(c2, HEARTS));
    ASSERT_EQUAL(alice->play_card(c2, HEARTS), example->play_card(c2, HEARTS));
    ASSERT_EQUAL(alice->play_card(c2, HEARTS), example->play_card(c2, HEARTS));
    ASSERT_EQUAL(alice->play_card(c2, HEARTS), example->play_card(c2, HEARTS));
    ASSERT_EQUAL(alice->play_card(c2, HEARTS), example->play_card(c2, HEARTS));//implement play card and check playcard
    delete alice;
    delete example;
}

TEST(test_order_up_bug) {
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(NINE, CLUBS));
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(KING, HEARTS));
    
    Card nine_spades(NINE, SPADES);
    Suit trump;
    bool orderup = alice->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_TRUE(trump == CLUBS);

    delete alice;
}

TEST(test_round1_orderup) {
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(NINE, CLUBS));
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(KING, HEARTS));
    
    Card nine_spades(NINE, SPADES);
    Suit trump;
    bool orderup = alice->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );
  ASSERT_TRUE(!orderup);

    delete alice;
}

TEST(test_round1_leftbower) {
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(JACK, CLUBS));
    alice->add_card(Card(ACE, SPADES));
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(KING, HEARTS));
    
    Card nine_spades(NINE, SPADES);
    Suit trump;
    bool orderup = alice->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(SPADES, trump);

    delete alice;
}

TEST(test_order_up) {
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(ACE, SPADES));
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(ACE, CLUBS));
    alice->add_card(Card(ACE, DIAMONDS));
    alice->add_card(Card(KING, SPADES));
    
    Card nine_spades(NINE, SPADES);
    Suit trump;
    bool orderup = alice->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );
  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);


    delete alice;
}

TEST(testplayer_lead_card1) {
  Player * alice = Player_factory("Bob", "Simple");
    alice->add_card(Card(ACE, SPADES));
    alice->add_card(Card(JACK, SPADES));
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(TEN, SPADES));
    alice->add_card(Card(KING, SPADES));
    


  Card card_led = alice->lead_card(HEARTS);
  Card jack_clubs(ACE, SPADES);
  ASSERT_EQUAL(card_led, jack_clubs); 

  Card card_led4 = alice->lead_card(HEARTS);
  Card ace_spades(KING, SPADES);
  ASSERT_EQUAL(card_led4, ace_spades); 

  Card card_led2 = alice->lead_card(HEARTS);
  Card king_spades(QUEEN, SPADES);
  ASSERT_EQUAL(card_led2, king_spades); 

  Card card_led3 = alice->lead_card(HEARTS);
  Card queen_spades(JACK, SPADES);
  ASSERT_EQUAL(card_led3, queen_spades); 

  Card card_led5 = alice->lead_card(HEARTS);
  Card nine_spades(TEN, SPADES);
  ASSERT_EQUAL(card_led5, nine_spades); 

  delete alice;
}

TEST(testplayer_lead_card_nontrump) {
  Player * alice = Player_factory("Bob", "Simple");
    alice->add_card(Card(NINE, SPADES));
    alice->add_card(Card(NINE, CLUBS));
    alice->add_card(Card(NINE, HEARTS));
    alice->add_card(Card(NINE, DIAMONDS));
    alice->add_card(Card(TEN, SPADES));
    


  Card card_led = alice->lead_card(SPADES);

  Card nine_diamons(NINE, DIAMONDS);
  ASSERT_EQUAL(card_led, nine_diamons); 

  delete alice;
}

TEST(testplayer_lead_card_left) {
  Player * alice = Player_factory("Bob", "Simple");
    alice->add_card(Card(ACE, SPADES));
    alice->add_card(Card(JACK, CLUBS));
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(NINE, SPADES));
    alice->add_card(Card(KING, SPADES));
    


  Card card_led = alice->lead_card(SPADES);

  Card jack_clubs(JACK, CLUBS);
  ASSERT_EQUAL(card_led, jack_clubs); 

  delete alice;
}

TEST(testplayer_lead_card_left_bower) {
  Player * alice = Player_factory("Bob", "Simple");
    alice->add_card(Card(ACE, SPADES));
    alice->add_card(Card(JACK, CLUBS));
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(NINE, SPADES));
    alice->add_card(Card(KING, SPADES));
    


  Card card_led = alice->lead_card(SPADES);
  Card jack_clubs(JACK, CLUBS);
  ASSERT_EQUAL(card_led, jack_clubs); 

  Card card_led4 = alice->lead_card(SPADES);
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led4, ace_spades); 

  Card card_led2 = alice->lead_card(SPADES);
  Card king_spades(KING, SPADES);
  ASSERT_EQUAL(card_led2, king_spades); 

  Card card_led3 = alice->lead_card(SPADES);
  Card queen_spades(QUEEN, SPADES);
  ASSERT_EQUAL(card_led3, queen_spades); 

  Card card_led5 = alice->lead_card(SPADES);
  Card nine_spades(NINE, SPADES);
  ASSERT_EQUAL(card_led5, nine_spades); 

  delete alice;
}

TEST(test_print_basic) {
  Player * alice = Player_factory("Alice", "Simple");

  // Capture our output
  ostringstream s;
  s << *alice;

  // Correct output
  ostringstream correct;
  correct << "Alice";
  ASSERT_EQUAL(s.str(), correct.str());
  delete alice;
}

TEST(playcard){
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(TEN, SPADES));
    alice->add_card(Card(JACK, SPADES));
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(ACE, SPADES));

    Card led(TEN, HEARTS);

    Card c1 = alice->play_card(led, HEARTS);
    Card c2 = alice->play_card(led, HEARTS);
    Card c3 = alice->play_card(led, HEARTS);
    Card c4 = alice->play_card(led, HEARTS);
    Card c5 = alice->play_card(led, HEARTS);

    ASSERT_EQUAL(c1, Card(TEN, SPADES));
    ASSERT_EQUAL(c2, Card(JACK, SPADES));
    ASSERT_EQUAL(c3, Card(QUEEN, SPADES));
    ASSERT_EQUAL(c4, Card(KING, SPADES));
    ASSERT_EQUAL(c5, Card(ACE, SPADES));
    delete alice;
}

TEST(playcardled){
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(ACE, SPADES));

    Card led(TEN, HEARTS);

    Card c1 = alice->play_card(led, HEARTS);
    Card c2 = alice->play_card(led, HEARTS);
    Card c3 = alice->play_card(led, HEARTS);
    Card c4 = alice->play_card(led, HEARTS);
    Card c5 = alice->play_card(led, HEARTS);

    ASSERT_EQUAL(c1, Card(JACK, HEARTS));
    ASSERT_EQUAL(c2, Card(ACE, HEARTS));
    ASSERT_EQUAL(c3, Card(QUEEN, SPADES));
    ASSERT_EQUAL(c4, Card(KING, SPADES));
    ASSERT_EQUAL(c5, Card(ACE, SPADES));
    delete alice;
}

TEST(playcardlednotrump){
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(JACK, SPADES));
    alice->add_card(Card(ACE, SPADES));

    Card led(TEN, HEARTS);

    Card c1 = alice->play_card(led, SPADES);
    Card c2 = alice->play_card(led, SPADES);
    Card c3 = alice->play_card(led, SPADES);
    Card c4 = alice->play_card(led, SPADES);
    Card c5 = alice->play_card(led, SPADES);

    ASSERT_EQUAL(c1, Card(ACE, HEARTS));
    ASSERT_EQUAL(c2, Card(JACK, HEARTS));
    ASSERT_EQUAL(c3, Card(QUEEN, SPADES));
    ASSERT_EQUAL(c4, Card(ACE, SPADES));
    ASSERT_EQUAL(c5, Card(JACK, SPADES));
    delete alice;
}


// Add more tests here

TEST_MAIN()
