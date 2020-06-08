// Using Nexo's memory class
// https://github.com/YanderewareDev/MemoryClass
//
//USE MULTI-BYTE CHARACTER SET! (already done for this sln)
//
//PLEASE ADD JUNK CODE BELOW TO AVOID V.A.C DETECTION!
//https://junkcode.gehaxelt.in/

#include <iostream>
#include <Windows.h>

#include "Memory.h"
#include "Offsets.h"

cMemory mem;

DWORD clientModule;
int csgo;
bool glowEnabled;



void glowEnemy()
{
	DWORD localPlayer = mem.ReadMemory<DWORD>(clientModule + hazedumper::signatures::dwLocalPlayer);
	int myTeam = mem.ReadMemory<int>(localPlayer + hazedumper::netvars::m_iTeamNum);
	DWORD glowOBJ = mem.ReadMemory<DWORD>(clientModule + hazedumper::signatures::dwGlowObjectManager);

	for (short int i = 0; i < 64; i++)
	{
		DWORD entity = mem.ReadMemory<DWORD>(clientModule + hazedumper::signatures::dwEntityList + i * 0x10);
		if (entity != NULL)
		{
			int glowIndex = mem.ReadMemory<int>(entity + hazedumper::netvars::m_iGlowIndex);
			int entityTeam = mem.ReadMemory<int>(entity + hazedumper::netvars::m_iTeamNum);

			if (myTeam != entityTeam)
			{
				mem.WriteMemory<float>(glowOBJ + ((glowIndex * 0x38) + 0x4), 2);
				mem.WriteMemory<float>(glowOBJ + ((glowIndex * 0x38) + 0x8), 0);
				mem.WriteMemory<float>(glowOBJ + ((glowIndex * 0x38) + 0xC), 0);
				mem.WriteMemory<float>(glowOBJ + ((glowIndex * 0x38) + 0x10), 1);

				mem.WriteMemory<bool>(glowOBJ + ((glowIndex * 0x38) + 0x24), true);
				mem.WriteMemory<bool>(glowOBJ + ((glowIndex * 0x38) + 0x25), false);
			}
		}
	}
}

int main()
{
	csgo = mem.FindProcess("csgo.exe");
	std::cout << "[*] press INSERT to toggle the glowhack!" << std::endl;
	if (csgo != NULL)
	{
		clientModule = mem.FindModule("client.dll");



		while (true)
		{
			if (GetAsyncKeyState(VK_INSERT) & 1)
			{
				glowEnabled = !glowEnabled;
				std::cout << "glow is now " << glowEnabled << std::endl;
			}

			if (glowEnabled)
			{
				glowEnemy();
			}

			Sleep(1);
		}
	}
	else
	{
		std::cout << "csgo not found!" << std::endl;
		Sleep(1000);
	}
}