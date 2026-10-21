package main

import (
	"errors"
	"strings"
)

type DNode struct {
	data       string
	next, prev *DNode
}

type DoubleList struct {
	head, tail *DNode
}

func NewDoubleList() *DoubleList { return &DoubleList{} }

func (l *DoubleList) PushFront(v string) {
	n := &DNode{data: v}
	if l.head == nil {
		l.head, l.tail = n, n
		return
	}
	n.next = l.head
	l.head.prev = n
	l.head = n
}

func (l *DoubleList) PushBack(v string) {
	n := &DNode{data: v}
	if l.tail == nil {
		l.head, l.tail = n, n
		return
	}
	n.prev = l.tail
	l.tail.next = n
	l.tail = n
}

func (l *DoubleList) PushAfter(target, value string) error {
	for cur := l.head; cur != nil; cur = cur.next {
		if cur.data == target {
			n := &DNode{data: value, prev: cur, next: cur.next}
			if cur.next != nil {
				cur.next.prev = n
			} else {
				l.tail = n
			}
			cur.next = n
			return nil
		}
	}
	return errors.New("цель не найдена")
}

func (l *DoubleList) PushBefore(target, value string) error {
	for cur := l.head; cur != nil; cur = cur.next {
		if cur.data == target {
			n := &DNode{data: value, next: cur, prev: cur.prev}
			if cur.prev != nil {
				cur.prev.next = n
			} else {
				l.head = n
			}
			cur.prev = n
			return nil
		}
	}
	return errors.New("цель не найдена")
}

func (l *DoubleList) PopFront() (string, error) {
	if l.head == nil {
		return "", errors.New("список пуст")
	}
	v := l.head.data
	l.head = l.head.next
	if l.head != nil {
		l.head.prev = nil
	} else {
		l.tail = nil
	}
	return v, nil
}

func (l *DoubleList) PopBack() (string, error) {
	if l.tail == nil {
		return "", errors.New("список пуст")
	}
	v := l.tail.data
	l.tail = l.tail.prev
	if l.tail != nil {
		l.tail.next = nil
	} else {
		l.head = nil
	}
	return v, nil
}

func (l *DoubleList) PopAfter(target string) error {
	for cur := l.head; cur != nil; cur = cur.next {
		if cur.data == target {
			if cur.next == nil {
				return errors.New("нет элемента после цели")
			}
			next := cur.next
			cur.next = next.next
			if next.next != nil {
				next.next.prev = cur
			} else {
				l.tail = cur
			}
			return nil
		}
	}
	return errors.New("цель не найдена")
}

func (l *DoubleList) PopBefore(target string) error {
	for cur := l.head; cur != nil; cur = cur.next {
		if cur.data == target {
			if cur.prev == nil {
				return errors.New("нет элемента перед целью")
			}
			prev := cur.prev
			cur.prev = prev.prev
			if prev.prev != nil {
				prev.prev.next = cur
			} else {
				l.head = cur
			}
			return nil
		}
	}
	return errors.New("цель не найдена")
}

func (l *DoubleList) DeleteByValue(value string) error {
	for cur := l.head; cur != nil; cur = cur.next {
		if cur.data == value {
			if cur.prev != nil {
				cur.prev.next = cur.next
			} else {
				l.head = cur.next
			}
			if cur.next != nil {
				cur.next.prev = cur.prev
			} else {
				l.tail = cur.prev
			}
			return nil
		}
	}
	return errors.New("значение не найдено")
}

func (l *DoubleList) Get(index int) (string, error) {
	if index < 0 {
		return "", errors.New("индекс вне диапазона")
	}
	i := 0
	for cur := l.head; cur != nil; cur = cur.next {
		if i == index {
			return cur.data, nil
		}
		i++
	}
	return "", errors.New("индекс вне диапазона")
}

func (l *DoubleList) Set(index int, value string) error {
	if index < 0 {
		return errors.New("индекс вне диапазона")
	}
	i := 0
	for cur := l.head; cur != nil; cur = cur.next {
		if i == index {
			cur.data = value
			return nil
		}
		i++
	}
	return errors.New("индекс вне диапазона")
}

func (l *DoubleList) Insert(index int, value string) error {
	if index == 0 {
		l.PushFront(value)
		return nil
	}
	cur := l.head
	i := 0
	for cur != nil && i < index-1 {
		cur = cur.next
		i++
	}
	if cur == nil {
		return errors.New("индекс вне диапазона")
	}
	if cur == l.tail {
		l.PushBack(value)
		return nil
	}
	n := &DNode{data: value, prev: cur, next: cur.next}
	cur.next.prev = n
	cur.next = n
	return nil
}

func (l *DoubleList) Size() int {
	n := 0
	for cur := l.head; cur != nil; cur = cur.next {
		n++
	}
	return n
}

func (l *DoubleList) String() string {
	var parts []string
	for cur := l.head; cur != nil; cur = cur.next {
		parts = append(parts, cur.data)
	}
	return strings.Join(parts, " <-> ")
}