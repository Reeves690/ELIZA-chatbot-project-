// ResponseTracker.cpp
#include "ResponseTracker.h"

int ResponseTracker::recordAndCount(const std::string& normalizedInput) {
    orderedHistory_.push_back(normalizedInput);
    auto it = counts_.find(normalizedInput);
    if (it == counts_.end()) {
        counts_[normalizedInput] = 1;
        return 1;
    }
    it->second += 1;
    return it->second;
}

bool ResponseTracker::isRepeat(const std::string& normalizedInput) const {
    auto it = counts_.find(normalizedInput);
    return it != counts_.end() && it->second > 0;
}

size_t ResponseTracker::distinctInputCount() const {
    return counts_.size();
}

const std::vector<std::string>& ResponseTracker::history() const {
    return orderedHistory_;
}
