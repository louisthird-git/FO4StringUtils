#pragma once

// ====================
// Plugin Configuration
// ====================

// F4SE
#include "f4se_common/f4se_version.h" // for CURRENT_RELEASE_RUNTIME -- see for f4se versions

#define PLUGIN_AUTHOR                 "louisthird"
#define PLUGIN_VERSION                1
#define PLUGIN_VERSION_STRING         "1.0.0"
#define PLUGIN_NAME_SHORT             "FO4StringUtils"
#define PLUGIN_NAME_LONG              "Fallout 4 String Utilities"
#define SUPPORTED_RUNTIME_VERSION     CURRENT_RELEASE_RUNTIME
#define MINIMUM_RUNTIME_VERSION       SUPPORTED_RUNTIME_VERSION
#define COMPATIBLE(runtimeVersion)    (runtimeVersion == SUPPORTED_RUNTIME_VERSION)

// BUILD NOTES:
//
// Modified ScaleformValue.h to comment out an overload where GFxValue(int v) essentially duplicated GFxValue(SInt32 v) 
// Modified PapyrusStruct.h to add #include <map> as std::map was used but not included
//
// Build required these F4SE C++ files to be added to plugin project:
// GameAPI.cpp
// GameExtraData.cpp
// GameTypes.cpp
// GameUtilities.cpp
// PapyrusArgs.cpp
// PapyrusInterfaces.cpp
// PapyrusValue.cpp
// PapyrusVM.cpp
