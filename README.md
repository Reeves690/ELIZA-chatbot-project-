ELIZA SIMULATION - FINAL PROJECT SUBMISSION
=============================================

Reeves Holliday

PROJECT OVERVIEW
-----------------
This program is a C++ reimplementation of ELIZA, the early natural
language chatbot that simulates a psychiatrist conducting an initial
interview. The user types natural-language sentences; the program uses
std::regex (regex_match, regex_search, and regex_replace) to detect
patterns in the input and generate a conversational reply.

The program is organized into one "major functionality component" per
required topic area, each in its own header/source file pair:

  Component          Files                      Keywords
  ------------------  -------------------------  ------------------------
  Concern             Concern.h / Concern.cpp     hate, kill, suicide, ...
  Generic verbs        GenericVerbs.h / .cpp       have, buy, travel, know
  Relationships        Relationships.h / .cpp      love, spouse, girlfriend
  Financial            Financial.h / .cpp          money, savings, debt
  Wellbeing            Wellbeing.h / .cpp          exercise, sleep, relax
  Education            Education.h / .cpp          university, studying
  Entertainment         Entertainment.h / .cpp     movie, concert, dancing
  Family (group's      Family.h / .cpp            mother, father, siblings
   "Others" component)

Supporting infrastructure:
  Eliza.h / Eliza.cpp             - core dispatcher, greeting/exit
                                     detection, repeated-input handling
  ResponseTracker.h / .cpp        - records every normalized user input
                                     and reports when one repeats
  Utils.h / Utils.cpp             - trimming, lowercasing, the shared
                                     regex-rule matcher (tryRules), and
                                     pronoun reflection ("I" -> "you", etc.)
  Rule.h                          - shared struct pairing a regex with a
                                     list of response templates
  main.cpp                        - contains ONLY int main() and the
                                     top-level read/respond loop

There are 65 distinct regular expressions spread across the eight
components.

Every user turn is first checked against the Concern component
,then against each topic component in
turn, and finally against a small set of generic ELIZA-style fallback
prompts ("Please tell me more about that.", "Why do you say that?",
etc.) if nothing else matched.

Repeated-input handling: every normalized (trimmed, lowercased) line the
user types is recorded. If the exact same line is typed again later in
the conversation, the program prepends a short nudge ("You've told me
something very similar before -- I'd like to hear something new.") to
its normal reply, motivating the user to say something different.

The conversation ends when the user types "bye" (checked with
regex_match against the whole line, so "bye", "Bye!", "bye." all work).


HOW TO COMPILE
---------------
Requires a C++17-capable compiler (developed and tested with g++ 13 on
the CSE Linux machines).

Option A - using the provided Makefile:
    make

Option B - manual compilation:
    g++ -std=c++17 -Wall -Wextra -O2 -o eliza main.cpp Eliza.cpp Utils.cpp \
        ResponseTracker.cpp Concern.cpp GenericVerbs.cpp Relationships.cpp \
        Financial.cpp Wellbeing.cpp Education.cpp Entertainment.cpp Family.cpp

No special compiler flags beyond -std=c++17 are required.

To remove compiled object files and the executable:
    make clean


HOW TO RUN
-----------
    ./eliza

The program will print a greeting and then a "> " prompt. Type natural
sentences and press Enter after each one. Type "bye" at any time to end
the session.




