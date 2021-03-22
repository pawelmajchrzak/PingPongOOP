//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x=-4, y=-4;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ballTimerTimer(TObject *Sender)
{
        ball->Left += x;
        ball->Top += y;

        if (ball->Top <= bg->Top) y = -y;
        if (ball->Top + ball->Height  >= bg->Height) y = -y;

        // lose
        if ((ball->Left <= pl->Left - ball->Width)||(ball->Left + ball->Width >= de->Left + de->Width + ball->Width))
        {
                ballTimer->Enabled = false;
        }
        else if ((ball->Top + ball->Height/2 > pl->Top) && (ball->Top + ball->Height/2 < pl->Top + pl->Height) && (ball->Left < pl->Left + pl->Width))
        {
                if(x<0) x = -x;
        }
        else if ((ball->Top + ball->Height/2 > de->Top) && (ball->Top + ball->Height/2 < de->Top + de->Height) && (ball->Left + ball->Width > de->Left))
        {
                if (x>0) x = -x;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::plUpTimer(TObject *Sender)
{
        if(pl->Top > 0) pl->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::plDownTimer(TObject *Sender)
{
        if(pl->Top + pl->Height < bg->Height) pl->Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 'A') plUp -> Enabled = true;
        if (Key == 'Z') plDown -> Enabled = true;

        if (Key == VK_UP) deUp -> Enabled = true;
        if (Key == VK_DOWN) deDown -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 'A') plUp -> Enabled = false;
        if (Key == 'Z') plDown -> Enabled = false;

        if (Key == VK_UP) deUp -> Enabled = false;
        if (Key == VK_DOWN) deDown -> Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::deUpTimer(TObject *Sender)
{
        if(de->Top > 0) de->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::deDownTimer(TObject *Sender)
{
        if(de->Top + de->Height < bg->Height) de->Top += 10;
}
//---------------------------------------------------------------------------

