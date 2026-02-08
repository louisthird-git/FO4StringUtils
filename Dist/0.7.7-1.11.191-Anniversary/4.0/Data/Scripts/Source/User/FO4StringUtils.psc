;---------------------------------------------------------------------------
; Script: FO4StringUtils
;
; Description:
;   A native utility library providing robust string manipulation,
;   comparison, searching, and transformation functions for Fallout 4
;   Papyrus scripts.
;
;   This library is designed to work around limitations and quirks of the
;   Papyrus string system by offering predictable, defensive behavior for
;   common string operations that are otherwise cumbersome or unreliable
;   to implement in pure Papyrus.
;
; Notes:
;   - All string comparison, search, and sort functions in this library are
;     case-insensitive by design.
;
;   - Fallout 4 Papyrus uses an internal string cache which may return
;     strings with different casing than what was originally authored.
;     As a result, case-sensitive string behavior cannot be reliably
;     guaranteed.
;
;   - Functions that depend on consistent casing (such as IsLower, IsUpper,
;     ToLower, or ToUpper) are intentionally not included, as their results
;     may vary across systems, load orders, or runtime conditions.
;
;   - Functions in this library favor correctness, safety, and predictability
;     over raw performance.
;
;   - All functions are implemented natively for efficiency and to avoid
;     common Papyrus performance and memory pitfalls.
;
;   - Unless otherwise stated, functions do not modify their inputs and
;     instead return new string or array instances.
;
;---------------------------------------------------------------------------
Scriptname FO4StringUtils Native Hidden

;---------------------------------------------------------------------------
; Function: Echo
;
; Description:
;   Returns the input string unchanged.
;   Primarily used for testing string behavior and engine string caching.
;
; Parameters:
;   source - The string to return.
;
; Returns:
;   The same string value that was passed in.
;
; Notes:
;   Useful for exposing Papyrus string cache behavior.
;---------------------------------------------------------------------------
String   Function Echo(String source) Global Native

;---------------------------------------------------------------------------
; Function: Count
;
; Description:
;   Returns the number of characters in the given string.
;
; Parameters:
;   source - The string to measure.
;
; Returns:
;   The number of characters in the string.
;   Returns 0 if the string is empty.
;
; Notes:
;   This function exists because Papyrus does not provide a built-in
;   string length property.
;---------------------------------------------------------------------------
Int      Function Count(String source) Global Native

;---------------------------------------------------------------------------
; Function: IsEmpty
;
; Description:
;   Determines whether the given string is empty.
;
; Parameters:
;   source - The string to test.
;
; Returns:
;   True if the string has zero characters, false otherwise.
;
; Notes:
;   This is equivalent to checking Count(source) == 0, but provided
;   as a convenience function for clarity.
;---------------------------------------------------------------------------
Bool     Function IsEmpty(String source) Global Native

;---------------------------------------------------------------------------
; Function: Compare
;
; Description:
;   Performs a case-insensitive lexicographical comparison between two strings.
;
; Parameters:
;   left  - The first string to compare.
;   right - The second string to compare.
;
; Returns:
;   -1 if left < right
;    0 if left == right
;    1 if left > right
;
; Notes:
;   Comparison is case-insensitive due to Papyrus string caching behavior.
;   This function is suitable for sorting and equality checks.
;---------------------------------------------------------------------------
Int      Function Compare(String left, String right) Global Native

;---------------------------------------------------------------------------
; Function: Equals
;
; Description:
;   Determines whether two strings are equal using a case-insensitive comparison.
;
; Parameters:
;   left  - The first string.
;   right - The second string.
;
; Returns:
;   True if the strings are considered equal, false otherwise.
;
; Notes:
;   This function should be preferred over the Papyrus '==' operator
;   when predictable string comparison is required.
;---------------------------------------------------------------------------
Bool     Function Equals(String left, String right) Global Native

;---------------------------------------------------------------------------
; Function: Search
;
; Description:
;   Searches for the first occurrence of a substring within a string.
;
; Parameters:
;   source - The string to search in.
;   needle - The substring to search for.
;
; Returns:
;   The zero-based index of the first occurrence of needle in source,
;   or -1 if not found.
;
; Notes:
;   Search is performed in a case-insensitive manner.
;---------------------------------------------------------------------------
Int      Function Search(String source, String needle) Global Native

;---------------------------------------------------------------------------
; Function: SearchReverse
;
; Description:
;   Searches for the last occurrence of a substring within a string.
;
; Parameters:
;   source - The string to search in.
;   needle - The substring to search for.
;
; Returns:
;   The zero-based index of the last occurrence of needle in source,
;   or -1 if not found.
;
; Notes:
;   Search is performed in a case-insensitive manner.
;---------------------------------------------------------------------------
Int      Function SearchReverse(String source, String needle) Global Native

;---------------------------------------------------------------------------
; Function: SearchIndex
;
; Description:
;   Searches for the first occurrence of a substring within a string,
;   starting from the specified index.
;
; Parameters:
;   source     - The string to search in.
;   needle     - The substring to search for.
;   startIndex - The index at which to begin searching.
;
; Returns:
;   The zero-based index of the first occurrence of needle at or after
;   startIndex, or -1 if not found.
;
; Notes:
;   Search is performed in a case-insensitive manner.
;---------------------------------------------------------------------------
Int      Function SearchIndex(String source, String needle, Int startIndex) Global Native

;---------------------------------------------------------------------------
; Function: SearchIndexReverse
;
; Description:
;   Searches for the last occurrence of a substring within a string,
;   searching backward from the specified index.
;
; Parameters:
;   source     - The string to search in.
;   needle     - The substring to search for.
;   startIndex - The index at which to begin searching backward.
;
; Returns:
;   The zero-based index of the last occurrence of needle at or before
;   startIndex, or -1 if not found.
;
; Notes:
;   Search is performed in a case-insensitive manner.
;---------------------------------------------------------------------------
Int      Function SearchIndexReverse(String source, String needle, Int startIndex) Global Native

;---------------------------------------------------------------------------
; Function: Contains
;
; Description:
;   Determines whether a string contains a substring.
;
; Parameters:
;   source - The string to search within.
;   needle - The substring to search for.
;
; Returns:
;   True if needle is found in source, otherwise false.
;
; Notes:
;   Case-insensitive.
;---------------------------------------------------------------------------
Bool     Function Contains(String source, String needle) Global Native

;---------------------------------------------------------------------------
; Function: StartsWith
;
; Description:
;   Checks whether a string begins with the specified prefix.
;
; Parameters:
;   source - The string to check.
;   prefix - The prefix to test.
;
; Returns:
;   True if source starts with prefix, otherwise false.
;
; Notes:
;   Case-insensitive.
;---------------------------------------------------------------------------
Bool     Function StartsWith(String source, String prefix) Global Native

;---------------------------------------------------------------------------
; Function: EndsWith
;
; Description:
;   Checks whether a string ends with the specified suffix.
;
; Parameters:
;   source - The string to check.
;   suffix - The suffix to test.
;
; Returns:
;   True if source ends with suffix, otherwise false.
;
; Notes:
;   Case-insensitive.
;---------------------------------------------------------------------------
Bool     Function EndsWith(String source, String suffix) Global Native

;---------------------------------------------------------------------------
; Function: Replace
;
; Description:
;   Replaces the first occurrence of a substring with another string.
;
; Parameters:
;   source      - The original string.
;   needle      - The substring to replace.
;   replacement - The string to insert.
;
; Returns:
;   A new string with the first occurrence replaced.
;
; Notes:
;   Case-insensitive search.
;---------------------------------------------------------------------------
String   Function Replace(String source, String needle, String replacement) Global Native

;---------------------------------------------------------------------------
; Function: ReplaceAll
;
; Description:
;   Replaces all occurrences of a substring with another string.
;
; Parameters:
;   source      - The original string.
;   needle      - The substring to replace.
;   replacement - The string to insert.
;
; Returns:
;   A new string with all occurrences replaced.
;
; Notes:
;   Case-insensitive search.
;---------------------------------------------------------------------------
String   Function ReplaceAll(String source, String needle, String replacement) Global Native

;---------------------------------------------------------------------------
; Function: ReplaceIndex
;
; Description:
;   Replaces a portion of a string at a specified index with a new string.
;
; Parameters:
;   source      - The original string.
;   startIndex  - The zero-based index at which to begin replacement.
;   count       - The number of characters to replace.
;   replacement - The string to insert at the specified position.
;
; Returns:
;   A new string with the specified range replaced.
;
; Notes:
;   This function operates purely by index and length and does not perform
;   any searching or comparison.
;
;   Index and count values are defensively clamped to valid ranges.
;   This function is unaffected by Papyrus string case-caching behavior.
;---------------------------------------------------------------------------
String   Function ReplaceIndex(String source, Int startIndex, Int count, String replacement) Global Native

;---------------------------------------------------------------------------
; Function: Substring
;
; Description:
;   Extracts a portion of a string starting at a given index.
;
; Parameters:
;   source     - The source string.
;   startIndex - Zero-based index to begin extraction.
;   count      - Number of characters to extract.
;
; Returns:
;   The extracted substring, or an empty string if invalid.
;---------------------------------------------------------------------------
String   Function Substring(String source, Int startIndex, Int count) Global Native

;---------------------------------------------------------------------------
; Function: CharAt
;
; Description:
;   Extracts a one character string starting at a given index.
;
; Parameters:
;   source     - The source string.
;   startIndex - Zero-based index to begin extraction.
;
; Returns:
;   The extracted one character string, or an empty string if invalid.
;---------------------------------------------------------------------------
String   Function CharAt(String source, Int startIndex) Global Native

;---------------------------------------------------------------------------
; Function: OrdinalAt
;
; Description:
;   Extracts a one character string starting at a given index and
;   converts that character into an ordinal value.
;
; Parameters:
;   source     - The source string.
;   startIndex - Zero-based index to begin extraction.
;
; Returns:
;   The extracted one character string as an ordinal. Returns -1 if invalid.
;---------------------------------------------------------------------------
Int      Function OrdinalAt(String source, Int startIndex) Global Native

;---------------------------------------------------------------------------
; Function: Remove
;
; Description:
;   Removes the first string found in another string.
;
; Parameters:
;   source     - The source string.
;   needle     - The needle string.
;
; Returns:
;   The modified string.
;---------------------------------------------------------------------------
String   Function Remove(String source, String needle) Global Native

;---------------------------------------------------------------------------
; Function: Remove
;
; Description:
;   Removes all the strings found in another string.
;
; Parameters:
;   source     - The source string.
;   needle     - The needle string.
;
; Returns:
;   The modified string.
;---------------------------------------------------------------------------
String   Function RemoveAll(String source, String needle) Global Native

;---------------------------------------------------------------------------
; Function: Reverse
;
; Description:
;   Returns a new string with the characters of the source string reversed.
;
; Parameters:
;   source - The original string.
;
; Returns:
;   A new string with characters in reverse order.
;
; Notes:
;   This function operates on character order only and performs no searching
;   or comparison.
;
;   Behavior is deterministic and unaffected by Papyrus string case-caching.
;---------------------------------------------------------------------------
String   Function Reverse(String source) Global Native

;---------------------------------------------------------------------------
; Function: Repeat
;
; Description:
;   Repeats the source string a specified number of times.
;
; Parameters:
;   source - The string to repeat.
;   count  - The number of times to repeat the string.
;
; Returns:
;   A new string containing the source string repeated count times.
;
; Notes:
;   If count is less than or equal to zero, an empty string is returned.
;
;   Internal safeguards prevent excessive memory usage.
;
;   Case behavior is inherited from the Papyrus string cache and should not
;   be relied upon.
;---------------------------------------------------------------------------
String   Function Repeat(String source, Int count) Global Native

;---------------------------------------------------------------------------
; Function: ToChar
;
; Description:
;   Converts a numeric ordinal value into a single-character string.
;
; Parameters:
;   ordinal - The numeric character code to convert.
;
; Returns:
;   A string containing the character represented by the given ordinal.
;
; Notes:
;   Ordinal values are interpreted as unsigned byte values (0–255).
;
;   Values outside the valid range may produce implementation-defined
;   results.
;---------------------------------------------------------------------------
String   Function ToChar(Int ordinal) Global Native

;---------------------------------------------------------------------------
; Function: ToTitleCase
;
; Description:
;   Converts a string to title case (capitalizes the first letter of each word).
;
; Parameters:
;   source - The string to convert.
;
; Returns:
;   The title-cased string.
;
; Notes:
;   Word boundaries include whitespace and punctuation such as '-' and '_'.
;---------------------------------------------------------------------------
String   Function ToTitleCase(String source) Global Native

;---------------------------------------------------------------------------
; Function: ToOrdinal
;
; Description:
;   Converts the first character of a string into its ASCII ordinal value.
;
; Parameters:
;   source - The source string.
;
; Returns:
;   The ASCII ordinal value (0–255) of the first character in the string.
;
; Notes:
;   If source is empty, 0 is returned.
;
;   Due to Papyrus string caching, the character used may not reflect the
;   original case of the input string.
;---------------------------------------------------------------------------
Int      Function ToOrdinal(String source) Global Native

;---------------------------------------------------------------------------
; Function: TrimStart
;
; Description:
;   Removes all leading whitespace characters from the start of a string.
;
; Parameters:
;   source - The source string.
;
; Returns:
;   A new string with leading whitespace removed.
;
; Notes:
;   Whitespace is determined using standard ASCII whitespace classification.
;
;   Case of the returned string is subject to Papyrus string caching behavior.
;---------------------------------------------------------------------------
String   Function TrimStart(String source) Global Native

;---------------------------------------------------------------------------
; Function: TrimEnd
;
; Description:
;   Removes all trailing whitespace characters from the end of a string.
;
; Parameters:
;   source - The source string.
;
; Returns:
;   A new string with trailing whitespace removed.
;
; Notes:
;   Whitespace is determined using standard ASCII whitespace classification.
;
;   Case of the returned string is subject to Papyrus string caching behavior.
;---------------------------------------------------------------------------
String   Function TrimEnd(String source) Global Native

;---------------------------------------------------------------------------
; Function: TrimBoth
;
; Description:
;   Removes all leading and trailing whitespace characters from a string.
;
; Parameters:
;   source - The source string.
;
; Returns:
;   A new string with both leading and trailing whitespace removed.
;
; Notes:
;   Equivalent to calling TrimStart followed by TrimEnd.
;
;   Whitespace is determined using standard ASCII whitespace classification.
;
;   Case of the returned string is subject to Papyrus string caching behavior.
;---------------------------------------------------------------------------
String   Function TrimBoth(String source) Global Native

;---------------------------------------------------------------------------
; Function: IsAlpha
;
; Description:
;   Returns true if all characters in the string are alphabetic (A-Z, a-z).
;
; Parameters:
;   source - The string to check.
;
; Returns:
;   True if all characters are alphabetic, false otherwise.
;
; Notes:
;   Empty strings return false.
;   Case is subject to Papyrus string caching behavior.
;---------------------------------------------------------------------------
Bool     Function IsAlpha(String source) Global Native

;---------------------------------------------------------------------------
; Function: IsDigit
;
; Description:
;   Returns true if all characters in the string are decimal digits (0-9).
;
; Parameters:
;   source - The string to check.
;
; Returns:
;   True if all characters are digits, false otherwise.
;
; Notes:
;   Empty strings return false.
;---------------------------------------------------------------------------
Bool     Function IsDigit(String source) Global Native

;---------------------------------------------------------------------------
; Function: IsHex
;
; Description:
;   Returns true if all characters in the string are valid hexadecimal digits
;   (0-9, A-F, a-f).
;
; Parameters:
;   source - The string to check.
;
; Returns:
;   True if all characters are valid hex digits, false otherwise.
;
; Notes:
;   Empty strings return false.
;   Case is subject to Papyrus string caching behavior.
;---------------------------------------------------------------------------
Bool     Function IsHex(String source) Global Native

;---------------------------------------------------------------------------
; Function: IsAlphaNumeric
;
; Description:
;   Returns true if all characters in the string are alphabetic or decimal digits.
;
; Parameters:
;   source - The string to check.
;
; Returns:
;   True if all characters are alphanumeric, false otherwise.
;
; Notes:
;   Empty strings return false.
;   Case is subject to Papyrus string caching behavior.
;---------------------------------------------------------------------------
Bool     Function IsAlphaNumeric(String source) Global Native

;---------------------------------------------------------------------------
; Function: IsWhitespace
;
; Description:
;   Returns true if all characters in the string are whitespace characters
;   (space, tab, etc.).
;
; Parameters:
;   source - The string to check.
;
; Returns:
;   True if all characters are whitespace, false otherwise.
;
; Notes:
;   Empty strings return false.
;---------------------------------------------------------------------------
Bool     Function IsWhitespace(String source) Global Native

;---------------------------------------------------------------------------
; Function: IsPunctuation
;
; Description:
;   Returns true if all characters in the string are punctuation characters.
;
; Parameters:
;   source - The string to check.
;
; Returns:
;   True if all characters are punctuation, false otherwise.
;
; Notes:
;   Empty strings return false.
;   Punctuation is determined using standard ASCII classification.
;---------------------------------------------------------------------------
Bool     Function IsPunctuation(String source) Global Native

;---------------------------------------------------------------------------
; Function: IsASCII
;
; Description:
;   Returns true if all characters in the string are valid ASCII characters
;   (0-127).
;
; Parameters:
;   source - The string to check.
;
; Returns:
;   True if all characters are ASCII, false otherwise.
;
; Notes:
;   Empty strings return false.
;---------------------------------------------------------------------------
Bool     Function IsASCII(String source) Global Native

;---------------------------------------------------------------------------
; Function: IsControl
;
; Description:
;   Returns true if all characters in the string are control characters
;   (ASCII 0-31, 127).
;
; Parameters:
;   source - The string to check.
;
; Returns:
;   True if all characters are control characters, false otherwise.
;
; Notes:
;   Empty strings return false.
;---------------------------------------------------------------------------
Bool     Function IsControl(String source) Global Native

;---------------------------------------------------------------------------
; Function: IsPrintable
;
; Description:
;   Returns true if all characters in the string are printable ASCII characters
;   (32-126).
;
; Parameters:
;   source - The string to check.
;
; Returns:
;   True if all characters are printable, false otherwise.
;
; Notes:
;   Empty strings return false.
;---------------------------------------------------------------------------
Bool     Function IsPrintable(String source) Global Native

;---------------------------------------------------------------------------
; Function: IsGraph
;
; Description:
;   Returns true if all characters in the string are graphical characters
;   (printable and not space).
;
; Parameters:
;   source - The string to check.
;
; Returns:
;   True if all characters are graphical, false otherwise.
;
; Notes:
;   Empty strings return false.
;---------------------------------------------------------------------------
Bool     Function IsGraph(String source) Global Native

;---------------------------------------------------------------------------
; Function: Join
;
; Description:
;   Concatenates an array of strings into a single string, inserting the
;   specified delimiter between each element.
;
; Parameters:
;   parts     - The array of strings to join.
;   delimiter - The string inserted between each element.
;
; Returns:
;   A single string consisting of all elements in parts separated by the
;   delimiter.
;
; Notes:
;   If parts is empty, an empty string is returned.
;
;   If delimiter is an empty string, the elements are concatenated directly.
;
;   Case behavior of the result is subject to Papyrus string caching and
;   should not be relied upon.
;---------------------------------------------------------------------------
String   Function Join(String[] parts, String delimiter) Global Native

;---------------------------------------------------------------------------
; Function: Split
;
; Description:
;   Splits a string into an array of substrings using the specified delimiter.
;
; Parameters:
;   source    - The string to split.
;   delimiter - The string used to separate elements.
;
; Returns:
;   An array of substrings extracted from the source string.
;
; Notes:
;   If delimiter is an empty string, the source string is split into individual
;   characters.
;
;   Consecutive delimiters will produce empty string elements in the result.
;
;   Case-insensitive behavior applies when locating delimiters, consistent
;   with other search operations in this library.
;
;   The case of returned substrings is subject to Papyrus string caching and
;   should not be relied upon.
;---------------------------------------------------------------------------
String[] Function Split(String source, String delimiter) Global Native

;---------------------------------------------------------------------------
; Function: OrdinalJoin
;
; Description:
;   Builds a string from an array of character ordinal values.
;
; Parameters:
;   parts - Array of character ordinals.
;
; Returns:
;   The constructed string.
;---------------------------------------------------------------------------
String   Function OrdinalJoin(Int[] parts) Global Native

;---------------------------------------------------------------------------
; Function: OrdinalSplit
;
; Description:
;   Splits a string into an array of character ordinal values.
;
; Parameters:
;   source - The string to split.
;
; Returns:
;   An array of integer character ordinals.
;---------------------------------------------------------------------------
Int[]    Function OrdinalSplit(String source) Global Native

;---------------------------------------------------------------------------
; Function: Sort
;
; Description:
;   Sorts an array of strings using case-insensitive comparison.
;
; Parameters:
;   parts - The array of strings to sort.
;
; Returns:
;   A new sorted array of strings.
;
; Notes:
;   Sorting is case-insensitive and stable.
;---------------------------------------------------------------------------
String[] Function Sort(String[] parts) Global Native
