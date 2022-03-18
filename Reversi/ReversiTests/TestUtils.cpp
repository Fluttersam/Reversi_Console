#include "pch.h"
#include "TestUtils.h"

bool CompareBoardFields(Board& boardA, Board& boardB)
{
	auto fieldsA = boardA.getFields();
	auto fieldsB = boardB.getFields();

	for (size_t i = 0; i < fieldsA.size(); i++)
	{
		if (fieldsA[i] != fieldsB[i])
			return false;
	}

	return true;
}

bool ComparePossibleFields(Player& playerA, Player& playerB)
{
	auto fieldsA = playerA.getPossibleFields();
	auto fieldsB = playerB.getPossibleFields();

	for (size_t i = 0; i < fieldsA.size(); i++)
	{
		if (fieldsA[i] != fieldsB[i])
			return false;
	}

	return true;
}

bool CompareOccupiedFields(Player& playerA, Player& playerB)
{
	auto fieldsA = playerA.getOccupiedFields();
	auto fieldsB = playerB.getOccupiedFields();

	for (size_t i = 0; i < fieldsA.size(); i++)
	{
		if (fieldsA[i] != fieldsB[i])
			return false;
	}

	return true;
}