#include "picnamer.h"

PicNamer::PicNamer()
{
}

PicNamer::~PicNamer()
{
}

void PicNamer::setPattern(const QString pattern)
{
    this->m_pattern = pattern;
}

void PicNamer::setPicsPath(const QString picsPath)
{
    this->m_picsPath = picsPath;
}

QString PicNamer::checkName(const QString oldPicName) const
{
    QString picName = this->m_pattern;

    // original pic names
    picName.replace("%fname%", oldPicName);

    // "normal" whitespaces fix
    picName.replace("%20", " ");
    // brackets
    picName.replace("%28", "(");
    picName.replace("%29", ")");


    //filename check
    QFileInfo info(QDir(this->m_picsPath), picName);
    QString picFullName = info.absoluteFilePath();

    QString picFileName = info.completeBaseName();
    QString picFileExt = info.suffix();


    int count = 0;
    while (QFile::exists(picFullName)) {
        count++;
        info = QFileInfo(QDir(this->m_picsPath),
                         picFileName +
                         "_" +
                         QString::number(count) +
                         "." +
                         picFileExt
                         );
        picFullName = info.absoluteFilePath();
    }

    return picFullName;
}
