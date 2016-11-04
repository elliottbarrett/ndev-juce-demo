#ifndef MIDISCROLLER_H_INCLUDED
#define MIDISCROLLER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class MidiScroller
{
public:
	MidiScroller()
	{
		midiFileName = "./FurElise.mid";
		File* f = new File(midiFileName);
		midiFileInputStream = f->createInputStream();
		midiFile.readFrom(*midiFileInputStream);
		int numTracks = midiFile.getNumTracks();

		// If the value returned is positive, it indicates the number of midi ticks per quarter-note.
		// It it's negative, the upper byte indicates the frames-per-second (but negative), 
		// and the lower byte is the number of ticks per frame - see setSmpteTimeFormat().
		short timeFormat = midiFile.getTimeFormat();

		// Time sig events will be used for horizontal dividers
		// Tempo events will be used to dictate scrolling speed
		// Key sig events will be used for ???
		MidiMessageSequence timeSigSequence;
		MidiMessageSequence tempoSequence;
		MidiMessageSequence keySigSequence;
		midiFile.findAllTimeSigEvents(timeSigSequence);
        midiFile.findAllTempoEvents(tempoSequence);
		midiFile.findAllKeySigEvents(keySigSequence);

		for (int i=0; i < numTracks; i++)
		{
			MidiMessage *tempMessage;
			const MidiMessageSequence *seq = midiFile.getTrack(i);
			int eventCount = seq->getNumEvents();
			for (int ei=0; ei < eventCount; ei++)
			{
				tempMessage = &(seq->getEventPointer(ei)->message);
				if (tempMessage->isNoteOn())
				{
					int noteNumber = tempMessage->getNoteNumber();
					String noteName = MidiMessage::getMidiNoteName(noteNumber, true, true, 3);
				}
				else if (tempMessage->isNoteOff())
				{
					int noteNumber = tempMessage->getNoteNumber();
					String noteName = MidiMessage::getMidiNoteName(noteNumber, true, true, 3);
				}
				else if (tempMessage->isTempoMetaEvent())
				{
                    double tickLength = tempMessage->getTempoMetaEventTickLength(timeFormat);
                    double secondsPerQuarterNote = tempMessage->getTempoSecondsPerQuarterNote();
                    int asdf = 9;
				}
			}
		}
	}

	~MidiScroller()
	{
        delete midiFileInputStream;
	}
private:
	// Members
	String midiFileName;
	FileInputStream *midiFileInputStream;
	MidiFile midiFile;

	// Methods
};
#endif
