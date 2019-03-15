#lang racket

#|
  CPSC-3740 Assignment 1
  Prof. Howard Cheng
  Gideon Richter
  001181085
  January 21st, 2019
|#

;; Check if two lists are equal
;; Rewritten after submission
;; .parameter x is a list
;; .parameter y is a list
(define myequal2?
  (lambda (x y)
    (cond
      ((one-empty? x y) #f) ; lists are not equal length
      ((both-empty? x y) #t) ; empty lists are equal
      ((one-list? (car x) (car y)) ; they might both be lists
       (cond
         ((both-list? (car x) (car y))
          (cond
            ; check that the first elements are
            ; equal and recurse the rest.
            ((myequal2? (car x) (car y)) (myequal2? (cdr x) (cdr y)))
            (else #f))) ; nested lists are not equal
         (else #f))) ; one is a list and not the other
      ((equal? (car x) (car y))
       ; they are both single elements,
       ; test equal and recurse the rest.
       (myequal2? (cdr x) (cdr y)))
      (else #f))))

;; Check if two lists are equal
;; .parameter x is a list
;; .parameter y is a list
;; .example (myequal? '(1 2 3) '(1 2 3)) => # t
(define (myequal? x y)
  (if (one-empty? x y)
      #f ; lists are not equal length
      (if (both-empty? x y)
          #t ; empty lists are equal

          (if (one-list? (first x) (first y))
              ;; they might both be lists
              (if (both-list? (first x) (first y))
                  ;; check first element of each and recurse
                  (if (myequal? (first x) (first y))
                      (myequal? (rest x) (rest y))
                      #f) ; nested lists are not equal
                  #f) ; one is a list and not the other
              
              ;; neither of them are lists
              ;; check them and recurse the rest
              (if (equal? (first x) (first y))
                  (myequal? (rest x) (rest y))
                  #f)))))

;; Check if one object is empty
;; .parameter x is an object
;; .parameter y is an object
;; .example (one-empty '() '(1 2 3)) => #t
(define (one-empty? x y)
  (xor (null? x) (null? y)))

;; Check if both objects is empty
;; .parameter x is an object
;; .parameter y is an object
;; .example (both-empty '() '()) => #t
(define (both-empty? x y)
  (and (null? x) (null? y)))

;; Check if one object is a list
;; .parameter x is an object
;; .parameter y is an object
;; .example (one-list '(1 2 3) 1) => #t
(define (one-list? x y)
  (or (pair? x)
      (pair? y)))

;; Check if both objects are a list
;; .parameter x is an object
;; .parameter y is an object
;; .example (both-list '(1 8 16) '(1 2 4) => #t
(define (both-list? x y)
  (and (pair? x)
       (pair? y)))
      
(display "PART 1: myequal? tests \n #f, #f, #t, #t\n")
(myequal2? '() '(1)) ; #f
(myequal2? '(1 2 3 4 5 6) '(1 2 3 (4 5 (6)))) ; #f
(myequal2? '((1 2 (3)) 6) '((1 2 (3)) 6)) ; #t
(myequal2? '(1 2 3 (4 5 (6))) '(1 2 3 (4 5 (6)))) ; #t
(display "end myequal? tests\n\n")

;; Check if an object is within a list
;; .parameter x is the object
;; .parameter y is the list
;; .example (mymember? 1 '(1 2 3)) => #t
(define (mymember? x y)
  (cond
    [(null? y) #f]
    [(equal? x (first y)) #t]
    [else (mymember? x (rest y))]))

(display "PART 2: mymember? tests\n #f, #f, #t, #t\n")
(mymember? 1 '()) ; #f
(mymember? '6 '(1 2 3 (4 5 (6)))) ; #f
(mymember? 1 '(1)) ; #t
(mymember? '(4 5 (6)) '(1 2 3 (4 5 (6)))) ; #t
(display "end mymember? tests")

