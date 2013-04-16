#ifndef _IDRAWABLECOMPARE_H_
#define _IDRAWABLECOMPARE_H_

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
    bool operator()(IDrawable*& d1, IDrawable*& d2)
    {
       return (d1->getPriority() > d2->getPriority());
    }
};
#endif