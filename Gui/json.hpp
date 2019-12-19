#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <Windows.h>

#include <sstream>
#include <fstream>
#include <string>
using namespace std;

extern string appFile;

class OperateStr
{
public:
	static wstring string2wstring(string str)
	{
		wstring result;
		//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
		int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
		TCHAR* buffer = new TCHAR[len + 1];
		//多字节编码转换成宽字节编码  
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
		buffer[len] = '\0';             //添加字符串结尾  
		//删除缓冲区并返回值  
		result.append(buffer);
		delete[] buffer;
		return result;
	}

	//将wstring转换成string  
	static string wstring2string(wstring wstr)
	{
		string result;
		//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
		int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
		char* buffer = new char[len + 1];
		//宽字节编码转换成多字节编码  
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
		buffer[len] = '\0';
		//删除缓冲区并返回值  
		result.append(buffer);
		delete[] buffer;
		return result;

	}
};

class json {

public:

	static bool read_json(string file_path, boost::property_tree::wptree& value)
	{
		try
		{
			wstringstream ss;
			wfstream file;

			file.open(file_path, ios::in);
			if (!file.good())
			{
				return false;
			}

			ss << file.rdbuf();

			boost::property_tree::read_json(ss, value);
		}
		catch (...)
		{
			return false;
		}

		return true;
	}

	static bool write_json(string file_path, boost::property_tree::wptree& value)
	{
		try
		{
			boost::property_tree::write_json(file_path, value);
		}
		catch (...)
		{
			return false;
		}

		return true;
	}

	//解析json中的数组
	static bool json2vector_str(string& file_path, const wchar_t* json_path, vector<string>& value)
	{
		try {
			value.clear();//清空原有数组

			boost::property_tree::wptree conf_json;

			read_json(file_path, conf_json);

			//获取json数组
			auto op = conf_json.get_child_optional(json_path);

			//如果没有key
			if (!op)
			{
				return false;
			}

			//添加到数组中 转成string
			for (auto temp : op.get())
			{
				string str = OperateStr::wstring2string(temp.second.get_value<wstring>());

				//过滤无效值
				if (str.empty())
					continue;

				value.push_back(str);
			}


		}
		catch (...)
		{
			return false;
		}

		return true;
	}

	static bool json2vector_longlong(string file_path, const wchar_t* json_path, vector<long long>& value)
	{
		try {
			value.clear();//清空原有数组

			boost::property_tree::wptree conf_json;

			read_json(file_path, conf_json);

			//获取json数组
			auto op = conf_json.get_child_optional(json_path);

			//如果没有key
			if (!op)
			{
				return false;
			}

			//添加到数组中 转成string
			for (auto temp : op.get())
			{
				long long num = temp.second.get_value<long long>();

				//过滤无效值
				if (num == 0)
					continue;

				value.push_back(num);
			}


		}
		catch (...)
		{
			return false;
		}

		return true;
	}


	//构造json中的数组
	static bool vector2json_str(string file_path, const wchar_t* json_path, const wchar_t* json_after, vector<string>& value)
	{
		try
		{
			wstring all_path = json_path;
			all_path += L".";
			all_path += json_after;

			boost::property_tree::wptree conf_json;

			read_json(file_path, conf_json);

			conf_json.get_child(json_path).erase(json_after);//删除原来的
			conf_json.add_child(all_path.c_str(), boost::property_tree::wptree(L""));//构造新的

			//添加数组 转成wstring
			boost::property_tree::wptree child;
			for (auto temp : value)
			{
				if (temp.empty())
					continue;

				child.put<wstring>(L"", OperateStr::string2wstring(temp));
				conf_json.get_child(all_path.c_str()).push_back(make_pair(L"", child));
			}

		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	static bool vector2json_longlong(string& file_path, const wchar_t* json_path, const wchar_t* json_after, vector<long long>& value)
	{
		try
		{
			//检测是否有主子结点
			//如果没有自己新建一个
			boost::property_tree::wptree conf_json;

			read_json(file_path, conf_json);

			auto op = conf_json.get_child_optional(json_path);
			if (!op)
			{
				conf_json.add_child(json_path, boost::property_tree::wptree(L""));//构造新的
			}

			wstring all_path = json_path;
			all_path += L".";
			all_path += json_after;

			conf_json.get_child(json_path).erase(json_after);//删除原来的
			conf_json.add_child(all_path.c_str(), boost::property_tree::wptree(L""));//构造新的

			//添加数组 转成wstring
			boost::property_tree::wptree child;
			for (auto temp : value)
			{
				//过滤无效值
				if (temp == 0)
					continue;

				child.put<long long>(L"", temp);

				conf_json.get_child(all_path.c_str()).push_back(make_pair(L"", child));
			}

		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	//	//群单独设置map 存放到json
	//	static bool map2json_longlong(const wchar_t* json_after, map<long long, vector<long long>>& value)
	//	{
	//		try
	//		{
	//			for (auto temp : value)
	//			{
	//				vector2json_longlong((L"GroupConf." + to_wstring(temp.first)).c_str(), json_after, temp.second);
	//			}
	//
	//		}
	//		catch (exception & e)
	//		{
	//#ifdef DEBUG
	//
	//			cout << e.what() << endl;
	//
	//#endif // DEBUG
	//			return false;
	//		}
	//		return true;
	//	}
	//
	//	static bool map2json_str(const wchar_t* json_after, map<long long, vector<string>>& value)
	//	{
	//		try
	//		{
	//			for (auto temp : value)
	//			{
	//				json_vector2json_str((L"GroupConf." + to_wstring(temp.first)).c_str(), json_after, temp.second);
	//
	//			}
	//
	//		}
	//		catch (exception & e)
	//		{
	//#ifdef DEBUG
	//
	//			cout << e.what() << endl;
	//
	//#endif // DEBUG
	//			return false;
	//		}
	//		return true;
	//	}
	//
	//
	//	//群单独设置json 读取map
	//	static bool json2map_str(const wchar_t* json_after, map<long long, vector<string>>& value)
	//	{
	//		try
	//		{
	//			for (auto temp : conf_json.get_child(L"GroupConf"))
	//			{
	//				wstring temp_str;
	//				temp_str = L"GroupConf.";
	//				temp_str += temp.first.data();
	//				temp_str += L".";
	//				temp_str += json_after;
	//
	//				json_json2vector_str(temp_str.c_str(), value[_wtoll(temp.first.data())]);
	//
	//			}
	//		}
	//		catch (exception & e)
	//		{
	//#ifdef DEBUG
	//
	//			cout << e.what() << endl;
	//
	//#endif // DEBUG
	//			return false;
	//		}
	//		return true;
	//	}
	//
	//	static bool json2map_longlong(const wchar_t* json_after, map<long long, vector<long long>>& value)
	//	{
	//		try
	//		{
	//			for (auto temp : conf_json.get_child(L"GroupConf"))
	//			{
	//				wstring temp_str;
	//				temp_str = L"GroupConf.";
	//				temp_str += temp.first.data();
	//				temp_str += L".";
	//				temp_str += json_after;
	//
	//				json_json2vector_longlong(temp_str.c_str(), value[_wtoll(temp.first.data())]);
	//
	//			}
	//		}
	//		catch (exception & e)
	//		{
	//#ifdef DEBUG
	//
	//			cout << e.what() << endl;
	//
	//#endif // DEBUG
	//			return false;
	//		}
	//		return true;
	//	}

};

class Conf
{
public:
	static void makeUpdate()
	{
		ofstream file(appFile + "update.tmp", ios::out);
		file << "需要读取配置";
		file.close();
	}
};