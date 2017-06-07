// 
// This is the home of the audio thread, 
// you can interface with the audio thread
// using the procedures in this file,
// but be warey that it is on another
// thread and if you don't treat it
// nice things will go south, fast.
#pragma once

#include "basic.h"
#include <thread>

namespace hate {
	// Runs the thread, this is the main loop
	// of the thread and is handled by the engine.
	extern void _run();


	/* Thoughts so far:
	 *
	 * In the audio thread, set every
	 * audiocomponent everyframe. This makes
	 * it less messy to send in new information
	 * and stuff. 
	 *
	 * Translate audio from "local audio space", to
	 * "global audio space" with a variable.
	 *
	 * The sounds are sorted into groups,
	 * for music and for sound effects
	 * so the engine can tell them appart.
	 *
	 * We store all audio events in a que
	 * that is then processed in the same 
	 * order in the other thread.
	 *
	 * You can also get a refference to 
	 * a source from the thread, not sure
	 * how to do this yet, which can be
	 * used to make things fade, change volume,
	 * pause or what ever.
	 *
	 * I also need to write the wav loader,
	 * and make sure it works.
	 */
	

}
