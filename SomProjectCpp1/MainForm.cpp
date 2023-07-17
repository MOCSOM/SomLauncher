#include "MainForm.h"



void SomLauncherMainWin::MainForm::animationtoppanel(bool expect, int anim)
{
	if (expect == true && anim == 1)
	{
		while (!this->expect_table_menu && this->tableLayoutPanel_menu->Location.Y < 0)
		{
			this->expect_table_menu = true;
			this->tableLayoutPanel_menu->Location = System::Drawing::Point(this->tableLayoutPanel_menu->Location.X,
				//this->tableLayoutPanel_menu->Location.Y - this->tableLayoutPanel_menu->Location.Y / 18 + 1);
				this->tableLayoutPanel_menu->Location.Y + 2);
			this->expect_table_menu = false;
		}

		this->button_game->TextAlign = System::Drawing::ContentAlignment(32);
		this->button_news->TextAlign = System::Drawing::ContentAlignment(32);
		this->button_donate->TextAlign = System::Drawing::ContentAlignment(32);
		this->button_servers->TextAlign = System::Drawing::ContentAlignment(32);
	}
	if (expect == true && anim == 2)
	{
		Sleep(300);

		while (!this->expect_table_menu && this->tableLayoutPanel_menu->Location.Y > -90)
		{
			this->expect_table_menu = true;
			this->tableLayoutPanel_menu->Location = System::Drawing::Point(this->tableLayoutPanel_menu->Location.X,
				this->tableLayoutPanel_menu->Location.Y - 1);
			this->expect_table_menu = false;
		}

		this->button_game->TextAlign = System::Drawing::ContentAlignment(512);
		this->button_news->TextAlign = System::Drawing::ContentAlignment(512);
		this->button_donate->TextAlign = System::Drawing::ContentAlignment(512);
		this->button_servers->TextAlign = System::Drawing::ContentAlignment(512);
	}
}

void SomLauncherMainWin::MainForm::create_form_changeserv()
{
	SomLauncherMainWin::ChangeServerForm^ form_serv = gcnew SomLauncherMainWin::ChangeServerForm(config_path);
	form_serv->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
	form_serv->ShowDialog();

	//// Create a new form.
	//Form^ form_change_server = gcnew Form();
	//// Set the text displayed in the caption.
	//form_change_server->Text = "Change server";
	//// Size the form to be 300 pixels in height and width.
	//form_change_server->Size = System::Drawing::Size(300, 400);
	//// Display the form in the center of the screen.
	//form_change_server->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;

	//// Display the form as a modal dialog box.
	//form_change_server->ShowDialog();
}

System::Void SomLauncherMainWin::MainForm::test_Click(System::Object^ sender, System::EventArgs^ e)
{
	
	//// Create a new form.
	//Form^ form2 = gcnew Form();
	//// Set the text displayed in the caption.
	//form2->Text = "My Form";
	//// Set the opacity to 75%.
	//form2->Opacity = .75;
	//// Size the form to be 300 pixels in height and width.
	//form2->Size = System::Drawing::Size(300, 300);
	//// Display the form in the center of the screen.
	//form2->StartPosition = FormStartPosition::CenterScreen;

	//// Display the form as a modal dialog box.
	//form2->ShowDialog();s


	if (win_is_small == false)
	{
		this->Size = System::Drawing::Size(449, 598);
		this->win_is_small = true;
	}
	else if (win_is_small == true)
	{
		this->Size = System::Drawing::Size(1069, 598);
		this->win_is_small = false;
	}

}

System::Void SomLauncherMainWin::MainForm::panel_toppanel_hover_MouseEnter(System::Object^ sender, System::EventArgs^ e)
{
	this->tableLayoutPanel_menu->Capture = true;

	animationtoppanel(is_down_table_menu, 1);


}

System::Void SomLauncherMainWin::MainForm::panel_toppanel_hover_MouseLeave(System::Object^ sender, System::EventArgs^ e)
{
	this->tableLayoutPanel_menu->Capture = false;

	animationtoppanel(is_down_table_menu, 2);
	

	/*Invoke(gcnew System::Action<int>(this, &MainForm::animationtoppanel), is_down_table_menu, 2);
	
	this->Invoke(gcnew System::Action(this, &SomLauncherMainWin::MainForm::animationtoppanel), is_down_table_menu, 2);
	System::Threading::ThreadStart^ threadDelegate = gcnew System::Threading::ThreadStart(gcnew int, &SomLauncherMainWin::MainForm::animationtoppanel);
	System::Threading::Thread^ newThread = gcnew System::Threading::Thread(threadDelegate);
	newThread->Start();

	System::Threading::Thread^ myThread = gcnew System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(animationtoppanel));
	array<Object^>^ args = gcnew array<Object^>{is_down_table_menu, 2};

	myThread->Start(args);*/

	
}

System::Void SomLauncherMainWin::MainForm::button_servers_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->panelserv->BringToFront();
	this->tableLayoutPanel_menu->BringToFront();
}

System::Void SomLauncherMainWin::MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	this->tableLayoutPanel_menu->BringToFront();
	//listpages->Add(panelmainwitout);
	//listpages->Add(panelserv);
}

System::Void SomLauncherMainWin::MainForm::button_game_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->panelmainwitout->BringToFront();
	this->tableLayoutPanel_menu->BringToFront();
}

System::Void SomLauncherMainWin::MainForm::button_game_MouseEnter(System::Object^ sender, System::EventArgs^ e)
{
	is_down_table_menu = false;
}

System::Void SomLauncherMainWin::MainForm::button_game_MouseLeave(System::Object^ sender, System::EventArgs^ e)
{
	is_down_table_menu = true;
}

System::Void SomLauncherMainWin::MainForm::button_play_Click(System::Object^ sender, System::EventArgs^ e)
{
	start_minecraft_params();
}

System::Void SomLauncherMainWin::MainForm::button_changeserv_Click(System::Object^ sender, System::EventArgs^ e)
{
	create_form_changeserv();
}

System::Void SomLauncherMainWin::MainForm::label_botton_profile_Click(System::Object^ sender, System::EventArgs^ e)
{

	return System::Void();
}
