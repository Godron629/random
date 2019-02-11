#lang racket

(define tree '(1 (2 (4 () ()) (5 () ())) (15 () ()) (16 () ())))
;(define tree '(1 (2 (4))))
  
;; Function height
;; Return the height of a tree represented as a list.
;; .param ls is a tree list
;; .returns integer height of tree
;; .example (height '(1 (2 (4 () ()))) -> 3
(define height
  (lambda (ls)
    ; A nodes car is equal to its left subtree, and
    ; its cdr is equal to the remaining right siblings
    ; on the same level.
    (cond
      ((is-leaf-node? ls) 0)
      ; The height of a node is one greater than
      ; the height of its left subtree, and the
      ; same height as each of its siblings. 
      (else (max
             (add1 (height (car ls)))
             (height (cdr ls)))))))

;; Function is-leaf-node
;; Return if a list meets the definition of a leaf node.
;; .param ls is a tree list
;; .returns #t/#f
;; .example (is-leaf-node '(1)) -> #t
(define is-leaf-node?
  (lambda (ls)
    (not (pair? ls))))

;; Function that walks a list representation of a tree
;; and returns the same tree where each node is a tuple
;; containing the original value and the level of the node.
;; .param ls is a list tree
;; .param level is the integer height of the tree
;; .return list
;; .example (label-tree-levels '(1 (2)) 2) -> '((1 2) ((2 1))
(define (label-tree-levels ls)
  (define (helper tree tree-height)
    (cond
      ((null? tree) '())
      ((is-leaf-node? tree)
       ; return value of the leaf
       (cons tree tree-height))
      ((null? (cdr tree))
       ; no right siblings - go down a level
       (helper (car tree) (sub1 tree-height)))
      (else (append
             ; recurse right siblings and children
             (helper (car tree) (sub1 tree-height))
             (helper (cdr tree) tree-height)))))
  (helper ls (+ 1 (height ls))))

;; Function that appends two lists together similar to
;; `[1, 2] + [3, 4] == [1, 2, 3, 4]` in python.
;; .param ls1 is a list
;; .param ls2 is a list
;; .return list
;; .example (append '(1 2) '(3 4)) -> (1 2 3 4)
(define append
  (lambda (ls1 ls2)
    (cond
      ((null? ls1) ls2)
      ((not (pair? ls1)) (cons ls1 ls2))
      (else (cons (car ls1) (append (cdr ls1) ls2))))))

;; Function that returns a list of first pair values
;; if the second value of the same pair is equal to
;; test-value. 
;; .param ls is a list of pairs
;; .param test-value is an object
;; .return list
;; .example (firsts-if-seconds-match '((1 . 2) (3 . 4)) 2) -> (1)
(define firsts-if-seconds-match
  (lambda (ls test-value)
    (cond
      ((null? ls) '())
      ((equal? (cadar ls) test-value)
       ; return the first value and recurse the remaining pairs
       (cons
        (caar ls)
        (firsts-if-seconds-match (cdr ls) test-value)))
      ; recurse the remaining pairs
      (else (firsts-if-seconds-match (cdr ls) test-value)))))

;; Function that turns an item into a list
;; .param item is any item
;; .return list
;; .example (make-list-of-one 1) -> '(1)
(define make-list-of-one
 (lambda (item)
   (cons item '())))

;; Function that turns two items into a list
;; .param item1 is any item
;; .param item2 is any item
;; .return list
;; .example (make-list-of-two 1 2) -> '(1 2)
(define make-list-of-two
  (lambda (item1 item2)
    (cons item1 (make-list-of-one item2))))

;; Function that takes a list and returns a list
;; where every two values are combined into a pair.
;; .param ls is a list of EVEN length
;; .return list
;; .example (group-by-two '(1 2 3 4)) -> '((1 2) (3 4))
(define group-by-two
  (lambda (ls)
    (cond
      ((not (pair? ls)) '())
      (else (cons (make-list-of-two (car ls) (cadr ls)) (group-by-two (cddr ls)))))))

(require racket/trace)

;; level takes a tree represented as a list
;; and returns all values that are at `level`,
;; in the same order that they are traversed.
;; .param tree is a tree represented as a list
;; .param level is the level of which values are returned
;; .returns list
;; .example (level '(1 (3)) 2) -> 3
(define (level tree level)
  (letrec
      ((flat-labelled-tree (label-tree-levels tree))
       (grouped-labelled-tree (group-by-two flat-labelled-tree)))
    (firsts-if-seconds-match grouped-labelled-tree level)))

(define (max-of-seconds ls)
  (cond
    ((null? ls) 0)
    (else (max
           (cadar ls)
           (max-of-seconds (cdr ls))))))

(define (seconds-increasing ls)
  (define (helper ls previous)
    (cond
      ((null? ls) #t)
      ((equal? (+ 1 previous) (cadar ls))
       (helper (cdr ls) (add1 previous)))
      (else #f)))
  (helper ls 0))

(define (seconds-increasing2 ls)
  (define (helper ls previous)
    (cond
      ((null? ls) '())
      ((not (equal? (+ 1 previous) (cadar ls)))
       #f)
      ((null? (cdr ls)) ls)
      (else
       (if (equal? (+ 2 previous) (cadadr ls))
           (cons (car ls) (helper (cdr ls) (add1 previous)))
           '()))))
  (helper ls 0))


;(seconds-increasing2 (car thing))

(define (return-increasing-perm ls)
  (cond
    ((null? ls) '())
    ((not (seconds-increasing2 (car ls))) (return-increasing-perm (cdr ls)))
    (else (cons (seconds-increasing2 (car ls)) (return-increasing-perm (cdr ls))))))

(define (sum-of-firsts ls)
  (cond
    ((null? ls) 0)
    (else (+ (caar ls) (sum-of-firsts (cdr ls))))))

(define (sum-of-sublist-firsts ls)
  (cond
    ((null? ls) '())
    (else (cons (sum-of-firsts (car ls)) (sum-of-sublist-firsts (cdr ls))))))

(remove-duplicates (sum-of-sublist-firsts (return-increasing-perm (permutations (group-by-two (label-tree-levels tree))))))


;(define (sum? tree value)


  
