package main

import (
	"errors"
	"strconv"
	"strings"
)

type Stack struct {
	data []int
}

func NewStack() *Stack { return &Stack{} }

func (s *Stack) Push(v int) {
	s.data = append(s.data, v)
}

func (s *Stack) Pop() (int, error) {
	if len(s.data) == 0 {
		return 0, errors.New("стек пуст")
	}
	v := s.data[len(s.data)-1]
	s.data = s.data[:len(s.data)-1]
	return v, nil
}

func (s *Stack) String() string {
	parts := make([]string, len(s.data))
	for i, v := range s.data {
		parts[i] = strconv.Itoa(v)
	}
	return strings.Join(parts, " ")
}