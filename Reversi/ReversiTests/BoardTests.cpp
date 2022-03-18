#include "pch.h"
#include "Board.h"
#include "TestUtils.h"
TEST(Board, BoardSetUp) {
	// Arrange
	Board boardInit;
	Board boardSetUp;

	// Act
	boardInit.initBoard();
	boardSetUp.setUpBoard("________|________|________|___ox___|___xo___|________|________|________");
	
	// Assert
	EXPECT_TRUE(CompareBoardFields(boardInit, boardSetUp));
}

TEST(Board, PossibleFieldsEdgeCaseMinusSeven) {
	// Arrange
	Board board;
	board.setUpBoard("________|________|___x___x|__oooo_x|___ooxxx|___o_o__|________|________");

	Player testPlayer(Token::Colour::blue);
	testPlayer.addPossibleField(Field(2, 3));
	testPlayer.addPossibleField(Field(2, 4));
	testPlayer.addPossibleField(Field(2, 5));
	testPlayer.addPossibleField(Field(6, 7));
	testPlayer.addPossibleField(Field(6, 8));

	// Act
	Player player(Token::Colour::blue);
	board.calculatePossibleFields(player);

	// Assert
	EXPECT_TRUE(ComparePossibleFields(testPlayer, player));
}

TEST(Board, PossibleFieldsEdgeCasePlusSeven) {
	// Arrange
	Board board;
	board.setUpBoard("________|________|________|__oxx___|xxoxo___|x__xo___|____o___|________");

	Player testPlayer(Token::Colour::blue);
	testPlayer.addPossibleField(Field(3, 3));
	testPlayer.addPossibleField(Field(3, 5));
	testPlayer.addPossibleField(Field(4, 6));
	testPlayer.addPossibleField(Field(6, 3));
	testPlayer.addPossibleField(Field(7, 3));

	// Act
	Player player(Token::Colour::blue);
	board.calculatePossibleFields(player);

	// Assert
	EXPECT_TRUE(ComparePossibleFields(testPlayer, player));
}

TEST(Board, PossibleFieldsEdgeCaseMinusNine) {
	// Arrange
	Board board;
	board.setUpBoard("________|________|________|__oxo___|__xxo___|ooox____|_x______|________");

	Player testPlayer(Token::Colour::green);
	testPlayer.addPossibleField(Field(3, 2));
	testPlayer.addPossibleField(Field(3, 3));
	testPlayer.addPossibleField(Field(3, 6));
	testPlayer.addPossibleField(Field(4, 2));
	testPlayer.addPossibleField(Field(4, 6));
	testPlayer.addPossibleField(Field(5, 2));
	testPlayer.addPossibleField(Field(5, 6));
	testPlayer.addPossibleField(Field(6, 6));
	testPlayer.addPossibleField(Field(7, 1));
	testPlayer.addPossibleField(Field(7, 3));

	// Act
	Player player(Token::Colour::green);
	board.calculatePossibleFields(player);

	// Assert
	EXPECT_TRUE(ComparePossibleFields(testPlayer, player));
}

TEST(Board, PossibleFieldsEdgeCasePlusNine) {
	// Arrange
	Board board;
	board.setUpBoard("________|________|________|___ooox_|__xxxooo|____xx__|________|________");

	Player testPlayer(Token::Colour::green);
	testPlayer.addPossibleField(Field(3, 3));
	testPlayer.addPossibleField(Field(3, 4));
	testPlayer.addPossibleField(Field(3, 5));
	testPlayer.addPossibleField(Field(3, 6));
	testPlayer.addPossibleField(Field(3, 7));
	testPlayer.addPossibleField(Field(4, 3));
	testPlayer.addPossibleField(Field(4, 8));
	testPlayer.addPossibleField(Field(6, 7));
	
	// Act
	Player player(Token::Colour::green);
	board.calculatePossibleFields(player);

	// Assert
	EXPECT_TRUE(ComparePossibleFields(testPlayer, player));
}

TEST(Board, PossibleFieldsDiagonals) {
	// Arrange
	Board board;
	board.setUpBoard("________|________|___x____|__oooo__|___xoo__|_____o__|________|________");

	Player testPlayer(Token::Colour::green);
	testPlayer.addPossibleField(Field(3, 2));
	testPlayer.addPossibleField(Field(3, 6));
	testPlayer.addPossibleField(Field(5, 2));
	testPlayer.addPossibleField(Field(5, 7));
	testPlayer.addPossibleField(Field(6, 7));

	// Act
	Player player(Token::Colour::green);
	board.calculatePossibleFields(player);

	// Assert
	EXPECT_TRUE(ComparePossibleFields(testPlayer, player));
}

TEST(Board, OccupiedFieldsBlue) {
	// Arrange
	Board board;
	board.setUpBoard("________|________|___x____|__oooo__|___xoo__|_____o__|________|________");

	Player testPlayerBlue(Token::Colour::blue);
	testPlayerBlue.addOccupiedField(Field(4, 3));
	testPlayerBlue.addOccupiedField(Field(4, 4));
	testPlayerBlue.addOccupiedField(Field(4, 5));
	testPlayerBlue.addOccupiedField(Field(4, 6));
	testPlayerBlue.addOccupiedField(Field(5, 5));
	testPlayerBlue.addOccupiedField(Field(5, 6));
	testPlayerBlue.addOccupiedField(Field(6, 6));

	Player testPlayerGreen(Token::Colour::green);
	testPlayerGreen.addOccupiedField(Field(3, 4));
	testPlayerGreen.addOccupiedField(Field(5, 4));

	// Act
	Player playerBlue(Token::Colour::blue);
	board.calculateOccupiedFields(playerBlue);

	Player playerGreen(Token::Colour::green);
	board.calculateOccupiedFields(playerGreen);

	// Assert
	EXPECT_TRUE(ComparePossibleFields(testPlayerBlue, playerBlue));
	EXPECT_TRUE(ComparePossibleFields(testPlayerGreen, playerGreen));
}

TEST(Board, AddBlueToken) {
	// Arrange
	Board board;
	board.setUpBoard("________|___o____|__xxxxo_|__xxo___|_x_oxo__|___o____|________|________");

	Board boardResult;
	boardResult.setUpBoard("________|___o____|__oxxxo_|_oooo___|_x_oxo__|___o____|________|________");

	Player testPlayerBlue(Token::Colour::blue);
	
	Player playerBlue(Token::Colour::blue);
	boardResult.calculateOccupiedFields(playerBlue);

	// Act
	board.placeToken(Position(4, 2), Token::Colour::blue);
	board.calculateOccupiedFields(testPlayerBlue);

	// Assert
	EXPECT_TRUE(CompareOccupiedFields(testPlayerBlue, playerBlue));
	EXPECT_TRUE(CompareBoardFields(board, boardResult));
}

TEST(Board, AddTheUltimateGreenToken) {
	// Arrange
	Board board;
	board.setUpBoard("xxxxxxxx|xoooooox|xoooooox|xoo_ooox|xoooooox|xoooooox|xoooooox|xxxxxxxx");

	Board boardResult;
	boardResult.setUpBoard("xxxxxxxx|xxoxoxox|xoxxxoox|xxxxxxxx|xoxxxoox|xxoxoxox|xooxooxx|xxxxxxxx");

	Player testPlayerGreen(Token::Colour::green);

	Player playerGreen(Token::Colour::green);
	boardResult.calculateOccupiedFields(playerGreen);

	// Act
	board.placeToken(Position(4, 4), Token::Colour::green);
	board.calculateOccupiedFields(testPlayerGreen);

	// Assert
	EXPECT_TRUE(CompareOccupiedFields(testPlayerGreen, playerGreen));
	EXPECT_TRUE(CompareBoardFields(board, boardResult));
}

TEST(Board, ChangeTokensDontMoveThrough_Up) {
	// Arrange
	Board board;
	board.setUpBoard("________|________|__xoo___|___x_x__|___o__o_|___x____|________|________");

	Board boardResult;
	boardResult.setUpBoard("________|________|__xoo___|___x_x__|___o__o_|___o____|___o____|________");

	Player testPlayerBlue(Token::Colour::blue);

	Player playerBlue(Token::Colour::blue);
	boardResult.calculateOccupiedFields(playerBlue);

	// Act
	board.placeToken(Position(7, 4), Token::Colour::blue);
	board.calculateOccupiedFields(testPlayerBlue);

	// Assert
	EXPECT_TRUE(CompareOccupiedFields(testPlayerBlue, playerBlue));
	EXPECT_TRUE(CompareBoardFields(board, boardResult));
}

TEST(Board, ChangeTokensDontMoveThrough_Right_RightDown) {
	// Arrange
	Board board;
	board.setUpBoard("________|________|___o____|___ooxo_|___o____|____x___|_____o__|________");

	Board boardResult;
	boardResult.setUpBoard("________|________|___o____|__xxxxo_|___x____|____x___|_____o__|________");

	Player testPlayerGreen(Token::Colour::green);

	Player playerGreen(Token::Colour::green);
	boardResult.calculateOccupiedFields(playerGreen);

	// Act
	board.placeToken(Position(4, 3), Token::Colour::green);
	board.calculateOccupiedFields(testPlayerGreen);

	// Assert
	EXPECT_TRUE(CompareOccupiedFields(testPlayerGreen, playerGreen));
	EXPECT_TRUE(CompareBoardFields(board, boardResult));
}

TEST(Board, ChangeTokensDontMoveThrough_Left_Up_LeftUp) {
	// Arrange
	Board board;
	board.setUpBoard("________|________|______x_|___x__o_|____o_x_|_____xx_|__xoxx__|________");

	Board boardResult;
	boardResult.setUpBoard("________|________|______x_|___x__o_|____o_o_|_____oo_|__xoooo_|________");

	Player testPlayerBlue(Token::Colour::blue);

	Player playerBlue(Token::Colour::blue);
	boardResult.calculateOccupiedFields(playerBlue);

	// Act
	board.placeToken(Position(7, 7), Token::Colour::blue);
	board.calculateOccupiedFields(testPlayerBlue);

	// Assert
	EXPECT_TRUE(CompareOccupiedFields(testPlayerBlue, playerBlue));
	EXPECT_TRUE(CompareBoardFields(board, boardResult));
}

TEST(Board, ChangeTokensDontMoveThrough_Down_RightUp) {
	// Arrange
	Board board;
	board.setUpBoard("________|_____o__|____xo__|___ox___|___o____|__o_____|__x_____|__o_____");

	Board boardResult;
	boardResult.setUpBoard("________|_____o__|____xo__|___xx___|__xo____|__x_____|__x_____|__o_____");

	Player testPlayerGreen(Token::Colour::green);

	Player playerGreen(Token::Colour::green);
	boardResult.calculateOccupiedFields(playerGreen);

	// Act
	board.placeToken(Position(5, 3), Token::Colour::green);
	board.calculateOccupiedFields(testPlayerGreen);

	// Assert
	EXPECT_TRUE(CompareOccupiedFields(testPlayerGreen, playerGreen));
	EXPECT_TRUE(CompareBoardFields(board, boardResult));
}

TEST(Board, ChangeTokensDontMoveThrough_Down_LeftDown) {
	// Arrange
	Board board;
	board.setUpBoard("________|________|________|____xx__|___x_o__|__o__x__|_x______|________");

	Board boardResult;
	boardResult.setUpBoard("________|________|_____o__|____oo__|___o_o__|__o__x__|_x______|________");

	Player testPlayerBlue(Token::Colour::blue);

	Player playerBlue(Token::Colour::blue);
	boardResult.calculateOccupiedFields(playerBlue);

	// Act
	board.placeToken(Position(3, 6), Token::Colour::blue);
	board.calculateOccupiedFields(testPlayerBlue);

	// Assert
	EXPECT_TRUE(CompareOccupiedFields(testPlayerBlue, playerBlue));
	EXPECT_TRUE(CompareBoardFields(board, boardResult));
}