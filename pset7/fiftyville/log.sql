-- Keep a log of any SQL queries you execute as you solve the mystery.

-- LIST OF SUSPECTS
-- Ruth
-- Eugene
-- Raymond


-- Get the crime reports descriptions from the 28th of July
SELECT day, month, description 
FROM crime_scene_reports WHERE day=28 AND month=7;
-- The of the crimes that on day the following description matches the duck:
-- "Theft of the CS50 duck took place at 10:15am at the Chamberlin Street 
-- courthouse. Interviews were conducted today with three witnesses who were 
-- present at the time — each of their interview transcripts mentions the 
-- courthouse."

-- I should look for the interviews conducted on 28/7 that included "courhouse" 
-- in the transcript
SELECT name, transcript 
FROM interviews 
WHERE day=28 AND month=7 AND transcript LIKE '%Courthouse%';

-- Ruth|Sometime within ten minutes of the theft, I saw the thief get into a car
-- in the courthouse parking lot and drive away. If you have security footage 
-- from the courthouse parking lot, you might want to look for cars that left 
-- the parking lot in that time frame.
-- TODO: Check courthouse_security_logs for that time frame

-- Eugene|I don't know the thief's name, but it was someone I recognized. 
-- Earlier this morning, before I arrived at the courthouse, I was walking by 
-- the ATM on Fifer Street and saw the thief there withdrawing some money.
-- TODO: Check atm_transactions for people withdrawing money before 10:15 on 
-- that day on Fifer Street

-- Raymond|As the thief was leaving the courthouse, they called someone who 
-- talked to them for less than a minute. In the call, I heard the thief say 
-- that they were planning to take the earliest flight out of Fiftyville 
-- tomorrow. The thief then asked the person on the other end of the phone to 
-- purchase the flight ticket.
-- TODO: Check for phone calls with a duration of less than a minute at around 
-- 10:15, check the earliest flight out of Fiftyville on 29/7 


-- CHEKING courthouse_security_logs
SELECT hour, minute, license_plate 
FROM courthouse_security_logs 
WHERE year=2020 AND month=7 AND day=28 AND hour=10 AND minute <= 25 AND activity="exit";
-- The following are the time and license plates of vehicles leaving the 
-- courhouse within 10 of the theft
-- 10|16|5P2BI95
-- 10|18|94KL13X
-- 10|18|6P58WS2
-- 10|19|4328GD8
-- 10|20|G412CB7
-- 10|21|L93JTIZ
-- 10|23|322W7JE
-- 10|23|0NTHK55

-- Get name of every person matching the licence plates retrieved
SELECT name 
FROM people 
WHERE license_plate IN (SELECT license_plate 
                        FROM courthouse_security_logs 
                        WHERE year=2020 AND month=7 AND day=28 AND hour=10 AND minute <= 25 AND activity="exit");
-- Patrick
-- Amber
-- Elizabeth
-- Roger
-- Danielle
-- Russell
-- Evelyn
-- Ernest

-- CHEKING atm_transactions
SELECT account_number, amount 
FROM atm_transactions 
WHERE month=7 AND day=28 AND atm_location="Fifer Street" AND transaction_type="withdraw";
-- The following are the account_number and amount of withdrawal made at the 
-- atm on Fifer Street on that day
-- 28500762|48
-- 28296815|20
-- 76054385|60
-- 49610011|50
-- 16153065|80
-- 25506511|20
-- 81061156|30
-- 26013199|35

-- Get name of every person matching account numbers retrieved
SELECT name 
FROM people 
WHERE id IN (SELECT person_id 
             FROM bank_accounts 
             WHERE account_number IN (SELECT account_number 
                                      FROM atm_transactions 
                                      WHERE month=7 AND day=28 AND atm_location="Fifer Street" AND transaction_type="withdraw"));
-- Bobby
-- Elizabeth
-- Victoria
-- Madison
-- Roy
-- Danielle
-- Russell
-- Ernest

-- CHEKING phone_calls
SELECT caller, receiver
FROM phone_calls 
WHERE year=2020 AND month=7 AND day=28 AND duration < 60;
-- The following are the caller and receiver numbers of calls made on that day 
-- with a duration of less than a minute 
-- (130) 555-0289|(996) 555-8899
-- (499) 555-9472|(892) 555-8872
-- (367) 555-5533|(375) 555-8161
-- (499) 555-9472|(717) 555-1342
-- (286) 555-6063|(676) 555-6554
-- (770) 555-1861|(725) 555-3243
-- (031) 555-6622|(910) 555-3251
-- (826) 555-1652|(066) 555-9701
-- (338) 555-6650|(704) 555-2131

-- Get name of every person that made a call of less than a minute on that day
SELECT name 
FROM people 
WHERE phone_number IN (SELECT caller 
                       FROM phone_calls 
                       WHERE year=2020 AND month=7 AND day=28 AND duration < 60);
-- Bobby
-- Roger
-- Victoria
-- Madison
-- Russell
-- Evelyn
-- Ernest
-- Kimberly

-- Get name of every person that received a call of less than a minute on that day
SELECT name 
FROM people 
WHERE phone_number IN (SELECT receiver 
                       FROM phone_calls 
                       WHERE year=2020 AND month=7 AND day=28 AND duration < 60);
-- James
-- Larry
-- Anna
-- Jack
-- Melissa
-- Jacqueline
-- Philip
-- Berthold
-- Doris

SELECT "---------------------------------" AS '';
-- Retrieve the intersections form the three lists of names
SELECT name 
FROM people 
WHERE license_plate IN 
(SELECT license_plate 
 FROM courthouse_security_logs 
 WHERE year=2020 AND month=7 AND day=28 AND hour=10 AND minute <= 25 AND activity="exit")

INTERSECT

SELECT name 
FROM people 
WHERE id IN
(SELECT person_id 
 FROM bank_accounts 
 WHERE account_number IN
(SELECT account_number
 FROM atm_transactions 
 WHERE month=7 AND day=28 AND atm_location="Fifer Street" AND transaction_type="withdraw"))

INTERSECT

SELECT name
FROM people
WHERE phone_number IN
(SELECT caller
 FROM phone_calls 
 WHERE year=2020 AND month=7 AND day=28 AND duration < 60);
-- The following two persons match all three queries and are suspects
-- Ernest
-- Russell
SELECT "---------------------------------" AS '';

-- Get the names of the person that the suspects called
SELECT people_caller.name, people_receiver.name
FROM phone_calls 
JOIN people people_caller
ON phone_calls.caller = people_caller.phone_number
JOIN people people_receiver 
ON phone_calls.receiver = people_receiver.phone_number
WHERE year=2020 AND month=7 AND day=28 AND duration < 60
      AND (people_caller.name IN (SELECT name 
                                  FROM people 
                                  WHERE license_plate IN 
                                  (SELECT license_plate 
                                  FROM courthouse_security_logs 
                                  WHERE year=2020 AND month=7 AND day=28 AND hour=10 AND minute <= 25 AND activity="exit")
                                  INTERSECT
                                  SELECT name 
                                  FROM people 
                                  WHERE id IN
                                  (SELECT person_id 
                                  FROM bank_accounts 
                                  WHERE account_number IN
                                  (SELECT account_number
                                  FROM atm_transactions 
                                  WHERE month=7 AND day=28 AND atm_location="Fifer Street" AND transaction_type="withdraw"))
                                  INTERSECT
                                  SELECT name
                                  FROM people
                                  WHERE phone_number IN
                                  (SELECT caller
                                  FROM phone_calls 
                                  WHERE year=2020 AND month=7 AND day=28 AND duration < 60)));
-- Ernest|Berthold
-- Russell|Philip

SELECT "---------------------------------" AS '';
-- I now have to investigate the flight that the thief took
-- From the list of airporst, the one from which the thief took off is the Fiftyville one
SELECT id, abbreviation, full_name 
FROM airports 
WHERE abbreviation="CSF";
SELECT "---------------------------------" AS '';
-- 8|CSF|Fiftyville Regional Airport
-- Use this id to get the earliest flight that departed from Fiftyville on day after the theft
SELECT id, destination_airport_id, hour, minute 
FROM flights 
WHERE year=2020 AND month=7 AND day=29 AND origin_airport_id=(SELECT id 
                                                              FROM airports 
                                                              WHERE abbreviation="CSF")
                                                              ORDER BY hour, minute 
                                                              LIMIT 1;
-- 36|4|8|20
-- The flight the thief took had flight id 36 going to the airport with id 4 at 8:20

-- Get the name of the destination of the thief
SELECT city
FROM airports 
WHERE id=4;
-- London

SELECT "---------------------------------" AS '';
-- Get the passport number of the passengers on the flight with id 36
SELECT passport_number, seat
FROM passengers 
WHERE flight_id=36;
-- 7214083635
-- 1695452385
-- 5773159633
-- 1540955065
-- 8294398571
-- 1988161715
-- 9878712108
-- 8496433585
SELECT "---------------------------------" AS '';
SELECT name FROM people 
WHERE passport_number IN (SELECT passport_number 
                          FROM passengers 
                          WHERE flight_id=36);
-- Bobby
-- Roger
-- Madison
-- Danielle
-- Evelyn
-- Edward
-- Ernest
-- Doris

-- Ernest is the two suspect and should be the thief
-- He escaped to London
-- His accomplice is Berthold