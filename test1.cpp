#include <iostream>
#include <compare>
#include <iomanip>
#include <vector>

#include <fmt/core.h>
#include <fmt/color.h>

#include <string.h>

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>


using namespace std;

// declarations
char *trim(char *str);

string& trim2(string& s);
vector<string> split(string s, string delimiter);


// the code
// See: https://yosefk.com/c++fqa/defective.html#defect-12
typedef std::map<std::string,std::string> StringToStringMap;

void print(const StringToStringMap& dict) {
    //for(StringToStringMap::iterator p=dict.begin(); p!=dict.end(); ++p) { // error
    //for(StringToStringMap::const_iterator p=dict.begin(); p!=dict.end(); ++p) { // OK   
    for(auto p=dict.begin(); p!=dict.end(); ++p) { // OK
        std::cout << p->first << " -> " << p->second << std::endl;
    }
}

// error: no viable conversion from 
// 'std::__1::map<std::__1::basic_string<char>, std::__1::basic_string<char>>::const_iterator' 
// (aka '__map_const_iterator<__tree_const_iterator<std::__1::__value_type<std::__1::basic_string<char>, std::__1::basic_string<char>>, std::__1::__tree_node<std::__1::__value_type<std::__1::basic_string<char>, std::__1::basic_string<char>>, void *> *, long>>') 
// to 'StringToStringMap::iterator' 
// (aka '__map_iterator<__tree_iterator<std::__1::__value_type<std::__1::basic_string<char>, std::__1::basic_string<char>>, std::__1::__tree_node<std::__1::__value_type<std::__1::basic_string<char>, std::__1::basic_string<char>>, void *> *, long>>')
// 
// for(StringToStringMap::iterator p=dict.begin(); p!=dict.end(); ++p) {
//                                 ^ ~~~~~~~~~~~~
// dict.begin() == const_iterator
// StringToStringMap::iterator p == iterator


// Chevron hell redux:
// See: https://yosefk.com/c++fqa/defective.html#defect-7
// You may think it's a StringToStringMap, but only until the tools enlighten you - it's actually more of a...
//
// // don't read this, it's impossible. just count the lines
// std::map<std::basic_string<char, std::char_traits<char>, std::allocator<char> >,
// std::basic_string<char, std::char_traits<char>, std::allocator<char> >,
// std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> >
//   >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>,
// std::allocator<char> > const, std::basic_string<char, std::char_traits<char>,
// std::allocator<char> > > > >
//
// map<basic_string<char, char_traits<char>, allocator<char> >,
//     basic_string<char, char_traits<char>, allocator<char> >,
//     less<basic_string<char, char_traits<char>, allocator<char> > >,
//     allocator<pair<basic_string<char, char_traits<char>, allocator<char> > const,
//                    basic_string<char, char_traits<char>, allocator<char> > > > >
//  

// NOTE: to get angle bracket pairing in vscode to work change:
// /Applications/Visual Studio Code.app/Contents/Resources/app/extensions/cpp/language-configuration.json
// See: https://stackoverflow.com/questions/62068072/how-to-activate-automatic-angle-bracket-pairing-completion-in-visual-studio
// Layout like JSON makes templates more readable
map<basic_string<char, char_traits<char>, allocator<char>>,
    basic_string<char, char_traits<char>, allocator<char>>,
    less<basic_string<char, char_traits<char>, allocator<char>>>,
    allocator<pair<basic_string<char, char_traits<char>, allocator<char>> const,
                   basic_string<char, char_traits<char>, allocator<char>>>>> my_map2;

map<
    basic_string<char, char_traits<char>, allocator<char>>,
    basic_string<char, char_traits<char>, allocator<char>>,
    less<
        basic_string<char, char_traits<char>, allocator<char>>
    >,
    allocator<
        pair<
            basic_string<char, char_traits<char>, allocator<char>> const,
            basic_string<char, char_traits<char>, allocator<char>>
        >
    >
> my_map3;




int main()
{
    int x = 2;

    if ((x<=>1) > 0) {
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
    // We need the equivalent of split() and trim()
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
    ///////////////////////////////////


    // In C++
    string line2 = "ADCX %E2%80%94 Unsigned Integer Addition of Two Operands with Carry Flag";
    string search2 = "%E2%80%94";

    // Roll your own split() Really?
    // See: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    // Let's not use boost, regex, templates, lambdas or ranges
    string mnemonic2 = split(line2, search2)[0];
    string summary2  = split(line2, search2)[1];

    cout << mnemonic2 << "\n";
    cout << summary2 << "\n";

    // And trim() roll your own. C++ sucks.
    // See: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
    cout << trim2(mnemonic2) << "\n";
    cout << trim2(summary2) << "\n";
    ///////////////////////////////////


    // Take a boost
    string line3 = "ADCX %E2%80%94 Unsigned Integer Addition of Two Operands with Carry Flag";
    string search3 = "%E2%80%94";

    vector<string> result;
    //boost::split(result, line3, search3);
    // NONO: only with boost::is_any_of() characters as separator
    // NOTE: we are getting atrocious error reports because of templates
    // Only with regex. Gonna be dog slow.
    boost::algorithm::split_regex(result, line3, boost::regex(search3));

    string mnemonic3 = result[0];
    string summary3  = result[1];

    cout << mnemonic3 << "\n";
    cout << summary3 << "\n";

    // trim (in-place and does not return. Sucks.)
    boost::trim(mnemonic3);
    boost::trim(summary3);

    cout << mnemonic3 << "\n";
    cout << summary3 << "\n";
    ///////////////////////////////////

    // template test
    StringToStringMap my_map = {{"test1", "abc"}, {"test2", "def"}, {"test3", "ghi"}};
    print(my_map);


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

string& trim2(string& s)
{
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    s.erase(0, s.find_first_not_of(" \n\r\t"));                                                                                               
    return s;
}


vector<string> split(string s, string delimiter)
{
    size_t pos = 0;
    std::string token;
    vector<string> res;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        //std::cout << token << std::endl;
        res.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    // And the rest:
    //std::cout << s << std::endl;
    res.push_back(s);

    return res;
}



