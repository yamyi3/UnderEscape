#pragma once
#include"vivid.h"

class Visual
{
public:
	Visual();
	~Visual() = default;
	//������
	void Initialize();
	//�X�V
	void Update(void);
	//�`��
	void Draw(vivid::Vector2 scroll);
	//���
	void Finalize(void);

private:

	vivid::Vector2 Scale;
	int map_chip_size;
};