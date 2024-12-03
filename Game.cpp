//---------------------------------------------------------------------------

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define step 10
#define step1 1

#include <vcl.h>
#pragma hdrstop

#include "Game.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma comment(lib, "gdiplus.lib")
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;
TGameForm *GameForm;
TBitmap *playerBmp;
TTimer *Timer3;

//---------------------------------------------------------------------------
__fastcall TGameForm::TGameForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TGameForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	MainForm->Close();
}
//---------------------------------------------------------------------------



void __fastcall TGameForm::paintMob() {

	for (int i = 0; i <= MAXMOB; i++)
	if (mobs[i]->live) {
		float angle = atan2(PlayerIMG->Top - PlayerIMG->Height / 2 - mobs[i]->img->Top, PlayerIMG->Left + PlayerIMG->Width / 2 - mobs[i]->img->Left - mobs[i]->img->Width / 2) * 180.f / 3.14f;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		Gdiplus::Graphics graphics1(mobs[i]->img->Canvas->Handle);
		Gdiplus::Image image1(L"D:\\Папка Ильи\\MonsterKiller\\Resourses\\mob1.bmp");
		graphics1.TranslateTransform(mobs[i]->img->Width / 2, mobs[i]->img->Height / 2);

		graphics1.RotateTransform(angle + 90);

		mobs[i]->img->Picture->Bitmap->Canvas->FillRect( Rect( 0, 0,
			mobs[i]->img->Picture->Bitmap->Width,
			mobs[i]->img->Picture->Bitmap->Height) );
		graphics1.DrawImage(&image1, -130, -160);
	}
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::setOptionsMob() {
	for (int i = 0; i <= MAXMOB; i++)
	if (mobs[i]->live){
		mobs[i]->curX = mobs[i]->img->Left;
		mobs[i]->curY = mobs[i]->img->Top;
		mobs[i]->toX = PlayerIMG->Left;
		mobs[i]->toY = PlayerIMG->Top;
		double d = sqrt(pow(mobs[i]->curX - mobs[i]->toX, 2) + pow(mobs[i]->curY - mobs[i]->toY, 2))/double(step1);
		mobs[i]->dx = (mobs[i]->toX - mobs[i]->curX) / double(d);
		mobs[i]->dy = (mobs[i]->toY - mobs[i]->curY) / double(d);
	}
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::paintPlayer() {
  float angle = atan2(mouseY - PlayerIMG->Top - PlayerIMG->Height / 2, mouseX - PlayerIMG->Left - PlayerIMG->Width / 2) * 180.f / 3.14f;

  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
  Gdiplus::Graphics graphics(PlayerIMG->Canvas->Handle);
  Gdiplus::Image image(L"D:\\Папка Ильи\\MonsterKiller\\Resourses\\player2.bmp");
  graphics.TranslateTransform(PlayerIMG->Width / 2, PlayerIMG->Height / 2);

  graphics.RotateTransform(angle + 83);

  PlayerIMG->Picture->Bitmap->Canvas->FillRect( Rect( 0, 0,
	  PlayerIMG->Picture->Bitmap->Width,
	  PlayerIMG->Picture->Bitmap->Height) );
  graphics.DrawImage(&image, -40, -70);
  PlayerIMG->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::movePlayer() {
	if ((GetKeyState((int)'W') & 128) == 128 && (GetKeyState((int)'D') & 128) == 128) {
		if (PlayerIMG->Top - speed >= 1)
			PlayerIMG->Top -= diagSpeed;
		if (PlayerIMG->Left + PlayerIMG->Width <= speed + GameForm->Width)
			PlayerIMG->Left += diagSpeed;
		return;
	  }
	if ((GetKeyState((int)'W') & 128) == 128 && (GetKeyState((int)'A') & 128) == 128) {
		if (PlayerIMG->Top - speed >= 1)
			PlayerIMG->Top -= diagSpeed;
		if (PlayerIMG->Left + speed >= 1)
			PlayerIMG->Left -= diagSpeed;
		return;
	  }
	if ((GetKeyState((int)'S') & 128) == 128 && (GetKeyState((int)'A') & 128) == 128) {
		if (PlayerIMG->Top + PlayerIMG->Height <= speed + GameForm->Height)
			PlayerIMG->Top += diagSpeed;
		if (PlayerIMG->Left + speed >= 1)
			PlayerIMG->Left -= diagSpeed;
		return;
	  }
	if ((GetKeyState((int)'S') & 128) == 128 && (GetKeyState((int)'D') & 128) == 128) {
		if (PlayerIMG->Top + PlayerIMG->Height <= speed + GameForm->Height)
			PlayerIMG->Top += diagSpeed;
		if (PlayerIMG->Left + PlayerIMG->Width <= speed + GameForm->Width)
			PlayerIMG->Left += diagSpeed;
		return;
	  }
	if ((GetKeyState((int)'W') & 128) == 128) {
		if (PlayerIMG->Top - speed >= 1)
			PlayerIMG->Top -= speed;
	}
	if ((GetKeyState((int)'S') & 128) == 128) {
		if (PlayerIMG->Top + PlayerIMG->Height <= speed + GameForm->Height)
			PlayerIMG->Top += speed;
	}
	if ((GetKeyState((int)'A') & 128) == 128) {
		if (PlayerIMG->Left + speed >= 1)
			PlayerIMG->Left -= speed;
	}
	if ((GetKeyState((int)'D') & 128) == 128) {
		if (PlayerIMG->Left + PlayerIMG->Width <= speed + GameForm->Width)
			PlayerIMG->Left += speed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::gameOver() {
	Timer1->Enabled = false;
	Timer2->Enabled = false;
	Timer3->Enabled = false;
	Timer4->Enabled = false;
	Timer5->Enabled = false;
	Timer6->Enabled = false;
	delete(player);
	for (int i = 0; i < 100; i++)
		delete(bullet[i]);
	for (int i = 0; i < MAXMOB; i++) {
		mobs[i]->img->Left = -100;
		mobs[i]->img->Top = -100;
		mobs[i]->img->Enabled = false;
        mobs[i]->img->Visible = false;
		delete(mobs[i]);
	}
	String lostS = "You lost\nYour Score is " + IntToStr(score) + "\nTry again";
	MessageDlg(lostS, mtInformation, TMsgDlgButtons() << mbOK, 0);
	GameForm->Hide();
	MainForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TGameForm::Timer1Timer(TObject *Sender)
{
	if (player->hp <= 0) {
		gameOver();
	}
	for (int i = 0; i <= MAXMOB; i++)
	if (mobs[i]->live){
		if (mobs[i]->hp <= 0) {
			mobs[i]->img->Enabled = false;
			mobs[i]->img->Visible = false;
			mobs[i]->img->Left = -100;
			mobs[i]->img->Top = -100;
			mobs[i]->damage = 0;
			player->hp += mobs[i]->giveHp;
			mobs[i]->giveHp = 0;
			score += mobs[i]->giveScore;
			mobs[i]->giveScore = 0;
			mobs[i]->live = false;
		}
	}
	HealthLB->Caption = IntToStr(player->hp);
	ScoreNumLB->Caption = IntToStr(score);
	mouseX = Mouse->CursorPos.x;
	mouseY = Mouse->CursorPos.y;
	for (int i = 0; i <= MAXMOB; i++)
	if (mobs[i]->live){
		paintMob();
		setOptionsMob();
	}
	paintPlayer();
	movePlayer();

}
//---------------------------------------------------------------------------

void __fastcall TGameForm::createBullet() {
	curBul++;
	if (curBul == 100) {
		curBul = 1;
		bullet[0] = bullet[99];
	}
	bullet[curBul] = new Node;
	bullet[curBul]->img = new TImage(GameForm);
	bullet[curBul]->img->SendToBack();
	bullet[curBul]->img->Parent = GameForm;
	bullet[curBul]->img->Left = PlayerIMG->Left + PlayerIMG->Width;
	bullet[curBul]->img->Width = 100;
	bullet[curBul]->img->Top = PlayerIMG->Top;
	bullet[curBul]->img->Height = 50;
	bullet[curBul]->damage = 5;
	bullet[curBul]->img->Visible = true;
	bullet[curBul]->img->Transparent = true;
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::paintBullet() {
    float angle = atan2(mouseY - bullet[curBul]->img->Top - bullet[curBul]->img->Height / 2, mouseX - bullet[curBul]->img->Left - bullet[curBul]->img->Width / 2) * 180.f / 3.14f;

	fireX = PlayerIMG->Left + PlayerIMG->Width / 2;
	fireY = PlayerIMG->Top + PlayerIMG->Height / 2;

  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
  Gdiplus::Graphics graphics(bullet[curBul]->img->Canvas->Handle);
  Gdiplus::Image image(L"D:\\Папка Ильи\\MonsterKiller\\Resourses\\bullet2.bmp");

  graphics.TranslateTransform(bullet[curBul]->img->Width / 2, bullet[curBul]->img->Height / 2);

  graphics.RotateTransform(angle + 90);

  bullet[curBul]->img->Picture->Bitmap->Canvas->FillRect( Rect( 0, 0,
	  bullet[curBul]->img->Picture->Bitmap->Width,
	  bullet[curBul]->img->Picture->Bitmap->Height ) );

  graphics.DrawImage(&image, 0, 0);
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::setOptionsBullet() {
    bullet[curBul]->curX = fireX;
	bullet[curBul]->curY = fireY;
	double d = sqrt(pow(bullet[curBul]->curX - mouseX, 2) + pow(bullet[curBul]->curY - mouseY, 2))/double(step);
	bullet[curBul]->dx = (mouseX - bullet[curBul]->curX) / double(d);
	bullet[curBul]->dy = (mouseY - bullet[curBul]->curY) / double(d);
	bullet[curBul]->toX = mouseX;
	bullet[curBul]->toY = mouseY;
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::fire() {
	createBullet();
	paintBullet();
	setOptionsBullet();
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Timer3->Enabled = true;
	fire();
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::MoveBullet(TObject *Sender)
{
	for (int i = 0; i <= curBul; i++) {
		for (int j = 0; j < 5; j++)
		if (sqrt(pow(bullet[i]->curX - bullet[i]->toX, 2) + pow(bullet[i]->curY - bullet[i]->toY, 2)) < step) {
			bullet[i]->curX = bullet[i]->toX;
			bullet[i]->curY = bullet[i]->toY;
			bullet[i]->img->Left = bullet[i]->toX - 8;
			bullet[i]->img->Top = bullet[i]->toY - 8;
		}
		else {
			bullet[i]->curX += bullet[i]->dx;
			bullet[i]->curY += bullet[i]->dy;
			bullet[i]->img->Left = round(bullet[i]->curX) - 8;
			bullet[i]->img->Top = round(bullet[i]->curY) - 8;
		}
		if (abs(bullet[i]->curX - bullet[i]->toX) <= 8 && abs(bullet[i]->curY - bullet[i]->toY) <= 8) {
			bullet[i]->img->Visible = false;
			bullet[i]->img->Enabled = false;
			bullet[i]->img->Left = -100;
			bullet[i]->img->Top = -100;
			bullet[i]->damage = 0;
		}

		for (int c = 0; c <= MAXMOB; c++)
		if (mobs[c]->live)
			if (bullet[i]->img->Left >= mobs[c]->img->Left && bullet[i]->img->Left <= mobs[c]->img->Left + mobs[c]->img->Width - 50
			 && bullet[i]->img->Top >= mobs[c]->img->Top && bullet[i]->img->Top <= mobs[c]->img->Top + mobs[c]->img->Height - 50) {
				mobs[c]->hp -= bullet[i]->damage;
                bullet[i]->img->Visible = false;
				bullet[i]->img->Enabled = false;
                bullet[i]->img->Left = -100;
				bullet[i]->img->Top = -100;
				bullet[i]->damage = 0;
			}
	}
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::CreateBulletT(TObject *Sender)
{
	fire();
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Timer3->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::MoveMob(TObject *Sender)
{

	int l = 1;
	for (int j = 0 ; j <= MAXMOB; j++)
	if (mobs[j]->live) {
		for (int i = 0; i < 3; i++) {
			if (sqrt(pow(mobs[j]->curX - mobs[j]->toX, 2) + pow(mobs[j]->curY - mobs[j]->toY, 2)) < step1) {
				mobs[j]->curX = mobs[j]->toX;
				mobs[j]->curY = mobs[j]->toY;
				mobs[j]->img->Left = mobs[j]->toX - l;
				mobs[j]->img->Top = mobs[j]->toY - l;
			}
			else {
				mobs[j]->curX += mobs[j]->dx;
				mobs[j]->curY += mobs[j]->dy;
				mobs[j]->img->Left = round(mobs[j]->curX);
				mobs[j]->img->Top = round(mobs[j]->curY);
			}
		}
	}
}
//---------------------------------------------------------------------------



void __fastcall TGameForm::MobIMGMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Timer3->Enabled = true;
	fire();
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::MobIMGMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Timer3->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::FormShow(TObject *Sender)
{
	for (int i = 0; i < 3; i++) {
		mobs[i] = new Node;
		mobs[i]->img = new TImage(GameForm);
        mobs[i]->live = false;
	}
	PlayerIMG->Height = 150;
	PlayerIMG->Width = 150;
	player = new(Node);
	player->hp = 100;
	Timer1->Enabled = true;
	Timer2->Enabled = true;
	Timer4->Enabled = true;
	Timer5->Enabled = true;
	Timer6->Enabled = true;
	GameForm->Color = (TColor)RGB(34, 177, 76);
	spawnMob();
}
//---------------------------------------------------------------------------



void __fastcall TGameForm::HealthIMGMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    Timer3->Enabled = true;
	fire();
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::HealthLBMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    Timer3->Enabled = true;
	fire();
}
//---------------------------------------------------------------------------
void __fastcall TGameForm::spawnMob() {
	bool spawnFlag = false;
	for (int i = 0; i < 3; i++) {
		if (!mobs[i]->live) {
			curMob = i;
			spawnFlag = true;
			break;
		}
	}

	if (!spawnFlag) {
		curMob = firstMob;
		mobs[firstMob]->img->Left = -100;
		mobs[firstMob]->img->Top = -100;
		mobs[firstMob]->img->Visible = false;
		mobs[firstMob]->img->Enabled = false;
		firstMob++;
		while (!mobs[firstMob]->live)
			firstMob++;
	}
	mobs[curMob] = new Node;
	mobs[curMob]->img = new TImage(GameForm);
	mobs[curMob]->img->SendToBack();
	mobs[curMob]->img->Parent = GameForm;
	srand(time(0));
	int side = 1 + rand() % 4;
	if (side == LU) {
		mobs[curMob]->img->Left = 0;
		mobs[curMob]->img->Top = 0;
	}
	if (side == RU) {
		mobs[curMob]->img->Left = 1600;
		mobs[curMob]->img->Top = 0;
	}
	if (side == LD) {
		mobs[curMob]->img->Left = 0;
		mobs[curMob]->img->Top = 900;
	}
	if (side == RD) {
		mobs[curMob]->img->Left = 1500;
		mobs[curMob]->img->Top = 900;
	}
	mobs[curMob]->img->Width = 400;
	mobs[curMob]->img->Height = 300;
	mobs[curMob]->hp = 130;
	mobs[curMob]->damage = 10;
	mobs[curMob]->giveHp = 2;
	mobs[curMob]->giveScore = 1;
	mobs[curMob]->live = true;
	mobs[curMob]->img->OnMouseDown = MobIMGMouseDown;
	mobs[curMob]->img->OnMouseUp = MobIMGMouseUp;
	mobs[curMob]->img->Visible = true;
	mobs[curMob]->img->Transparent = true;
}

//---------------------------------------------------------------------------
void __fastcall TGameForm::Timer5Timer(TObject *Sender)
{
	spawnMob();
	setOptionsMob();
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::HealthIMGMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    Timer3->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::HealthLBMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Timer3->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TGameForm::Timer6Timer(TObject *Sender)
{
	for (int i = 0; i <= MAXMOB; i++)
		if (mobs[i]->live){
		if (mobs[i]->img->Left + mobs[i]->img->Width - 50 >= PlayerIMG->Left
		&& mobs[i]->img->Top + mobs[i]->img->Height - 40  >= PlayerIMG->Top)
		{
			player->hp -= mobs[i]->damage;
        }
	}
}
//---------------------------------------------------------------------------

