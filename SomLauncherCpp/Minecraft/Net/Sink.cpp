#include "Sink.h"

void Net::Sink::addValidator(Validator* validator)
{
    if (validator)
    {
        this->validators.push_back(std::shared_ptr<Validator>(validator));
    }
}

bool Net::Sink::finalizeAllValidators(QNetworkReply& reply)
{
    for (auto& validator : this->validators)
    {
        if (!validator->validate(reply))
            return false;
    }
    return true;
}

bool Net::Sink::failAllValidators()
{
    bool success = true;
    for (auto& validator : this->validators)
    {
        success &= validator->abort();
    }
    return success;
}

bool Net::Sink::initAllValidators(QNetworkRequest& request)
{
    for (auto& validator : this->validators)
    {
        if (!validator->init(request))
            return false;
    }
    return true;
}

bool Net::Sink::writeAllValidators(QByteArray& data)
{
    for (auto& validator : this->validators)
    {
        if (!validator->write(data))
            return false;
    }
    return true;
}
