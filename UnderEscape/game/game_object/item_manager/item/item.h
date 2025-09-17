#pragma once
#include "vivid.h"
#include "item_id.h"
#include "..\..\stage\stage.h"
#include "..\..\character\character.h"
class CItem
{
public:
    // �R���X�g���N�^ 
    CItem(ITEM_ID id, ITEM_STATE state, float width, float heght, float radius, float effect_area, int number_of_times);

    // �f�X�g���N�^ 
    virtual ~CItem(void);

    // ������ 
    virtual void    Initialize(const vivid::Vector2& position);

    // �X�V 
    virtual void    Update(vivid::Vector2 c_pos, float c_width, float c_height, float r_height);

    // �`�� 
    virtual void    Draw(void);

    // ��� 
    virtual void    Finalize(void);

    // �A�C�e���̕ێ�
    void CheckObject(vivid::Vector2 c_pos, float c_width, float c_height);

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
        return m_Position;
    }
    //�A�C�e���I�u�W�F�N�g�̒��S�_�̎擾
    vivid::Vector2 GetItemCenter(void)
    {
        return m_Center;
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
    //�A�C�e���̓����蔻��
    void WallCheck(void);

    //�A�C�e���̌��ʂ��L�����ǂ������擾
    bool GetItemActive(void) { return m_Active; }

    //�A�C�e���̌��ʔ͈͂��擾
    float GetEffectiveArea(void) { return m_Effect_Area; }

    //�A�C�e���̏�Ԃ��擾
    ITEM_STATE GetItemState(void) { return m_ItemState; }

    //�A�C�e����ID���擾
    ITEM_ID GetItemID(void) { return m_ItemID; }

    //�L���b�`�t���O�̎擾
    bool GetCatchFlg(void) { return m_CatchFlg; }

    //�A�N�e�B�u�t���O�̎擾
    bool IsActive(void) { return m_ActiveFlag; }

    //�I�u�W�F�N�g�̍폜
    void Destroy(void) { m_ActiveFlag = false; }

    //�����Ă����Ԃ�Ԃ�
    bool CanPickUp(void) { return m_Color == m_can_pick_up_color; }

    //�E������
    void Found(void);

    //�����铮��
    void Thrown(void);

    //�u������Ɉڍs������
    void Place(vivid::Vector2 c_pos);

    //�u������
    void ItemPlace(vivid::Vector2 c_pos);
    bool WallCheck(vivid::Vector2 position);
    bool GroundCheck(vivid::Vector2 position );
    bool CelingCheck(vivid::Vector2 position);
    bool LeftWallCheck(vivid::Vector2 position);
    bool RightWallCheck(vivid::Vector2 position);
protected:

    //�v���C���[�������Ă����Ԃ̏���
    virtual void GetMove(vivid::Vector2 c_pos, float c_width, float c_height);

    //�v���C���[����������̏���(�}�E�X�j
    virtual void UseMove();

    //�A�C�e���O���̈ʒu�Z�b�g
    virtual void SetOrbitPosition(vivid::Vector2 position, vivid::Vector2 c_pos);

    static const unsigned int   m_default_color;        //!< �f�t�H���g�̐F
    static const unsigned int   m_can_pick_up_color;    //!< �擾�\�ȐF
    static const unsigned int   m_picked_up_color;      //!< �擾�����F
    static const unsigned int   m_throw_color;		    //!< �������F

    static const float          throw_speed;		//�A�C�e���I�u�W�F�N�g�̓����鑬�x

    float                       m_Ga;				//�d�͉����x
    int                         m_Width;            //!< �� 
    int                         m_Height;           //!< ���� 
    float                       m_Radius;           //!< ���a 
    float                       m_Rotation;         //!< ��]�l 

    vivid::Vector2              m_Position;         //!< �ʒu 
    vivid::Vector2              m_Velocity;         //!< ���x 
    vivid::Vector2              m_Anchor;           //!< ��_ 
    vivid::Vector2              m_Center;			//�A�C�e���I�u�W�F�N�g�̒��S�_
    vivid::Vector2              m_Scale;            //!< �g�嗦 
    vivid::Rect                 m_Rect;             //!< �ǂݍ��ݔ͈� 

    unsigned int                m_Color;            //!< �F 
    bool                        m_ActiveFlag;       //!< �A�N�e�B�u�t���O 
    bool 					    m_Active;           //�A�C�e�����ʂ̗L������
    bool                        m_Place_Flg;        //�u������Ɉڍs���邩�t���O

    ITEM_ID                     m_ItemID;  	        //!< �A�C�e����ID
    ITEM_STATE				    m_ItemState;        //!< �A�C�e���̏��

    float                       m_Effect_Area;      //!< �A�C�e���̗L���͈�
    vivid::Rect                 m_Effect_Rect;      //!< �A�C�e�����ʔ͈͕\�� 
    vivid::Vector2              m_Effect_Scale;     //!< �g�嗦 
    vivid::Vector2              m_Effect_Anchor;    //!< �g�嗦 
    unsigned int                m_Effect_Color;	    //�A�C�e�����ʔ͈͂̐F

    vivid::Vector2              m_Orbit_Position[10];   //�A�C�e���O���̈ʒu

    bool                        m_First;           //�ŏ��̈�񂾂�true
    bool                        m_CatchFlg;			//�A�C�e���擾�̔��f�t���O
    float                       m_Fall;			    //�A�C�e���I�u�W�F�N�g�̗������x
    int                         m_Active_Time;	    //�A�C�e���̌��ʎ���	
    int                         m_Number_Of_Times;  //�A�C�e���̌��ʉ�

    bool						ceiling_wall;	    //�V��ƕǂ̔���t���O
    bool 					    left_right_wall;	//���E�̕ǂ̔���t���O
    bool                        ground_wall;		//���̔���t���O
};