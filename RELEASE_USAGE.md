# FO4StringUtils Releases

## Organization
- Folders are organized by game edition: <F4SE-Version>-<FO4-Version>-<FO4-Edition>
- Beneath that are FO4StringUtils release versions for that game edition: X.Y

## Installation

Choose your version: Make sure you pick the release that matches your game edition:
- GOTY → 0.6.23-1.10.163-GOTY
- NextGen → 0.7.2-1.10.984-NextGen
- Anniversary → 0.7.7-1.11.191-Anniversary

Copy the Data folder: Take the Data/ folder from the release you want and merge it into your Fallout 4 game directory’s Data/ folder.

Enable the ESP/Plugin:
- Open your mod manager or Fallout 4 launcher.
- Make sure the corresponding FO4StringUtils_*.dll plugin and the .esp (if using a test harness) are activated.
- Verify Papyrus scripts: The .pex files are precompiled; the .psc source is included for reference or debugging in the Scripts/Source/User/ path. You don’t need to compile them yourself for normal use.
- Launch the game: The functions are now available to Papyrus scripts in your mods.

## Notes
- Follow the installation structions above carefully.
- Each release folder is fully self-contained for its version of the game/F4SE.
- The .7z archive is included if you prefer to download or backup a single file.

## Folder Structure

FO4StringUtils/
└── Releases/
    ├── 0.6.23-1.10.163-GOTY/
    │   └── 1.0/
    │       ├── Data/
    │       │   ├── F4SE/
    │       │   │   └── Plugins/
    │       │   │       └── FO4StringUtils_1_0.dll
    │       │   └── Scripts/
    │       │       ├── FO4StringUtils.pex
    │       │       └── Source/
    │       │           └── User/
    │       │               └── FO4StringUtils.psc
    │       └── FO4StringUtils-v1.0.7z
    │
    ├── 0.7.2-1.10.984-NextGen/
    │   └── 2.0/
    │       ├── Data/
    │       │   ├── F4SE/
    │       │   │   └── Plugins/
    │       │   │       └── FO4StringUtils_2_0.dll
    │       │   └── Scripts/
    │       │       ├── FO4StringUtils.pex
    │       │       └── Source/
    │       │           └── User/
    │       │               └── FO4StringUtils.psc
    │       └── FO4StringUtils-v2.0.7z
    │
    └── 0.7.7-1.11.191-Anniversary/
        └── 4.0/
            ├── Data/
            │   ├── F4SE/
            │   │   └── Plugins/
            │   │       └── FO4StringUtils_4_0.dll
            │   └── Scripts/
            │       ├── FO4StringUtils.pex
            │       └── Source/
            │           └── User/
            │               └── FO4StringUtils.psc
            └── FO4StringUtils-v4.0.7z
