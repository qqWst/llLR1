package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	app := NewApp()
	scanner := bufio.NewScanner(os.Stdin)

	fmt.Println("Abstract Data Structures (Go). Введите HELP для справки.")

	for {
		fmt.Print("> ")
		if !scanner.Scan() {
			break
		}
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}
		tokens := strings.Fields(line)
		cmd := getCommand(tokens[0])
		args := tokens[1:]

		switch cmd {

		case MPUSH:
			if len(args) < 2 {
				fmt.Println("Использование: MPUSH <имя> <значение>")
				break
			}
			app.Array(args[0]).PushBack(strings.Join(args[1:], " "))

		case SLPUSHBACK:
			if len(args) < 2 {
				fmt.Println("Использование: SLPUSHBACK <имя> <значение>")
				break
			}
			app.SList(args[0]).PushBack(strings.Join(args[1:], " "))

		case DLPUSHBACK:
			if len(args) < 2 {
				fmt.Println("Использование: DLPUSHBACK <имя> <значение>")
				break
			}
			app.DList(args[0]).PushBack(strings.Join(args[1:], " "))

		case SPUSH:
			if len(args) != 2 {
				fmt.Println("Использование: SPUSH <имя> <значение>")
				break
			}
			v, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: значение должно быть целым числом")
				break
			}
			app.StackByName(args[0]).Push(v)

		case QPUSH:
			if len(args) != 2 {
				fmt.Println("Использование: QPUSH <имя> <значение>")
				break
			}
			v, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: значение должно быть целым числом")
				break
			}
			app.QueueByName(args[0]).Push(v)

		case TADD:
			if len(args) != 2 {
				fmt.Println("Использование: TADD <имя> <значение>")
				break
			}
			v, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: значение должно быть целым числом")
				break
			}
			app.TreeByName(args[0]).Add(v)

		case SLPUSHFRONT:
			if len(args) < 2 {
				fmt.Println("Использование: SLPUSHFRONT <имя> <значение>")
				break
			}
			app.SList(args[0]).PushFront(strings.Join(args[1:], " "))

		case DLPUSHFRONT:
			if len(args) < 2 {
				fmt.Println("Использование: DLPUSHFRONT <имя> <значение>")
				break
			}
			app.DList(args[0]).PushFront(strings.Join(args[1:], " "))

		case SLPUSHAFTER:
			if len(args) < 3 {
				fmt.Println("Использование: SLPUSHAFTER <имя> <цель> <значение>")
				break
			}
			if err := app.SList(args[0]).PushAfter(args[1], strings.Join(args[2:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case DLPUSHAFTER:
			if len(args) < 3 {
				fmt.Println("Использование: DLPUSHAFTER <имя> <цель> <значение>")
				break
			}
			if err := app.DList(args[0]).PushAfter(args[1], strings.Join(args[2:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case SLPUSHBEFORE:
			if len(args) < 3 {
				fmt.Println("Использование: SLPUSHBEFORE <имя> <цель> <значение>")
				break
			}
			if err := app.SList(args[0]).PushBefore(args[1], strings.Join(args[2:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case DLPUSHBEFORE:
			if len(args) < 3 {
				fmt.Println("Использование: DLPUSHBEFORE <имя> <цель> <значение>")
				break
			}
			if err := app.DList(args[0]).PushBefore(args[1], strings.Join(args[2:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case MSET:
			if len(args) < 3 {
				fmt.Println("Использование: MSET <имя> <индекс> <значение>")
				break
			}
			idx, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть целым числом")
				break
			}
			if err := app.Array(args[0]).Set(idx, strings.Join(args[2:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case SLSET:
			if len(args) < 3 {
				fmt.Println("Использование: SLSET <имя> <индекс> <значение>")
				break
			}
			idx, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть целым числом")
				break
			}
			if err := app.SList(args[0]).Set(idx, strings.Join(args[2:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case DLSET:
			if len(args) < 3 {
				fmt.Println("Использование: DLSET <имя> <индекс> <значение>")
				break
			}
			idx, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть целым числом")
				break
			}
			if err := app.DList(args[0]).Set(idx, strings.Join(args[2:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case MGET:
			if len(args) != 2 {
				fmt.Println("Использование: MGET <имя> <индекс>")
				break
			}
			idx, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть целым числом")
				break
			}
			v, err := app.Array(args[0]).Get(idx)
			if err != nil {
				fmt.Println("Ошибка:", err)
				break
			}
			fmt.Println(v)

		case SLGET:
			if len(args) != 2 {
				fmt.Println("Использование: SLGET <имя> <индекс>")
				break
			}
			idx, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть целым числом")
				break
			}
			v, err := app.SList(args[0]).Get(idx)
			if err != nil {
				fmt.Println("Ошибка:", err)
				break
			}
			fmt.Println(v)

		case DLGET:
			if len(args) != 2 {
				fmt.Println("Использование: DLGET <имя> <индекс>")
				break
			}
			idx, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть целым числом")
				break
			}
			v, err := app.DList(args[0]).Get(idx)
			if err != nil {
				fmt.Println("Ошибка:", err)
				break
			}
			fmt.Println(v)

		case TFIND:
			if len(args) != 2 {
				fmt.Println("Использование: TFIND <имя> <значение>")
				break
			}
			v, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: значение должно быть целым числом")
				break
			}
			if app.TreeByName(args[0]).Search(v) {
				fmt.Println("Найдено")
			} else {
				fmt.Println("Не найдено")
			}

		case MREMOVE:
			if len(args) != 2 {
				fmt.Println("Использование: MREMOVE <имя> <индекс>")
				break
			}
			idx, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть целым числом")
				break
			}
			if err := app.Array(args[0]).Remove(idx); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case SLREMOVE:
			if len(args) < 2 {
				fmt.Println("Использование: SLREMOVE <имя> <значение>")
				break
			}
			if err := app.SList(args[0]).DeleteByValue(strings.Join(args[1:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case DLREMOVE:
			if len(args) < 2 {
				fmt.Println("Использование: DLREMOVE <имя> <значение>")
				break
			}
			if err := app.DList(args[0]).DeleteByValue(strings.Join(args[1:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case MINSERT:
			if len(args) < 3 {
				fmt.Println("Использование: MINSERT <имя> <индекс> <значение>")
				break
			}
			idx, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть целым числом")
				break
			}
			if err := app.Array(args[0]).Insert(idx, strings.Join(args[2:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case SLINSERT:
			if len(args) < 3 {
				fmt.Println("Использование: SLINSERT <имя> <индекс> <значение>")
				break
			}
			idx, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть целым числом")
				break
			}
			if err := app.SList(args[0]).Insert(idx, strings.Join(args[2:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case DLINSERT:
			if len(args) < 3 {
				fmt.Println("Использование: DLINSERT <имя> <индекс> <значение>")
				break
			}
			idx, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть целым числом")
				break
			}
			if err := app.DList(args[0]).Insert(idx, strings.Join(args[2:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case MSIZE:
			if len(args) != 1 {
				fmt.Println("Использование: MSIZE <имя>")
				break
			}
			fmt.Println(app.Array(args[0]).Length())

		case SLSIZE:
			if len(args) != 1 {
				fmt.Println("Использование: SLSIZE <имя>")
				break
			}
			fmt.Println(app.SList(args[0]).Size())

		case DLSIZE:
			if len(args) != 1 {
				fmt.Println("Использование: DLSIZE <имя>")
				break
			}
			fmt.Println(app.DList(args[0]).Size())

		case MDEL:
			if len(args) != 1 {
				fmt.Println("Использование: MDEL <имя>")
				break
			}
			app.arrays.Delete(args[0])

		case TDEL:
			if len(args) != 1 {
				fmt.Println("Использование: TDEL <имя>")
				break
			}
			app.trees.Delete(args[0])

		case SLPOPBACK:
			if len(args) != 1 {
				fmt.Println("Использование: SLPOPBACK <имя>")
				break
			}
			v, err := app.SList(args[0]).PopBack()
			if err != nil {
				fmt.Println("Ошибка:", err)
				break
			}
			fmt.Println(v)

		case DLPOPBACK:
			if len(args) != 1 {
				fmt.Println("Использование: DLPOPBACK <имя>")
				break
			}
			v, err := app.DList(args[0]).PopBack()
			if err != nil {
				fmt.Println("Ошибка:", err)
				break
			}
			fmt.Println(v)

		case SPOP:
			if len(args) != 1 {
				fmt.Println("Использование: SPOP <имя>")
				break
			}
			v, err := app.StackByName(args[0]).Pop()
			if err != nil {
				fmt.Println("Ошибка:", err)
				break
			}
			fmt.Println(v)

		case QPOP:
			if len(args) != 1 {
				fmt.Println("Использование: QPOP <имя>")
				break
			}
			v, err := app.QueueByName(args[0]).Pop()
			if err != nil {
				fmt.Println("Ошибка:", err)
				break
			}
			fmt.Println(v)

		case SLPOPFRONT:
			if len(args) != 1 {
				fmt.Println("Использование: SLPOPFRONT <имя>")
				break
			}
			v, err := app.SList(args[0]).PopFront()
			if err != nil {
				fmt.Println("Ошибка:", err)
				break
			}
			fmt.Println(v)

		case DLPOPFRONT:
			if len(args) != 1 {
				fmt.Println("Использование: DLPOPFRONT <имя>")
				break
			}
			v, err := app.DList(args[0]).PopFront()
			if err != nil {
				fmt.Println("Ошибка:", err)
				break
			}
			fmt.Println(v)

		case SLPOPAFTER:
			if len(args) < 2 {
				fmt.Println("Использование: SLPOPAFTER <имя> <цель>")
				break
			}
			if err := app.SList(args[0]).PopAfter(strings.Join(args[1:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case DLPOPAFTER:
			if len(args) < 2 {
				fmt.Println("Использование: DLPOPAFTER <имя> <цель>")
				break
			}
			if err := app.DList(args[0]).PopAfter(strings.Join(args[1:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case SLPOPBEFORE:
			if len(args) < 2 {
				fmt.Println("Использование: SLPOPBEFORE <имя> <цель>")
				break
			}
			if err := app.SList(args[0]).PopBefore(strings.Join(args[1:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case DLPOPBEFORE:
			if len(args) < 2 {
				fmt.Println("Использование: DLPOPBEFORE <имя> <цель>")
				break
			}
			if err := app.DList(args[0]).PopBefore(strings.Join(args[1:], " ")); err != nil {
				fmt.Println("Ошибка:", err)
			}

		case PRINT:
			if len(args) != 2 {
				fmt.Println("Использование: PRINT <тип> <имя>")
				break
			}
			printStructure(app, args[0], args[1])

		case HELP:
			printHelp()

		case EXIT:
			fmt.Println("Выход.")
			return

		default:
			fmt.Println("Неизвестная команда. Введите HELP для справки.")
		}
	}
}

func printStructure(app *App, kind, name string) {
	switch strings.ToUpper(kind) {
	case "ARRAY", "M":
		a, ok := app.arrays.Get(name)
		if !ok {
			fmt.Println("Массив не найден")
			return
		}
		fmt.Println(a.String())
	case "SLIST", "SL":
		l, ok := app.slists.Get(name)
		if !ok {
			fmt.Println("Список не найден")
			return
		}
		fmt.Println(l.String())
	case "DLIST", "DL":
		l, ok := app.dlists.Get(name)
		if !ok {
			fmt.Println("Список не найден")
			return
		}
		fmt.Println(l.String())
	case "STACK", "S":
		s, ok := app.stacks.Get(name)
		if !ok {
			fmt.Println("Стек не найден")
			return
		}
		fmt.Println(s.String())
	case "QUEUE", "Q":
		q, ok := app.queues.Get(name)
		if !ok {
			fmt.Println("Очередь не найдена")
			return
		}
		fmt.Println(q.String())
	case "TREE", "T":
		t, ok := app.trees.Get(name)
		if !ok {
			fmt.Println("Дерево не найдено")
			return
		}
		fmt.Print(t.Print())
	default:
		fmt.Println("Неизвестный тип структуры")
	}
}