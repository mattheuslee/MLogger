#pragma once

#ifndef MLOGGER_HPP_
#define MLOGGER_HPP_

//!
//! termcolor
//! ~~~~~~~~~
//!
//! termcolor is a header-only c++ library for printing colored messages
//! to the terminal. Written just for fun with a help of the Force.
//!
//! :copyright: (c) 2013 by Ihor Kalnytskyi
//! :license: BSD, see LICENSE for details
//!

// the following snippet of code detects the current OS and
// defines the appropriate macro that is used to wrap some
// platform specific things
#if defined(_WIN32) || defined(_WIN64)
#   define TERMCOLOR_OS_WINDOWS
#elif defined(__APPLE__)
#   define TERMCOLOR_OS_MACOS
#elif defined(__unix__) || defined(__unix)
#   define TERMCOLOR_OS_LINUX
#else
#   error unsupported platform
#endif


// This headers provides the `isatty()`/`fileno()` functions,
// which are used for testing whether a standart stream refers
// to the terminal. As for Windows, we also need WinApi funcs
// for changing colors attributes of the terminal.
#if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
#   include <unistd.h>
#elif defined(TERMCOLOR_OS_WINDOWS)
#   include <io.h>
#   include <windows.h>
#endif


#include <iostream>
#include <cstdio>



namespace termcolor
{
    // Forward declaration of the `_internal` namespace.
    // All comments are below.
    namespace _internal
    {
        inline FILE* get_standard_stream(const std::ostream& stream);
        inline bool is_atty(const std::ostream& stream);

    #if defined(TERMCOLOR_OS_WINDOWS)
        inline void win_change_attributes(std::ostream& stream, int foreground, int background=-1);
    #endif
    }


    inline
    std::ostream& reset(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[00m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1, -1);
        #endif
        }
        return stream;
    }


    inline
    std::ostream& bold(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[1m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }


    inline
    std::ostream& dark(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[2m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }


    inline
    std::ostream& underline(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[4m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }


    inline
    std::ostream& blink(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[5m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }


    inline
    std::ostream& reverse(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[7m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }


    inline
    std::ostream& concealed(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[8m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }


    inline
    std::ostream& grey(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[30m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                0   // grey (black)
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& red(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[31m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_RED
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& green(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[32m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_GREEN
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& yellow(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[33m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_GREEN | FOREGROUND_RED
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& blue(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[34m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& magenta(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[35m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_RED
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& cyan(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[36m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_GREEN
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& white(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[37m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
            );
        #endif
        }
        return stream;
    }



    inline
    std::ostream& on_grey(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[40m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                0   // grey (black)
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_red(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[41m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_RED
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_green(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[42m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_yellow(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[43m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_RED
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_blue(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[44m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_BLUE
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_magenta(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[45m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_BLUE | BACKGROUND_RED
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_cyan(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[46m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_BLUE
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_white(std::ostream& stream)
    {
        if (_internal::is_atty(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[47m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED
            );
        #endif
        }

        return stream;
    }



    //! Since C++ hasn't a way to hide something in the header from
    //! the outer access, I have to introduce this namespace which
    //! is used for internal purpose and should't be access from
    //! the user code.
    namespace _internal
    {
        //! Since C++ hasn't a true way to extract stream handler
        //! from the a given `std::ostream` object, I have to write
        //! this kind of hack.
        inline
        FILE* get_standard_stream(const std::ostream& stream)
        {
            if (&stream == &std::cout)
                return stdout;
            else if ((&stream == &std::cerr) || (&stream == &std::clog))
                return stderr;

            return 0;
        }


        //! Test whether a given `std::ostream` object refers to
        //! a terminal.
        inline
        bool is_atty(const std::ostream& stream)
        {
            FILE* std_stream = get_standard_stream(stream);

            // Unfortunately, fileno() ends with segmentation fault
            // if invalid file descriptor is passed. So we need to
            // handle this case gracefully and assume it's not a tty
            // if standard stream is not detected, and 0 is returned.
            if (!std_stream)
                return false;

        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            return ::isatty(fileno(std_stream));
        #elif defined(TERMCOLOR_OS_WINDOWS)
            return ::_isatty(_fileno(std_stream));
        #endif
        }


    #if defined(TERMCOLOR_OS_WINDOWS)
        //! Change Windows Terminal colors attribute. If some
        //! parameter is `-1` then attribute won't changed.
        inline void win_change_attributes(std::ostream& stream, int foreground, int background)
        {
            // yeah, i know.. it's ugly, it's windows.
            static WORD defaultAttributes = 0;

            // get terminal handle
            HANDLE hTerminal = INVALID_HANDLE_VALUE;
            if (&stream == &std::cout)
                hTerminal = GetStdHandle(STD_OUTPUT_HANDLE);
            else if (&stream == &std::cerr)
                hTerminal = GetStdHandle(STD_ERROR_HANDLE);

            // save default terminal attributes if it unsaved
            if (!defaultAttributes)
            {
                CONSOLE_SCREEN_BUFFER_INFO info;
                if (!GetConsoleScreenBufferInfo(hTerminal, &info))
                    return;
                defaultAttributes = info.wAttributes;
            }

            // restore all default settings
            if (foreground == -1 && background == -1)
            {
                SetConsoleTextAttribute(hTerminal, defaultAttributes);
                return;
            }

            // get current settings
            CONSOLE_SCREEN_BUFFER_INFO info;
            if (!GetConsoleScreenBufferInfo(hTerminal, &info))
                return;

            if (foreground != -1)
            {
                info.wAttributes &= ~(info.wAttributes & 0x0F);
                info.wAttributes |= static_cast<WORD>(foreground);
            }

            if (background != -1)
            {
                info.wAttributes &= ~(info.wAttributes & 0xF0);
                info.wAttributes |= static_cast<WORD>(background);
            }

            SetConsoleTextAttribute(hTerminal, info.wAttributes);
        }
    #endif // TERMCOLOR_OS_WINDOWS

    } // namespace _internal

} // namespace termcolor

#undef TERMCOLOR_OS_WINDOWS
#undef TERMCOLOR_OS_MACOS
#undef TERMCOLOR_OS_LINUX

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

class MLogger {

public:
    typedef std::ostream& (*Colour)(std::ostream &);

    /***** output modifiers *****/
    static bool add_ostream(std::ostream & stream) {
        auto streamRefWrapper = std::reference_wrapper<std::ostream>(stream);
        if (!find_ostream_wrapper_(stream)) {
            instance_().ostreamWrappers_.push_back(streamRefWrapper);
            return true;
        }
        return false;
    }

    static void clear_ostreams() {
        while (!instance_().ostreamWrappers_.empty()) {
            instance_().ostreamWrappers_.erase(instance_().ostreamWrappers_.begin());
        }
        while (!instance_().ostreamPtrs_.empty()) {
            instance_().ostreamPtrs_.erase(instance_().ostreamPtrs_.begin());
        }
    }

    static bool add_file(std::string const & fileName) {
        auto file = std::make_shared<std::ofstream>();
        file->open(fileName);
        if (file->is_open() && !find_ostream_ptr_(*file)) {
            instance_().ostreamPtrs_.push_back(file);
            return true;
        }
        return false;
    }

    /***** level controls *****/
    static bool add_level(std::string const & level) {
        if (is_valid_level_(level)) {
            return instance_().levels_.insert(level).second;
        }
        return false;
    }

    static bool add_levels(std::initializer_list<std::string> levels) {
        auto result = true;
        for (auto const &level : levels) {
            if (!add_level(level)) {
                result = false;
            }
        }
        return result;
    }

    static bool remove_level(std::string const & level) {
        return instance_().levels_.erase(level) == 1;
    }

    static void clear_levels() {
        instance_().levels_.clear();
    }

    static bool set_max_level(std::string const & level) {
        auto result = false;
        if (is_valid_level_(level)) {
            result = true;
            clear_levels();
            if (!add_level(level)) {
                result = false;
            }
            if (level == "debug") {
                if (!add_levels({"trace"})) {
                    result = false;
                }
            } else if (level == "info") {
                if (!add_levels({"trace", "debug"})) {
                    result = false;
                }
            } else if (level == "warn") {
                if (!add_levels({"trace", "debug", "info"})) {
                    result = false;
                }
            } else if (level == "error") {
                if (!add_levels({"trace", "debug", "info", "warn"})) {
                    result = false;
                }
            } else if (level == "fatal") {
                if (!add_levels({"trace", "debug", "info", "warn", "error"})) {
                    result = false;
                }
            }
        }
        return result;
    }

    /***** format controls *****/
    struct TimeGetter {
        // Returns the current time formatted as a std::string
        virtual std::string operator() () {
            return "";
        }
    };

    struct StlTimeGetter : public TimeGetter {
        std::string operator() () {
            auto currTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            auto currTimeStr = std::string(std::ctime(&currTime));
            return currTimeStr.erase(currTimeStr.size() - 1); // Remove newline character
        }
    };

    template <class TG>
    static void set_time_getter(TG & timeGetter) {
        instance_().timeGetter_ = std::shared_ptr<TG>(&timeGetter);
    }

    static void reset_time_getter() {
        instance_().timeGetter_ = std::make_shared<StlTimeGetter>();
    }

    /***** logging *****/
    static void blank_line() {
        for (auto & ostreamWrapper : instance_().ostreamWrappers_) {
            ostreamWrapper.get() << std::endl;
        }
        for (auto & streamPtr : instance_().ostreamPtrs_) {
            *streamPtr << std::endl;
        }
    }

    static void log(std::string const & level, std::string const & message, int const & subLevel = 0) {
        if (!message.empty() && is_added_level_(level)) {
            auto colour = get_colour_(level);
            auto additionalWhitespace = std::string(subLevel * 4, ' ');
            std::ostringstream oss;
            oss << additionalWhitespace << get_time_() << " [" + level + "] : " << message;
            for (auto & ostreamWrapper : instance_().ostreamWrappers_) {
                ostreamWrapper.get() << colour << oss.str() << termcolor::reset << std::endl;
            }
            for (auto & streamPtr : instance_().ostreamPtrs_) {
                *streamPtr << colour << oss.str() << termcolor::reset << std::endl;
            }
            instance_().lastMessage_ = message;
        }
    }

    static void trace(std::string const & message, int const & subLevel = 0) {
        log("trace", message, subLevel);
    }

    static void debug(std::string const & message, int const & subLevel = 0) {
        log("debug", message, subLevel);
    }

    static void info(std::string const & message, int const & subLevel = 0) {
        log("info", message, subLevel);
    }

    static void warn(std::string const & message, int const & subLevel = 0) {
        log("warn", message, subLevel);
    }

    static void error(std::string const & message, int const & subLevel = 0) {
        log("error", message, subLevel);
    }

    static void fatal(std::string const & message, int const & subLevel = 0) {
        log("fatal", message, subLevel);
    }

    /***** for stream logging *****/
    class stream {

    public:
        stream() {}

        ~stream() {
            MLogger::log(level_, stream_.str(), subLevel_);
        }

        std::ostringstream& trace(int const & subLevel = 0) {
            level_ = "trace";
            subLevel_ = subLevel;
            return stream_;
        }

        std::ostringstream& debug(int const & subLevel = 0) {
            level_ = "debug";
            subLevel_ = subLevel;
            return stream_;
        }

        std::ostringstream& info(int const & subLevel = 0) {
            level_ = "info";
            subLevel_ = subLevel;
            return stream_;
        }

        std::ostringstream& warn(int const & subLevel = 0) {
            level_ = "warn";
            subLevel_ = subLevel;
            return stream_;
        }

        std::ostringstream& error(int const & subLevel = 0) {
            level_ = "error";
            subLevel_ = subLevel;
            return stream_;
        }

        std::ostringstream& fatal(int const & subLevel = 0) {
            level_ = "fatal";
            subLevel_ = subLevel;
            return stream_;
        }

    private:
        std::string level_;
        int subLevel_;
        std::ostringstream stream_;

    };

    /***** retrieve last logged message *****/
    static std::string last_message() {
        return instance_().lastMessage_;
    }

private:
    typedef void (*Log)(std::string const &);

    MLogger() {
        timeGetter_ = std::make_shared<StlTimeGetter>();
    }

    std::vector<std::reference_wrapper<std::ostream>> ostreamWrappers_;
    std::vector<std::shared_ptr<std::ostream>> ostreamPtrs_;
    std::unordered_set<std::string> levels_;
    std::shared_ptr<TimeGetter> timeGetter_;
    std::string lastMessage_;
    std::ostringstream streamer_;
    Log streamerLogger_;

    static MLogger& instance_() {
        static MLogger instance;
        return instance;
    }

    static bool find_ostream_wrapper_(std::ostream const & stream) {
        return std::any_of(instance_().ostreamWrappers_.begin(), instance_().ostreamWrappers_.end(),
            [&](std::reference_wrapper<std::ostream> & wrapper) {
                return wrapper.get() == stream;
            });
    }

    static bool find_ostream_ptr_(std::ostream const & stream) {
        return std::any_of(instance_().ostreamPtrs_.begin(), instance_().ostreamPtrs_.end(),
            [&](std::shared_ptr<std::ostream> & ptr) {
                return *ptr == stream;
            });
    }

    static Colour get_colour_(std::string const & level) {
        if (level == "fatal") {
            return termcolor::red;
        } else if (level == "error") {
            return termcolor::magenta;
        } else if (level == "warn") {
            return termcolor::yellow;
        } else if (level == "info") {
            return termcolor::green;
        } else {
            return termcolor::reset;
        }
    }

    static std::string get_time_() {
        return (*(instance_().timeGetter_))();
    }

    static bool is_valid_level_(std::string const & level) {
        return level == "trace"
            || level == "debug"
            || level == "info"
            || level == "warn"
            || level == "error"
            || level == "fatal";
    }

    static bool is_added_level_(std::string const & level) {
        return instance_().levels_.find(level) != instance_().levels_.end();
    }

};

#endif // MLOGGER_HPP_
