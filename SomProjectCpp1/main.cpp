#include "MainForm.h"
#include <Windows.h>
//#include "Json.h"
//#include "DownloadClasses.h"
#include "Minecraftus.h"
//#include "CallbackDict.h"


int main() {

	/*Json::JsonParcer json_parcer;
	auto data = json_parcer.ParseFile("DATA.json");

	System::Console::WriteLine(data->get_count());

	

	data->SaveJsonToFile("DATA2.json", 4);

	System::Console::Read();*/

	/*wchar_t* a = NULL;

	System::Console::WriteLine(System::String(StrDogW(a, L"dadads")).ToString());
	System::Console::Read();*/

	//MCCL::Option::MinecraftOptions options;
	//options.customResolution = false;
	//options.gameDirectory = JoinA({ getenv("APPDATA"), ".SomSomSom" });
	//options.launcherName = L"1";
	//options.launcherVersion = L"1";
	//options.username = L"lox";
	//options.jvmArguments = StrDogW(L"-Xms1024M -Xmx", StrDogW(L"8000", L"M"));
	//options.executablePath = JoinA({ getenv("APPDATA"), ".SomSomSom", "jdk8u372-b07", "bin", "java.exe"});
	//options.uuid = L"uuu";
	//options.token = L"uuu";

	///* minecraft_version = 1.12.2 + "-" + forge_version = 14.23.5.2860 */
	//wchar_t* launch_varsion = L"1.12.2";

	////DDIC::DownloadDeleteClass dd;
	////MCCL::install_minecraft_version(L"1.12.2", options.gameDirectory);
	//MCCL::Forge::install_forge_version(L"1.12.2-14.23.5.2860", options.gameDirectory);
	//wchar_t* command = MCCL::get_minecraft_command__(launch_varsion, options.gameDirectory, options);
	//System::Console::WriteLine(System::String(command).ToString());
	//MCCL::start_minecraft(L"", command);

	//CallbackDict ad;
	//DDIC::Download::Files::download_file(L"https://launchermeta.mojang.com/v1/products/java-runtime/2ec0cc96c44e5a76b9c8b7c39df7210883d12871/all.json", NULL, ad);

	//System::Console::Read();


	using namespace SomLauncherMainWin;
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	System::Windows::Forms::Application::Run(gcnew MainForm);
	return 0;
}