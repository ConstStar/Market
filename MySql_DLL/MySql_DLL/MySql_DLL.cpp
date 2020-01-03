#include <iostream>
#include <sstream>
#include <mysql/jdbc.h>

using namespace std;
#define MYSQL_ADDR "111.229.185.226:3306"
#define MYSQL_NAME "Market"
#define MYSQL_PASSWD "28BCSeCWrsfL5LL5"


//秘钥对比 更新登录时间   返回值     0 通过  1 过期  2机器码有误  3秘钥不存在   -1验证异常
#ifdef __cplusplus         // if used by C++ code
extern "C" {                  // we need to export the C interface
#endif
	__declspec(dllexport) int keyComp(const char* key, char* ExceedDateTime, const char* computerId, const char* num)
	{
		//防破解
		int temp_num = atoi(num) + 7;
		temp_num *= 3 * temp_num;

		try {
			sql::Driver* driver;
			sql::Connection* con;
			sql::Statement* stmt;
			sql::ResultSet* res;


			/* 创建连接 */
			driver = get_driver_instance();
			con = driver->connect(MYSQL_ADDR, MYSQL_NAME, MYSQL_PASSWD); // 需要修改为你数据库的用户密码
			/* 连接 MySQL 数据库 university  */
			con->setSchema("Market");

			stmt = con->createStatement();

			string sql_Computer;
			string temp_ExceedDateTime;
			bool noExceed = false;
			stringstream sql;

			sql << "SELECT `Computer`,DATE_ADD(UsingDateTime, INTERVAL ExceedDateTime MONTH),DATE_ADD(UsingDateTime, INTERVAL ExceedDateTime MONTH) > NOW() FROM `key` WHERE ";
			sql << "`Key` = '" << key << "';";


			res = stmt->executeQuery(sql.str().c_str());

			//秘钥不存在
			if (!res->rowsCount())
			{
				cout << "秘钥不存在" << endl;
				return temp_num + 3;
			}

			while (res->next())
			{
				sql_Computer = res->getString(1).c_str();
				temp_ExceedDateTime = res->getString(2).c_str();
				noExceed = res->getInt(3);
			}

			if (computerId == sql_Computer)
			{
				strcpy_s(ExceedDateTime, 30, temp_ExceedDateTime.c_str());

				if (noExceed == false)
				{
					cout << "秘钥过期 过期时间:" << ExceedDateTime << endl;
					return temp_num + 1;
				}

				stringstream sql;

				sql << "UPDATE `Market`.`key` SET `LoginDateTime` = NOW() WHERE ";
				sql << "`Key` = '" << key << "';";

				stmt->executeUpdate(sql.str().c_str()); // 标准sql语句

				cout << "密钥通过" << endl;
				return temp_num + 0;
			}
			else
			{
				//密钥无效
				cout << "机器码有误" << endl;
				return temp_num + 2;
			}

			//res->close();
			con->close();
			stmt->close();
			//delete res;
			delete stmt;
			delete con;

		}
		catch (sql::SQLException & e) {
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;

			return temp_num + -1;
		}

		return temp_num + -1;
	}
#ifdef __cplusplus
}
#endif


//int main()
//{
//	string key = "3";
//	//string local_Computer = "1234";
//	string QQId = "1164442003";
//	char ExceedDateTime[30];
//
//	cout << keyComp(key.c_str(), ExceedDateTime, QQId.c_str()) << endl;
//
//
//	cout << "到期时间 " << ExceedDateTime << endl;
//
//	return 0;
//}