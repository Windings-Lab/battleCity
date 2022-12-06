#include "PCHeader.h"
#include "FrameworkWrapper.h"
#include "Screen.h"

void ShowUsage()
{
	std::cout
		<< "Usage: " << "BattleCity.exe\n"
		<< "Options:\n"
		<< "\t-w, -window 800x600\tSpecify window size"
		<< std::endl;
}


int main(int argc, const char* argv[])
{
	int width = 800;
	int height = 600;
#ifdef _DEBUG
	bool fullScreen = false;
#else
	bool fullScreen = true;
#endif

	if (argc != 1)
	{
		if (argc != 3)
		{
			ShowUsage();
			return 1;
		}

		std::string argv1 = argv[1];

		if(!(argv1 == "-w" || argv1 == "-window"))
		{
			ShowUsage();
			return 1;
		}

		int it = 0;
		int token[2]{};

		std::istringstream input;
		input.str(argv[2]);
		for (std::string line; std::getline(input, line, 'x'); )
		{
			it++;
			if(it > 2)
			{
				ShowUsage();
				return 1;
			}
			try
			{
				token[it - 1] = std::stoi(line);
			}
			catch (...)
			{
				ShowUsage();
				return 1;
			}
		}

		if(it != 2)
		{
			ShowUsage();
			return 1;
		}

		if (!SCR.IsValidSize(token[0], token[1]))
		{
			std::cout << "Incorrect window size" << std::endl;
			return 1;
		}

		fullScreen = false;
		width = token[0];
		height = token[1];
	}
	
	SCR.Set(width, height, fullScreen);
	
	const auto framework = std::make_unique<BattleCity::FrameworkWrapper>();

	return run(framework.get());
}

// ---> ^ X
// ^ ---> O
