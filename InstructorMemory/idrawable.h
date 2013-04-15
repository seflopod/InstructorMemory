/*idrawable.h
 * Peter Bartosch
 * created: 4/6/2013
 * last modified: 4/13/2013
 * IS346 - Instructor Memory
 * Kahn
 *
 * defines interface: IDrawable
 * This is an interface used to flag an object as something to be drawn.  It
 * makes sure that there is a draw function and a means to enable and disable
 * the object in regards to being drawn.
 *
 * defines class: IDrawableCompare
 * IDrawableCompare is a utility class used for comparing two IDrawable objects.
 * I'm not entirely sure of why I overload (), so I will be looking into that.
 * For now, I'm content with knowing that this should work.  Used
 * http://comsci.liu.edu/~jrodriguez/cs631sp08/c++priorityqueue.html for
 * reference.
 *
 * Since IDrawableCompare is inextricably linked to IDrawable, it made the most
 * sense to define it within the same file and header guards.
 *
 */
#ifndef _IDRAWABLE_H_
#define _IDRAWABLE_H_

//since math.h will be used for a number of drawable objects, may as well
//include it.
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#include <math.h>
#endif

#include <GL/freeglut.h>

//given that Color will probably be used by classes that draw, including it here
//saves some further includes down the road.
#include "color3.h"
#include "ColorScheme.h"

class IDrawable
{
public:
    /*enable()
     * takes: nothing
     * returns: nothing
     *
     * Flags the implementation as visible (drawn).
     *
     */
    virtual void enable()=0;
    
    /*disable()
     * takes: nothing
     * returns: nothing
     *
     * Flags the implementation as invisible (not drawn).
     *
     */
    virtual void disable()=0;
    
    /*isEnabled()
     * takes: nothing
     * returns: true if enabled; false otherwise.
     *
     */
    virtual bool isEnabled()=0;
    
    /*getPriority()
     * takes: nothing
     * returns: the priority for drawing the IDrawable
     *
     * This is useful for when using a priority queue of IDrawables to get the
     * priority for drawing an implementation.
     *
     */
    int getPriority();
    
    /*setPriority(priority)
     * takes: an int to indicate the draw priority
     * returns: nothing
     *
     * Allows a reset of the draw priority for an IDrawable.  Primarilty for
     * use with a priority queue.
     *
     */
    void setPriority(int);
    
    /*draw()
     * takes: nothing
     * returns: nothing
     * 
     * Draws the object to the screen.
     *
     */
    virtual void draw()=0;
};

class IDrawableCompare
{
public:
    /*operator()(&d1, &d2)
     * takes: references to two IDrawable objects
     * returns: true if d1 has a lower priority than d2; false otherwise.
     *
     * Not sure why this operator, but this should produce an ordering from
     * largest priority to lowest.
     *
     */
    bool operator()(IDrawable& d1, IDrawable& d2)
    {
       return (d1.getPrioirty() < d2.getPriority());
    }
};
#endif