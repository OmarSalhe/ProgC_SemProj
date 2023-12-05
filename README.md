# ProgC_SemProj
Semester Project for Ed Crotty

look at code version for better reading.

GROUP:
  * Abu - Main Function
  * Yao - Do the Month stuff. 
  * Omar - implementing Zeller
    
JOBS:
  * Print calendar
      * Monthly
      * Yearly
        
  * Events file
      * Making
      * Deleting
        
  * Implementing Zeller

  * Main function

  * Additional feature = ???

  * Will add more 

MAKE SURE TO COMMENT!


I recommend that you develop the program in stages, so the requirements are outlined in that fashion,

Stage 1:  Print calendars for a particular month or year

 write a C program that will print a calendar for any month of any year since 15 October 1582; the calendar should be formatted like a  typical calendar page: Month and Year on the top line, then Days of the week Sunday to Saturday, then, in a block, the dates of the    month in their proper day columns.

 the user is to input a year and month and the program is to print a calendar for that month. You are to decide whether the user        should type in an integer or a word for the month. Both entries should be validated, any errors flagged, and the user should be asked  to reenter the erroneous data. (see samples on page ??)

 Include an option for the user to request a calendar for an entire year, say by entering the word “all” for the month.
 Once you have a basic program working properly, then move to stage two.
 

Stage 2:  Add the ability to maintain a list of events by date

 Add a function to allow the user to enter an event and date (time might be included as part of the event listing or could be entered   as a separate item

 The events are to be written to a text file, one event per line; the file name is to be the name of the user. The user should be       asked to enter their (file) name when starting a session and the program is to pull up and display any saved events that belong to     this particular user.  (see samples, page ??)
 the user should be able to add, delete and modify events as desired.

 when a user requests a calendar for a particular month & year, any events for that month are to be displayed either in or below the    actual calendar display.




Stage 3:  Add additional capabilities of your own devising.  (optional)
 



Scoring Rubric:

Function:
  3 points:  program functions as described for Stage 1
  
  5 points:  program functions as described for both Stage 1 and Stage 2
  
  plus up to 3 bonus points for any stage 3 additions


Program style, correct use of functions and C constructs, etc:

  5 points:  program is written in good style, properly subdivided into functions with correct usage of appropriate C constructs;        validation of inputs and file opens/closes, etc.


Necessary formulas and examples:

Zeller’s Congruence:  Calculates the day of the week for the Gregorian Calendar (also available for the Julian Calendar)
h = (q + (13 * (m + 1) / 5) + K + (K / 4) + (J / 4) - 2 * J) % 7
where: 

h = day of week (0 = Saturday, 1 = Sunday, 2 = Monday, … , 6 = Friday)
q = day of the month
m = month (3 = March, 4 = April, 5 = May, … 12 = December, 13 = January, 14 = February
K = year of the century (year mod 100)
J is the zero based century (actually) e.g. 1995 -> 19
[...] is the floor function (integer part of a non-negative real, e.g.,
mod is the modulus operator or remainder after division (%)
 

in this algorithm January and February are counted as months 13 and 14 of the previous year. e.g. if it is 2 February 2010, the algorithm counts the date as the second day of the fourteenth month of 2009 (02/14/2009 in DD/MM/YYYY format)
