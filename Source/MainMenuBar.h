/*
  ==============================================================================

    MainMenuBar.h
    Created: 18 Sep 2013 1:26:32pm
    Author:  Daniel

  ==============================================================================
*/

#ifndef MAINMENUBAR_H_INCLUDED
#define MAINMENUBAR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MainMenuBar    
    : public Component,
      public MenuBarModel,
      public ApplicationCommandTarget
{
public:
    MainMenuBar();
    ~MainMenuBar();

    void paint (Graphics&);
    void resized();

	//==============================================================================
    /** This method must return a list of the names of the menus. */
    virtual StringArray getMenuBarNames();

    /** This should return the popup menu to display for a given top-level menu.

        @param topLevelMenuIndex    the index of the top-level menu to show
        @param menuName             the name of the top-level menu item to show
    */
    virtual PopupMenu getMenuForIndex (int topLevelMenuIndex,
                                       const String& menuName);

    /** This is called when a menu item has been clicked on.

        @param menuItemID           the item ID of the PopupMenu item that was selected
        @param topLevelMenuIndex    the index of the top-level menu from which the item was
                                    chosen (just in case you've used duplicate ID numbers
                                    on more than one of the popup menus)
    */
    virtual void menuItemSelected (int menuItemID,
                                   int topLevelMenuIndex);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainMenuBar)
};


#endif  // MAINMENUBAR_H_INCLUDED
