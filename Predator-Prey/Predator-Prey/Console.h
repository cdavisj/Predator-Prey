#pragma once

enum Color
{
	yellow = 6, green = 10, red = 12, purple = 13, white = 15
};

namespace console
{
	void gotoxy(const short&, const short&);

	void showCursor(const bool&);

	void clearScreen();

	void setTextColor(Color);
}