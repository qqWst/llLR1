package main

import (
	"errors"
	"strconv"
	"strings"
)

type Queue struct {
	data []int
}

func NewQueue() *Queue { return &Queue{} }

func (q *Queue) Push(v int) {
	q.data = append(q.data, v)
}

func (q *Queue) Pop() (int, error) {
	if len(q.data) == 0 {
		return 0, errors.New("очередь пуста")
	}
	v := q.data[0]
	q.data = q.data[1:]
	return v, nil
}

func (q *Queue) String() string {
	parts := make([]string, len(q.data))
	for i, v := range q.data {
		parts[i] = strconv.Itoa(v)
	}
	return strings.Join(parts, " ")
}