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
	enum class RESULT
	{
		GameClear,
		GameOver
	};
	RESULT result = RESULT::GameClear;
protected:
	unsigned int color;				//�F
	bool Right;						//�J�[�\���̉E���ʒu[�E�̏ꍇ��true][���̏ꍇ��false]
	vivid::Vector2 Cpos;			//�J�[�\���̕\���ʒu
	vivid::Vector2 pos1;			//���̑I�����̈ʒu
	vivid::Vector2 pos2;			//�E�̑I�����̈ʒu
	vivid::Vector2 pos3;			//�Q�[���I�[�o�[or�Q�[���N���A�̈ʒu
};