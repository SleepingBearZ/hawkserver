ProtocolId = 
{
	--����֪ͨ
	ERR_NOTIFY = 100,
	--��Ϣ֪ͨ
	MSG_NOTIFY = 101,
	--ʱ��ͬ��
	TIME_SYNC = 102,
	--������Ϸ
	LOGIN_GAME = 200,
	--�߳���Ϸ
	KICKOUT_GAME = 201,
	--��ҳ�ʼ��
	PLAYER_INIT = 202,
	--ͬ���������
	PLAYER_ASSEMBLY = 203,
}

ProtocolStub = 
{
	[100] = ErrNotify,
	[101] = MsgNotify,
	[102] = TimeSync,
	[200] = LoginGame,
	[201] = KickoutGame,
	[202] = PlayerInit,
	[203] = PlayerAssembly,
}
