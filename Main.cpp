#include "PCHeader.h"
#include "FrameworkWrapper.h"

namespace 
{
	void ShowUsage()
	{
		std::cout
			<< "Usage: " << "BattleCity.exe\n"
			<< "Options:\n"
			<< "\t-w, -window 800x600\tSpecify window size"
			<< std::endl;
	}
}

namespace BattleCity::Framework::Screen
{
	void Set(int, int, bool);
	bool IsValidSize(int w, int h);
}

int main(int argc, const char* argv[])
{
#ifdef _DEBUG
	BattleCity::Framework::Screen::Set(800, 600, false);
#else
	BattleCity::Framework::Screen::Set(800, 600, true);
#endif

	if (argc != 1)
	{
		if (argc != 3)
		{
			ShowUsage();
			return 1;
		}

		std::string argv1 = argv[1];

		if (!(argv1 == "-w" || argv1 == "-window"))
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
			if (it > 2)
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

		if (it != 2)
		{
			ShowUsage();
			return 1;
		}

		if (!BattleCity::Framework::Screen::IsValidSize(token[0], token[1]))
		{
			std::cout << "Incorrect window size" << std::endl;
			return 1;
		}

		BattleCity::Framework::Screen::Set(token[0], token[1], false);
	}
	
	const auto framework = std::make_unique<BattleCity::Framework::FrameworkWrapper>();

	return run(framework.get());
}
