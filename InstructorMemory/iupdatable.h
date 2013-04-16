/*iupdatable.h
 * Peter Bartosch and Ross Greenman
 * created: 4/15/2013
 * last modified: 4/15/2013
 *
 * defines interface: IUpdatable
 * IUpdatable is an interface that should be implemented by classes that intend
 * to be updated during the game loop.  It defines an update function and as
 * well as a method for determining if that update should happen.  Maybe some
 * sort of timing should be involved?
 *
 * This is a test, we'll see if this stays.
 *
 */
#ifndef _IUPDATABLE_H_
#define _IUPDATABLE_H_

class IUpdatable
{
public:
	/*enableUpdates()
	 * takes: nothing
	 * returns: nothing
	 * 
	 * This marks the object as being able to do updates.
	 *
	 */
	virtual void enableUpdates()=0;

	/*disableUpdates()
	 * takes: nothing
	 * returns: nothing
	 *
	 * This marks the object as being unable to do updates.
	 *
	 */
	virtual void disableUpdates()=0;

	/*canUpdate()
	 * takes: nothing
	 * returns: true if the object can do updates; false otherwise.
	 *
	 */
	virtual bool canUpdate()=0;

	/*update(dt)
	 * takes: a float for the number of seconds passed since the last update
	 * returns: nothing
	 *
	 * This is where the meat of the updating happens for any IUpdatable.  The
	 * passed time variable may or may not be used, but since updates tend to
	 * be done with motion, it seems like a necessary variable.
	 *
	 */
	virtual void update(float dt)=0;
};
#endif