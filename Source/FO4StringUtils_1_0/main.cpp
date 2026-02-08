
// =================================
// Plugin Exports -- see exports.def
// =================================

// F4SE
#include "f4se/PluginAPI.h"		// for plugin registration callback functions

#include "main.h"				// for plugin name and version
#include "functions.h"			// for plugin papyrus functions

// F4SE Plugin Query - Called when the plugin is queried
extern "C" bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* info)
{
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
