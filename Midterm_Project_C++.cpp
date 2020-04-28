#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <random>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::string;

// Card class that has a suit, name, and value as well as a compare and
// print card details methods
class Card
{
	private:
		string suit;
		string name;
		int value;
		int alt_value;
	public:
		Card()
		{
			suit = "none";
			name = "UNSURE";
			value = -1;
			alt_value = -1;
		}
		Card(string assign_suit, string assign_name, int assign_value)
		{
			suit = assign_suit;
			name = assign_name;
			value = assign_value;
			// Giving the alternate value to the Ace card
			if (name == "Ace")
			{
				alt_value = 11;
			}
			else
			{
				alt_value = -1;
			}
		}
		int compare(Card c2)
		{
			// Determines if it is the same card (names are unique)
			if (name == c2.get_name() && suit == c2.get_suit())
			{
				return 1;
			}
			// Determines if the card being compared has a greater value
			else if (c2.get_value() > value || c2.get_alt_value() > value)
			{
				return -1;
			}
			// Determine if the cards have the same value
			else if (c2.get_value() == value)
			{
				return 0;
			}
		}
		string get_suit()
		{
			return suit;
		}
		void set_suit(string new_suit)
		{
			suit = new_suit;	
		}
		string get_name()
		{
			return name;
		}
		void set_name(string new_name)
		{
			name = new_name;
		}
		int get_value()
		{
			return value;
		}
		void set_value(int new_value)
		{
			value = new_value;
		}
		int get_alt_value()
		{
			return alt_value;
		}
		void set_alt_value(int new_alt_value)
		{
			alt_value = new_alt_value;
		}
		// Card details printer method
		void print_card_details()
		{
			cout << name << " of " << suit << endl;
			cout << "Value: " << value << endl;
			if (alt_value != -1)
			{
				cout << "Alternate Value: " << alt_value << endl;
			}
		}
};
// Deck class inheriting the Card class with shuffle, deal, and sort methods
class Deck : public Card
{
	private:
		int size;
		vector<Card> cards;
	public:
		// Initialize a standard 52 card deck for default constructor
		Deck()
		{
			size = 52;
			vector<Card> cards;
			vector<string> name{"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
			vector<string> suit{"Spades","Hearts","Diamonds","Clubs"};
			for (int i=0; i<4; i++)
			{
				for (int j=0; j<13; j++)
				{
					if (j<9)
					{
						cards.push_back(Card(suit[i], name[j], j+1));
						cards[0];
					}
					if (j>=9)
					{
						cards.push_back(Card(suit[i], name[j], 10));
					}
				}
			}
			string input;
			cout << "Would you like to see your default deck? (Y/N)" << endl;
			// Input checking for seeing the deck
			cin >> input;
			if (input == "Y")
			{
				for (Card c : cards)
				{
					c.print_card_details();
				}
			}
			string next_input;
			srand(time(NULL));
			cout << "Would you like to see your default deck shuffled? (Y/N)" << endl;
			// Input checking for seeing shuffled deck
			cin >> next_input;
			if (next_input == "Y")
			{
				for (int i = 0; i < size; i++)
				{
					int r = rand() % size;
					Card tmp = cards[i];
					cards[i] = cards[r];
					cards[r] = tmp;
				}
				for (Card c : cards)
				{
					c.print_card_details();
				}
			}
		}
		Deck(vector<Card> user_deck, int user_size)
		{
			cards = user_deck;
			size = user_size;
		}
		void shuffle(Deck d2)
		{
			vector<Card> tmp_vec = get_deck();
			int full_size = d2.get_size() + size;
			vector<Card> full_deck;
			if (d2.get_size() != size)
			{
				int size_diff = abs(d2.get_size() - size);
				if (d2.get_size() < size)
				{
					for (int i = 0; i < d2.get_size(); i++)
					{
						full_deck.push_back(tmp_vec[i]);
						full_deck.push_back(d2.get_deck()[i]);
					}
					for (int j = 0; j < size_diff; j++)
					{
						full_deck.push_back(tmp_vec[d2.get_size()+j]);
					}
					set_deck(full_deck);
				}
				else if (size < d2.get_size())
				{
					for (int i = 0; i < size; i++)
					{
						full_deck.push_back(d2.get_deck()[i]);
						full_deck.push_back(tmp_vec[i]);
					}
					for (int j = 0; j < size_diff; j++)
					{
						full_deck.push_back(d2.get_deck()[size+j]);
					}
					set_deck(full_deck);
				}
			}
			else if (d2.get_size() == size)
			{
				for (int i = 0; i < full_size/2; i++)
				{
					full_deck.push_back(d2.get_deck()[i]);
					full_deck.push_back(tmp_vec[i]);
				}
				set_deck(full_deck);
			}
			set_deck(full_deck);
		}
		Deck deal(int num_cards)
		{
			vector<Card> tmp_vect;
			vector<Card> retrieve = cards;
			for (int i=0; i<num_cards; i++)
			{
				tmp_vect.push_back(retrieve[i]);
				retrieve.erase(cards.begin() + i);
			}
			set_deck(retrieve);
			cout << tmp_vect.size() << endl;
			Deck new_d(tmp_vect, num_cards);
			cout << "Here is the hand you are dealt" << endl;
			return new_d;
		}
		int get_size()
		{
			return size;
		}
		vector<Card> get_deck()
		{
			return cards;
		}
		void set_deck(vector<Card> upd_deck)
		{
			cards = upd_deck;
		}
};

int main()
{
	srand(time(NULL));
	// Small example check for Card class
	string suit1 = "Spades"; string name1 = "Jack"; int value1 = 10;
	string suit2 = "Hearts"; string name2 = "King"; int value2 = 10;
	Card c1(suit1, name1, value1);
	Card c2(suit2, name2, value2);
	c1.print_card_details();
	c2.print_card_details();
	cout << c1.compare(c2) << endl;
	int size = 26;
	vector<Card> D1;
	vector<Card> D2;
	vector<string> name{"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
	vector<string> suit{"Spades","Hearts","Diamonds","Clubs"};
	for (int i=0; i<4; i++)
	{
		if (i == 0 || i == 1)
		{
			for (int j=0; j<13; j++)
			{
				if (j<9)
				{
					D1.push_back(Card(suit[i], name[j], j+1));
				}
				if (j>=9)
				{
					D1.push_back(Card(suit[i], name[j], 10));
				}
			}
		}
		else
		{
			for (int k=0; k<13; k++)
			{
				if (k<9)
				{
					D2.push_back(Card(suit[i], name[k], k+1));
				}
				if (k>=9)
				{
					D2.push_back(Card(suit[i], name[k], 10));
				}
			}
		}
	}
	Deck d;
	Deck deck1(D1, size);
	Deck deck2(D2, size);
	int num_cards = 10;
	deck1.shuffle(deck2);
	d = deck1.deal(num_cards);
	for (Card c : d.get_deck())
	{
		c.print_card_details();
	}
}
