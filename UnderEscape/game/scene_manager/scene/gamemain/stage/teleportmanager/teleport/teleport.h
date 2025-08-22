#pragma once
#include"vivid.h"

class Teleport
{
public:
	Teleport();
	~Teleport()=default;
	//������
	void Initialize();
	void Initialize(vivid::Vector2);
	void Initialize(vivid::Vector2, vivid::Vector2);
	//�X�V
	void Update(void);
	//�`��
	void Draw(void);
	//���
	void Finalize(void);

	void InputTpPos(vivid::Vector2);

	bool GetTeleportFlg(vivid::Vector2 p_pos);
	vivid::Vector2 GetTeleportPos(vivid::Vector2 p_pos);

private:
	vivid::Vector2 TpPos[2];
	static const int TpCount;

	float ch_width;					//���@�̕�
	float ch_height;				//���@�̍���
	int map_chip_size;
};