#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <MessageFilter.h>
#include <Messenger.h>
#include <Handler.h>
#include <Window.h>
#include "GameStyle.h"

class BitmapButton;
class CounterView;
class TimerView;
class FieldView;

enum
{
	FACE_NORMAL = 0,
	FACE_WORRY,
	FACE_WIN,
	FACE_LOSE
};

enum
{
	M_PAUSE_GAME = 'psgm',
	M_SET_DIFFICULTY = 'stdf'
};

class MainWindow : public BWindow
{
public:
			MainWindow(BRect r);
	bool	QuitRequested(void);
	void	MessageReceived(BMessage *msg);
	void	WindowActivated(bool active);
	void	SetupGame(void);
	void	SetFace(int32 value);
	void	HighScoreCheck(void);
	void	AchievementCheck(void);
	void	SetTheme(const char *name);
	void	AboutRequested(void);

private:
	const char* TranslateWellKnownThemes(const char *name);
	void	ResetLayout(void);
	void	LoadSettings(void);
	void	SaveSettings(void);
	bool 	CanScale(void);

	BitmapButton	*fSmileyButton;
	int8			fSmileyState;
	TimerView		*fTimerView;
	FieldView		*fFieldView;
	CounterView		*fCounterView;
	BMenuBar		*fMenuBar;
};



class SpaceBarFilter : public BMessageFilter
{
public:
	SpaceBarFilter(uint32 command)
	:
	BMessageFilter(B_PROGRAMMED_DELIVERY,
		B_ANY_SOURCE,B_KEY_DOWN),
	fCommand(command)
	{
	}
	~SpaceBarFilter(void)
	{
	}

	filter_result
	Filter(BMessage *msg, BHandler **target)
	{
		int32 rawchar;
		msg->FindInt32("raw_char",&rawchar);

		if (rawchar == B_SPACE) {
			BLooper *loop = (*target)->Looper();
			if (loop) {
				BMessenger msgr(loop);
				msgr.SendMessage(fCommand);
				return B_SKIP_MESSAGE;
			}
		}
		return B_DISPATCH_MESSAGE;
	}
private:
	uint32 fCommand;
};

#endif
