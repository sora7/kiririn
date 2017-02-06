#include "postinfo.h"

PostInfo::PostInfo()
{
//    this->_has_orig = 0;
//    this->_has_resize = 0;
}

PostInfo::~PostInfo()
{
}

ostream& operator <<(ostream &os, const PostInfo &postInfo)
{
    os << "rating: " << postInfo.rating.toStdString() << endl;
    os << "========================== PICS ==========================" << endl;
    for(int i = 0; i < postInfo.pics.count(); i++) {
        cout << "pic #" << i+1 << endl;
        cout << postInfo.pics.at(i) << endl;
    }
    return os;
}
