-- Keep a log of any SQL queries you execute as you solve the mystery.

-- LIST OF SUSPECTS
-- Ruth
-- Eugene
-- Raymond

-- Look at the columns in crime_scene_reports
.schema crime_scene_reports;

-- Get the crime reports descriptions from the 28th of July
SELECT day, month, description FROM crime_scene_reports WHERE day=28 AND month=7;
-- The of the crimes that on day the following description matches the duck:
-- "Theft of the CS50 duck took place at 10:15am at the Chamberlin Street 
-- courthouse. Interviews were conducted today with three witnesses who were 
-- present at the time — each of their interview transcripts mentions the 
-- courthouse."

-- I should look for the interviews conducted on 28/7 that included "courhouse" 
-- in the transcript
SELECT name, transcript FROM interviews WHERE day=28 AND month=7 AND transcript LIKE '%Courthouse%';

-- Ruth|Sometime within ten minutes of the theft, I saw the thief get into a car
-- in the courthouse parking lot and drive away. If you have security footage 
-- from the courthouse parking lot, you might want to look for cars that left 
-- the parking lot in that time frame.

-- Eugene|I don't know the thief's name, but it was someone I recognized. 
-- Earlier this morning, before I arrived at the courthouse, I was walking by 
-- the ATM on Fifer Street and saw the thief there withdrawing some money.

-- Raymond|As the thief was leaving the courthouse, they called someone who 
-- talked to them for less than a minute. In the call, I heard the thief say 
-- that they were planning to take the earliest flight out of Fiftyville 
-- tomorrow. The thief then asked the person on the other end of the phone to 
-- purchase the flight ticket.