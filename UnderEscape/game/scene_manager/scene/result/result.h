//���U���g�V�[���N���X
#pragma once
#include"../scene.h"
#include"vivid.h"
class ResultScene :public IScene
{
public:
	ResultScene();
	~ResultScene() = default;
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Finalize()override;
	//�X�V
	void Update(bool);

	void cursor_move();		//�J�[�\���̈ړ�
	bool GetCursor();		//�J�[�\���̎擾
private:
	enum class RESULT		//���U���g�̕���
	{
		GameClear,
		GameOver
	};
	RESULT result = RESULT::GameClear;
protected:
	unsigned int defult_color;				//�F
	bool left_right;						//�J�[�\���̉E���ʒu[�E�̏ꍇ��true][���̏ꍇ��false]
	vivid::Vector2 cursor_pos;			//�J�[�\���̕\���ʒu
	vivid::Vector2 left_pos;			//���̑I�����̈ʒu
	vivid::Vector2 right_pos;			//�E�̑I�����̈ʒu
	vivid::Vector2 result_pos;			//�Q�[���I�[�o�[or�Q�[���N���A�̈ʒu
};