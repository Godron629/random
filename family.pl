% Assignment 3 Prolog
male(bill).
male(john).
male(frank).
male(joe).
male(larrie).
male(philip).
male(kevin).
male(chris).
male(danny).

female(anne).
female(dorothy).
female(sharon).
female(rochelle).
female(danelle).
female(marg).
female(connie).
female(corrie).

parent(bill,john).
parent(bill,frank).
parent(bill,joe).
parent(anne,john).
parent(anne,frank).
parent(anne,joe).
parent(john,larrie).
parent(john,sharon).
parent(john,philip).
parent(john,kevin).
parent(dorothy,larrie).
parent(dorothy,sharon).
parent(dorothy,philip).
parent(dorothy,kevin).
parent(larrie,connie).
parent(larrie,corrie).
parent(larrie,chris).
parent(marg,connie).
parent(marg,corrie).
parent(marg,chris).
parent(danny,rochelle).
parent(danny,danelle).
parent(sharon,rochelle).
parent(sharon,danelle).

% Assignment 3
% Programming Languages 3740
% Gideon Richter 001181085

%-------- General -----------
% Assert X and Y are not the same
not_same(X,Y) :- X \= Y.

% Child is inverse of parent
child(X,Y) :- parent(Y,X).

% Grandparent is parent of same parent
grandparent(X,Y) :- parent(X,Z), parent(Z,Y).

% Grandchild is inverse of grandparent
grandchild(X,Y) :- grandparent(Y,X).

% Two siblings have the same parent
sibling(X,Y) :- parent(Z,X), parent(Z,Y).


%-------- Assignment -----------

% Father is a male parent
father(X,Y) :- parent(X,Y), male(X).

% Mother is a female parent
mother(X,Y) :- parent(X,Y), female(X).

% Son is a child of Y that is male
son(X,Y) :- child(X,Y), male(X).

% Daughter is a child of Y that is female
daughter(X,Y) :- child(X,Y), female(X).

% Brother  X is a son of the same parent as child Y 
brother(X,Y) :- parent(Z,Y), son(X,Z), not_same(X,Y).

% Sister X is a daughter of the same parent as child Y 
sister(X,Y) :- parent(Z,Y), daughter(X,Z), not_same(X,Y). 

% Grandfather is a male grandparent
grandfather(X,Y) :- grandparent(X,Y), male(X).

% Grandmother is a female grandparent
grandmother(X,Y) :- grandparent(X,Y), female(X).

% Grandson X has a grandparent Y and is male
grandson(X,Y) :- grandparent(Y,X), male(X).

% Granddaughter X has a grandparent Y and is female
granddaughter(X,Y) :- grandparent(Y,X), female(X).

% Uncle is a parent's brother
uncle(X,Y) :- parent(Z,Y), brother(X,Z). 

% Aunt is a parent's sister
aunt(X,Y) :- parent(Z,Y), sister(X,Z).

% A nephew is a son of a sibling
nephew(X,Y) :- son(X,Z), sibling(Z,Y).

% A niece is a daughter of a sibling
niece(X,Y) :- daughter(X,Z), sibling(Z,Y).

% Ancestor is any recursive parent of X
ancestor(X,Y) :- parent(X,Y).
ancestor(X,Y) :- parent(X,Z), ancestor(Z,Y).

% Descendant is any recursive child of X
descendant(X,Y) :- child(X,Y).
descendant(X,Y) :- child(X,Z), descendant(Z,Y).
