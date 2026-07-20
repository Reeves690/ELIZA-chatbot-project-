/// Eliza.cpp
#include "Eliza.h"
#include "Utils.h"

#include "Concern.h"
#include "GenericVerbs.h"
#include "Relationships.h"
#include "Financial.h"
#include "Wellbeing.h"
#include "Education.h"
#include "Entertainment.h"
#include "Family.h"

#include <regex>
#include <vector>
#include <string>

Eliza::Eliza() : fallbackRotation_(0) {}

std::string Eliza::greeting() const {
    return "Hello, I'm here to listen. What's on your mind today? "
           "(type 'bye' any time to end our session)";
}

std::string Eliza::farewell() const {
    return "Thank you for talking with me today. Take care of yourself. Goodbye.";
}

bool Eliza::isExitCommand(const std::string& rawInput) const {
    std::string normalized = Utils::toLower(Utils::trim(rawInput));
    // regex_match requires the WHOLE string to match, so "bye", "bye!",
    // "Bye." all end the session, but "bye for now, see you at the party"
    // does not (it gets treated as ordinary conversation instead).
    static const std::regex exitPattern(R"(bye[\.\!]*)", std::regex::icase);
    return std::regex_match(normalized, exitPattern);
}

std::string Eliza::fallbackResponse() {
    static const std::vector<std::string> fallbacks = {
        "Please tell me more about that.",
        "Why do you say that?",
        "I see. Can you elaborate on that?",
        "Go on, I'm listening.",
        "How does that make you feel?",
        "That's interesting -- what makes you bring that up right now?"
    };
    const std::string& response = fallbacks[fallbackRotation_ % fallbacks.size()];
    fallbackRotation_++;
    return response;
}

std::string Eliza::dispatch(const std::string& input) {
    std::string response;

    // Concern is checked first on every turn: language suggesting distress
    // or hostility should never be missed just because some other rule
    // (e.g. a generic verb pattern) happened to match earlier in the text.
    if (matchConcern(input, response))        return response;
    if (matchRelationships(input, response))  return response;
    if (matchFamily(input, response))         return response;
    if (matchFinancial(input, response))      return response;
    if (matchWellbeing(input, response))      return response;
    if (matchEducation(input, response))      return response;
    if (matchEntertainment(input, response))  return response;
    if (matchGenericVerbs(input, response))   return response;

    return fallbackResponse();
}

std::string Eliza::respond(const std::string& rawInput) {
    std::string trimmed = Utils::trim(rawInput);

    if (trimmed.empty()) {
        return "I didn't quite catch that -- could you say something?";
    }

    // Exact-phrase greeting check using regex_match (whole-string match).
    static const std::regex greetingPattern(R"((hi|hello|hey)[\.\!,]*)", std::regex::icase);
    if (std::regex_match(Utils::toLower(trimmed), greetingPattern)) {
        return "Hello again. How are you feeling today?";
    }

    std::string normalized = Utils::toLower(trimmed);
    bool repeated = tracker_.isRepeat(normalized);
    tracker_.recordAndCount(normalized);

    std::string reply = dispatch(trimmed);

    if (repeated) {
        // Motivate the user toward a different answer instead of just
        // silently repeating whatever canned response matched again.
        return "You've told me something very similar before -- I'd like to hear "
               "something new. " + reply;
    }
    return reply;
}
