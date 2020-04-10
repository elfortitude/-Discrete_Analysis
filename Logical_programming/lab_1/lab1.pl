%	TASK ONE (REALIZATION OF STANDART PREDICATES)
% my version of predicate 'length'
my_length([], 0).
my_length([_|T], N) :-
    my_length(T, N1), N is N1+1.
% my version of predicate 'member'
my_member(X, [X|_]).
my_member(X, [_|T]) :-
    my_member(X, T).
% my version of predicate 'append'
my_append([], M, M).
my_append([H|T], M, [H|X]) :-
    my_append(T, M, X).
% my version of predicate 'remove' (delete(InputList, X, Result) in SWI-Prolog)
my_remove(M, [M|T], T).
my_remove(M, [H|T], [H|X]) :-
    my_remove(M, T, X).
% my version of predicate 'permute'
my_permute([], []).
my_permute(L, [H|T]) :-
    my_remove(H, L, X),
    my_permute(X, T).
% my version of predicate 'sublist' (subset(X, Y) in SWI-Prolog)
my_sublist([], []).
my_sublist(X, Y) :-
    my_append(_, T, Y),
    my_append(X, _, T).

%	TASK TWO (WORKING WITH LISTS, INDIVIDUAL TASK)
% getting the last element of a list using standard predicates
last_elem(X, L) :-
    append(_, [X], L).

% my owmn realisation of getting the last element of a list
my_last_elem(X, [X]).
my_last_elem(X, [_|T]) :-
    my_last_elem(X, T).

%	TASK THREE (WORKING WITH NUMBER LISTS, INDIVIDUAL TASK)
% getting the sum of all list elements
my_sum([], 0).
my_sum([H|T], X) :-
	my_sum(T, X1),
	X is H + X1.

%	TASK FOUR (EXAMPLE OF USE TWO PREDICATES)
% delete the last elemenet of a list
my_delete_last(L, X) :-
    my_last_elem(Y, L), my_remove(Y, L, X).