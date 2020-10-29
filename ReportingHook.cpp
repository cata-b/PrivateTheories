//from http://winfig.com/detecting-memory-leaks-in-qt-applications-with-visual-studio/
#include "ReportingHook.h"
#if defined(WIN32)

#include <string.h>
#include "crtdbg.h"

#define FALSE   0
#define TRUE    1

_CRT_REPORT_HOOK previousHook;

int reportingHook(int reportType, char* userMessage, int* returnValue)
{
	// This function is called several times for each memory leak.
	// Each time a part of the error message is supplied.
	// This holds number of subsequent detail messages after
	// a leak was reported
	const int numFollowupDebugMsgParts = 2;
	static bool ignoreMessage = false;
	static int debugMsgPartsCount = 0;

	// check if the memory leak reporting starts
	if ((strncmp(userMessage, "Detected memory leaks!\n", 10) == 0)
		|| ignoreMessage)
	{
		// check if the memory leak reporting ends
		if (strncmp(userMessage, "Object dump complete.\n", 10) == 0)
		{
			_CrtSetReportHook(previousHook);
			ignoreMessage = false;
		}
		else
			ignoreMessage = true;

		// something from our own code?
		if (strstr(userMessage, ".cpp") == nullptr)
		{
			if (debugMsgPartsCount++ < numFollowupDebugMsgParts)
				// give it back to _CrtDbgReport() to be printed to the console
				return FALSE;
			return TRUE;
			// ignore it
		}
		debugMsgPartsCount = 0;
		// give it back to _CrtDbgReport() to be printed to the console
		return FALSE;
	}
	// give it back to _CrtDbgReport() to be printed to the console
	return FALSE;
};

void setFilterDebugHook(void)
{
	//change the report function to only report memory leaks from program code
	previousHook = _CrtSetReportHook(reportingHook);
}

#endif
