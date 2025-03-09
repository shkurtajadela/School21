select id, name, case
	when age >= 10 and age <= 20 then 'interval 10-20'
	when age > 20 and age < 24 then 'interval 20-24'
	else 'interval more than 23'
	end as interval_info
from person
order by interval_info asc