#include "PCHeader.h"
#include "FrameworkWrapper.h"

namespace BattleCity::Framework::Screen
{
	void Set(int, int, bool);
	bool IsValidSize(int w, int h);
}

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

	bool IsValidArgCount(const int argc)
	{
		return argc == 3;
	}

	bool IsValidWindowOption(std::string_view option)
	{
		return option == "-w" || option == "-window";
	}

	bool IsValidWindowSize(std::string_view option, int& width, int& height)
	{
		char delim;

		std::istringstream argv2(option.data());
		argv2 >> width;
		argv2.get(delim);
		argv2 >> height;

		if (!argv2 || !argv2.eof() || delim != 'x')
		{
			return false;
		}

		if (!BattleCity::Framework::Screen::IsValidSize(width, height))
		{
			std::cerr << "Incorrect window size\n";
			return false;
		}

		return true;
	}
}

int main(const int argc, const char* argv[])
{
#ifdef _DEBUG
	BattleCity::Framework::Screen::Set(800, 600, false);
#else
	BattleCity::Framework::Screen::Set(800, 600, true);
#endif

	if (argc != 1)
	{
		if (!IsValidArgCount(argc))
		{
			ShowUsage();
			return 1;
		}

		if(!IsValidWindowOption(argv[1]))
		{
			ShowUsage();
			return 1;
		}

		int width = 0, height = 0;

		if(!IsValidWindowSize(argv[2], width, height))
		{
			ShowUsage();
			return 1;
		}

		BattleCity::Framework::Screen::Set(width, height, false);
	}
	
	const auto framework = std::make_unique<BattleCity::Framework::FrameworkWrapper>();

	return run(framework.get());
}
