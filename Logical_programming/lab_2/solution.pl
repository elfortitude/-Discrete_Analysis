%	LABORATORY WORK №2 (var 20)

%	INITIAL DATA

%	Есть ребята с такими именами
name("Dina").
name("Sonya").
name("Kolya").
name("Roma").
name("Misha").

%	У Ромы нет мамы
without_mom("Roma").

%	По именам судим о гендере
gender("Dina", woman).
gender("Sonya", woman).
gender("Kolya", man).
gender("Roma", man).
gender("Misha", man).


%	Напишем вспомогательные предикаты

%	Проверка списка на уникальность элементов
my_unique([]) :- !.
my_unique([H|T]) :-
	member(H, T), !, fail;
	my_unique(T).

%	Одного гендера
one_gender(X, Y) :- gender(X, Z), gender(Y, Z).
%	Разного гендера
diffrent_gender(X, Y) :- not(one_gender(X, Y)).

%	Есть мама
has_mom(X) :- not(without_mom(X)).

%	Т.к. "отец Коли уже договорился с родителями Карпенко", значит фамилия Коли не Карпенко
not_name("Kolya", "Karpenko").
absolutely_not(X, Y) :- not(not_name(X, Y)).

%	Если родители знакомы - значит это не Дина с Колей
parents_not_knows("Kolya", "Dina").
parents_knows(X, Y) :- not(parents_not_knows(X, Y)), not(parents_not_knows(Y, X)).

%	Опишем решение:

solve(Solve) :-
	%	Ответ примет вид, содержащий 5 человек с именем и фамилией.
    Solve = [
		person(AName, "Boychenko"),
		person(BName, "Karpenko"),
		person(CName, "Lysenko"),
		person(DName, "Savchenko"),
		person(EName, "Shevchenko")
	],
	%	Все переменные в ответе - это имена:
	name(AName),
	name(BName),
	name(CName),
	name(DName),
	name(EName),
	%	При этом разные:
	my_unique([AName, BName, CName, DName, EName]),
	% 	При этом выполняются следующие условия:
	% 	у Карпенко сын
	gender(BName, man),
	%	условие на то, что имя Карпенко не будет Коля
	absolutely_not(BName, "Karpenko"),
	%	Шевченко и Бойченко в одной команде, поэтому, наверное, одного пола.
	one_gender(EName, AName),
	%	Лысенко и Бойченко хотят пожениться, поэтому, наверное, разного пола.
	diffrent_gender(CName, AName),
	%	Мать Шевченко пришла к матери Карпенко, поэтому у них есть матери
	has_mom(EName),
	has_mom(BName),
	%	Отец и мать вчетвером дружат с родителями бойченко, поэтому у ниих тоже есть матери
	has_mom(CName),
	has_mom(AName),
	%	Шевченко знакомы с Карпенко
	parents_knows(EName, BName),
	%	Родители Коли знакомы с Карпенко
	parents_knows(BName, "Kolya"),
	%	Лысенко и Бойченко хорошие друзья
	parents_knows(AName, CName).
