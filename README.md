# FO4StringUtils

Native F4SE plugin providing additional string utilities to Papyrus.

- /Dist   – Prebuilt plugin binaries for each Fallout 4 version (see DIST_USAGE.md)
- /Source – C++ source and Visual Studio projects (see SOURCE_USAGE.md)
- /Test   – Papyrus test mod and scripts (see TEST_USAGE.md)

## Supported Fallout 4 Versions

- 1.10.163 (GOTY) → Dist/0.6.23-1.10.163-GOTY
- 1.10.984 (Next-Gen) → Dist/0.7.2-1.10.984-NextGen
- 1.11.191 (Anniversary) → Dist/0.7.7-1.11.191-Anniversary

## Installation (for Users)

1. Install the correct version of F4SE for your Fallout 4 runtime.
2. Copy the FO4StringUtils DLL from the appropriate folder into:

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
   String result = FO4StringUtils.Replace("Radroach Meat", "Radroach", "Bloatfly")
   Debug.Notification(result)  ; "Bloatfly Meat"
EndEvent
```

