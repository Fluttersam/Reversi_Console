#include "pch.h"
#include "Gamecontroller.h"
#include "TestUtils.h"

TEST(CPU, DifficultyNormal) {
	// Arrange
	GameController gameCTRL;
	Board board = gameCTRL.getBoard();

	board.setUpBoard("________|________|___x_x__|_x_oox__|_xooo___|________|________|________");

	gameCTRL.makePlayer2CPU(Player::Difficulty::normal);
	Player cpuPlayer = gameCTRL.getPlayer2();

	Board boardResult;
	boardResult.setUpBoard("________|________|___x_x__|_x_xox__|_xxxx___|___x____|________|________");

	Player testPlayer(Token::Colour::green, Player::Difficulty::normal);

	testPlayer.addOccupiedField(Field(3, 4, Token::Colour::green));
	testPlayer.addOccupiedField(Field(3, 6, Token::Colour::green));
	testPlayer.addOccupiedField(Field(4, 2, Token::Colour::green));
	testPlayer.addOccupiedField(Field(4, 4, Token::Colour::green));
	testPlayer.addOccupiedField(Field(4, 6, Token::Colour::green));
	testPlayer.addOccupiedField(Field(5, 2, Token::Colour::green));
	testPlayer.addOccupiedField(Field(5, 3, Token::Colour::green));
	testPlayer.addOccupiedField(Field(5, 4, Token::Colour::green));
	testPlayer.addOccupiedField(Field(5, 5, Token::Colour::green));
	testPlayer.addOccupiedField(Field(6, 4, Token::Colour::green));

	// Act
	board.calculatePossibleFields(cpuPlayer);
	Position position = cpuPlayer.selectPossibleField(board);
	board.placeToken(position, cpuPlayer.getColour());
	board.calculateOccupiedFields(cpuPlayer);

	// Assert
	EXPECT_TRUE(CompareBoardFields(board, boardResult));
	EXPECT_TRUE(CompareOccupiedFields(cpuPlayer, testPlayer));
}

TEST(CPU, DifficultyHard) {
	// Arrange
	GameController gameCTRL;
	Board board = gameCTRL.getBoard();

	board.setUpBoard("________|________|________|___xo___|x__xx___|_o_oo___|__oo____|________");

	Board boardResult;
	boardResult.setUpBoard("________|________|________|___xo___|x__xx___|_x_xo___|__xx____|___x____");

	gameCTRL.makePlayer2CPU(Player::Difficulty::hard);
	Player cpuPlayer = gameCTRL.getPlayer2();

	Player testPlayer(Token::Colour::green, Player::Difficulty::hard);

	testPlayer.addOccupiedField(Field(4, 4, Token::Colour::green));
	testPlayer.addOccupiedField(Field(5, 1, Token::Colour::green));
	testPlayer.addOccupiedField(Field(5, 4, Token::Colour::green));
	testPlayer.addOccupiedField(Field(5, 5, Token::Colour::green));
	testPlayer.addOccupiedField(Field(6, 2, Token::Colour::green));
	testPlayer.addOccupiedField(Field(6, 4, Token::Colour::green));
	testPlayer.addOccupiedField(Field(7, 3, Token::Colour::green));
	testPlayer.addOccupiedField(Field(7, 4, Token::Colour::green));
	testPlayer.addOccupiedField(Field(8, 4, Token::Colour::green));

	// Act
	board.calculatePossibleFields(cpuPlayer);
	Position position = cpuPlayer.selectPossibleField(board);
	board.placeToken(position, cpuPlayer.getColour());
	board.calculateOccupiedFields(cpuPlayer);

	// Assert
	EXPECT_TRUE(CompareBoardFields(board, boardResult));
	EXPECT_TRUE(CompareOccupiedFields(cpuPlayer, testPlayer));
}