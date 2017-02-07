#include "job.h"

const QString Job::INITIAL_URL = "initial_url";

Job::Job()
{
    this->done = false;
    this->search_done = false;
    this->posts_done = false;

    this->filenames = "%fname%";
    this->try_max = 3;

    this->lastSearchUrl = Job::INITIAL_URL;
}

Job::~Job()
{
    //    this->jobDB.close();
}

ostream& operator<<(ostream &os, const Job &job)
{
    os << "id: "        << job.id << endl;
    os << "site: "      << job.site.toStdString() << endl;
    os << "tags: "      << job.tags.join(", ").toStdString() << endl;
    os << "save path: " << job.save_path.toStdString() << endl;

    os << "pic types: ";
    QList<PicType> picTypesList = job.pic_types.toList();
    for (int i = 0; i < picTypesList.count(); i++) {
        os << PicInfo::to_str(picTypesList.at(i));
        os << ", ";
    }
    os << endl;

//     << picTypesList.join(", ").toStdString() << endl;
//    QStringList ratingList(job.rating.toList());
    os << "rating: ";
    QList<PostRating> postRatingList = job.rating.toList();
    for (int i = 0; i < postRatingList.count(); i++) {
        os << PostInfo::to_str(postRatingList.at(i));
        os << ", ";
    }
    os << endl;

//    << ratingList.join(", ").toStdString() << endl;



//    QStringList fileTypesList(job.file_types.toList());
    os << "file types: ";
    QList<PicFormat> picFormatList = job.file_types.toList();
    for (int i = 0; i < picFormatList.count(); i++) {
        os << PicInfo::to_str(picFormatList.at(i));
        os << ", ";
    }
    os << endl;

//    << fileTypesList.join(", ").toStdString() << endl;
    return os;
}

int Job::getId() const
{
    return id;
}

void Job::setId(const int value)
{
    id = value;
}

//bool Job::picType(QString pictype) const
//{
//    return this->pic_types.contains(pictype);
//}
