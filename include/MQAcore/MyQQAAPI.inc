//MYQQA�汾API

/// <summary>
/// MYQQA�汾Ver1.0.3����API
/// </summary>

MQAAPI(ApplyGroupEventEx, Text, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, LLInteger fromSeq, Integer op, Integer fromType, Text reason)
MQAAPI(GetFriendFileDownUrl,Text, LLInteger botQQ, Text FileId, Text fileName)
MQAAPI(InviteGroup_other, void, LLInteger botQQ, LLInteger fromGroupId, LLInteger objQQ, LLInteger toGroupId)
MQAAPI(GetVer, Text)
MQAAPI(GetBotStatus, Integer, Text botQQ)

/// <summary>
/// MYQQA�汾Ver1.0.2ǰ����API
/// </summary>

MQAAPI(Output, void, Text content)
MQAAPI(SendFriendMsg, Integer, LLInteger botQQ, LLInteger objQQ, Text msgContent, Integer req, LLInteger random)
MQAAPI(SendFriendXMLMsg, Integer, LLInteger botQQ, LLInteger objQQ, Text msgContent, Integer req, LLInteger random)
MQAAPI(SendGroupMsg, Integer, LLInteger botQQ, LLInteger groupId, Text msgContent, bool anonymous)
MQAAPI(SendGroupXMLMsg, Integer, LLInteger botQQ, LLInteger groupId, Text msgContent, bool anonymous)
MQAAPI(SendGroupMemberMsg, Integer, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Text msgContent, Integer req, LLInteger random)
MQAAPI(SendGuildMsg, Integer, LLInteger botQQ, LLInteger guildId, LLInteger subGuildId, Text msgContent)
MQAAPI(GetMsgReq, Integer)
MQAAPI(GetMsgRandom, LLInteger)
MQAAPI(PbMsgWithDraw_Friend, bool, LLInteger botQQ, LLInteger objQQ, Integer req, LLInteger random, Integer recvTime)
MQAAPI(PbMsgWithDraw_Group, bool, LLInteger botQQ, LLInteger groupId,Integer req, LLInteger random)
MQAAPI(AddFriend, Text, LLInteger botQQ, LLInteger objQQ, Text Anwser)
MQAAPI(UploadFriendPic, Text, LLInteger botQQ, LLInteger objQQ, Text img_path)
MQAAPI(UploadFriendAudio, Text, LLInteger botQQ, LLInteger objQQ, Text file_path)
MQAAPI(UploadGroupPic, Text, LLInteger botQQ, LLInteger groupId, Text img_path)
MQAAPI(UploadGroupAudio, Text, LLInteger botQQ, LLInteger groupId, Text file_path)
MQAAPI(UploadHead, Integer, LLInteger botQQ, Text img_path)
MQAAPI(UploadFriendPicEx, Text, LLInteger botQQ, LLInteger objQQ, Integer ptr, Integer len)
MQAAPI(UploadGroupPicEx, Text, LLInteger botQQ, LLInteger groupId, Integer ptr, Integer len)
MQAAPI(UploadFriendAudioEx, Text, LLInteger botQQ, LLInteger objQQ, Integer ptr, Integer len)
MQAAPI(UploadGroupAudioEx, Text, LLInteger botQQ, LLInteger groupId, Integer ptr, Integer len)
MQAAPI(UploadHeadEx, Integer, LLInteger botQQ,  Integer ptr, Integer len)
MQAAPI(SetGroupMemberCard, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Text card)
MQAAPI(GetNickCache, Text, LLInteger objQQ)
MQAAPI(GetNick_Acquisition, Text, LLInteger botQQ, LLInteger objQQ)
MQAAPI(GetFriendMsg, Text, LLInteger botQQ, Integer fromReq, Integer fromSendTime, LLInteger fromSeq)
MQAAPI(GetGroupMsg, Text, LLInteger botQQ, LLInteger groupId, LLInteger objQQ,  Integer fromReq, Integer fromRecvTime, LLInteger fromMsgRandom)
//����Ⱥ��֤
MQAAPI(ApplyGroupEvent, void, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, LLInteger fromSeq, Integer op, Integer fromType)
//����������֤��#�����¼�_��������
MQAAPI(ApplyFriendEvent, void, LLInteger botQQ, LLInteger objQQ, LLInteger fromSeq, Integer op)
//���ͷ�������ʮ�����Ƶ��ֽڼ�
MQAAPI(SendPacket, Text,LLInteger botQQ, Text cmd, Text pack, Integer time_out)
//ȡ�������ص�ַ
MQAAPI(GetAudioUrl, Text, LLInteger botQQ, Text token, Text MD5)
//ȡSkey
MQAAPI(GetSkey, Text, LLInteger botQQ)
//ȡPskey
MQAAPI(GetPskey, Text, LLInteger botQQ, Text domain)
//ȡClientkey
MQAAPI(GetClientkey, Text, LLInteger botQQ)
//ȡ����QQ��#���з��ģ�һ��һ��
MQAAPI(GetOnlineQQ, Text)
//ȡ����QQ��#���з��ģ�һ��һ��
MQAAPI(GetAllQQ, Text)
//ȡ�����б�������json
MQAAPI(GetFriends, Text, LLInteger botQQ)
//ȡȺ�б�������json
MQAAPI(GetGroups, Text, LLInteger botQQ)
//ȡȺ��Ա�б�������json
MQAAPI(GetGroupMembers, Text, LLInteger botQQ, LLInteger groupId)
//���û�ȡ������
MQAAPI(SetManager, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Integer op)
//ȡ����Ա�б�������Ⱥ��������json
MQAAPI(GetManager, Text, LLInteger botQQ, LLInteger groupId)
//�߳�Ⱥ��Ա
MQAAPI(RemoveMember, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, bool refuseJoin)
//�޸�ǩ��
MQAAPI(SetSign, bool, LLInteger botQQ, Text newSign)
//�޸��ǳ�
MQAAPI(SetNick, bool, LLInteger botQQ, Text newNick)
//����ר��ͷ��
MQAAPI(SetRank, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Text rank)
//��һ��_Ⱥ
MQAAPI(TakeGroup, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
//��һ��_����ͷ��
MQAAPI(TakeFriendsPic, bool, LLInteger botQQ, LLInteger objQQ)
//��һ��_��������״̬
MQAAPI(TakeFriendsOnline, bool, LLInteger botQQ, LLInteger objQQ)
//����ĳ��
MQAAPI(ShutUp, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Integer time)
//��Ⱥ
MQAAPI(Quit, bool, LLInteger botQQ, LLInteger groupId)
//��ɢȺ
MQAAPI(DelGroup, bool, LLInteger botQQ, LLInteger groupId)
//ȫԱ����
MQAAPI(ShutUpAll, bool, LLInteger botQQ, LLInteger groupId, bool isOpen)
//ȡ����ͼƬ�ϴ���Ϣ
MQAAPI(GetUploadInfo, Text, LLInteger botQQ, LLInteger objQQ, Text pic_md5, LLInteger pic_size)
//ȡȺ�ļ���Ϣ
MQAAPI(GetGroupFileInfo, Text, LLInteger botQQ, LLInteger groupId, Text FileId)
//���ںŻ�Աǩ��
MQAAPI(vip_pub_subbutton_qiandao, bool, LLInteger botQQ)
//�ֻ���Ա��ҳǩ��
MQAAPI(vip_qiandao_web, bool, LLInteger botQQ)
//Ⱥ����_��ȡ��Ⱥ�ĵȼ�������8000-ô�г鵽��7779-�ȼ�����
MQAAPI(draw_lucky_gift, Integer, LLInteger botQQ, LLInteger groupId)
//��������
MQAAPI(QueryMusicInfo_fcg_music_search, Text, LLInteger botQQ, Text keyword)
//�鿴��������
MQAAPI(QueryMusicInfo_fcg_music_get_song_info_batch, Text, LLInteger botQQ, Text songId)
//�鿴ת�������¼����
MQAAPI(MultiMsg_ApplyDown_Group, Text, LLInteger botQQ, Text resId, Integer type)
//�ϴ�Ⱥ�ļ�
MQAAPI(UpFlieGroup, void, LLInteger botQQ, LLInteger groupId, Text file_path, Text to_folder)
//ȡƵ���û����ڵ�
MQAAPI(GetGuildUserHome, Text, LLInteger botQQ, LLInteger guildId, LLInteger userId)
//ȡƵ���û��ǳ�
MQAAPI(GetGuildUserName, Text, LLInteger botQQ, LLInteger guildId, LLInteger userId)
//ȡ����Ƶ��ʱ��
MQAAPI(GetJoinGuildTime, Text, LLInteger botQQ, LLInteger guildId, LLInteger userId)
//ȡƵ���û�ͷ����������
MQAAPI(GetGuildHead, Text, LLInteger botQQ, LLInteger guildId, LLInteger userId)
//ȡ��Ƶ���б�������json
MQAAPI(GetGuildChannelList, Text, LLInteger botQQ, LLInteger guildId)
//����Ⱥjson��Ϣ
MQAAPI(SendGroupJson, Integer, LLInteger botQQ, LLInteger groupId, Text json, bool anony)
//������Ƶ����Ϣ
MQAAPI(PbMsgWithDraw_ChannelGuild, bool, LLInteger botQQ, LLInteger guildId, LLInteger subGuildId, Integer MsgReq)
//Ƶ������_ȫԱ����
MQAAPI(ChannelSet_totalSilence, bool, LLInteger botQQ, LLInteger guildId, LLInteger time)
//ȡ����ǩ��
MQAAPI(GetSign, Text, LLInteger botQQ, LLInteger objQQ)
//��Ⱥ��Ƭ
MQAAPI(SetGroupCard, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Text card)
//�������Ƿ񱻽��ԣ��������Է���ʣ�����ʱ��
MQAAPI(BotIsShutUp, LLInteger, LLInteger botQQ, LLInteger groupId)
//����anony����
MQAAPI(SetGroupAnonOpen, bool, LLInteger botQQ, LLInteger groupId)
//��ֹanony����
MQAAPI(SetGroupAnonClose, bool, LLInteger botQQ, LLInteger groupId)
//����
MQAAPI(Like, Text, LLInteger botQQ, LLInteger objQQ)
//���û�����Ƶ������
MQAAPI(SetRobotGuildNick, bool, LLInteger botQQ, LLInteger GuildId, Text Nick)
//�˳�Ƶ��
MQAAPI(QuitGuild, bool, LLInteger botQQ, LLInteger GuildId)
//��ѯ�����ȡ���飬����json
MQAAPI(GetRedPackDetail, Text, LLInteger botQQ, LLInteger groupId, Text listid, Text authkey)
//���ӹܼ��ʴ𣬷���json
MQAAPI(AddBotKeyWord, Text, LLInteger botQQ, LLInteger groupId, Text question, Text msg_content)
//ȡȺ��Ϣ������json
MQAAPI(GetGroupInfo, Text, LLInteger botQQ, LLInteger groupId)
//ȡȺ��Ƭ
MQAAPI(GetGroupMemberCard, Text, LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
//ȡȺ�ļ��б�������json
MQAAPI(GetGroupFileList, Text, LLInteger botQQ, LLInteger groupId)
//ȡȺ�ļ���������
MQAAPI(GetGroupFileDownUrl, Text, LLInteger botQQ, LLInteger groupId, Text FlieID, Text FlieName)
//ȡ����ȫ���Աʣ����������磺ʣ��xx��
MQAAPI(GetGroupAtAllNum, Text, LLInteger botQQ, LLInteger groupId)
//��ѯ������Ƭ������json
MQAAPI(GetFriendCard, Text, LLInteger botQQ, LLInteger objQQ)
//ȡ���ں��ǳ�
MQAAPI(GetPublicNick, Text, LLInteger botQQ, LLInteger PublicQQ)
//����Ⱥ���ö�
MQAAPI(TopGroup, void, LLInteger botQQ, LLInteger groupId)
//�ر�Ⱥ���ö�
MQAAPI(UnTopGroup, void, LLInteger botQQ, LLInteger groupId)
//����Ⱥ�ļ��У��ɹ����ؿգ�ʧ�ܷ���ԭ��
MQAAPI(CreatGroupFloder, Text, LLInteger botQQ, LLInteger groupId, Text folderName)
//��Ⱥ��
MQAAPI(SetGroupName, bool, LLInteger botQQ, LLInteger groupId, Text groupName)
//ȡȺ��_�ӻ���
MQAAPI(GetGroupName, Text, LLInteger botQQ, LLInteger groupId)
//��Ⱥ��Ϣ����
MQAAPI(SetGroupRecType, void, LLInteger botQQ, LLInteger groupId, Integer type)
//����Ƶ��ͨ��֤��Ⱥ
MQAAPI(GrantCheckToGroup, bool, LLInteger botQQ, LLInteger guildId, LLInteger groupId, Integer num)
//ȡ��������״̬�������ߡ����뿪��...
MQAAPI(GetFriendOnlineStatus, Text, LLInteger botQQ, LLInteger objQQ)
//ǿ��ȡȺ����ID
MQAAPI(GetAnonId, LLInteger, LLInteger botQQ, LLInteger groupId)
//ȡȺ�ļ�����������������������json
MQAAPI(GetGroupFileNum, Text, LLInteger botQQ, LLInteger groupId)
//ȡȺ�ļ���������������������json
MQAAPI(GetGroupFileCapacity, Text, LLInteger botQQ, LLInteger groupId)
//����Ⱥ��Ǯ���ɹ�����c_no��ʧ�ܷ��ؿ�
MQAAPI(CreateGroupPay, Text, LLInteger botQQ, LLInteger groupId, Text title, Integer type, Text objQQ, Text money)
//�ر�Ⱥ��Ǯ���ɹ������棬ʧ�ܷ��ؼ�
MQAAPI(CloseGroupPay, bool, LLInteger botQQ, Text c_no)
//��ѯȺ��Ǯ�˵����飬�ɹ�����json���ɵ���Api_GetGroupPayIsOk��Ⱥ��Ǯ�˵��Ƿ���֧��������
MQAAPI(GetGroupPayDetail, Text, LLInteger botQQ, Text c_no)
//Ⱥ��Ǯ�˵��Ƿ���֧������֧������1��δ֧������0
MQAAPI(GetGroupPayIsOk, Integer, LLInteger botQQ, Text payDetail)
//����Ⱥ��Ǯ�˵�����֪ͨ���ɹ�����1��ʧ�ܷ���0
MQAAPI(SendGroupPayMsg, Integer, LLInteger botQQ, Text c_no)
//��ͨ������ɹ�success������Ϊʧ��ԭ��
MQAAPI(RedPack_Ordinary, Text, LLInteger botQQ, Text payPwd, Text sourceId, Text num, Text money, Text greeting, Integer type1)
//ƴ����������ɹ�success������Ϊʧ��ԭ��
MQAAPI(RedPack_Luck, Text, LLInteger botQQ, Text payPwd, Text sourceId, Text num, Text money, Text greeting)
//���ѷ�����ר��������ɹ�success������Ϊʧ��ԭ��
MQAAPI(RedPack_Exclusive, Text, LLInteger botQQ, Text payPwd, Text sourceId, Text objQQ, Text num, Text money, Text greeting)
//���������ɹ�success������Ϊʧ��ԭ��
MQAAPI(RedPack_KeyWord, Text, LLInteger botQQ, Text payPwd, Text sourceId, Text num, Text money, Text discourse, Integer type)
//ת�ˣ��ɹ�success������Ϊʧ��ԭ��
MQAAPI(TransferAccounts, Text, LLInteger botQQ, Text payPwd, Text objQQ, Text objNick, Text money, Text msg, Integer type)
//��ѯǮ�����ɹ����������ֵ�����򷵻�ʧ��ԭ��
MQAAPI(QueryBalance, Text, LLInteger botQQ, Text payPwd)
//��ѯ�����¼���ɹ����������ֵ�����򷵻�ʧ��ԭ��
MQAAPI(RedPack_Log, Text, LLInteger botQQ, Text payPwd, Text year, Integer typ, Integer page)
//ȡ����guildId_�ӻ���
MQAAPI(GetGuildSelfId_cache, Text, LLInteger botQQ)
//ȡcookies
MQAAPI(GetCookies, Text, LLInteger botQQ)
//�ϴ�С��Ƶ���ɹ�������Ϣʱ���
MQAAPI(UploadLitleVideo, Integer, LLInteger botQQ, LLInteger groupId, Text filePath)
//����Ⱥ���棨�ɹ������棬ʧ�ܷ��ؼ٣������ô�APIӦ��֤botQQΪ����Ա
MQAAPI(PBGroupNotic, bool, LLInteger botQQ, LLInteger groupId, Text title, Text content)
//ȡȺ����
MQAAPI(GetGroupNotice, Text, LLInteger botQQ, LLInteger groupId)
//ȡͼƬ��������
MQAAPI(GetPicLink, Text, LLInteger botQQ, Integer type, LLInteger sourceId, Text imgId)
//��ȡ��Ⱥ���ӣ���ȡָ��Ⱥ�ļ�Ⱥ����
MQAAPI(GetGroupUrl, Text, LLInteger botQQ, LLInteger groupId)
//����ȺͶƱ_��ѡ������ͶƱfid
MQAAPI(PublishVote_A, Text, LLInteger botQQ, LLInteger groupId, Text title, Text option1, Text option2, Text option3, Text deadline, Text anony)
//����ȺͶƱ_��ѡ������ͶƱfid
MQAAPI(PublishVote_B, Text, LLInteger botQQ, LLInteger groupId, Text title, Text option1, Text option2, Text option3, Text much, Text deadline, Text anony)
//ȡȺ��Աͷ�Σ�����json�����medalList[0]['medal_desc']=˽�˶��ƣ�������ҫ����ômedalList[0].name����ר��ͷ�Σ����medalList[0]['medal_desc']=��Ծ�ȼ�����ômedalList[0].name���ǻ�Ծͷ��
MQAAPI(GetGroupMerRank, Text, LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
//ȡȺ������Ϣ�������˳��õ�Ⱥ������Ϣ��ȫȺ���ԡ��Լ������ԡ��������б�����Ϣ������json
MQAAPI(GetGroupSetInfo, Text, LLInteger botQQ, LLInteger groupId)
//�ϴ���Ƭǽ���ɹ�����filekey��������ɾ����Ƭǽ��ʧ�ܷ��ؿ�
MQAAPI(UpPhotoWall, Text, LLInteger botQQ, Text imgPath)
//��ȡ��Ƭǽ���ɹ�����json��ʧ�ܷ��ؿ�
MQAAPI(GetPhotoWall, Text, LLInteger botQQ, Text objQQ)
//ɾ����Ƭǽ���ɹ������棬ʧ�ܷ��ؼ�
MQAAPI(DelPhotoWall, bool, LLInteger botQQ, Text filekey)
//��ȡ�Լ���ĳ��Ⱥ���Ƿ񱻽��ԣ�0=û�б����ԣ�����Ϊʣ���������������Ƶ��ʹ�ã������ȡȺ������Ϣ(Api_GetGroupSetInfo)����ͬʱ���ȫȺ������Ϣ
MQAAPI(getMeIsShutup, Integer, LLInteger botQQ, LLInteger groupId)
//��ȡȺ�������ȫ����ԣ���=�����ˣ���=δ����������Ƶ��ʹ�ã������ȡȺ������Ϣ(Api_GetGroupSetInfo)����ͬʱ����Լ���������Ϣ
MQAAPI(getAllIsShutup, bool, LLInteger botQQ, LLInteger groupId)
//��ȡ��������ĳ��Ⱥ���Ƿ񱻽��ԣ�0=û�б����ԣ�����Ϊʣ���������
MQAAPI(getOthIsShutup, Integer, LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
//ȡ�Ƿ�����Ⱥ��Ա������ʱ�Ự���ȶ��棬����Ƶ��ʹ�ã������ȡȺ������Ϣ(Api_GetGroupSetInfo)����ͬʱ����Ƿ�����Ⱥ��Ա����Ⱥ�ĵ�����Ⱥ������Ϣ
MQAAPI(GetGroupTempSessionEx, bool, LLInteger botQQ, LLInteger sourceId)
//ȡ�Ƿ�����Ⱥ��Ա����Ⱥ�ģ��ȶ��棬����Ƶ��ʹ�ã������ȡȺ������Ϣ(Api_GetGroupSetInfo)����ͬʱ����Ƿ�����Ⱥ��Ա������ʱ�Ự������Ⱥ������Ϣ
MQAAPI(GetGroupLaunchNewEx, bool, LLInteger botQQ, LLInteger sourceId)
//����QQ������QQ�������
MQAAPI(AddQQ, bool,Text QQ, Text pwd, Integer type, bool savePwd)
//��ȡ��¼��ά�룬���磺{"qrcode_path":"C:\Users\13301\Desktop\MyQQA\data\cache\363751070.jpg","qrcode_sign":"33DBDB7583E601FFBBF0BF38FD1DE8C41293F821F74D2E40"}
MQAAPI(GetQrcode, Text, Text QQ)
MQAAPI(GetOffQQ, Text)
//����¼��ά��״̬�����巵��ֵ�뿴�ĵ�, 
MQAAPI(CationQrcode, Text, LLInteger QQ)
//��¼ָ��QQ��Ӧȷ��QQ�������б����Ѵ���
MQAAPI(Login, void, LLInteger botQQ)
//����ָ��QQ��Ӧȷ��QQ���������б���������
MQAAPI(Logout, void, LLInteger botQQ)
//ɾ��ָ��QQ���ߣ�Ӧȷ��QQ�������б����Ѵ���
MQAAPI(Delete, void, LLInteger botQQ)
//��ȷ��binĿ¼��ffmpegת���(��ܲ��Դ�)���ɹ�����amr�ļ�����·������ֱ�ӵ����ϴ�����api��ʧ�ܷ��ؿ�
MQAAPI(Mp3ToAmr, Text, Text mp3, Text amr)
//��ȷ��binĿ¼��ffmpegת���(��ܲ��Դ�)���ɹ�����amr�ļ�����·������ֱ�ӵ����ϴ�����api��ʧ�ܷ��ؿ�
MQAAPI(WavToAmr, Text, Text wav, Text amr)
/*
* ��Ҫ����Api����ݹ�����������...
* MQAAPI(Api��׺, ��������, �����б�)
*/