//MYQQA版本API

/// <summary>
/// MYQQA版本Ver1.0.3新增API
/// </summary>

MQAAPI(ApplyGroupEventEx, Text, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, LLInteger fromSeq, Integer op, Integer fromType, Text reason)
MQAAPI(GetFriendFileDownUrl,Text, LLInteger botQQ, Text FileId, Text fileName)
MQAAPI(InviteGroup_other, void, LLInteger botQQ, LLInteger fromGroupId, LLInteger objQQ, LLInteger toGroupId)
MQAAPI(GetVer, Text)
MQAAPI(GetBotStatus, Integer, Text botQQ)

/// <summary>
/// MYQQA版本Ver1.0.2前所有API
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
//处理群验证
MQAAPI(ApplyGroupEvent, void, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, LLInteger fromSeq, Integer op, Integer fromType)
//处理好友验证，#好友事件_好友请求
MQAAPI(ApplyFriendEvent, void, LLInteger botQQ, LLInteger objQQ, LLInteger fromSeq, Integer op)
//发送封包，结果十六进制到字节集
MQAAPI(SendPacket, Text,LLInteger botQQ, Text cmd, Text pack, Integer time_out)
//取语音下载地址
MQAAPI(GetAudioUrl, Text, LLInteger botQQ, Text token, Text MD5)
//取Skey
MQAAPI(GetSkey, Text, LLInteger botQQ)
//取Pskey
MQAAPI(GetPskey, Text, LLInteger botQQ, Text domain)
//取Clientkey
MQAAPI(GetClientkey, Text, LLInteger botQQ)
//取在线QQ，#换行符的，一行一个
MQAAPI(GetOnlineQQ, Text)
//取所有QQ，#换行符的，一行一个
MQAAPI(GetAllQQ, Text)
//取好友列表，返回json
MQAAPI(GetFriends, Text, LLInteger botQQ)
//取群列表，返回json
MQAAPI(GetGroups, Text, LLInteger botQQ)
//取群成员列表，返回json
MQAAPI(GetGroupMembers, Text, LLInteger botQQ, LLInteger groupId)
//设置或取消管理
MQAAPI(SetManager, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Integer op)
//取管理员列表，包括群主，返回json
MQAAPI(GetManager, Text, LLInteger botQQ, LLInteger groupId)
//踢出群成员
MQAAPI(RemoveMember, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, bool refuseJoin)
//修改签名
MQAAPI(SetSign, bool, LLInteger botQQ, Text newSign)
//修改昵称
MQAAPI(SetNick, bool, LLInteger botQQ, Text newNick)
//设置专属头衔
MQAAPI(SetRank, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Text rank)
//拍一拍_群
MQAAPI(TakeGroup, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
//拍一拍_好友头像
MQAAPI(TakeFriendsPic, bool, LLInteger botQQ, LLInteger objQQ)
//拍一拍_好友在线状态
MQAAPI(TakeFriendsOnline, bool, LLInteger botQQ, LLInteger objQQ)
//禁言某人
MQAAPI(ShutUp, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Integer time)
//退群
MQAAPI(Quit, bool, LLInteger botQQ, LLInteger groupId)
//解散群
MQAAPI(DelGroup, bool, LLInteger botQQ, LLInteger groupId)
//全员禁言
MQAAPI(ShutUpAll, bool, LLInteger botQQ, LLInteger groupId, bool isOpen)
//取好友图片上传信息
MQAAPI(GetUploadInfo, Text, LLInteger botQQ, LLInteger objQQ, Text pic_md5, LLInteger pic_size)
//取群文件信息
MQAAPI(GetGroupFileInfo, Text, LLInteger botQQ, LLInteger groupId, Text FileId)
//公众号会员签到
MQAAPI(vip_pub_subbutton_qiandao, bool, LLInteger botQQ)
//手机会员网页签到
MQAAPI(vip_qiandao_web, bool, LLInteger botQQ)
//群礼物_抽取，群聊等级抽礼物8000-么有抽到，7779-等级不够
MQAAPI(draw_lucky_gift, Integer, LLInteger botQQ, LLInteger groupId)
//搜索音乐
MQAAPI(QueryMusicInfo_fcg_music_search, Text, LLInteger botQQ, Text keyword)
//查看音乐详情
MQAAPI(QueryMusicInfo_fcg_music_get_song_info_batch, Text, LLInteger botQQ, Text songId)
//查看转发聊天记录内容
MQAAPI(MultiMsg_ApplyDown_Group, Text, LLInteger botQQ, Text resId, Integer type)
//上传群文件
MQAAPI(UpFlieGroup, void, LLInteger botQQ, LLInteger groupId, Text file_path, Text to_folder)
//取频道用户所在地
MQAAPI(GetGuildUserHome, Text, LLInteger botQQ, LLInteger guildId, LLInteger userId)
//取频道用户昵称
MQAAPI(GetGuildUserName, Text, LLInteger botQQ, LLInteger guildId, LLInteger userId)
//取加入频道时间
MQAAPI(GetJoinGuildTime, Text, LLInteger botQQ, LLInteger guildId, LLInteger userId)
//取频道用户头像下载链接
MQAAPI(GetGuildHead, Text, LLInteger botQQ, LLInteger guildId, LLInteger userId)
//取子频道列表，返回json
MQAAPI(GetGuildChannelList, Text, LLInteger botQQ, LLInteger guildId)
//发送群json消息
MQAAPI(SendGroupJson, Integer, LLInteger botQQ, LLInteger groupId, Text json, bool anony)
//撤回子频道消息
MQAAPI(PbMsgWithDraw_ChannelGuild, bool, LLInteger botQQ, LLInteger guildId, LLInteger subGuildId, Integer MsgReq)
//频道设置_全员禁言
MQAAPI(ChannelSet_totalSilence, bool, LLInteger botQQ, LLInteger guildId, LLInteger time)
//取个性签名
MQAAPI(GetSign, Text, LLInteger botQQ, LLInteger objQQ)
//置群名片
MQAAPI(SetGroupCard, bool, LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Text card)
//机器人是否被禁言，若被禁言返回剩余禁言时长
MQAAPI(BotIsShutUp, LLInteger, LLInteger botQQ, LLInteger groupId)
//允许anony聊天
MQAAPI(SetGroupAnonOpen, bool, LLInteger botQQ, LLInteger groupId)
//禁止anony聊天
MQAAPI(SetGroupAnonClose, bool, LLInteger botQQ, LLInteger groupId)
//点赞
MQAAPI(Like, Text, LLInteger botQQ, LLInteger objQQ)
//设置机器人频道名称
MQAAPI(SetRobotGuildNick, bool, LLInteger botQQ, LLInteger GuildId, Text Nick)
//退出频道
MQAAPI(QuitGuild, bool, LLInteger botQQ, LLInteger GuildId)
//查询红包领取详情，返回json
MQAAPI(GetRedPackDetail, Text, LLInteger botQQ, LLInteger groupId, Text listid, Text authkey)
//添加管家问答，返回json
MQAAPI(AddBotKeyWord, Text, LLInteger botQQ, LLInteger groupId, Text question, Text msg_content)
//取群信息，返回json
MQAAPI(GetGroupInfo, Text, LLInteger botQQ, LLInteger groupId)
//取群名片
MQAAPI(GetGroupMemberCard, Text, LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
//取群文件列表，返回json
MQAAPI(GetGroupFileList, Text, LLInteger botQQ, LLInteger groupId)
//取群文件下载链接
MQAAPI(GetGroupFileDownUrl, Text, LLInteger botQQ, LLInteger groupId, Text FlieID, Text FlieName)
//取艾特全体成员剩余次数，例如：剩余xx次
MQAAPI(GetGroupAtAllNum, Text, LLInteger botQQ, LLInteger groupId)
//查询好友名片，返回json
MQAAPI(GetFriendCard, Text, LLInteger botQQ, LLInteger objQQ)
//取公众号昵称
MQAAPI(GetPublicNick, Text, LLInteger botQQ, LLInteger PublicQQ)
//开启群聊置顶
MQAAPI(TopGroup, void, LLInteger botQQ, LLInteger groupId)
//关闭群聊置顶
MQAAPI(UnTopGroup, void, LLInteger botQQ, LLInteger groupId)
//创建群文件夹，成功返回空，失败返回原因
MQAAPI(CreatGroupFloder, Text, LLInteger botQQ, LLInteger groupId, Text folderName)
//置群名
MQAAPI(SetGroupName, bool, LLInteger botQQ, LLInteger groupId, Text groupName)
//取群名_从缓存
MQAAPI(GetGroupName, Text, LLInteger botQQ, LLInteger groupId)
//置群消息接收
MQAAPI(SetGroupRecType, void, LLInteger botQQ, LLInteger groupId, Integer type)
//发送频道通行证到群
MQAAPI(GrantCheckToGroup, bool, LLInteger botQQ, LLInteger guildId, LLInteger groupId, Integer num)
//取好友在线状态：“在线”“离开”...
MQAAPI(GetFriendOnlineStatus, Text, LLInteger botQQ, LLInteger objQQ)
//强制取群匿名ID
MQAAPI(GetAnonId, LLInteger, LLInteger botQQ, LLInteger groupId)
//取群文件数量，和上限数量，返回json
MQAAPI(GetGroupFileNum, Text, LLInteger botQQ, LLInteger groupId)
//取群文件容量，和总容量，返回json
MQAAPI(GetGroupFileCapacity, Text, LLInteger botQQ, LLInteger groupId)
//发起群收钱，成功返回c_no，失败返回空
MQAAPI(CreateGroupPay, Text, LLInteger botQQ, LLInteger groupId, Text title, Integer type, Text objQQ, Text money)
//关闭群收钱，成功返回真，失败返回假
MQAAPI(CloseGroupPay, bool, LLInteger botQQ, Text c_no)
//查询群收钱账单详情，成功返回json，可调用Api_GetGroupPayIsOk（群收钱账单是否已支付）解析
MQAAPI(GetGroupPayDetail, Text, LLInteger botQQ, Text c_no)
//群收钱账单是否已支付，已支付返回1，未支付返回0
MQAAPI(GetGroupPayIsOk, Integer, LLInteger botQQ, Text payDetail)
//发送群收钱账单催收通知，成功返回1，失败返回0
MQAAPI(SendGroupPayMsg, Integer, LLInteger botQQ, Text c_no)
//普通红包，成功success，否则为失败原因
MQAAPI(RedPack_Ordinary, Text, LLInteger botQQ, Text payPwd, Text sourceId, Text num, Text money, Text greeting, Integer type1)
//拼手气红包，成功success，否则为失败原因
MQAAPI(RedPack_Luck, Text, LLInteger botQQ, Text payPwd, Text sourceId, Text num, Text money, Text greeting)
//（已废弃）专属红包，成功success，否则为失败原因
MQAAPI(RedPack_Exclusive, Text, LLInteger botQQ, Text payPwd, Text sourceId, Text objQQ, Text num, Text money, Text greeting)
//口令红包，成功success，否则为失败原因
MQAAPI(RedPack_KeyWord, Text, LLInteger botQQ, Text payPwd, Text sourceId, Text num, Text money, Text discourse, Integer type)
//转账，成功success，否则为失败原因
MQAAPI(TransferAccounts, Text, LLInteger botQQ, Text payPwd, Text objQQ, Text objNick, Text money, Text msg, Integer type)
//查询钱包余额，成功返回余额数值，否则返回失败原因
MQAAPI(QueryBalance, Text, LLInteger botQQ, Text payPwd)
//查询红包记录，成功返回余额数值，否则返回失败原因
MQAAPI(RedPack_Log, Text, LLInteger botQQ, Text payPwd, Text year, Integer typ, Integer page)
//取自身guildId_从缓存
MQAAPI(GetGuildSelfId_cache, Text, LLInteger botQQ)
//取cookies
MQAAPI(GetCookies, Text, LLInteger botQQ)
//上传小视频，成功返回消息时间戳
MQAAPI(UploadLitleVideo, Integer, LLInteger botQQ, LLInteger groupId, Text filePath)
//发布群公告（成功返回真，失败返回假），调用此API应保证botQQ为管理员
MQAAPI(PBGroupNotic, bool, LLInteger botQQ, LLInteger groupId, Text title, Text content)
//取群公告
MQAAPI(GetGroupNotice, Text, LLInteger botQQ, LLInteger groupId)
//取图片下载连接
MQAAPI(GetPicLink, Text, LLInteger botQQ, Integer type, LLInteger sourceId, Text imgId)
//获取加群链接，获取指定群的加群链接
MQAAPI(GetGroupUrl, Text, LLInteger botQQ, LLInteger groupId)
//发起群投票_单选，返回投票fid
MQAAPI(PublishVote_A, Text, LLInteger botQQ, LLInteger groupId, Text title, Text option1, Text option2, Text option3, Text deadline, Text anony)
//发起群投票_多选，返回投票fid
MQAAPI(PublishVote_B, Text, LLInteger botQQ, LLInteger groupId, Text title, Text option1, Text option2, Text option3, Text much, Text deadline, Text anony)
//取群成员头衔，返回json，如果medalList[0]['medal_desc']=私人订制，无上荣耀，那么medalList[0].name就是专属头衔，如果medalList[0]['medal_desc']=活跃等级，那么medalList[0].name就是活跃头衔
MQAAPI(GetGroupMerRank, Text, LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
//取群设置信息，包含了常用的群设置信息、全群禁言、自己被禁言、被禁言列表等信息，返回json
MQAAPI(GetGroupSetInfo, Text, LLInteger botQQ, LLInteger groupId)
//上传照片墙，成功返回filekey，可用来删除照片墙，失败返回空
MQAAPI(UpPhotoWall, Text, LLInteger botQQ, Text imgPath)
//获取照片墙，成功返回json，失败返回空
MQAAPI(GetPhotoWall, Text, LLInteger botQQ, Text objQQ)
//删除照片墙，成功返回真，失败返回假
MQAAPI(DelPhotoWall, bool, LLInteger botQQ, Text filekey)
//获取自己在某个群里是否被禁言，0=没有被禁言，否则为剩余禁言秒数，如需频繁使用，请调用取群设置信息(Api_GetGroupSetInfo)，可同时获得全群禁言信息
MQAAPI(getMeIsShutup, Integer, LLInteger botQQ, LLInteger groupId)
//获取群里否开启了全体禁言，真=开启了，假=未开启，如需频繁使用，请调用取群设置信息(Api_GetGroupSetInfo)，可同时获得自己被禁言信息
MQAAPI(getAllIsShutup, bool, LLInteger botQQ, LLInteger groupId)
//获取其他人在某个群里是否被禁言，0=没有被禁言，否则为剩余禁言秒数
MQAAPI(getOthIsShutup, Integer, LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
//取是否允许群成员发起临时会话，稳定版，如需频繁使用，请调用取群设置信息(Api_GetGroupSetInfo)，可同时获得是否允许群成员发起群聊等其他群设置信息
MQAAPI(GetGroupTempSessionEx, bool, LLInteger botQQ, LLInteger sourceId)
//取是否允许群成员发起群聊，稳定版，如需频繁使用，请调用取群设置信息(Api_GetGroupSetInfo)，可同时获得是否允许群成员发起临时会话等其他群设置信息
MQAAPI(GetGroupLaunchNewEx, bool, LLInteger botQQ, LLInteger sourceId)
//添加QQ，添加QQ到框架里
MQAAPI(AddQQ, bool,Text QQ, Text pwd, Integer type, bool savePwd)
//获取登录二维码，例如：{"qrcode_path":"C:\Users\13301\Desktop\MyQQA\data\cache\363751070.jpg","qrcode_sign":"33DBDB7583E601FFBBF0BF38FD1DE8C41293F821F74D2E40"}
MQAAPI(GetQrcode, Text, Text QQ)
MQAAPI(GetOffQQ, Text)
//检查登录二维码状态，具体返回值请看文档, 
MQAAPI(CationQrcode, Text, LLInteger QQ)
//登录指定QQ，应确保QQ号码在列表中已存在
MQAAPI(Login, void, LLInteger botQQ)
//下线指定QQ，应确保QQ号码已在列表中且在线
MQAAPI(Logout, void, LLInteger botQQ)
//删除指定QQ下线，应确保QQ号码在列表中已存在
MQAAPI(Delete, void, LLInteger botQQ)
//请确保bin目录有ffmpeg转码库(框架不自带)，成功返回amr文件完整路径，可直接调用上传语音api，失败返回空
MQAAPI(Mp3ToAmr, Text, Text mp3, Text amr)
//请确保bin目录有ffmpeg转码库(框架不自带)，成功返回amr文件完整路径，可直接调用上传语音api，失败返回空
MQAAPI(WavToAmr, Text, Text wav, Text amr)
/*
* 需要其他Api请根据官网自行添加...
* MQAAPI(Api后缀, 返回类型, 参数列表)
*/