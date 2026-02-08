# FO4StringUtils Plugin – USAGE

FO4StringUtils is a Papyrus native plugin for Fallout 4 that provides enhanced string manipulation functions. All functions are global and can be called from any script that imports FO4StringUtils.

## Installation

Copy the DLL for your game version into your F4SE Plugins folder:

- Data\F4SE\Plugins\FO4StringUtils_X_Y.dll

Replace X_Y with the appropriate version number for your game (e.g., 1_0 for GOTY, 2_0 for Next-Gen, 4_0 for Anniversary).

Copy the compiled Papyrus scripts:

- Data\Scripts\FO4StringUtils.pex
- Data\Scripts\Source\User\FO4StringUtils.psc

## Building

- Using Visual Studio 2022 (x64) to build.
- Requires downloading the matching F4SE source distribution -- the F4SE libraries are not included with the FO4StringUtils library.
- Open the F4SE Solution (.sln) file and build either Debug or Release version.
- If unresolved symbols occur, compile the required F4SE `.cpp` files as part of the plugin project (see GOTY / NG / AE BUILD NOTES in main.h)
- Some of the F4SE source distribution files have minor C++ errors that must be corrected to compile properly which are also documented in the GOTY / NG / AE BUILD NOTES in main.h header file.
- Add the appropriate FO4StringUtils_X_Y directory and FO4StringUtils_Shared folders & projects into the F4SE solution to build.

Use the provided compiled .pex file, but to compile the Papyrus script if needed, i.e. generate a .pex (Papyrus executable file) from a .psc (Papyrus source file):

"C:\Program Files (x86)\Steam\steamapps\common\Fallout 4\Papyrus Compiler\PapyrusCompiler.exe" %1 -f="C:\Program Files (x86)\Steam\steamapps\common\Fallout 4\Data\Scripts\Source\Base\Institute_Papyrus_Flags.flg" -i="C:\Program Files (x86)\Steam\steamapps\common\Fallout 4\Data\Scripts\Source" -op -r -final "C:\Program Files (x86)\Steam\steamapps\common\Fallout 4\Data\Scripts\Source\User\FO4StringUtils.psc"

Ensure your mod imports FO4StringUtils before using the functions.

## Importing in Papyrus

Import FO4StringUtils

Once imported, you can call any of the global native functions provided by FO4StringUtils.

## Design Philosophy:

FO4StringUtils is designed to provide reliable and comprehensive string utilities for Fallout 4 Papyrus. It addresses the quirks of the vanilla string system, such as inconsistent string caching and case handling.

### Key Principles:
- All comparison, search, and sort operations are case-insensitive to ensure consistent behavior regardless of the Papyrus string cache.
- Functions that cannot reliably guarantee results in vanilla Papyrus (e.g., IsLower, ToLower, IsUpper, ToUpper) are deliberately excluded.
- Safety and robustness are prioritized: no crashes, infinite loops, or out-of-bounds errors.
- Convenience: provides easy-to-use functions for common tasks like splitting, joining, replacing, trimming, repeating, and title-casing.

Intended for modders who need dependable, full-featured string utilities without worrying about Papyrus caching quirks or inconsistent behavior.

### Case Sensitivity, String Normalization, and Engine String Internals

All string search, comparison, and mutation functions provided by FO4StringUtils are case-insensitive by design. This decision is intentional and reflects the way Papyrus strings are handled internally by the Fallout 4 engine. Operations such as Search, Compare, Equals, Replace, and related functions operate on normalized string data so that character casing does not affect results.

Internally, many game strings are pooled, cached, or resolved through the engine’s string table. As a result, strings originating from engine-managed sources—such as EditorIDs, form names, dialogue text, or other cached values—may be canonicalized or reused in ways that make casing unreliable or inconsistent when observed from Papyrus or the Creation Kit. Treating string comparisons as case-sensitive in this environment can therefore lead to surprising or non-deterministic behavior.

FO4StringUtils embraces this reality by normalizing strings before performing comparisons or mutations, ensuring consistent and predictable behavior regardless of how the original strings were cased or cached by the engine. Rather than exposing or depending on engine-specific casing behavior, the library provides a stable, deterministic API that aligns with how Papyrus strings behave in practice. This avoids ambiguous matching semantics, eliminates subtle bugs caused by string pooling, and ensures that string operations behave consistently across all call sites and data sources.

Example:

```papyrus
r = FO4StringUtils.Replace(
    FO4StringUtils.ToLower(s),
    "pass",
    "***"
)
```

Sequence of events:
- The original string s has the value "Password". Internally, the engine may resolve or cache this value using a canonical form (for example, "PASSWORD"), which would not exactly match "pass" in a case-sensitive comparison.
- ToLower() explicitly normalizes the string value passed to FO4StringUtils, producing "password".
- Replace() performs a strict, case-sensitive match of "pass" within "password" and replaces the matched span with "***".
- The resulting value assigned to r is "***word".

## Function Reference

### Searching & Comparison

| Function                                       | Description                                                          | Example                                                          |
| ---------------------------------------------- | -------------------------------------------------------------------- | ---------------------------------------------------------------- |
| Search(source, needle)                         | Returns the first index of needle in source, or -1 if not found      | Int i = FO4StringUtils.Search("hello world", "world")            |
| SearchReverse(source, needle)                  | Returns the last index of needle in source, or -1 if not found       | Int i = FO4StringUtils.SearchReverse("hello world", "l")         |
| SearchIndex(source, needle, startIndex)        | Finds needle starting from startIndex, or -1 if not found            | Int i = FO4StringUtils.SearchIndex("hello world", "l", 3)        |
| SearchIndexReverse(source, needle, startIndex) | Finds needle in reverse starting from startIndex, or -1 if not found | Int i = FO4StringUtils.SearchIndexReverse("hello world", "l", 8) |
| Contains(source, needle)                       | Returns True if needle is found in source                            | Bool b = FO4StringUtils.Contains("hello", "ell")                 |
| StartsWith(source, prefix)                     | Returns True if source starts with prefix                            | Bool b = FO4StringUtils.StartsWith("hello", "he")                |
| EndsWith(source, suffix)                       | Returns True if source ends with suffix                              | Bool b = FO4StringUtils.EndsWith("hello", "lo")                  |
| Compare(left, right)                           | Case-insensitive comparison; returns -1, 0, or 1                     | Int cmp = FO4StringUtils.Compare("abc", "ABC") => 0              |
| Equals(left, right)                            | Returns True if left equals right (case-insensitive)                 | Bool b = FO4StringUtils.Equals("abc", "ABC")                     |

### Replacing & Removing

| Function                                             | Description                                                        | Example                                                                 |
| ---------------------------------------------------- | ------------------------------------------------------------------ | ----------------------------------------------------------------------- |
| Replace(source, needle, replacement)                 | Replaces the first occurrence of needle with replacement           | String s = FO4StringUtils.Replace("hello world", "world", "universe")   |
| ReplaceAll(source, needle, replacement)              | Replaces all occurrences of needle with replacement                | String s = FO4StringUtils.ReplaceAll("lalala", "la", "ra")              |
| ReplaceIndex(source, startIndex, count, replacement) | Replaces starting at startIndex with length count with replacement | String s = FO4StringUtils.ReplaceIndex("hello world", 6, 5, "universe") |
| Remove(source, needle)                               | Removes the first occurrence of needle from source                 | String s = FO4StringUtils.Remove("hello world", "world")                |
| RemoveAll(source, needle)                            | Removes all occurrences of needle from source                      | String s = FO4StringUtils.RemoveAll("lalala", "la")                     |
| Substring(source, startIndex, count)                 | Returns substring of count characters starting at startIndex       | String s = FO4StringUtils.Substring("hello world", 6, 5)                |
| CharAt(source, startIndex)                           | Returns one character string starting at startIndex                | String s = FO4StringUtils.CharAt("world", 2) => "r"                     |
| OrdinalAt(source, startIndex)                        | Returns an ordinal number for the character starting at startIndex | Int ch = FO4StringUtils.OrdinalAt("CAT", 1) => 65                       |

### String Transformations

| Function              | Description                           | Example                                                         |
| --------------------- | ------------------------------------- | --------------------------------------------------------------- |
| Reverse(source)       | Reverses the string                   | String s = FO4StringUtils.Reverse("hello") => "olleh"           |
| Repeat(source, count) | Repeats the string count times        | String s = FO4StringUtils.Repeat("ha", 3) => "hahaha"           |
| ToChar(ordinal)       | Converts ordinal number to character  | String s = FO4StringUtils.ToChar(65) => "A"                     |
| ToOrdinal(source)     | Converts character to ordinal number  | Int ch = FO4StringUtils.ToOrdinal("ABC") => 65                  |
| TrimStart(source)     | Removes whitespace from the start     | String s = FO4StringUtils.TrimStart(" hello")                   |
| TrimEnd(source)       | Removes whitespace from the end       | String s = FO4StringUtils.TrimEnd("hello ")                     |
| TrimBoth(source)      | Removes whitespace from both ends     | String s = FO4StringUtils.TrimBoth(" hello ")                   |
| ToTitleCase(source)   | Capitalizes first letter of each word | String s = FO4StringUtils.ToTitleCase("john doe") => "John Doe" |

### Character Checks

| Function               | Description                                                 | Example                                              |
| ---------------------- | ----------------------------------------------------------- | ---------------------------------------------------- |
| IsAlpha(source)        | Is the string all letters (A-Z or a-z)                      | Bool b = FO4StringUtils.IsAlpha("Cat")               |
| IsDigit(source)        | Is the string all digits (0-9)                              | Bool b = FO4StringUtils.IsDigit("0123")              |
| IsHex(source)          | Is the string all hexadecimal digits (0-9 or A-F or a-f)    | Bool b = FO4StringUtils.IsHex("DeAd")                |
| IsAlphaNumeric(source) | Is the string all letters (A-Z or a-z) or digits (0-9)      | Bool b = FO4StringUtils.IsAlphaNumeric("Fred123")    |
| IsWhitespace(source)   | Is the string all spaces, tabs, or newlines                 | Bool b = FO4StringUtils.IsWhitespace("   ")          |
| IsPunctuation(source)  | Is the string all punctuation (e.g., !, ., ,, ;)            | Bool b = FO4StringUtils.IsPunctuation(",,,")         |
| IsASCII(source)        | Is the string all 7-bit ASCII characters (0-127)            | Bool b = FO4StringUtils.IsASCII("All ASCII Chars!")  |
| IsControl(source)      | Is the string all control characters (e.g., \n, \r, \t, \0) | Bool b = FO4StringUtils.IsControl("\n\n")            |
| IsPrintable(source)    | Is the string all printable characters including spaces     | Bool b = FO4StringUtils.IsPrintable("Printable 123") |
| IsGraph(source)        | Is the string all printable characters excluding spaces     | Bool b = FO4StringUtils.IsGraph("Graph123")          |

### Array Operations

| Function                 | Description                                  | Example                                                                                        |
| ------------------------ | -------------------------------------------- | ---------------------------------------------------------------------------------------------- |
| Join(parts, delimiter)   | Joins a string array with the delimiter      | String s = FO4StringUtils.Join(["one","two","three"], ",") => "one,two,three"                  |
| Split(source, delimiter) | Splits a string into an array by delimiter   | String[] arr = FO4StringUtils.Split("one,two,three", ",") => ["one","two","three"]             |
| OrdinalJoin(parts)       | Joins an array of ordinals into a string     | String s = FO4StringUtils.OrdinalJoin([65,66,67]) => "ABC"                                     |
| OrdinalSplit(source)     | Splits a string into an array of ordinals    | Int[] arr = FO4StringUtils.OrdinalSplit("ABC") => [65,66,67]                                   |
| Sort(parts)              | Sorts an array of strings (case-insensitive) | String[] arr = FO4StringUtils.Sort(["banana","Apple","carrot"]) => ["Apple","banana","carrot"] |
| Count(source)            | Returns the number of characters in string   | Int len = FO4StringUtils.Count("Hello") => 5                                                   |
| IsEmpty(source)          | Returns True if string is empty              | Bool b = FO4StringUtils.IsEmpty("") => True                                                    |

## Example Usage in a Quest Script

```papyrus
ScriptName FO4StringUtils_TestQuest extends Quest

Import FO4StringUtils

Event OnQuestInit()
    String original = "   hello world   "
    String upper = FO4StringUtils.ToUpper(original)
    String trimmed = FO4StringUtils.TrimBoth(original)
    Bool contains = FO4StringUtils.Contains(original, "world")
    String[] parts = FO4StringUtils.Split(original, " ")
    String joined = FO4StringUtils.Join(parts, "-")

    Debug.Notification("Upper: " + upper)
    Debug.Notification("Trimmed: " + trimmed)
    Debug.Notification("Contains 'world'? " + contains)
    Debug.Notification("Joined: " + joined)
EndEvent
```

### Expected notifications:

- Upper:    HELLO WORLD   
- Trimmed: hello world
- Contains 'world'? True
- Joined: hello-world

## Notes

- All functions are Global Native; they do not require instantiation.
- Strings in Papyrus are immutable, so functions always return new string values.
- Indexes are 0-based.
- Functions that return Int will return -1 if the search fails (e.g., Search/SearchReverse).
- Papyrus String Cache Behavior: Be aware that vanilla strings may not preserve original case; this library is designed around that behavior.
- Case-Sensitive Functions Are Avoided: Functions like IsLower or ToLower are omitted because they cannot reliably guarantee behavior due to caching.
- Focus on Safety and Reliability: Functions are defensive by default, preventing crashes, infinite loops, and other unexpected behaviors common with complex string manipulation in vanilla Papyrus.

## How the FO4StringUtils Library Differs From Vanilla Papyrus

- FO4StringUtils is a comprehensive string utility library for Fallout 4 Papyrus that addresses several quirks and limitations of the built-in string handling.
- Unlike the vanilla Papyrus string API, this library provides consistent, robust, and case-insensitive operations across a wide range of common string tasks.

### Key Differences and Improvements

#### Case-Insensitive Comparison and Search
- Due to Papyrus’s string caching behavior, the case of strings can be inconsistent across different game sessions or systems.
- All search, comparison, and sort functions in this library are case-insensitive by design.
- Functions like Contains, StartsWith, EndsWith, Compare, and Equals will reliably handle strings regardless of their internal cached case.

#### Reliable String Splitting and Joining
- Functions like Split and Join handle both standard delimiters and single-character splitting safely.
- Avoids crashes that occur in vanilla Papyrus when performing complex splits or iterative replacements.

#### Safe Replacement Functions
- Replace, ReplaceAll, and ReplaceIndex provide controlled string replacement with built-in safety against infinite loops and unexpected behavior.

#### Extended Ordinal Support
- OrdinalSplit and OrdinalJoin allow converting between strings and their character code (ASCII/Unicode) representations.
- Useful for low-level character manipulation, sorting, or comparisons.

#### Trimming and Reversal Utilities
- TrimStart, TrimEnd, TrimBoth, and Reverse provide flexible manipulation of whitespace and string order, filling gaps left by vanilla Papyrus.

#### Title Case / Capitalization
- ToTitleCase safely capitalizes the first letter of each word, with optional support for separators like spaces, dashes, and underscores.

#### Comprehensive Validation Functions
- IsAlpha, IsDigit, IsHex, IsAlphaNumeric, IsWhitespace, IsPunctuation, IsASCII, IsControl, IsPrintable, and IsGraph allow robust character-level validation that goes beyond what vanilla Papyrus provides.

#### Sorting Utilities
- Sort uses a case-insensitive comparison function, making it easy to order string arrays in a consistent, predictable way.

#### Additional Convenience Functions
- Echo, CharAt, ToChar, ToOrdinal, Repeat, and Count provide helper functionality for routine string tasks without relying on complex workarounds.
