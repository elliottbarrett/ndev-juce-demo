#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "FirstSynthAudioManager.cpp"

/*
	This component lives inside our window, and this is where you should put all
	your controls and content.
*/
class MainContentComponent   :	public AnimatedAppComponent
{
public:
	// Constructor
	MainContentComponent()
	{
		setSize (800, 600);
		setFramesPerSecond (60);
        
    }

	// Destructor
	~MainContentComponent()
	{

	}

	// Methods
	void update() override
	{
        
	}

	void paint (Graphics& g) override
	{
		g.fillAll (Colours::grey);
	}

	void resized() override
	{

	}

private:
	// Members
    FirstSynthAudioManager firstSynthAudioManager;

	// Methods
    
    // Boilerplate
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()	{ return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
