#lang racket

(define (harmonic-sum n)
  ;; sum the first n terms of the harmonic series
  (cond
    ((zero? n) 0)
    (else (+ (/ 1 n) (harmonic-sum (sub1 n))))))

(harmonic-sum 0)
(harmonic-sum 1)
(harmonic-sum 2)
(harmonic-sum 3)

(define (list-of-zeroes n)
  ;; return a list with n zeros
  (cond
    ((zero? n) '())
    (else
     (cons 0 (list-of-zeroes (sub1 n))))))

(list-of-zeroes 0)
(list-of-zeroes 1)
(list-of-zeroes 5)


(define (=length= ls)
  (cond
    ((null? ls) 0)
    (else (add1 (=length= (cdr ls))))))

(=length= '())
(=length= '(1 2))

(define (=list-ref= ls idx)
  (cond
    ((>= idx (=length= ls))
     (error "list-ref: Index" idx "out of range for list" ls))
    (else
     ;; only check for length once
     (list-ref-helper ls idx))))

(define (list-ref-helper ls idx)
  (cond
    ((zero? idx) (car ls))
    (else
     (list-ref-helper (cdr ls) (sub1 idx)))))

(=list-ref= '(1 2 3 4 (a b)) 4)

(define (=sum= ls)
  ;; sum a list of numbers
  (cond
    ((null? ls) 0)
    (else (+ (car ls) (=sum= (cdr ls))))))

(define (sum-n ls n)
  ;; sum the first n elements of a list
  ;; recursively this was an interview
  ;; question at farmersedge that i could
  ;; not answer.
  (cond
    ((null? ls) 0)
    ((zero? n) 0)
    (else
     (+ (car ls) (sum-n (cdr ls) (sub1 n))))))


(define (pairwise-sum ntpl-1 ntpl-2)
  ;; return the pairwise sum of two equal
  ;; length lists
  (cond
    ((null? ntpl-1) '())
    (else
     (cons (+ (car ntpl-1) (car ntpl-2))
           (pairwise-sum (cdr ntpl-1) (cdr ntpl-2))))))

(define (pairwise-product ntpl-1 ntpl-2)
  ;; return the pairwise product of two equal
  ;; length lists
  (cond
    ((null? ntpl-1) '())
    (else
     (cons (* (car ntpl-1) (car ntpl-2))
           (pairwise-product (cdr ntpl-1) (cdr ntpl-2))))))

(define (dot-product ntpl-1 ntpl-2)
  ;; return the dot product of two
  ;; equal length lists
  (cond
    ((null? ntpl-1) 0)
    (else
     (+ (* (car ntpl-1) (car ntpl-2))
        (dot-product (cdr ntpl-1) (cdr ntpl-2))))))

(define (mult-by-n n ntpl)
  ;; multiply a list by a scalar n
  (cond
    ((null? ntpl) '())
    (else
     (cons (* n (car ntpl)) (mult-by-n n (cdr ntpl))))))

(define (index item ls)
  ;; return the index of an item in ls
  ;; if the item does not exist, return -1
  (define (index-helper item ls counter)
    (cond
      ((null? ls) -1)
      ((equal? item (car ls)) counter)
      (else
       (index-helper item (cdr ls) (add1 counter)))))
  ;; we need to start a counter at zero without
  ;; adding any more parameters to the function `index`.
  (index-helper item ls 0))










      
