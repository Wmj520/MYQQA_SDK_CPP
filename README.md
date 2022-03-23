# MYQQA_SDK_CPP_Ver1.0.3

MYQQA_SDK_CPP��װ���ṩ��MQA��DLL�ӿ���صĵײ��߼���Ϊ���������ṩ���ִ���C++�ӿڡ�

### Ŀ¼

[TOC]



### Demo

```c++
#include <MQAconfig.h>
#include <MQAcore/MQAHeader.h>
#include <GlobalVar.h>
using namespace MQA;
//MQA::Api		MQA �ṩ��api�����ӿ�
//MQA::Enum		MQA �¼�����
//MQA::Event	MQA ע���¼��ص�����
//MQA::Logging	MQA ��־
//MQA::�ı�����	MQA �ı�����


void processPrivatMsg(const Event::PrivateEvent& e)
{
	if (e.myUin == e.fromUin)return;
	//��־��� fun
	Api::FrameAPI::OutPut("fun");
	//��־���[info]fun
	Logging::info("fun");
	//����
	Api::MessageAPI::SendFriendMsg(std::stoll(e.myUin), std::stoll(e.fromUin), e.message_content, 0, 0);
}
/*
* ������
* ���ڸú�(MQA_REGISTER_EVENT)����������ע��ص�����
* �ھ�̬��Ա��ʼ�������ϵͳ�����¼�֮�󣬲���û������¼�����֮ǰ��ִ��,��������SDK��ע���¼��ص�
*/
MQA_REGISTER_EVENT
{
	if (EventContInit)return;
	//ע���¼��ص�����1,���ȼ�20000
	Event::reg_PrivateMsg(processPrivatMsg, 20000);
	//ע���¼��ص�����2,���ȼ�15000
	Event::reg_PrivateMsg([](const Event::PrivateEvent& e) {
		if (e.myUin == e.fromUin)return;
		Api::FrameAPI::OutPut("lambda expression");
		Api::MessageAPI::SendFriendMsg(std::stoll(e.myUin), std::stoll(e.fromUin), MQA::�ı�����::С�ƶ�����(1) + e.message_content, 0, 0);
		//��ֹ�������¼��ص�����ִ��,�����ȼ��ص�������Ȩ�ܾ�
		e.eventBlock();
	}, 15000);
	//ע���¼��ص�����3,���ȼ�10000
	Event::reg_Load([](const Event::LoadEvent& e) {
		//�����¼�����ֵΪ����,�������ȼ��ص��������������޷��޸�����״̬
		e.retIgnore();
	}, 10000);
	//ע�����ô���,���ȼ�ΪĬ��30000
	Event::reg_Setting([](const auto& e) {
		MessageBoxA(nullptr, "Text", "Caption", 0);
		});
	EventContInit = true;
}
```

### ����

- `MQA::Api` �����ռ��װ��MQA�ṩ�Ĵ󲿷�api�ӿڣ��ָ��µ�MyQQA `1.0.3` �汾
- `MQA::�ı�����` �����ռ��ṩ�˿��ٹ���MQA�ı�����Ľӿ�
- `MQA::Enum`�����ռ��װ��MQA��س��� `MQAEventEnum` ���¼�����ֵ `EventRet`...
- `MQA::Event` �����ռ��ṩ��ע��MQA���¼��ص������ӿڣ���` reg_PrivateMsg`�����ҷ�װ��MQA���¼��������࣬�� `PrivateEvent` �ȣ������¼��ص������д���
- ......

### Ԥ��

����Ŀʹ�� [Visual Studio](https://visualstudio.microsoft.com/zh-hans/) ��������ȷ����װ�� **Visual Studio 2019** ������ѡ��ʹ�� C++ �����濪��������װ�� **MSVC v142**��**Windows 10 SDK** �����

���Ѱ�װ **Visual Studio 2019**����ֱ�Ӵ�Ŀ¼�µ� **[MYQQA_SDK_CPP.sln](MYQQA_SDK_CPP.sln)** �ļ���

### �޸Ĳ����Ϣ

���� [`MQAHeader.h`](include/MQcore/MQHeader.h) �ļ��޸Ĳ����ص� `PluginId` ��`PluginAuthor`��`PluginDesc` ��`PluginVersion` ��Ϣ��������Ŀ������Ϊ��Ĳ������������Ŀ����Ҫ�� `PluginId` ��һ�£����������ܻ�����ʧ�ܡ�

### ��д���

�Ƴ� [`main/MQAdemo.cpp`](main/MQdemo.cpp) ������������޸ģ�ʵ���Լ��Ĺ��ܡ�

����API�������¼��������������ռ� `MQA` �ڲ��ҡ�

����δ��ӵ�MQA api������������ӣ�`MyQQAApi.dll` ������Ϊ`MQAHModule` ��

### ������Ŀ

�� **Visual Studio** ʹ�ÿ�ݼ� **Ctrl + Alt + F7** ������Ŀ�����ɵ� **dll�ļ�** �������ļ��� **[out](out) **�¡�

Ȼ��ֻ��Ҫ�����ɵ� **dll�ļ�** ������ **MyQQA\plugin** �ļ����£�Ȼ��� **MyQQA.exe** ���� **�������** ���ò�����ɡ�

### ע������

- ��SDK�����谲װ Visual C++ ���ٷ�����������������û���װ�����ص�ַ�� [����֧�ֵ� Visual C++ ����](https://support.microsoft.com/zh-cn/help/2977003/the-latest-supported-visual-c-downloads)��

### ���ⷴ��

���ʹ�ø�sdk�����������κ����⡢Bug����������������飬��ӭ�� [issue](https://github.com/Wmj520/MYQQA_SDK_CPP/issues) �����߼� **QQ2216193879** �������ۡ�
