#pragma once
#include "vivid.h"
class Ground
{
public:
	Ground();
	~Ground() = default;
	//������
	void Initialize(vivid::Vector2 pos, float V, float H);
	void Initialize(vivid::Vector2 pos1, vivid::Vector2 pos2);
	void Initialize(vivid::Vector2 pos, float V, float H, int color);
	void Initialize(vivid::Vector2 pos1, vivid::Vector2 pos2, int color);
	//�X�V
	void Update(void);
	//�`��
	void Draw(float scroll);
	// �J��
	void Finalize();
	//�v���C���[�Ƃ̓����蔻����`�F�b�N
	bool CheckHitPlayer(const vivid::Vector2& center_c_pos, int ch_height, int ch_width);

	bool IsActive(void)const { return m_ActiveFlag; }
	void Destroy(void) { m_ActiveFlag = false; }

private:
	static const std::string ground_picture_name;
	static const int ground_picture_width_size;
	static const int ground_picture_height_size;


	vivid::Vector2 w_Pos;
	vivid::Vector2 w_Scale;
	float w_WidthSize;					//��Q���̉��̃h�b�g��
	float w_HeightSize;                 //��Q���̏c�̃h�b�g��
	unsigned int w_color;

	bool m_ActiveFlag;	//�A�N�e�B�u�t���O
};