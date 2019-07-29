#include "Mylogger.h"
#include <iostream>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
using std::cout;
using std::endl;
using namespace wd;

namespace wd
{

Mylogger * Mylogger::getInstance()
{
    if(_pInstance == nullptr)
        _pInstance = new Mylogger();
    return _pInstance;
}

void Mylogger::destroy()
{
    if(_pInstance)
        delete _pInstance;
}

Mylogger::Mylogger()
: _mycategory( Category::getRoot().getInstance("mycategory") )
{
    PatternLayout * pLayout1 = new PatternLayout();
    pLayout1->setConversionPattern("%d [%p] %m%n");

    PatternLayout * pLayout2 = new PatternLayout();
    pLayout2->setConversionPattern("%d [%p] %m%n");

    OstreamAppender * pOstreamAppender = new OstreamAppender("OstreamAppender", &cout);
    pOstreamAppender->setLayout(pLayout1);

    FileAppender * pFileAppender = new FileAppender("FileAppender","log.txt");
    pFileAppender->setLayout(pLayout2);

    _mycategory.addAppender(pOstreamAppender);
    _mycategory.addAppender(pFileAppender);
    _mycategory.setPriority(Priority::DEBUG);

    cout << "Mylogger()" << endl;
}

Mylogger::~Mylogger()
{
    Category::shutdown();
    cout << "~Mylogger()" << endl;
}

void Mylogger::error(const char * msg)
{
    _mycategory.error(msg);
    
}

void Mylogger::warn(const char * msg)
{
    _mycategory.warn(msg);
}

void Mylogger::info(const char * msg)
{
    _mycategory.info(msg);
}

void Mylogger::debug(const char * msg)
{
    _mycategory.debug(msg);
}

Mylogger * Mylogger::_pInstance = nullptr;

}


