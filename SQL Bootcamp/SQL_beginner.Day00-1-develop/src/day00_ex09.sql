select person.name, pizzeria.name
from (select * from person_visits where visit_date between '2022-01-07' and '2022-01-09') as pv, person, pizzeria
where person.id = pv.person_id and pv.pizzeria_id = pizzeria.id
order by person.name asc, pizzeria.name desc