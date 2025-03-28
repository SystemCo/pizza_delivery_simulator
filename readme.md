# Welcome to the Pizza Delivery Simulator!
## Overview:
Have you ever wanted to work minimum wage delivering pizzas? 
Of course not, but now you can!
* Avoid pedestrians and other vehicles on the road! 
* Fight against the clock! Pay your victims’ horrific medical bills! 
* In Pizza Delivery Simulator!

## Technical Requirements:
* Programming in C++
* Graphics package with OpenGL
* Inputs
    * Keyboard
        * \<Left\_Arrow\> - \<Right\_Arrow\> -> Turning
        * \<Up\_Arrow\> - \<Down\_Arrow\> -> Accelerate / Decelerate + Forward / Reverse
        * Esc -> Pause Menu
    *   Mouse
        * Navigate title screen
        * Initiate and close deliveries
        * Daily options selections

## Build requirements:
* Currently only supports linux
* c++11 compatible compiler
* libX11
* libGL
* libGLU

## Build:
* run make
* run ./pizza\_deliv

## Schedules:
### Avelina
My schedule is subject to change based on my work schedule + work meetings. 
* Monday
    * Available 1pm-7pm. Will notify if not. 
* Tuesday
    * Typically available any time after 10am. Will notify if not.
* Wednesday
    * Available all day after 1pm. Will notify if not.
* Thursday
    * Available 10am-6pm. Will notify if not.
* Friday
    * Typically not available on Fridays
* Weekends
    * Typically available all weekend. Will notify if not.

### David
* Sunday
    * Typically free all day after 2:00. Will notify if not.
* Monday - Tuesday
    * Available: 10:00 - 11:00, 5:00 - 9:00
* Wednesday
    * Available: 10:00 - 11:00, 5:00 - 6:30
* Thursday
    * Available: 5:00 - 9:00
* Friday
    * Schedule is weird. I'm very available, but at inconsistent times.
        * Make appointment.
* Saturday
    * Available: Typically all day.
        * Appointment helps

### Fenoon
Monday- Wednesday 
Available: 10:00-11:00, 12:00-1:00, 4:00-5:30
Friday: 
Available: 10:00-11:00, 2:00-5:30 

### Francisco
My schedule is usually subject to change depending on my work schedule
* Monday
    * 5:00 PM - 9:00 PM
* Tuesday
    * 7:00 PM - 10:00 PM (availability varies bi-weekly)
* Wednesday
    * 12:30 PM - 3:45 PM, 6:30 PM - 10:00 PM
* Thursday
    * 11:30 AM - 5:15 PM, 7:00 PM - 10:00 PM
* Friday
    * 10:00 AM (varies to 10:30 AM bi-weekly) - 3:45 PM, 6:30 PM - 11:00 PM
* Saturday
    * 3:00 PM - 12:00 AM
* Sunday
    * 11:00 AM - 7:00 PM

### Lesslie
* Monday
    * 12:00 PM - 7:00 PM
* Wednesday
    * 12:00 PM - 7:00 PM
* Thursday
    * 10:30 AM - 12:30 PM, 4:00 PM - 7:00 PM
* Friday
    * 11:00 AM - 7:00 PM
* Saturday
    * 11:00 AM - 4:00 PM
## TODO:

### Avelina
* Make sure title button only displays when in the title screen
    * Assigned on: Wednesday 03/12/25
    * Assigned by: David
    * Due by:      Wednesday 03/19/25
    * Status:      Incomplete

* Add start menu screen
    * Only needs a single button which will start gameplay
    * Uses a unique background
    * Assigned by: David
    * Assigned on: Wednesday 03/12/25
    * Due by:      Wednesday 03/12/25
    * Status:      Incomplete

### David
* Implement path following method using an array of points
    * Assigned on: Monday 03/10/25
    * Assigned by: David
    * Due by:      Monday 03/17/25
    * Status:      Complete 

* Implement sprite sheets using the frameworks 
    * Assigned on: Monday 03/10/25
    * Assigned by: David
    * Due by:      Monday 03/17/25
    * Status:      Complete

* Force application into fullscreen
    * Assigned on: Friday 03/10/25
    * Assigned by: David
    * Due by:      Monday 03/17/25
    * Status:      Complete 

### Fenoon
* Add pause functionality when <esc> keyboaord key is pressed
    * Assigned on: Monday 03/03/25
    * Assigned by: David
    * Due by:      Monday 03/10/25
    * Status:      Incomplete

* Add clickable button that will return to play while in pause menu
    * Assigned on: Wednesday 03/12/25
    * Assigned by: David
    * Due by:      Wednesday 03/19/25
    * Status:      Incomplete
    * Note:        Talk to Lina for help!

### Francisco
* Extract audio files for intro
    * Assigned on: Sunday 03/02/25
    * Assigned by: Francisco
    * Due by:      Monday 03/11/25
    * Status:      Complete

* Make sure that only the title background displays during the title
    And only the map background displays during the playing state
    * Talk to Fen if you need help!
    * Assigned on: Wednesday 03/12/25
    * Assigned by: David
    * Due by:      Wednesday 03/19/25
    * Status:      Complete

* Make buttons dim when and only when mouse is hovering over them.
    * Assigned on: Thursday 03/13/25
    * Assigned by: Francisco
    * Due by:      Thursday 03/20/25
    * Status:      Complete

### Lesslie
* Get started on timer system
    * Assigned on: Monday 03/10/25
    * Assigned by: Lesslie
    * Due by:      Monday 03/17/25
    * Status:      Incomplete

* Make a timer sprite that will visually indicate how much time an order has left
    * Assigned on: Wednesday 03/12/25
    * Assigned by: David
    * Due by:      Wednesday 03/19/25
    * Status:      Incomplete

## Project Phases
### Basic UI / UX
* Animated intro
    -> Timeout, Click, any button push
* Home Menu
    * Looks like pizza order menu
* Tutorial
* Controls
* Options (i.e. sound)
* Game Play
    -> Push the play game button from Home Menu
* Pause Menu
    -> Push esc while playing
* Exit Game
    -> Quit button, from home, from pause, alt+<F4>

### Animated Intro
* If intro is not complex enough, then not valid
    * Spinning world is not enough
    * Just Animated text is not enough
* Add scrolling backdrop, weelie, pizza boxes, etc. 

### Map features
* How to handle collisions with each element of the map
* Need to make an AABB collision function
* Need to have logic for what to do with each type of element
* Types
    * street lamp, building, water, sidewalk, etc

### Extra animation features
* Pizza guy dismounting to pick up the pizza
* Hit pedestrians explode!
* Add vehicle damage
    * Traffic
    * Player Motorcycle

### Add more traffic
* Add traffic pathing logic
* random?
    * Both
    * Different vehicle types have different levels of predictability
* Add pedestrians

### Extra game elements
* Money mechanics
* Things that cost money
    * Not delivering pizza on time
    * Accidents/crashes
    * Hitting pedestrians
    * Rent and water bills
        * random
* If you don't complete all deliveris, you're fired, game over
* Too many late deliveries and you're fired
    * shown by a "performance" meter?
    * Deliveries that are more late hurt your performance more;
    * Performance slowly fills back up.

## Ideas
### Title screen 
* Add text to the title screen
    * Animate the text.
* Make the motorcycle larger and realistically drive forward,
    Popping a weelie
* Add pizza to the motorcycle
    * Have the pizza fall off as part of the animation
* Add a menu to the title screen that can be clicked on
    * Have the buttons change color when hovered over
### Gameplay
* Add a goal to get from point a to point b
* Add a score system
* Add obstacles and a punishment for hitting those obstacles
* Add levels

## Completed Tasks

### Avelina
* Completed In: February 2025
    * Add name to credits

* Completed In: March 2025
    * Add title button

### David
* Completed In: February 2025
    * Add name to credits
    * Set up visual framework & abstractions
    * Set up main character gameplay physics Phase 1

* Completed In: March 2025
    * Make the player motorcycle character visually turn the handlebars when turning
    * Create parent mouse click Button class
    * Modify Motorcycle physics to match new handlebar turning.

### Fenoon
* Completed In: February 2025
    * Animate Motorcycle in Title Screen Phase 1

* Completed In: March 2025
    * Add name to credits

### Francisco
* Completed In: February 2025
    * Add name to credits

* Completed In: March 2025
    * Extracted audio files for animated intro
    * Made title and map background display in their respective states
    * Added logic for title button to darken when hovered over

### Lesslie
* Completed In: February 2025
    * Add name to credits

* Completed In: March 2025
    * Design Map 1 of the game

