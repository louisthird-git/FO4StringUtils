#pragma once

// ========================
// Plugin Papyrus Functions
// ========================

#include <string>

#define PAPYRUS_CLASS_NAME                 "FO4StringUtils"    // Name of the Papyrus class for registration

#define PLUGIN_VERSION_FUNCTION_NAME       "PluginVersion"
#define GAME_VERSION_FUNCTION_NAME         "GameVersion"
#define RUNTIME_VERSION_FUNCTION_NAME      "RuntimeVersion"
#define VERSION_INFO_FUNCTION_NAME         "VersionInfo"
#define ECHO_FUNCTION_NAME                 "Echo"
#define COUNT_FUNCTION_NAME                "Count"
#define IS_EMPTY_FUNCTION_NAME             "IsEmpty"
#define COMPARE_FUNCTION_NAME              "Compare"
#define EQUALS_FUNCTION_NAME               "Equals"
#define SEARCH_FUNCTION_NAME               "Search"
#define SEARCH_REVERSE_FUNCTION_NAME       "SearchReverse"
#define SEARCH_INDEX_FUNCTION_NAME         "SearchIndex"
#define SEARCH_INDEX_REVERSE_FUNCTION_NAME "SearchIndexReverse"
#define CONTAINS_FUNCTION_NAME             "Contains"
#define STARTS_WITH_FUNCTION_NAME          "StartsWith"
#define ENDS_WITH_FUNCTION_NAME            "EndsWith"
#define REPLACE_FUNCTION_NAME              "Replace"
#define REPLACE_ALL_FUNCTION_NAME          "ReplaceAll"
#define REPLACE_INDEX_FUNCTION_NAME        "ReplaceIndex"
#define SUBSTRING_FUNCTION_NAME            "Substring"
#define CHAR_AT_FUNCTION_NAME              "CharAt"
#define ORDINAL_AT_FUNCTION_NAME           "OrdinalAt"
#define REMOVE_FUNCTION_NAME               "Remove"
#define REMOVE_ALL_FUNCTION_NAME           "RemoveAll"
#define REVERSE_FUNCTION_NAME              "Reverse"
#define REPEAT_FUNCTION_NAME               "Repeat"
#define TO_CHAR_FUNCTION_NAME              "ToChar"
#define TO_TITLE_CASE_FUNCTION_NAME        "ToTitleCase"
#define TO_ORDINAL_FUNCTION_NAME           "ToOrdinal"
#define TRIM_START_FUNCTION_NAME           "TrimStart"
#define TRIM_END_FUNCTION_NAME             "TrimEnd"
#define TRIM_BOTH_FUNCTION_NAME            "TrimBoth"
#define IS_ALPHA_FUNCTION_NAME             "IsAlpha"
#define IS_DIGIT_FUNCTION_NAME             "IsDigit"
#define IS_HEX_FUNCTION_NAME               "IsHex"
#define IS_ALPHA_NUMERIC_FUNCTION_NAME     "IsAlphaNumeric"
#define IS_WHITESPACE_FUNCTION_NAME        "IsWhitespace"
#define IS_PUNCTUATION_FUNCTION_NAME       "IsPunctuation"
#define IS_ASCII_FUNCTION_NAME             "IsASCII"
#define IS_CONTROL_FUNCTION_NAME           "IsControl"
#define IS_PRINTABLE_FUNCTION_NAME         "IsPrintable"
#define IS_GRAPH_FUNCTION_NAME             "IsGraph"
#define JOIN_FUNCTION_NAME                 "Join"
#define SPLIT_FUNCTION_NAME                "Split"
#define ORDINAL_JOIN_FUNCTION_NAME         "OrdinalJoin"
#define ORDINAL_SPLIT_FUNCTION_NAME        "OrdinalSplit"
#define SORT_FUNCTION_NAME                 "Sort"

class VirtualMachine;

namespace Papyrus
{
    const std::string WHITESPACE_CHARS = " \t\n\r";
    const std::string EMPTY_STRING = "";
    constexpr int NOT_FOUND = -1;
    constexpr int UPPER_BOUND_ASCII = 127;
    constexpr int UPPER_BOUND_EXTENDED_ASCII = 255;

    // Prevent insane allocations (Papyrus-safe upper bound)
    constexpr size_t MAX_OUTPUT_SIZE = static_cast<size_t>(1024u) * 1024u * 16u;

    bool RegisterFunctions(VirtualMachine* vm);
}

// +-----------------------------------+
// | Papyrus  | C++ (native)           |
// |----------|------------------------|
// | Int      | SInt32                 |
// | Bool     | bool                   |
// | Float    | float                  |
// | String   | BSFixedString          |
// | Int[]    | VMArray<SInt32>        |
// | String[] | VMArray<BSFixedString> |
// +-----------------------------------+
