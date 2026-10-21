package main

import (
	"errors"
	"strings"
)

type Array struct {
	data []string
}

func NewArray() *Array {
	return &Array{data: make([]string, 0)}
}

func (a *Array) Length() int {
	return len(a.data)
}

func (a *Array) Get(index int) (string, error) {
	if index < 0 || index >= len(a.data) {
		return "", errors.New("индекс вне диапазона")
	}
	return a.data[index], nil
}

func (a *Array) Set(index int, value string) error {
	if index < 0 || index >= len(a.data) {
		return errors.New("индекс вне диапазона")
	}
	a.data[index] = value
	return nil
}

func (a *Array) PushBack(value string) {
	a.data = append(a.data, value)
}

func (a *Array) Insert(index int, value string) error {
	if index < 0 || index > len(a.data) {
		return errors.New("индекс вне диапазона")
	}
	a.data = append(a.data, "")
	copy(a.data[index+1:], a.data[index:])
	a.data[index] = value
	return nil
}

func (a *Array) Remove(index int) error {
	if index < 0 || index >= len(a.data) {
		return errors.New("индекс вне диапазона")
	}
	a.data = append(a.data[:index], a.data[index+1:]...)
	return nil
}

func (a *Array) String() string {
	return strings.Join(a.data, " ")
}