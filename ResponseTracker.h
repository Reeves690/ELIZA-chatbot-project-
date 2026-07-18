// ResponseTracker.h
// Keeps a history of everything the user has typed so the system can
// detect when the user gives the same (or a near-identical) response
// more than once, and nudge them toward a different answer instead of
// just repeating the same canned reply.
#ifndef RESPONSE_TRACKER_H
#define RESPONSE_TRACKER_H

#include <string>
#include <unordered_map>
#include <vector>

class ResponseTracker {
public:
    ResponseTracker() = default;

    // Records a (normalized) user input and returns how many times,
    // including this one, that exact input has now been seen.
    int recordAndCount(const std::string& normalizedInput);

    // True if normalizedInput has been seen at least once before
    // (i.e., this is a repeat).
    bool isRepeat(const std::string& normalizedInput) const;

    // Total number of distinct inputs recorded so far.
    size_t distinctInputCount() const;

    // Full ordered history of everything the user has typed (normalized).
    const std::vector<std::string>& history() const;

private:
    std::unordered_map<std::string, int> counts_;
    std::vector<std::string> orderedHistory_;
};

#endif // RESPONSE_TRACKER_H
