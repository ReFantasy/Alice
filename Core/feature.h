#ifndef FEATURE_H
#define FEATURE_H
#include <QString>
#include <QRegExp>

class StringProcess
{
public:
    virtual QString Process(QString s)
    {
        return s;
    }
};

class ReplaceLinefeed:public StringProcess
{
public:

    virtual QString Process(QString s)override
    {
        return s.replace(QRegExp(QString("\\n")), QChar('\0x20'));
    }
};



#endif // FEATURE_H
