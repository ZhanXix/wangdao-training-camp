/*熟悉log4cpp的用法，动手敲代码*/
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>

#include <iostream>
using std::cout;
using std::endl;

int main()
{
    log4cpp::PatternLayout * ptLayout = new log4cpp::PatternLayout();
    ptLayout->setConversionPattern("%d [%p] %c %x: %m%n");

    log4cpp::OstreamAppender * osAppender = new log4cpp::OstreamAppender("osAppender", &cout);
    osAppender->setLayout(ptLayout);

    log4cpp::Category & root = log4cpp::Category::getRoot();
    log4cpp::Category & myCategory = root.getInstance("myCategory");

    myCategory.addAppender(osAppender);
    myCategory.setPriority(log4cpp::Priority::DEBUG);

    myCategory.info("I am info");
    myCategory.warn("I am warn");
    myCategory.error("I am error");
    myCategory.fatal("I am fatal");
    myCategory.debug("I am debug");
    
    return 0;
}

