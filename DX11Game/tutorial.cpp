#include "tutorial.h"
#include "model.h"
#include "collision.h"
#include "input.h"
#include "debugproc.h"
#include "Sound.h"

#define PATH_POPUP1_TEXTURE	L"data/texture/tutorial/popup1.png"
#define PATH_POPUP2_TEXTURE	L"data/texture/tutorial/popup2.png"
#define PATH_POPUP3_TEXTURE	L"data/texture/tutorial/popup3.png"
#define PATH_POPUP4_TEXTURE	L"data/texture/tutorial/popup4.png"
#define PATH_POPUP5_TEXTURE	L"data/texture/tutorial/popup5.png"
#define PATH_POPUP6_TEXTURE	L"data/texture/tutorial/popup6.png"
#define PATH_POPUP7_TEXTURE	L"data/texture/tutorial/popup7.png"
#define PATH_POPUP8_TEXTURE	L"data/texture/tutorial/popup8.png"
#define PATH_POPUP9_TEXTURE	L"data/texture/tutorial/popup9.png"
#define PATH_POPUP10_TEXTURE L"data/texture/tutorial/popup10.png"
#define PATH_POPUP11_TEXTURE L"data/texture/tutorial/popup11.png"

bool Tutorial::m_bPopupNum[] = {false,false, false, false, false, false, false, false, false, false, false, };
bool Tutorial::m_bPopupNum2[] = { false,false, false, false, false, false, false, false, false, false, false, };

Tutorial::Tutorial()
{
	ID3D11Device* pDevice = GetDevice();

	// �ϐ�������
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(0.0f, 10.0f, 0.0f);// XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	m_bPopup = false;
	m_bTrigger = false;
	m_nCnt = 0;

	for ( int i = 0; i < 1; i++)
	{
		m_bPaperTrigger[i] = false;

	}
	m_bPaperTrriger = false;
	// �e�N�X�`���Ǎ�
	CreateTextureFromFile(pDevice, PATH_POPUP1_TEXTURE, &m_pTexture);
}
Tutorial::~Tutorial()
{
	// �w�i�e�N�X�`�����
	SAFE_RELEASE(m_pTexture);
}
void Tutorial::Update(EStage stage)
{
	ID3D11Device* pDevice = GetDevice();
	

	// �|�b�v�A�b�v�\�����ꂽ�Ƃ�
	if (m_bPopup)
	{
		if (!m_bPaperTrriger)
		{
			CSound::SetVolume(SE_PAPER, 1.0f);
			CSound::Play(SE_PAPER);
			m_bPaperTrriger = true;
		}
		m_size.x += 100.0f;
		if (m_size.x > SCREEN_WIDTH-300)
		{
			m_size.x = SCREEN_WIDTH-300;
			m_size.y += 100.0f;
			if (m_size.y > SCREEN_HEIGHT-100)
			{
				m_size.y = SCREEN_HEIGHT-100;
			}
		}

		// �R���g���[���[�X�e�B�b�N���擾
		LONG stickLX = GetJoyLX(0);
		LONG stickLY = GetJoyLY(0);

		LONG stickRX = GetJoyRX(0);
		LONG stickRY = GetJoyRY(0);

		// �R���g���[���[�X�e�B�b�N�ɂ��{�^���I������
		// �f�b�h�]�[������
		if ((stickLX < STICK_DEAD_ZONE && stickLX > -STICK_DEAD_ZONE) &&
			(stickLY < STICK_DEAD_ZONE && stickLY > -STICK_DEAD_ZONE) &&
			(stickRX < STICK_DEAD_ZONE && stickRX > -STICK_DEAD_ZONE) &&
			(stickRY < STICK_DEAD_ZONE && stickRY > -STICK_DEAD_ZONE)
			)
		{
			stickLX = 0;
			stickLY = 0;
			stickRX = 0;
			stickRY = 0;
			m_bTrigger = false;
		}	// �X�e�B�b�N�����ɌX�����Ƃ�
		else if (stickLX > 20000 || stickRX > 20000 )
		{
			if (!m_bTrigger)
			{
				m_nCnt++;
				m_bTrigger = true;
				CSound::SetVolume(SE_PAPER, 1.0f);
				CSound::Play(SE_PAPER);
				//if (m_nCnt > 5) m_nCnt = 0;
			}
		}
		// �X�e�B�b�N����ɌX�����Ƃ�
		else if (stickLX < -20000 || stickRX < -20000 )
		{
			if (!m_bTrigger)
			{
				m_nCnt--;
				m_bTrigger = true;
				CSound::SetVolume(SE_PAPER, 1.0f);
				CSound::Play(SE_PAPER);
				//if (m_nCnt < 0) m_nCnt = 5;
			}
		}
		else
		{
			m_bTrigger = false;
		}

		if (GetKeyTrigger(VK_RIGHT) || GetKeyTrigger(VK_D) || GetJoyRelease(0, JOYSTICKID1) || GetKeyTrigger(VK_RETURN) || GetKeyTrigger(VK_SPACE))
		{
			m_nCnt++;
			CSound::SetVolume(SE_PAPER, 1.0f);
			CSound::Play(SE_PAPER);
		 }

		if (GetKeyTrigger(VK_LEFT) || GetKeyTrigger(VK_A) || GetJoyRelease(0, JOYSTICKID2))
		{
			m_nCnt--;
			CSound::SetVolume(SE_PAPER, 1.0f);
			CSound::Play(SE_PAPER);
		}

		if (m_bPopupNum2[0])
		{
			if (m_nCnt > 3)
			{
				
				// �Q�[���ɖ߂�
				if (GetJoyRelease(0, JOYSTICKID1) || GetKeyTrigger(VK_RETURN) || GetKeyTrigger(VK_SPACE))	// �R���g���[���[A�{�^��
				{
					if (m_bPopup)
					{
						m_bPopup = false;
					}

				}
				m_nCnt = 3;
			}

				
			if (m_nCnt < 0) m_nCnt = 0;
			
			switch (m_nCnt)
			{
			case 0:
				CreateTextureFromFile(pDevice, PATH_POPUP1_TEXTURE, &m_pTexture);
				break;
			case 1:
				CreateTextureFromFile(pDevice, PATH_POPUP2_TEXTURE, &m_pTexture);
				break;
			case 2:
				CreateTextureFromFile(pDevice, PATH_POPUP3_TEXTURE, &m_pTexture);
				break;
			case 3:
				CreateTextureFromFile(pDevice, PATH_POPUP4_TEXTURE, &m_pTexture);
				break;
			case 4:
				CreateTextureFromFile(pDevice, PATH_POPUP6_TEXTURE, &m_pTexture);
				break;
			case 5:
				CreateTextureFromFile(pDevice, PATH_POPUP7_TEXTURE, &m_pTexture);
				break;
			case 6:
				CreateTextureFromFile(pDevice, PATH_POPUP8_TEXTURE, &m_pTexture);
				break;
			case 7:
				CreateTextureFromFile(pDevice, PATH_POPUP4_TEXTURE, &m_pTexture);
				break;
			default:
				break;
			}
		}
		if (m_bPopupNum2[6])
		{
			if (m_nCnt > 1)
			{
			
				// �Q�[���ɖ߂�
				if (GetJoyRelease(0, JOYSTICKID1) || GetKeyTrigger(VK_RETURN) || GetKeyTrigger(VK_SPACE))	// �R���g���[���[A�{�^��
				{
					if (m_bPopup)
					{
						m_bPopup = false;
					}
				}
				m_nCnt = 1;
			}
			if (m_nCnt < 0) m_nCnt = 0;
			switch (m_nCnt)
			{
			case 0:
				CreateTextureFromFile(pDevice, PATH_POPUP5_TEXTURE, &m_pTexture);
				break;
			case 1:
				CreateTextureFromFile(pDevice, PATH_POPUP6_TEXTURE, &m_pTexture);
				break;

			default:
				break;
			}
		}
		if (m_bPopupNum2[7])
		{
			// �Q�[���ɖ߂�
			if (GetJoyRelease(0, JOYSTICKID1) || GetKeyTrigger(VK_RETURN) || GetKeyTrigger(VK_SPACE))	// �R���g���[���[A�{�^��
			{
				if (m_bPopup)
				{
					m_bPopup = false;
				}

			}
		}
		if (m_bPopupNum2[10])
		{
			if (m_nCnt > 1)
			{
				
				// �Q�[���ɖ߂�
				if (GetJoyRelease(0, JOYSTICKID1) || GetKeyTrigger(VK_RETURN) || GetKeyTrigger(VK_SPACE))	// �R���g���[���[A�{�^��
				{
					if (m_bPopup)
					{
						m_bPopup = false;
					}
				}
				m_nCnt = 1;
			}
			if (m_nCnt < 0) m_nCnt = 0;
			switch (m_nCnt)
			{
			case 0:
				CreateTextureFromFile(pDevice, PATH_POPUP10_TEXTURE, &m_pTexture);
				break;
			case 1:
				CreateTextureFromFile(pDevice, PATH_POPUP11_TEXTURE, &m_pTexture);
				break;
			
			default:
				break;
			}
		}
	}
	else
	{
		m_size.y -= 100.0f;
		if (m_size.y < 0)
		{
			m_size.y = 0;
			m_size.x -= 100.0f;
			if (m_size.x < 0)
			{
				m_size.x = 0;

			}
		}
		m_bPopupNum2[0] = false;
		m_bPopupNum2[6] = false;
		m_bPopupNum2[10] = false;
		m_bPaperTrriger = false;
	}

	//
	switch (stage)
	{
		
	case STAGE_1:
		// �|�b�v�A�b�v1�`4
		if (!m_bPopupNum[0] && CollisionAABB(GetModelPos(),XMFLOAT3(10,1000,10), XMFLOAT3(-1000, 600, -1500),XMFLOAT3(300, 1000, 300)))
		{
			
			//CreateTextureFromFile(pDevice, PATH_POPUP1_TEXTURE, &m_pTexture);
			m_bPopupNum[0] = true;
			m_bPopupNum2[0] = true;

			m_bPopup = true;
		}

		// �|�b�v�A�b�v5�`6
		if (!m_bPopupNum[6] && CollisionAABB(GetModelPos(), XMFLOAT3(10, 1000, 10), XMFLOAT3(-1300, 600, 0), XMFLOAT3(300, 1000, 300)))
		{

			//CreateTextureFromFile(pDevice, PATH_POPUP7_TEXTURE, &m_pTexture);
			m_bPopupNum[6] = true;
			m_bPopupNum2[6] = true;

			m_bPopup = true;
		}

		// �|�b�v�A�b�v7
		if (!m_bPopupNum[7] && CollisionAABB(GetModelPos(), XMFLOAT3(10, 1000, 10), XMFLOAT3(-600, 800, 900), XMFLOAT3(100, 1000, 100)))
		{

			CreateTextureFromFile(pDevice, PATH_POPUP7_TEXTURE, &m_pTexture);
			m_bPopupNum[7] = true;
			m_bPopupNum2[7] = true;
			
			m_bPopup = true;
		}

		// �|�b�v�A�b�v4
		/*if (!m_bPopupNum[3]&&GetSTM() < 100)
		{
			CreateTextureFromFile(pDevice, PATH_POPUP3_TEXTURE, &m_pTexture);
			m_bPopupNum[3] = true;
			m_bPopup = true;
		}*/

		// �X�^����Tips
		/*if (!m_bPopupNum[4] && (GetStanModel() || GetOverHeartModel()))
		{
			CreateTextureFromFile(pDevice, PATH_POPUP5_TEXTURE, &m_pTexture);
			m_bPopupNum[4] = true;
			m_bPopup = true;
		}*/
		break;
	case STAGE_2:
		break;
	case STAGE_3:
		// �G�U��Tips
		if (!m_bPopupNum[10] && CollisionAABB(GetModelPos(), XMFLOAT3(10, 1000, 10), GetModelPos(), XMFLOAT3(100, 1000, 100)))
		{
			//CreateTextureFromFile(pDevice, PATH_POPUP5_TEXTURE, &m_pTexture);
			m_bPopupNum[10] = true;
			m_bPopupNum2[10] = true;
			m_bPopup = true;
		}
		break;
	case STAGE_4:
		break;
	case STAGE_5:
		break;
	case MAX_STAGE:
		break;
	default:
		break;
	}
#if _DEBUG
	
	// �f�o�b�N�p������
	PrintDebugProc("m_nCnt:%d\n",m_nCnt);
	PrintDebugProc("\n");
#endif
}
void Tutorial::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��		

	// �w�i
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size.x, m_size.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos.x, m_pos.y);	// �|���S���ʒu
	SetPolygonTexture(m_pTexture);		// �|���S���e�N�X�`��
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x

	DrawPolygon(pDC);				// �|���S���`��		
	
	SetBlendState(BS_NONE);	// �A���t�@�u�����h����		
}