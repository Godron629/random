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

(define (=append= ls1 ls2)
  ;; append two lists
  (cond
    ((null? ls1) ls2)
    (else (cons (car ls1) (=append= (cdr ls1) ls2)))))

(define (subst-all new old ls)
  ;; substitute all top level and nested
  ;; occurences of `old` with `new` in a list.
  (cond
    ((null? ls) '())
    ((equal? old (car ls))
     (cons new (subst-all new old (cdr ls))))
    ((pair? (car ls))
     (cons (subst-all new old (car ls)) (subst-all new old (cdr ls))))
    (else
     (cons (car ls) (subst-all new old (cdr ls))))))

(define (insert-left-all new old ls)
  ;; Put a `new` to the left of every `old`
  ;; at the top and nested levels of list.
  (cond
    ((null? ls) '())
    ((equal? old (car ls))
     (cons new (cons old (insert-left-all new old (cdr ls)))))
    ((pair? (car ls))
     (cons (insert-left-all new old (car ls))
           (insert-left-all new old (cdr ls))))
    (else
     (cons (car ls) (insert-left-all new old (cdr ls))))))

(define (sum-all ls)
  ;; sum top and nested numbers in a list
  (cond
    ((null? ls) 0)
    ((pair? (car ls))
     (+ (sum-all (car ls))
        (sum-all (cdr ls))))
    (else (+ (car ls) (sum-all (cdr ls))))))










