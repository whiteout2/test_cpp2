#include <iostream>
#include <compare>
#include <iomanip>

#include <fmt/core.h>
#include <fmt/color.h>

#include <string.h>

// declarations
char *trim(char *p);

using namespace std;

int main()
{
    int x = 2;

    if (x<=>1 > 0) {
        std::cout << "Test!\n";
    }

    fmt::print("The answer is {}.\n", 42);

    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
             "Hello, {}!\n", "world");
    fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
             fmt::emphasis::underline, "Hello, {}!\n", "мир");
    fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
             "Hello, {}!\n", "世界");


    string str1 = "Hello, ";
    string str2 = "world!\n";

    cout << "cout: " + str1 + str2;
    fmt::print("fmt: {}{}", str1, str2);
    fmt::print("fmt: {}", str1+str2);

    // printf
    printf("%0.10f:%04d:%+g:%s:%p:%c:%%\n",
                1.234, 42, 3.13, "str", (void*)1000, (int)'X');

    // iostreams (What a mess! chevron hell)
    std::cout << std::setprecision(10) << std::fixed << 1.234 << ':'
                << std::resetiosflags(std::ios::floatfield)
                << std::setw(4) << std::setfill('0') << 42 << std::setfill(' ') << ':'
                << std::setiosflags(std::ios::showpos) << 3.13 << std::resetiosflags(std::ios::showpos) << ':'
                << "str" << ':'
                << (void*)1000 << ':'
                << 'X' << ":%\n";

    // fmt
    fmt::print("{:.10f}:{:04}:{:+}:{}:{}:{}:%\n",
                1.234, 42, 3.13, "str", (void*)1000, 'X');


    // TEST: string manipulation in C and C++
    // Always easy in JS, C# and PHP.
    // String: ADCX — Unsigned Integer Addition of Two Operands with Carry Flag
    // var txt = "ADCX %E2%80%94 Unsigned Integer Addition of Two Operands with Carry Flag"
    // var mnemonic = decodeURIComponent( txt.split('%E2%80%94')[0] ).trim();
    // var summary  = decodeURIComponent( txt.split('%E2%80%94')[1] ).trim();

    // In C:
    char *token;
    char line[] = "ADCX %E2%80%94 Unsigned Integer Addition of Two Operands with Carry Flag";
    char search[] = "%E2%80%94";

    // NOTE: strtok() will modify the string
    token = strtok(line, search);
    char *mnemonic = token;
    token = strtok(NULL, search);
    char *summary = token;

    printf("%s\n", mnemonic);
    printf("%s\n", summary);

    // Roll your own trim()
    // See: https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
    printf("%s\n", trim(mnemonic));
    printf("%s\n", trim(summary));     


    std::cout << std::flush;
    int dummy = 0;

    return 0;
}


// NOTE: isspace() needs (unsigned char) but who cares?
char *trim(char *str)
{
    char *p = str, *q = str;
    while (isspace(*p)) p++;
    while (*q) q++;
    while (q > str && isspace(*--q)) *q = 0;
    return p;
}