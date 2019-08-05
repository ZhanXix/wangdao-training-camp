/*
 * 5-2 *
	输出的日志信息能同时输出到终端和文件
		int main(void)
		{
			cout << "hello,world"<<endl;
			
			LogInfo("Message");	//或者   
			LogError("Message");
			LogWarn("Message");
			LogDebug("Message");
		}
	加分项：输出的日志信息中最好能有文件的名字，函数的名字及其所在的行号
				//使用单例模式
				class Mylogger
				{
				public:
					void warn(const char * msg);
					void error(const char * msg);
					void debug(const char * msg);
					void info(const char * msg);
					
				private:
					Mylog();
					~Mylog();
				private:
				  //......
				};
				
				Mylogger * log = Mylogger::getInstance();
				log->warn("hello")；
 
 **************

 * 12-3 *
 实现log4cpp的封装，使其可以像printf一样使用，测试用例如下:

	void test() {
		int number = 100;
		const char * pstr = "hello, log4cpp";
		LogInfo("this is an info message. number = %d, str = %s\n", number, pstr);
	}

*/

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using log4cpp::Category;
using log4cpp::Priority;
using log4cpp::OstreamAppender;
using log4cpp::FileAppender;
using log4cpp::PatternLayout;

class Mylogger
{
public:
    static Mylogger * getInstance()
    {
        if(NULL == _pMylog){
            _pMylog = new Mylogger("myLog.txt");
        }
        return _pMylog;
    }

    static Mylogger * getInstance(const char * LogFileName)
    {
        if(NULL == _pMylog){
            _pMylog = new Mylogger(LogFileName);
        }
        return _pMylog;
    }

    static void destory()
    {
        if( _pMylog )
        {
            Category::shutdown();
            delete _pMylog;
        }
    }

    template<typename... Args>
    void warn(Args... args)
    {
        _mycategory.warn(args...);
    }

    template<typename... Args>
    void error(Args... args)
    {
        _mycategory.error(args...);
    }

    template<typename... Args>
    void debug(Args... args)
    {
        _mycategory.debug(args...);
    }

    template<typename... Args>
    void info(Args... args)
    {
        _mycategory.info(args...);
    }

private:
    Mylogger(const char * LogFileName)
    : _mycategory( Category::getRoot().getInstance("mycategory") )
    {
        cout << "Mylogger()" << endl;

        PatternLayout * _ptnLayout1 = new PatternLayout();
        PatternLayout * _ptnLayout2 = new PatternLayout();
        OstreamAppender * _osAppender = new OstreamAppender("osAppender", &cout);
        FileAppender * _fAppender = new FileAppender("fAppender", LogFileName);

        _ptnLayout1->setConversionPattern("%d [%p] %m%n");
        _ptnLayout2->setConversionPattern("%d [%p] %m%n");
        _osAppender->setLayout(_ptnLayout1);
        _fAppender->setLayout(_ptnLayout2);
        
        _mycategory.setPriority(Priority::DEBUG);
        _mycategory.addAppender(_osAppender);
        _mycategory.addAppender(_fAppender);
    }

    ~Mylogger()
    {
        cout << "~Mylogger()" << endl;
    }

    //data
    static Mylogger *_pMylog;
    Category & _mycategory;
};

Mylogger * Mylogger::_pMylog = Mylogger::getInstance(); 


#define LogWarn(args...) LogWarnFunc(__FUNCTION__,__FILE__,__LINE__,args);  
#define LogError(args...) LogErrorFunc(__FUNCTION__,__FILE__,__LINE__,args);  
#define LogDebug(args...) LogDebugFunc(__FUNCTION__,__FILE__,__LINE__,args);  
#define LogInfo(args...) LogInfoFunc(__FUNCTION__,__FILE__,__LINE__,args);  

template<typename... Args>
void LogWarnFunc(const char* func, const char* file, int line, const char *msg, Args... args)
{
    string trueMsg = string(func).append("@").append(file).append(",").append(std::to_string(line)).append(" : ").append(msg);
    Mylogger::getInstance()->warn(trueMsg.c_str(),args...);
}

template<typename... Args>
void LogErrorFunc(const char* func, const char* file, int line, const char *msg, Args... args)
{
    string trueMsg = string(func).append("@").append(file).append(",").append(std::to_string(line)).append(" : ").append(msg);
    Mylogger::getInstance()->error(trueMsg.c_str(),args...);
}

template<typename... Args>
void LogDebugFunc(const char* func, const char* file, int line, const char *msg, Args... args)
{
    string trueMsg = string(func).append("@").append(file).append(",").append(std::to_string(line)).append(" : ").append(msg);
    Mylogger::getInstance()->debug(trueMsg.c_str(),args...);
}

template<typename... Args>
void LogInfoFunc(const char* func, const char* file, int line, const char *msg, Args... args)
{
    string trueMsg = string(func).append("@").append(file).append(",").append(std::to_string(line)).append(" : ").append(msg);
    Mylogger::getInstance()->info(trueMsg.c_str(),args...);
}

//测试代码
int main()
{
    LogWarn("This is warn msg!");
    LogError("This is error msg!");
    LogDebug("This is debug msg!");
    LogInfo("This is info msg!");

    int number = 100;
    const char * pstr = "hello, log4cpp";
    LogInfo("this is an info message. number = %d, str = %s\n", number, pstr);
    LogError("this is an error message. number = %d, str = %s\n", number, pstr);
    LogWarn("this is a warn message. number = %d, str = %s\n", number, pstr);
    LogDebug("this is a debug message. number = %d, str = %s\n", number, pstr);


    Mylogger::destory();

    return 0;
}

