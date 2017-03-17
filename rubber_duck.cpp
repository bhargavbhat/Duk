// Compile with g++ -std=c++11 file_name.cpp -lreadline -Wextra -Wall -Wpedantic -Werror
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <readline/readline.h>
#include <readline/history.h>

// tags is a standard ctags file
const std::string TAGS_FILE = "./tags";

std::vector<std::string> completion_candidates;

char* completion_gen(const char *text, int state)
{
    static int count;
    if(state == 0)
        count = -1;

    int text_len = ::strlen(text);

    while(count < ((int) completion_candidates.size() -1))
    {
        count++;
        if(::strncmp(completion_candidates[count].c_str(), text, text_len) == 0)
            return ::strdup(completion_candidates[count].c_str());
    }

    return NULL;
}

char** completion_fun(const char *text, int start, int end)
{
    (void) start;
    (void) end;

    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, completion_gen);
}

void populate_completion_candidates()
{
    std::ifstream infile(TAGS_FILE);

    // pass 1 : line counting
    infile.unsetf(std::ios_base::skipws);
    unsigned long line_count = std::count(std::istream_iterator<char>(infile),
        std::istream_iterator<char>(), '\n');

    completion_candidates.reserve(line_count);

    // pass 2 : actual parsing of tags
    infile.clear();
    infile.seekg(0);
    infile.setf(std::ios_base::skipws);
    
    std::string line;
    while(std::getline(infile, line))
    {
        // skip over the metadata in the
        // tags file, begins with !
        if(line[0] == '!')
            continue;

        // read each line, extract tag
        // first field in each line is tag
        // fields delimited by TAB char
        std::stringstream cur_line_stream(line);
        std::string tag;
        std::getline(cur_line_stream, tag, '\t');

        // add tag as a completion candidate
        completion_candidates.push_back(tag);
    }

    // some defaults + commands
    completion_candidates.push_back("hello");
    completion_candidates.push_back("hi");
    completion_candidates.push_back("bye");
    completion_candidates.push_back("quit");
    completion_candidates.push_back("exit");
    completion_candidates.push_back("help");

    // filter out duplicates
    std::sort(completion_candidates.begin(), completion_candidates.end());
    completion_candidates.erase(std::unique(completion_candidates.begin(), 
                completion_candidates.end()), completion_candidates.end());
}

void init_readline()
{
    populate_completion_candidates();
    rl_readline_name = "duk";
    rl_catch_signals = 0;
    rl_catch_sigwinch = 0;
    rl_completer_quote_characters = strdup("\"\'"); 
    rl_attempted_completion_function = completion_fun;
    rl_bind_key('\t', rl_complete);
}

bool read_user_input(std::string& usr_input)
{
    bool retVal = true;
    char* buf = NULL;
    if((buf = readline("U: ")) != NULL)
    {
        if(strlen(buf) > 0)
        {
            // fill out param
            usr_input.assign(buf);
            
            // add to history for Up/Dn Arrow
            // scrolling
            add_history(buf);
         
            if(::strcmp(buf, "exit") == 0 || ::strcmp(buf, "quit") == 0)
                retVal = false;
        }
    }

    ::free(buf);
    buf = NULL;
    
    return retVal;
}

std::string generate_response(const std::string& usr_input)
{
    static size_t idx = 0;

    std::vector<std::string> resp = {
        "...",
        "hmmm",
        "okay",
        "oh!",
        "so?",
        "and...",
        "uh huh",
        "um?",
        "go on...",
    };

    if(idx >= resp.size())
        idx = 0;

    if(usr_input.length() <= 1)
        return resp[0];
    else
        return resp[idx++];
}

int main()
{
    init_readline();
    std::cout<<"D: Hi, I'm Duk! Let's talk about your code..."<<std::endl;
    
    while(1)
    {
        std::string usr_input;
        auto proceed = read_user_input(usr_input);
        if(!proceed)
            break;
        else
            std::cout<<"D: " << generate_response(usr_input) << std::endl;
    }
    return 0;
}
