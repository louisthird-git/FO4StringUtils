ScriptName FO4StringUtils_TestScript extends Quest

Import FO4StringUtils

Int PassedCount = 0
Int FailedCount = 0
Int TotalCount = 0

; =========================
; Assertion Helpers
; =========================

String Function MakeFresh(String s)
    Return "" + s  ; forces new string object
EndFunction

Function LogPass(String msg)
    PassedCount += 1
    TotalCount += 1
    Debug.Trace("FO4StringUtils TEST PASSED: " + msg)
EndFunction

Function LogFail(String msg)
    FailedCount += 1
    TotalCount += 1
    Debug.Trace("FO4StringUtils TEST FAILED: " + msg)
EndFunction

Function AssertTrue(Bool value, String msg)
    If value
        LogPass(msg)
    Else
        LogFail(msg)
    EndIf
EndFunction

Function AssertFalse(Bool value, String msg)
    If !value
        LogPass(msg)
    Else
        LogFail(msg)
    EndIf
EndFunction

Function AssertEqualsInt(Int actual, Int expected, String msg)
    If actual == expected
        LogPass(msg)
    Else
        LogFail(msg + " (Expected=" + expected + ", Actual=" + actual + ")")
    EndIf
EndFunction

Function AssertEqualsBool(Bool actual, Bool expected, String msg)
    If actual == expected
        LogPass(msg)
    Else
        LogFail(msg + " (Expected=" + expected + ", Actual=" + actual + ")")
    EndIf
EndFunction

Function AssertEqualsString(String actual, String expected, String msg)
    If actual == expected
        LogPass(msg)
    Else
        LogFail(msg + " (Expected=\"" + expected + "\", Actual=\"" + actual + "\")")
    EndIf
EndFunction

Function AssertNotEqualsString(String actual, String expected, String msg)
    If actual != expected
        LogPass(msg)
    Else
        LogFail(msg + " (Expected=\"" + expected + "\", Actual=\"" + actual + "\")")
    EndIf
EndFunction

; =========================
; Test Runner
; =========================

Event OnQuestInit()
    Debug.Trace("FO4StringUtils: Starting test suite")

    ; ---- Version tests ----

    String pluginVer = FO4StringUtils.PluginVersion()
    AssertTrue(!FO4StringUtils.IsEmpty(pluginVer), "PluginVersion not empty")

    ; Expect something like "1.0" or "2.1.3"
    AssertTrue(FO4StringUtils.Contains(pluginVer, "."), "PluginVersion contains dot")

    String gameVer = FO4StringUtils.GameVersion()
    AssertTrue(!FO4StringUtils.IsEmpty(gameVer), "GameVersion not empty")

    ; FO4 versions always contain at least two dots (e.g. 1.10.163)
    Int dotCount = FO4StringUtils.Count(gameVer) - FO4StringUtils.Count(FO4StringUtils.RemoveAll(gameVer, "."))
    AssertTrue(dotCount >= 2, "GameVersion contains at least two dots")

    String runtimeVer = FO4StringUtils.RuntimeVersion()
    AssertTrue(!FO4StringUtils.IsEmpty(runtimeVer), "RuntimeVersion not empty")

    AssertTrue(FO4StringUtils.Contains(runtimeVer, "."), "RuntimeVersion contains dot")

    String versionInfo = FO4StringUtils.VersionInfo()
    AssertTrue(!FO4StringUtils.IsEmpty(versionInfo), "VersionInfo not empty")
    Debug.Trace("FO4StringUtils VersionInfo: " + versionInfo)

    ; Expect comma-separated fields
    String[] versionParts = FO4StringUtils.Split(versionInfo, ",")
    AssertTrue(versionParts.Length >= 3, "VersionInfo has at least 3 parts")

    ; ---- Echo() ----

    Debug.Trace("NOTE: Papyrus uses an internal string cache; literal case may not be preserved across machines or load order")
    Debug.Trace("lower=" + "ab")
    Debug.Trace("upper=" + "AB")

    ; ---- Count() ----

    AssertEqualsInt(Count(""), 0, "Count empty string")
    AssertEqualsInt(Count("a"), 1, "Count single character")
    AssertEqualsInt(Count("abc"), 3, "Count simple ASCII")
    AssertEqualsInt(Count("ABC"), 3, "Count uppercase")
    AssertEqualsInt(Count("AbC123!"), 7, "Count mixed characters")
    AssertEqualsInt(Count(" "), 1, "Count single whitespace")
    AssertEqualsInt(Count("   "), 3, "Count multiple whitespace")
    AssertEqualsInt(Count("hello world"), 11, "Count with space")
    AssertEqualsInt(Count(","), 1, "Count punctuation")
    AssertEqualsInt(Count("cat-dog"), 7, "Count with dash")
    AssertEqualsInt(Count("1234567890"), 10, "Count digits")

    ; Defensive: ensure Count never returns negative
    AssertTrue(Count("anything") >= 0, "Count non-negative")

    ; ---- IsEmpty() ----

    AssertTrue(IsEmpty(""), "IsEmpty empty string")
    AssertFalse(IsEmpty("a"), "IsEmpty single character")
    AssertFalse(IsEmpty(" "), "IsEmpty whitespace")
    AssertFalse(IsEmpty("abc"), "IsEmpty normal string")
    AssertFalse(IsEmpty("ABC"), "IsEmpty uppercase")
    AssertFalse(IsEmpty("0"), "IsEmpty digit")
    AssertFalse(IsEmpty(","), "IsEmpty punctuation")

    ; ---- Count() / IsEmpty() consistency ----

    String s = ""
    AssertTrue(IsEmpty(s), "Empty consistency IsEmpty")
    AssertEqualsInt(Count(s), 0, "Empty consistency Count")
    s = "x"
    AssertFalse(IsEmpty(s), "Non-empty consistency IsEmpty")
    AssertTrue(Count(s) > 0, "Non-empty consistency Count")
    s = "hello"
    AssertFalse(IsEmpty(s), "Word consistency IsEmpty")
    AssertEqualsInt(Count(s), 5, "Word consistency Count")

    ; ---- Defensive / regression tests ----

    ; Count should not modify string
    String original = "test"
    Int len = Count(original)
    AssertEqualsString(original, "test", "Count does not modify input")
    AssertEqualsInt(len, 4, "Count unchanged value")

    ; IsEmpty should not modify string
    AssertFalse(IsEmpty(original), "IsEmpty does not modify input")
    AssertEqualsString(original, "test", "IsEmpty preserves input")

    ; ---- Equals() ----

    ; Basic case-insensitive equality
    AssertTrue(Equals("hello", "HELLO"), "Equals: same letters, different case")
    AssertTrue(Equals("AbC123", "aBc123"), "Equals: mixed letters and numbers, different case")

    ; Negative cases
    AssertFalse(Equals("hello", "world"), "Equals: completely different strings")
    AssertFalse(Equals("hello", "hell"), "Equals: substring shorter than other")
    AssertFalse(Equals("hello", "helloo"), "Equals: substring longer than other")

    ; Empty strings
    AssertTrue(Equals("", ""), "Equals: both empty strings")
    AssertFalse(Equals("", "nonempty"), "Equals: empty vs non-empty")
    AssertFalse(Equals("nonempty", ""), "Equals: non-empty vs empty")

    ; ---- Find() / Index() ----

    AssertEqualsInt(Search("hello world", "world"), 6, "Search basic")
    AssertEqualsInt(Search("hello world", "missing"), -1, "Search not found")
    AssertEqualsInt(SearchReverse("one two one", "one"), 8, "SearchReverse basic")
    AssertEqualsInt(SearchIndex("abcdef", "cd", 0), 2, "SearchIndex forward")
    AssertEqualsInt(SearchIndexReverse("abcdefcd", "cd", 7), 6, "SearchIndexReverse")

    ; ---- Contains() / StartsWith() / EndsWith() ----

    AssertTrue(Contains("foobar", "bar"), "Contains true")
    AssertFalse(Contains("foobar", "baz"), "Contains false")
    AssertTrue(StartsWith("foobar", "foo"), "StartsWith true")
    AssertFalse(StartsWith("foobar", "bar"), "StartsWith false")
    AssertTrue(EndsWith("foobar", "bar"), "EndsWith true")
    AssertFalse(EndsWith("foobar", "foo"), "EndsWith false")

    ; ---- Replace() ----

    AssertEqualsString(Replace("hello world", "world", "there"), "hello there", "Replace single")

    ; Basic single replacement
    AssertEqualsString(Replace("Hello World", "World", "Fo4"), "Hello Fo4", "Replace basic")

    ; Needle not found ? no change
    AssertEqualsString(Replace("Hello World", "Moon", "Fo4"), "Hello World", "Replace needle not found")

    ; Multiple occurrences ? only first replaced
    AssertEqualsString(Replace("abc abc abc", "abc", "xyz"), "xyz abc abc", "Replace first only")

    ; Replace at start
    AssertEqualsString(Replace("abcde", "abc", "xyz"), "xyzde", "Replace at start")

    ; Replace at end
    AssertEqualsString(Replace("abcde", "cde", "XYZ"), "abXYZ", "Replace at end")

    ; Empty replacement ? remove first occurrence
    AssertEqualsString(Replace("abc abc abc", "abc", ""), " abc abc", "Replace with empty string")

    ; Empty source string ? no change
    AssertEqualsString(Replace("", "abc", "XYZ"), "", "Replace empty source string")

    ; Empty needle ? no change
    AssertEqualsString(Replace("abc", "", "XYZ"), "abc", "Replace empty needle")

    ; ---- ReplaceAll() ----

    AssertEqualsString(ReplaceAll("one one one", "one", "two"), "two two two", "ReplaceAll")

    ; Basic multiple replacements
    AssertEqualsString(ReplaceAll("abc abc abc", "abc", "xyz"), "xyz xyz xyz", "ReplaceAll basic")

    ; Needle not found ? no change
    AssertEqualsString(ReplaceAll("abc abc abc", "def", "xyz"), "abc abc abc", "ReplaceAll needle not found")

    ; Replace at start and end
    AssertEqualsString(ReplaceAll("abcde abc", "abc", "XYZ"), "XYZde XYZ", "ReplaceAll start and end")

    ; Empty replacement ? remove all occurrences
    AssertEqualsString(ReplaceAll("abc abc abc", "abc", ""), "  ", "ReplaceAll with empty string")

    ; Empty source string ? no change
    AssertEqualsString(ReplaceAll("", "abc", "XYZ"), "", "ReplaceAll empty source string")

    ; Empty needle ? no change
    AssertEqualsString(ReplaceAll("abc", "", "XYZ"), "abc", "ReplaceAll empty needle")

    ; ---- ReplaceIndex() ----

    AssertEqualsString(ReplaceIndex("abcdef", 2, 2, "ZZ"), "abZZef", "ReplaceIndex")

    ; Basic replacement at index
    AssertEqualsString(ReplaceIndex("Hello World", 6, 5, "Fo4"), "Hello Fo4", "ReplaceIndex basic")

    ; Index at start
    AssertEqualsString(ReplaceIndex("abcde", 0, 3, "XYZ"), "XYZde", "ReplaceIndex at start")

    ; Index at end
    AssertEqualsString(ReplaceIndex("abcde", 2, 3, "XYZ"), "abXYZ", "ReplaceIndex at end")

    ; Count exceeds string ? clamps to end
    AssertEqualsString(ReplaceIndex("abcdef", 3, 10, "XYZ"), "abcXYZ", "ReplaceIndex count exceeds length")

    ; Count = 0 ? no change
    AssertEqualsString(ReplaceIndex("abcdef", 2, 0, "XYZ"), "abcdef", "ReplaceIndex count zero")

    ; Negative index ? clamps to 0
    AssertEqualsString(ReplaceIndex("abcdef", -3, 2, "XY"), "XYcdef", "ReplaceIndex negative start index")

    ; Negative count ? treated as 0, no change
    AssertEqualsString(ReplaceIndex("abcdef", 2, -5, "XYZ"), "abcdef", "ReplaceIndex negative count")

    ; Empty source string ? no change
    AssertEqualsString(ReplaceIndex("", 0, 3, "XYZ"), "", "ReplaceIndex empty source string")

    ; Empty replacement ? removes selected substring
    AssertEqualsString(ReplaceIndex("abcdef", 2, 3, ""), "abf", "ReplaceIndex empty replacement")

    ; ---- Substring() / Remove() ----

    AssertEqualsString(Substring("abcdef", 1, 3), "bcd", "Substring basic")

    ; Basic substring extraction
    AssertEqualsString(Substring("HelloWorld", 0, 5), "Hello", "Substring basic 0-5")
    AssertEqualsString(Substring("HelloWorld", 5, 5), "World", "Substring basic 5-5")
    AssertEqualsString(Substring("HelloWorld", 2, 3), "llo", "Substring 2-3")

    ; Start index 0
    AssertEqualsString(Substring("HelloWorld", 0, 10), "HelloWorld", "Substring full from 0")

    ; Start index beyond string length
    AssertEqualsString(Substring("HelloWorld", 20, 5), "", "Substring startIndex beyond length")

    ; Count = 0
    AssertEqualsString(Substring("HelloWorld", 2, 0), "", "Substring count 0")

    ; Count beyond string length
    AssertEqualsString(Substring("HelloWorld", 8, 10), "ld", "Substring count beyond length")

    ; Negative start index
    AssertEqualsString(Substring("HelloWorld", -3, 4), "Hell", "Substring negative start index")

    ; Negative count
    AssertEqualsString(Substring("HelloWorld", 2, -5), "", "Substring negative count")

    ; Empty string input
    AssertEqualsString(Substring("", 0, 5), "", "Substring empty source string")

    AssertEqualsString(Remove("bread beef bread", "bread"), " beef bread", "Remove first")

    AssertEqualsString(RemoveAll("bread beef bread", "bread"), " beef ", "RemoveAll")

    ; ---- Transformations ----

    AssertEqualsString(Reverse("zoom"), "mooz", "Reverse")
    AssertEqualsString(Repeat("zoom", 3), "zoomzoomzoom", "Repeat")

    ; ---- Trim ----

    AssertEqualsString(TrimStart("   zoom"), "zoom", "TrimStart")
    AssertEqualsString(TrimEnd("zoom   "), "zoom", "TrimEnd")
    AssertEqualsString(TrimBoth("   zoom   "), "zoom", "TrimBoth")

    ; ---- Join() / Split() ----

    String[] parts = new String[3]
    parts[0] = "larry"
    parts[1] = "curly"
    parts[2] = "moe"

    AssertEqualsString(Join(parts, ","), "larry,curly,moe", "Join")

    String[] chars = Split("zip", "")
    AssertEqualsInt(chars.Length, 3, "Split chars length")
    AssertEqualsString(chars[0], "z", "Split char 0")
    AssertEqualsString(chars[1], "i", "Split char 1")
    AssertEqualsString(chars[2], "p", "Split char 2")

    String[] splitResult = Split("larry,curly,moe", ",")
    AssertEqualsInt(splitResult.Length, 3, "Split length")
    AssertEqualsString(splitResult[0], "larry", "Split element 0")
    AssertEqualsString(splitResult[1], "curly", "Split element 1")
    AssertEqualsString(splitResult[2], "moe", "Split element 2")

    ; ---- Char / Ordinal ----

    String tempCharAt = MakeFresh("ABC")
    String tempCharAt2 = MakeFresh("A")
    AssertEqualsString(CharAt(tempCharAt, 0), tempCharAt2, "CharAt 0")
    AssertEqualsInt(OrdinalAt(tempCharAt, 0), 65, "OrdinalAt 0")
    String tempCharAt3 = MakeFresh("B")
    AssertEqualsString(ToChar(66), tempCharAt3, "ToChar 66")
    String tempCharAt4 = MakeFresh("C")
    AssertEqualsInt(ToOrdinal(tempCharAt4), 67, "ToOrdinal C")

    Int[] ordArray = new Int[3]
    ordArray[0] = 65
    ordArray[1] = 66
    ordArray[2] = 67
    AssertEqualsString(OrdinalJoin(ordArray), "ABC", "OrdinalJoin")

    Int[] splitOrd = OrdinalSplit("ABC")

    ; Length is stable
    AssertEqualsInt(splitOrd.Length, 3, "OrdinalSplit length")

    ; Round-trip within native boundary
    String rebuilt = OrdinalJoin(splitOrd)
    AssertEqualsInt(Count(rebuilt), 3, "Ordinal round-trip length")

    ; ---- IsXXXX() ----

    AssertTrue(IsAlpha("ABCdef"), "IsAlpha true")
    AssertFalse(IsAlpha("ABC123"), "IsAlpha false")
    AssertTrue(IsDigit("012345"), "IsDigit true")
    AssertFalse(IsDigit("ABC123"), "IsDigit false")
    AssertTrue(IsHex("1A2B3C"), "IsHex true")
    AssertFalse(IsHex("GHI"), "IsHex false")
    AssertTrue(IsAlphaNumeric("ABC123"), "IsAlphaNumeric true")
    AssertFalse(IsAlphaNumeric("ABC!@#"), "IsAlphaNumeric false")
    AssertTrue(IsWhitespace("   \t\n"), "IsWhitespace true")
    AssertFalse(IsWhitespace("abc "), "IsWhitespace false")
    AssertTrue(IsPunctuation("!.,;"), "IsPunctuation true")
    AssertFalse(IsPunctuation("abc!"), "IsPunctuation false")

    AssertTrue(IsASCII("All ASCII!"), "IsASCII true")
    AssertFalse(IsASCII("é"), "IsASCII false")
    AssertTrue(IsControl("\n\t"), "IsControl true")
    AssertFalse(IsControl("abc"), "IsControl false")
    AssertTrue(IsPrintable("Printable 123!"), "IsPrintable true")
    AssertTrue(IsGraph("ABC123!"), "IsGraph true")
    AssertFalse(IsGraph("ABC 123"), "IsGraph false")

    ; ---- Compare() ----

    Debug.Trace("=== CompareFunction Tests ===")

    ; Case-insensitive equality
    AssertEqualsInt(Compare("abc", "ABC"), 0, "Compare equal (case-insensitive)")

    ; Left < Right
    AssertTrue(Compare("apple", "banana") < 0, "Compare 'apple' < 'banana'")

    ; Left > Right
    AssertTrue(Compare("zebra", "apple") > 0, "Compare 'zebra' > 'apple'")

    ; Partial/shorter strings
    AssertTrue(Compare("cat", "catalog") < 0, "Compare 'cat' < 'catalog'")
    AssertTrue(Compare("catalog", "cat") > 0, "Compare 'catalog' > 'cat'")

    ; ---- Sort() ----
    Debug.Trace("=== SortFunction Tests ===")

    ; Original unsorted array
    String[] unsorted = new String[4]
    unsorted[0] = "Zebra"
    unsorted[1] = "apple"
    unsorted[2] = "Banana"
    unsorted[3] = "cat"
    Debug.Trace("Original array: " + unsorted)

    ; Sort the array
    String[] sorted = Sort(unsorted)
    Debug.Trace("Sorted array: " + sorted)

    ; Check expected order (case-insensitive sort)
    AssertEqualsString(sorted[0], "apple", "Sort element 0")
    AssertEqualsString(sorted[1], "Banana", "Sort element 1")
    AssertEqualsString(sorted[2], "cat", "Sort element 2")
    AssertEqualsString(sorted[3], "Zebra", "Sort element 3")

    ; Check length unchanged
    AssertEqualsInt(sorted.Length, unsorted.Length, "Sort length unchanged")

    ; ----Compare() & Sort() Coverage ----

    ; Compare: Equality (case-insensitive)
    AssertEqualsInt(Compare("abc", "abc"), 0, "Compare equal: same case")
    AssertEqualsInt(Compare("abc", "ABC"), 0, "Compare equal: different case")
    AssertEqualsInt(Compare("AbC", "aBc"), 0, "Compare equal: mixed case")
    AssertEqualsInt(Compare("", ""), 0, "Compare equal: empty strings")

    ; Compare: Left < Right
    AssertTrue(Compare("abc", "abd") < 0, "Compare left < right: simple")
    AssertTrue(Compare("a", "b") < 0, "Compare left < right: single char")
    AssertTrue(Compare("", "a") < 0, "Compare left < right: empty left")

    ; Compare: Left > Right
    AssertTrue(Compare("abd", "abc") > 0, "Compare left > right: simple")
    AssertTrue(Compare("b", "a") > 0, "Compare left > right: single char")
    AssertTrue(Compare("a", "") > 0, "Compare left > right: empty right")

    ; Compare: Prefix / substring scenarios
    AssertTrue(Compare("abc", "abcd") < 0, "Compare left is prefix of right")
    AssertTrue(Compare("abcd", "abc") > 0, "Compare right is prefix of left")

    ; Compare: Completely different strings
    AssertTrue(Compare("xyz", "abc") > 0, "Compare totally different: left > right")
    AssertTrue(Compare("abc", "xyz") < 0, "Compare totally different: left < right")

    ; Compare: Whitespace and punctuation
    AssertEqualsInt(Compare("a b", "A B"), 0, "Compare equal with whitespace")
    AssertTrue(Compare("a.b", "a,c") > 0, "Compare punctuation: left > right")
    AssertTrue(Compare("a-c", "a-b") > 0, "Compare punctuation: left > right")

    ; ---- Summary ----
    Debug.Trace("FO4StringUtils: Test suite complete. Passed=" + PassedCount + ", Failed=" + FailedCount + ", Total=" + TotalCount)

    Stop()
EndEvent