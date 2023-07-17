#ifndef MAINFORM_H_     // equivalently, #if !defined HEADER_H_
#define MAINFORM_H_

#include "Minecraftus.h"
//#include "Json.h"
//#include "SomDict.h" //TODO бл€
#include "DownloadClasses.h"
#include "CallbackDict.h"
#include "ChangeServerForm.h"
#include "Additionals.h"
#include <Windows.h>

namespace SomLauncherMainWin {

	/*using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;*/

	/// <summary>
	/// —водка дл€ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel_main;
	private: System::Windows::Forms::Panel^ panelmainwitout;

	protected:

	private: System::Windows::Forms::Button^ test;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::PictureBox^ pictureBox_logo;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Button^ button_changeserv;
	private: System::Windows::Forms::Button^ button_chaeckupd;
	private: System::Windows::Forms::Button^ button_Reportbug;
	private: System::Windows::Forms::Panel^ panel7;
	private: System::Windows::Forms::Button^ button_play;
	private: System::Windows::Forms::Label^ label_serverstatus;
	private: System::Windows::Forms::Label^ label_clienttype_changer;
	private: System::Windows::Forms::Label^ label_modscount_changer;
	private: System::Windows::Forms::Label^ label_Server_changer;
	private: System::Windows::Forms::Label^ label_typeclient;
	private: System::Windows::Forms::Label^ label_modscount;
	private: System::Windows::Forms::Label^ label_server;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel_menu;
	private: System::Windows::Forms::Button^ button_game;
	private: System::Windows::Forms::Panel^ panel_account;
	private: System::Windows::Forms::Button^ button_donate;
	private: System::Windows::Forms::Button^ button_servers;
	private: System::Windows::Forms::Button^ button_news;
	private: System::Windows::Forms::Panel^ panelserv;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
	private: System::Windows::Forms::SplitContainer^ splitContainer2;
	protected private: System::Windows::Forms::RadioButton^ radioButton1;
	private:

	private: System::Windows::Forms::TabControl^ tabControl1;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::Label^ label_serv_ver2;

	private: System::Windows::Forms::Label^ label_serv_status2;

	private: System::Windows::Forms::Label^ label_serv_name2;

	private: System::Windows::Forms::ProgressBar^ progressBar2;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::RichTextBox^ richTextBox2;
	private: System::Windows::Forms::SplitContainer^ splitContainer1;
	protected private: System::Windows::Forms::RadioButton^ radioButton_sev_select;
	private:

	private:

	private: System::Windows::Forms::TabControl^ tabControl_serv;
	private: System::Windows::Forms::TabPage^ tabPage_serv_info;
	private: System::Windows::Forms::Label^ label_serv_ver;
	private: System::Windows::Forms::Label^ label_serv_status;
	private: System::Windows::Forms::Label^ label_serv_name;

	private: System::Windows::Forms::ProgressBar^ progressBar_serv_capacity;
	private: System::Windows::Forms::TabPage^ tabPage_serv_description;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Label^ label_serv_capacit;
	private: System::Windows::Forms::Label^ label_serv_capacit2;
	private: System::Windows::Forms::Label^ label_botton_profile;


	protected:

	protected:


	protected:


	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel_main = (gcnew System::Windows::Forms::Panel());
			this->panelmainwitout = (gcnew System::Windows::Forms::Panel());
			this->test = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->pictureBox_logo = (gcnew System::Windows::Forms::PictureBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->button_changeserv = (gcnew System::Windows::Forms::Button());
			this->button_chaeckupd = (gcnew System::Windows::Forms::Button());
			this->button_Reportbug = (gcnew System::Windows::Forms::Button());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->button_play = (gcnew System::Windows::Forms::Button());
			this->label_serverstatus = (gcnew System::Windows::Forms::Label());
			this->label_clienttype_changer = (gcnew System::Windows::Forms::Label());
			this->label_modscount_changer = (gcnew System::Windows::Forms::Label());
			this->label_Server_changer = (gcnew System::Windows::Forms::Label());
			this->label_typeclient = (gcnew System::Windows::Forms::Label());
			this->label_modscount = (gcnew System::Windows::Forms::Label());
			this->label_server = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->tableLayoutPanel_menu = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button_game = (gcnew System::Windows::Forms::Button());
			this->panel_account = (gcnew System::Windows::Forms::Panel());
			this->label_botton_profile = (gcnew System::Windows::Forms::Label());
			this->button_donate = (gcnew System::Windows::Forms::Button());
			this->button_servers = (gcnew System::Windows::Forms::Button());
			this->button_news = (gcnew System::Windows::Forms::Button());
			this->panelserv = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->label_serv_capacit2 = (gcnew System::Windows::Forms::Label());
			this->label_serv_ver2 = (gcnew System::Windows::Forms::Label());
			this->label_serv_status2 = (gcnew System::Windows::Forms::Label());
			this->label_serv_name2 = (gcnew System::Windows::Forms::Label());
			this->progressBar2 = (gcnew System::Windows::Forms::ProgressBar());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->radioButton_sev_select = (gcnew System::Windows::Forms::RadioButton());
			this->tabControl_serv = (gcnew System::Windows::Forms::TabControl());
			this->tabPage_serv_info = (gcnew System::Windows::Forms::TabPage());
			this->label_serv_capacit = (gcnew System::Windows::Forms::Label());
			this->label_serv_ver = (gcnew System::Windows::Forms::Label());
			this->label_serv_status = (gcnew System::Windows::Forms::Label());
			this->label_serv_name = (gcnew System::Windows::Forms::Label());
			this->progressBar_serv_capacity = (gcnew System::Windows::Forms::ProgressBar());
			this->tabPage_serv_description = (gcnew System::Windows::Forms::TabPage());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->panel_main->SuspendLayout();
			this->panelmainwitout->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_logo))->BeginInit();
			this->panel3->SuspendLayout();
			this->panel7->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->tableLayoutPanel_menu->SuspendLayout();
			this->panel_account->SuspendLayout();
			this->panelserv->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->BeginInit();
			this->splitContainer2->Panel1->SuspendLayout();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->tabControl_serv->SuspendLayout();
			this->tabPage_serv_info->SuspendLayout();
			this->tabPage_serv_description->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel_main
			// 
			this->panel_main->Controls->Add(this->panelmainwitout);
			this->panel_main->Controls->Add(this->tableLayoutPanel_menu);
			this->panel_main->Controls->Add(this->panelserv);
			this->panel_main->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel_main->Location = System::Drawing::Point(0, 0);
			this->panel_main->Margin = System::Windows::Forms::Padding(2);
			this->panel_main->Name = L"panel_main";
			this->panel_main->Size = System::Drawing::Size(841, 447);
			this->panel_main->TabIndex = 2;
			// 
			// panelmainwitout
			// 
			this->panelmainwitout->Controls->Add(this->test);
			this->panelmainwitout->Controls->Add(this->tableLayoutPanel1);
			this->panelmainwitout->Controls->Add(this->progressBar1);
			this->panelmainwitout->Controls->Add(this->tableLayoutPanel2);
			this->panelmainwitout->Location = System::Drawing::Point(9, 36);
			this->panelmainwitout->Margin = System::Windows::Forms::Padding(2);
			this->panelmainwitout->Name = L"panelmainwitout";
			this->panelmainwitout->Size = System::Drawing::Size(822, 402);
			this->panelmainwitout->TabIndex = 0;
			// 
			// test
			// 
			this->test->Location = System::Drawing::Point(238, 238);
			this->test->Margin = System::Windows::Forms::Padding(2);
			this->test->Name = L"test";
			this->test->Size = System::Drawing::Size(60, 19);
			this->test->TabIndex = 17;
			this->test->Text = L"test";
			this->test->UseVisualStyleBackColor = true;
			this->test->Click += gcnew System::EventHandler(this, &MainForm::test_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				611)));
			this->tableLayoutPanel1->Controls->Add(this->pictureBox_logo, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->panel3, 1, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(2, 269);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(2);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(820, 122);
			this->tableLayoutPanel1->TabIndex = 15;
			// 
			// pictureBox_logo
			// 
			this->pictureBox_logo->Location = System::Drawing::Point(2, 2);
			this->pictureBox_logo->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox_logo->Name = L"pictureBox_logo";
			this->pictureBox_logo->Size = System::Drawing::Size(204, 116);
			this->pictureBox_logo->TabIndex = 1;
			this->pictureBox_logo->TabStop = false;
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->button_changeserv);
			this->panel3->Controls->Add(this->button_chaeckupd);
			this->panel3->Controls->Add(this->button_Reportbug);
			this->panel3->Controls->Add(this->panel7);
			this->panel3->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::World,
				static_cast<System::Byte>(204)));
			this->panel3->Location = System::Drawing::Point(211, 2);
			this->panel3->Margin = System::Windows::Forms::Padding(2);
			this->panel3->MinimumSize = System::Drawing::Size(536, 80);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(606, 116);
			this->panel3->TabIndex = 2;
			// 
			// button_changeserv
			// 
			this->button_changeserv->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::World,
				static_cast<System::Byte>(204)));
			this->button_changeserv->Location = System::Drawing::Point(68, 4);
			this->button_changeserv->Margin = System::Windows::Forms::Padding(2);
			this->button_changeserv->Name = L"button_changeserv";
			this->button_changeserv->Size = System::Drawing::Size(177, 26);
			this->button_changeserv->TabIndex = 6;
			this->button_changeserv->Text = L"Change server";
			this->button_changeserv->UseVisualStyleBackColor = true;
			this->button_changeserv->Click += gcnew System::EventHandler(this, &MainForm::button_changeserv_Click);
			// 
			// button_chaeckupd
			// 
			this->button_chaeckupd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::World,
				static_cast<System::Byte>(204)));
			this->button_chaeckupd->Location = System::Drawing::Point(251, 4);
			this->button_chaeckupd->Margin = System::Windows::Forms::Padding(2);
			this->button_chaeckupd->Name = L"button_chaeckupd";
			this->button_chaeckupd->Size = System::Drawing::Size(177, 26);
			this->button_chaeckupd->TabIndex = 5;
			this->button_chaeckupd->Text = L"Check for updates";
			this->button_chaeckupd->UseVisualStyleBackColor = true;
			// 
			// button_Reportbug
			// 
			this->button_Reportbug->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::World,
				static_cast<System::Byte>(204)));
			this->button_Reportbug->Location = System::Drawing::Point(434, 4);
			this->button_Reportbug->Margin = System::Windows::Forms::Padding(2);
			this->button_Reportbug->Name = L"button_Reportbug";
			this->button_Reportbug->Size = System::Drawing::Size(170, 26);
			this->button_Reportbug->TabIndex = 4;
			this->button_Reportbug->Text = L"Report bug";
			this->button_Reportbug->UseVisualStyleBackColor = true;
			// 
			// panel7
			// 
			this->panel7->Controls->Add(this->button_play);
			this->panel7->Controls->Add(this->label_serverstatus);
			this->panel7->Controls->Add(this->label_clienttype_changer);
			this->panel7->Controls->Add(this->label_modscount_changer);
			this->panel7->Controls->Add(this->label_Server_changer);
			this->panel7->Controls->Add(this->label_typeclient);
			this->panel7->Controls->Add(this->label_modscount);
			this->panel7->Controls->Add(this->label_server);
			this->panel7->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 13, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::World,
				static_cast<System::Byte>(204)));
			this->panel7->Location = System::Drawing::Point(68, 34);
			this->panel7->Margin = System::Windows::Forms::Padding(2);
			this->panel7->MaximumSize = System::Drawing::Size(536, 80);
			this->panel7->MinimumSize = System::Drawing::Size(536, 80);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(536, 80);
			this->panel7->TabIndex = 3;
			// 
			// button_play
			// 
			this->button_play->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::World,
				static_cast<System::Byte>(204)));
			this->button_play->Location = System::Drawing::Point(284, 7);
			this->button_play->Margin = System::Windows::Forms::Padding(2);
			this->button_play->Name = L"button_play";
			this->button_play->Size = System::Drawing::Size(236, 64);
			this->button_play->TabIndex = 7;
			this->button_play->Text = L"Play";
			this->button_play->UseVisualStyleBackColor = true;
			this->button_play->Click += gcnew System::EventHandler(this, &MainForm::button_play_Click);
			// 
			// label_serverstatus
			// 
			this->label_serverstatus->AutoSize = true;
			this->label_serverstatus->Location = System::Drawing::Point(56, 11);
			this->label_serverstatus->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_serverstatus->Name = L"label_serverstatus";
			this->label_serverstatus->Size = System::Drawing::Size(43, 16);
			this->label_serverstatus->TabIndex = 6;
			this->label_serverstatus->Text = L"NONE";
			// 
			// label_clienttype_changer
			// 
			this->label_clienttype_changer->AutoSize = true;
			this->label_clienttype_changer->Location = System::Drawing::Point(89, 57);
			this->label_clienttype_changer->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_clienttype_changer->Name = L"label_clienttype_changer";
			this->label_clienttype_changer->Size = System::Drawing::Size(43, 16);
			this->label_clienttype_changer->TabIndex = 5;
			this->label_clienttype_changer->Text = L"NONE";
			// 
			// label_modscount_changer
			// 
			this->label_modscount_changer->AutoSize = true;
			this->label_modscount_changer->Location = System::Drawing::Point(93, 34);
			this->label_modscount_changer->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_modscount_changer->Name = L"label_modscount_changer";
			this->label_modscount_changer->Size = System::Drawing::Size(43, 16);
			this->label_modscount_changer->TabIndex = 4;
			this->label_modscount_changer->Text = L"NONE";
			// 
			// label_Server_changer
			// 
			this->label_Server_changer->AutoSize = true;
			this->label_Server_changer->Location = System::Drawing::Point(109, 11);
			this->label_Server_changer->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_Server_changer->Name = L"label_Server_changer";
			this->label_Server_changer->Size = System::Drawing::Size(43, 16);
			this->label_Server_changer->TabIndex = 3;
			this->label_Server_changer->Text = L"NONE";
			// 
			// label_typeclient
			// 
			this->label_typeclient->AutoSize = true;
			this->label_typeclient->Location = System::Drawing::Point(6, 57);
			this->label_typeclient->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_typeclient->Name = L"label_typeclient";
			this->label_typeclient->Size = System::Drawing::Size(79, 16);
			this->label_typeclient->TabIndex = 2;
			this->label_typeclient->Text = L"Client type:";
			// 
			// label_modscount
			// 
			this->label_modscount->AutoSize = true;
			this->label_modscount->Location = System::Drawing::Point(6, 34);
			this->label_modscount->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_modscount->Name = L"label_modscount";
			this->label_modscount->Size = System::Drawing::Size(83, 16);
			this->label_modscount->TabIndex = 1;
			this->label_modscount->Text = L"Mods count:";
			// 
			// label_server
			// 
			this->label_server->AutoSize = true;
			this->label_server->Location = System::Drawing::Point(6, 11);
			this->label_server->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_server->Name = L"label_server";
			this->label_server->Size = System::Drawing::Size(53, 16);
			this->label_server->TabIndex = 0;
			this->label_server->Text = L"Server:";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(302, 238);
			this->progressBar1->Margin = System::Windows::Forms::Padding(2);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(499, 14);
			this->progressBar1->TabIndex = 16;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 3;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				38.47516F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				30.76242F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				30.76242F)));
			this->tableLayoutPanel2->Controls->Add(this->pictureBox1, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->pictureBox2, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->pictureBox3, 2, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(4, 26);
			this->tableLayoutPanel2->Margin = System::Windows::Forms::Padding(2);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(813, 192);
			this->tableLayoutPanel2->TabIndex = 18;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(2, 2);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(308, 188);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox2->Location = System::Drawing::Point(314, 2);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(246, 188);
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox3->Location = System::Drawing::Point(564, 2);
			this->pictureBox3->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(247, 188);
			this->pictureBox3->TabIndex = 2;
			this->pictureBox3->TabStop = false;
			// 
			// tableLayoutPanel_menu
			// 
			this->tableLayoutPanel_menu->BackColor = System::Drawing::SystemColors::Highlight;
			this->tableLayoutPanel_menu->ColumnCount = 5;
			this->tableLayoutPanel_menu->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				18.18033F)));
			this->tableLayoutPanel_menu->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				18.18215F)));
			this->tableLayoutPanel_menu->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				18.18215F)));
			this->tableLayoutPanel_menu->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				18.18215F)));
			this->tableLayoutPanel_menu->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				27.27323F)));
			this->tableLayoutPanel_menu->Controls->Add(this->button_game, 0, 0);
			this->tableLayoutPanel_menu->Controls->Add(this->panel_account, 4, 0);
			this->tableLayoutPanel_menu->Controls->Add(this->button_donate, 3, 0);
			this->tableLayoutPanel_menu->Controls->Add(this->button_servers, 1, 0);
			this->tableLayoutPanel_menu->Controls->Add(this->button_news, 2, 0);
			this->tableLayoutPanel_menu->Location = System::Drawing::Point(9, -90);
			this->tableLayoutPanel_menu->Margin = System::Windows::Forms::Padding(2);
			this->tableLayoutPanel_menu->Name = L"tableLayoutPanel_menu";
			this->tableLayoutPanel_menu->RowCount = 1;
			this->tableLayoutPanel_menu->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel_menu->Size = System::Drawing::Size(822, 121);
			this->tableLayoutPanel_menu->TabIndex = 12;
			this->tableLayoutPanel_menu->MouseEnter += gcnew System::EventHandler(this, &MainForm::panel_toppanel_hover_MouseEnter);
			this->tableLayoutPanel_menu->MouseLeave += gcnew System::EventHandler(this, &MainForm::panel_toppanel_hover_MouseLeave);
			// 
			// button_game
			// 
			this->button_game->Location = System::Drawing::Point(2, 2);
			this->button_game->Margin = System::Windows::Forms::Padding(2);
			this->button_game->Name = L"button_game";
			this->button_game->Size = System::Drawing::Size(144, 115);
			this->button_game->TabIndex = 4;
			this->button_game->Text = L"GAME";
			this->button_game->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->button_game->UseVisualStyleBackColor = true;
			this->button_game->Click += gcnew System::EventHandler(this, &MainForm::button_game_Click);
			this->button_game->MouseEnter += gcnew System::EventHandler(this, &MainForm::button_game_MouseEnter);
			this->button_game->MouseLeave += gcnew System::EventHandler(this, &MainForm::button_game_MouseLeave);
			// 
			// panel_account
			// 
			this->panel_account->BackColor = System::Drawing::SystemColors::GrayText;
			this->panel_account->Controls->Add(this->label_botton_profile);
			this->panel_account->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel_account->Location = System::Drawing::Point(598, 2);
			this->panel_account->Margin = System::Windows::Forms::Padding(2);
			this->panel_account->Name = L"panel_account";
			this->panel_account->Size = System::Drawing::Size(222, 117);
			this->panel_account->TabIndex = 1;
			// 
			// label_botton_profile
			// 
			this->label_botton_profile->AutoSize = true;
			this->label_botton_profile->Location = System::Drawing::Point(169, 95);
			this->label_botton_profile->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_botton_profile->Name = L"label_botton_profile";
			this->label_botton_profile->Size = System::Drawing::Size(54, 13);
			this->label_botton_profile->TabIndex = 0;
			this->label_botton_profile->Text = L"topdouwn";
			this->label_botton_profile->Click += gcnew System::EventHandler(this, &MainForm::label_botton_profile_Click);
			// 
			// button_donate
			// 
			this->button_donate->Location = System::Drawing::Point(449, 2);
			this->button_donate->Margin = System::Windows::Forms::Padding(2);
			this->button_donate->Name = L"button_donate";
			this->button_donate->Size = System::Drawing::Size(144, 115);
			this->button_donate->TabIndex = 3;
			this->button_donate->Text = L"ABOUT US";
			this->button_donate->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->button_donate->UseVisualStyleBackColor = true;
			// 
			// button_servers
			// 
			this->button_servers->Location = System::Drawing::Point(151, 2);
			this->button_servers->Margin = System::Windows::Forms::Padding(2);
			this->button_servers->Name = L"button_servers";
			this->button_servers->Size = System::Drawing::Size(144, 115);
			this->button_servers->TabIndex = 0;
			this->button_servers->Text = L"SERVERS";
			this->button_servers->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->button_servers->UseVisualStyleBackColor = true;
			this->button_servers->Click += gcnew System::EventHandler(this, &MainForm::button_servers_Click);
			// 
			// button_news
			// 
			this->button_news->Location = System::Drawing::Point(300, 2);
			this->button_news->Margin = System::Windows::Forms::Padding(2);
			this->button_news->Name = L"button_news";
			this->button_news->Size = System::Drawing::Size(144, 115);
			this->button_news->TabIndex = 2;
			this->button_news->Text = L"NEWS";
			this->button_news->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->button_news->UseVisualStyleBackColor = true;
			// 
			// panelserv
			// 
			this->panelserv->Controls->Add(this->tableLayoutPanel4);
			this->panelserv->Location = System::Drawing::Point(9, 37);
			this->panelserv->Margin = System::Windows::Forms::Padding(2);
			this->panelserv->Name = L"panelserv";
			this->panelserv->Size = System::Drawing::Size(821, 394);
			this->panelserv->TabIndex = 15;
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 3;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33334F)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33334F)));
			this->tableLayoutPanel4->Controls->Add(this->splitContainer2, 1, 0);
			this->tableLayoutPanel4->Controls->Add(this->splitContainer1, 0, 0);
			this->tableLayoutPanel4->Location = System::Drawing::Point(2, 2);
			this->tableLayoutPanel4->Margin = System::Windows::Forms::Padding(2);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 3;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(816, 390);
			this->tableLayoutPanel4->TabIndex = 0;
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer2->Location = System::Drawing::Point(273, 2);
			this->splitContainer2->Margin = System::Windows::Forms::Padding(2);
			this->splitContainer2->Name = L"splitContainer2";
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->radioButton1);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->tabControl1);
			this->splitContainer2->Size = System::Drawing::Size(268, 126);
			this->splitContainer2->SplitterDistance = 32;
			this->splitContainer2->SplitterWidth = 3;
			this->splitContainer2->TabIndex = 3;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Dock = System::Windows::Forms::DockStyle::Right;
			this->radioButton1->Location = System::Drawing::Point(18, 0);
			this->radioButton1->Margin = System::Windows::Forms::Padding(2);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(14, 126);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Tag = L"radio2";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Margin = System::Windows::Forms::Padding(2);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(233, 126);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->label_serv_capacit2);
			this->tabPage1->Controls->Add(this->label_serv_ver2);
			this->tabPage1->Controls->Add(this->label_serv_status2);
			this->tabPage1->Controls->Add(this->label_serv_name2);
			this->tabPage1->Controls->Add(this->progressBar2);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Margin = System::Windows::Forms::Padding(2);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(2);
			this->tabPage1->Size = System::Drawing::Size(225, 100);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Server info";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// label_serv_capacit2
			// 
			this->label_serv_capacit2->AutoSize = true;
			this->label_serv_capacit2->Dock = System::Windows::Forms::DockStyle::Top;
			this->label_serv_capacit2->Location = System::Drawing::Point(2, 46);
			this->label_serv_capacit2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_serv_capacit2->Name = L"label_serv_capacit2";
			this->label_serv_capacit2->Size = System::Drawing::Size(38, 13);
			this->label_serv_capacit2->TabIndex = 4;
			this->label_serv_capacit2->Text = L"NONE";
			// 
			// label_serv_ver2
			// 
			this->label_serv_ver2->AutoSize = true;
			this->label_serv_ver2->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->label_serv_ver2->Location = System::Drawing::Point(2, 85);
			this->label_serv_ver2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_serv_ver2->Name = L"label_serv_ver2";
			this->label_serv_ver2->Size = System::Drawing::Size(38, 13);
			this->label_serv_ver2->TabIndex = 3;
			this->label_serv_ver2->Text = L"NONE";
			// 
			// label_serv_status2
			// 
			this->label_serv_status2->AutoSize = true;
			this->label_serv_status2->Dock = System::Windows::Forms::DockStyle::Top;
			this->label_serv_status2->Location = System::Drawing::Point(2, 33);
			this->label_serv_status2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_serv_status2->Name = L"label_serv_status2";
			this->label_serv_status2->Size = System::Drawing::Size(38, 13);
			this->label_serv_status2->TabIndex = 2;
			this->label_serv_status2->Text = L"NONE";
			// 
			// label_serv_name2
			// 
			this->label_serv_name2->AutoSize = true;
			this->label_serv_name2->Dock = System::Windows::Forms::DockStyle::Top;
			this->label_serv_name2->Location = System::Drawing::Point(2, 20);
			this->label_serv_name2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_serv_name2->Name = L"label_serv_name2";
			this->label_serv_name2->Size = System::Drawing::Size(38, 13);
			this->label_serv_name2->TabIndex = 1;
			this->label_serv_name2->Text = L"NONE";
			// 
			// progressBar2
			// 
			this->progressBar2->Dock = System::Windows::Forms::DockStyle::Top;
			this->progressBar2->Location = System::Drawing::Point(2, 2);
			this->progressBar2->Margin = System::Windows::Forms::Padding(2);
			this->progressBar2->Name = L"progressBar2";
			this->progressBar2->Size = System::Drawing::Size(221, 18);
			this->progressBar2->TabIndex = 0;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->richTextBox2);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Margin = System::Windows::Forms::Padding(2);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(2);
			this->tabPage2->Size = System::Drawing::Size(225, 100);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Server description";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// richTextBox2
			// 
			this->richTextBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBox2->Location = System::Drawing::Point(2, 2);
			this->richTextBox2->Margin = System::Windows::Forms::Padding(2);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->ReadOnly = true;
			this->richTextBox2->Size = System::Drawing::Size(221, 96);
			this->richTextBox2->TabIndex = 0;
			this->richTextBox2->Text = L"";
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(2, 2);
			this->splitContainer1->Margin = System::Windows::Forms::Padding(2);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->radioButton_sev_select);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->tabControl_serv);
			this->splitContainer1->Size = System::Drawing::Size(267, 126);
			this->splitContainer1->SplitterDistance = 32;
			this->splitContainer1->SplitterWidth = 3;
			this->splitContainer1->TabIndex = 3;
			// 
			// radioButton_sev_select
			// 
			this->radioButton_sev_select->AutoSize = true;
			this->radioButton_sev_select->Dock = System::Windows::Forms::DockStyle::Right;
			this->radioButton_sev_select->Location = System::Drawing::Point(18, 0);
			this->radioButton_sev_select->Margin = System::Windows::Forms::Padding(2);
			this->radioButton_sev_select->Name = L"radioButton_sev_select";
			this->radioButton_sev_select->Size = System::Drawing::Size(14, 126);
			this->radioButton_sev_select->TabIndex = 0;
			this->radioButton_sev_select->TabStop = true;
			this->radioButton_sev_select->Tag = L"radio1";
			this->radioButton_sev_select->UseVisualStyleBackColor = true;
			// 
			// tabControl_serv
			// 
			this->tabControl_serv->Controls->Add(this->tabPage_serv_info);
			this->tabControl_serv->Controls->Add(this->tabPage_serv_description);
			this->tabControl_serv->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl_serv->Location = System::Drawing::Point(0, 0);
			this->tabControl_serv->Margin = System::Windows::Forms::Padding(2);
			this->tabControl_serv->Name = L"tabControl_serv";
			this->tabControl_serv->SelectedIndex = 0;
			this->tabControl_serv->Size = System::Drawing::Size(232, 126);
			this->tabControl_serv->TabIndex = 0;
			// 
			// tabPage_serv_info
			// 
			this->tabPage_serv_info->Controls->Add(this->label_serv_capacit);
			this->tabPage_serv_info->Controls->Add(this->label_serv_ver);
			this->tabPage_serv_info->Controls->Add(this->label_serv_status);
			this->tabPage_serv_info->Controls->Add(this->label_serv_name);
			this->tabPage_serv_info->Controls->Add(this->progressBar_serv_capacity);
			this->tabPage_serv_info->Location = System::Drawing::Point(4, 22);
			this->tabPage_serv_info->Margin = System::Windows::Forms::Padding(2);
			this->tabPage_serv_info->Name = L"tabPage_serv_info";
			this->tabPage_serv_info->Padding = System::Windows::Forms::Padding(2);
			this->tabPage_serv_info->Size = System::Drawing::Size(224, 100);
			this->tabPage_serv_info->TabIndex = 0;
			this->tabPage_serv_info->Text = L"Server info";
			this->tabPage_serv_info->UseVisualStyleBackColor = true;
			// 
			// label_serv_capacit
			// 
			this->label_serv_capacit->AutoSize = true;
			this->label_serv_capacit->Dock = System::Windows::Forms::DockStyle::Top;
			this->label_serv_capacit->Location = System::Drawing::Point(2, 46);
			this->label_serv_capacit->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_serv_capacit->Name = L"label_serv_capacit";
			this->label_serv_capacit->Size = System::Drawing::Size(38, 13);
			this->label_serv_capacit->TabIndex = 4;
			this->label_serv_capacit->Text = L"NONE";
			// 
			// label_serv_ver
			// 
			this->label_serv_ver->AutoSize = true;
			this->label_serv_ver->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->label_serv_ver->Location = System::Drawing::Point(2, 85);
			this->label_serv_ver->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_serv_ver->Name = L"label_serv_ver";
			this->label_serv_ver->Size = System::Drawing::Size(38, 13);
			this->label_serv_ver->TabIndex = 3;
			this->label_serv_ver->Text = L"NONE";
			// 
			// label_serv_status
			// 
			this->label_serv_status->AutoSize = true;
			this->label_serv_status->Dock = System::Windows::Forms::DockStyle::Top;
			this->label_serv_status->Location = System::Drawing::Point(2, 33);
			this->label_serv_status->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_serv_status->Name = L"label_serv_status";
			this->label_serv_status->Size = System::Drawing::Size(38, 13);
			this->label_serv_status->TabIndex = 2;
			this->label_serv_status->Text = L"NONE";
			// 
			// label_serv_name
			// 
			this->label_serv_name->AutoSize = true;
			this->label_serv_name->Dock = System::Windows::Forms::DockStyle::Top;
			this->label_serv_name->Location = System::Drawing::Point(2, 20);
			this->label_serv_name->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_serv_name->Name = L"label_serv_name";
			this->label_serv_name->Size = System::Drawing::Size(38, 13);
			this->label_serv_name->TabIndex = 1;
			this->label_serv_name->Text = L"NONE";
			// 
			// progressBar_serv_capacity
			// 
			this->progressBar_serv_capacity->Dock = System::Windows::Forms::DockStyle::Top;
			this->progressBar_serv_capacity->Location = System::Drawing::Point(2, 2);
			this->progressBar_serv_capacity->Margin = System::Windows::Forms::Padding(2);
			this->progressBar_serv_capacity->Name = L"progressBar_serv_capacity";
			this->progressBar_serv_capacity->Size = System::Drawing::Size(220, 18);
			this->progressBar_serv_capacity->TabIndex = 0;
			// 
			// tabPage_serv_description
			// 
			this->tabPage_serv_description->Controls->Add(this->richTextBox1);
			this->tabPage_serv_description->Location = System::Drawing::Point(4, 22);
			this->tabPage_serv_description->Margin = System::Windows::Forms::Padding(2);
			this->tabPage_serv_description->Name = L"tabPage_serv_description";
			this->tabPage_serv_description->Padding = System::Windows::Forms::Padding(2);
			this->tabPage_serv_description->Size = System::Drawing::Size(224, 100);
			this->tabPage_serv_description->TabIndex = 1;
			this->tabPage_serv_description->Text = L"Server description";
			this->tabPage_serv_description->UseVisualStyleBackColor = true;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBox1->Location = System::Drawing::Point(2, 2);
			this->richTextBox1->Margin = System::Windows::Forms::Padding(2);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(220, 96);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(841, 447);
			this->Controls->Add(this->panel_main);
			this->Margin = System::Windows::Forms::Padding(2);
			this->MaximumSize = System::Drawing::Size(858, 486);
			this->MinimumSize = System::Drawing::Size(362, 486);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SomLaucher";
			this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->panel_main->ResumeLayout(false);
			this->panelmainwitout->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_logo))->EndInit();
			this->panel3->ResumeLayout(false);
			this->panel7->ResumeLayout(false);
			this->panel7->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->tableLayoutPanel_menu->ResumeLayout(false);
			this->panel_account->ResumeLayout(false);
			this->panel_account->PerformLayout();
			this->panelserv->ResumeLayout(false);
			this->tableLayoutPanel4->ResumeLayout(false);
			this->splitContainer2->Panel1->ResumeLayout(false);
			this->splitContainer2->Panel1->PerformLayout();
			this->splitContainer2->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->EndInit();
			this->splitContainer2->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->tabControl_serv->ResumeLayout(false);
			this->tabPage_serv_info->ResumeLayout(false);
			this->tabPage_serv_info->PerformLayout();
			this->tabPage_serv_description->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion


	private:
		//SomLauncherMainWin::ChangeServerForm^ form_serv = gcnew SomLauncherMainWin::ChangeServerForm();

	private:
		
		System::String^ minecraft_core_dir_path = System::String(JoinA({ getenv("APPDATA"), ".SomSomSom" })).ToString();
		System::String^ config_path = System::String::Join("\\", minecraft_core_dir_path, "SOMCONFIG.json");
		System::String^ launcher_name = L"SomLauncher";
		System::String^ launcher_version = L"2.0";
		System::String^ username = nullptr;
		System::String^ servers_json = System::String::Join("\\", minecraft_core_dir_path, "SERVERS.json" );

	private:
		bool win_is_small = true;
		bool expect_table_menu = false;
		bool is_down_table_menu = true;
		int server;

	private:
		void animationtoppanel(bool expect, int anim);
		void create_form_changeserv();

		void start_minecraft_params();
		void install_run_minecraft(System::String^ version, System::String^ loader_mame, System::String^ loader_version, System::String^ java, System::String^ mcdir, MCCL::Option::MinecraftOptions options);


private: System::Void test_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void panel_toppanel_hover_MouseEnter(System::Object^ sender, System::EventArgs^ e);
private: System::Void panel_toppanel_hover_MouseLeave(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_servers_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_game_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_game_MouseEnter(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_game_MouseLeave(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_play_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_changeserv_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void label_botton_profile_Click(System::Object^ sender, System::EventArgs^ e);
};
}


#endif // MAINFORM_H_