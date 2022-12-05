#include "FrameworkWrapper.h"
#include "Screen.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>


static void show_usage(std::string name)
{
	std::cerr << "Usage: " << name << " <option(s)> SOURCES\n"
		<< "Options:\n"
		<< "\t-h,--help\t\tShow this help message\n"
		<< "\t-w,-window 800x600\tSpecify window size"
		<< std::endl;
}

int main(int argc, char* argv[])
{
	int width = 800;
	int height = 600;
	bool fullScreen = false;
	if (argc != 1)
	{
		std::vector<int> tokens;
		std::vector<std::string> sources;
		if (argc < 3)
		{
			show_usage(argv[0]);
			return 1;
		}
		std::string window;
		for (int i = 1; i < argc; ++i)
		{
			std::string arg = argv[i];
			if ((arg == "-h") || (arg == "--help"))
			{
				show_usage(argv[0]);
				return 0;
			}
			if ((arg == "-w") || (arg == "-window"))
			{
				if (i + 1 < argc)
				{
					// Make sure we aren't at the end of argv!
					window = argv[i++]; // Increment 'i' so we don't get the argument as the next argv[i].
				}
				else
				{
					// Uh-oh, there was no argument to the window option.
					std::cerr << "--window option requires one argument." << std::endl;
					return 1;
				}
			}
			else
			{
				show_usage(argv[0]);
				return 1;
			}
			sources.push_back(argv[i]);
		}
		std::string token;
		std::istringstream tokenStream(sources[0]);
		while (getline(tokenStream, token, 'x'))
		{
			try
			{
				tokens.push_back(stoi(token));
			}
			catch (const std::exception&)
			{
				show_usage(argv[0]);
				return 1;
			}
		}
		fullScreen = false;
		width = tokens[0];
		height = tokens[1];
	}

	srand(time(nullptr));
	BattleCity::SCR.Set(width, height, fullScreen);

	auto framework = std::make_unique<BattleCity::FrameworkWrapper>();

	return run(framework.get());
}

// ---> ^ X
// ^ ---> O
