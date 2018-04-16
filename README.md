# Quadris

#### By Jonathan Donas and Ryan Quanz.

Made for CS246, Fall 2016. University of Waterloo.

<kbd><img src="http://i.imgur.com/ejliJEK.png" width="400"></kbd>

As a bonus feature, we also built an AI that played the game (usually) better than we could. In testing, the AI would play up to 7000 successful moves on the hardest level before losing.

<kbd><img src="http://i.imgur.com/xZ0rk1h.gif" width="400"></kbd>

Here is the usage:

```
  Options:
    -text                    Run in text-only mode
    -seed [seed]             Set the random number generator's seed
    -scriptfile [file]       Use [file] instead of the default sequence.txt
    -startlevel [n]          Start game in level [n]
    -h  or  --help           Display this help message
    -hold                    Play with the hold feature (bonus!)
    -ai                      Enable AI feature
  
  In-game commands:
    left
    right
    down
    clockwise
    counterclockwise
    drop
    levelup
    leveldown
    restart
    norandom                 Make levels 3 and 4 read from input file
    random                   Make levels 3 and 4 random (default)
    sequence [file]          Change sequence file
    I, J, L, etc.            Replace current block with specified block
    hold                     Holds the current block for later use
    hint                     Display a hint
    auto                     Makes the best move for you
  
  Commands can be shortened (eg. counterclockwise -> co)
  and executed multiple times (eg. 2left)
```
