#include <iostream>

#include <string>
#include <vector>

enum CommandlineOptionType
{
    withValue,
    withoutValue
};

CommandlineOptionType defaultOptionType = withoutValue;
bool defaultSetStopOnErrors = true;
const std::string emptyString;
const int helpDescriptionPrintMargin1(6);
const int helpDescriptionPrintMargin2(5);

class CommandlineOption
{
public:
    std::string name;
    std::vector<std::string> flagsList;
    std::vector<std::string> helpString;
    CommandlineOptionType type;
    bool isSet;
    std::string value;
    
    CommandlineOption();

    CommandlineOption(const std::string& name, 
                      const std::vector<std::string>& flags);

    CommandlineOption(const std::string& name, 
                      const std::vector<std::string>& flags, 
                      const std::vector<std::string>& helpLine);

    CommandlineOption(const std::string& name, 
                      const std::vector<std::string>& flags, 
                      const std::vector<std::string>& helpLine, 
                      CommandlineOptionType type);

    bool hasFlag(const std::string& flag) const;

};

CommandlineOption::CommandlineOption()
: name(""),
  flagsList(std::vector<std::string>()),
  helpString(std::vector<std::string>()),
  type(defaultOptionType),
  isSet(false),
  value("")
{
}

CommandlineOption::CommandlineOption(const std::string& name,
                  const std::vector<std::string>& flags)
: name(name),
  flagsList(flags),
  helpString(std::vector<std::string>()),
  type(defaultOptionType),
  isSet(false),
  value("")
{
}

CommandlineOption::CommandlineOption(const std::string& name,
                  const std::vector<std::string>& flags,
                  const std::vector<std::string>& helpLine)
: name(name),
  flagsList(flags),
  helpString(helpLine),
  type(defaultOptionType),
  isSet(false),
  value("")
{
}

CommandlineOption::CommandlineOption(const std::string& name,
                  const std::vector<std::string>& flags,
                  const std::vector<std::string>& helpLine,
                  CommandlineOptionType type)
: name(name),
  flagsList(flags),
  helpString(helpLine),
  type(type),
  isSet(false),
  value("")
{
}

bool CommandlineOption::hasFlag(const std::string& flag) const
{
    for ( int i = 0; i < flagsList.size(); ++i )
    {
        if ( flagsList[i] == flag)
        {
            return true;
        }
    }
    return false;
}

class CommandlineOptionsParser
{
private:

    bool m_bOptionsParsedCorrectly;
    bool m_bStopOnErrors;
    std::vector<CommandlineOption> m_options;

public:

    CommandlineOptionsParser();
    
    void addOption( std::string& name, 
                    std::vector<std::string>& flags );
    
    void addOption( std::string& name, 
                    std::vector<std::string>& flags, 
                    std::vector<std::string>& helpLIne );

    void addOption( std::string& name, 
                    std::vector<std::string>& flags, 
                    std::vector<std::string>& helpLIne, 
                    CommandlineOptionType type );

    void addOption(const CommandlineOption& opt);

    int parse(int argc, char* argv[]);

    void clear();

    void setStopOnError(bool s);

    bool getStopOnError() const;

    bool allOptionsParsedCorrectly() const;

    bool isSet(const std::string& optName) const;

    std::string value(const std::string& optName) const;

    std::string getHelpDescription() const;

    const CommandlineOption& getOption(const std::string& name) const;

private: 

    struct searchResult
    {
        searchResult(bool b, size_t pos)
        : exists(b), position(pos)
        { }
        bool exists;
        size_t position;
    };

    searchResult optionSearch(const std::string& optionName) const;

    searchResult flagSearch(const std::string& inputFlag) const;

    std::string getFlagsAsString(const CommandlineOption& opt) const;

    size_t getMaxSizeOfFlagString(int minSize) const;
};

CommandlineOptionsParser::CommandlineOptionsParser()
: m_bOptionsParsedCorrectly(false),
  m_bStopOnErrors(defaultSetStopOnErrors)
{
}

//=============================================================================================================

void CommandlineOptionsParser::clear()
{
    m_options.clear();
}

//=============================================================================================================

bool CommandlineOptionsParser::allOptionsParsedCorrectly() const
{
    return m_bOptionsParsedCorrectly;
}

//=============================================================================================================


void CommandlineOptionsParser::addOption(std::string& name,
                                         std::vector<std::string>& flags)
{
    m_options.push_back(CommandlineOption(name, flags));
}

void CommandlineOptionsParser::addOption(std::string& name,
                                         std::vector<std::string>& flags,
                                         std::vector<std::string>& helpLine)
{
    m_options.push_back(CommandlineOption(name, flags, helpLine, defaultOptionType));
}

void CommandlineOptionsParser::addOption(std::string& name,
                                         std::vector<std::string>& flags,
                                         std::vector<std::string>& helpLine,
                                         CommandlineOptionType type)
{
    m_options.push_back(CommandlineOption(name, flags, helpLine, defaultOptionType));
}

void CommandlineOptionsParser::addOption(const CommandlineOption& opt)
{
    m_options.push_back(opt);
}

CommandlineOptionsParser::searchResult CommandlineOptionsParser::flagSearch(const std::string& inputFlag) const
{

    for(size_t i = 0; i < m_options.size(); ++i)
    {
        if(m_options[i].hasFlag(inputFlag))
        {
            return searchResult(true, i);
        }
    }
    return searchResult(false,  0);
}

CommandlineOptionsParser::searchResult CommandlineOptionsParser::optionSearch(const std::string& optName) const
{
    for (size_t i = 0; i < m_options.size(); ++i)
    {
        if(m_options[i].name == optName)
        {
            return searchResult(true, i);
        }
    }
    return searchResult(false, 0);
}

const CommandlineOption& CommandlineOptionsParser::getOption(const std::string& name) const
{
    searchResult thisSearch = optionSearch(name);
    return m_options[thisSearch.position];
}

void CommandlineOptionsParser::setStopOnError(bool s)
{
    m_bStopOnErrors = s;
}

bool CommandlineOptionsParser::getStopOnError() const
{
    return m_bStopOnErrors;
}

//=============================================================================================================

bool CommandlineOptionsParser::isSet(const std::string& optionName) const
{
    searchResult thisSearch(optionSearch(optionName));
    if(thisSearch.exists)
    {
        return m_options[thisSearch.position].isSet;
    } else {
        return false;
    }
}

//=============================================================================================================

std::string CommandlineOptionsParser::value(const std::string& optionName) const
{
    searchResult thisSearch(optionSearch(optionName));
    if(thisSearch.exists)
    {
        return m_options[thisSearch.position].value;
    } else {
        return std::string();
    }
}

//=============================================================================================================

std::string CommandlineOptionsParser::getFlagsAsString(const CommandlineOption& opt) const
{
    std::string concatFlags(opt.flagsList[0]);
    for(int i = 1; i < opt.flagsList.size(); ++i)
    {
        concatFlags += ", " + opt.flagsList[i];
    }
    return concatFlags;
}

size_t CommandlineOptionsParser::getMaxSizeOfFlagString(int minSize) const
{
    size_t maxFlagStringSize(minSize);
    for(int i = 0; i < m_options.size(); ++i)
    {
        size_t fSize(getFlagsAsString(m_options[i]).size());
        if( maxFlagStringSize < fSize )
        {
            maxFlagStringSize = fSize;
        }
    }
    return maxFlagStringSize;
}

std::string CommandlineOptionsParser::getHelpDescription() const
{

    size_t colWidth(getMaxSizeOfFlagString(helpDescriptionPrintMargin1 + helpDescriptionPrintMargin2));

    std::string helpStr("Options:\n");
    for ( int i = 0; i < m_options.size(); ++i )
    {
        std::string flags(getFlagsAsString(m_options[i]));
        helpStr += flags + std::string(colWidth - flags.size(),' ');
        if ( m_options[i].helpString.size() > 0 ) 
        {
            helpStr += m_options[i].helpString[0] + "\n";
            for ( int j = 1; j < m_options[i].helpString.size(); ++j)
            {
                helpStr += std::string(colWidth, ' ') + m_options[i].helpString[j] + "\n";
            }
        }

    }
    helpStr += "\n";
    return helpStr;
}

int CommandlineOptionsParser::parse(int argc, char** argv)
{
    int i = 1;
    for( ; i < argc; ++i)
    {
        std::string inputflag(argv[i]);
        searchResult optionSearch(flagSearch(inputflag));
        if(optionSearch.exists)
        {
            CommandlineOption& opt = m_options[optionSearch.position];
            opt.isSet = true;
            if (opt.type == withValue)
            {
                bool notLastInputArg(i < (argc -1));
                if( notLastInputArg )
                {
                    opt.value = std::string(argv[i + 1]);
                    ++i;
                } else {
                    if(m_bStopOnErrors)
                    {
                        std::cout << "Error parsing input argumets. Arg: " << opt.name << " requires a following value.\n";
                        return 1;
                    }
                }
            }
        } else {
            if(m_bStopOnErrors)
            {
                std::cout << "Error. Input argument unknown: " << argv[i] << "\n";
                return 1;
            }
        }
    }

    if ( i == argc)
    {
        m_bOptionsParsedCorrectly = true;   
    }

    return 0;
}

void testOption(const CommandlineOptionsParser& parser, const std::string& name)
{
        std::cout << "\n";
        if(parser.isSet(name))
        {
            std::cout << "option " << name << " is set!!!\n";
            if(parser.getOption(name).type == withValue)
            {
                std::cout << "and its value is : " << parser.value("option1");
            }
        } else {
            std::cout << "option " << name << " is missing!!!\n";
        }
        std::cout << "\n";
}

int main(int argc, char* argv[])
{
    std::vector<std::string> opt1Flags;
    opt1Flags.push_back("-dsfs");
    std::vector<std::string> opt1Help;
    opt1Help.push_back("This is my second help");
    CommandlineOption opt1("option1", opt1Flags, opt1Help, withoutValue);
    
    std::vector<std::string> opt2Flags;
    opt2Flags.push_back("-f");
    opt2Flags.push_back("--file");
    std::vector<std::string> opt2Help;
    opt2Help.push_back("this is my help");
    opt2Help.push_back("Because this is my second example.");
    CommandlineOption opt2("option2", opt2Flags, opt2Help, withValue);

    CommandlineOption opt3(opt1);
    opt3.name = std::string("option3");
    // opt3.flagsList[0] = std::string("-ff");
    // opt3.flagsList[1] = std::string("--ffile");
    // opt3.helpString[0] = "this is my help modified";
    // opt3.helpString.pop_back();
    
    std::vector<std::string> opt4Flags;
    opt4Flags.push_back("-h");
    opt4Flags.push_back("--help");
    std::vector<std::string> opt4Help;
    opt4Help.push_back("this is the HELP!!");
    opt4Help.push_back("Because this is my second example.");
    CommandlineOption opt4("help", opt4Flags, opt4Help, withoutValue);

    // if( opt2.hasFlag("-f") )
    // {
    //     std::cout << "it has the flag!!\n";
    // } else {
    //     std::cout << "it doesn't have the flag!!\n";
    // }

    CommandlineOptionsParser parser;
    parser.addOption(opt1);
    parser.addOption(opt2);
    parser.addOption(opt3);
    parser.addOption(opt4);
    parser.setStopOnError(false);

    parser.parse(argc, argv);
    
    if( parser.allOptionsParsedCorrectly() )
    {
        testOption(parser, "option1");
        testOption(parser, "option2");
        testOption(parser, "option3");
        testOption(parser, "help");
    }


    std::cout << parser.getHelpDescription();

    return 0;

}
