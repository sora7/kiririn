#include "job.h"

Job::Job()
{
//    this->done = false;
//    this->search_done = false;
//    this->posts_done = false;

    this->_status = READY;

    this->_filenameTemplate = "%fname%";
    this->_tryMax = 3;

    this->_lastSearchUrl = QString("");
}

Job::~Job()
{
    //    this->jobDB.close();
}

ostream& operator<<(ostream &os, const Job &job)
{
    os << "id: "        << job._id << endl;
    os << "site: "      << job._site.toStdString() << endl;
    os << "tags: "      << job._tags.join(", ").toStdString() << endl;
    os << "save path: " << job._savePath.toStdString() << endl;

    os << "pic types: ";
    QList<PicType> picTypesList = job._pic_types.toList();
    for (int i = 0; i < picTypesList.count(); i++) {
        os << PicInfo::to_str(picTypesList.at(i));
        os << ", ";
    }
    os << endl;

//     << picTypesList.join(", ").toStdString() << endl;
//    QStringList ratingList(job.rating.toList());
    os << "rating: ";
    QList<PostRating> postRatingList = job._rating.toList();
    for (int i = 0; i < postRatingList.count(); i++) {
        os << PostInfo::to_str(postRatingList.at(i));
        os << ", ";
    }
    os << endl;

//    << ratingList.join(", ").toStdString() << endl;



//    QStringList fileTypesList(job.file_types.toList());
    os << "file types: ";
    QList<PicFormat> picFormatList = job._file_types.toList();
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
    return _id;
}

void Job::setId(const int value)
{
    _id = value;
}

void Job::addRating(const PostRating postRating)
{
    this->_rating << postRating;
}

void Job::addType(const PicType picType)
{
    this->_pic_types << picType;
}

void Job::addFormat(const PicFormat picFormat)
{
    this->_file_types << picFormat;
}

bool Job::okRating(const PostRating postRating) const
{
    return this->_rating.contains(postRating);
}

bool Job::okType(const PicType picType) const
{
    return this->_pic_types.contains(picType);
}

bool Job::okFormat(const PicFormat picFormat) const
{
    return this->_file_types.contains(picFormat);
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

int Job::getTryMax() const
{
    return _tryMax;
}

void Job::setTryMax(int value)
{
    _tryMax = value;
}

QString Job::getFilenameTemplate() const
{
    return _filenameTemplate;
}

void Job::setFilenameTemplate(const QString &value)
{
    _filenameTemplate = value;
}

QString Job::getSavePath() const
{
    return _savePath;
}

void Job::setSavePath(const QString &value)
{
    _savePath = value;
}

QStringList Job::getTags() const
{
    return _tags;
}

void Job::setTags(const QStringList &value)
{
    _tags = value;
}

QString Job::getSite() const
{
    return _site;
}

void Job::setSite(const QString &value)
{
    _site = value;
}

QString Job::getLastSearchUrl() const
{
    return _lastSearchUrl;
}

void Job::setLastSearchUrl(const QString &value)
{
    _lastSearchUrl = value;
}

QSet<PicFormat> Job::getPicFormats() const
{
    return _file_types;
}

void Job::setPicFormats(const QSet<PicFormat> picFormats)
{
    _file_types = picFormats;
}

QSet<PostRating> Job::getRating() const
{
    return _rating;
}

void Job::setRating(const QSet<PostRating> postRating)
{
    _rating = postRating;
}

QSet<PicType> Job::getPicTypes() const
{
    return _pic_types;
}

void Job::setPicTypes(const QSet<PicType> picTypes)
{
    _pic_types = picTypes;
}

JobStatus Job::getStatus() const
{
    return _status;
}

void Job::setStatus(const JobStatus jobStatus)
{
    _status = jobStatus;
}
