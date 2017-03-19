#ifndef PICNAMER_H
#define PICNAMER_H

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QRegExp>

class PicNamer
{
public:
    PicNamer();
    ~PicNamer();

    void setPattern(const QString pattern);
    void setPicsPath(const QString picsPath);

    QString checkName(const QString oldPicName) const;
private:
    QString _pattern;
    QString _picsPath;
};

#endif // PICNAMER_H
