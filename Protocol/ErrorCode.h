#ifndef __ERRORCODE_H__
#define __ERRORCODE_H__

#include "HawkUtil.h"

namespace Hawk
{
	//��½ģ�������[100-150]
	namespace LoginErr
	{
		enum
		{
			//�û����Ƿ�
			NAME_INVALID = 100,
			//�û�������
			NAME_ERROR = 101,
			//�������
			PWD_ERROR = 102,
		};
	};

}
#endif
