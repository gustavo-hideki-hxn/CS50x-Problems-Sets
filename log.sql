-- Harvard CS50x - Week 7 - Problem Set 7
-- Fiftyville: https://cs50.harvard.edu/x/psets/7/fiftyville/
-- Log of queries for solving the mystery, database provided by Harvard

-- Visualize crime_scene reports table for July 27th
SELECT *
FROM crime_scene_reports
WHERE month = 7
and
day = 28;
-- crime report:
    -- Time: 10:15
    -- Local: Bakery
    -- Number of Witnesses: 3
    -- Time of interview: same day
    -- Interviews mentioned bakery

-- Get interviews from July 27th
SELECT *
FROM interviews
WHERE month = 7
AND
DAY = 28
AND
transcript LIKE '%bakery%';
-- Interview 1:
    -- Thief left on a car sometime ten minutes of the theft
-- Interview 2:
    -- Thief withdrwawn money on ATM early morning on Leggett Street
-- Interview 3:
    -- Thief called someone for about 1 minute
    -- Thief + accomplice will take the earliest flight out Fityville July 29th
    -- Accomplice bought the flight (purchase on July 28th)

-- Get bakery security camera log from July 28th from 10:15am to 10:25am
SELECT *
FROM bakery_security_logs
WHERE year = 2025
AND
month = 7
AND
day = 28
AND
hour = 10
AND
minute >= 15
AND
minute <= 25;
-- Possible car plates:
    -- 5P2BI95
    -- 94KL13X
    -- 6P58WS2
    -- 4328GD8
    -- G412CB7
    -- L93JTIZ
    -- 322W7JE
    -- 0NTHK55

-- Get atm transaction from morning of July 28th on Leggett Street
SELECT *
FROM atm_transactions
WHERE year = 2025
AND
month = 7
AND
day = 28
AND
atm_location = 'Leggett Street'
AND
transaction_type = 'withdraw';
-- Withdraws and ammount:
    -- 28500762 - 48
    -- 28296815 - 20
    -- 76054385 - 60
    -- 49610011 - 50
    -- 16153065 - 80
    -- 25506511 - 20
    -- 81061156 - 30
    -- 26013199 - 35

-- Get phone call from July 28th around 10h15 with duration of less than a minute
SELECT *
FROM phone_calls
WHERE year = 2025
AND
month = 7
AND
day = 28
AND
duration < 60;
-- caller (possible thief) and receiver (possible accomplice)
    -- (130) 555-0289 | (996) 555-8899
    -- (499) 555-9472 | (892) 555-8872
    -- (367) 555-5533 | (375) 555-8161
    -- (499) 555-9472 | (717) 555-1342
    -- (286) 555-6063 | (676) 555-6554
    -- (770) 555-1861 | (725) 555-3243
    -- (031) 555-6622 | (910) 555-3251
    -- (826) 555-1652 | (066) 555-9701
    -- (338) 555-6650 | (704) 555-2131

-- Get people with caller number from list (possible thief) with same license_plate from camera log list and bank account from ATM withdraws
SELECT *
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2025
    AND
    month = 7
    AND
    day = 28
    AND
    duration < 60
    )
AND
license_plate IN (
    SELECT bakery_security_logs.license_plate
    FROM bakery_security_logs
    WHERE year = 2025
    AND
    month = 7
    AND
    day = 28
    AND
    hour = 10
    AND
    minute >= 15
    AND
    minute <= 25
    )
AND
id IN (
    SELECT person_id
    from bank_accounts
    WHERE account_number IN (
        SELECT atm_transactions.account_number
        FROM atm_transactions
        WHERE year = 2025
        AND
        month = 7
        AND
        day = 28
        AND
        atm_location = 'Leggett Street'
        AND
        transaction_type = 'withdraw'
            )
        );
-- possible thieves (people id and name) and possible accomplice number:
    -- 514354 | Diana | (725) 555-3243
    -- 686048 | Bruce | (375) 555-8161

-- Get name, phone_number, passport_number and license plate from possible thieves and accomplices
SELECT *
FROM people
WHERE id = 514354
OR
id = 686048
OR
phone_number = '(725) 555-3243'
OR
phone_number = '(375) 555-8161';
-- possible thieves and accomplice (id, name, phone_number, license_plate):
    -- Pair 1:
        -- Thief: 514354 | Diana | (770) 555-1861 | 3592750733 | 322W7JE
        -- Accomplice: 847116 | Philip | (725) 555-3243 | 3391710505 | GW362R6
    -- Pair 2:
        -- Thief: 686048 | Bruce  | (367) 555-5533 | 5773159633 | 94KL13X
        -- Accomplice: 864400 | Robin  | (375) 555-8161 | NA | 4V16VO0

-- Confirm thief and accomplice with flight passengers record from July 29th morning departuring from fiftyville
-- Get flights from fiftyville on July 29th
SELECT *
FROM flights
WHERE origin_airport_id IN (
    SELECT id
    FROM airports
    WHERE city = 'Fiftyville'
)
AND
year = 2025
AND
month = 7
AND
day = 29;
-- earliest flight at 8h20, id = 36

-- Get passanger from flight id = 36
SELECT name, id
FROM people
WHERE passport_number IN (
    SELECT passengers.passport_number
    FROM passengers
    WHERE flight_id = 36
);

-- Get the destination city for city id = 4 (flight 36 destination)
SELECT city
FROM airports
WHERE id = 4;
-- result:
    -- Thief = Bruce
    -- Accomplice = Robin
    -- Destination = New York City
