#ifndef __STDPROTOCOL_H__
#define __STDPROTOCOL_H__

#include "ProtocolId.h"
#include "ErrorCode.h"

namespace Hawk
{
	//����֪ͨ
	class ErrNotify : public HawkProtocol
	{
	public:
		ErrNotify(UInt16 iErrId = 0, Int8 iMode = 0) : HawkProtocol(ProtocolId::ERR_NOTIFY), m_iErrId(iErrId), m_iMode(iMode)
		{
		};

		virtual HawkProtocol* Clone() const
		{
			return new ErrNotify;
		};

		virtual HawkOctetsStream& Marshal(HawkOctetsStream& rhsOS)
		{
			rhsOS << m_iErrId << m_iMode;
			return rhsOS;
		};

		virtual HawkOctetsStream& Unmarshal(HawkOctetsStream& rhsOS)
		{
			rhsOS >> m_iErrId >> m_iMode;
			return rhsOS;
		};

	public:
		UInt16 m_iErrId;
		Int8 m_iMode;
	};

	//��Ϣ֪ͨ
	class MsgNotify : public HawkProtocol
	{
	public:
		MsgNotify(const UString& sMsg = UString(), Int8 iMode = 0) : HawkProtocol(ProtocolId::MSG_NOTIFY), m_sMsg(sMsg), m_iMode(iMode)
		{
		};

		virtual HawkProtocol* Clone() const
		{
			return new MsgNotify;
		};

		virtual HawkOctetsStream& Marshal(HawkOctetsStream& rhsOS)
		{
			rhsOS << m_sMsg << m_iMode;
			return rhsOS;
		};

		virtual HawkOctetsStream& Unmarshal(HawkOctetsStream& rhsOS)
		{
			rhsOS >> m_sMsg >> m_iMode;
			return rhsOS;
		};

	public:
		UString m_sMsg;
		Int8 m_iMode;
	};

	//ʱ��ͬ��
	class TimeSync : public HawkProtocol
	{
	public:
		TimeSync(UInt32 iTime = 0) : HawkProtocol(ProtocolId::TIME_SYNC), m_iTime(iTime)
		{
		};

		virtual HawkProtocol* Clone() const
		{
			return new TimeSync;
		};

		virtual HawkOctetsStream& Marshal(HawkOctetsStream& rhsOS)
		{
			rhsOS << m_iTime;
			return rhsOS;
		};

		virtual HawkOctetsStream& Unmarshal(HawkOctetsStream& rhsOS)
		{
			rhsOS >> m_iTime;
			return rhsOS;
		};

	public:
		UInt32 m_iTime;
	};

}
#endif
