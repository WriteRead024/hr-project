
// Rich W.
//portions of this miniprogram monked from
// https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
// https://stackoverflow.com/a/1022961
//Jun 3, 2018
// MSL.l otherwise

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <time.h>
#include <iostream>
using namespace std;

static string getDateTimeString()
{
    time_t time_now = time(0);
    struct tm time_struct;
    char char_buff[80];
    time_struct = *localtime(&time_now);
    //http://en.cppreference.com/w/cpp/chrono/c/strftime
    strftime(char_buff, sizeof(char_buff), "%Y-%m-%d::%X", &time_struct);
    return char_buff;
}

static void printStringRepeats(string argString, int argRepeats)
{
    for (int repeat_count = 0; repeat_count < argRepeats; repeat_count++)
    {
        cout << argString << endl;
    }
}

int main(int argc, char *argv[])
{
    int loop_count = 0;
    int loop_limit = 2048;
    struct winsize w;
    int print_repeat = 3;
    int in_print_repeat = print_repeat;
    string hr_char_str = "-";
    string in_char_str = "";

    
    for(int arg_index = 1; arg_index < argc; arg_index++)
    {        
        in_char_str = argv[arg_index];
        in_print_repeat = print_repeat;
        try
        {
            print_repeat = std::stoi(in_char_str);
        }
        catch (const std::exception &e)
        {
            print_repeat = in_print_repeat;
            hr_char_str = in_char_str[0];
            //std::cerr << e.what() << '\n';
        }
    }
    
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    string out_string_hr = "";
    while (out_string_hr.length() < w.ws_col && loop_count++ < loop_limit)
    {
        out_string_hr = out_string_hr + hr_char_str;
    }

    string timestamp = getDateTimeString();

    printStringRepeats(out_string_hr, print_repeat);
    cout << timestamp << endl;
    printStringRepeats(out_string_hr, print_repeat);

    return 0;
}