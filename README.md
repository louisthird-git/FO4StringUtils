# FO4StringUtils

Native F4SE plugin providing additional string utilities to Papyrus.

- /Release – Prebuilt plugin binaries for each Fallout 4 version (see RELEASE_USAGE.md)
- /Source  – C++ source and Visual Studio projects (see SOURCE_USAGE.md)
- /Test    – Papyrus test mod and scripts (see TEST_USAGE.md)

## Supported Fallout 4 Versions

- 1.0 → 1.10.163 (GOTY) → FO4StringUtils_1_0
- 2.0 → 1.10.984 (Next-Gen) → FO4StringUtils_2_0
- 4.0 → 1.11.191 (Anniversary) → FO4StringUtils_4_0

## Installation (for Users)

1. Install the correct version of F4SE for your Fallout 4 runtime.
2. Copy the DLL from the appropriate folder into:

   Data\F4SE\Plugins\

3. Copy the `Scripts` folder into:

   Data\Scripts\

   (or merge with your existing Scripts folder)

Only install one version of the DLL matching your game edition runtime.

## Using FO4StringUtils in Papyrus (for Mod Authors)

Add the script as an import:

```papyrus
ScriptName MyScript extends Quest

Import FO4StringUtils

Event OnQuestInit()
   String result = FO4StringUtils.ToUpper("hello world")
   Debug.Notification(result)
EndEvent
```

