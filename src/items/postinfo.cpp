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
            return "all";
        }
    }
    return "";
}

int PostInfo::getId() const
{
    return _id;
}

void PostInfo::setId(int value)
{
    _id = value;
}

QString PostInfo::getUrl() const
{
    return _url;
}

void PostInfo::setUrl(const QString &value)
{
    _url = value;
}

QList<PicInfo> PostInfo::getPics() const
{
    return _pics;
}

void PostInfo::setPics(const QList<PicInfo> &value)
{
    _pics = value;
}

PostRating PostInfo::getRating() const
{
    return _rating;
}

void PostInfo::setRating(const PostRating &value)
{
    _rating = value;
}

ostream& operator <<(ostream &os, const PostInfo &postInfo)
{
    os << "rating: " << PostInfo::to_str(postInfo._rating) << endl;
    os << "========================== PICS ==========================" << endl;
    for(int i = 0; i < postInfo._pics.count(); i++) {
        cout << "pic #" << i+1 << endl;
        cout << postInfo._pics.at(i) << endl;
    }
    return os;
}
