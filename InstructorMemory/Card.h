/*Card.h
 * Peter Bartosch and Ross Greenman
 * created: 4/11/2013
 * last modified: 4/15/2013
 * IS346 - Instructor Memory
 * Kahn
 *
 * defines class: Card
 * It's a Card for a game of memory.  I don't have time for commenting right now.
 *
 */
#ifndef CARD_H
#define CARD_H

#include "idrawable.h"
#include "iupdatable.h"
#include "vector2.h"
#include "vector3.h"

//Forward declaration to avoid compiler issues
class Board;

class Card : public IUpdatable, public IDrawable
{
public:
	/*Card()
	 * takes: nothing
	 * returns: nothing
	 *
	 * Default ctor, inits everything to NULL or equivilent.
	 */
	Card();

	/*init(rowCol, faceTexId, backTexId)
	 * takes: a row,column position and texture ids for the face and back
	 * returns: nothing
	 *
	 * This will do the inits for the Card.
	 *
	 */
	void init(Vector2 rowCol, GLuint faceTexId, GLuint backTexId);

	//NEED COMMENT!
	void moveToRC(int row, int col);

	/*collideWithCard(position)
	 * takes: a Vector3 representing the position to check
	 * returns: true if that position collides with the Card; false otherwise.
	 *
	 */
	bool collideWithCard(Vector3 position);

	/*faceUp()
	 * takes: nothing
	 * returns: true if the Card's face is showing; false otherwise.
	 *
	 */
	bool faceUp();

	/*flip()
	 * takes: nothing
	 * returns: nothing
	 *
	 * This will flip the card over by flagging the card for updates and for
	 * flipping.  The texture swap will occur in the update.
	 *
	 */
	void flip();

	/*getFaceTextureId()
	 * takes: nothing
	 * returns: A GLuint for the id of the face texture.
	 *
	 */
	GLuint getFaceTextureId();

	/*setFaceTextureId(faceTex)
	 * takes: A GLuint for the id of the face texture.
	 * returns: nothing
	 *
	 */
	void setFaceTextureId(GLuint faceTex);

	/*getBackTextureId()
	 * takes: nothing
	 * returns: A GLuint for the id of the back texture.
	 *
	 */
	GLuint getBackTextureId();

	/*setBackTextureId(backTex)
	 * takes: A GLuint for the id of the back texture.
	 * returns: nothing
	 *
	 */
	void setBackTextureId(GLuint backTex);

	Vector2& getRowCol();

	//IUpdtable implementation
	virtual void enableUpdates();
	virtual void disableUpdates();
	virtual bool canUpdate();
	virtual void update(float dt);
	
	//IDrawable implementation
	virtual void enable();
	virtual void disable();
	virtual bool isEnabled();
	virtual int getPriority();
	virtual void setPriority(int);
	virtual void draw();
private:
	Vector2 _rowCol;
	bool _canDraw;
	int _drawPriority;
	Vector3 _center;
	bool _showFace;
	GLuint _faceTex;
	GLuint _backTex;
	bool _canUpdate;
	float _wPct;
	bool _flipping;
	float _flipSpeed;
	Color4 _faceColor;
	Color4 _backColor;
};
#endif