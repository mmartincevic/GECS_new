#ifndef GECS_XMLSETTINGSPARSER_H
#define GECS_XMLSETTINGSPARSER_H

#pragma once

#include "tinyxml2.h"
#include <mutex>
#include <string>

namespace gecs {

    class XMLSettingsParser {
    private:
        // Private constructor
        XMLSettingsParser();

        // Delete copy constructor and assignment operator
        XMLSettingsParser(const XMLSettingsParser&) = delete;
        XMLSettingsParser& operator=(const XMLSettingsParser&) = delete;

        // The single instance of the class
        static XMLSettingsParser instance;

        // Mutex for thread-safe singleton initialization and XML parsing
        static std::mutex mtx;

        // XML document
        tinyxml2::XMLDocument doc;

    public:
        // Method to get the single instance of the class
        static XMLSettingsParser& getInstance();

        // Method to load XML settings from a file
        bool loadSettings(const std::string& filename);

        // Method to get a setting value by its path
        std::string getSetting(const std::string& path);
    };

} // namespace gecs

#endif // GECS_XMLSETTINGSPARSER_H
