#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>

enum Rank
{
	HIGH_CARD,
	PAIR,
	TWO_PAIRS,
	THREE_OF_A_KIND,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	STRAIGHT_FLUSH,
	ROYAL_FLUSH
};

enum letterValues { JOKER = 11, QUEEN = 12, KING = 13, ACE = 14 };

static int convertToNumber(char value) 
{
	switch (value) 
	{
	case 'T':
		return 10; break;
	case 'J':
		return JOKER; break;
	case 'Q':
		return QUEEN; break;
	case 'K':
		return KING; break;
	case 'A':
		return ACE; break;
	default:
		return value - '0';
	}
}

static bool checkIsIncreasingByOne(std::vector<int> vec)
{
	for (size_t i = 1; i < 5; i++)
	{
		if (vec[i] - vec[i - 1] != 1)
		{
			return false;
		}
	}

	return true;
}

struct PokerHand
{
	mutable int sumOfValues = 0;
	const std::string cardsCombination;
	Rank rank;

	PokerHand(std::string pokerhand) : cardsCombination(pokerhand)
	{
		this->rank = setRank();
	}

	Rank setRank()
	{
		std::string types;
		std::string suits;

		for (size_t i = 1; i < cardsCombination.length(); i += 3)
		{
			types += cardsCombination[i - 1];
			suits += cardsCombination[i];
		}

		std::vector<int> values;

		for (size_t i = 0; i < cardsCombination.length(); i += 3)
		{
			int value = convertToNumber(cardsCombination[i]);
			values.push_back(value);
		}

		std::sort(values.begin(), values.end());
		sumOfValues = std::accumulate(values.begin(), values.end(), 0);

		std::set<char> uniqueSuits(suits.begin(), suits.end());
		std::set<int> uniqueValues(values.begin(), values.end());

		bool isFlush = uniqueSuits.size() == 1;
		bool isBasicStraight = values == std::vector<int>{2, 3, 4, 5, 14};

		if (isBasicStraight)
		{
			sumOfValues -= (letterValues::ACE - 1);
		}

		bool isStraight = checkIsIncreasingByOne(values) || isBasicStraight;

		if (isFlush && isStraight && values.back() == 14) return Rank::ROYAL_FLUSH;
		if (isFlush && isStraight) return Rank::STRAIGHT_FLUSH;
		if (isFlush) return Rank::FLUSH;
		if (isStraight) return Rank::STRAIGHT;

		int countOfKindValues = 0;
		bool foursome = false;
		bool triple = false;
		int twos = 0;

		for (int value : uniqueValues)
		{
			countOfKindValues = std::count(values.begin(), values.end(), value);
			switch (countOfKindValues)
			{
			case 2: twos++; break;
			case 3: triple = true; break;
			case 4: foursome = true; break;
			}
		}

		if (foursome) return Rank::FOUR_OF_A_KIND;
		if (triple && twos == 1) return Rank::FULL_HOUSE;
		if (triple) return Rank::THREE_OF_A_KIND;
		if (twos == 2) return Rank::TWO_PAIRS;
		if (twos == 1) return Rank::PAIR;

		return Rank::HIGH_CARD;
	}
};

enum class Result { Win, Loss, Tie };

Result compare(const PokerHand& player, const PokerHand& opponent) 
{
	if (player.rank > opponent.rank) 
	{
		return Result::Win;
	}
	else if (player.rank < opponent.rank)
	{
		return Result::Loss;
	}
	else
	{
		if (player.sumOfValues > opponent.sumOfValues)
		{
			return Result::Win;
		}
		else if (player.sumOfValues < opponent.sumOfValues)
		{
			return Result::Loss;
		}

		return Result::Tie;
	}
}

void testPokerHands(const std::vector<std::tuple<std::string, std::string, Result>>& hands)
{
	for (const auto& handTuple : hands)
	{
		PokerHand player(std::get<0>(handTuple));
		PokerHand opponent(std::get<1>(handTuple));
		Result expected = std::get<2>(handTuple);

		Result actual = compare(player, opponent);

		if (actual != expected)
		{
			std::cout << "Incorrect result for hands: " << std::get<0>(handTuple) << " vs " << std::get<1>(handTuple) << std::endl;
			std::cout << "Expected: ";
			switch (expected)
			{
			case Result::Win:
				std::cout << "Win";
				break;
			case Result::Loss:
				std::cout << "Loss";
				break;
			case Result::Tie:
				std::cout << "Tie";
				break;
			}
			std::cout << ", Actual: ";
			switch (actual)
			{
			case Result::Win:
				std::cout << "Win";
				break;
			case Result::Loss:
				std::cout << "Loss";
				break;
			case Result::Tie:
				std::cout << "Tie";
				break;
			}
			std::cout << std::endl;
		}
	}
}

int main()
{
	std::vector<std::tuple<std::string, std::string, Result>> testCases = {
		// Insert your test cases here
		{"3H 4C 4H 3S 2H", "6S 8S 7S 5H 9H", Result::Loss},
		{"QC KH TS JS AH", "JH 8S TH AH QH", Result::Win},
		{"5S 5D 2C KH KH", "9D 8H 2C 6S 7H", Result::Win},
		{"8C 9C 5C 3C TC", "TC 8C 2S JH 6C", Result::Win},
		{"4C 5C 9C 8C KC", "KS 8D 4D 9S 4S", Result::Win},
		{"2D 6D 9D TH 7D", "AS 3C KH AD KH", Result::Loss},
		{"3S 8S 9S 5S KS", "JH 8S TH AH QH", Result::Win},
		{"JH AH TH KH QH", "9D 8H 2C 6S 7H", Result::Win},
		{"QH 8H KD JH 8S", "5C 6C 3C 7C 4C", Result::Loss},
		{"KC 4H KS 2H 8D", "JH 9H TH KH QH", Result::Loss},
		{"3C 5C 4C 2C AH", "8C 4S KH JS 4D", Result::Win},
		{"TC 8C 2S JH 6C", "TC 8C 2S JH 6C", Result::Tie},
		{"3D 2H 3H 2C 2D", "TS KS 5S 9S AC", Result::Win},
		{"2D 6D 9D TH 7D", "AS 3C KH AD KH", Result::Loss},
		{"KC 4H KS 2H 8D", "JH 8S TH AH QH", Result::Win},
		{"2D 6D 3D 4D 5D", "AH 8S AS KC JH", Result::Win},
		{"4C 5C 9C 8C KC", "QH 8H KD JH 8S", Result::Win},
		{"TS KS 5S 9S AC", "2H 2C 3S 3H 3D", Result::Loss},
		{"KC 4H KS 2H 8D", "KH KC 3S 3H 3D", Result::Loss},
		{"6S 8S 7S 5H 9H", "JH 9H TH KH QH", Result::Loss},
		{"4C 5C 9C 8C KC", "QC KH TS JS AH", Result::Win},
		{"TC 8C 2S JH 6C", "5S 5D 2C KH KH", Result::Loss},
		{"7C 7S 3S 7H 5S", "KH KC 3S 3H 3D", Result::Loss},
		{"TS KS 5S 9S AC", "3S 8S 9S 5S KS", Result::Loss},
		{"7C 7S 3S 7H 5S", "3C KH 5D 5S KH", Result::Win},
		{"5S 5D 2C KH KH", "JH 9H TH KH QH", Result::Loss},
		{"3H 4C 4H 3S 2H", "7C 7S 3S 7H 5S", Result::Loss},
		{"2D 6D 9D TH 7D", "TC 8C 2S JH 6C", Result::Loss},
		{"KD 4S KC 3H 8S", "JC 6H JS JD JH", Result::Loss},
		{"AC KH QH AH AS", "KC 4H KS 2H 8D", Result::Win},
		{"5C 6C 3C 7C 4C", "3C KH 5D 5S KH", Result::Win},
		{"JS QS 9H TS KH", "QC KH TS JS AH", Result::Loss},
		{"5S 5D 2C KH KH", "7C 7S 3S 7H 5S", Result::Loss},
		{"JH 8S TH AH QH", "QC KH TS JS AH", Result::Loss},
		{"JH 9H TH KH QH", "3S 8S 9S 5S KS", Result::Win},
		{"AH 8S AS KC JH", "3C KH 5D 5S KH", Result::Loss},
		{"4S 3H 2C 7S 5H", "3C KH 5D 5S KH", Result::Loss},
		{"3D 2H 3H 2C 2D", "7C 7S KH 2H 7H", Result::Win},
		{"2D 6D 3D 4D 5D", "JS QS 9H TS KH", Result::Win},
		{"JC 7H JS JD JH", "5S 5D 2C KH KH", Result::Win},
		{"JH 8H AH KH QH", "5C 6C 3C 7C 4C", Result::Loss},
		{"AH 8S AS KC JH", "2D 6D 9D TH 7D", Result::Win},
		{"5S 5D 2C KH KH", "TC 8C 2S JH 6C", Result::Win},
		{"JC 7H JS JD JH", "3S 8S 9S 5S KS", Result::Win},
		{"2D 6D 3D 4D 5D", "3H 4C 4H 3S 2H", Result::Win},
		{"5C 6C 3C 7C 4C", "JC 7H JS JD JH", Result::Win},
		{"7C 7S 3S 7H 5S", "QH 8H KD JH 8S", Result::Win},
		{"KS 8D 4D 9S 4S", "KH KC 3S 3H 3D", Result::Loss},
		{"AS 3C KH AD KH", "AH 8S AS KC JH", Result::Win},
		{"KD 6S 9D TH AD", "5S 5D 2C KH KH", Result::Loss},
		{"4C 5C 9C 8C KC", "KS 8D 4D 9S 4S", Result::Win},
		{"3D 2H 3H 2C 2D", "JH 8H AH KH QH", Result::Win},
		{"KD 4S KC 3H 8S", "QH 8H KD JH 8S", Result::Win},
	};

	testPokerHands(testCases);

	return 0;
}
