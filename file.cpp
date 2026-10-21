#include "file.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void printHelp() {
    cout << "Формат: КОМАНДА <имя_структуры> [аргументы]" << endl;
    cout << "ARRAY (M..): MPUSH <name> <value> | MINSERT <name> <value> <index>" << endl;
    cout << "             MGET <name> <index> | MSET <name> <value> <index>" << endl;
    cout << "             MDEL <name> <index> | MREMOVE <name> <value> | MSIZE <name>" << endl;
    cout << "SINGLE LIST (SL..): SLPUSHBACK|SLPUSHFRONT <name> <value>" << endl;
    cout << "             SLPUSHAFTER|SLPUSHBEFORE|SLINSERT <name> <value> <target>" << endl;
    cout << "             SLSET <name> <value> <target> | SLGET <name> <value>" << endl;
    cout << "             SLREMOVE <name> <value> | SLSIZE <name>" << endl;
    cout << "             SLPOPBACK|SLPOPFRONT <name>" << endl;
    cout << "             SLPOPAFTER|SLPOPBEFORE <name> <target>" << endl;
    cout << "DOUBLE LIST (DL..): DLPUSHBACK|DLPUSHFRONT <name> <value>" << endl;
    cout << "             DLPUSHAFTER|DLPUSHBEFORE|DLINSERT <name> <value> <target>" << endl;
    cout << "             DLSET <name> <value> <index> | DLGET <name> <index>" << endl;
    cout << "             DLREMOVE <name> <value> | DLSIZE <name>" << endl;
    cout << "             DLPOPBACK|DLPOPFRONT <name>" << endl;
    cout << "             DLPOPAFTER|DLPOPBEFORE <name> <target>" << endl;
    cout << "STACK: SPUSH <name> <value> | SPOP <name>" << endl;
    cout << "QUEUE: QPUSH <name> <value> | QPOP <name>" << endl;
    cout << "TREE: TADD <name> <number> | TDEL <name> <number> | TFIND <name> <number>" << endl;
    cout << "ELSE: PRINT array|slist|dlist|stack|queue|tree <name> | HELP | EXIT" << endl;
}

const string FILE_NAME = "data.txt";

Storage<ArrOfArrays> arrays = {nullptr, 0, 0};
Storage<ArrOfSlists> slists = {nullptr, 0, 0};
Storage<ArrOfDlists> dlists = {nullptr, 0, 0};
Storage<ArrOfStacks> stacks = {nullptr, 0, 0};
Storage<ArrOfQueues> queues = {nullptr, 0, 0};
Storage<ArrOfTrees>  trees  = {nullptr, 0, 0};

template <typename T>
static void regGrow(Storage<T>& r) {
    size_t newCap = r.capacity == 0 ? 4 : r.capacity * 2;
    T* n = new T[newCap];
    for (size_t i = 0; i < r.size; ++i) n[i] = r.items[i];
    delete[] r.items;
    r.items = n;
    r.capacity = newCap;
}

Array* fetchArray(const string& name) {
    for (size_t i = 0; i < arrays.size; ++i)
        if (arrays.items[i].name == name) return arrays.items[i].ptr;

    if (arrays.size == arrays.capacity) regGrow(arrays);

    Array* a = new Array;
    a->data = nullptr;
    a->size = 0;
    a->capacity = 0;

    arrays.items[arrays.size++] = {a, name};
    return a;
}

SingleList* fetchSingleList(const string& name) {
    for (size_t i = 0; i < slists.size; ++i)
        if (slists.items[i].name == name) return slists.items[i].ptr;

    if (slists.size == slists.capacity) regGrow(slists);

    SingleList* s = new SingleList;
    createSList(*s);

    slists.items[slists.size++] = {s, name};
    return s;
}

DoubleList* fetchDoubleList(const string& name) {
    for (size_t i = 0; i < dlists.size; ++i)
        if (dlists.items[i].name == name) return dlists.items[i].ptr;

    if (dlists.size == dlists.capacity) regGrow(dlists);

    DoubleList* d = new DoubleList;
    createDList(*d);

    dlists.items[dlists.size++] = {d, name};
    return d;
}

Stack* fetchStack(const string& name) {
    for (size_t i = 0; i < stacks.size; ++i)
        if (stacks.items[i].name == name) return stacks.items[i].ptr;

    if (stacks.size == stacks.capacity) regGrow(stacks);

    Stack* s = new Stack;
    createStack(s);

    stacks.items[stacks.size++] = {s, name};
    return s;
}

Queue* fetchQueue(const string& name) {
    for (size_t i = 0; i < queues.size; ++i)
        if (queues.items[i].name == name) return queues.items[i].ptr;

    if (queues.size == queues.capacity) regGrow(queues);

    Queue* q = new Queue;
    createQueue(q);

    queues.items[queues.size++] = {q, name};
    return q;
}

TreeNode** fetchTree(const string& name) {
    for (size_t i = 0; i < trees.size; ++i)
        if (trees.items[i].name == name) return trees.items[i].ptr;

    if (trees.size == trees.capacity) regGrow(trees);

    TreeNode** t = new TreeNode*(nullptr);
    trees.items[trees.size++] = {t, name};
    return t;
}

static void destroyTreeRecursive(TreeNode* node) {
    if (!node) return;
    destroyTreeRecursive(node->left);
    destroyTreeRecursive(node->right);
    delete node;
}

static void dumpTreeValues(TreeNode* node, ostream& os) {
    if (!node) return;
    os << node->data << " ";
    dumpTreeValues(node->left, os);
    dumpTreeValues(node->right, os);
}

void SaveAll() {
    ofstream f(FILE_NAME);
    if (!f) return;

    for (size_t i = 0; i < arrays.size; ++i) {
        Array* a = arrays.items[i].ptr;
        f << "ARRAY " << arrays.items[i].name << " " << lengthArray(*a) << "\n";
        for (size_t j = 0; j < lengthArray(*a); ++j) f << getArray(*a, j) << "\n";
    }

    for (size_t i = 0; i < slists.size; ++i) {
        SingleList* s = slists.items[i].ptr;
        int count = 0;
        for (SNode* n = s->head; n; n = n->next) count++;
        f << "FLIST " << slists.items[i].name << " " << count << "\n";
        for (SNode* n = s->head; n; n = n->next) f << n->data << "\n";
    }

    for (size_t i = 0; i < dlists.size; ++i) {
        DoubleList* d = dlists.items[i].ptr;
        int count = 0;
        for (DNode* n = d->head; n; n = n->next) count++;
        f << "DLIST " << dlists.items[i].name << " " << count << "\n";
        for (DNode* n = d->head; n; n = n->next) f << n->data << "\n";
    }

    for (size_t i = 0; i < stacks.size; ++i) {
        Stack* st = stacks.items[i].ptr;
        int count = 0;
        for (StackNode* n = st->head; n; n = n->next) count++;
        f << "STACK " << stacks.items[i].name << " " << count << "\n";
        for (StackNode* n = st->head; n; n = n->next) f << n->value << "\n";
    }

    for (size_t i = 0; i < queues.size; ++i) {
        Queue* q = queues.items[i].ptr;
        int count = 0;
        for (QueueNode* n = q->head; n; n = n->next) count++;
        f << "QUEUE " << queues.items[i].name << " " << count << "\n";
        for (QueueNode* n = q->head; n; n = n->next) f << n->value << "\n";
    }

    for (size_t i = 0; i < trees.size; ++i) {
        TreeNode* r = *trees.items[i].ptr;
        f << "TREE " << trees.items[i].name << " ";
        ostringstream oss;
        dumpTreeValues(r, oss);
        f << oss.str() << "\n";
    }
}

void LoadAll() {
    ifstream f(FILE_NAME);
    if (!f) return;
    string tag, name;
    int count;

    while (f >> tag >> name) {
        if (tag == "TREE") {
            string line; getline(f, line);
            istringstream iss(line);
            int v;
            TreeNode** tree = fetchTree(name);
            while (iss >> v) {
                AddTree(*tree, v);
            }
            continue;
        }

        if (f >> count) {
            f.ignore();
            if (tag == "ARRAY") {
                Array* arr = fetchArray(name);
                for (int i = 0; i < count; ++i) {
                    string s; getline(f, s);
                    push_backArray(*arr, s);
                }
            } else if (tag == "FLIST") {
                SingleList* slist = fetchSingleList(name);
                for (int i = 0; i < count; ++i) {
                    string s; getline(f, s);
                    push_backSList(*slist, s);
                }
            } else if (tag == "DLIST") {
                DoubleList* dlist = fetchDoubleList(name);
                for (int i = 0; i < count; ++i) {
                    string s; getline(f, s);
                    push_backDList(*dlist, s);
                }
            } else if (tag == "STACK") {
                Stack* stack = fetchStack(name);
                string* buf = new string[count > 0 ? count : 1];
                for (int i = 0; i < count; ++i) getline(f, buf[i]);
                for (int i = count - 1; i >= 0; --i) {
                    try { pushStack(stack, stoi(buf[i])); } catch (...) {}
                }
                delete[] buf;
            } else if (tag == "QUEUE") {
                Queue* queue = fetchQueue(name);
                for (int i = 0; i < count; ++i) {
                    string s; getline(f, s);
                    try { pushQueue(queue, stoi(s)); } catch (...) {}
                }
            }
        }
    }
}

void freeEverything() {
    for (size_t i = 0; i < arrays.size; ++i) { killArray(*arrays.items[i].ptr); delete arrays.items[i].ptr; }
    delete[] arrays.items;

    for (size_t i = 0; i < slists.size; ++i) { killSList(*slists.items[i].ptr); delete slists.items[i].ptr; }
    delete[] slists.items;

    for (size_t i = 0; i < dlists.size; ++i) { killDList(*dlists.items[i].ptr); delete dlists.items[i].ptr; }
    delete[] dlists.items;

    for (size_t i = 0; i < stacks.size; ++i) { deleteStack(*stacks.items[i].ptr); delete stacks.items[i].ptr; }
    delete[] stacks.items;

    for (size_t i = 0; i < queues.size; ++i) { freeQueue(*queues.items[i].ptr); delete queues.items[i].ptr; }
    delete[] queues.items;

    for (size_t i = 0; i < trees.size; ++i) { destroyTreeRecursive(*trees.items[i].ptr); delete trees.items[i].ptr; }
    delete[] trees.items;
}