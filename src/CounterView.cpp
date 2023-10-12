#include "CounterView.h"
#include "GameStyle.h"
#include <stdio.h>
#include "Globals.h"

CounterView::CounterView(void)
	:	BView(BRect(0,0,1,1),"counterview",B_FOLLOW_NONE, B_WILL_DRAW),
		fCount(0),
		fBitmaps(gGameStyle->LEDSprites())
{
	if (!fBitmaps)
		debugger("BUG: empty counter theme");

	BBitmap *zero = fBitmaps[0];
	int multiplier = gScale2x ? 2 : 1;
	ResizeTo(zero->Bounds().Width() * 3 * multiplier,zero->Bounds().Height() * multiplier);
}


void
CounterView::SetCount(uint16 count)
{
	if (count > 999)
		count = 999;

	fCount = count;
	Draw(Bounds());
}


uint16
CounterView::GetCount(void)
{
	return fCount;
}


void
CounterView::Draw(BRect update)
{
	int multiplier = gScale2x ? 2 : 1;
	char countstr[5];
	sprintf(countstr,"%.3d",fCount);

	BPoint pt(0,0);
	BRect rect(pt.x,pt.y,pt.x + fBitmaps[0]->Bounds().Width() * multiplier,
				fBitmaps[0]->Bounds().Height() * multiplier);
	DrawBitmap(fBitmaps[countstr[0] - 48], rect);
	pt.x += fBitmaps[0]->Bounds().Width() * multiplier;
	rect.OffsetTo(pt);
	DrawBitmap(fBitmaps[countstr[1] - 48],rect);
	pt.x += pt.x;
	rect.OffsetTo(pt);
	DrawBitmap(fBitmaps[countstr[2] - 48],rect);
}


void
CounterView::StyleChanged(void)
{
	fBitmaps = gGameStyle->LEDSprites();
	BBitmap *zero = fBitmaps[0];
	int multiplier = gScale2x ? 2 : 1;
	ResizeTo(zero->Bounds().Width() * 3 * multiplier,zero->Bounds().Height() * multiplier);
	Invalidate();
}
