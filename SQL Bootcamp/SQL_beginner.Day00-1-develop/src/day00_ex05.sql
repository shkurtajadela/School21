SELECT 
    (SELECT p.name
    FROM person p
    WHERE p.id = o.person_id) AS person_name
FROM person_order o
WHERE (o.menu_id = 13 or o.menu_id = 14 or o.menu_id = 18)
    AND o.order_date = '2022-01-07';
