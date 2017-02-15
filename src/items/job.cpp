#include "job.h"

Job::Job()
{
//    this->done = false;
//    this->search_done = false;
//    this->posts_done = false;

    this->status = READY;

    this->filenames = "%fname%";
    this->try_max = 3;

    this->lastSearchUrl = QString("");
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

void Job::addRating(const PostRating postRating)
{
    this->rating << postRating;
}

void Job::addType(const PicType picType)
{
    this->pic_types << picType;
}

void Job::addFormat(const PicFormat picFormat)
{
    this->file_types << picFormat;
}

bool Job::okRating(const PostRating postRating) const
{
    return this->rating.contains(postRating);
}

bool Job::okType(const PicType picType) const
{
    return this->pic_types.contains(picType);
}

bool Job::okFormat(const PicFormat picFormat) const
{
    return this->file_types.contains(picFormat);
}

string Job::to_str(JobStatus jobStatus)
{
    switch (jobStatus) {
        case READY: {
            return "ready";
        }
        case SEARCH_START: {
            return "search start";
        }
        case SEARCH_DONE: {
            return "search done";
        }
        case POSTS_DONE: {
            return "posts done";
        }
        case PICS_DONE: {
            return "picsc done";
        }
    }
    return "";
}

JobStatus Job::getStatus() const
{
    return status;
}

void Job::setStatus(const JobStatus jobStatus)
{
    status = jobStatus;
}
