#include"Log.h"

using namespace T;
using namespace T::Util;
using namespace T::FileUtil;


namespace T
{

Log::Log()
    :file_("log", 10)
    ,work_("fem", &Log::write, this)
{

}

Log::~Log()
{
    file_.flush();
    work_.stop();
}


void Log::write()
{
    std::string str;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [] { return Log::sharedInstance().getLogStream().empty();});
        str = os_.buffer().toString();
        os_.reset();
    }
    file_.write(str);
}

Log& Log::sharedInstance()
{
    static Log instance;
    return instance;
}

} //end namespace T

