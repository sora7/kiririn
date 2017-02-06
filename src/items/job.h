#ifndef JOB_H
#define JOB_H

//#include <QtSql>

#include <iostream>

#include <QString>
#include <QStringList>
#include <QSet>

using namespace std;

namespace job {
    const QString INIT_URL = "initial_url";
}

//typedef QSet<QString> ItemSet;

class Job
{
public:
    Job();
    ~Job();

    friend ostream &operator<<(ostream &os, const Job &job);

    int id;
    QString site;
    QStringList tags;
    QString save_path;

    QSet<QString> pic_types;
    QSet<QString> rating;
    QSet<QString> file_types;

    QString lastSearchUrl;

    QString filenames;
    int try_max;

    bool done;
    bool search_done;
    bool posts_done;

    int getId() const;
    void setId(int value);

private:
};

#endif // JOB_H
