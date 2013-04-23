#ifndef _AIPLAYER_H_
#define _AIPLAYER_H_

#include "player.h"
#include "iupdatable.h"

class AIPlayer : public Player, public IUpdatable
{
public:
	AIPlayer();
	AIPlayer(int difficulty);

	virtual void init(const Color4 cGrad[2]);
	virtual Card* selectCard();
	void setBufferSize(int newSize);
	int getBufferSize();
	int getCardsRemembered();
	Card** getCardBuffer();

	//IUpdatable implementation
	virtual void enableUpdates();
	virtual void disableUpdates();
	virtual bool canUpdate();
	virtual void update(float dt);

	//draw override
	virtual void draw();
private:
	Card** _cardBuffer;
	Card* _nextSelect;
	Card* _selected;
	int _maxBufferSize;
	int _cardsRemembered;
	int _bufferIdx;
	bool _selectedOneCard;
	bool _canUpdate;
	float _flipTimer;
	float _flipWait;

	Card* findCardToSelect();

};
#endif