// Education.cpp
#include "Education.h"
#include "Rule.h"
#include "Utils.h"
#include <vector>

namespace {
    int rotation = 0;

    const std::vector<Rule> rules = {
        { std::regex(R"(\bi(?:'m| am) (?:taking|enrolled in) (?:a course|a class) (.*)$)", std::regex::icase),
          { "What made you choose that course?" } },

        { std::regex(R"(\buniversity (.*)$)", std::regex::icase),
          { "What's your experience with university been like?" } },

        { std::regex(R"(\bi(?:'m| am) (?:studying|study) (.*)$)", std::regex::icase),
          { "What drew you to studying %R%?", "How is studying %R% going for you?" } },

        { std::regex(R"(\bi(?:'m| am) a student\b)", std::regex::icase),
          { "What are you studying?", "How do you like being a student?" } },

        { std::regex(R"(\beducation (.*)$)", std::regex::icase),
          { "What are your thoughts on %R%?" } },

        { std::regex(R"(\bi (failed|passed) (my|an|the) (exam|test|class|course)\b)", std::regex::icase),
          { "How did that make you feel?" } },

        { std::regex(R"(\bhomework (.*)$)", std::regex::icase),
          { "How do you feel about %R%?" } },

        { std::regex(R"(\bmy (teacher|professor|instructor)\b.*$)", std::regex::icase),
          { "Tell me more about your %R%." } },
    };
}

bool matchEducation(const std::string& input, std::string& outResponse) {
    return Utils::tryRules(rules, input, outResponse, rotation);
}