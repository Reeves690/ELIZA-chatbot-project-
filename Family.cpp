// Family.cpp
#include "Family.h"
#include "Rule.h"
#include "Utils.h"
#include <vector>

namespace {
    int rotation = 0;

    const std::vector<Rule> rules = {
        { std::regex(R"(\bmy (mother|mom) (.*)$)", std::regex::icase),
          { "Tell me more about your mother.", "How does that make you feel about her?" } },

        { std::regex(R"(\bmy (father|dad) (.*)$)", std::regex::icase),
          { "Tell me more about your father.", "How does that make you feel about him?" } },

        { std::regex(R"(\bmy (sister|brother|sibling)\b.*$)", std::regex::icase),
          { "What's your relationship with your %R% like?" } },

        { std::regex(R"(\bmy parents (.*)$)", std::regex::icase),
          { "How do your parents feel about that?" } },

        { std::regex(R"(\bmy (kids|children|son|daughter)\b.*$)", std::regex::icase),
          { "Tell me more about your %R%." } },

        { std::regex(R"(\bmy family (.*)$)", std::regex::icase),
          { "What's your family like?" } },

        { std::regex(R"(\bmy (aunt|uncle|cousin|grandmother|grandfather|grandma|grandpa) (.*)$)", std::regex::icase),
          { "How close are you with them?" } },

        { std::regex(R"(\bgrew up (.*)$)", std::regex::icase),
          { "What was that like, growing up?" } },
    };
}

bool matchFamily(const std::string& input, std::string& outResponse) {
    return Utils::tryRules(rules, input, outResponse, rotation);
}