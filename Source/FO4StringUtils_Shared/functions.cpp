// ========================
// Plugin Papyrus Functions
// ========================

// F4SE
#include "f4se/PapyrusNativeFunctions.h"    // for NativeFunction definition

#include <algorithm>                        // for std::transform
#include <cctype>                           // for std char type functions like std::isdigit
#include <functional>                       // for std::function

#include "version.h"                        // for version strings
#include "functions.h"                      // for papyrus plugin functions

namespace Papyrus
{
    // Return if a character is a word separator
    //
    inline bool IsWordSeparator(char c)
    {
        return !std::isalpha(static_cast<unsigned char>(c));
    }

    // Return if ordinal number is in a valid extended ASCII range
    //
    inline bool IsExtendedASCIIOrdinal(SInt32 ordinal)
    {
        return ordinal >= 0 && ordinal <= UPPER_BOUND_EXTENDED_ASCII;
    }

    // Generic iteration over all characters of a string
    //
    inline bool IsAllFunction(const std::string& str, std::function<bool(unsigned char)> charCheck)
    {
        // empty string does not match condition of all matching the check
        if (str.empty())
        {
            return false;
        }

        // always cast to unsigned char for safety
        for (unsigned char c : str)
        {
            // return false if we found a character not passing check
            if (!charCheck(c))
            {
                return false;
            }
        }

        // otherwise the entire string passes
        return true;
    }

    // Usage: std::string sourceStr = FromBSFixedString(sourceBS);
    //
    inline std::string FromBSFixedString(const BSFixedString& sourceBS)
    {
        const char* new_str = sourceBS.c_str();
        return new_str ? std::string(new_str) : std::string();
    }

    // Usage: return ToBSFixedString(sourceStr);
    //
    inline BSFixedString ToBSFixedString(const std::string& str)
    {
        return BSFixedString(str.c_str());
    }

    inline std::string ToLowerCopy(const std::string& str)
    {
        std::string result;
        result.reserve(str.size());

        for (unsigned char c : str)
        {
            result.push_back(static_cast<char>(std::tolower(c)));
        }

        return result;
    }

    inline std::string NormalizeForSearch(const BSFixedString& sourceBS)
    {
        return ToLowerCopy(FromBSFixedString(sourceBS));
    }

    BSFixedString PluginVersionFunction(StaticFunctionTag* base)
    {
        return ToBSFixedString(PluginVersion());
    }

    BSFixedString GameVersionFunction(StaticFunctionTag* base)
    {
        return ToBSFixedString(GameVersion());
    }

    BSFixedString RuntimeVersionFunction(StaticFunctionTag* base)
    {
        return ToBSFixedString(RuntimeVersion());
    }

    BSFixedString VersionInfoFunction(StaticFunctionTag* base)
    {
        std::string info = std::string("Plugin:") + PluginVersion() + ",Game:" + GameVersion() + ",Runtime:" + RuntimeVersion();
        return ToBSFixedString(info);
    }

    BSFixedString EchoFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        return sourceBS;
    }

    SInt32 CountFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        // Convert to C++ string for length
        std::string sourceStr = FromBSFixedString(sourceBS);
        return static_cast<SInt32>(sourceStr.length());
    }

    bool IsEmptyFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        // Convert to C++ string and check length
        std::string sourceStr = FromBSFixedString(sourceBS);
        return sourceStr.empty();
    }

    SInt32 CompareFunction(StaticFunctionTag* base, BSFixedString leftBS, BSFixedString rightBS)
    {
        // Normalize to C++ strings
        std::string leftStr = NormalizeForSearch(leftBS);
        std::string rightStr = NormalizeForSearch(rightBS);
        const size_t leftLen = leftStr.length();
        const size_t rightLen = rightStr.length();

        // Perform the comparison
        int cmp = leftStr.compare(rightStr);

        // Return output values
        if (cmp < 0)
        {
            return -1;
        }
        if (cmp > 0)
        {
            return 1;
        }
        return 0;
    }

    bool EqualsFunction(StaticFunctionTag* base, BSFixedString leftBS, BSFixedString rightBS)
    {
        return CompareFunction(base, leftBS, rightBS) == 0;
    }

    SInt32 SearchFunction(StaticFunctionTag* base, BSFixedString sourceBS, BSFixedString needleBS)
    {
        // Normalize to C++ strings
        std::string sourceStr = NormalizeForSearch(sourceBS);
        std::string needleStr = NormalizeForSearch(needleBS);
        const size_t sourceLen = sourceStr.length();
        const size_t needleLen = needleStr.length();

        // Special case: empty source and needle trivially matches
        if (sourceLen == 0 && needleLen == 0)
        {
            // Trivial match
            return 0;
        }

        // Special case: empty source cannot be found
        if (sourceLen == 0)
        {
            // Not found
            return NOT_FOUND;
        }

        // Special case: empty needle with non-empty source always matches start
        if (needleLen == 0)
        {
            // Trivial match
            return 0;
        }

        // Special case: search string longer than source string
        if (needleLen > sourceLen)
        {
            // Not found
            return NOT_FOUND;
        }

        // Perform the operation
        const size_t found = sourceStr.find(needleStr);

        // Determine the result
        SInt32 result;
        if (found != std::string::npos)
        {
            // Return the zero-based index
            result = static_cast<SInt32>(found);
        }
        else
        {
            // Not found
            result = NOT_FOUND;
        }

        // Return the result string
        return result;
    }

    SInt32 SearchReverseFunction(StaticFunctionTag* base, BSFixedString sourceBS, BSFixedString needleBS)
    {
        // Normalize to C++ strings
        std::string sourceStr = NormalizeForSearch(sourceBS);
        std::string needleStr = NormalizeForSearch(needleBS);
        const size_t sourceLen = sourceStr.length();
        const size_t needleLen = needleStr.length();

        // Special case: empty source and needle trivially matches
        if (sourceLen == 0 && needleLen == 0)
        {
            // Trivial match
            return 0;
        }

        // Special case: empty source cannot be found
        if (sourceLen == 0)
        {
            // Not found
            return NOT_FOUND;
        }

        // Special case: empty needle with non-empty source always matches start
        if (needleLen == 0)
        {
            // Trivial match
            return 0;
        }

        // Special case: search string longer than source string
        if (needleLen > sourceLen)
        {
            // Not found
            return NOT_FOUND;
        }

        // Perform the operation
        const size_t found = sourceStr.rfind(needleStr);

        // Determine the result
        SInt32 result;
        if (found != std::string::npos)
        {
            // Return the zero-based index
            result = static_cast<SInt32>(found);
        }
        else
        {
            // Not found
            result = NOT_FOUND;
        }

        // Return the result string
        return result;
    }

    SInt32 SearchIndexFunction(StaticFunctionTag* base, BSFixedString sourceBS, BSFixedString needleBS, SInt32 startIndex)
    {
        // Normalize to C++ strings
        std::string sourceStr = NormalizeForSearch(sourceBS);
        std::string needleStr = NormalizeForSearch(needleBS);
        const size_t sourceLen = sourceStr.length();
        const size_t needleLen = needleStr.length();

        // Special case: empty source and needle trivially matches
        if (sourceLen == 0 && needleLen == 0)
        {
            // Trivially matches
            return 0;
        }

        // Special case: empty source cannot be found
        if (sourceLen == 0)
        {
            // Set result not found
            return NOT_FOUND;
        }

        // Special case: empty needle with non-empty source always matches start
        if (needleLen == 0)
        {
            // Set match at start
            return 0;
        }

        // Special case: search string longer than source string
        if (needleLen > sourceLen)
        {
            // Not found
            return NOT_FOUND;
        }

        // Validate positive index value
        if (startIndex < 0)
        {
            // Set result not found
            return NOT_FOUND;
        }

        // We know startIndex is non-negative so convert to non-negative variable
        const size_t uStartIndex = static_cast<size_t>(startIndex);

        // Validate index is not greater than string size
        if (uStartIndex >= sourceLen)
        {
            // Set result not found
            return NOT_FOUND;
        }

        // Perform the operation
        const size_t found = sourceStr.find(needleStr, uStartIndex);

        // Determine the result
        SInt32 result;
        if (found != std::string::npos)
        {
            // Return the zero-based index
            result = static_cast<SInt32>(found);
        }
        else
        {
            // Set result not found
            result = NOT_FOUND;
        }

        // Return the result string
        return result;
    }

    SInt32 SearchIndexReverseFunction(StaticFunctionTag* base, BSFixedString sourceBS, BSFixedString needleBS, SInt32 startIndex)
    {
        // Normalize to C++ strings
        std::string sourceStr = NormalizeForSearch(sourceBS);
        std::string needleStr = NormalizeForSearch(needleBS);
        const size_t sourceLen = sourceStr.length();
        const size_t needleLen = needleStr.length();

        // Special case: empty source and needle trivially matches
        if (sourceLen == 0 && needleLen == 0)
        {
            // Trivially matches
            return 0;
        }

        // Special case: empty source cannot be found
        if (sourceLen == 0)
        {
            // Set result not found
            return NOT_FOUND;
        }

        // Special case: empty needle with non-empty source always matches start
        if (needleLen == 0)
        {
            // Set match at start
            return 0;
        }

        // Special case: search string longer than source string
        if (needleLen > sourceLen)
        {
            // Not found
            return NOT_FOUND;
        }

        // Validate positive index value
        if (startIndex < 0)
        {
            // Set result not found
            return NOT_FOUND;
        }

        // We know startIndex is non-negative so convert to non-negative variable
        size_t uStartIndex = static_cast<size_t>(startIndex);

        // Clamp index to last valid character
        if (uStartIndex >= sourceLen)
        {
            uStartIndex = sourceLen - 1;
        }

        // Perform the operation
        const size_t found = sourceStr.rfind(needleStr, uStartIndex);

        // Determine the result
        SInt32 result;
        if (found != std::string::npos)
        {
            // Return the zero-based index
            result = static_cast<SInt32>(found);
        }
        else
        {
            // Set result not found
            result = NOT_FOUND;
        }

        // Return the result string
        return result;
    }

    bool ContainsFunction(StaticFunctionTag* base, BSFixedString sourceBS, BSFixedString needleBS)
    {
        // Normalize to C++ strings
        std::string sourceStr = NormalizeForSearch(sourceBS);
        std::string needleStr = NormalizeForSearch(needleBS);
        const size_t sourceLen = sourceStr.length();
        const size_t needleLen = needleStr.length();

        // Special case: empty source and needle trivially matches
        if (sourceLen == 0 && needleLen == 0)
        {
            // Trivially matches
            return true;
        }

        // Special case: empty source cannot be found
        if (sourceLen == 0)
        {
            // Set result not found
            return false;
        }

        // Special case: empty needle with non-empty source always matches start
        if (needleLen == 0)
        {
            // Set match at start
            return true;
        }

        // Special case: search string longer than source string
        if (needleLen > sourceLen)
        {
            // Not found
            return false;
        }

        // Perform the operation
        return sourceStr.find(needleStr) != std::string::npos;
    }

    bool StartsWithFunction(StaticFunctionTag* base, BSFixedString sourceBS, BSFixedString prefixBS)
    {
        // Normalize to C++ strings
        std::string sourceStr = NormalizeForSearch(sourceBS);
        std::string prefixStr = NormalizeForSearch(prefixBS);
        const size_t sourceLen = sourceStr.length();
        const size_t prefixLen = prefixStr.length();

        // Special case: empty prefix -> true
        if (prefixLen == 0)
        {
            // Always matches
            return true;
        }

        // Special case: empty source -> false
        if (sourceLen == 0)
        {
            // Empty source with non-empty prefix cannot match
            return false;
        }

        // Early out: prefix longer than source -> cannot match
        if (prefixLen > sourceLen)
        {
            // Cannot match
            return false;
        }

        // Compare start of source with prefix using std::string::compare
        return (sourceStr.compare(0, prefixStr.length(), prefixStr) == 0);
    }

    bool EndsWithFunction(StaticFunctionTag* base, BSFixedString sourceBS, BSFixedString suffixBS)
    {
        // Normalize to C++ strings
        std::string sourceStr = NormalizeForSearch(sourceBS);
        std::string suffixStr = NormalizeForSearch(suffixBS);
        const size_t sourceLen = sourceStr.length();
        const size_t suffixLen = suffixStr.length();

        // Special case: empty suffix -> true
        if (suffixLen == 0)
        {
            // Always matches
            return true;
        }

        // Special case: empty source -> false
        if (sourceLen == 0)
        {
            // Empty source with non-empty suffix cannot match
            return false;
        }

        // Early out: suffix longer than source -> cannot match
        if (suffixLen > sourceLen)
        {
            // Cannot match
            return false;
        }

        // Compare end of source with suffix using std::string::compare
        return (sourceStr.compare(sourceStr.length() - suffixStr.length(), suffixStr.length(), suffixStr) == 0);
    }

    BSFixedString ReplaceFunction(StaticFunctionTag* base, BSFixedString sourceBS, BSFixedString needleBS, BSFixedString replacementBS)
    {
        // Normalize and convert to C++ strings
        std::string originalStr = FromBSFixedString(sourceBS);
        std::string sourceStr = NormalizeForSearch(sourceBS);
        std::string needleStr = NormalizeForSearch(needleBS);
        std::string replacementStr = FromBSFixedString(replacementBS);
        const size_t sourceLen = sourceStr.length();
        const size_t needleLen = needleStr.length();

        // Special case: empty old string -> nothing to replace
        if (sourceLen == 0 || needleLen == 0)
        {
            // Return original string unchanged
            return sourceBS;
        }

        // Perform replacement
        size_t position = 0;
        if ((position = sourceStr.find(needleStr, position)) != std::string::npos)
        {
            originalStr.replace(position, needleLen, replacementStr);
        }

        // Return the result string
        return ToBSFixedString(originalStr.c_str());
    }

    BSFixedString ReplaceAllFunction(StaticFunctionTag* base, BSFixedString sourceBS, BSFixedString needleBS, BSFixedString replacementBS)
    {
        // Normalize and convert to C++ strings
        std::string originalStr = FromBSFixedString(sourceBS);
        std::string sourceStr = NormalizeForSearch(sourceBS);
        std::string needleStr = NormalizeForSearch(needleBS);
        std::string replacementStr = FromBSFixedString(replacementBS);
        std::string replacementNorm = NormalizeForSearch(replacementBS);

        const size_t sourceLen = sourceStr.length();
        const size_t needleLen = needleStr.length();
        const size_t replacementLen = replacementNorm.length();

        // Special case: empty old string -> nothing to replace
        if (sourceLen == 0 || needleLen == 0)
        {
            // Return original string unchanged
            return sourceBS;
        }

        // Perform replacement
        size_t position = 0;
        while ((position = sourceStr.find(needleStr, position)) != std::string::npos)
        {
            originalStr.replace(position, needleLen, replacementStr);
            sourceStr.replace(position, needleLen, replacementNorm);

            position += replacementLen; // move past replacement
        }

        // Return the result string
        return ToBSFixedString(originalStr.c_str());
    }

    BSFixedString ReplaceIndexFunction(StaticFunctionTag* base, BSFixedString sourceBS, SInt32 startIndex, SInt32 count, BSFixedString replacementBS)
    {
        // Convert to C++ strings
        std::string sourceStr = FromBSFixedString(sourceBS);
        std::string replacementStr = FromBSFixedString(replacementBS);
        const size_t sourceLen = sourceStr.length();

        // Special case: empty old string -> nothing to replace
        if (sourceLen == 0)
        {
            // Return original string unchanged
            return sourceBS;
        }

        // Special case: count less than zero or zero -> nothing to do
        if (count <= 0)
        {
            // Return original string unchanged
            return sourceBS;
        }

        // Defensive clamping of startIndex and count to valid range
        if (startIndex < 0)
        {
            startIndex = 0;
        }
        if ((size_t)startIndex > sourceLen)
        {
            startIndex = static_cast<SInt32>(sourceLen);
        }
        if ((size_t)(startIndex + count) > sourceLen)
        {
            count = static_cast<SInt32>(sourceLen - startIndex);
        }

        // Replace / insert
        sourceStr.replace(startIndex, count, replacementStr);

        // Return the result string
        return ToBSFixedString(sourceStr);
    }

    BSFixedString SubstringFunction(StaticFunctionTag* base, BSFixedString sourceBS, SInt32 startIndex, SInt32 count)
    {
        // Convert source to std::string for safe manipulation
        std::string sourceStr = FromBSFixedString(sourceBS);
        const size_t sourceLen = sourceStr.length();

        // No source string to extract from
        if (sourceLen == 0)
        {
            // Zero-length source -> empty string
            return ToBSFixedString(EMPTY_STRING);
        }

        // Special case: count less than zero or zero -> nothing to do
        if (count <= 0)
        {
            // Zero-length substring -> empty string
            return ToBSFixedString(EMPTY_STRING);
        }

        // Defensive clamping of startIndex and count to valid range
        if (startIndex < 0)
        {
            startIndex = 0;
        }
        if ((size_t)startIndex > sourceLen)
        {
            startIndex = static_cast<SInt32>(sourceLen);
        }
        if ((size_t)(startIndex + count) > sourceLen)
        {
            count = static_cast<SInt32>(sourceLen - startIndex);
        }

        // Extract substring
        return ToBSFixedString(sourceStr.substr(startIndex, count));
    }

    BSFixedString ToCharFunction(StaticFunctionTag* base, SInt32 ordinal)
    {
        // only valid ordinal range is allowed otherwise an empty string
        if (!IsExtendedASCIIOrdinal(ordinal))
        {
            // values outside the range are an empty string
            return ToBSFixedString(EMPTY_STRING);
        }

        // turn the ordinal into a character
        char c = static_cast<char>(ordinal);

        // create a std::string with one character
        std::string charStr(1, c);

        // convert std::string to BSFixedString
        return ToBSFixedString(charStr);
    }

    BSFixedString ToTitleCaseFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        // Convert to C++ string
        std::string sourceStr = FromBSFixedString(sourceBS);
        const size_t sourceLen = sourceStr.length();

        // No source string to extract from
        if (sourceLen == 0)
        {
            // Zero-length source -> empty string
            return ToBSFixedString(EMPTY_STRING);
        }

        bool capitalizeNext = true;

        for (size_t i = 0; i < sourceLen; i++)
        {
            unsigned char c = static_cast<unsigned char>(sourceStr[i]);

            // Whitespace resets word start
            if (IsWordSeparator(c))
            {
                capitalizeNext = true;
            }
            else
            {
                if (capitalizeNext)
                {
                    sourceStr[i] = static_cast<char>(std::toupper(c));
                    capitalizeNext = false;
                }
                else
                {
                    sourceStr[i] = static_cast<char>(std::tolower(c));
                }
            }
        }

        // Convert back to BSFixedString
        return ToBSFixedString(sourceStr);
    }
    
    BSFixedString CharAtFunction(StaticFunctionTag* base, BSFixedString sourceBS, SInt32 startIndex)
    {
        return SubstringFunction(base, sourceBS, startIndex, 1);
    }

    SInt32 ToOrdinalFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        // Convert to C++ string
        std::string sourceStr = FromBSFixedString(sourceBS);
        const size_t sourceLen = sourceStr.length();

        // empty string check
        if (sourceLen == 0)
        {
            // return that the ordinal value cannot be found for empty string
            return NOT_FOUND;
        }

        // take the first character
        unsigned char c = static_cast<unsigned char>(sourceStr[0]);

        // return as integer ordinal
        return static_cast<SInt32>(c);
    }

    SInt32 OrdinalAtFunction(StaticFunctionTag* base, BSFixedString sourceBS, SInt32 startIndex)
    {
       // convert to ordinal and will be -1 if string empty or out-of-bounds
        return ToOrdinalFunction(base, CharAtFunction(base, sourceBS, startIndex)); 
    }

    BSFixedString RemoveFunction(StaticFunctionTag* base, BSFixedString sourceBS, BSFixedString targetBS)
    {
        // Normalize and convert to C++ strings for safe manipulation
        std::string originalStr = FromBSFixedString(sourceBS);
        std::string sourceStr = NormalizeForSearch(sourceBS);
        std::string targetStr = NormalizeForSearch(targetBS);
        const size_t sourceLen = sourceStr.length();
        const size_t targetLen = targetStr.length();

        // If target is empty, nothing to remove
        if (sourceLen == 0 || targetLen == 0)
        {
            // Return original string
            return sourceBS;
        }

        // Remove first occurrence of target
        const size_t position = sourceStr.find(targetStr);
        if (position != std::string::npos)
        {
            originalStr.erase(position, targetLen);
        }

        // Return the result string
        return ToBSFixedString(originalStr);
    }

    BSFixedString RemoveAllFunction(StaticFunctionTag* base, BSFixedString sourceBS, BSFixedString targetBS)
    {
        // Normalize and convert to C++ strings for safe manipulation
        std::string originalStr = FromBSFixedString(sourceBS);
        std::string sourceStr = NormalizeForSearch(sourceBS);
        std::string targetStr = NormalizeForSearch(targetBS);
        const size_t sourceLen = sourceStr.length();
        const size_t targetLen = targetStr.length();

        // If target is empty, nothing to remove
        if (sourceLen == 0 || targetLen == 0)
        {
            // Return original string
            return sourceBS;
        }

        // Remove all occurrences of target
        size_t position = 0;
        while ((position = sourceStr.find(targetStr, position)) != std::string::npos)
        {
            // erase at the found position
            originalStr.erase(position, targetLen);
            sourceStr.erase(position, targetLen);
        }

        // Return the result string
        return ToBSFixedString(originalStr);
    }

    BSFixedString ReverseFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        // Convert to C++ string for manipulation
        std::string sourceStr = FromBSFixedString(sourceBS);
        const size_t sourceLen = sourceStr.length();

        // Empty string in then empty string out
        if (sourceLen == 0)
        {
            // Return empty string
            return ToBSFixedString(EMPTY_STRING);
        }

        // Reverse the string
        std::reverse(sourceStr.begin(), sourceStr.end());

        // Return the result string
        return ToBSFixedString(sourceStr);
    }

    BSFixedString RepeatFunction(StaticFunctionTag* base, BSFixedString sourceBS, SInt32 count)
    {
        // Setup the string
        std::string sourceStr = FromBSFixedString(sourceBS);
        const size_t sourceLen = sourceStr.length();

        // Non-positive repeat → empty string
        if (count <= 0 || sourceLen == 0)
        {
            // Return empty string
            return ToBSFixedString(EMPTY_STRING);
        }

        // Prevent overflow & runaway memory use
        if (sourceLen > MAX_OUTPUT_SIZE || count > MAX_OUTPUT_SIZE || (sourceLen * count) > MAX_OUTPUT_SIZE)
        {
            return ToBSFixedString(EMPTY_STRING);
        }

        // Build output efficiently
        std::string outStr;
        outStr.reserve(sourceLen * count); // optional, avoids reallocs

        for (int i = 0; i < count; ++i)
        {
            outStr.append(sourceStr); // append the whole string
        }

        // Return the result string
        return ToBSFixedString(outStr.c_str());
    }

    BSFixedString TrimStartFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        // Convert to C++ string for manipulation
        std::string sourceStr = FromBSFixedString(sourceBS);
        const size_t sourceLen = sourceStr.length();

        // Empty string in then empty string out
        if (sourceLen == 0)
        {
            // Return empty string
            return ToBSFixedString(EMPTY_STRING);
        }

        // Find first non-whitespace character
        size_t start = sourceStr.find_first_not_of(WHITESPACE_CHARS);
        if (start == std::string::npos)
        {
            // String is all whitespace; clear it
            sourceStr.clear();
        }
        else
        {
            // Trim leading whitespace
            sourceStr = sourceStr.substr(start);
        }

        // Return the result string
        return ToBSFixedString(sourceStr);
    }

    BSFixedString TrimEndFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        // Convert to C++ string for manipulation
        std::string sourceStr = FromBSFixedString(sourceBS);
        const size_t sourceLen = sourceStr.length();

        // Empty string in then empty string out
        if (sourceLen == 0)
        {
            // Return empty string
            return ToBSFixedString(EMPTY_STRING);
        }

        // Find the last non-whitespace character
        size_t end = sourceStr.find_last_not_of(WHITESPACE_CHARS);

        // If the string is all whitespace
        if (end == std::string::npos)
        {
            // clear it
            sourceStr.clear();
        }
        else
        {
            // trim the end
            sourceStr = sourceStr.substr(0, end + 1);
        }

        // Return the result string
        return ToBSFixedString(sourceStr);
    }

    BSFixedString TrimBothFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        // Convert to C++ string for manipulation
        std::string sourceStr = FromBSFixedString(sourceBS);
        const size_t sourceLen = sourceStr.length();

        // Empty string in then empty string out
        if (sourceLen == 0)
        {
            // Return empty string
            return ToBSFixedString(EMPTY_STRING);
        }

        // Find first non-whitespace character
        size_t start = sourceStr.find_first_not_of(WHITESPACE_CHARS);

        // Find last non-whitespace character
        size_t end = sourceStr.find_last_not_of(WHITESPACE_CHARS);

        // If string is all whitespace, clear
        if (start == std::string::npos || end == std::string::npos)
        {
            sourceStr.clear();
        }
        else
        {
            // Extract trimmed substring
            sourceStr = sourceStr.substr(start, end - start + 1);
        }

        // Return the result string
        return ToBSFixedString(sourceStr);
    }

    bool IsAlphaFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        return IsAllFunction(FromBSFixedString(sourceBS), ::isalpha);
    }

    bool IsDigitFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        return IsAllFunction(FromBSFixedString(sourceBS), ::isdigit);
    }

    bool IsHexFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        return IsAllFunction(FromBSFixedString(sourceBS), ::isxdigit);
    }

    bool IsAlphaNumericFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        return IsAllFunction(FromBSFixedString(sourceBS), ::isalnum);
    }

    bool IsWhitespaceFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        return IsAllFunction(FromBSFixedString(sourceBS), ::isspace);
    }

    bool IsPunctuationFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        return IsAllFunction(FromBSFixedString(sourceBS), ::ispunct);
    }

    bool IsASCIIFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        return IsAllFunction(FromBSFixedString(sourceBS), [](unsigned char c)
        {
            return c <= UPPER_BOUND_ASCII;
        });
    }

    bool IsControlFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        return IsAllFunction(FromBSFixedString(sourceBS), ::iscntrl);
    }

    bool IsPrintableFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        return IsAllFunction(FromBSFixedString(sourceBS), ::isprint);
    }

    bool IsGraphFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        return IsAllFunction(FromBSFixedString(sourceBS), ::isgraph);
    }

    BSFixedString JoinFunction(StaticFunctionTag* base, VMArray<BSFixedString> arrayData, BSFixedString delimiterBS)
    {
        // Convert to C++ string for manipulation
        std::string delimiterStr = FromBSFixedString(delimiterBS);

        std::string resultStr;

        const UInt32 len = arrayData.Length();
        bool first = true;

        // Loop through the parts of the array
        for (UInt32 i = 0; i < len; i++)
        {
            BSFixedString part;
            arrayData.Get(&part, i);

            // Defensive: treat null as empty
            if (!part.data)
            {
                continue;
            }

            // Append delimiter; except for first element
            if (!first)
            {
                resultStr += delimiterStr;
            }

            // Append the element
            resultStr += part.c_str();

            // Not the first element anymore
            first = false;
        }

        // Return the result string
        return ToBSFixedString(resultStr);
    }

    VMArray<BSFixedString> SplitFunction(StaticFunctionTag* base, BSFixedString sourceBS, BSFixedString delimiterBS)
    {
        // The result array
        VMArray<BSFixedString> result;

        // Defensive: null source
        if (!sourceBS.data)
        {
            return result;
        }

        // Convert to C++ string for manipulation
        std::string sourceStr = FromBSFixedString(sourceBS);

        // Convert to C++ string for manipulation
        std::string delimiterStr = FromBSFixedString(delimiterBS);
        size_t delimiterLen = delimiterStr.length();

        // Empty delimiter = split into characters
        if (delimiterLen == 0)
        {
            for (char ch : sourceStr)
            {
                std::string oneChar(1, ch);
                BSFixedString oneCharBS = ToBSFixedString(oneChar.c_str());
                result.Push(&oneCharBS);
            }
            return result;
        }

        size_t start = 0;

        // Loop through until we do not find any more delimiters
        while (true)
        {
            // Find the next position
            size_t pos = sourceStr.find(delimiterStr, start);

            // If not found then we are done
            if (pos == std::string::npos)
            {
                break;
            }

            // Append the segment
            std::string token = sourceStr.substr(start, pos - start);
            BSFixedString tokenBS = ToBSFixedString(token.c_str());
            result.Push(&tokenBS);

            // Move past the delimiter
            start = pos + delimiterLen;
        }

        // Final segment (can be empty)
        std::string tail = sourceStr.substr(start);
        BSFixedString tailBS = ToBSFixedString(tail.c_str());
        result.Push(&tailBS);

        // Return the result string
        return result;
    }

    BSFixedString OrdinalJoinFunction(StaticFunctionTag* base, VMArray<SInt32> arrayData)
    {
        std::string resultStr;

        // get the VMArray length
        const UInt32 len = arrayData.Length();

        // loop through the entire array turning the ordinal values into characters
        for (UInt32 i = 0; i < len; ++i)
        {
            // read the element value from the VMArray
            SInt32 ordinal = 0;
            arrayData.Get(&ordinal, i);

            // Use ToChar logic: skip invalid element
            if (!IsExtendedASCIIOrdinal(ordinal))
            {
                // do not even include elements outside the valid ordinal range
                continue;
            }

            // append character to the end of result string
            resultStr.push_back(static_cast<char>(ordinal));
        }

        // return the result string
        return ToBSFixedString(resultStr);
    }

    VMArray<SInt32> OrdinalSplitFunction(StaticFunctionTag* base, BSFixedString sourceBS)
    {
        VMArray<SInt32> resultArray;

        // Convert BSFixedString to std::string for easy iteration
        std::string sourceStr = FromBSFixedString(sourceBS);
        const size_t sourceLen = sourceStr.length();

        for (size_t i = 0; i < sourceLen; ++i)
        {
            // Assure character is in range character range
            SInt32 c = static_cast<unsigned char>(sourceStr[i]);

            // Push into VMArray<SInt32>
            resultArray.Push(&c);
        }

        // return the result array
        return resultArray;
    }

    VMArray<BSFixedString> SortFunction(StaticFunctionTag* base, VMArray<BSFixedString> parts)
    {
        // Determine length of input array
        UInt32 length = parts.Length();

        // Defensive: empty array -> return empty VMArray
        if (length == 0)
        {
            // return empty array
            return VMArray<BSFixedString>();
        }

        // Temporary vector to hold all elements safely
        std::vector<BSFixedString> tempVec(length);

        // Copy elements from VMArray into vector
        for (UInt32 i = 0; i < length; ++i)
        {
            parts.Get(&tempVec[i], i);
        }

        // Sort the vector using case-insensitive CompareFunction
        std::sort(tempVec.begin(), tempVec.end(), [](const BSFixedString& a, const BSFixedString& b)
        {
            return CompareFunction(nullptr, a, b) < 0;
        });

        // Prepare result VMArray
        VMArray<BSFixedString> result;

        // Push sorted elements into result safely
        for (UInt32 i = 0; i < length; ++i)
        {
            result.Push(&tempVec[i]);
        }

        // Return the sorted array
        return result;
    }

    bool RegisterFunctions(VirtualMachine* vm)
    {
        vm->RegisterFunction(new NativeFunction0<StaticFunctionTag, BSFixedString>(PLUGIN_VERSION_FUNCTION_NAME, PAPYRUS_CLASS_NAME, PluginVersionFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, PLUGIN_VERSION_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction0<StaticFunctionTag, BSFixedString>(GAME_VERSION_FUNCTION_NAME, PAPYRUS_CLASS_NAME, GameVersionFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, GAME_VERSION_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction0<StaticFunctionTag, BSFixedString>(RUNTIME_VERSION_FUNCTION_NAME, PAPYRUS_CLASS_NAME, RuntimeVersionFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, RUNTIME_VERSION_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction0<StaticFunctionTag, BSFixedString>(VERSION_INFO_FUNCTION_NAME, PAPYRUS_CLASS_NAME, VersionInfoFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, VERSION_INFO_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, BSFixedString, BSFixedString>(ECHO_FUNCTION_NAME, PAPYRUS_CLASS_NAME, EchoFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, ECHO_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, SInt32, BSFixedString>(COUNT_FUNCTION_NAME, PAPYRUS_CLASS_NAME, CountFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, COUNT_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>(IS_EMPTY_FUNCTION_NAME, PAPYRUS_CLASS_NAME, IsEmptyFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, IS_EMPTY_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, SInt32, BSFixedString, BSFixedString>(COMPARE_FUNCTION_NAME, PAPYRUS_CLASS_NAME, CompareFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, COMPARE_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, BSFixedString>(EQUALS_FUNCTION_NAME, PAPYRUS_CLASS_NAME, EqualsFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, EQUALS_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, SInt32, BSFixedString, BSFixedString>(SEARCH_FUNCTION_NAME, PAPYRUS_CLASS_NAME, SearchFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, SEARCH_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, SInt32, BSFixedString, BSFixedString>(SEARCH_REVERSE_FUNCTION_NAME, PAPYRUS_CLASS_NAME, SearchReverseFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, SEARCH_REVERSE_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction3<StaticFunctionTag, SInt32, BSFixedString, BSFixedString, SInt32>(SEARCH_INDEX_FUNCTION_NAME, PAPYRUS_CLASS_NAME, SearchIndexFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, SEARCH_INDEX_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction3<StaticFunctionTag, SInt32, BSFixedString, BSFixedString, SInt32>(SEARCH_INDEX_REVERSE_FUNCTION_NAME, PAPYRUS_CLASS_NAME, SearchIndexReverseFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, SEARCH_INDEX_REVERSE_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, BSFixedString>(CONTAINS_FUNCTION_NAME, PAPYRUS_CLASS_NAME, ContainsFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, CONTAINS_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, BSFixedString>(STARTS_WITH_FUNCTION_NAME, PAPYRUS_CLASS_NAME, StartsWithFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, STARTS_WITH_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, BSFixedString>(ENDS_WITH_FUNCTION_NAME, PAPYRUS_CLASS_NAME, EndsWithFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, ENDS_WITH_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction3<StaticFunctionTag, BSFixedString, BSFixedString, BSFixedString, BSFixedString>(REPLACE_FUNCTION_NAME, PAPYRUS_CLASS_NAME, ReplaceFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, REPLACE_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction3<StaticFunctionTag, BSFixedString, BSFixedString, BSFixedString, BSFixedString>(REPLACE_ALL_FUNCTION_NAME, PAPYRUS_CLASS_NAME, ReplaceAllFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, REPLACE_ALL_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction3<StaticFunctionTag, BSFixedString, BSFixedString, SInt32, SInt32>(SUBSTRING_FUNCTION_NAME, PAPYRUS_CLASS_NAME, SubstringFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, SUBSTRING_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction4<StaticFunctionTag, BSFixedString, BSFixedString, SInt32, SInt32, BSFixedString>(REPLACE_INDEX_FUNCTION_NAME, PAPYRUS_CLASS_NAME, ReplaceIndexFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, REPLACE_INDEX_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, BSFixedString, BSFixedString, SInt32>(CHAR_AT_FUNCTION_NAME, PAPYRUS_CLASS_NAME, CharAtFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, CHAR_AT_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, SInt32, BSFixedString, SInt32>(ORDINAL_AT_FUNCTION_NAME, PAPYRUS_CLASS_NAME, OrdinalAtFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, ORDINAL_AT_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, BSFixedString, BSFixedString, BSFixedString>(REMOVE_FUNCTION_NAME, PAPYRUS_CLASS_NAME, RemoveFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, REMOVE_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, BSFixedString, BSFixedString, BSFixedString>(REMOVE_ALL_FUNCTION_NAME, PAPYRUS_CLASS_NAME, RemoveAllFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, REMOVE_ALL_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, BSFixedString, BSFixedString>(REVERSE_FUNCTION_NAME, PAPYRUS_CLASS_NAME, ReverseFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, REVERSE_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, BSFixedString, BSFixedString, SInt32>(REPEAT_FUNCTION_NAME, PAPYRUS_CLASS_NAME, RepeatFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, REPEAT_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, BSFixedString, SInt32>(TO_CHAR_FUNCTION_NAME, PAPYRUS_CLASS_NAME, ToCharFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, TO_CHAR_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, BSFixedString, BSFixedString>(TO_TITLE_CASE_FUNCTION_NAME, PAPYRUS_CLASS_NAME, ToTitleCaseFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, TO_TITLE_CASE_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, SInt32, BSFixedString>(TO_ORDINAL_FUNCTION_NAME, PAPYRUS_CLASS_NAME, ToOrdinalFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, TO_ORDINAL_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, BSFixedString, BSFixedString>(TRIM_START_FUNCTION_NAME, PAPYRUS_CLASS_NAME, TrimStartFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, TRIM_START_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, BSFixedString, BSFixedString>(TRIM_END_FUNCTION_NAME, PAPYRUS_CLASS_NAME, TrimEndFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, TRIM_END_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, BSFixedString, BSFixedString>(TRIM_BOTH_FUNCTION_NAME, PAPYRUS_CLASS_NAME, TrimBothFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, TRIM_BOTH_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>(IS_ALPHA_FUNCTION_NAME, PAPYRUS_CLASS_NAME, IsAlphaFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, IS_ALPHA_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>(IS_DIGIT_FUNCTION_NAME, PAPYRUS_CLASS_NAME, IsDigitFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, IS_DIGIT_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>(IS_HEX_FUNCTION_NAME, PAPYRUS_CLASS_NAME, IsHexFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, IS_HEX_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>(IS_ALPHA_NUMERIC_FUNCTION_NAME, PAPYRUS_CLASS_NAME, IsAlphaNumericFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, IS_ALPHA_NUMERIC_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>(IS_WHITESPACE_FUNCTION_NAME, PAPYRUS_CLASS_NAME, IsWhitespaceFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, IS_WHITESPACE_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>(IS_PUNCTUATION_FUNCTION_NAME, PAPYRUS_CLASS_NAME, IsPunctuationFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, IS_PUNCTUATION_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>(IS_ASCII_FUNCTION_NAME, PAPYRUS_CLASS_NAME, IsASCIIFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, IS_ASCII_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>(IS_CONTROL_FUNCTION_NAME, PAPYRUS_CLASS_NAME, IsControlFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, IS_CONTROL_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>(IS_PRINTABLE_FUNCTION_NAME, PAPYRUS_CLASS_NAME, IsPrintableFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, IS_PRINTABLE_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>(IS_GRAPH_FUNCTION_NAME, PAPYRUS_CLASS_NAME, IsGraphFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, IS_GRAPH_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, BSFixedString, VMArray<BSFixedString>, BSFixedString>(JOIN_FUNCTION_NAME, PAPYRUS_CLASS_NAME, JoinFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, JOIN_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction2<StaticFunctionTag, VMArray<BSFixedString>, BSFixedString, BSFixedString>(SPLIT_FUNCTION_NAME, PAPYRUS_CLASS_NAME, SplitFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, SPLIT_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, BSFixedString, VMArray<SInt32>>(ORDINAL_JOIN_FUNCTION_NAME, PAPYRUS_CLASS_NAME, OrdinalJoinFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, ORDINAL_JOIN_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, VMArray<SInt32>, BSFixedString>(ORDINAL_SPLIT_FUNCTION_NAME, PAPYRUS_CLASS_NAME, OrdinalSplitFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, ORDINAL_SPLIT_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        vm->RegisterFunction(new NativeFunction1<StaticFunctionTag, VMArray<BSFixedString>, VMArray<BSFixedString>>(SORT_FUNCTION_NAME, PAPYRUS_CLASS_NAME, SortFunction, vm));
        vm->SetFunctionFlags(PAPYRUS_CLASS_NAME, SORT_FUNCTION_NAME, IFunction::kFunctionFlag_NoWait);

        return true;
    }
}
