#lang racket

(define (make-rtl x y)
  ;; create a representation of a real number
  ;; in this case, it is represented as a pair.
  (if (zero? y)
      (error "make-rtl: denominator cannot be 0")
      (cons x y)))

(define (numr rtl)
  ;; Return the numerator of a real number
  (car rtl))

(define (denr rtl)
  ;; Return the denominator of a rational number
  (cdr rtl))

(define (r+ x y)
  ;; Add two rational numbers
  (make-rtl
   (+ (* (numr x) (denr y))
      (* (denr x) (numr y)))
   (* (denr x) (denr y))))

(define (r* x y)
  ;; Multiply to rational numbers
  (make-rtl
   (* (numr x) (numr y))
   (* (denr x) (denr y))))

(define (rminus x)
  ;; Take in a rational number and return the
  ;; negative
  (make-rtl
   (+ (numr x) (* -2 (numr x)))
   (denr x)))

(define (rpositive? x)
  ;; assert that a rational number is positive
  (same-sign? (numr x) (denr x)))

(define (same-sign? x y)
  ;; assert that two numbers have both the same sign
  (or (and (positive? x) (positive? y))
      (and (negative? x) (negative? y))))

(define (rabs x)
  ;; return the absolute value of a rational number
  (if (rpositive? x)
      x
      ;; else multiply it by negative 1
      (r* x
          (make-rtl -1 1))))

(define (=make-rtl= x y)
  ;; see make-rtl,
  ;; this one returns the number
  ;; reduced to lowest terms
  (cons (/ x (gcd x y))
        (/ y (gcd x y))))
