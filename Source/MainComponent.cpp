#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "FirstSynthAudioManager.h"
#include "DemoUIComponent.h"

/*
	This component lives inside our window, and this is where you should put all
	your controls and content.
*/
class MainContentComponent : public Component
{
public:
	// Constructor
    MainContentComponent() :
        demoUI(&audioManager)
	{
        setOpaque(true);
		setSize (800, 600);
        addAndMakeVisible(demoUI);
	}

	// Destructor
	~MainContentComponent()
	{

	}

	// Methods
	void resized() override
	{
        Rectangle<int> area (getLocalBounds());
        demoUI.setBounds(area);
	}
    
    void paint(Graphics& g) override
    {
        g.fillAll(Colours::grey);
    }

private:
	// Members
	FirstSynthAudioManager audioManager;
    DemoUIComponent demoUI;

	// Methods
	
	// Boilerplate
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()	{ return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
