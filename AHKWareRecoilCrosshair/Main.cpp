/*
	RecoilCrosshair for CSGO v1.0.1
	by C0

	TODO:
	Add more crosshair customization
	Add a config for each weapon
*/

#include <Windows.h>
#include <iostream>
#include <string>
#include "SimpleIni.h"

using namespace std;

int main()
{	
	//Setup varibles
	COORD crosshair;
	COORD crosshairorigin;
	POINT mp;
	HDC _hdc = GetDC(NULL);
	HWND activewindow;
	INT steps;
	INT steps2 = 0;
	INT steps3 = 0;

	//Setup setting ini file for reading
	CSimpleIni settings;
	settings.SetUnicode();
	settings.LoadFile("settings.ini");
	
	//Retrive all settings from ini file
	int recenterkey = settings.GetLongValue("Keys"		, "recenterkey"	, VK_F1);
	int intensity	= settings.GetLongValue("General"	, "speed"		, 1);
	int delay		= settings.GetLongValue("General"	, "delay"		, 20);
	int stoptime	= settings.GetLongValue("General"	, "stoptime"	, 150);
	int Tspray		= settings.GetLongValue("Sprays"	, "Tspray"		, 1);
	int ttTdcL		= settings.GetLongValue("Sprays"	, "tspraytimeR"	, 30);
	int ttTdcR		= settings.GetLongValue("Sprays"	, "tspraytimeL"	, 30);
	int chcolor_r	= settings.GetLongValue("Crosshair"	, "chcolor_r"	, 255);
	int chcolor_g	= settings.GetLongValue("Crosshair"	, "chcolor_g"	, 0);
	int chcolor_b	= settings.GetLongValue("Crosshair"	, "chcolor_b"	, 0);
	int chsize		= settings.GetLongValue("Crosshair"	, "chsize"		, 3);

	//Initializing some varibles before running the loop
	GetCursorPos(&mp);
	crosshair.X	= mp.x;
	crosshair.Y	= mp.y;
	crosshairorigin = crosshair;

	//Loop
	for (;;)
	{
		//Draw recoil crosshair at position
		for (int x = 0; x < chsize; x++)
		{
			for (int y = 0; y < chsize; y++)
			{
				SetPixel(_hdc, -x + crosshair.X, -y + crosshair.Y, RGB(chcolor_r, chcolor_g, chcolor_b));
			} 
		}

		//Respond to input
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (steps != stoptime)
			{
				crosshair.Y -= intensity;
				Sleep(delay);
				steps++;
			}
			else
			{
				if (Tspray = 1)
				{
					if (steps2 != ttTdcR)
					{
						crosshair.X -= intensity;
						Sleep(delay);
						steps2++;
					}
					else
					{
						if (steps3 == 0)
						{
							crosshair.X += ttTdcR;
						}

						if (steps3 != ttTdcL)
						{
							crosshair.X += intensity;
							Sleep(delay);
							steps3++;
						}
					}
				}
			}
		}
		else
		{
			crosshair = crosshairorigin;
			steps = 0;
			steps2 = 0;
			steps3 = 0;
		}

		if (GetAsyncKeyState(recenterkey))
		{
			GetCursorPos(&mp);
			crosshair.X = mp.x;
			crosshair.Y = mp.y;
			crosshairorigin = crosshair;
		}
	}
}