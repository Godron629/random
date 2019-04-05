%
% check if an item is an element of a given list
% 
my_member(Item, [Item|Tail]).
my_member(Item, [Not_Item|Tail]) :-
	my_member(Item, Tail).

%
% Assignment Q1. Check if two lists are equal
%
% Two empty lists are equal, otherwise, if the Head of
% each list is the same as the other, then recurse on 
% the Tail of each.
%
equal([], []).
equal([Head|Tail1], [Head|Tail2]) :-
	equal(Tail1, Tail2).
	
%
% append one list to another
%
my_append([], List, List).
my_append([Head|Tail], List2, [Head|Result]) :- 
	append(Tail, List2, Result).

cdr([],[]).

cdr([_|L],L).

cddr([_|L],R) :-
	cdr(L,R).

cdddr([_|L],R) :-
	cddr(L,R).

%
% Assignment Q2: Return the height H of a tree T
% Note: Does not work
%
height([], 0).   
height([Head|[]], 1).
height([Head|Tail], Count) :-
	height(Tail, Count2), 
	Count2 is 1 + Count.

%
% Assignment Q3: Assert that a given sum can be found 
% by following a path in the tree T. 
% Note: Does not work
%

