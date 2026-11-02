-- Harvard CS50x - Week 7 - Problem Set 7
-- Songs: https://cs50.harvard.edu/x/psets/7/songs/
-- Collection of problem 1-8, database provided by Harvard

-- 1.
SELECT name 
FROM songs;

--2.
SELECT name 
FROM songs 
ORDER BY tempo;

--3.
SELECT name 
FROM songs 
ORDER BY duration_ms DESC LIMIT 5;

--4.
SELECT name 
FROM songs
WHERE danceability > 0.75
AND energy > 0.75
AND valence > 0.75;

--5.
SELECT AVG(energy) 
FROM songs;

--6.
SELECT name
FROM songs
WHERE artist_id = (
    SELECT id
    from artists
    WHERE artists.name = 'Post Malone'
);

--7.
SELECT avg(energy)
FROM songs
WHERE artist_id = (
    SELECT id
    FROM artists
    WHERE artists.name = 'Drake'
);

--8.
SELECT name
FROM songs
WHERE name LIKE "%feat.%";