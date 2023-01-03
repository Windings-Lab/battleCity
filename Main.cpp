#include "PCHeader.h"

#include "Framework/Wrapper.h"
#include "Framework/Screen.h"

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
		if(!(arg == "-w" || arg == "-window"))
		{
			throw std::invalid_argument("Invalid first argument");
		}
	}

	void IsValidSizeArg(std::string_view arg)
	{
		int width = 0, height = 0;
		char delim;

		std::istringstream argv2(arg.data());
		argv2 >> width;
		argv2.get(delim);
		argv2 >> height;

		if (!argv2 || !argv2.eof() || delim != 'x')
		{
			throw std::invalid_argument("Invalid third argument");
		}

		if (!BattleCity::Framework::Screen::IsValidSize(width, height))
		{
			throw std::invalid_argument("Incorrect window size");
		}

		BattleCity::Framework::Screen::Set(width, height, false);
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
		try
		{
			IsValidArgCount(argc);
			IsValidWindowArg(argv[1]);
			IsValidSizeArg(argv[2]); // Sets window size if everything correct
		}
		catch (const std::invalid_argument& ex)
		{
			std::cerr << ex.what() << "\n";
			ShowUsage();
			return 0;
		}
	}
	
	const auto framework = std::make_unique<BattleCity::Framework::Game>();

	return run(framework.get());
}
