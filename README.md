# ELIZA-chatbot-project-
ELIZA SIMULATION - MILESTONE SUBMISSION
=========================================

GROUP MEMBERS
-------------
Reeves Holliday

MILESTONE SCOPE
-----------------
Per the assignment, this milestone submission includes:

  1. Full working functionality for major functionality component 1
     (Generic Verbs -- keywords like have, purchase, travel, know,
     learn, want, need, think, feel, believe), implemented with 10
     distinct regular expressions in GenericVerbs.h / GenericVerbs.cpp.

  2. Repeated-response tracking: every normalized (trimmed, lowercased)
     line the user types is recorded by ResponseTracker. If the same
     line is typed again later in the conversation, the program
     prepends a short nudge ("You've told me something very similar
     before -- I'd like to hear something new.") to its normal reply,
     motivating the user to give a different response.



FILES INCLUDED
---------------
  main.cpp                     - contains ONLY int main() and the
                                  top-level read/respond loop
  Eliza.h / Eliza.cpp          - core dispatcher, greeting/exit
                                  detection, repeated-input handling
                                  (milestone scope: dispatches to
                                  Generic Verbs only, then fallback)
  ResponseTracker.h / .cpp     - records every normalized user input
                                  and reports when one repeats
  Utils.h / Utils.cpp          - trimming, lowercasing, the shared
                                  regex-rule matcher (tryRules), and
                                  pronoun reflection ("I" -> "you")
  Rule.h                       - shared struct pairing a regex with a
                                  list of response templates
  GenericVerbs.h / .cpp        - major functionality component 1
  Makefile                     - builds only the files listed above


HOW TO COMPILE
---------------
Option A - using the provided Makefile:
    make

Option B - manual compilation:
    g++ -std=c++17 -Wall -Wextra -O2 -o eliza main.cpp Eliza.cpp \
        Utils.cpp ResponseTracker.cpp GenericVerbs.cpp

To remove compiled object files and the executable:
    make clean


HOW TO RUN
-----------
    ./eliza

The program prints a greeting and then a "> " prompt. Type natural
sentences and press Enter after each one. Type "bye" at any time to end
the session.

