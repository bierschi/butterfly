
#ifndef BUTTERFLY_LOGGER_H
#define BUTTERFLY_LOGGER_H

#include <string>

#include <boost/log/trivial.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>

BOOST_LOG_GLOBAL_LOGGER(sysLogger, boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level>);

BOOST_LOG_GLOBAL_LOGGER(dataLogger, boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level>);

#define LOG_LOG_LOCATION(LOGGER, LEVEL, ARG)            \
  BOOST_LOG_SEV(LOGGER, boost::log::trivial::LEVEL)     \
    << boost::log::add_value("Line", __LINE__)          \
    << boost::log::add_value("File", __FILE__)          \
    << boost::log::add_value("Function", __FUNCTION__) << ARG;

// System Log macros
#define LOG_TRACE(ARG) LOG_LOG_LOCATION(sysLogger::get(), trace, ARG);
#define LOG_DEBUG(ARG) LOG_LOG_LOCATION(sysLogger::get(), debug, ARG);
#define LOG_INFO(ARG)  LOG_LOG_LOCATION(sysLogger::get(), info, ARG);
#define LOG_WARN(ARG)  LOG_LOG_LOCATION(sysLogger::get(), warning, ARG);
#define LOG_ERROR(ARG) LOG_LOG_LOCATION(sysLogger::get(), error, ARG);
#define LOG_FATAL(ARG) LOG_LOG_LOCATION(sysLogger::get(), fatal, ARG);

// Data log macros
#define LOG_DATA_TRACE(ARG) BOOST_LOG_SEV(dataLogger::get(), boost::log::trivial::trace) << ARG
#define LOG_DATA_DEBUG(ARG) BOOST_LOG_SEV(dataLogger::get(), boost::log::trivial::debug) << ARG
#define LOG_DATA_INFO(ARG)  BOOST_LOG_SEV(dataLogger::get(), boost::log::trivial::info) << ARG
#define LOG_DATA_WARN(ARG)  BOOST_LOG_SEV(dataLogger::get(), boost::log::trivial::warning) << ARG
#define LOG_DATA_ERROR(ARG) BOOST_LOG_SEV(dataLogger::get(), boost::log::trivial::error) << ARG
#define LOG_DATA_FATAL(ARG) BOOST_LOG_SEV(dataLogger::get(), boost::log::trivial::fatal) << ARG

/**
 * class Logger to log important statements to console or file
 */
class Logger
{

public:

    /**
     * Inits the default Logger
     */
    static void init();

    /**
     * Inits the Logger with a config file
     *
     * @param configFileName: name of the config file
     */
    static void initFromConfig(const std::string &configFileName);

    /**
     * Adds a data file log
     *
     * @param logFileName: name of the log file
     */
    static void addDataFileLog(const std::string &logFileName);

    /**
     * Disables logging
     */
    static void disable();

};

#endif //BUTTERFLY_LOGGER_H
