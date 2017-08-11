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

    // Logs with level argument
    MLogger::log("trace", "logging to trace");
    MLogger::log("debug", "logging to debug");
    MLogger::log("info", "logging to info");
    MLogger::log("warn", "logging to warn");
    MLogger::log("error", "logging to error");
    MLogger::log("fatal", "logging to fatal");

    // Logs with level argument and sublevel argument
    MLogger::log("info", "logging to info, sublevel 0 (default)");
    MLogger::log("info", "logging to info, sublevel 1", 1);
    MLogger::log("info", "logging to info, sublevel 2", 2);

    MLogger::blank_line();

    // Logs using specific methods
    MLogger::trace("logging to trace using method");
    MLogger::debug("logging to debug using method");
    MLogger::info("logging to info using method");
    MLogger::warn("logging to warn using method");
    MLogger::error("logging to error using method");
    MLogger::fatal("logging to fatal using method");

    // Logs using specific methods and sublevel argument
    MLogger::info("logging to info using method, sublevel 0 (default)");
    MLogger::info("logging to info using method, sublevel 1", 1);
    MLogger::info("logging to info using method, sublevel 2", 2);

    MLogger::blank_line();

    // Logs using streams
    MLogger::stream().trace() << "trace" << " using streams " << 0;
    MLogger::stream().debug() << "debug" << " using streams " << 1;
    MLogger::stream().info() << "info" << " using streams " << 2;
    MLogger::stream().warn() << "warn" << " using streams " << 3;
    MLogger::stream().error() << "error" << " using streams " << 4;
    MLogger::stream().fatal() << "fatal" << " using streams " << 5;

    // Logs using streams and sublevel argument
    MLogger::stream().info() << "info" << " using streams, sublevel " << 0 << " (default)";
    MLogger::stream().info(1) << "info" << " using streams, sublevel " << 1;
    MLogger::stream().info(2) << "info" << " using streams, sublevel " << 2;

    MLogger::blank_line();

    // Custom date getter
    struct MyTimeGetter : public MLogger::TimeGetter {
        std::string operator() () {
            return "my own custom time getter";
        }
    } myTimeGetter;
    MLogger::set_time_getter(myTimeGetter);
    MLogger::info("info with custom date formatter");

    MLogger::reset_time_getter();
    MLogger::info("info with default date formatter");

    // Get last logged message (useful for tests)
    assert(MLogger::last_message() == "info with default date formatter");

    // Non-added logging levels do not show up
    assert(MLogger::remove_level("info"));
    MLogger::info("info should not be displayed here");

    return 0;
}
