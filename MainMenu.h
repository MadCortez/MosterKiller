//---------------------------------------------------------------------------

#ifndef MainMenuH
#define MainMenuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Buttons.hpp>
#include <Game.h>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TSpeedButton *ExitBt;
	TSpeedButton *AboutBt;
	TSpeedButton *PlayBt;
	TLabel *AboutLb;
	TImage *Image1;
	TLabel *VersionLB;
	TLabel *DeveloperLB;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ExitBtClick(TObject *Sender);
	void __fastcall AboutBtClick(TObject *Sender);
	void __fastcall PlayBtClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};

bool flag = false;
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
