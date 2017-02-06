#include "searchinfo.h"

SearchInfo::SearchInfo()
{
    this->_hasNext = false;
}

SearchInfo::~SearchInfo()
{
}

bool SearchInfo::hasNext() const
{
    return _hasNext;
}

QString SearchInfo::nextPage() const
{
    return _next_page;
}

void SearchInfo::setNextPage(const QString &value)
{
    if (value.length() > 0) {
        this->_hasNext = true;
    }
    _next_page = value;
}

QStringList SearchInfo::getPosts() const
{
    return _posts;
}

void SearchInfo::setPosts(const QStringList &value)
{
    _posts = value;
}

ostream& operator <<(ostream &os, const SearchInfo &searchInfo)
{
    os << "next: " << searchInfo._next_page.toStdString() << endl;
    for(int i = 0; i < searchInfo._posts.count(); i++) {
        cout << "post #" << i+1;
        cout << " " << searchInfo._posts.at(i).toStdString() << endl;
    }
    return os;
}
