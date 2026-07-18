// Utils.cpp
#include "Utils.h"
#include <sstream>
#include <cctype>
#include <regex>
#include <unordered_map>
#include <vector>

namespace Utils {

    std::string trim(const std::string& s) {
        size_t start = s.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) return "";
        size_t end = s.find_last_not_of(" \t\n\r");
        return s.substr(start, end - start + 1);
    }

    std::string toLower(const std::string& s) {
        std::string result = s;
        for (char& c : result) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        return result;
    }

    std::string normalizeWhitespace(const std::string& s) {
        std::istringstream iss(s);
        std::ostringstream oss;
        std::string word;
        bool first = true;
        while (iss >> word) {
            if (!first) oss << " ";
            oss << word;
            first = false;
        }
        return oss.str();
    }

    bool tryRules(const std::vector<Rule>& rules,
                  const std::string& input,
                  std::string& outResponse,
                  int& rotationCounter) {
        for (const auto& rule : rules) {
            std::smatch match;
            if (std::regex_search(input, match, rule.pattern)) {
                // Pick a response template, rotating through the list so
                // repeated matches of the same rule don't feel robotic.
                const std::string& templateStr =
                    rule.responses[rotationCounter % rule.responses.size()];
                rotationCounter++;

                if (templateStr.find("%R%") != std::string::npos && match.size() > 1) {
                    // Use the LAST capture group rather than the first: for
                    // rules like "i (watched|am watching) (.*)$" the first
                    // group is just the matched verb alternative, while the
                    // final group holds the actual content to reflect back.
                    std::string reflected = reflect(normalizeWhitespace(match[match.size() - 1].str()));
                    outResponse = std::regex_replace(templateStr, std::regex("%R%"), reflected);
                } else {
                    // No placeholder to fill, or the pattern had no capture
                    // group -- just strip a stray %R% if present.
                    outResponse = std::regex_replace(templateStr, std::regex("%R%"), "that");
                }
                return true;
            }
        }
        return false;
    }

    // Pronoun/verb swap implemented with std::regex_replace. Each entry in
    // the ordered table is applied in turn using a word-boundary regex
    // (\b...\b, case-insensitive) so that "I" inside "I'm" or "chief" does
    // not get corrupted. Placeholder tokens (\x01, \x02, ...) are used for
    // the first pass so that, e.g., "I" -> "you" -> (later rule) "I" can't
    // cascade back and forth.
    std::string reflect(const std::string& s) {
        // Ordered so longer/contraction forms are handled before their
        // shorter component words.
        static const std::vector<std::pair<std::string, std::string>> table = {
            {"i'm", "\x01"}, {"i've", "\x02"}, {"i'll", "\x03"}, {"i'd", "\x04"},
            {"myself", "\x05"}, {"yourself", "\x06"},
            {"mine", "\x07"}, {"yours", "\x08"},
            {"my", "\x09"}, {"your", "\x0A"},
            {"me", "\x0B"}, {"i", "\x0C"}, {"you", "\x0D"},
            {"am", "\x0E"}, {"was", "\x0F"}, {"were", "\x10"}
        };
        static const std::unordered_map<std::string, std::string> resolve = {
            {"\x01", "you are"}, {"\x02", "you have"}, {"\x03", "you will"}, {"\x04", "you would"},
            {"\x05", "yourself"}, {"\x06", "myself"},
            {"\x07", "yours"}, {"\x08", "mine"},
            {"\x09", "your"}, {"\x0A", "my"},
            {"\x0B", "you"}, {"\x0C", "you"}, {"\x0D", "I"},
            {"\x0E", "are"}, {"\x0F", "were"}, {"\x10", "was"}
        };

        std::string result = s;
        for (const auto& entry : table) {
            std::regex wordPattern("\\b" + entry.first + "\\b", std::regex::icase);
            result = std::regex_replace(result, wordPattern, entry.second);
        }
        for (const auto& entry : resolve) {
            std::string placeholder(1, entry.first[0]);
            size_t pos;
            while ((pos = result.find(placeholder)) != std::string::npos) {
                result.replace(pos, 1, entry.second);
            }
        }
        return result;
    }
}
