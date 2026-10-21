#ifndef FILE_H
#define FILE_H
#include <string>

#include "command.h"
#include "structs/array.h"
#include "structs/flist.h"
#include "structs/doubleList.h"
#include "structs/stack.h"
#include "structs/queue.h"
#include "structs/redBlackTree.h"

void printHelp();

extern const std::string FILE_NAME;

struct ArrOfArrays { Array*      ptr; std::string name; };
struct ArrOfSlists { SingleList* ptr; std::string name; };
struct ArrOfDlists { DoubleList* ptr; std::string name; };
struct ArrOfStacks { Stack*      ptr; std::string name; };
struct ArrOfQueues { Queue*      ptr; std::string name; };
struct ArrOfTrees  { TreeNode**  ptr; std::string name; };

template <typename T>
struct Storage {
    T* items;
    size_t size;
    size_t capacity;
};

extern Storage<ArrOfArrays> arrays;
extern Storage<ArrOfSlists> slists;
extern Storage<ArrOfDlists> dlists;
extern Storage<ArrOfStacks> stacks;
extern Storage<ArrOfQueues> queues;
extern Storage<ArrOfTrees>  trees;

Array*      fetchArray(const std::string& name);
SingleList* fetchSingleList(const std::string& name);
DoubleList* fetchDoubleList(const std::string& name);
Stack*      fetchStack(const std::string& name);
Queue*      fetchQueue(const std::string& name);
TreeNode**  fetchTree(const std::string& name);

void SaveAll();
void LoadAll();

void freeEverything();

#endif