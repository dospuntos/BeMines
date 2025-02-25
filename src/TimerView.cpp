#include "TimerView.h"
#include <Messenger.h>
#include <stdio.h>
#include "GameStyle.h"
#include "Globals.h"

#define M_INC_TIMER 'inct'

TimerView::TimerView(void)
	:	BView(BRect(0,0,1,1),"timerview",B_FOLLOW_NONE, B_WILL_DRAW),
		fState(TIMER_STOP),
		fRunner(NULL),
		fTime(0),
		fBitmaps(gGameStyle->LEDSprites())
{
	if (!fBitmaps)
		debugger("BUG: empty timer theme");

	BBitmap *zero = fBitmaps[0];
	ResizeTo(zero->Bounds().Width() * 3 * gScale,zero->Bounds().Height() * gScale);
}


TimerView::~TimerView(void)
{
	delete fRunner;
}


void
TimerView::SetState(TimerState s)
{
	switch (s)
	{
		case TIMER_START:
		{
			delete fRunner;
			BMessage msg(M_INC_TIMER);
			fRunner = new BMessageRunner(BMessenger(this),&msg,1000000);
			break;
		}
		case TIMER_STOP:
		{
			delete fRunner;
			fRunner = NULL;
			break;
		}
		case TIMER_RESET:
		{
			delete fRunner;
			fRunner = NULL;
			fTime = 0;
			break;
		}
		default:
			break;
	}
	fState = s;
	Draw(Bounds());
}


TimerState
TimerView::GetState(void)
{
	return fState;
}


void
TimerView::MessageReceived(BMessage *msg)
{
	switch (msg->what)
	{
		case M_INC_TIMER:
		{
			if (fTime < 999)
			{
				fTime++;
				Draw(Bounds());
			}
			break;
		}
		default:
		{
			BView::MessageReceived(msg);
			break;
		}
	}
}


void
TimerView::Draw(BRect update)
{
	char timestr[5];
	sprintf(timestr,"%.3d",fTime);

	BPoint pt(0,0);
	BRect rect(pt.x,pt.y,pt.x + fBitmaps[0]->Bounds().Width() * gScale,
		fBitmaps[0]->Bounds().Height() * gScale);
	DrawBitmap(fBitmaps[timestr[0] - 48],rect);
	pt.x += fBitmaps[0]->Bounds().Width() * gScale;
	rect.OffsetTo(pt);
	DrawBitmap(fBitmaps[timestr[1] - 48],rect);
	pt.x += pt.x;
	rect.OffsetTo(pt);
	DrawBitmap(fBitmaps[timestr[2] - 48],rect);
}


void
TimerView::StyleChanged(void)
{
	fBitmaps = gGameStyle->LEDSprites();
	BBitmap *zero = fBitmaps[0];
	ResizeTo(zero->Bounds().Width() * 3 * gScale,zero->Bounds().Height() * gScale);
}


uint16
TimerView::GetTime(void)
{
	return fTime;
}


void
TimerView::SetTime(uint16 time)
{
	fTime = time;
}
