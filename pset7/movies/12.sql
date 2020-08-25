SELECT title FROM movies
WHERE id IN
(SELECT movie_id FROM
(SELECT movie_id, count(*) AS qtdd FROM stars
WHERE person_id IN
(SELECT id FROM people
WHERE name in ("Johnny Depp", "Helena Bonham Carter"))
GROUP BY movie_id
HAVING qtdd > 1));

/*
Too slow

SELECT title FROM
(SELECT title, COUNT(*) AS qtdd FROM movies
INNER JOIN stars ON movies.id = stars.movie_id
INNER JOIN people ON stars.person_id = people.id
WHERE people.name in ("Johnny Depp", "Helena Bonham Carter")
GROUP BY movies.title) as tb
WHERE qtdd > 1;
*/