/*keyboard.h
 * Peter Bartosch and Ross Greenman
 * created: 4/13/2013
 * last modified: 4/13/2013
 * IS346 - Instructor Memory
 * Kahn
 *
 * defines class: Keyboard
 * A Keyboard is a class that stores a list of a map of keybindings for use
 * in a game.  Because it should register with glut for the applicable keyboard
 * funcs, all members are static.  Rather than create multiple instances of
 * Keyboard, different binding maps will be stored in a list.  The map used
 * maps an unsigned character to a function pointer.  All of the functions
 * pointed to will return void and take mouse x and y for parameters on the
 * chance that those will be important.  Since those are the only parameters,
 * it is necessary to create a single function for each key that is bound.
 * This will probably necessitate a static class (KeyBindings) that will store
 * all of the functions that are called.
 *
 * This is a bit of challenge, and as such the syntax used is almost identical
 * to the syntax found in the top answer at:
 * http://stackoverflow.com/questions/2136998/using-a-stl-map-of-function-pointers
 * There are a few differences, one of which is the use of an unordered_map
 * as there is no need to directy iterate over a given map, and the speed
 * increase is desirable.  If we wanted a larger increase in speed, we would
 * probably write our own unordered map.
 *
 */
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <unordered_map>

using std::unordered_map
using std::pair

typedef void (*BoundFunction)(int,int);
typedef unordered_map<unsigned char, BoundFunction> bindingMap;
typedef pair<unsigned char, BoundFunction) keyBinding;

class Keyboard
{
public:
    /*addBindings(newBindingMap)
     * takes: a bindingMap to add to the list of bindingMaps
     * returns: nothing
     *
     * This will add a bindingMap at the first open index of the array of
     * bindingMaps.  If there is no open index, then nothing is done.  If this
     * is the first bindingMap, then initd is set to true.
     *
     */
    static void addBindings(bindingMap);
    
    /*addBindingToCurrent(newKeyBinding, replace)
     * takes: a keyBinding and true/false for replacing a keyBinding
     * returns: nothing
     *
     * This adds the passed keyBinding to the current bindingMap.  If a
     * keyBinding for the unsigned char (keyBinding.first) already exists, then
     * it will be replaced if replace=true.  Otherwise the newKeyBinding will
     * not be added.
     *
     */
    static void addBindingToCurrent(keyBinding, bool);
    
    /*switchBindings(bindingToUse)
     * takes: the index of the bindingMap to use
     * returns: true if the switch ocurred; false otherwise.
     *
     * This will attempt to change _curBindingMap to the passed index.  If the
     * passed index is invalid (>= _nBindings) then false is returned and
     * nothing changes.  Otherwise true is returned.
     *
     */
    static void switchBindings(unsigned int);
    
    /*procNormalKey(key, mouseX, mouseY)
     * takes: the key pressed and curreny mouse coordinates
     * returns: nothing
     *
     * This is the function to register with glutKeyboardFunc.  It will attempt
     * to locate the passed key in the current bindingMap.  If the key is found
     * then the mouse coordinates are passed on to the associated function.  If
     * the key is not found then nothing is done.
     *
     * This will also check _initd to make sure that the Keyboard has been
     * initialized with at least one bindingMap.
     *
     */
    static void procNormalKey(unsigned char, int, int);
private:
    static bool _initd;
    
    //10 might even be high for different keyBindings
    static bindingMap _bindingMaps[10];
    static int _nBindingMap;
    static int _curBindingMap;
};
#endif