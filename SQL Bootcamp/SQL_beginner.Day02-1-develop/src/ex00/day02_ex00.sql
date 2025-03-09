SELECT name, rating
FROM
    (SELECT pizzeria.name, person_visits.person_id, pizzeria.rating
        FROM pizzeria
        LEFT JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id) AS pizzeria
WHERE (person_id IS NULL);
