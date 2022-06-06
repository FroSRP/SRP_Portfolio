#pragma once
#include "framework.h"
#include <string>
using std::wstring;

class UI
{
public:
	enum class BUTTON
	{
		Start = 0,
		Log,
		Score,
		Option,
		Quit,
		E_MAX
	};

private:
	Gdiplus::Rect*	clientRect;
	Gdiplus::RectF	buttonRect[(unsigned int)UI::BUTTON::E_MAX];
	int				buttonMouseOn;
	wstring			wstrMenu[(unsigned int)UI::BUTTON::E_MAX];

public:
	void			Init(Gdiplus::Rect* _clientRect);
	void			Release();
	Gdiplus::RectF*	getButtonRect();
	void			DrawLobbyUI(Graphics& graphics);
	void			DrawTitle(Graphics& graphics);
	void			DrawTextButton(Graphics& graphics);
	void			DrawPlayUI(Graphics &graphics);
	void			DrawOverUI(Graphics &graphics);
	void			whereMenuMouseOn(POINT* ptMousePos);
	BUTTON			LButtonDown();
};