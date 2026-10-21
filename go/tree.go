package main

import (
	"errors"
	"fmt"
	"strings"
)

type color bool

const (
	red   color = true
	black color = false
)

type TreeNode struct {
	data               int
	color              color
	left, right, parent *TreeNode
}

type Tree struct {
	root, nilNode *TreeNode
}

func NewTree() *Tree {
	n := &TreeNode{color: black}
	return &Tree{root: n, nilNode: n}
}

func (t *Tree) leftRotate(x *TreeNode) {
	y := x.right
	x.right = y.left
	if y.left != t.nilNode {
		y.left.parent = x
	}
	y.parent = x.parent
	if x.parent == t.nilNode {
		t.root = y
	} else if x == x.parent.left {
		x.parent.left = y
	} else {
		x.parent.right = y
	}
	y.left = x
	x.parent = y
}

func (t *Tree) rightRotate(x *TreeNode) {
	y := x.left
	x.left = y.right
	if y.right != t.nilNode {
		y.right.parent = x
	}
	y.parent = x.parent
	if x.parent == t.nilNode {
		t.root = y
	} else if x == x.parent.right {
		x.parent.right = y
	} else {
		x.parent.left = y
	}
	y.right = x
	x.parent = y
}

func (t *Tree) Add(value int) {
	y := t.nilNode
	x := t.root
	for x != t.nilNode {
		y = x
		if value < x.data {
			x = x.left
		} else if value > x.data {
			x = x.right
		} else {
			return
		}
	}
	z := &TreeNode{data: value, color: red, left: t.nilNode, right: t.nilNode, parent: y}
	if y == t.nilNode {
		t.root = z
	} else if value < y.data {
		y.left = z
	} else {
		y.right = z
	}
	t.insertFixup(z)
}

func (t *Tree) insertFixup(z *TreeNode) {
	for z.parent.color == red {
		if z.parent == z.parent.parent.left {
			y := z.parent.parent.right
			if y.color == red {
				z.parent.color, y.color, z.parent.parent.color = black, black, red
				z = z.parent.parent
			} else {
				if z == z.parent.right {
					z = z.parent
					t.leftRotate(z)
				}
				z.parent.color = black
				z.parent.parent.color = red
				t.rightRotate(z.parent.parent)
			}
		} else {
			y := z.parent.parent.left
			if y.color == red {
				z.parent.color, y.color, z.parent.parent.color = black, black, red
				z = z.parent.parent
			} else {
				if z == z.parent.left {
					z = z.parent
					t.rightRotate(z)
				}
				z.parent.color = black
				z.parent.parent.color = red
				t.leftRotate(z.parent.parent)
			}
		}
	}
	t.root.color = black
}

func (t *Tree) Search(value int) bool {
	x := t.root
	for x != t.nilNode {
		if value == x.data {
			return true
		}
		if value < x.data {
			x = x.left
		} else {
			x = x.right
		}
	}
	return false
}

func (t *Tree) findNode(value int) *TreeNode {
	x := t.root
	for x != t.nilNode {
		if value == x.data {
			return x
		}
		if value < x.data {
			x = x.left
		} else {
			x = x.right
		}
	}
	return nil
}

func (t *Tree) transplant(u, v *TreeNode) {
	if u.parent == t.nilNode {
		t.root = v
	} else if u == u.parent.left {
		u.parent.left = v
	} else {
		u.parent.right = v
	}
	v.parent = u.parent
}

func (t *Tree) minimum(x *TreeNode) *TreeNode {
	for x.left != t.nilNode {
		x = x.left
	}
	return x
}

func (t *Tree) Remove(value int) error {
	z := t.findNode(value)
	if z == nil {
		return errors.New("значение не найдено")
	}
	y := z
	yColor := y.color
	var x *TreeNode
	if z.left == t.nilNode {
		x = z.right
		t.transplant(z, z.right)
	} else if z.right == t.nilNode {
		x = z.left
		t.transplant(z, z.left)
	} else {
		y = t.minimum(z.right)
		yColor = y.color
		x = y.right
		if y.parent == z {
			x.parent = y
		} else {
			t.transplant(y, y.right)
			y.right = z.right
			y.right.parent = y
		}
		t.transplant(z, y)
		y.left = z.left
		y.left.parent = y
		y.color = z.color
	}
	if yColor == black {
		t.deleteFixup(x)
	}
	return nil
}

func (t *Tree) deleteFixup(x *TreeNode) {
	for x != t.root && x.color == black {
		if x == x.parent.left {
			w := x.parent.right
			if w.color == red {
				w.color = black
				x.parent.color = red
				t.leftRotate(x.parent)
				w = x.parent.right
			}
			if w.left.color == black && w.right.color == black {
				w.color = red
				x = x.parent
			} else {
				if w.right.color == black {
					w.left.color = black
					w.color = red
					t.rightRotate(w)
					w = x.parent.right
				}
				w.color = x.parent.color
				x.parent.color = black
				w.right.color = black
				t.leftRotate(x.parent)
				x = t.root
			}
		} else {
			w := x.parent.left
			if w.color == red {
				w.color = black
				x.parent.color = red
				t.rightRotate(x.parent)
				w = x.parent.left
			}
			if w.right.color == black && w.left.color == black {
				w.color = red
				x = x.parent
			} else {
				if w.left.color == black {
					w.right.color = black
					w.color = red
					t.leftRotate(w)
					w = x.parent.left
				}
				w.color = x.parent.color
				x.parent.color = black
				w.left.color = black
				t.rightRotate(x.parent)
				x = t.root
			}
		}
	}
	x.color = black
}

func mark(c color) string {
	if c == red {
		return "К"
	}
	return "Ч"
}

func (t *Tree) preorder(n *TreeNode, res *[]string) {
	if n == t.nilNode {
		return
	}
	*res = append(*res, fmt.Sprintf("%d(%s)", n.data, mark(n.color)))
	t.preorder(n.left, res)
	t.preorder(n.right, res)
}

func (t *Tree) inorder(n *TreeNode, res *[]string) {
	if n == t.nilNode {
		return
	}
	t.inorder(n.left, res)
	*res = append(*res, fmt.Sprintf("%d(%s)", n.data, mark(n.color)))
	t.inorder(n.right, res)
}

func (t *Tree) postorder(n *TreeNode, res *[]string) {
	if n == t.nilNode {
		return
	}
	t.postorder(n.left, res)
	t.postorder(n.right, res)
	*res = append(*res, fmt.Sprintf("%d(%s)", n.data, mark(n.color)))
}

func (t *Tree) Print() string {
	var pre, in, post []string
	t.preorder(t.root, &pre)
	t.inorder(t.root, &in)
	t.postorder(t.root, &post)
	var sb strings.Builder
	sb.WriteString("Прямой обход: " + strings.Join(pre, " ") + "\n")
	sb.WriteString("Симметричный обход: " + strings.Join(in, " ") + "\n")
	sb.WriteString("Обратный обход: " + strings.Join(post, " ") + "\n")
	return sb.String()
}