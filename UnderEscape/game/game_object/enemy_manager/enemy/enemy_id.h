#pragma once
enum class ENEMY_ID
{
	SPIDER_ROBO,
	CREATURE,
};
enum class eSTATUS									//�G�l�~�[�̏�Ԃ̎��
{
	Stop,		//��~
	Wandering,	//�p�j
	Chase,		//�ǂ�������
	Vigilance,	//�x��
	Surprised,	//����
	Kill,		//�L��

	MAX,		//eSTATUS�̍ő�l
};
enum class eCHASE_STATUS	//�G�l�~�[���ǂ������Ă�����̔��ʗp
{
	Hearing,	//���o
	Sight,		//���o
};