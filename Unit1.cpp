//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x=-3, y=-3;
int pktPl = 0;
int pktDe = 0;
int numberOfBounce = 0;
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
        if (ball->Left <= pl->Left - ball->Width)
        {
                ballTimer->Enabled = false;
                pktDe++;
                Label1->Caption = "Punkt dla Niemiec >>";
                Label2->Caption = IntToStr(pktPl)+" : "+IntToStr(pktDe);
                Label3->Caption = "Iloœæ odbiæ: "+IntToStr(numberOfBounce);
                Label1->Visible = true;
                Label2->Visible = true;
                Label3->Visible = true;
                Button1 -> Visible = true;
                Button2 -> Visible = true;
        }
        else if (ball->Left + ball->Width >= de->Left + de->Width + ball->Width)
        {
                ballTimer->Enabled = false;
                pktPl++;
                Label1->Caption = "<< Punkt dla Polski";
                Label2->Caption = IntToStr(pktPl)+" : "+IntToStr(pktDe);
                Label3->Caption = "Iloœæ odbiæ: "+IntToStr(numberOfBounce);
                Label1->Visible = true;
                Label2->Visible = true;
                Label3->Visible = true;
                Button1 -> Visible = true;
                Button2 -> Visible = true;
        }
        else if ((ball->Top + ball->Height/2 > pl->Top) && (ball->Top + ball->Height/2 < pl->Top + pl->Height) && (ball->Left < pl->Left + pl->Width))
        {
                if(x<0)
                {
                        x = -x;
                        numberOfBounce++;
                        if ( numberOfBounce%3 == 0)
                        {
                                x += 2;
                                y += 2;
                        }
                }
        }
        else if ((ball->Top + ball->Height/2 > de->Top) && (ball->Top + ball->Height/2 < de->Top + de->Height) && (ball->Left + ball->Width > de->Left))
        {
                if (x>0)
                {
                        x = -x;
                        numberOfBounce++;
                }
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

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        if(!(pktPl == 0 && pktDe == 0))
        {
                if(Application->MessageBox(
                "Czy napewno chcesz rozpocz¹æ now¹ grê?","PotwierdŸ",
                MB_YESNO | MB_ICONQUESTION) == IDYES)
                {
                        ball->Left = 392;
                        ball->Top = 256;
                        x=-3; y=-3;
                        pktPl = 0;
                        pktDe = 0;
                        numberOfBounce = 0;
                        Button1 -> Visible = false;
                        Button2 -> Visible = false;
                        Label1 -> Visible = false;
                        Label2 -> Visible = false;
                        Label3 -> Visible = false;
                        ballTimer -> Enabled = true;
                }
        }
        else
        {
                        Button1 -> Visible = false;
                        Label1 -> Visible = false;
                        ballTimer -> Enabled = true;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
        randomize();
        int positiveNegativeX = random(2)*2 - 1;
        int positiveNegativeY = random(2)*2 - 1;
        ball->Left = 392;
        ball->Top = 256;
        x=-3*positiveNegativeX; y=-3*positiveNegativeY;
        numberOfBounce = 0;
        Button1 -> Visible = false;
        Button2 -> Visible = false;
        Label1 -> Visible = false;
        Label2 -> Visible = false;
        Label3 -> Visible = false;
        ballTimer -> Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Application->MessageBox("Witaj w grze PingPong.\n\nLewy gracz sterujg wciskaj¹c klawisze A oraz Z.\nPrawy gracz steruje wciskaj¹c strza³ki do góry i w dó³.\n\nIm d³u¿ej odbijasz tym pi³ka szybciej przemieszcza siê.\n\nMi³ej zabawy!",
				"Ping Pong", MB_OK);
}
//---------------------------------------------------------------------------

