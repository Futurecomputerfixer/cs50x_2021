-- Keep a log of any SQL queries you execute as you solve the mystery.

-- query the information about the theft
SELECT * FROM crime_scene_reports WHERE street = 'Chamberlin Street' AND month = 7 AND day = 28;
-- the theft took place at 10:15 am 

-- query the witnesses words
SELECT * FROM interviews WHERE month = 7 AND day = 28;
-- interviews with id = 161, 162, 163 are related to the theft
-- useful information were retrieved from those interviews:
-- 1. Sometime within ten minutes of the theft, the thief get into a car in the courthouse parking lot and drive away. 
-- Refer to the Security Footage with the right time frame(10 mins early or late from 10:15am)
-- eight cars exited from the parking lot in that time period; unable to identify the car
-- 2. the theif was withdrawing money from an ATM on Fizer Street in the morning of the day when the theft happened.
-- 3. As the theif leaving the courthouse, they were planning to take the earliest flight out of Fiftyville tomorrow(the day after the theft happened) as the they called someone for less than one minute


-- query using the information provided, three suspects were found 
SELECT name FROM people
WHERE people.id IN (SELECT person_id FROM bank_accounts WHERE bank_accounts.account_number IN (SELECT atm_transactions.account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = 'withdraw' AND atm_location = "Fifer Street"))
AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60) AND license_plate IN (SELECT courthouse_security_logs.license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND 15 < minute AND minute< 25 AND hour = 10);

--Russell
--Ernest


SELECT * FROM airports;
-- query all the airports. the airport that the theif took off from has an id of 8


SELECT name FROM people WHERE people.passport_number In (SELECT passengers.passport_number FROM passengers WHERE passengers.flight_id In (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = '8' ORDER BY hour LIMIT 1));
-- because the theif booked the earliest flight, they flew to an airport with an id of 4: Heathrow Airport | London; flight id = 36
-- the name of the theif: Ernest


-- the theif's accomplice
SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.receiver WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60" AND caller = (SELECT phone_number FROM people WHERE name = "Ernest");

-- the accomplice is Berthold





CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE courthouse_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);