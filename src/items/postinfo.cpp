#include "postinfo.h"

PostInfo::PostInfo()
{
//    this->_has_orig = 0;
//    this->_has_resize = 0;
}

PostInfo::~PostInfo()
{
}

string PostInfo::to_str(PostRating postRating)
{
    switch (postRating) {
        case SAFE: {
            return "safe";
        }
        case QUESTIONABLE: {
            return "questionable";
        }
        case EXPLICIT: {
            return "explicit";
        }
        case RT_OTHER: {
            return "other";
        }
    }
    return "";
}

int PostInfo::getId() const
{
    return m_id;
}

void PostInfo::setId(int value)
{
    m_id = value;
}

QString PostInfo::getUrl() const
{
    return m_url;
}

void PostInfo::setUrl(const QString &value)
{
    m_url = value;
}

QList<PicInfo> PostInfo::getPics() const
{
    return m_pics;
}

void PostInfo::setPics(const QList<PicInfo> &value)
{
    m_pics = value;
}

PostRating PostInfo::getRating() const
{
    return m_rating;
}

void PostInfo::setRating(const PostRating &value)
{
    m_rating = value;
}

ostream& operator <<(ostream &os, const PostInfo &postInfo)
{
    os << "rating: " << PostInfo::to_str(postInfo.m_rating) << endl;
    os << "========================== PICS ==========================" << endl;
    for(int i = 0; i < postInfo.m_pics.count(); i++) {
        cout << "pic #" << i+1 << endl;
        cout << postInfo.m_pics.at(i) << endl;
    }
    return os;
}
