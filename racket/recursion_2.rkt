#lang racket

(define append
  (lambda (ls1 ls2)
    (if (null? ls1)
        ls2
        (cons (car ls1) (append (cdr ls1) ls2)))))

(require racket/trace)

(define reverse
  (lambda (ls)
    (cond
      ((null? ls) '())
      (else (append (reverse (cdr ls)) (list (car ls)))))))

(define merge
  (lambda (sorted-ntpl1 sorted-ntpl2 )
    (cond
      ((null? sorted-ntpl1) sorted-ntpl2)
      ((null? sorted-ntpl2) sorted-ntpl1)
      ((< (car sorted-ntpl1) (car sorted-ntpl2))
       (cons (car sorted-ntpl1) (merge (cdr sorted-ntpl1) sorted-ntpl2)))
      (else
       (cons (car sorted-ntpl2) (merge sorted-ntpl1 (cdr sorted-ntpl2)))))))

(define even?
  (lambda (int)
      (cond
        ((zero? int) #t)
        (else (odd? (sub1 int))))))

(define odd?
  (lambda (int)
    (cond
      ((zero? int) #f)
      (else (even? (sub1 int))))))

(define remove
  (lambda (item ls)
    (cond
      ((null? ls) '())
      ((equal? item (car ls)) (remove item (cdr ls)))
      (else (cons (car ls) (remove item (cdr ls)))))))

(define (swapper x y ls)
  ;; Swap every top level instance of x and y
  ;; in a list
  (cond
    ((null? ls) '())
    (else
     (cons (swap-tester x y ls)
           (swapper x y (cdr ls))))))

(define (swap-tester x y ls)
  (cond
    ((equal? x (car ls)) y)
    ((equal? y (car ls)) x)
    (else (car ls))))

(swapper 'cat 'dog '(my cat likes dog food))
(swapper 'cat 'dog '())



              