package main

import (
	"errors"
	"strings"
)

type SNode struct {
	data string
	next *SNode
}

type SingleList struct {
	head *SNode
}

func NewSingleList() *SingleList { return &SingleList{} }

func (l *SingleList) PushFront(v string) {
	l.head = &SNode{data: v, next: l.head}
}

func (l *SingleList) PushBack(v string) {
	n := &SNode{data: v}
	if l.head == nil {
		l.head = n
		return
	}
	cur := l.head
	for cur.next != nil {
		cur = cur.next
	}
	cur.next = n
}

func (l *SingleList) PushAfter(target, value string) error {
	cur := l.head
	for cur != nil {
		if cur.data == target {
			cur.next = &SNode{data: value, next: cur.next}
			return nil
		}
		cur = cur.next
	}
	return errors.New("цель не найдена")
}

func (l *SingleList) PushBefore(target, value string) error {
	if l.head == nil {
		return errors.New("цель не найдена")
	}
	if l.head.data == target {
		l.head = &SNode{data: value, next: l.head}
		return nil
	}
	cur := l.head
	for cur.next != nil {
		if cur.next.data == target {
			cur.next = &SNode{data: value, next: cur.next}
			return nil
		}
		cur = cur.next
	}
	return errors.New("цель не найдена")
}

func (l *SingleList) PopFront() (string, error) {
	if l.head == nil {
		return "", errors.New("список пуст")
	}
	v := l.head.data
	l.head = l.head.next
	return v, nil
}

func (l *SingleList) PopBack() (string, error) {
	if l.head == nil {
		return "", errors.New("список пуст")
	}
	if l.head.next == nil {
		v := l.head.data
		l.head = nil
		return v, nil
	}
	cur := l.head
	for cur.next.next != nil {
		cur = cur.next
	}
	v := cur.next.data
	cur.next = nil
	return v, nil
}

func (l *SingleList) PopAfter(target string) error {
	cur := l.head
	for cur != nil {
		if cur.data == target {
			if cur.next == nil {
				return errors.New("нет элемента после цели")
			}
			cur.next = cur.next.next
			return nil
		}
		cur = cur.next
	}
	return errors.New("цель не найдена")
}

func (l *SingleList) PopBefore(target string) error {
	if l.head == nil {
		return errors.New("список пуст")
	}
	if l.head.data == target {
		return errors.New("нет элемента перед целью")
	}
	cur := l.head
	for cur.next != nil {
		if cur.next.data == target {
			cur.next = cur.next.next
			return nil
		}
		cur = cur.next
	}
	return errors.New("цель не найдена")
}

func (l *SingleList) DeleteByValue(value string) error {
	if l.head == nil {
		return errors.New("значение не найдено")
	}
	if l.head.data == value {
		l.head = l.head.next
		return nil
	}
	cur := l.head
	for cur.next != nil {
		if cur.next.data == value {
			cur.next = cur.next.next
			return nil
		}
		cur = cur.next
	}
	return errors.New("значение не найдено")
}

func (l *SingleList) Get(index int) (string, error) {
	cur := l.head
	i := 0
	for cur != nil {
		if i == index {
			return cur.data, nil
		}
		cur = cur.next
		i++
	}
	return "", errors.New("индекс вне диапазона")
}

func (l *SingleList) Set(index int, value string) error {
	cur := l.head
	i := 0
	for cur != nil {
		if i == index {
			cur.data = value
			return nil
		}
		cur = cur.next
		i++
	}
	return errors.New("индекс вне диапазона")
}

func (l *SingleList) Insert(index int, value string) error {
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
	cur.next = &SNode{data: value, next: cur.next}
	return nil
}

func (l *SingleList) Size() int {
	n := 0
	for cur := l.head; cur != nil; cur = cur.next {
		n++
	}
	return n
}

func (l *SingleList) String() string {
	var parts []string
	for cur := l.head; cur != nil; cur = cur.next {
		parts = append(parts, cur.data)
	}
	return strings.Join(parts, " -> ")
}