#pragma once
#include"vivid.h"

class Visual
{
public:
	Visual();
	~Visual() = default;
	//‰Šú‰»
	void Initialize();
	//XV
	void Update(void);
	//•`‰æ
	void Draw(vivid::Vector2 scroll);
	//‰ğ•ú
	void Finalize(void);

private:

	vivid::Vector2 Scale;
	int map_chip_size;
};