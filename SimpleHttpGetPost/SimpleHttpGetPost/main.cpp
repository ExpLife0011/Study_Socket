#include <winsock.h> 
#include "HttpConnect.h"
#include "jsoncpp/json.h"

int main(int agrc,char* agrv[])
{
	HttpConnect http;
	// ������д�ֻ��ź�key��tpl_id
	std::string  strContent = "mobile=18888888888&tpl_id=tpl_id&key=key";
	// ע��û��HTTPͷ��
	std::string  host = "v.juhe.cn";
	std::string  path = "/sms/send.php";
	http.getData(host,path,strContent);
	// ��ȡ����Ľ��
	std::string strGetResult = http.GetLastRequestResult();
	
	printf("\n\n�������\n");
	printf("Result: %s \n", strGetResult.c_str());
	if (!strGetResult.empty())
	{
		// ����ƽ̨������Ϣ
		std::string strReason;
		std::string strResult;
		std::string strSid;
		int	nFee = 0;
		int nCount = 0;
		std::string strErrCode;
		Json::Reader reader;
		Json::Value  root;
		// ������������
		// strGetResult = "{\"reason\":\"�����ɹ�\",\"result\":{\"sid\":\"201808211342552514347\",\"fee\":1,\"count\":1},\"error_code\":0}";
		if (reader.parse(strGetResult, root))
		{
			if (!root["reason"].isNull())
			{
				strReason = root["reason"].asString();
			}
			// �����ֶν���
			if (!root["result"].isNull())
			{
				if (root["result"].isArray())
				{
					printf("sadfsd\n");
				}
				Json::Value jsonResult = root["result"];
				if (!jsonResult["sid"].isNull())
				{
					strSid = jsonResult["sid"].asString();
				}
				if (!jsonResult["fee"].isNull())
				{
					nFee = jsonResult["fee"].isInt();
				}
				if (!jsonResult["count"].isNull())
				{
					nCount = jsonResult["count"].isInt();
				}
			}
			if (!root["error_code"].isNull())
			{
				strReason = root["error_code"].asString();
			}
		}
	}
	return 0;
}