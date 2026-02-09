
// =================================
// Plugin Exports -- see exports.def
// =================================

#include <shlobj.h>

// F4SE
#include "f4se/PluginAPI.h" // for plugin registration callback functions

#include "main.h"           // for plugin name and version
#include "functions.h"      // for plugin papyrus functions

IDebugLog gLog;

const char* PluginVersion()
{
	return PLUGIN_VERSION_STRING; // from main.h
}

const char* GameVersion()
{
	return GAME_VERSION_STRING; // from main.h
}

const char* RuntimeVersion()
{
	return RUNTIME_VERSION_STRING; // from main.h
}

// F4SE Plugin Query - Called when the plugin is queried
extern "C" bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* info)
{
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE_PATH);

	_MESSAGE("%s Query v%s", PLUGIN_NAME_SHORT, PLUGIN_VERSION_STRING);

	// populate info structure
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = PLUGIN_NAME_LONG;		// set in config.h
	info->version = PLUGIN_VERSION;		// set in config.h

	// check for compatible versions
	if (!COMPATIBLE(f4se->runtimeVersion))
	{
		return false;
	}

	// supported runtime version
	return true;
}

// F4SE Plugin Load - Called when the plugin loads everytime
extern "C" bool F4SEPlugin_Load(const F4SEInterface* f4se)
{
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE_PATH);

	_MESSAGE("%s Load v%s", PLUGIN_NAME_SHORT, PLUGIN_VERSION_STRING);

	// check for compatible versions
	if (f4se->isEditor || !COMPATIBLE(f4se->runtimeVersion))
	{
		return false;
	}
		
	// try to get the papyrus interface or disable if it's unable
	F4SEPapyrusInterface* papyrus = (F4SEPapyrusInterface*)f4se->QueryInterface(kInterface_Papyrus);
	if (!papyrus)
	{
		return false;
	}

	// register papyrus functions
	return papyrus->Register(Papyrus::RegisterFunctions);
}
