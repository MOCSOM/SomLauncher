#include "ChangeServerForm.h"

System::String^ SomLauncherMainWin::ChangeServerForm::get_value_serv()
{
    return server;
}

System::Void SomLauncherMainWin::ChangeServerForm::ChangeServerForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
    this->checkedListBox_changeserv->Items->Clear();
    Json::JsonParcer json_serv;
    auto json_parce = json_serv.ParseFile("SERVERS.json");
    auto parce_config = json_serv.ParseFile(this->config_path);

    for (int i = 0; i < json_parce["servers"]->get_count(); ++i)
    {
        this->checkedListBox_changeserv->Items->Add(json_parce["servers"][i]["name"]->to_string(), false);
    }

    if (this->checkedListBox_changeserv->CheckedItems->ToString() == "")
    {
        this->button_apply->Enabled = false;
    }
    else
    {
        this->button_apply->Enabled = true;
    }

    //this->checkedListBox_changeserv->SetSelected(parce_config["user"]["server"]->to_int(), true);
    this->checkedListBox_changeserv->SetItemChecked(parce_config["user"]["server"]->to_int(), true);
}

System::Void SomLauncherMainWin::ChangeServerForm::checkedListBox_changeserv_ItemCheck(System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e)
{
    //if (e->NewValue == System::Windows::Forms::CheckState::Checked)
    //{
    //    for (int Count = 0; Count < this->checkedListBox_changeserv->Items->Count; Count++)
    //    {
    //        if (this->checkedListBox_changeserv->GetItemChecked(Count))
    //            System::Console::WriteLine(this->checkedListBox_changeserv->GetItemText(this->checkedListBox_changeserv->Items[Count]));
    //    }
    //}
    //else
    //{

    //}
    //System::Console::WriteLine(e->NewValue.ToString());
    //int count = this->checkedListBox_changeserv->CheckedItems->Count;
    
}
 
System::Void SomLauncherMainWin::ChangeServerForm::checkedListBox_changeserv_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
    /* Превращение в radio bottom */
    int index = this->checkedListBox_changeserv->SelectedIndex;
    int count = this->checkedListBox_changeserv->Items->Count;
    for (int i = 0; i < count; i++)
    {
        if (index != i)
        {
            this->checkedListBox_changeserv->SetItemChecked(i, false);
        }
    }
    if (this->checkedListBox_changeserv->CheckedItems->Count != 0)
    {
        System::Console::WriteLine(this->checkedListBox_changeserv->CheckedItems[0]);
        server = this->checkedListBox_changeserv->CheckedItems[0]->ToString();
        this->button_apply->Enabled = true;
    }
    else
    {
        server = "";
        this->button_apply->Enabled = false;
    }
}

System::Void SomLauncherMainWin::ChangeServerForm::button_cancel_Click(System::Object^ sender, System::EventArgs^ e)
{
    this->~ChangeServerForm();
}

System::Void SomLauncherMainWin::ChangeServerForm::button_apply_Click(System::Object^ sender, System::EventArgs^ e)
{
    // TODO: Вставить функцию из Json.h которая сохраняет в файл

    Json::JsonParcer json_config;
    auto config_parce = json_config.ParseFile(config_path);
    config_parce["user"]["server"]->operator=(this->checkedListBox_changeserv->CheckedIndices[0]);
    
    System::Console::Write("Server is: ");
    System::Console::WriteLine(config_parce["user"]["server"]->to_string());

    config_parce->SaveJsonToFile(config_path, 4);

    //System::IO::File::WriteAllText(config_path, config_parce->to_string());

    System::Console::WriteLine("Server saved");
}
