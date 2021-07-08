SELECT DISTINCT people.name--, people.birth, movies.year
FROM people 
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.year=2004
ORDER BY people.birth;