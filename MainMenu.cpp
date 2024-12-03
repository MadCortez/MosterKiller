//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainMenu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	//Image1->Width = 1920;
	//Image1->Height = 1080;
    DeveloperLB->Caption = "Developer\nPestunov Ilya\n051007\nBSUIR";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ExitBtClick(TObject *Sender)
{
	if (flag) {
		flag = false;
		AboutBt->Visible = true;
		ExitBt->Caption = "EXIT";
		ExitBt->Visible = true;
		PlayBt->Visible = true;
		AboutLb->Visible = false;
	}
	else
		MainForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AboutBtClick(TObject *Sender)
{
	flag = true;
	AboutBt->Visible = false;
	ExitBt->Caption = "BACK";
    ExitBt->BringToFront();
	PlayBt->Visible = false;
	AboutLb->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PlayBtClick(TObject *Sender)
{
	GameForm->Show();
	MainForm->Hide();
}
//---------------------------------------------------------------------------

