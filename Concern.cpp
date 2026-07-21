// Concern.cpp
#include "Concern.h"
#include "Rule.h"
#include "Utils.h"
#include <vector>

namespace {
    int rotation = 0;

    const std::vector<Rule> rules = {
        // Suicide / self-harm -- highest priority, checked first.
        { std::regex(R"(\b(suicide|kill myself|end my life|hurt myself|self[- ]harm)\b)", std::regex::icase),
          { "I'm concerned about what you just said. You matter, and it might help to talk to someone right now -- in the US you can call or text 988 (Suicide & Crisis Lifeline). Can you tell me more about what's going on?",
            "That sounds really heavy to carry. Please consider reaching out to a crisis line (988 in the US) or someone you trust. What has been happening?" } },

        { std::regex(R"(\b(hopeless|worthless|no reason to live|can't go on)\b)", std::regex::icase),
          { "It sounds like things feel very heavy right now. You don't have to go through that alone -- would you be willing to talk to a counselor or someone you trust?",
            "That's a hard thing to feel. What's been making things feel %R%?" } },

        { std::regex(R"(\bi (hate|despise) (.*)$)", std::regex::icase),
          { "Hate is a strong word. What is it about %R% that brings up that feeling?",
            "It sounds like %R% really frustrates you. Can you say more?" } },

        { std::regex(R"(\b(kill|hurt|attack) (him|her|them|someone|somebody)\b)", std::regex::icase),
          { "That's a serious thing to say. What's making you feel that angry?",
            "I want to understand -- what happened that made you feel this way toward %R%?" } },

        { std::regex(R"(\bi(?:'m| am) (?:scared|afraid|terrified) of (.*)$)", std::regex::icase),
          { "Fear can be really consuming. What is it about %R% that scares you most?" } },

        { std::regex(R"(\b(angry|furious|enraged) (at|with) (.*)$)", std::regex::icase),
          { "It sounds like %R% has really gotten under your skin. What happened?" } },

        { std::regex(R"(\bi feel (like a failure|worthless|useless)\b)", std::regex::icase),
          { "That's a painful way to feel about yourself. What's been contributing to that feeling lately?" } },
    };
}

bool matchConcern(const std::string& input, std::string& outResponse) {
    return Utils::tryRules(rules, input, outResponse, rotation);
}
