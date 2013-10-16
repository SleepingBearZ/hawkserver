#ifndef __PROTOCOLID_H__
#define __PROTOCOLID_H__

#include "HawkUtil.h"

namespace Hawk
{
	namespace ProtocolId
	{
		enum
		{
			//����֪ͨ
			ERR_NOTIFY = 100,
			//��Ϣ֪ͨ
			MSG_NOTIFY = 101,
			//ʱ��ͬ��
			TIME_SYNC = 102,
			//������Ϸ
			LOGIN_GAME = 200,
			//�߳���Ϸ
			KICKOUT_GAME = 201,
			//��ҳ�ʼ��
			PLAYER_INIT = 202,
			//ͬ���������
			PLAYER_ASSEMBLY = 203,
		};
	}
}
#endif
