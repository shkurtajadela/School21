create table if not exists nodes (
	point1 bpchar not null,
	point2 bpchar not null,
	cost integer not null
);
insert into nodes values
	('a', 'b', 10),
	('a', 'd', 20),
	('a', 'c', 15),
	('b', 'a', 10),
	('b', 'c', 35),
	('b', 'd', 25),
	('c', 'a', 15),
	('c', 'b', 35),
	('c', 'd', 30),
	('d', 'a', 20),
	('d', 'b', 25),
	('d', 'c', 30);

WITH _res AS (	
    WITH RECURSIVE _n AS
    (SELECT point1,
    point2,
    cost,
    1 AS level,
    ARRAY[point1] AS tour,
    FALSE AS cycle,
    ARRAY[cost] AS costs
    FROM nodes
    WHERE point1 = 'a'

    UNION ALL

    SELECT nodes.point1,
    nodes.point2,
    nodes.cost+_n.cost AS cost,
    _n.level+1 AS level,
    _n.tour || nodes.point1 AS tour,
    nodes.point1 = ANY (_n.tour) AS cycle,
    _n.costs || nodes.cost AS costs
    FROM nodes INNER JOIN _n ON _n.point2 = nodes.point1 AND NOT cycle)

SELECT cost - costs[5] AS total_cost , tour 
FROM _n WHERE tour[5] ='a')
SELECT DISTINCT * FROM _res
WHERE total_cost = (SELECT min(total_cost) FROM _res)
ORDER BY 2;
