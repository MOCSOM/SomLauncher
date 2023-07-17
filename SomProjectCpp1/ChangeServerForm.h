#ifndef CHANGESERVFORM_H_     // equivalently, #if !defined HEADER_H_
#define CHANGESERVFORM_H_

#include "Json.h"

namespace SomLauncherMainWin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для ChangeServerForm
	/// </summary>
	public ref class ChangeServerForm : public System::Windows::Forms::Form
	{
	public:
		ChangeServerForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		ChangeServerForm(System::String^ config_path) : config_path(config_path)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}


	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~ChangeServerForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckedListBox^ checkedListBox_changeserv;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::Button^ button_apply;

	private: System::Windows::Forms::Button^ button_cancel;

	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->checkedListBox_changeserv = (gcnew System::Windows::Forms::CheckedListBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button_apply = (gcnew System::Windows::Forms::Button());
			this->button_cancel = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// checkedListBox_changeserv
			// 
			this->checkedListBox_changeserv->CheckOnClick = true;
			this->checkedListBox_changeserv->Dock = System::Windows::Forms::DockStyle::Top;
			this->checkedListBox_changeserv->FormattingEnabled = true;
			this->checkedListBox_changeserv->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"foo1", L"foo2", L"foo3" });
			this->checkedListBox_changeserv->Location = System::Drawing::Point(0, 0);
			this->checkedListBox_changeserv->Name = L"checkedListBox_changeserv";
			this->checkedListBox_changeserv->Size = System::Drawing::Size(412, 378);
			this->checkedListBox_changeserv->TabIndex = 0;
			this->checkedListBox_changeserv->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &ChangeServerForm::checkedListBox_changeserv_ItemCheck);
			this->checkedListBox_changeserv->SelectedIndexChanged += gcnew System::EventHandler(this, &ChangeServerForm::checkedListBox_changeserv_SelectedIndexChanged);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 4;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->Controls->Add(this->button_apply, 3, 0);
			this->tableLayoutPanel1->Controls->Add(this->button_cancel, 2, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 378);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(412, 62);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// button_apply
			// 
			this->button_apply->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button_apply->Location = System::Drawing::Point(334, 3);
			this->button_apply->Name = L"button_apply";
			this->button_apply->Size = System::Drawing::Size(75, 56);
			this->button_apply->TabIndex = 1;
			this->button_apply->Text = L"Apply";
			this->button_apply->UseVisualStyleBackColor = true;
			this->button_apply->Click += gcnew System::EventHandler(this, &ChangeServerForm::button_apply_Click);
			// 
			// button_cancel
			// 
			this->button_cancel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button_cancel->Location = System::Drawing::Point(253, 3);
			this->button_cancel->Name = L"button_cancel";
			this->button_cancel->Size = System::Drawing::Size(75, 56);
			this->button_cancel->TabIndex = 0;
			this->button_cancel->Text = L"Cancel";
			this->button_cancel->UseVisualStyleBackColor = true;
			this->button_cancel->Click += gcnew System::EventHandler(this, &ChangeServerForm::button_cancel_Click);
			// 
			// ChangeServerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(412, 440);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->checkedListBox_changeserv);
			this->Name = L"ChangeServerForm";
			this->Text = L"ChangeServerForm";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ChangeServerForm::ChangeServerForm_Paint);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		//System::Collections::ArrayList^ server_list = gcnew System::Collections::ArrayList();
		System::String^ server = "";
		System::String^ config_path;

	public:
		System::String^ get_value_serv();

	private: System::Void ChangeServerForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	private: System::Void checkedListBox_changeserv_ItemCheck(System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e);
	private: System::Void checkedListBox_changeserv_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_cancel_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_apply_Click(System::Object^ sender, System::EventArgs^ e);
};
}


#endif /*CHANGESERVFORM_H_*/