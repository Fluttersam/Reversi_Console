The game reversi written in C++ as a console game.

How it works:
Normally the board is 8x8 and starts with four tokens in the middle of the board.
The goal of the game is to have more tokens than your opponent.
You will have to enter x and y numbers sepparatly.*+*

Now each round the active player places a token on the board which must fulfill the following conditions:
* it must be next to at least one opponent token
* it has to turn at least one opponent token to the active players colour.

This goes on until the game ends, which happens int the following cases:
* the board is full with tokens
* both players can't place any tokens 
* one player doesn't have any tokens left on the board.

Who ever has more tokens at the end wins.

The game also features a mode were you can play alone against the CPU.
There are three difficulties from which you can choose from:
* 1 easy: chooses a random field to place a token
* 2 normal: chooses the field from which it can turn tokens in the most directions
* 3 hard: chooses the field from which it turns the most tokens.

This project also features automated tests.

*+*
Important: x refers to the column and y to the row number.
This is because I built my position class like coordinates
and only realized the mistake/confusions it causes after all the logic was already implemented.