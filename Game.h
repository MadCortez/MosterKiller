//---------------------------------------------------------------------------

#ifndef GameH
#define GameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Graphics.hpp>
#include <MainMenu.h>
#include <Vcl.Imaging.jpeg.hpp>
#include <string>
#include <gdiplus.h>
#include <cstring>
#include <algorithm>

#define MAXMOB 3
#define LU 1
#define RU 2
#define LD 3
#define RD 4
//---------------------------------------------------------------------------
class TGameForm : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TImage *PlayerIMG;
	TTimer *Timer2;
	TTimer *Timer3;
	TTimer *Timer4;
	TImage *MobIMG;
	TImage *HealthIMG;
	TLabel *HealthLB;
	TTimer *Timer5;
	TTimer *Timer6;
	TLabel *ScoreLB;
	TLabel *ScoreNumLB;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall MoveBullet(TObject *Sender);
	void __fastcall CreateBulletT(TObject *Sender);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall fire();
	void __fastcall MoveMob(TObject *Sender);
	void __fastcall MobIMGMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall MobIMGMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall createBullet();
	void __fastcall paintBullet();
    void __fastcall setOptionsBullet();
	void __fastcall HealthIMGMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall HealthLBMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall paintMob();
	void __fastcall setOptionsMob();
	void __fastcall paintPlayer();
	void __fastcall movePlayer();
	void __fastcall Timer5Timer(TObject *Sender);
	void __fastcall HealthIMGMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall HealthLBMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall spawnMob();
	void __fastcall Timer6Timer(TObject *Sender);
	void __fastcall gameOver();







private:	// User declarations
public:		// User declarations
	__fastcall TGameForm(TComponent* Owner);
};

const int speed = 10;
const float diagSpeed = 7;

int mouseX = 0, mouseY = 0;
int curBul = -1;
int curMob = -1;
int fireX = 0, fireY = 0;
bool fireFlag = false;
TBitmap* PlayerB = new TBitmap;
TJPEGImage* test = new TJPEGImage;
int toX, toY;
double curX = 0, curY = 0, dx = 0, dy = 0;
int score;
int firstMob = 0;

struct Node {
	TImage *img;
	int toX, toY;
	double curX, curY, dx, dy;
	int hp;
	int armor;
	int damage;
	int giveHp;
	int giveScore;
    bool live;
};

Node *bullet[100];
Node *mobs[MAXMOB];
Node *player;

//---------------------------------------------------------------------------
extern PACKAGE TGameForm *GameForm;
//---------------------------------------------------------------------------
#endif
