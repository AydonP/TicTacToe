<div align="center">
  <img height="100px" src="https://github.com/AydonP/TicTacToe/assets/81772180/729609c1-1387-4b11-abb6-29e40f892a5a">
  <br>
  
  [<img src="https://github.com/AydonP/TicTacToe/actions/workflows/static.yml/badge.svg">](https://aydonp.github.io/TicTacToe/)
  
</div>


## About
A simple version of Tic Tac Toe created and themed for an event. The longer the game goes on, the computer will be more likely to choose a random move instead of the best one.

## Usage
You can download an already-compiled version in Github Releases or use the version hosted on GitHub pages [here](https://aydonp.github.io/TicTacToe/).

This project uses emscripten to build. You can use the scripts `configure && build` to wrap emscripten. You can also manually define the `TICTACTOE_WON_CODE` macro to change the JavaScript code ran when the player finishes. It is stored in the Webassembly file to try to prevent inspection from browser dev tools. If you don't want it to do anything besides go to the finish screen when the player wins, this can be set to `;`. By default, if it is not defined, it will be set to `alert("You won!!")`.

If you compile it normally, without emscripten, it will compile as a console based TicTacToe game used for development.
