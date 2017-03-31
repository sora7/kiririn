#include "searchinfo.h"

SearchInfo::SearchInfo()
{
    this->m_hasNext = false;
}

SearchInfo::~SearchInfo()
{
}

bool SearchInfo::hasNext() const
{
    return m_hasNext;
}

QString SearchInfo::nextPage() const
{
    return m_next_page;
}

void SearchInfo::setNextPage(const QString &value)
{
    if (value.length() > 0) {
        this->m_hasNext = true;
    }
    m_next_page = value;
}

QStringList SearchInfo::getPosts() const
{
    return m_posts;
}

void SearchInfo::setPosts(const QStringList &value)
{
    m_posts = value;
}

ostream& operator <<(ostream &os, const SearchInfo &searchInfo)
{
    os << "next: " << searchInfo.m_next_page.toStdString() << endl;
    for(int i = 0; i < searchInfo.m_posts.count(); i++) {
        cout << "post #" << i+1;
        cout << " " << searchInfo.m_posts.at(i).toStdString() << endl;
    }
    return os;
}
