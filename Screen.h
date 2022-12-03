#pragma once

#define SCR Screen::getInstance()

class Screen
{
public:
	~Screen() = default;

	unsigned int getWidth();
	unsigned int getHeight();
	bool getFullscreen();

	/// <summary>
	/// boundaryR = 760
	/// </summary>
	/// <param name="744">last coordinate for creating wall</param>
	float getBoundaryR();
	/// <summary>
	/// boundaryD = 556
	/// </summary>
	/// <param name="540">last coordinate for creating wall</param>
	float getBoundaryD();

	/// <summary>
	/// boundaryL = 40
	/// </summary>
	/// <param name="40">First coordinate for creating wall</param>
	float getBoundaryL();
	/// <summary>
	/// boundaryU = 44
	/// </summary>
	/// <param name="44">First coordinate for creating wall</param>
	float getBoundaryU();

	/// <summary>
	/// Initialize screen
	/// </summary>
	/// <param name="">Width</param>
	/// <param name="">Height</param>
	/// <param name="">Fullscreen</param>
	/// <returns></returns>
	static Screen& set(unsigned int wValue, unsigned int hValue, bool fValue) noexcept;
	static Screen& getInstance();
	static void boundaryRSet(unsigned int newWidth);
	static void boundaryDSet(unsigned int newHeight);
	static void boundaryLSet(unsigned int newWidth);
	static void boundaryUSet(unsigned int newHeight);

private:
	Screen() {}
	Screen(const Screen&); // copy constructor
	Screen(Screen&&); // move constructor

	static unsigned int _width;
	static unsigned int _height;
	static bool _fullscreen;

	static float _boundaryR;
	static float _boundaryD;

	static float _boundaryL;
	static float _boundaryU;

	void operator=(Screen const&);
};
