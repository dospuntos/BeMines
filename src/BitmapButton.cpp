/*
	BitmapButton.cpp: A button which uses a BBitmap for its looks
	Written by DarkWyrm <darkwyrm@earthlink.net>, Copyright 2007
	Released under the MIT license.
*/
#include "BitmapButton.h"

BitmapButton::BitmapButton(const BRect &frame, const char *name, BBitmap *up,
						BBitmap *down, BMessage *msg, bool own,
						const int32 &resize,
						const int32 &flags)
 :	BButton(frame, name, "", msg, resize, flags),
 	fOwnBitmaps(own),
 	fUp(up),
 	fDown(down),
 	fDisabled(NULL),
 	fFocusUp(NULL),
 	fFocusDown(NULL)
{
	fUp = up;
	fDown = down;
}


BitmapButton::~BitmapButton(void)
{
	if (fOwnBitmaps)
	{
		delete fUp;
		delete fDown;
		delete fDisabled;
		delete fFocusUp;
		delete fFocusDown;
	}
}


void
BitmapButton::SetBitmaps(BBitmap *up, BBitmap *down)
{
	if (fOwnBitmaps)
	{
		delete fUp;
		delete fDown;
	}

	fUp = up;
	fDown = down;

	if (IsEnabled())
		Invalidate();
}


BBitmap *
BitmapButton::UpBitmap(void)
{
	return fUp;
}


BBitmap *
BitmapButton::DownBitmap(void)
{
	return fDown;
}


void
BitmapButton::SetDisabledBitmap(BBitmap *disabled)
{
	if (fOwnBitmaps)
		delete fDisabled;

	fDisabled = disabled;

	if (!IsEnabled())
		Invalidate();
}


BBitmap *
BitmapButton::DisabledBitmap(void) const
{
	return fDisabled;
}


void
BitmapButton::SetFocusBitmaps(BBitmap *up, BBitmap *down)
{
	if (fOwnBitmaps)
	{
		delete fFocusUp;
		delete fFocusDown;
	}

	fFocusUp = up;
	fFocusDown = down;
}


BBitmap *
BitmapButton::UpFocusBitmap(void)
{
	return fFocusUp;
}


BBitmap *
BitmapButton::DownFocusBitmap(void)
{
	return fFocusDown;
}


void
BitmapButton::Draw(BRect update)
{
	if (!IsEnabled()) {
		if (fDisabled)
			DrawBitmap(fDisabled, update);
		else
			StrokeRect(Bounds());
		return;
	}

	if (Value() == B_CONTROL_ON) {
		if (IsFocus()) {
			if (fFocusDown)
				DrawBitmap(fFocusDown, update);
			else {
				if (fDown)
					DrawBitmap(fUp, update);
				SetHighColor(ui_color(B_KEYBOARD_NAVIGATION_COLOR));
				StrokeRect(Bounds());
			}
		} else {
			if (fDown)
				DrawBitmap(fDown, update);
			else
				StrokeRect(Bounds());
		}
	} else {
		if (IsFocus()) {
			if (fFocusUp)
				DrawBitmap(fFocusUp, update);
			else {
				if (fUp)
					DrawBitmap(fUp, update);
				SetHighColor(ui_color(B_KEYBOARD_NAVIGATION_COLOR));
				StrokeRect(Bounds());
			}
		} else {

			if (fUp)
				DrawBitmap(fUp, update);
			else
				StrokeRect(Bounds());
		}
	}
}


void
BitmapButton::ResizeToPreferred(void)
{
	if (fUp)
		ResizeTo(fUp->Bounds().Width(),fUp->Bounds().Height());
	else if (fDown)
		ResizeTo(fDown->Bounds().Width(),fDown->Bounds().Height());
	else if (fDisabled)
		ResizeTo(fDisabled->Bounds().Width(),fDisabled->Bounds().Height());
}
