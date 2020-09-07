//
// Created on 05.09.20.
//

#ifndef RANSOMWARE_LOGGER_H
#define RANSOMWARE_LOGGER_H

#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

/**
 *
 */
class Logger {

private:

public:
    /**
     *
     */
    Logger();

    /**
     *
     */
    ~Logger();

    /**
     *
     */
    void init();

};
#endif //RANSOMWARE_LOGGER_H
