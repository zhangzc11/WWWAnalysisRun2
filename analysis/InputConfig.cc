#include "InputConfig.h"

InputConfig input;

// The function to determine all the configuration above
void InputConfig::determine_input_settings(TString file_path, TString tree_name)
{

    // Set the current file name that was used to determine the input settings
    current_file_name = file_path;

    // Parse baby_type and year from the input file path
    std::vector<TString> file_path_tokens = RooUtil::StringUtil::split(file_path, "/");

    // The last token (the base file name) will tell us whether it's signal, data, or bkg or whatever.
    TString file_name = file_path_tokens.back();

    // If the first four letters are "www_" that's our signal sample
    if (TString(file_name(0, 4)).EqualTo("www_"))
        is_www = true;
    else
        is_www = false;

    // If the first three letters are "vh_" that's our signal sample (but it could be a bkg events if not in t_www tree)
    if (TString(file_name(0, 3)).EqualTo("vh_"))
        is_vh = true;
    else
        is_vh = false;

    // If the first five letters are "data_" that's our signal sample
    if (TString(file_name(0, 5)).EqualTo("data_"))
        is_data = true;
    else
        is_data = false;

    // If the first three letters are "vh_" that's our signal sample (but it could be a bkg events if not in t_www tree)
    if ((is_vh or is_www) and tree_name.EqualTo("t_www"))
        is_sig = true;
    else
        is_sig = false;

    // If not signal not data then it is bkg
    if (not is_sig and not is_data)
        is_bkg = true;
    else
        is_bkg = false;

    // Loop over all tokens and do simple if/then checks (NOTE: This could be improved but... OK...)
    bool found_the_token = false;
    for (auto& token : file_path_tokens)
    {

        // 
        // 1. Setting baby type, version, and year
        //
        // The token for determining the version will have the following format
        // <BABYTYPE><YEAR>_v<VERSION>
        // Condition is therefore,
        // when split via "_v" the size == 2
        // The first part's last 4 charaters are integer with either 2016, 2017, or 2018

        // Splitting by "_v"
        std::vector<TString> items = RooUtil::StringUtil::split(token, "_v");

        // Check that it is item of size 2 then this might be the token of interest
        if (items.size() == 2)
        {

            // Get the year part
            TString year_substring = items[0](items[0].Length()-4,items[0].Length());

            // If the year is not 2016, 2017, or 2018 go to next token
            if (year_substring.Atoi() == 2016 or year_substring.Atoi() == 2017 or year_substring.Atoi() == 2018)
            {

                // At this point this token is identified as the "<BABYTYPE><YEAR>_v<VERSION>" string

                // Set year
                year = year_substring.Atoi();

                // Set baby type
                baby_type = items[0](0, items[0].Length()-4);

                // Set baby version
                baby_version = items[1];

                // Sanity check that I found the token
                found_the_token = true;

            }

        }

    }

    // If it failed to find the right token to determine which sample it is, throw error
    if (not found_the_token)
    {
        std::cout << "ERROR: Couldn't figure out which sample I am running on file_path = " << file_path << std::endl;
        exit(-1);
    }

    // If v1.2.2 WWW2016 sample with is_www, then set do_www_xsec_scaling
    if (baby_type.EqualTo("WWW") and baby_version.EqualTo("1.2.2") and is_www)
        do_www_xsec_scaling = true;
    else
        do_www_xsec_scaling = false;

    // Lastly print out the input setting for completeness
    print_input_settings();

}

// Print input file settings to be clear
void InputConfig::print_input_settings()
{

    std::cout <<  "============================================" << std::endl;
    std::cout <<  " InputConfig settings based on the file path" << std::endl;
    std::cout <<  "--------------------------------------------" << std::endl;
    std::cout <<  " current_file_name: " << current_file_name.Data() << std::endl;
    std::cout <<  " baby_type: " << baby_type <<  std::endl;
    std::cout <<  " baby_version: " << baby_version <<  std::endl;
    std::cout <<  " year: " << year <<  std::endl;
    std::cout <<  " is_data: " << is_data <<  std::endl;
    std::cout <<  " is_bkg: " << is_bkg <<  std::endl;
    std::cout <<  " is_sig: " << is_sig <<  std::endl;
    std::cout <<  " is_www: " << is_www <<  std::endl;
    std::cout <<  " is_vh: " << is_vh <<  std::endl;
    std::cout <<  " do_www_xsec_scaling: " << do_www_xsec_scaling <<  std::endl;
    std::cout <<  "============================================" << std::endl;

}
