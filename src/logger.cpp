#include <boost/algorithm/string/predicate.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/exception_handler.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/filter_parser.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/log/utility/setup/settings.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <fstream>
#include <string>

#include "logger.h"

BOOST_LOG_GLOBAL_LOGGER_CTOR_ARGS(sysLogger,
                                  boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level>,
                                  (boost::log::keywords::channel = "SYSLF"));

BOOST_LOG_GLOBAL_LOGGER_CTOR_ARGS(dataLogger,
                                  boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level>,
                                  (boost::log::keywords::channel = "DATALF"));

// Custom formatter factory to add timestamp format support in config ini file.
class TimestampFormatterFactory : public boost::log::basic_formatter_factory<char, boost::posix_time::ptime>
{

public:
    formatter_type create_formatter(const boost::log::attribute_name &name, const args_map &args)
    {
        args_map::const_iterator it = args.find("format");
        if (it != args.end())
        {
            return boost::log::expressions::stream
                    << boost::log::expressions::format_date_time<boost::posix_time::ptime>(
                            boost::log::expressions::attr<boost::posix_time::ptime>(name), it->second);
        } else
        {
            return boost::log::expressions::stream << boost::log::expressions::attr<boost::posix_time::ptime>(name);
        }
    }
};

// Custom formatter factory to add uptime format support in config ini file.
class UptimeFormatterFactory : public boost::log::basic_formatter_factory<char, boost::posix_time::time_duration>
{

public:
    formatter_type create_formatter(const boost::log::attribute_name &name, const args_map &args)
    {
        args_map::const_iterator it = args.find("format");
        if (it != args.end())
        {
            return boost::log::expressions::stream
                    << boost::log::expressions::format_date_time<boost::posix_time::time_duration>(
                            boost::log::expressions::attr<boost::posix_time::time_duration>(name), it->second);
        } else
        {
            return boost::log::expressions::stream
                    << boost::log::expressions::attr<boost::posix_time::time_duration>(name);
        }
    }
};

void Logger::init()
{
    initFromConfig("");
}

void Logger::initFromConfig(const std::string &configFileName)
{

    boost::log::core::get()->set_exception_handler(boost::log::make_exception_suppressor());

    // add common attributes (lineid, timestamp, processid, threadid)
    boost::log::add_common_attributes();
    // Add boost log timer as global attribute Uptime
    boost::log::core::get()->add_global_attribute("Uptime", boost::log::attributes::timer());
    // Allows %Severity% to be used in ini config file for property Filter.
    boost::log::register_simple_filter_factory<boost::log::trivial::severity_level, char>("Severity");
    // Allows %Severity% to be used in ini config file for property Format.
    boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");
    // Allows %TimeStamp(format=\"%Y.%m.%d %H:%M:%S.%f\")% to be used in ini config file for property Format.
    boost::log::register_formatter_factory("TimeStamp", boost::make_shared<TimestampFormatterFactory>());
    // Allows %Uptime(format=\"%O:%M:%S.%f\")% to be used in ini config file for property Format.
    boost::log::register_formatter_factory("Uptime", boost::make_shared<UptimeFormatterFactory>());

    if (configFileName.empty())
    {
        //config file empty. Log only to console
    } else
    {
        std::ifstream ifs(configFileName);
        if (!ifs.is_open())
        {
            LOG_WARN("Unable to open logging config file: " << configFileName);
        } else
        {

            try
            {
                boost::log::init_from_stream(ifs);
            } catch (std::exception &e)
            {
                std::string err = "Caught exception initializing boost logging: ";
                err += e.what();
                std::cerr << "ERROR: " << err << std::endl;
                LOG_ERROR(err);
            }

        }
    }
}

void Logger::addDataFileLog(const std::string &logFileName)
{

    // create a text file sink
    boost::shared_ptr<boost::log::sinks::text_ostream_backend> backend(new boost::log::sinks::text_ostream_backend());
    backend->add_stream(boost::shared_ptr<std::ostream>(new std::ofstream(logFileName)));

    // flush after each log record
    backend->auto_flush(true);

    // create a sink for the backend
    typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> sink_t;
    boost::shared_ptr<sink_t> sink(new sink_t(backend));

    // log output formatter
    sink->set_formatter(
            boost::log::expressions::format("[%1%][%2%] %3%")
            % boost::log::expressions::attr<boost::posix_time::ptime>("TimeStamp")
            % boost::log::trivial::severity
            % boost::log::expressions::smessage
    );

    // filter by severity and by DATALF channel
    sink->set_filter(
            boost::log::trivial::severity >= boost::log::trivial::info &&
            boost::log::expressions::attr<std::string>("Channel") == "DATALF");

    // add it to the core
    boost::log::core::get()->add_sink(sink);
}

void Logger::disable()
{
    boost::log::core::get()->set_logging_enabled(false);
}
