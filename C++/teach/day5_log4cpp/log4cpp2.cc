//g++ log4cpp2.cc -llog4cpp -lpthread

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>

#include <iostream>
using std::cout;
using std::endl;
using namespace log4cpp;

int main()
{
    PatternLayout * ptnLayout1 = new PatternLayout();
    ptnLayout1->setConversionPattern("%d %c [%p] %m%n");
    PatternLayout * ptnLayout2 = new PatternLayout();
    ptnLayout2->setConversionPattern("%d %c [%p] %m%n");

    OstreamAppender * ostreamAppender = new OstreamAppender("ostreamAppender", &cout); 
    ostreamAppender->setLayout(ptnLayout1);

    FileAppender * fileAppender = new FileAppender("fileAppender", "wangdao.log");
    fileAppender->setLayout(ptnLayout2);//重用PatternLayout会造成段错误

    Category & mycategory = Category::getRoot().getInstance("mycategory");
    mycategory.setPriority(Priority::DEBUG);
    mycategory.addAppender(ostreamAppender);
    mycategory.addAppender(fileAppender);

    mycategory.alert("this is alert message");
    mycategory.crit("this is crit message");
    mycategory.error("this is error message");
    mycategory.warn("this is warn message");
    mycategory.info("this is info message");
    mycategory.notice("this is notice message");

    Category::shutdown();

    return 0;
}

