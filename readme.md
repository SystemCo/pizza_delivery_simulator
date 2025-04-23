# Welcome to the Pizza Delivery Simulator!
## Overview:
Have you ever wanted to work minimum wage delivering pizzas? 
Of course not, but now you can!
* Avoid pedestrians and other vehicles on the road! 
* Fight against the clock! Pay your victims’ horrific medical bills! 
* In Pizza Delivery Simulator!

---

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

---

## Build requirements:
* Currently only supports linux
* c++11 compatible compiler
* libX11
* libGL
* libGLU

## Build:
* run make
* run ./pizza\_deliv

# Meet the developers
## Avelina
* Manager of Menus
## David
* Group Lead
## Fenoon
* Head of Physics
## Francisco
* Auditor of Audio
## Lesslie
* Head of Gameplay UI/Display

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
* New responsibility: Responsible for menus screens
* Related TODO steps:
    * Implement a global array of backgrounds in your personal files.
    * Implement macros for indexing into the array.
    * Make an init_all() function for an array of images.
        * You can place the file names for all background images in your personal cpp file.
        * If someone wants to add a new background, they need to ask you to update your files to accommodate.

* Add start menu screen
    * Only needs a single button which will start gameplay
    * Uses a unique background
    * Assigned by: David
    * Assigned on: Wednesday 03/12/25
    * Due by:      Wednesday 03/12/25
    * Status:      Incomplete



### David
* Implement traffic logical calls for many vehicles to drive realistically along the road.

### Fenoon

* Add two collision detection methods to the Entity class. 
    * One that takes an entity as a parameter;
    * One that takes an AABB as a parameter. 
    * (this may be a position and two floats for width and height)    

    * Assigned on: Friday 03/28/25
    * Assigned by: Fenoon
    * Due by:      Friday 04/5/25
    * Status:      Incomplete
      
* implement motorcycle collision method to track whether motorcyle was going backwards or forward
* Add text to screen when collision detected with entities
* Add text to screen when pizza is delivered
* Fix animated text in animation page
* Fix pause menu positions   

  
### Francisco
* Add global audio functions
    * Assigned on:  Tuesday 04/22/25
    * Assigned by:  Francisco
    * Due by:       Sunday 04/27/25
    * Status:       Incomplete

* Import audio files
    * Assigned on:  Tuesday 04/22/25
    * Assigned by:  Francisco
    * Due by:       Sunday 04/27/25
    * Status:       Incomplete

* Implement money system
    * Assigned on:  Tuesday 04/22/25
    * Assigned by:  Francisco
    * Due by:       Sunday 04/27/25
    * Status:       Incomplete


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
* Make a list of timers which can all be rendered with a single function call.
    * Could implement an array or a linked list. 
    * Assigned on: Friday 03/28/25
    * Assigned by: David
    * Due by:      Friday 04/05/25
    * Status:      Incomplete
 * Orginally used linked list for list of timers, use array instead


# Project Tasks
### Basic UI / UX
* Animated intro
    -> Timeout, Click, any button push
* Home Menu
    * Looks like pizza order menu
* Tutorial
* Controls
* Options (i.e. sound)
    * Volume adjustment only
* Game Play
    -> Push the play game button from Home Menu
* Pause Menu
    -> Push esc while playing
* Exit Game
    -> Quit button, from home, from pause, alt+<F4>

### Animated Intro
* TODO: Make the animation clean, specific and meaningful
    * Wheelie, driving forward, pizzaboxes if we have time

* If intro is not complex enough, then not valid
    * Spinning world is not enough
    * Just Animated text is not enough
* Add scrolling backdrop, weelie, pizza boxes, etc. 

## Gameplay
### Termination
* Endless
* Timed 
    * (Goal high score)
    * Goal: Win -> Score > some value

* Victory Upon Reaching target score
    * Retirement

### Delivery
* Add a goal to get from point a to point b
* You must deliver in x amount of timee or lose a life
* Recieve money for every delivery
    * $10.00 -> $20.10
    -> $30.30
    $40.60
    $51.10
* Goal of the game is to get as much money before dying
* Popup notification upon successful delivery

### Collision
* Add Motorcycle logic when collision occurs
    * Should not keep moving
    * Explosions visual
    * Noise
* Lose a life

### Add more traffic
* Add traffic pathing logic
* random?
    * Both
    * Different vehicle types have different levels of predictability
* Add pedestrians

## Completed Tasks

### Avelina
* Completed In: February 2025
    * Add name to credits

* Completed In: March 2025
    * Add title button
    * Make sure title button only displays when in the title screen

### David
* Completed In: February 2025
    * Add name to credits
    * Set up visual framework & abstractions
    * Set up main character gameplay physics Phase 1

* Completed In: March 2025
    * Make the player motorcycle character visually turn the handlebars when turning
    * Create parent mouse click Button class
    * Modify Motorcycle physics to match new handlebar turning.
    * Implement path following method using an array of points
    * Implement sprite sheets using the frameworks 

* Completed In: April 2025
    * Force application into fullscreen

### Fenoon
* Completed In: February 2025
    * Animate Motorcycle in Title Screen Phase 1

* Completed In: March 2025
    * Add name to credits
    * Add pause functionality when <esc> keyboaord key is pressed
    * Add clickable button that will return to play while in pause menu

* Completed In: April 2025
    * Add collision functions to detect when the motorcycle collides with an AABB
    

### Francisco
* Completed In: February 2025
    * Add name to credits

* Completed In: March 2025
    * Extracted audio files for animated intro
    * Made title and map background display in their respective states
    * Added logic for title button to darken when hovered over
    * Make sure only one background displays at a time

* Completed In: April 2025
    * Make buttons dim when and only when mouse is hovering over them.

### Lesslie
* Completed In: February 2025
    * Add name to credits

* Completed In: March 2025
    * Design Map 1 of the game

