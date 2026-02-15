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

Example:
```
[02/15/2026 - 03:29:48AM] FO4StringUtils: Starting test suite
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: PluginVersion not empty
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: PluginVersion contains dot
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: GameVersion not empty
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: GameVersion contains at least two dots
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: RuntimeVersion not empty
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: RuntimeVersion contains dot
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: VersionInfo not empty
[02/15/2026 - 03:29:48AM] FO4StringUtils VersionInfo: Plugin:2.1.0,Game:1.10.984,Runtime:0.7.2
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: VersionInfo has at least 3 parts
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count empty string
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count single character
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count simple ASCII
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count uppercase
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count mixed characters
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count single whitespace
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count multiple whitespace
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count with space
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count punctuation
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count with dash
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count digits
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count non-negative
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsEmpty empty string
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsEmpty single character
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsEmpty whitespace
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsEmpty normal string
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsEmpty uppercase
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsEmpty digit
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsEmpty punctuation
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Empty consistency IsEmpty
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Empty consistency Count
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Non-empty consistency IsEmpty
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Non-empty consistency Count
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Word consistency IsEmpty
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Word consistency Count
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count does not modify input
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Count unchanged value
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsEmpty does not modify input
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsEmpty preserves input
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Equals: same letters, different case
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Equals: mixed letters and numbers, different case
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Equals: completely different strings
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Equals: substring shorter than other
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Equals: substring longer than other
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Equals: both empty strings
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Equals: empty vs non-empty
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Equals: non-empty vs empty
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Search basic
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Search not found
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: SearchReverse basic
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: SearchIndex forward
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: SearchIndexReverse
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Contains true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Contains false
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: StartsWith true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: StartsWith false
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: EndsWith true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: EndsWith false
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Replace single
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Replace basic
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Replace needle not found
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Replace first only
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Replace at start
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Replace at end
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Replace with empty string
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Replace empty source string
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Replace empty needle
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceAll
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceAll basic
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceAll needle not found
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceAll start and end
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceAll with empty string
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceAll empty source string
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceAll empty needle
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceIndex
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceIndex basic
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceIndex at start
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceIndex at end
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceIndex count exceeds length
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceIndex count zero
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceIndex negative start index
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceIndex negative count
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceIndex empty source string
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ReplaceIndex empty replacement
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Substring basic
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Substring basic 0-5
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Substring basic 5-5
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Substring 2-3
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Substring full from 0
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Substring startIndex beyond length
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Substring count 0
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Substring count beyond length
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Substring negative start index
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Substring negative count
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Substring empty source string
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Remove first
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: RemoveAll
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Reverse
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Repeat
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: TrimStart
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: TrimEnd
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: TrimBoth
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Join
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Split chars length
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Split char 0
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Split char 1
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Split char 2
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Split length
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Split element 0
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Split element 1
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Split element 2
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: CharAt 0
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: OrdinalAt 0
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ToChar 66
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: ToOrdinal C
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: OrdinalJoin
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: OrdinalSplit length
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Ordinal round-trip length
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsAlpha true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsAlpha false
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsDigit true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsDigit false
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsHex true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsHex false
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsAlphaNumeric true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsAlphaNumeric false
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsWhitespace true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsWhitespace false
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsPunctuation true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsPunctuation false
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsASCII true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsASCII false
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsControl true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsControl false
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsPrintable true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsGraph true
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: IsGraph false
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare equal (case-insensitive)
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare 'apple' < 'banana'
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare 'zebra' > 'apple'
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare 'cat' < 'catalog'
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare 'catalog' > 'cat'
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Sort element 0
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Sort element 1
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Sort element 2
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Sort element 3
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Sort length unchanged
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare equal: same case
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare equal: different case
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare equal: mixed case
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare equal: empty strings
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare left < right: simple
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare left < right: single char
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare left < right: empty left
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare left > right: simple
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare left > right: single char
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare left > right: empty right
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare left is prefix of right
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare right is prefix of left
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare totally different: left > right
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare totally different: left < right
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare equal with whitespace
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare punctuation: left > right
[02/15/2026 - 03:29:48AM] FO4StringUtils TEST PASSED: Compare punctuation: left > right
[02/15/2026 - 03:29:48AM] FO4StringUtils: Test suite complete. Passed=162, Failed=0, Total=162
```

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
