#lang racket

(define (insert-left new old ls)
  ;; insert `new` item to the left of
  ;; every `old` item in a list.
  (cond
    ((null? ls) '())
    ((equal? old (car ls))
     (cons new (cons old (insert-left new old (cdr ls)))))
    (else (cons (car ls) (insert-left new old (cdr ls))))))

(define (insert-right new old ls)
  ;; insert `new` item to the right of
  ;; every `old` item in a list.
  (cond
    ((null? ls) '())
    ((equal? old (car ls))
     (cons (car ls) (cons new (insert-right new old (cdr ls)))))
    (else (cons (car ls) (insert-right new old (cdr ls))))))

(define (subst new old ls)
  ;; substitute every instance of `old`
  ;; with `new` in a list.
  (cond
    ((null? ls) '())
    ((equal? old (car ls))
     (cons new (subst new old (cdr ls))))
    (else (cons (car ls) (subst new old (cdr ls))))))

(define (deepen-1 ls)
  ;; warp a pair of parenthese around each top-level
  ;; item in a list.
  (cond
    ((null? ls) '())
    (else (cons (list (car ls)) (deepen-1 (cdr ls))))))