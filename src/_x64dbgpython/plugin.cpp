#include "plugin.h"


// Examples: https://github.com/x64dbg/x64dbg/wiki/Plugins
// References:
// - https://help.x64dbg.com/en/latest/developers/plugins/index.html
// - https://x64dbg.com/blog/2016/10/04/architecture-of-x64dbg.html
// - https://x64dbg.com/blog/2016/10/20/threading-model.html
// - https://x64dbg.com/blog/2016/07/30/x64dbg-plugin-sdk.html

static std::wstring makeX64dbgPackageDir(const std::wstring& directory)
{
    auto dir = directory;
    if (dir[dir.length() - 1] != L'\\')
        dir.push_back(L'\\');
    dir.append(L"Lib\\site-packages");
    return dir;
}

static bool isValidPythonHome(const wchar_t* directory)
{
    if (!directory || !*directory)
        return false;
    auto attr = GetFileAttributesW(makeX64dbgPackageDir(directory).c_str());
    if (attr == INVALID_FILE_ATTRIBUTES)
        return false;
    return (attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY;
}

static std::wstring Utf8ToUtf16(const std::string& str)
{
    if (str.empty())
        return L"";

    int size_needed = MultiByteToWideChar(
        CP_UTF8, 0,
        str.data(), (int)str.size(),
        nullptr, 0
    );

    std::wstring result(size_needed, 0);

    MultiByteToWideChar(
        CP_UTF8, 0,
        str.data(), (int)str.size(),
        &result[0], size_needed
    );

    return result;
}

std::string Utf16ToUtf8(const std::wstring& wstr)
{
    if (wstr.empty()) return {};

    int size_needed = WideCharToMultiByte(
        CP_UTF8, 0,
        wstr.c_str(), (int)wstr.size(),
        nullptr, 0, nullptr, nullptr
    );

    std::string result(size_needed, 0);

    WideCharToMultiByte(
        CP_UTF8, 0,
        wstr.c_str(), (int)wstr.size(),
        &result[0], size_needed,
        nullptr, nullptr
    );

    return result;
}

static bool findX64dbgPythonHome(std::wstring& pythonHome)
{
    // Get from configuration
    std::array<char, MAX_SETTING_SIZE> setting{};

    if (BridgeSettingGet("x64dbgpython", "PythonHome", setting.data()))
    {
        pythonHome = Utf8ToUtf16(setting.data());

        if (isValidPythonHome(pythonHome.c_str()))
        {
            dprintf("Found valid PythonHome in x64dbg.ini file!\n");
            dprintf("PythonHome=%s\n", setting.data());
            return true;
        }

        dprintf(
            "Found invalid PythonHome setting \"%s\"... in x64dbg.ini file!\n",
            setting.data()
        );
    }

    return false;
}




// Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    //dprintf("pluginInit(pluginHandle: %d)\n", pluginHandle);

        
    std::wstring pythonHome;
    if(!findX64dbgPythonHome(pythonHome))
    {        
        BridgeSettingSet("x64dbgpython", "PythonHome", "Set PythonHome in x64dbg.ini");       
        return false;
    }


	std::string pythonHomeUtf8 = Utf16ToUtf8(pythonHome);

    if(AddDllDirectory(pythonHome.c_str()) != 0)
    {
        dprintf("PythonHome=%s added to x64dbg binary directories\n", pythonHomeUtf8.c_str());
    }
    else
    {
        dprintf("Failed to add PythonHome=%s to x64dbg binary directories\n", pythonHomeUtf8.c_str());
    }

    // Prefix of the functions to call here: _plugin_register
    //_plugin_registercommand(pluginHandle, PLUGIN_NAME, cbExampleCommand, true);

    // Return false to cancel loading the plugin.
    return true;
}

// Deinitialize your plugin data here.
// NOTE: you are responsible for gracefully closing your GUI
// This function is not executed on the GUI thread, so you might need
// to use WaitForSingleObject or similar to wait for everything to close.
void pluginStop()
{
    // Prefix of the functions to call here: _plugin_unregister

    //dprintf("pluginStop(pluginHandle: %d)\n", pluginHandle);
}

// Do GUI/Menu related things here.
// This code runs on the GUI thread: GetCurrentThreadId() == GuiGetMainThreadId()
// You can get the HWND using GuiGetWindowHandle()
void pluginSetup()
{
    // Prefix of the functions to call here: _plugin_menu

    //dprintf("pluginSetup(pluginHandle: %d)\n", pluginHandle);
}