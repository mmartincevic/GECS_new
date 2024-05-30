#include "XMLSettingsParser.h"
#include <iostream>
#include <vector>

namespace gecs {

    // Initialize static members
    XMLSettingsParser XMLSettingsParser::instance;
    std::mutex XMLSettingsParser::mtx;

    XMLSettingsParser::XMLSettingsParser() {}

    XMLSettingsParser& XMLSettingsParser::getInstance() {
        return instance;
    }

    bool XMLSettingsParser::loadSettings(const std::string& filename) {
        std::lock_guard<std::mutex> lock(mtx);
        tinyxml2::XMLError eResult = doc.LoadFile(filename.c_str()); // Convert std::string to const char*
        if (eResult != tinyxml2::XML_SUCCESS) {
            std::cerr << "Error loading XML file: " << filename << std::endl;
            return false;
        }
        return true;
    }

    std::string XMLSettingsParser::getSetting(const std::string& path) {
        std::lock_guard<std::mutex> lock(mtx);

        tinyxml2::XMLElement* element = doc.RootElement();
        if (!element) {
            std::cerr << "Root element not found." << std::endl;
            return "";
        }

        // Split path by '.' to navigate through XML structure
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = path.find('.');
        while (end != std::string::npos) {
            tokens.push_back(path.substr(start, end - start));
            start = end + 1;
            end = path.find('.', start);
        }
        tokens.push_back(path.substr(start));

        // Navigate through the XML structure using tokens
        for (const auto& token : tokens) {
            element = element->FirstChildElement(token.c_str());
            if (!element) {
                std::cerr << "Element '" << token << "' not found for path: " << path << std::endl;
                return "";
            }
             std::cout << "Navigating to node: " << token << std::endl;
        }

        // Get text content of the final element
        const char* text = element->GetText();
        if (!text) {
            std::cerr << "Text not found for element: " << path << std::endl;
            return "";
        }

        std::cout << "Found text for element '" << path << "': " << text << std::endl;
        return text;
    }

} // namespace gecs