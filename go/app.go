package main

type App struct {
	arrays *Registry[Array]
	slists *Registry[SingleList]
	dlists *Registry[DoubleList]
	stacks *Registry[Stack]
	queues *Registry[Queue]
	trees  *Registry[Tree]
}

func NewApp() *App {
	return &App{
		arrays: NewRegistry[Array](),
		slists: NewRegistry[SingleList](),
		dlists: NewRegistry[DoubleList](),
		stacks: NewRegistry[Stack](),
		queues: NewRegistry[Queue](),
		trees:  NewRegistry[Tree](),
	}
}

func (app *App) Array(name string) *Array {
	a, ok := app.arrays.Get(name)
	if !ok {
		a = NewArray()
		app.arrays.Set(name, a)
	}
	return a
}

func (app *App) SList(name string) *SingleList {
	l, ok := app.slists.Get(name)
	if !ok {
		l = NewSingleList()
		app.slists.Set(name, l)
	}
	return l
}

func (app *App) DList(name string) *DoubleList {
	l, ok := app.dlists.Get(name)
	if !ok {
		l = NewDoubleList()
		app.dlists.Set(name, l)
	}
	return l
}

func (app *App) StackByName(name string) *Stack {
	s, ok := app.stacks.Get(name)
	if !ok {
		s = NewStack()
		app.stacks.Set(name, s)
	}
	return s
}

func (app *App) QueueByName(name string) *Queue {
	q, ok := app.queues.Get(name)
	if !ok {
		q = NewQueue()
		app.queues.Set(name, q)
	}
	return q
}

func (app *App) TreeByName(name string) *Tree {
	t, ok := app.trees.Get(name)
	if !ok {
		t = NewTree()
		app.trees.Set(name, t)
	}
	return t
}