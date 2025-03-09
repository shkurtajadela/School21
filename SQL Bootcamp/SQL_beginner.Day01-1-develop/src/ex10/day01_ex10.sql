SELECT person.name as person_name, m.pizza_name, pizzeria.name as pizzeria_name
FROM person_order
JOIN menu m ON person_order.menu_id = m.id
JOIN person ON person.id = person_order.person_id
JOIN pizzeria ON m.pizzeria_id=pizzeria.id
ORDER BY person_name, pizza_name, pizzeria_name;