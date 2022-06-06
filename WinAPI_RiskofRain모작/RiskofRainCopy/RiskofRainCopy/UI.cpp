#include "UI.h"

void UI::Init(Gdiplus::Rect * _clientRect)
{
	clientRect = _clientRect;

	Gdiplus::REAL left		= (clientRect->Width / 5.0f) * 2.0f;
	Gdiplus::REAL width		= clientRect->Width / 5.0f;
	Gdiplus::REAL top		= clientRect->Height / 4.0f;
	Gdiplus::REAL height	= clientRect->Height / 15.0f;
	for (int i = 0; i < (unsigned int)UI::BUTTON::E_MAX; i++)
	{
		buttonRect[i] = Gdiplus::RectF(left, top + height * i + 10, width, height);
	}
	buttonMouseOn = -1;

	wstrMenu[(unsigned int)UI::BUTTON::Start]	= L"Start";
	wstrMenu[(unsigned int)UI::BUTTON::Log]		= L"Log";
	wstrMenu[(unsigned int)UI::BUTTON::Score]	= L"Score";
	wstrMenu[(unsigned int)UI::BUTTON::Option]	= L"Option";
	wstrMenu[(unsigned int)UI::BUTTON::Quit]	= L"Quit";
}

void UI::Release()
{
}

Gdiplus::RectF * UI::getButtonRect()
{
	return buttonRect;
}

void UI::DrawLobbyUI(Graphics & graphics)
{
	DrawTitle(graphics);
	DrawTextButton(graphics);
}

void UI::DrawTitle(Graphics & graphics)
{
	SolidBrush brush(Color(255, 240, 240, 240));
	FontFamily fontFamily(L"Times New Roman");
	Font font(&fontFamily, clientRect->Width / 20.0f, FontStyleRegular, UnitPixel);
	Gdiplus::PointF pointF(clientRect->Width / 3.1f, clientRect->Height / 20.0f);
	graphics.DrawString(L"RISK OF RAIN", -1, &font, pointF, &brush);
}

void UI::DrawTextButton(Graphics & graphics)
{
	SolidBrush brush(Color(255, 135, 135, 135));
	SolidBrush brushMouseOn(Color(255, 240, 240, 240));
	FontFamily fontFamily(L"Times New Roman");
	Font font(&fontFamily, clientRect->Width / 60.0f, FontStyleRegular, UnitPixel);
	StringFormat stringFormat;
	stringFormat.SetAlignment(StringAlignmentCenter);
	stringFormat.SetLineAlignment(StringAlignmentCenter);
	for (int menu = 0; menu < (unsigned int)UI::BUTTON::E_MAX; menu++)
	{
		if (buttonMouseOn == menu)
		{
			graphics.DrawString(wstrMenu[menu].c_str(), -1, &font, buttonRect[menu], &stringFormat, &brushMouseOn);
		}
		else
		{
			graphics.DrawString(wstrMenu[menu].c_str(), -1, &font, buttonRect[menu], &stringFormat, &brush);
		}
	}
}

void UI::DrawPlayUI(Graphics & graphics)
{
}

void UI::DrawOverUI(Graphics & graphics)
{
}

void UI::whereMenuMouseOn(POINT * ptMousePos)
{
	for (int i = 0; i < (unsigned int)UI::BUTTON::E_MAX; i++)
	{
		if (ptMousePos->x >= buttonRect[i].GetLeft() && ptMousePos->x <= buttonRect[i].GetRight() &&
			ptMousePos->y >= buttonRect[i].GetTop() && ptMousePos->y <= buttonRect[i].GetBottom())
		{
			buttonMouseOn = i;
			return;
		}
	}
	
	buttonMouseOn = -1;
	return;
}

UI::BUTTON UI::LButtonDown()
{
	if (buttonMouseOn != -1)
	{
		return (UI::BUTTON)buttonMouseOn;
	}
	return UI::BUTTON::E_MAX;
}
