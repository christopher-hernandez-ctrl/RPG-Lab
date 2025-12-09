# ECE 312 - Lab 6 Write-Up

**Name:** ___________________________  
**EID:** ___________________________  
**Date:** ___________________________

---

## 1. Design Decisions (3-4 sentences)

Briefly describe your key design choices and rationale:

- **Overall implementations:** How did you make use of object-oriented concepts in your decision?  Specifically, how did you use inheritance and polymorphism (if you did) and how did it help or complicate the design over using a language like C?  Draw a diagram showing the classes you used and their relationships to each other (subclass to superclass relationships specifically.) 

The entire design of the lab heavily relied on object-oriented programming. Inheritance was used to make subclasses of players and monsters. The monster subclass was then made into even more subclasses of different types of monsters. I was able to use all the similar functions between the characters while still having the ability to override some with polymorphism. For instance, calculateDamage() and getAttackMessage() both used polymorphism to make the output of these functions specific to the character at run-time. Overall, this made creating the game a lot easier because I could use everything from the classes I already created instead of writing more functions doing the same thing for a different character type.


                Character
                /       \
            Player      Monster
                        /   |       \     \      \      \  
                    Goblin Skeleton Troll Wizard Dragon Ghost
- **Memory management:** What strategy did you use to avoid leaks? Any particular challenges?
To ensure there were no leaks, I made sure to test my code incrementally. Additionally, I made sure to be mindful of where new was used, to make sure there was a matching delete somewhere else. The main challenge was keeping track of not attempting to double delete. 

---


## 2. Testing & Debugging (2-3 sentences)

Describe your testing process and any major bugs you encountered:

- **Testing approach:** What was your strategy beyond running `make test`?
My testing strategy was to test my code incrementally. I made sure to stop and run test cases to test specifically what I had just written. I made sure to test for edge cases and not move on until there were no cracks in my code.


- **Most difficult bug:** What was the hardest bug to find/fix and how did you solve it?
The hardest bug to find was when my monsters were not dropping loot. I almost did not even notice it at first because my game still ran perfectly fine without it. However, when I was playing the game, I remembered that there should be loot dropped by the monsters after defeating them. I assumed the issue was in my monster files, so I spent some time going through them trying to find the issue. I eventually realized the issue was in my game initialiation logic. I was instantiating the monsters using the monster class instead of its subclasses.


---

## 3. Implementation Challenges (2-3 sentences)

Which TODOs were most challenging and why?

1. **Hardest TODO:** 
The combat system was the most challenging TODO because it had so many moving parts. I kept getting the monster and player classes confused. Additionally, I had to account for all the unique behaviors implemented in the different monster subclasses.

2. **Most time-consuming:** 
The most time-consuming TODO was the world initialization. This is actually were my hardest bug was, but this was not my only issue. I spent an embarrasing amount of time connecting the rooms properly. Although I could have added debug print statements, I took the long route of checking my world map was right by playing through the game.

3. **Most interesting:** 
The most interesting TODO was making all of the monster subclasses. It really showed me the power of polymorphism. Additionally, I was better able to understand virtual functions.

---


## 4. Reflection (1-2 sentences)

What was the most valuable lesson from this lab?
The most valuable lesson from this lab was gaining a better overall understand of object-oriented programming. Although it was difficult adjusting to at first, I eventually realized how powerful it is when trying to simplify a big project like this.


---

## Submission Checklist

- [ ] All functionality completed
- [ ] `make test` passes with no failures
- [ ] `make valgrind` shows no memory leaks
- [ ] Game fully functional 
- [ ] Code compiles without warnings (`-Wall -Wextra`)
- [ ] This write-up completed
- [ ] Optional Bonus attempted? (Yes/No): __Yes___(Extension 2: More monster types)
