#include "pch.h"
#include "Gamecontroller.h"

TEST(WinningCondition, BlueWins) {
	// Arrange
	GameController gameCTRL;
	Board board = gameCTRL.getBoard();

	board.setUpBoard("oooxxoox|xxooxxox|oxoooxox|xxooooxx|ooxooxxx|xxooxoox|xooxxoox|oooxxoox");

	// Act
	board.calculateOccupiedFields(gameCTRL.getPlayer1());
	board.calculateOccupiedFields(gameCTRL.getPlayer2());

	// 34 blue o:30 green x
	// Assert
	EXPECT_EQ(gameCTRL.evaluateWinner(), "o");
}

TEST(WinningCondition, Draw) {
	// Arrange
	GameController gameCTRL;
	Board board = gameCTRL.getBoard();

	board.setUpBoard("oooooooo|oooooooo|oooooooo|oooooooo|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx");

	// Act
	board.calculateOccupiedFields(gameCTRL.getPlayer1());
	board.calculateOccupiedFields(gameCTRL.getPlayer2());

	// 32 blue o:32 green x
	// Assert
	EXPECT_EQ(gameCTRL.evaluateWinner(), "Everyone wins");
}

TEST(WinningCondition, GreenWins) {
	// Arrange
	GameController gameCTRL;
	Board board = gameCTRL.getBoard();

	board.setUpBoard("oooooooo|oooooooo|oooooooo|oooxxooo|xxxxxxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx");
	
	// Act
	board.calculateOccupiedFields(gameCTRL.getPlayer1());
	board.calculateOccupiedFields(gameCTRL.getPlayer2());

	// 30 blue o:34 green x
	// Assert
	EXPECT_EQ(gameCTRL.evaluateWinner(), "x");
}