# FO4StringUtils Test Harness — How to Test

This document explains how to set up and run the FO4StringUtils test harness to verify all native functions work correctly in your installation of Fallout 4 / F4SE.

1. Requirements
- Fallout 4 installed (any supported version: GOTY, NextGen, Anniversary)
- F4SE matching your Fallout 4 version
- FO4StringUtils plugin DLLs built for your version (FO4StringUtils_1_0.dll, FO4StringUtils_2_0.dll, FO4StringUtils_4_0.dll)
- Test harness ESP: FO4StringUtils_Test.esp
- Papyrus scripts: all scripts located in Scripts/Source/User
- Note: Scripts must be in the same structure as the game expects, e.g. Data\Scripts\Source\User\FO4StringUtils_TestScript.psc.

2. Installation
- Copy the plugin DLL for your version to: Fallout 4\Data\F4SE\Plugins\
- Copy the test ESP to: Fallout 4\Data\
- Copy the Papyrus scripts to: Fallout 4\Data\Scripts\Source\User\
- Launch Fallout 4 with F4SE.
- The test harness ESP depends on F4SE being loaded.

3. Compiling the Test

The test harness Papyrus .psc source file should not need to be compiled as the included Papyrus .pex executable file can be used.  If compilation is necessary, then the following command can be used:

```
$ "C:\Program Files (x86)\Steam\steamapps\common\Fallout 4\Papyrus Compiler\PapyrusCompiler.exe" "C:\Program Files (x86)\Steam\steamapps\common\Fallout 4\Data\Scripts\Source\User\FO4StringUtils_TestScript.psc" -f="C:\Program Files (x86)\Steam\steamapps\common\Fallout 4\Data\Scripts\Source\Base\Institute_Papyrus_Flags.flg" -i="C:\Program Files (x86)\Steam\steamapps\common\Fallout 4\Data\Scripts\Source" -i="C:\Program Files (x86)\Steam\steamapps\common\Fallout 4\Data\Scripts\Source\Base" -op -r -final
Papyrus Compiler Version 2.8.0.4 for Fallout 4
Copyright (C) ZeniMax Media. All rights reserved.
Starting 1 compile threads for 1 files...
Compiling "C:\Program Files (x86)\Steam\steamapps\common\Fallout 4\Data\Scripts\Source\User\FO4StringUtils_TestScript.psc"...
Compilation succeeded.

Batch compile of 1 files finished. 1 succeeded, 0 failed.
```

4. Running the Test
- Start the game and load a save.
- Open the console (~) and type:
- Run: startquest FO4StringUtils_Test
- The quest will automatically trigger OnQuestInit() and run the full test suite.

Output:
- Assertions are printed to the Papyrus log (look for Passed or Failed).
- At the end of the test, a log reports: FO4StringUtils Passed: ### Failed: ### Total: ###
- This shows a summary of all tests run during initialization.

5. What Is Tested

The test harness checks all FO4StringUtils functions including edge cases, e.g.:
- Empty strings
- Index out-of-bounds
- Null / missing delimiters
- Single-character strings
- Strings with repeated patterns

6. Interpreting Results
- Passed: Function behaved as expected.
- Failed: Function produced unexpected output.
- Check the Papyrus log to see which assertions failed for more details.
- Tip: The log file is located in: Documents\My Games\Fallout4\F4SE\Papyrus\Papyrus.0.log

7. Resetting Tests

To re-run tests:
- Make any changes to scripts or plugin DLLs.
- Recompile / copy updated DLLs and scripts.
- Reload the test ESP or start a new game session.
- Re-run: startquest FO4StringUtils_Test

8. Notes
- This test harness does not affect your main gameplay save.
- You can safely keep it installed alongside other mods.
- Always test on a fresh save if you want reproducible results.

9. Optional: Multi-Version Testing

If you want to verify all FO4StringUtils versions:
- Install separate Fallout 4 versions (GOTY, NG, Anniversary) on different Steam accounts or directories.
- Install matching F4SE and build FO4StringUtils for each.
- Run the same test ESP in each version to ensure API consistency.
