#ifndef SANKAKUCHANNELPARSER_H
#define SANKAKUCHANNELPARSER_H

#include "parsers/sankakuparser.h"

namespace sankaku {
    const QString fullname = "Sankaku Channel";
    const QString shortname = "sankaku";
}

class SankakuChannelParser : public SankakuParser
{
public:
    SankakuChannelParser();
    ~SankakuChannelParser();

    QString name();
};

#endif // SANKAKUCHANNELPARSER_H
