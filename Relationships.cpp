// Relationships.cpp
#include "Relationships.h"
#include "Rule.h"
#include "Utils.h"
#include <vector>

namespace {
    int rotation = 0;

    const std::vector<Rule> rules = {
        { std::regex(R"(\bi love (.*)$)", std::regex::icase),
          { "What is it about %R% that you love?", "How long have you felt this way about %R%?" } },

        { std::regex(R"(\bmy (girlfriend|boyfriend|partner) (.*)$)", std::regex::icase),
          { "Tell me more about your relationship -- what's going on with %R%?" } },

        { std::regex(R"(\bmy (spouse|wife|husband) (.*)$)", std::regex::icase),
          { "How are things between you and your %R%?" } },

        { std::regex(R"(\b(marriage|married|engaged) (.*)$)", std::regex::icase),
          { "What are your thoughts about %R%?", "How do you feel about %R%?" } },

        { std::regex(R"(\bwe (broke up|are breaking up|split up)\b)", std::regex::icase),
          { "Breakups are hard. How are you handling it?", "What led to the two of you breaking up?" } },

        { std::regex(R"(\bi (miss|am missing) (.*)$)", std::regex::icase),
          { "What do you miss most about %R%?" } },

        { std::regex(R"(\b(dating|crush on) (.*)$)", std::regex::icase),
          { "What's it like getting to know %R%?" } },

        { std::regex(R"(\bi (trust|don't trust|distrust) (.*)$)", std::regex::icase),
          { "What has shaped how much you trust %R%?" } },
    };
}

bool matchRelationships(const std::string& input, std::string& outResponse) {
    return Utils::tryRules(rules, input, outResponse, rotation);
}
