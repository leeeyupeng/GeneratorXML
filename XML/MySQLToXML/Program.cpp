#include <stdio.h>
#include <string>
#include <stdlib.h>  
#include <iostream>  
#include <fstream>
#include <direct.h>

#include "winsock.h" 
#include "mysql.h" 
#pragma comment(lib,"libmySQL.lib") 

using namespace std;

MYSQL m_sqlCon;

char* serverIP = "localhost";
int serverPort = 3306;
char* user = "cmge";
char* password = "mw";

char* dst = "E:\\users\\administrator.user-ho7ku9ob20\\documents\\visual studio 2012\\Projects\\XML\\Debug\\out";

bool connect_mysql()
{
	try 
	{  
		mysql_init(&m_sqlCon);  
		// localhost:服务器 root为账号密码 test为数据库名 3306为端口  
		if(!mysql_real_connect(&m_sqlCon, serverIP,"root",user,password,serverPort,NULL,0))  
		{  
			printf("数据库连接失败!\n");
			return false;  
		}   
		return true;  

	}  
	catch (...)  
	{  
		return false;  
	} 
}

void disconnect_mysql()
{
	mysql_close(&m_sqlCon); 
}

void gettype(char** pName,enum_field_types type)
{
	char* name = NULL;
	name = "bitch";
	switch (type)
	{
	case MYSQL_TYPE_DECIMAL:
		name = "int";
		break;
	case MYSQL_TYPE_TINY:
		break;
	case MYSQL_TYPE_SHORT:
		name = "short";
		break;
	case MYSQL_TYPE_LONG:
		name = "int";
		break;
	case MYSQL_TYPE_FLOAT:
		name = "float";
		break;
	case MYSQL_TYPE_DOUBLE:
		break;
	case MYSQL_TYPE_NULL:
		break;
	case MYSQL_TYPE_TIMESTAMP:
		break;
	case MYSQL_TYPE_LONGLONG:
		break;
	case MYSQL_TYPE_INT24:
		break;
	case MYSQL_TYPE_DATE:
		break;
	case MYSQL_TYPE_TIME:
		break;
	case MYSQL_TYPE_DATETIME:
		break;
	case MYSQL_TYPE_YEAR:
		break;
	case MYSQL_TYPE_NEWDATE:
		break;
	case MYSQL_TYPE_VARCHAR:
		break;
	case MYSQL_TYPE_BIT:
		break;
	case MYSQL_TYPE_NEWDECIMAL:
		break;
	case MYSQL_TYPE_ENUM:
		break;
	case MYSQL_TYPE_SET:
		break;
	case MYSQL_TYPE_TINY_BLOB:
		break;
	case MYSQL_TYPE_MEDIUM_BLOB:
		break;
	case MYSQL_TYPE_LONG_BLOB:
		break;
	case MYSQL_TYPE_BLOB:
		break;
	case MYSQL_TYPE_VAR_STRING:
		break;
	case MYSQL_TYPE_STRING:
		name = "string";
		break;
	case MYSQL_TYPE_GEOMETRY:
		break;
	default:
		name = "bitch";
		break;
	}

	//(*pName) = name;
	strcpy(*pName,name);
}

void generatorAttribute()
{
	printf("generatorAttribute start\n");

	MYSQL_RES *pResultTables = NULL; 
	pResultTables = mysql_list_tables(&m_sqlCon,"");

	printf("table num : %d\n",pResultTables->row_count);

	char* xmlFileName = (char *)malloc(300);
	//sprintf(xmlFileName,".\\out\\%s.xml","attritube");
	//sprintf(xmlFileName,"%s\\%s.xml",dst,"attritube");
	_mkdir(dst);
	sprintf(xmlFileName,"%s\\%s.xml",dst,"attritube");

	printf("xmlFileName :%s\n",xmlFileName);
	ofstream out(xmlFileName);
	free(xmlFileName);
	xmlFileName = NULL;
	out << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
	out << "<Records>\n";

	MYSQL_ROW table;
	while(table = mysql_fetch_row(pResultTables))
	{
		printf("generator table:%s\n",table[0]);

		out << "	<Record ";
		MYSQL_FIELD *pResultField = NULL; 

		MYSQL_RES *pResultTable = NULL; 

		char* query = (char *)malloc(300);
		sprintf(query,"select * from %s",table[0]);

		printf("%s\n",query);
		mysql_query(&m_sqlCon,query);
		free(query);
		query = NULL;
		pResultTable = mysql_store_result(&m_sqlCon);

		char* attr = (char *)malloc(300);
		char* typeName = (char *)malloc(300);
		while(pResultField = mysql_fetch_field(pResultTable))
		{
			printf("db:%s %d\n",pResultField->name,pResultField->type);


			gettype(&typeName,pResultField->type);
			printf("%s\n",typeName);
			sprintf(attr,"%s=\"%s\" ",pResultField->name,typeName);
			out << attr;

		}
		free(attr);
		free(typeName);
		out << "/>\n";

		mysql_free_result(pResultTable);
	}

	out << "</Records>\n";
	out << "\n";
	out.close();

	mysql_free_result(pResultTables);

	printf("generatorAttribute success!\n");
}

void generatorRecords()
{
	printf("generatorRecords start\n");


	MYSQL_RES *pResultTables = NULL; 
	pResultTables = mysql_list_tables(&m_sqlCon,"");

	printf("table num : %d\n",pResultTables->row_count);

	MYSQL_ROW table;
	while(table = mysql_fetch_row(pResultTables))
	{
		printf("generator table:%s\n",table[0]);

		char* xmlFileName = (char *)malloc(300);
		sprintf(xmlFileName,"%s\\db",dst);
		_mkdir(xmlFileName);
		sprintf(xmlFileName,"%s\\db\\%s.xml",dst,table[0]);
		ofstream out(xmlFileName);
		free(xmlFileName);
		out << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
		out << "<Records>\n";

		MYSQL_FIELD *pResultField = NULL;

		MYSQL_ROW pResultRecord; 
		MYSQL_RES *pResultTable = NULL; 

		char* query = (char *)malloc(300);
		sprintf(query,"select * from %s",table[0]);

		printf("%s\n",query);
		mysql_query(&m_sqlCon,query);
		pResultTable = mysql_store_result(&m_sqlCon);		

		free(query);

		out << "	<Attribute ";
		char* attr = (char *)malloc(300);
		char* typeName = (char *)malloc(300);
		while(pResultField = mysql_fetch_field(pResultTable))
		{
			printf("db:%s %d\n",pResultField->name,pResultField->type);


			gettype(&typeName,pResultField->type);
			printf("%s\n",typeName);
			sprintf(attr,"%s=\"%s\" ",pResultField->name,typeName);
			out << attr;

		}
		free(attr);
		free(typeName);
		out << "/>\n";


		while(((pResultRecord = mysql_fetch_row(pResultTable)) != NULL))
		{
			out << "	<Record ";
			int i = 0;

			mysql_field_seek(pResultTable,0);
			while(pResultField = mysql_fetch_field(pResultTable))
			{
				//printf("db:%s %d\n",pResultRecord->name,pResultRecord->type);
				char* attr = (char *)malloc(300);
				sprintf(attr,"%s=\"%s\" ",pResultField->name,pResultRecord[i]);
				out << attr;

				free(attr);
				i++;
			}

			out << "/>\n";
		}

		mysql_free_result(pResultTable);

		out << "</Records>\n";
		out << "\n";
		out.close();
	}

	mysql_free_result(pResultTables);

	printf("generatorRecords success!\n");
}

void getStr(char** dst,char* str)
{
	char* temp;
	temp = str;
	int index = 0;
	for(int i = 0; i < strlen(str); i ++)
	{
		if(str[i] == '\"' || str[i] == ';')
		{
			continue;
		}

		temp[index] = str[i];
		index ++;
	}
	temp[index] = '\0';

	strcpy(*dst,temp);
}

void loadConfig()
{
	ifstream in;
	in.open("config.txt");
	char* str = (char *)malloc(300);
	in >> str;
	in >> str;
	in >> str;
	getStr(&serverIP,str);
	printf("serverIP : %s\n",serverIP);

	in >> str;
	in >> str;
	in >> serverPort;
	in >> str;

	in >> str;
	printf("user : %s\n",str);
	in >> str;
	printf("user : %s\n",str);
	in >> str;
	printf("user : %s\n",str);
	getStr(&user,str);
	printf("user : %s\n",user);

	in >> str;
	in >> str;
	in >> str;
	getStr(&password,str);
	printf("password : %s\n",password);

	in >> str;
	in >> str;
	in.get();
	in.getline(str,300);
	printf("dst : %s\n",str);
	getStr(&dst,str);
	printf("dst : %s\n",dst);

	free(str);
	str = NULL;
}

int main()
{
	serverIP = (char *)malloc(300);
	user = (char *)malloc(300);
	password = (char *)malloc(300);
	dst = (char *)malloc(300);

	loadConfig();

	printf("mysql to xml\n");

	if(connect_mysql())
	{
		//generatorAttribute();

		generatorRecords();

		disconnect_mysql();
		printf("success!\n");
	}
	else
	{
		printf("error\n");
	}

	free(serverIP);
	free(user);
	free(password);
	free(dst);

	printf("press enter  quit................\n");
	//char str;
	//scanf("%c",&str);

	getchar();
}