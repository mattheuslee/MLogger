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
    MLogger::log_trace("trace with colour");
    MLogger::log_debug("debug with colour");
    MLogger::log_info("info with colour");
    MLogger::log_warn("warn with colour");
    MLogger::log_error("error with colour");
    MLogger::log_fatal("fatal with colour");

    // Logs using streams
    MLogger::log_trace_stream() << "trace" << " using streams " << 0; MLogger::end_log_stream();
    MLogger::log_debug_stream() << "debug" << " using streams " << 1; MLogger::end_log_stream();
    MLogger::log_info_stream() << "info" << " using streams " << 2; MLogger::end_log_stream();
    MLogger::log_warn_stream() << "warn" << " using streams " << 3; MLogger::end_log_stream();
    MLogger::log_error_stream() << "error" << " using streams " << 4; MLogger::end_log_stream();
    MLogger::log_fatal_stream() << "fatal" << " using streams " << 5; MLogger::end_log_stream();

    // Custom date getter
    struct MyTimeGetter : public MLogger::TimeGetter {
        std::string operator() () {
            return "my own custom time getter";
        }
    } myTimeGetter;
    MLogger::set_time_getter(myTimeGetter);
    MLogger::log_info("info with custom date formatter");

    MLogger::reset_time_getter();
    MLogger::log_info("info with default date formatter");

    // Get last logged message (useful for tests)
    assert(MLogger::last_message() == "info with default date formatter");

    // Non-added logging levels do not show up
    assert(MLogger::remove_level("info"));
    MLogger::log_info("info should not be displayed here");

    return 0;
}
