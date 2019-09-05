//#pragma once
////#include <windows.h>
//
////#include <afxinet.h>
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <stdio.h> 
//#include <io.h>    
//#include <iterator>
//#include <mshtml.h> 
//#include <oleacc.h> 
//#include <atlbase.h> 
//#include <Shellapi.h>
//#include <Shlobj.h>
//#include <oleidl.h>
//#include <algorithm> 
//#include <propvarutil.h>
//
//#define MAXSIZE 1024
//
//#define STDMETHODIMP            HRESULT STDMETHODCALLTYPE
//#define STDMETHODCALLTYPE       __stdcall
//#define WM_ADDLISTITEM WM_USER + 50
//
//using namespace std;
//class Util
//{
//public :
//	 BOOL checkState;
//
//public:
//
//
//	//int转string
//	string intToString(int n){
//		
//		try{
//			std::stringstream newstr;
//			newstr << n;
//			return newstr.str();
//		}
//		catch (...){
//			return "";
//		}
//		
//	}
//	//string转int
//	int stringToInt(string  instringn){
//		try{
//			int index = _ttoi(instringn.c_str());
//			return index;
//		}
//		catch (...){
//			return -1;
//		}
//		
//	}
//	
//
//	/**
//	* 说明：去除文件后缀 只留文件名
//	* 参数：文件名
//	* 返回：纯文件名称不带后缀
//	*/
//	string getFileName(string fileName){
//		int pos = fileName.rfind(".");
//		if (pos > 0)
//			return fileName.substr(0, pos);
//		else
//			return fileName;
//	}
//
//	/**
//	* 说明：获得最后一级路径（可以获得路径的文件名）
//	* 参数：最后一级信息
//	* 返回：纯文件名称不带后缀
//	*/
//	string getPathTail(string fileName,string checkFH){
//		int pos = fileName.rfind(checkFH);
//		if (pos > 0)
//			return fileName.substr(pos+1, fileName.length());
//		else
//			return fileName;
//	}
//	/**
//	* 说明：去除最后一级路径（可以去除文件名保存路径）
//	* 参数：路径 "/" "\\"
//	* 返回：纯文件名称不带后缀
//	*/
//	string removePathTail(string fileName, string checkFH){
//		int pos = fileName.rfind(checkFH);
//		if (pos > 0)
//			return fileName.substr(0, pos);
//		else
//			return fileName;
//	}
//
//	/*
//	* 写入文件内容 不存在则创建  覆盖写入
//	* 参数一：文件路径
//	* 参数二：文件内容
//	* 返回：true成功/false失败
//	*/
//	BOOL saveFileData(string filePath, char* fileData){
//		ofstream outfile(filePath, ios::out);//ios::app表示在原文件末尾追加
//		outfile.write(fileData, strlen(fileData));
//		outfile.close();
//		return true;
//	}
//	/**
//	* 说明：字符串替换（不循环重复替换）
//	* 参数：1总字符串 2要替换的字符 3替换成的字符
//	* 返回：替换后的字符串
//	*/
//	string& replace_all_distinct(string& str, const string& old_value, const string& new_value)
//	{
//		for (string::size_type pos(0); pos != string::npos; pos += new_value.length()){
//			if ((pos = str.find(old_value, pos)) != string::npos)
//				str.replace(pos, old_value.length(), new_value);
//			else  break;
//		}
//		return   str;
//	}
//
//	/**
//	* 说明：字符串替换（循环重复替换）
//	* 参数：1总字符串 2要替换的字符 3替换成的字符
//	* 返回：替换后的字符串
//	*/
//	string& replace_all(string& str, const string& old_value, const string& new_value)
//	{
//		while (true) {
//			string::size_type pos(0);
//			if ((pos = str.find(old_value)) != string::npos)
//				str.replace(pos, old_value.length(), new_value);
//			else break;
//		}
//		return str;
//	}
//	/**
//	* 说明：根据ID获得html指定ID的html源码
//	* 参数：参数1 web对象   参数2 ID
//	* 返回：指定ID标签的HTML元素
//	*/
//	string getHtmlById(CWebBrowserUI* cWebUi,string id){
//		if (checkState == true){
//			return "";
//		}
//		checkState = true;
//		try{
//			//IDispatch *   pHtmlDocDisp = NULL;
//			CComPtr<IDispatch> dispDoc = NULL;
//			HRESULT   hr = S_FALSE;
//			CComPtr<IHTMLDocument2> spDoc = NULL;
//			IWebBrowser2* iweb2 = cWebUi->GetWebBrowser2();
//			if (iweb2 == NULL){
//				log("内容为空");
//			}
//			hr = iweb2->get_Document(&dispDoc);
//			hr = dispDoc->QueryInterface(IID_IHTMLDocument2, (LPVOID*)&spDoc);
//			IHTMLElementCollection *spElementss = NULL;
//			spDoc->get_all(&spElementss);
//			CComPtr<IDispatch>pDisp;
//
//			//char转VARIANT
//			//VARIANT myVariant;
//		//	HRESULT hrx = InitVariantFromBuffer(id.c_str(), sizeof(id.c_str())*3, &myVariant);
//			//myVariant.vt = VT_UI1;
//			//myVariant.bVal = (char)id.c_str();
//
//			VARIANT myVariant;
//			string mystring = id;
//			int mystringSize = (int)(mystring.length() + 1);
//			wchar_t* mywstring = new wchar_t[mystringSize];
//			MultiByteToWideChar(CP_UTF8, 0, mystring.c_str(), -1, mywstring, mystringSize);
//			myVariant.vt = VT_BSTR;
//			myVariant.bstrVal = mywstring;
//			
//
//			VARIANT myVarianty;
//			string mystring2 = "0";
//			int mystringSize2 = (int)(mystring2.length() + 1);
//			wchar_t* mywstring2 = new wchar_t[mystringSize2];
//			MultiByteToWideChar(CP_UTF8, 0, mystring2.c_str(), -1, mywstring2, mystringSize2);
//			myVarianty.vt = VT_BSTR;
//			myVarianty.bstrVal = mywstring2;
//			
//			spElementss->item(myVariant, myVarianty, &pDisp);
//			CComQIPtr<IHTMLElement, &IID_IHTMLElement>pElement;
//			if (pDisp == NULL){
//				return "";
//			}
//			CComBSTR pContentA;
//			pElement = pDisp;
//			pElement->get_outerHTML(&pContentA);//pElement->get_outerText(&pContentA);
//			string dataStr((_bstr_t)pContentA);
//			//释放内存
//			pDisp = NULL;
//			spElementss->Release();
//			iweb2->Release();
//			delete[] mywstring;
//			delete[] mywstring2;
//			checkState = false;
//			return dataStr;
//		}
//		catch (...){
//			checkState = false;
//			return "";
//		}
//	}
//
//
//	//写入html 指定ID的标签内容
//	string setHtmlById(CWebBrowserUI* cWebUi,string id, string value){
//		try{
//			VARIANT myVariant;
//			string mystring = id;
//			int mystringSize = (int)(mystring.length() + 1);
//			wchar_t* mywstring = new wchar_t[mystringSize];
//			MultiByteToWideChar(CP_UTF8, 0, mystring.c_str(), -1, mywstring, mystringSize);
//			myVariant.vt = VT_BSTR;
//			myVariant.bstrVal = mywstring;
//
//			VARIANT myVarianty;
//			string mystring2 = "0";
//			int mystringSize2 = (int)(mystring2.length() + 1);
//			wchar_t* mywstring2 = new wchar_t[mystringSize2];
//			MultiByteToWideChar(CP_UTF8, 0, mystring2.c_str(), -1, mywstring2, mystringSize2);
//			myVarianty.vt = VT_BSTR;
//			myVarianty.bstrVal = mywstring2;
//
//
//			CComPtr<IDispatch> dispDoc = NULL;
//			HRESULT   hr = S_FALSE;
//			CComPtr<IHTMLDocument2> spDoc = NULL;
//			IWebBrowser2* iweb2 = cWebUi->GetWebBrowser2();
//			if (iweb2 == NULL){
//				log("写入异常!");
//			}
//			hr = iweb2->get_Document(&dispDoc);
//			hr = dispDoc->QueryInterface(IID_IHTMLDocument2, (LPVOID*)&spDoc);
//
//			IHTMLElementCollection *spElementss = NULL;
//			spDoc->get_all(&spElementss);
//			CComPtr<IDispatch>pDisp;
//			spElementss->item(myVariant, myVarianty, &pDisp);
//			CComQIPtr<IHTMLElement, &IID_IHTMLElement>pElement;
//			if (pDisp == NULL)
//			{
//				return "获得标签失败！";
//			}
//			CComBSTR pContentA;
//			pElement = pDisp;
//			pElement->put_innerText(_bstr_t(value.c_str()));
//
//			//释放内存
//			spElementss->Release();
//			iweb2->Release();
//			delete[] mywstring;
//			delete[] mywstring2;
//			return "写入成功";
//		}
//		catch (...){
//			log("写入异常!");
//		}
//	}
//	/**
//	*写入Log标签内容
//	*参数一：红字  参数二：黑字    可为"" 
//	*/
//	string setLogById(CWebBrowserUI* cWebUi, string value, string value2){
//		try{
//			VARIANT myVariant;
//			string mystring = "LogDivValueTitle";
//			int mystringSize = (int)(mystring.length() + 1);
//			wchar_t* mywstring = new wchar_t[mystringSize];
//			MultiByteToWideChar(CP_UTF8, 0, mystring.c_str(), -1, mywstring, mystringSize);
//			myVariant.vt = VT_BSTR;
//			myVariant.bstrVal = mywstring;
//
//			VARIANT LogDivValueData;
//			string mystring3 = "LogDivValueData";
//			int mystringSize3 = (int)(mystring3.length() + 1);
//			wchar_t* mywstring3 = new wchar_t[mystringSize3];
//			MultiByteToWideChar(CP_UTF8, 0, mystring3.c_str(), -1, mywstring3, mystringSize3);
//			LogDivValueData.vt = VT_BSTR;
//			LogDivValueData.bstrVal = mywstring3;
//
//			VARIANT myVarianty;
//			string mystring2 = "0";
//			int mystringSize2 = (int)(mystring2.length() + 1);
//			wchar_t* mywstring2 = new wchar_t[mystringSize2];
//			MultiByteToWideChar(CP_UTF8, 0, mystring2.c_str(), -1, mywstring2, mystringSize2);
//			myVarianty.vt = VT_BSTR;
//			myVarianty.bstrVal = mywstring2;
//
//
//			CComPtr<IDispatch> dispDoc = NULL;
//			HRESULT   hr = S_FALSE;
//			CComPtr<IHTMLDocument2> spDoc = NULL;
//			IWebBrowser2* iweb2 = cWebUi->GetWebBrowser2();
//			if (iweb2 == NULL){
//				log("写入异常!");
//			}
//			hr = iweb2->get_Document(&dispDoc);
//			hr = dispDoc->QueryInterface(IID_IHTMLDocument2, (LPVOID*)&spDoc);
//
//			IHTMLElementCollection *spElementss = NULL;
//			spDoc->get_all(&spElementss);
//			CComPtr<IDispatch>pDisp;
//			CComQIPtr<IHTMLElement, &IID_IHTMLElement>pElement;
//			if (value != ""){
//				spElementss->item(myVariant, myVarianty, &pDisp);
//				if (pDisp == NULL)
//				{
//					return "获得标签失败！";
//				}
//				pElement = pDisp;
//				pElement->put_innerText(_bstr_t(value.c_str()));
//			}
//			pDisp = NULL;
//			if (value2!=""){
//				spElementss->item(LogDivValueData, myVarianty, &pDisp);
//				if (pDisp == NULL)
//				{
//					return "获得标签失败！";
//				}
//				pElement = pDisp;
//				pElement->put_innerText(_bstr_t(value2.c_str()));
//			}
//
//			//释放内存
//			spElementss->Release();
//			iweb2->Release();
//			delete[] mywstring;
//			delete[] mywstring2;
//			delete[] mywstring3;
//			return "写入成功";
//		}
//		catch (...){
//			log("写入异常!");
//		}
//	}
//
//	/**
//	* 说明：判断是否包含子串（A中是否包含B）
//	* 参数：A总字符串  B子串
//	* 返回：true包含 /false不包含
//	*/
//	BOOL checkIsStr(string strA, string strB){
//		string::size_type idx = strA.find(strB);
//		if (idx != string::npos)
//		{
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//	/**
//	* 说明：截取字符串（从A到B中间的字符串）
//	* 参数：all总字符串  a开始字符串  b结束字符串
//	* 返回：处理后的字符串
//	*/
//	string subCString(std::string all, string a, string b){
//		int ix = all.find(a);
//		int iy = all.find(b);
//		ix += strlen(a.c_str());
//		iy = iy - ix;
//		all = all.substr(ix, iy);
//		return all;
//	}
//	/**
//	* 说明：多字符串替换（不循环重复替换）
//	* 参数：str总字符串  old_vlaue_Arr要替换的字符（string[]类型）num要替换字符串的个数  new_value替换成的字符
//	* 返回：替换后的字符串
//	*/
//	string& replace_all_distinct_list(string& str, string old_vlaue_Arr[], int num, const string& new_value)
//	{
//		for (int i = 0; i < num; i++) {
//			const string& old_value = old_vlaue_Arr[i];
//			for (string::size_type pos(0); pos != string::npos; pos += new_value.length()){
//				if ((pos = str.find(old_value, pos)) != string::npos)
//					str.replace(pos, old_value.length(), new_value);
//				else  break;
//			}
//		}
//		return   str;
//	}
//	/**
//	* 说明：将字符串中的html标签转义
//	* 参数：需要转义的字符串
//	* 返回：处理后的字符串
//	*/
//	string replaceHTML(string str){
//		string strAryy[4]{ "</div>", "<em>", "</em>", "</p>"};
//		string replStr = replace_all_distinct_list((string)str, strAryy, 4, "");
//		replStr = replace_all_distinct(replStr, "&nbsp;", " ");
//		replStr = replace_all_distinct(replStr, "<br />", "\r\n");
//		return replStr.c_str();
//	}
//	//字符串分割函数
//	std::vector<std::string> split(std::string str, std::string pattern)
//	{
//		std::string::size_type pos;
//		std::vector<std::string> result;
//		str += pattern;//扩展字符串以方便操作
//		int size = str.size();
//
//		for (int i = 0; i<size; i++)
//		{
//			pos = str.find(pattern, i);
//			if (pos<size)
//			{
//				std::string s = str.substr(i, pos - i);
//				result.push_back(s);
//				i = pos + pattern.size() - 1;
//			}
//		}
//		return result;
//	}
//	
//	
//
//
//	unsigned char toHex(const unsigned char &x)
//	{
//		return x > 9 ? x - 10 + 'A' : x + '0';
//	}
//
//	unsigned char fromHex(const unsigned char &x)
//	{
//		return isdigit(x) ? x - '0' : x - 'A' + 10;
//	}
//	/**
//	* 说明：中文转为浏览器识别的特殊编码
//	* 参数：带转换字符串
//	* 返回：处理后的字符串
//	*/
//	string  URLEncode(const char *sIn)
//	{
//		string sOut;
//		for (size_t ix = 0; ix < strlen(sIn); ix++)
//		{
//			unsigned char buf[4];
//			memset(buf, 0, 4);
//			if (isalnum((unsigned char)sIn[ix]))
//			{
//				buf[0] = sIn[ix];
//			}
//			else
//			{
//				buf[0] = '%';
//				buf[1] = toHex((unsigned char)sIn[ix] >> 4);
//				buf[2] = toHex((unsigned char)sIn[ix] % 16);
//			}
//			sOut += (char *)buf;
//		}
//		return sOut;
//	};
//	/**
//	* 说明：浏览器识别的特殊编码转为中文
//	* 参数：带转换字符串
//	* 返回：处理后的字符串
//	*/
//	string URLDecode(const char *sIn)
//	{
//		string sOut;
//		for (size_t ix = 0; ix < strlen(sIn); ix++)
//		{
//			unsigned char ch = 0;
//			if (sIn[ix] == '%')
//			{
//				ch = (fromHex(sIn[ix + 1]) << 4);
//				ch |= fromHex(sIn[ix + 2]);
//				ix += 2;
//			}
//			else if (sIn[ix] == '+')
//			{
//				ch = ' ';
//			}
//			else
//			{
//				ch = sIn[ix];
//			}
//			sOut += (char)ch;
//		}
//
//		return sOut;
//
//	}
//	
//
//
//};