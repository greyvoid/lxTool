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
//	//intתstring
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
//	//stringתint
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
//	* ˵����ȥ���ļ���׺ ֻ���ļ���
//	* �������ļ���
//	* ���أ����ļ����Ʋ�����׺
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
//	* ˵����������һ��·�������Ի��·�����ļ�����
//	* ���������һ����Ϣ
//	* ���أ����ļ����Ʋ�����׺
//	*/
//	string getPathTail(string fileName,string checkFH){
//		int pos = fileName.rfind(checkFH);
//		if (pos > 0)
//			return fileName.substr(pos+1, fileName.length());
//		else
//			return fileName;
//	}
//	/**
//	* ˵����ȥ�����һ��·��������ȥ���ļ�������·����
//	* ������·�� "/" "\\"
//	* ���أ����ļ����Ʋ�����׺
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
//	* д���ļ����� �������򴴽�  ����д��
//	* ����һ���ļ�·��
//	* ���������ļ�����
//	* ���أ�true�ɹ�/falseʧ��
//	*/
//	BOOL saveFileData(string filePath, char* fileData){
//		ofstream outfile(filePath, ios::out);//ios::app��ʾ��ԭ�ļ�ĩβ׷��
//		outfile.write(fileData, strlen(fileData));
//		outfile.close();
//		return true;
//	}
//	/**
//	* ˵�����ַ����滻����ѭ���ظ��滻��
//	* ������1���ַ��� 2Ҫ�滻���ַ� 3�滻�ɵ��ַ�
//	* ���أ��滻����ַ���
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
//	* ˵�����ַ����滻��ѭ���ظ��滻��
//	* ������1���ַ��� 2Ҫ�滻���ַ� 3�滻�ɵ��ַ�
//	* ���أ��滻����ַ���
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
//	* ˵��������ID���htmlָ��ID��htmlԴ��
//	* ����������1 web����   ����2 ID
//	* ���أ�ָ��ID��ǩ��HTMLԪ��
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
//				log("����Ϊ��");
//			}
//			hr = iweb2->get_Document(&dispDoc);
//			hr = dispDoc->QueryInterface(IID_IHTMLDocument2, (LPVOID*)&spDoc);
//			IHTMLElementCollection *spElementss = NULL;
//			spDoc->get_all(&spElementss);
//			CComPtr<IDispatch>pDisp;
//
//			//charתVARIANT
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
//			//�ͷ��ڴ�
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
//	//д��html ָ��ID�ı�ǩ����
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
//				log("д���쳣!");
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
//				return "��ñ�ǩʧ�ܣ�";
//			}
//			CComBSTR pContentA;
//			pElement = pDisp;
//			pElement->put_innerText(_bstr_t(value.c_str()));
//
//			//�ͷ��ڴ�
//			spElementss->Release();
//			iweb2->Release();
//			delete[] mywstring;
//			delete[] mywstring2;
//			return "д��ɹ�";
//		}
//		catch (...){
//			log("д���쳣!");
//		}
//	}
//	/**
//	*д��Log��ǩ����
//	*����һ������  ������������    ��Ϊ"" 
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
//				log("д���쳣!");
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
//					return "��ñ�ǩʧ�ܣ�";
//				}
//				pElement = pDisp;
//				pElement->put_innerText(_bstr_t(value.c_str()));
//			}
//			pDisp = NULL;
//			if (value2!=""){
//				spElementss->item(LogDivValueData, myVarianty, &pDisp);
//				if (pDisp == NULL)
//				{
//					return "��ñ�ǩʧ�ܣ�";
//				}
//				pElement = pDisp;
//				pElement->put_innerText(_bstr_t(value2.c_str()));
//			}
//
//			//�ͷ��ڴ�
//			spElementss->Release();
//			iweb2->Release();
//			delete[] mywstring;
//			delete[] mywstring2;
//			delete[] mywstring3;
//			return "д��ɹ�";
//		}
//		catch (...){
//			log("д���쳣!");
//		}
//	}
//
//	/**
//	* ˵�����ж��Ƿ�����Ӵ���A���Ƿ����B��
//	* ������A���ַ���  B�Ӵ�
//	* ���أ�true���� /false������
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
//	* ˵������ȡ�ַ�������A��B�м���ַ�����
//	* ������all���ַ���  a��ʼ�ַ���  b�����ַ���
//	* ���أ��������ַ���
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
//	* ˵�������ַ����滻����ѭ���ظ��滻��
//	* ������str���ַ���  old_vlaue_ArrҪ�滻���ַ���string[]���ͣ�numҪ�滻�ַ����ĸ���  new_value�滻�ɵ��ַ�
//	* ���أ��滻����ַ���
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
//	* ˵�������ַ����е�html��ǩת��
//	* ��������Ҫת����ַ���
//	* ���أ��������ַ���
//	*/
//	string replaceHTML(string str){
//		string strAryy[4]{ "</div>", "<em>", "</em>", "</p>"};
//		string replStr = replace_all_distinct_list((string)str, strAryy, 4, "");
//		replStr = replace_all_distinct(replStr, "&nbsp;", " ");
//		replStr = replace_all_distinct(replStr, "<br />", "\r\n");
//		return replStr.c_str();
//	}
//	//�ַ����ָ��
//	std::vector<std::string> split(std::string str, std::string pattern)
//	{
//		std::string::size_type pos;
//		std::vector<std::string> result;
//		str += pattern;//��չ�ַ����Է������
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
//	* ˵��������תΪ�����ʶ����������
//	* ��������ת���ַ���
//	* ���أ��������ַ���
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
//	* ˵���������ʶ����������תΪ����
//	* ��������ת���ַ���
//	* ���أ��������ַ���
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