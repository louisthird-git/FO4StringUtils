#pragma once

// ====================
// Plugin Configuration
// ====================

// F4SE
#include "f4se_common/f4se_version.h" // for CURRENT_RELEASE_RUNTIME -- see for f4se versions

#define PLUGIN_AUTHOR                 "louisthird"
#define PLUGIN_VERSION                4
#define PLUGIN_VERSION_STRING         "4.0.0"
#define PLUGIN_NAME_SHORT             "FO4StringUtils"
#define PLUGIN_NAME_LONG              "Fallout 4 String Utilities"
#define SUPPORTED_RUNTIME_VERSION     CURRENT_RELEASE_RUNTIME
#define MINIMUM_RUNTIME_VERSION       SUPPORTED_RUNTIME_VERSION
#define COMPATIBLE(runtimeVersion)    (runtimeVersion == SUPPORTED_RUNTIME_VERSION)
#define PLUGIN_LOG_FILE_PATH          "\\My Games\\Fallout4\\F4SE\\FO4StringUtils.log"

// BUILD NOTES:
//
// PapyrusArgs.h: Needed to move GetTypeID template declaration so it is visible before first use
//
// Build required these F4SE C++ files to be added to plugin project under f4se_files:
// GameAPI.cpp
// GameExtraData.cpp
// GameTypes.cpp
// GameUtilities.cpp
// PapyrusArgs.cpp
// PapyrusInterfaces.cpp
// PapyrusValue.cpp
// PapyrusVM.cpp
