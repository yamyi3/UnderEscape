#pragma once
enum class ITEM_ID
{
	// �A�C�e����ID���`
	DUMMY,			//�_�~�[
	FLASH_ITEM,		//�t���b�V���A�C�e��
	SOUND_ITEM,		//���̏o��A�C�e��

	MAX
};

enum class ITEM_STATE
{
	DUMMY,		//�_�~�[
	PLACE,		//�ݒu
	GET,		//�v���C���[�擾
	USE,		//�������Ă���
	BREAK,		//�j��
};

enum class ITEM_ORBIT
{
	DUMMY,
	MAIN
};
