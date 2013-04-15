/*game.h
 * Peter Bartosch and Ross Greenman
 * created: 4/13/2013
 * last modified: 4/13/2013
 * IS346 - Instructor Memory
 * Kahn
 *
 * defines class: Game
 * Game is a singleton for organizing and running the entire game of Instructor
 * Memory.  The Game contains information for all cards, the deck of cards, the
 * Board, the Players and any other information pertinent to the playing of
 * Instructor Memory.  A Game is not drawn, and implements no interfaces.  It
 * does have a function (displayGame) that is used as the glutDisplayFunc.  As
 * this grows the class will probably also contain an update function and define
 * inputs.  As long as none of the classes withn Game need to refer back to
 * it, then it should be okay to include their headers.  Otherwise we will
 * need to foward declare the classes and then go from there.
 *
 */
#ifndef _GAME_H_
#define _GAME_H_

#include <queue>
#include "idrawable.h"
#include "card.h"
#include "deck.h"
#include "board.h"
#include "player.h"

using std::priority_queue;

class Game
{
public:
    /*instance()
     * takes: nothing
     * returns: a pointer to the instance of Game.
     *
     * If the private static variable _instance is NULL when this is called,
     * we will create the instance, and mark it as un-init'd.  All methods that
     * require the _instance to be init'd will have to check that state or
     * perish.
     */
    static Game* instance();
    
    /*displayGame()
     * take: nothing
     * returns: nothing
     *
     * This will go through the priority queue for IDrawables and draw them.
     * This should be registered as the glutDisplayFunc, and because of that it
     * is a static method.
     *
     */
    static void displayGame();
private:
    static Game* _instance;
    
    private priority_queue<IDrawable*, IDrawableCompare> _drawables;
};
#endif