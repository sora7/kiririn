#ifndef JOB_H
#define JOB_H

#include <iostream>

#include <QString>
#include <QStringList>
#include <QSet>

#include "items/postinfo.h"

using namespace std;

class Job
{
public:
    Job();
    ~Job();

    static const QString INITIAL_URL;

    friend ostream &operator<<(ostream &os, const Job &job);

    int id;
    QString site;
    QStringList tags;
    QString save_path;

    QSet<PicType> pic_types;
    QSet<PostRating> rating;
    QSet<PicFormat> file_types;

    QString lastSearchUrl;

    QString filenames;
    int try_max;

    bool done;
    bool search_done;
    bool posts_done;

    int getId() const;
    void setId(const int value);

//    bool picType(QString pictype) const;

private:
};

#endif // JOB_H
