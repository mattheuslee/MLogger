#include "MLogger.hpp"

#include <cassert>
#include <iostream>
#include <string>

int main(void) {
    using namespace std;

    // Add and remove types of outputs
    assert(MLogger::add_ostream(cout));
    MLogger::clear_ostreams();
    assert(MLogger::add_ostream(cout));
    assert(MLogger::add_ostream(cout) == false); // Checks for duplicates
    assert(MLogger::add_file("test.log"));

    // Add logging levels to be displayed
    assert(MLogger::add_level("trace"));
    assert(MLogger::add_level("debug"));
    assert(MLogger::add_level("info"));
    assert(MLogger::add_level("warn"));
    assert(MLogger::add_level("error"));
    assert(MLogger::add_level("fatal"));

    // Logs without colour
    MLogger::log("trace", "trace, no colour"); // Logs without colour
    MLogger::log("debug", "debug, no colour"); // Logs without colour
    MLogger::log("info", "info, no colour"); // Logs without colour
    MLogger::log("warn", "warn, no colour"); // Logs without colour
    MLogger::log("error", "error, no colour"); // Logs without colour
    MLogger::log("fatal", "fatal, no colour"); // Logs without colour

    // Logs with default colours
    MLogger::logTrace("trace with colour");
    MLogger::logDebug("debug with colour");
    MLogger::logInfo("info with colour");
    MLogger::logWarn("warn with colour");
    MLogger::logError("error with colour");
    MLogger::logFatal("fatal with colour");

    // Custom date getter
    struct MyTimeGetter : public MLogger::TimeGetter {
        std::string operator() () {
            return "my own custom time getter";
        }
    } myTimeGetter;
    MLogger::set_time_getter(myTimeGetter);
    MLogger::logInfo("info with custom date formatter");

    MLogger::reset_time_getter();
    MLogger::logInfo("info with default date formatter");

    // Get last logged message (useful for tests)
    assert(MLogger::last_message() == "info with default date formatter");

    // Non-added logging levels do not show up
    assert(MLogger::remove_level("info"));
    MLogger::logInfo("info should not be displayed here");

    return 0;
}
