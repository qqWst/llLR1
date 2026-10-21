package main

type Registry[T any] struct {
	items map[string]*T
}

func NewRegistry[T any]() *Registry[T] {
	return &Registry[T]{items: make(map[string]*T)}
}

func (r *Registry[T]) Get(name string) (*T, bool) {
	v, ok := r.items[name]
	return v, ok
}

func (r *Registry[T]) Set(name string, v *T) {
	r.items[name] = v
}

func (r *Registry[T]) Delete(name string) {
	delete(r.items, name)
}