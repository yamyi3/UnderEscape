#pragma once
#include "vivid.h"
#include "item_id.h"
#include "..\..\stage\stage.h"
#include "..\..\character\character.h"
class Item
{
public:
    // �R���X�g���N�^ 
    Item(ITEM_ID id,ITEM_STATE state, float width, float heght,float radius);

    // �f�X�g���N�^ 
    virtual ~Item(void);

    // ������ 
    virtual void    Initialize(const vivid::Vector2& position);
    // �X�V 
    virtual void    Update(vivid::Vector2 cPos, float cWidth, float cHeight, float rHeight);

    // �`�� 
    virtual void    Draw(void);

    // ��� 
    virtual void    Finalize(void);

	// �A�C�e���̕ێ�
    void CheckObject(vivid::Vector2 cPos, float cWidth, float cHeight);

    // �ʒu�̎擾 
    vivid::Vector2  GetPosition(void);

    // �ʒu�̐ݒ� 
    void            SetPosition(const vivid::Vector2& position);

    // ���S�ʒu�̎擾 
    vivid::Vector2  GetCenterPosition(void);

    // ���a�̎擾 
    float           GetRadius(void);

    // �A�N�e�B�u�t���O�̎擾 
    bool            GetActive(void);

    // �A�N�e�B�u�t���O�̐ݒ� 
    void            SetActive(bool active);

    // ���j�b�g���ʎq�擾 
    ITEM_ID   GetBulletCategory(void);

    //�A�C�e���I�u�W�F�N�g�̍��W�擾
    vivid::Vector2 GetItemPos(void)
    {
        return iPos;
    }
    //�A�C�e���I�u�W�F�N�g�̒��S�_�̎擾
    vivid::Vector2 GetItemCenter(void)
    {
        return iCenter;
    }
    //�A�C�e���I�u�W�F�N�g�̕��擾
    float GetItemWidth(void)
    {
        return m_Width;
    }
    //�A�C�e���I�u�W�F�N�g�̍����擾
    float GetItemHeight(void)
    {
        return m_Height;
    }
    void WallCheck();
    bool GetItemActive() { return m_Active; }
	float GetEffectiveArea() { return m_Area; } //�A�C�e���̗L���͈͂��擾

    bool IsActive() const { return m_ActiveFlag; }
    void Destroy() { m_ActiveFlag = false; }
protected:

    //�v���C���[�������Ă����Ԃ̏���
    virtual void GetMove(vivid::Vector2 cPos, float cWidth, float cHeight);
 
    //�v���C���[����������̏���(�}�E�X�j
    virtual void UseMove(vivid::Vector2);

   
    float                       Ga;					//�d�͉����x
    int                         m_Width;            //!< �� 
    int                         m_Height;           //!< ���� 
    float                       m_Radius;           //!< ���a 
    vivid::Vector2              m_Position;         //!< �ʒu 
    vivid::Vector2              m_Velocity;         //!< ���x 
    unsigned int                m_Color;            //!< �F 
    vivid::Vector2              m_Anchor;           //!< ��_ 
    vivid::Rect                 m_Rect;             //!< �ǂݍ��ݔ͈� 
    vivid::Vector2              m_Scale;            //!< �g�嗦 
    float                       m_Rotation;         //!< ��]�l 
    bool                        m_ActiveFlag;       //!< �A�N�e�B�u�t���O 
    ITEM_ID                     m_ItemID;  	        //!< �A�C�e����ID
	ITEM_STATE				    m_ItemState;        //!< �A�C�e���̏��
    bool                        catchFlg;			//�A�C�e���擾�̔��f�t���O
	vivid::Vector2              iPos;				//�A�C�e���I�u�W�F�N�g�̍��W
	vivid::Vector2              iCenter;			//�A�C�e���I�u�W�F�N�g�̒��S�_
	static const float          throw_speed;		//�A�C�e���I�u�W�F�N�g�̓����鑬�x
	float                       item_fall;			//�A�C�e���I�u�W�F�N�g�̗������x
	unsigned int                iColor;				//�A�C�e���I�u�W�F�N�g�̐F
	bool						ceiling_wall;	    //�V��ƕǂ̔���t���O
	bool 					    left_right_wall;	//���E�̕ǂ̔���t���O
	bool                        ground_wall;		//���̔���t���O
	bool 					    m_Active;           //!< �g�p�t���O
	float                       m_Area;             //!< �A�C�e���̗L���͈�
};