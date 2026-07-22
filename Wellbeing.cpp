// Wellbeing.cpp
#include "Wellbeing.h"
#include "Rule.h"
#include "Utils.h"
#include <vector>

namespace {
    int rotation = 0;

    const std::vector<Rule> rules = {
        { std::regex(R"(\bi (exercise|work out|workout) (.*)$)", std::regex::icase),
          { "How does exercising make you feel?", "What got you into %R%?" } },

        { std::regex(R"(\bvitamins? (.*)$)", std::regex::icase),
          { "What made you start thinking about %R%?" } },

        { std::regex(R"(\bi (relax|am relaxing|need to relax) (.*)$)", std::regex::icase),
          { "What helps you relax?", "What's making it hard to relax lately?" } },

        { std::regex(R"(\bi (can't sleep|cannot sleep|am not sleeping)\b)", std::regex::icase),
          { "Trouble sleeping can really wear on you. What's been keeping you up?" } },

        { std::regex(R"(\bi (sleep|slept) (.*)$)", std::regex::icase),
          { "How has your sleep been lately?" } },

        { std::regex(R"(\bi(?:'m| am) (?:tired|exhausted|drained)\b)", std::regex::icase),
          { "What's been wearing you out?" } },

        { std::regex(R"(\bi(?:'m| am) (?:stressed|stressed out|overwhelmed)\b)", std::regex::icase),
          { "What's contributing to that stress?" } },

        { std::regex(R"(\bhealthy (.*)$)", std::regex::icase),
          { "What does being healthy mean to you?" } },
    };
}

bool matchWellbeing(const std::string& input, std::string& outResponse) {
    return Utils::tryRules(rules, input, outResponse, rotation);
}
