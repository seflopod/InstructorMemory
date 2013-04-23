#ifndef _AIPLAYER_H_
#define _AIPLAYER_H_

#include "player.h"
#include "iupdatable.h"

class AIPlayer : Player, IUpdatable
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
private:
	Card** _cardBuffer;
	Card* _nextSelect;
	int _maxBufferSize;
	int _cardsRemembered;
	bool _selectedOneCard;
	bool _canUpdate;
	float _flipTimer;

};
#endif