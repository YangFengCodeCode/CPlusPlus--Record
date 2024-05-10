#include<iostream>
using namespace std;


#include<windows.h>

//double Division(int a, int b)
//{
//	// ��b == 0ʱ�׳��쳣
//	if (b == 0)
//		throw "Division by zero condition!";
//	else
//		return ((double)a / (double)b);
//}
//
//
//void Func()
//{
//	int len, time;
//	cout << "cin << len << time: ";
//	cin >> len >> time;
//	cout << Division(len, time) << endl;
//
//}
//
//void fxx()
//{
//	int i = 0;
//	cout << "cin >> i: ";
//	cin >> i;
//	if (i % 2 == 0)
//	{
//		throw 1;
//	}
//}
//
//int main()
//{
//	try 
//	{
//		fxx();
//		Func();
//	}
//	catch (const char* errmsg)
//	{
//		cout << "�����쳣 division: " << errmsg << endl;
//	}
//	catch (int x)
//	{
//		cout << "�����쳣x:"<< x << endl;
//	}
//
//	return 0;
//}


//#include<windows.h>
//
//double Division(int a, int b)
//{
//	// ��b == 0ʱ�׳��쳣
//	if (b == 0)
//		throw "Division by zero condition!";
//	else
//		return ((double)a / (double)b);
//}
//
//
//void fxx()
//{
//	int i = 0;
//	cout << "cin >> i: ";
//	cin >> i;
//	if (i % 2 == 0)
//	{
//		throw 1;
//	}
//}
//
//void Func()
//{
//	int len, time;
//	cout << "cin >> len >> time: ";
//	cin >> len >> time;
//	cout << Division(len, time) << endl;
//	try
//	{
//		fxx();
//	}
//	catch (int x)
//	{
//		cout <<__LINE__<<"�����쳣:" << x << endl;
//	}
//
//	cout << "=====================" << endl;
//
//}
//
//int main()
//{
//	try 
//	{
//		Func();
//	}
//	catch (const char* errmsg)
//	{
//		cout << errmsg << endl;
//	}
//	catch (int x)
//	{
//		cout << __LINE__ <<"�����쳣:"<< x << endl;
//	}
//
//	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
//
//	return 0;
//}


//double Division(int a, int b)
//{
//	if (b == 0)
//		throw "Division by zero condition!";
//	else
//		return ((double)a / (double)b);
//}
//
//
//void fxx()
//{
//	int i = 0;
//	cin >> i;
//	if (i % 2 == 0)
//	{
//		string s("����ż��");
//		throw s;
//	}
//}
//
//void Func()
//{
//	int len, time;
//	cin >> len >> time;
//	cout << Division(len, time) << endl;
//	fxx();
//}
//
//int main()
//{
//	try
//	{
//		Func();
//	}
//	catch (const char* errmsg)
//	{
//		cout << errmsg << endl;
//	}
//	catch (const string& err)//���ﲻ��s�ı��� ��s�Ŀ�������
//	{
//		cout << err << endl;
//	}
//	catch (...) // �������͵��쳣
//	{
//		cout << "δ֪�쳣" << endl;
//	}
//
//	return 0;
//}


// ������������ͨ��ʹ�õ��쳣�̳���ϵ
class Exception
{
public:
	Exception(const string& errmsg, int id)
		:_errmsg(errmsg)
		, _id(id)
	{}

	virtual string what() const
	{
		return _errmsg;
	}

protected:
	string _errmsg;  // ��������
	int _id;         // ������
};

// �̳кͶ�̬
class SqlException : public Exception
{
public:
	SqlException(const string& errmsg, int id, const string& sql)
		:Exception(errmsg, id)
		, _sql(sql)
	{}

	virtual string what() const
	{
		string str = "SqlException:";
		str += _errmsg;
		str += "->";
		str += _sql;
		return str;
	}
private:
	const string _sql;
};

class CacheException : public Exception
{
public:
	CacheException(const string& errmsg, int id)
		:Exception(errmsg, id)
	{}

	virtual string what() const
	{
		string str = "CacheException:";
		str += _errmsg;
		return str;
	}
};

class HttpServerException : public Exception
{
public:
	HttpServerException(const string& errmsg, int id, const string& type)
		:Exception(errmsg, id)
		, _type(type)
	{}

	virtual string what() const
	{
		string str = "HttpServerException:";
		str += _type;
		str += ":";
		str += _errmsg;
		return str;
	}
private:
	const string _type;
};


class A
{
public:
	A()
	{
		cout << "A()" << endl;
		_ptr1 = new int;
		_ptr2 = new int;
	}

	~A()
	{
		cout << "~A()" << endl;

		delete _ptr1;
		delete _ptr2;
	}

private:
	int* _ptr1;
	int* _ptr2;
};


void SQLMgr()
{
	srand(time(0));
	if (rand() % 7 == 0)
	{
		throw SqlException("Ȩ�޲���", 100, "select * from name = '����'");
	}

	cout << "!!!!!!!!!!!!!!!!!!!!!!!!���гɹ�" << endl;
}

void CacheMgr()
{
	srand(time(0));
	if (rand() % 5 == 0)
	{
		throw CacheException("Ȩ�޲���", 100);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("���ݲ�����", 101);
	}
	SQLMgr();
}

void HttpServer()
{
	A aa;
	srand(time(0));
	if (rand() % 3 == 0)
	{
		throw HttpServerException("������Դ������", 100, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpServerException("Ȩ�޲���", 101, "post");
	}

	CacheMgr();
}

//int main()
//{
//	srand(time(0));
//
//	while (1)
//	{
//		Sleep(1000);
//
//		try {
//			HttpServer(); // io
//		}
//		catch (const Exception& e) // ���ﲶ�������Ϳ���
//		{
//			// ��̬
//			cout << e.what() << endl;
//		}
//		catch (...)
//		{
//			cout << "Unkown Exception" << endl;
//		}
//	}
//
//	return 0;
//}
//


//double Division(int a, int b)
//{
//	// ��b == 0ʱ�׳��쳣
//	if (b == 0)
//	{
//		throw "Division by zero condition!";
//	}
//	return (double)a / (double)b;
//}
//void Func()
//{
//	// ������Կ������������0�����׳��쳣�����������arrayû�еõ��ͷš�
//	// �������ﲶ���쳣�󲢲������쳣���쳣���ǽ������洦�������ﲶ������
//	// �����׳�ȥ��
//	int* array = new int[10];
//	try {
//		int len, time;
//		cout << "cin >> len >> time: ";
//		cin >> len >> time;
//		cout << Division(len, time) << endl;
//	}
//	catch (...)
//	{
//		cout << "delete []" << array << endl;
//		delete[] array;
//		throw;//����ʲô���׳�ʲô
//	}
//	// ...
//	cout << "delete []" << array << endl;
//	delete[] array;
//}
//
//int main()
//{
//	try
//	{
//		Func();
//	}
//	catch (const char* errmsg)
//	{
//		cout << errmsg << endl;
//	}
//	return 0;
//}

#include<vector>

int main()
{
	try {
		vector<int> v(10, 5);
		// �������ϵͳ�ڴ治��Ҳ�����쳣
		v.reserve(1000000000);
		// ����Խ������쳣
		v.at(10) = 100;
	}
	catch (std::exception & e) // ���ﲶ�������Ϳ���
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "Unkown Exception" << endl;
	}
	return 0;
}

