# X-Tetris
X-Tetris is a reinterpretation of the traditional Tetris game written entirely in the ANSI C standard and was realised by myself and a university colleague.
The game consists of three modes: singleplayer, multiplayer and player vs. CPU.
The three modes are accessible via an initial game menu, from which the scoreboard and command section can also be accessed.

![Menu](/screenshot/screenshot_1.png)

## Singleplayer
Unlike the original Tetris, in X-Tetris the player is initially given 20 (or more, the choice is yours) pieces of each type, called tetramino, and a move consists of choosing which piece to play, where to drop it and with what rotation.
The playing field is 10 wide and 15 high. Once a tetramino has been placed, if one or more horizontal rows are filled in completely, these rows are deleted as in the original tetris.
Removing one row is worth 1 point, removing two rows with one piece is worth 3 points, three rows 6 points, four rows 12 points.
The game ends when the pieces run out or the player fails to place a tetramino in the playing field respecting the height limit.

![Singleplayer](/screenshot/screenshot_2.png)

## Multiplayer
The two players play alternating turns each on their own playing field but drawing from the same set of tetramino pieces. In this mode you will have twice as many pieces at your disposal. In case a player deletes one or two lines simultaneously, the game proceeds as for the single player case. In case the player deletes 3 or more lines with a single move, the opponent's field is changed by reversing the corresponding number of lines in the lowest part of the playing field: an empty position becomes full and vice versa.
A player loses the game if he does not place a piece correctly on his playing field. If the pieces run out, the player with the highest score wins.

![Multiplayer](/screenshot/screenshot_3.png)

## CPU Implementation
The strategy implemented for the CPU part is very simple but not random. 
In fact, at each turn, the programme will choose from all possible combinations of each tetramino, i.e. for each horizontal position and for each rotation, the piece that will occupy the most empty positions among the last occupied rows.

## Contributing
Being our first graphics project we understand that the code may not be perfect, so pull requests are welcome as well as advice and criticism.
