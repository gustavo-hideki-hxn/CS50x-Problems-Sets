-- Harvard CS50x - Week 7 - Problem Set 7
-- Movies: https://cs50.harvard.edu/x/psets/7/movies/
-- Collection of problem 1-13, database provided by Harvard

-- 1. Titles of all movies from 2008
SELECT title
FROM movies
WHERE year = 2008;

-- 2. Birth year of Emma Stone
SELECT birth
FROM people
WHERE name = 'Emma Stone';

-- 3. Titles of all movies since 2018, in alphabetical order
SELECT title
FROM movies
WHERE year >= 2018
ORDER BY title;

-- 4. Number of movies with a 10.0 rating
SELECT COUNT(*)
FROM ratings
WHERE rating = 10.0;

-- 5. Titles and years of all Harry Potter movies, in chronological order (title beginning with "Harry Potter and the ...")
SELECT title, year
FROM movies
WHERE title LIKE 'Harry Potter and the%'
ORDER BY year;

-- 6. Average rating of movies in 2012
SELECT avg(rating)
FROM ratings
WHERE movie_id IN (
    SELECT movies.id
    FROM movies
    WHERE movies.year = 2012
);

-- 7. All movies and ratings from 2010, in decreasing order by rating (alphabetical for those with same rating)
SELECT title, rating AS n
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2010
ORDER BY rating DESC, title;

-- 8. Names of people who starred in Toy Story
SELECT name
FROM people
WHERE people.id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id =(
        SELECT movies.id
        FROM movies
        WHERE title = "Toy Story"
    )
);

-- 9. Names of all people who starred in a movie released in 2004, ordered by birth year
SELECT DISTINCT id, name
FROM people
WHERE people.id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT movies.id
        FROM movies
        WHERE year = 2004
    )
)
ORDER BY birth;

-- 10. Names of all directors who have directed a movie that got a rating of at least 9.0
SELECT DISTINCT name
FROM people
WHERE people.id IN (
    SELECT person_id
    FROM directors
    WHERE movie_id IN (
        SELECT movie_id
        FROM ratings
        WHERE rating >= 9.0
    )
);

-- 11. Titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated
SELECT title
FROM movies
WHERE movies.id IN (
    SELECT movie_id
    FROM stars
    WHERE person_id IN (
        SELECT people.id
        FROM people
        WHERE name = 'Chadwick Boseman'
   )
)
ORDER BY (
    SELECT rating
    FROM ratings
    WHERE movie_id = movies.id
    AND
    rating <= 7.5
    ) DESC
LIMIT 5;

-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred
SELECT title
FROM movies
WHERE movies.id IN (
    SELECT movie_id
    FROM stars
    WHERE person_id = (
        SELECT people.id
        FROM people
        WHERE name = "Bradley Cooper")
INTERSECT
    SELECT movie_id
    FROM stars
    WHERE person_id = (
        SELECT people.id
        FROM people
        WHERE name = "Jennifer Lawrence")
);

-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred
SELECT name
FROM people
WHERE people.id != (
    SELECT people.id
            FROM people
            WHERE name = 'Kevin Bacon'
            AND
            birth = 1958
    )
    AND
    people.id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT movie_id
        FROM stars
        WHERE person_id = (
            SELECT people.id
            FROM people
            WHERE name = 'Kevin Bacon'
            AND
            birth = 1958
        )
    )
);
