#pragma once
#include"vivid.h"
#include "..\visual_id.h"
class Visual
{
public:
	Visual();
	~Visual() = default;
	//������
	void Initialize(VISUAL_ID v_id,int x,int y);
	//�X�V
	void Update(void);
	//�`��
	void Draw(vivid::Vector2 scroll);
	//�r�W���A��ID�o��
	VISUAL_ID GetVisual_ID() { return Visual_ID; }
	//���
	void Finalize(void);

private:

	static const std::string visual_picture_name[(int)VISUAL_ID::MAX];
	static const int visual_picture_width_size[(int)VISUAL_ID::MAX];
	static const int visual_picture_height_size[(int)VISUAL_ID::MAX];
	static const int visual_draw_width_size[(int)VISUAL_ID::MAX];
	static const int visual_draw_height_size[(int)VISUAL_ID::MAX];
	VISUAL_ID Visual_ID;
	vivid::Vector2 Pos;
	vivid::Vector2 Scale;
	vivid::Rect Rect;
	int map_chip_size;
};