// GenericVerbs.cpp
#include "GenericVerbs.h"
#include "Rule.h"
#include "Utils.h"
#include <vector>

namespace {
    int rotation = 0;

    const std::vector<Rule> rules = {
        { std::regex(R"(\bi have (.*)$)", std::regex::icase),
          { "How long have you had %R%?", "What does having %R% mean to you?" } },

        { std::regex(R"(\bi (purchase|purchased|bought|buy) (.*)$)", std::regex::icase),
          { "What made you decide to buy %R%?", "How do you feel about %R% now that you have it?" } },

        { std::regex(R"(\bi (travel|traveled|went|am going) to (.*)$)", std::regex::icase),
          { "What took you to %R%?", "Tell me more about your trip to %R%." } },

        { std::regex(R"(\bi know (.*)$)", std::regex::icase),
          { "How did you come to know %R%?", "What makes you so sure about %R%?" } },

        { std::regex(R"(\bi (learn|learned|am learning) (.*)$)", std::regex::icase),
          { "What got you interested in learning %R%?", "How is learning %R% going for you?" } },

        { std::regex(R"(\bi want (.*)$)", std::regex::icase),
          { "Why do you want %R%?", "What would it mean for you to get %R%?" } },

        { std::regex(R"(\bi need (.*)$)", std::regex::icase),
          { "What makes you feel you need %R%?", "What happens if you don't get %R%?" } },

        { std::regex(R"(\bi think (.*)$)", std::regex::icase),
          { "What makes you think %R%?", "How long have you thought %R%?" } },

        { std::regex(R"(\bi feel (.*)$)", std::regex::icase),
          { "Why do you feel %R%?", "How often do you feel %R%?" } },

        { std::regex(R"(\bi believe (.*)$)", std::regex::icase),
          { "What led you to believe %R%?", "Is that belief something you've always held?" } },
    };
}

bool matchGenericVerbs(const std::string& input, std::string& outResponse) {
    return Utils::tryRules(rules, input, outResponse, rotation);
}
