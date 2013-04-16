/*board.h
 * Peter Bartosch and Ross Greenman
 * created: 4/13/2013
 * last modified: 4/13/2013
 * IS346 - Instructor Memory
 * Kahn
 *
 * defines class: Board
 * The Board class implements the IDrawable interface.  It contains data for
 * its texture and/or color.  It also keeps track of the number of rows and
 * columns it has for placing Cards.  It has maximum values for x and y which
 * allows it to have the Vector2 functions that convert between (row,column) and
 * (x,y).
 *
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include "idrawable.h"
#include "vector2.h"
#include "vector3.h"

class Board : public IDrawable
{
public:
	//The Board needs to know how big Cards are in order to properly
	//do coordinate conversions.  The Board will define the size of
	//each card for uniformity.  This is static to get around the 
	//fact that this is probably bad design.
	const float CARD_WIDTH = 90.0f;
	const float CARD_HEIGHT = 140.0f;
	const float SIDE_MARGIN;
	const float CARD_HMARGIN;
	const float VERT_MARGIN;
	const float CARD_VMARGIN;

    /*Board()
     * takes: nothing
     * returns: nothing
     *
     * Default ctor for the Board.  This does not define anything, this will
     * only make sure that which needs some form of initialization receives
     * that init.  Use init for full initialization.
     *
     */
    Board();
    
    /*init(rows, cols)
     * takes: values for the number of rows and the number of columns
     * returns: nothing
     *
     * Initializes all values to default values, and uses the passed row and
     * column information to setup the bool array for card placement.
     *
     */
    void init(int, int);
    
    /*positionBoard(center)
     * takes: a Vector3 for the Board's position
     * returns: nothing
     *
     */
    void positionBoard(Vector3&);
    
    /*XYtoRC(&xyCoords)
     * takes: a reference to a Vector3 containing coordinate data
     * returns: a new Vector2 object that holds row, column data
     *
     * This will use the Board's information about xy and rc to convert the
     * values.  This assumes that the slot given to (row=0,col=0) has its
     * bottom-left corner at the origin.
     *
     */
    Vector2 XYtoRC(Vector3&);
    
    /*RCtoXY(&rcValues)
     * takes: a reference to a Vector2 containing row, column data
     * returns a new Vector2 object that holds coordinate data
     *
     * Does the opposite of XYtoRC.
     *
     */
    Vector3 RCtoXY(Vector2&);
    
    /*placeCardOnBoard(row, col, card)
     * takes: a pointer to the Card to place on the board and its position.
     * returns: nothing
     *
     */
    void placeCardOnBoard(int, int, Card*);
    
    /*removeCardFromBoard(row, col)
     * takes: the row and column for the card to remove
     * returns: a poitner to the Card removed
     *
     */
    Card* removeCardFromBoard(int, int);
    
    /*destroy()
     * takes: nothing
     * returns: nothing
     *
     * dtor replacement
     *
     */
    void destroy();
    
    //IDrawable implementation
    virtual void enable();
    virtual void disable();
    virtual bool isEnabled();
    virtual int getPriority();
    virtual void setPriority(int);
    virtual void draw();
private:
    Vector3 _center;
    int _rows;
    int _cols;
    Card* _cards;
    bool _canDraw;
    int _drawPriority;
};
#endif
 
