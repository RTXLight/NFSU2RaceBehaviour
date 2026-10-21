#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include "..\includes\IniReader.h"

bool BlownEngineEvent, TotaledEvent, LapKnockoutEvent, HurryTimerEvent;

void Init()
{
	// Read values from .ini
	CIniReader iniReader("NFSU2RaceBehaviourConfig.ini");

	// Menu
	BlownEngineEvent = iniReader.ReadInteger("Gameplay", "BlownEngineEvent", 1) != 0;
	TotaledEvent = iniReader.ReadInteger("Gameplay", "TotaledEvent", 1) != 0;
	LapKnockoutEvent = iniReader.ReadInteger("Gameplay", "LapKnockoutEvent", 1) != 0;
	HurryTimerEvent = iniReader.ReadInteger("Gameplay", "HurryTimerEvent", 1) != 0;
	
	// Blown engine event
	if (BlownEngineEvent)
	{
		injector::WriteMemory<BYTE>(0x6079DA, 0xD2, true); // Drag parameters
		injector::WriteMemory<BYTE>(0x5A4B7B, 0xD2, true); // Blown engine event
	}

	// Totaled event
	if (TotaledEvent)
	{
		injector::WriteMemory<BYTE>(0x6079DA, 0xD2, true); // Drag parameters
		injector::WriteMemory<BYTE>(0x59FC0D, 0xD2, true); // Totaled event
	}

	// Lap Knockout Event
	if (LapKnockoutEvent)
	{
		injector::WriteMemory<BYTE>(0x60792C, 0x01, true); // KO
		injector::WriteMemory<BYTE>(0x6084CA, 0x01, true); // KO
	}

	// "Hurry!" Event
	if (HurryTimerEvent)
	{
		injector::WriteMemory<BYTE>(0x606FA5, 0xD2, true); // KO
	}

	injector::WriteMemory<BYTE>(0x53F98B, 0x01, true); // Disable change upon entering a specific race 1
	injector::WriteMemory<BYTE>(0x53F638, 0x01, true); // Disable change upon entering a specific race 2
	injector::WriteMemory<BYTE>(0x540546, 0x89, true); // Make symbol to be 0 (1)
	injector::WriteMemory<BYTE>(0x540547, 0x1D, true); // Make symbol to be 0 (2)
	injector::WriteMemory<BYTE>(0x532567, 0xD2, true); // If symbol is 1
	injector::WriteMemory<BYTE>(0x532568, 0xE7, true);
	injector::WriteMemory<BYTE>(0x532569, 0x89, true); // change symbol 4
	injector::WriteMemory<BYTE>(0x53256B, 0x00, true);
	injector::WriteMemory<BYTE>(0x532559, 0xC7, true); // change symbol 3
	injector::WriteMemory<BYTE>(0x53255A, 0x05, true);
	injector::WriteMemory<BYTE>(0x53255B, 0xD2, true); // change symbol 2
	injector::WriteMemory<BYTE>(0x53255C, 0xE7, true);
	injector::WriteMemory<BYTE>(0x53255D, 0x89, true); // change symbol 1
	injector::WriteMemory<BYTE>(0x53255F, 0x01, true);

	injector::WriteMemory<BYTE>(0x532570, 0xD2, true); // set
	injector::WriteMemory<BYTE>(0x532571, 0xE7, true); // set
	injector::WriteMemory<BYTE>(0x532572, 0x89, true); // set
	injector::WriteMemory<BYTE>(0x532574, 0x01, true); // set

	injector::WriteMemory<BYTE>(0x540811, 0xD2, true);

	injector::WriteMemory<BYTE>(0x53F638, 0x00, true); // Disable symbol to be 1 on quickrace FREERUN (4000)
	injector::WriteMemory<BYTE>(0x53F638, 0x00, true); // Disable symbol to be 1 on dyno shop state (4706)

	injector::WriteMemory<BYTE>(0x4FF1AD, 0x89, true); // Make symbol to be 0 (1)
	injector::WriteMemory<BYTE>(0x4FF1AE, 0x1D, true); // Make symbol to be 0 (2)
	// RTX wrote this...
}