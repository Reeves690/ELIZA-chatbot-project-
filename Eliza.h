// Eliza.h
// The core conversation engine. Owns the ResponseTracker and is
// responsible for: normalizing each line of user input, detecting exact
// greeting/farewell phrases (via std::regex_match), checking for a
// repeated response, dispatching to each major functionality component
// in priority order (via each component's regex_search-based matcher),
// and falling back to a generic ELIZA-style prompt when nothing matches.
#ifndef ELIZA_H
#define ELIZA_H

#include <string>
#include "ResponseTracker.h"

class Eliza {
public:
    Eliza();

    // The opening line printed once at program start.
    std::string greeting() const;

    // True if the (raw, un-normalized) user input should end the session.
    // Uses std::regex_match against the whole line so that e.g. "bye"
    // or "bye." ends the session but "goodbye party" does not.
    bool isExitCommand(const std::string& rawInput) const;

    // Produces the system's reply to a single line of user input.
    std::string respond(const std::string& rawInput);

    // The closing line printed once the session ends.
    std::string farewell() const;

private:
    ResponseTracker tracker_;
    int fallbackRotation_;

    std::string dispatch(const std::string& input);
    std::string fallbackResponse();
};

#endif // ELIZA_H
