#lang racket

(define regroup
  (lambda (list-of-four)
    (make-list-of-two
     (first-group list-of-four)
     (second-group list-of-four))))

(define make-list-of-two
  (lambda (item1 item2)
    (cons item1 (make-list-of-one item2))))

(define make-list-of-three
  (lambda (item1 item2 item3)
    (cons item1 (make-list-of-two item2 item3))))

(define make-list-of-one
  (lambda (item)
    (cons item '())))

(define first-group
  (lambda (list-of-four)
    (make-list-of-two
     (car list-of-four)
     (cadr list-of-four))))

(define second-group
  (lambda (list-of-four)
    (cddr list-of-four)))

(define menu
  '(chicken soup ice cream))

(define second
  (lambda (ls)
    (cadr ls)))

(define third
  (lambda (ls)
    (caddr ls)))

(define firsts-of-both
  (lambda (list-1 list-2)
    (make-list-of-two
     (car list-1)
     (car list-2))))

(define juggle ; move each element of the list to the next index
  (lambda (ls)
    (make-list-of-three
     (third ls)
     (car ls)
     (second ls))))

(define switch ; swap the first and third elements of list
  (lambda (ls)
    (make-list-of-three
     (third ls)
     (second ls)
     (car ls))))
