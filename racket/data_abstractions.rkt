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

(define (make-list count item)
  ;; make a list of item repeated `count` times
  (cond
    ((zero? count) '())
    (else
     (cons item (make-list (sub1 count) item)))))

(define (all-same? ls)
  ;; assert that every element of a list
  ;; is the same.
  (cond
    ((or (null? ls) (null (cdr ls))) #t)
    ((equal? (car ls) (cdr ls)))
    (else #f)))

(define (count-background item ls)
  ;; return a count of the number
  ;; of elements in `ls` not equal
  ;; to `item`.
  (cond
    ((null? ls) 0)
    ((equal? item (car ls))
     (count-background item (cdr ls)))
    (else (add1 (count-background item (cdr ls))))))

(define (list-front ls n)
  ;; return the first n elements of ls
  (define (list-front-helper ls n)
    (cond
      ((or (null? ls) (zero? n)) '())
      (else
       (cons (car ls) (list-front (cdr ls) (sub1 n))))))
  (if (>= n (length ls))
      (error "length of " ls "is less than " n)
      (list-front-helper ls n)))

(define (wrapa item n)
  ;; wrap item in n brackets
  (cond
    ((zero? n) item) ; return the item 
    (else
     (cons (wrapa item (sub1 n)) '()))))

(define (multiple? m n)
  ;; assert that n is a multiple of m
  (cond
    ((zero? n) 0)
    (else (zero? (remainder m n)))))

(define (even? n)
  ;; assert that a number n is even
  (cond
    ((zero? n) #t)
    (else (odd? (sub1 n)))))

(define (odd? n)
  ;; assert that a number n is odd
  (cond
    ((zero? n) #f)
    (else (even? (sub1 n)))))

(define (sum-of-odds ls n)
  ;; return the sum of the first n odd integers
  (cond
    ((or (null? ls) (zero? n)) 0)
    ((odd? (car ls))
     (+ (car ls) (sum-of-odds (cdr ls) (sub1 n))))
    (else (sum-of-odds (cdr ls) n))))

(require racket/trace)
(define (n-tuple->integer ntpl)
  ;; convert an n tuple to its integer equivalent
  ;; i.e. (1 2 3) -> 123
  (define (helper ntpl n)
    (cond
      ((null? ntpl) 0)
      ((zero? n) (car ntpl))
      (else (+ (* (expt 10 n) (car ntpl))
               (helper (cdr ntpl) (sub1 n))))))
  (trace helper)
  ;; form an integer as the sum of the
  ;; list values multiplied by their place value.
  (helper ntpl (sub1 (length ntpl))))




      
