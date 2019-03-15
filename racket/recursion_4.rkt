#lang racket

(define (count-parens-all ls)
  ;; given a list, return the
  ;; number of parentheses.
  (cond
    ((null? ls) 2)
    ((null? (car ls))
     (+ 2 (count-parens-all (cdr ls))))
    ((pair? (car ls))
     (+ (count-parens-all (car ls))
        (count-parens-all (cdr ls))))
    (else (count-parens-all (cdr ls)))))

(define (count-background-all item ls)
  ;; count the number of items in a list
  ;; not equal to `item`.
  (cond
    ((null? ls) 0)
    ((and (not (equal? (car ls) item))
          (pair? (car ls)))
     (+ (count-background-all item (car ls))
        (count-background-all item (cdr ls))))
    ((not (equal? (car ls) item))
     (add1 (count-background-all item (cdr ls))))
    (else (count-background-all item (cdr ls)))))

(define (leftmost ls)
  ;; return the leftmost atomic item in the list
  (cond
    ((null? ls) '())
    ((not (pair? (car ls))) (car ls))
    (else (if (leftmost (car ls))
              (leftmost (car ls))
              (leftmost (cdr ls))))))

(define (rightmost ls)
  ;; return the rightmost atomic item in the list
  (cond
    ((null? ls) '())
    ((not (null? (cdr ls)))
     (rightmost (cdr ls)))
    ((not (pair? (car ls))) (car ls))
    (else (rightmost (car ls)))))

(define (fact n)
  (cond
    ((zero? n) 1)
    (else (* n (fact (sub1 n))))))