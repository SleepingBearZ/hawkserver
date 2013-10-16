#ifndef __GSPROTOCOL_H__
#define __GSPROTOCOL_H__

#include "StdProtocol.h"

namespace Hawk
{
	class PlayerInfo : public MarshalData
	{
	public:
		PlayerInfo(UInt32 iPlayerId = 0, const UString& sNickName = UString(), UInt8 iGender = 0) : m_iPlayerId(iPlayerId), m_sNickName(sNickName), m_iGender(iGender)
		{
		};

		PlayerInfo(const PlayerInfo& rhs) : m_iPlayerId(rhs.m_iPlayerId), m_sNickName(rhs.m_sNickName), m_iGender(rhs.m_iGender)
		{
		};

		virtual MarshalData* Clone() const
		{
			return new PlayerInfo;
		};

		virtual PlayerInfo& operator = (const PlayerInfo& rhs)
		{
			if(this != &rhs)
			{
				m_iPlayerId = rhs.m_iPlayerId;
				m_sNickName = rhs.m_sNickName;
				m_iGender = rhs.m_iGender;
			}
			return *this;
		};

		virtual HawkOctetsStream& Marshal(HawkOctetsStream& rhsOS)
		{
			rhsOS << m_iPlayerId << m_sNickName << m_iGender;
			return rhsOS;
		};

		virtual HawkOctetsStream& Unmarshal(HawkOctetsStream& rhsOS)
		{
			rhsOS >> m_iPlayerId >> m_sNickName >> m_iGender;
			return rhsOS;
		};

	public:
		UInt32 m_iPlayerId;
		UString m_sNickName;
		UInt8 m_iGender;
	};

	//������Ϸ
	class LoginGame : public HawkProtocol
	{
	public:
		LoginGame(const UString& sName = UString(), const UString& sPwd = UString(), UInt8 iFlag = 0) : HawkProtocol(ProtocolId::LOGIN_GAME), m_sName(sName), m_sPwd(sPwd), m_iFlag(iFlag)
		{
		};

		virtual HawkProtocol* Clone() const
		{
			return new LoginGame;
		};

		virtual HawkOctetsStream& Marshal(HawkOctetsStream& rhsOS)
		{
			rhsOS << m_sName << m_sPwd << m_iFlag;
			return rhsOS;
		};

		virtual HawkOctetsStream& Unmarshal(HawkOctetsStream& rhsOS)
		{
			rhsOS >> m_sName >> m_sPwd >> m_iFlag;
			return rhsOS;
		};

	public:
		UString m_sName;
		UString m_sPwd;
		UInt8 m_iFlag;
	};

	//�߳���Ϸ
	class KickoutGame : public HawkProtocol
	{
	public:
		KickoutGame(UInt32 iPlayerId = 0, const UString& sName = UString()) : HawkProtocol(ProtocolId::KICKOUT_GAME), m_iPlayerId(iPlayerId), m_sName(sName)
		{
		};

		virtual HawkProtocol* Clone() const
		{
			return new KickoutGame;
		};

		virtual HawkOctetsStream& Marshal(HawkOctetsStream& rhsOS)
		{
			rhsOS << m_iPlayerId << m_sName;
			return rhsOS;
		};

		virtual HawkOctetsStream& Unmarshal(HawkOctetsStream& rhsOS)
		{
			rhsOS >> m_iPlayerId >> m_sName;
			return rhsOS;
		};

	public:
		UInt32 m_iPlayerId;
		UString m_sName;
	};

	//��ҳ�ʼ��
	class PlayerInit : public HawkProtocol
	{
	public:
		PlayerInit(const PlayerInfo& sInfo = PlayerInfo()) : HawkProtocol(ProtocolId::PLAYER_INIT), m_sInfo(sInfo)
		{
		};

		virtual HawkProtocol* Clone() const
		{
			return new PlayerInit;
		};

		virtual HawkOctetsStream& Marshal(HawkOctetsStream& rhsOS)
		{
			rhsOS << m_sInfo;
			return rhsOS;
		};

		virtual HawkOctetsStream& Unmarshal(HawkOctetsStream& rhsOS)
		{
			rhsOS >> m_sInfo;
			return rhsOS;
		};

	public:
		PlayerInfo m_sInfo;
	};

	//ͬ���������
	class PlayerAssembly : public HawkProtocol
	{
	public:
		PlayerAssembly(UInt32 iPlayerId = 0, UInt32 iSvrId = 0) : HawkProtocol(ProtocolId::PLAYER_ASSEMBLY), m_iPlayerId(iPlayerId), m_iSvrId(iSvrId)
		{
		};

		virtual HawkProtocol* Clone() const
		{
			return new PlayerAssembly;
		};

		virtual HawkOctetsStream& Marshal(HawkOctetsStream& rhsOS)
		{
			rhsOS << m_iPlayerId << m_iSvrId;
			return rhsOS;
		};

		virtual HawkOctetsStream& Unmarshal(HawkOctetsStream& rhsOS)
		{
			rhsOS >> m_iPlayerId >> m_iSvrId;
			return rhsOS;
		};

	public:
		UInt32 m_iPlayerId;
		UInt32 m_iSvrId;
	};

}
#endif
