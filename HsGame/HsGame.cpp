#include "HsGame.h"
#include "HsPlayer.h"

namespace Hawk
{
	HsGame* g_Game = 0;

	HsGame::HsGame() : HawkAppFrame(XID(HSO_MANAGER, HMI_APP))
	{
		HawkAssert(g_Game == 0);
		g_Game = this;

		#include "HsProtoReg.inl"
	}

	HsGame::~HsGame()
	{
		g_Game = 0;
	}

	Bool HsGame::Init(const AString& sCfgFile)
	{		
		HawkXmlFile  xmlCfg;
		AXmlDocument xmlDoc;
		//��ȡxml�����ļ�
		if (xmlCfg.Open(sCfgFile, xmlDoc))
		{
			AXmlElement* pRoot = xmlDoc.GetRoot();			

			//��ʼ����Ϸȫ�ֶ���
			if(!InitGameObj())
			{
				HawkPrint("GameServer Init GameObj Error.");
				return false;
			}
			
			//�����ļ���ȡ
			AppCfg sAppCfg;

			//������ID
			if (pRoot->GetAttribute("LineId"))
				sAppCfg.AppId = (UInt32)pRoot->GetAttribute("LineId")->IntValue();

			//�Ƿ�������̨��ӡ
			if (pRoot->GetAttribute("Console"))
				sAppCfg.Console = (UInt32)pRoot->GetAttribute("Console")->BoolValue();

			//�߼��߳���
			if (pRoot->GetChildAttribute("GsCfg", "Threads"))
				sAppCfg.Threads = (UInt32)pRoot->GetChildAttribute("GsCfg", "Threads")->IntValue();

			//����������
			if (pRoot->GetChildAttribute("GsCfg", "ConnLimit"))
				sAppCfg.Gateproxy.ConnLimit = (UInt32)pRoot->GetChildAttribute("GsCfg", "ConnLimit")->IntValue();

			//��־��������ַ
			if (pRoot->GetChildAttribute("LgCfg", "Addr"))
				sAppCfg.LogAddr = pRoot->GetChildAttribute("LgCfg", "Addr")->StringValue();

			//���ط�������˵�ַ
			if (pRoot->GetChildAttribute("GwCfg", "Backend"))
			{
				sAppCfg.Gateproxy.Address = pRoot->GetChildAttribute("GwCfg", "Backend")->StringValue();
				HawkStringUtil::Replace<AString>(sAppCfg.Gateproxy.Address, "*", "127.0.0.1");
			}

			//�Ƿ�����������ģʽ
			Bool bInnerGate = false;
			if (pRoot->GetChildAttribute("GsCfg", "InnerGate"))
				bInnerGate = pRoot->GetChildAttribute("GsCfg", "InnerGate")->BoolValue();

			//��������
			if (bInnerGate)
			{
				//��������ǰ�˵�ַ
				if (pRoot->GetChildAttribute("GwCfg", "Frontend"))
					sAppCfg.Gateway.Address = pRoot->GetChildAttribute("GwCfg", "Frontend")->StringValue();

				//��������IO�߳���
				if (pRoot->GetChildAttribute("GwCfg", "Threads"))
					sAppCfg.Gateway.Threads = (UInt32)pRoot->GetChildAttribute("GwCfg", "Threads")->IntValue();

				//��������ģʽ
				if (pRoot->GetChildAttribute("GwCfg", "Mode"))
					sAppCfg.Gateway.Mode = pRoot->GetChildAttribute("GwCfg", "Mode")->IntValue();

				//�������ؼ���
				if (pRoot->GetChildAttribute("GwCfg", "Security"))
					sAppCfg.Gateway.Security = pRoot->GetChildAttribute("GwCfg", "Security")->BoolValue();

				//�������س�ʱʱ��
				if (pRoot->GetChildAttribute("GwCfg", "KeepAlive"))
					sAppCfg.Gateway.Timeout = pRoot->GetChildAttribute("GwCfg", "KeepAlive")->IntValue();

				//��������ƽ̨
				if (pRoot->GetChildAttribute("GwCfg", "Platform"))
					sAppCfg.Gateway.Platform = pRoot->GetChildAttribute("GwCfg", "Platform")->IntValue();

				//�����������ܼ���
				if (pRoot->GetChildAttribute("GwCfg", "Profiler"))
					sAppCfg.Gateway.Profiler = pRoot->GetChildAttribute("GwCfg", "Profiler")->StringValue();
			}			

			return HawkAppFrame::Init(sAppCfg);
		}
		return false;
	}

	Bool HsGame::Run()
	{
		return HawkAppFrame::Run();
	}

	Bool HsGame::OnTick(UInt32 iPeriod)
	{
		if (!HawkAppFrame::OnTick(iPeriod))
			return false;

		//��ʱ���¶���
		static UInt32 obj_tick_time = 0;
		if (!obj_tick_time || m_iTickTime - obj_tick_time >= HS_OBJ_TICK_PERIOD)
		{
			obj_tick_time = m_iTickTime;

			TickPlayers();
			TickManagers();
		}		

		HawkSleep(DEFAULT_SLEEP);
		return true;
	}

	Bool HsGame::TickPlayers()
	{
		ObjMan* pUserMan = GetObjMan(HSO_PLAYER);
		if (pUserMan)
		{
			static XIDVector vXID;
			vXID.clear();
			if (!pUserMan->CollectObjKey(vXID))
				return false;

			return PostTick(vXID);
		}
		return false;
	}

	Bool HsGame::TickManagers()
	{
		ObjMan* pManagerMan = GetObjMan(HSO_MANAGER);
		if (pManagerMan)
		{
			static XIDVector vXID;
			vXID.clear();
			if (!pManagerMan->CollectObjKey(vXID))
				return false;

			return PostTick(vXID);
		}
		return false;
	}

	Bool HsGame::Stop()
	{
		if (!HawkAppFrame::Stop())
			return false;

		return true;
	}

	Bool HsGame::OnMessage(const HawkMsg& sMsg)
	{
		//�����ͷ�
		if (sMsg.Msg == HSM_DELOBJ)
		{
			XID sXid = sMsg.Params.Get<XID>(0);
			DeleteObj(sXid);
			return true;
		}
		return false;
	}

	Bool HsGame::InitGameObj()
	{
		//ע����������
		CreateObjMan(HSO_MANAGER);		
		CreateObjMan(HSO_PLAYER);		
		
		//TODO: ������������
		return true;
	}

	HawkAppObj*	HsGame::AppCreateObj(const XID& sXid)
	{
		HawkAppObj* pObj = 0;

		if (sXid.Type == HSO_MANAGER)
		{
			//TODO: ������������
		}
		else if (sXid.Type == HSO_PLAYER)
		{
			pObj = new HsPlayer(sXid);
		}

		HawkAssert(pObj != 0);
		return pObj;
	}

	Bool HsGame::OnSessionStart(SID iSid, const AString& sAddr)
	{
		return HawkAppFrame::OnSessionStart(iSid, sAddr);
	}

	Bool HsGame::OnSessionProtocol(SID iSid, Protocol* pProto)
	{
		return HawkAppFrame::OnSessionProtocol(iSid, pProto);
	}

	Bool HsGame::PostProtocol(SID iSid, Protocol* pProto)
	{
		XID sXid;
		ProtoType iType = pProto->GetType();
		if (iType == ProtocolId::LOGIN_GAME)
		{
			UString sName = ((LoginGame*)pProto)->m_sName;

			HawkStringUtil::Trim<UString>(sName);
			UInt32 iPlayerId = HawkStringUtil::HashString<UString>(sName);

			SafeObj user_obj(XID(HSO_PLAYER, iPlayerId));
			if(!user_obj.IsObjValid())
				CreateObj(XID(HSO_PLAYER, iPlayerId));

			sXid = XID(HSO_PLAYER, iPlayerId);
		}
		else
		{
			sXid = GetXidBySid(iSid);
		}

		return HawkAppFrame::PostProtocol(sXid, iSid, pProto);
	}

	Bool HsGame::DispatchMsg(const XID& sXid, HawkMsg* pMsg)
	{
		if (sXid == XID(HSO_MANAGER, HMI_APP))
			return OnMessage(*pMsg);

		return HawkAppFrame::DispatchMsg(sXid, pMsg);
	}

	Bool HsGame::OnSessionClose(SID iSid, const AString& sAddr)
	{
		if (m_mSidAddr.Find(iSid))
		{
			//ע: �˴��п�����δ�󶨶���SID֮ǰ���������Ϣ©��
			//��: Э��ͨ���̳߳ش���, �п����ڰ�Э��Ͷ�ݶ�δ����ʱ�����˴�����
			XID sXid = GetXidBySid(iSid);
			if (sXid.IsValid())
			{
				HawkMsg* pMsg = P_MsgManager->GetMsg(HSM_DISCONNECT);
				if (pMsg)
				{
					pMsg->Target = sXid;
					pMsg->Params.Push<SID>(iSid);
					PostMsg(pMsg);
				}
			}
		}

		return HawkAppFrame::OnSessionClose(iSid, sAddr);
	}
}
