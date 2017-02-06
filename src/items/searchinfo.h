#ifndef SEARCHINFO_H
#define SEARCHINFO_H

#include <iostream>

#include <QString>
#include <QStringList>

using namespace std;

class SearchInfo
{
public:
    SearchInfo();
    ~SearchInfo();

    friend ostream &operator<<(ostream &os, const SearchInfo &searchInfo);

    bool hasNext() const;

    QString nextPage() const;
    void setNextPage(const QString &value);

    QStringList getPosts() const;
    void setPosts(const QStringList &value);

private:
    bool _hasNext;
    QString _next_page;
    QStringList _posts;
};

#endif // SEARCHINFO_H
