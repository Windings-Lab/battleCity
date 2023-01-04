#include "PCHeader.h"

#include "BattleCity/Framework/Framework.h"
#include "BattleCity/Framework/Screen.h"

#include "BattleCity/Game/Game.h"

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

	void IsValidArgCount(const int argc)
	{
		if (argc != 3)
		{
			throw std::invalid_argument("Invalid argument count");
		}
	}
	void IsValidWindowArg(std::string_view arg)
	{
		const bool correctArg = arg == "-w" || arg == "-window";

		if(!correctArg)
		{
			throw std::invalid_argument("Invalid first argument");
		}
	}
	void IsValidSizeArg(std::string_view arg, int& w, int& h)
	{
		char delim;

		std::istringstream argv2(arg.data());
		argv2 >> w;
		argv2.get(delim);
		argv2 >> h;

		if (!argv2 || !argv2.eof() || delim != 'x')
		{
			throw std::invalid_argument("Invalid third argument");
		}
	}
}

int main(const int argc, const char* argv[])
{
	int width = 800, height = 600;
	bool fullScreen = true;
	if (argc != 1)
	{
		try
		{
			IsValidArgCount(argc);
			IsValidWindowArg(argv[1]);
			IsValidSizeArg(argv[2], width, height);
		}
		catch (const std::invalid_argument& ex)
		{
			std::cerr << ex.what() << "\n";
			ShowUsage();
			return 0;
		}

		fullScreen = false;
	}

	NSFramework::Screen screen(width, height, fullScreen);

	const auto framework = std::make_unique<BattleCity::Game::Game>(screen);

	return run(framework.get());
}
