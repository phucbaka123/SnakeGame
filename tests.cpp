#include <iostream>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include "ArrayList.h"
#include "LinkedList.h"
using namespace std;

static int passed = 0;
static int failed = 0;

static void check(bool condition, const string& listName, const string& testName) {
    if (condition) {
        passed++;
        cout << "  [PASS] " << testName << "\n";
    } else {
        failed++;
        cout << "  [FAIL] " << testName << "   <-- (" << listName << ")\n";
    }
}

// True if the list holds exactly the expected values, in order.
template <typename L, typename T>
static bool equals(L& list, initializer_list<T> expected) {
    if (list.getLength() != (int)expected.size()) return false;
    int i = 0;
    for (const T& value : expected) {
        if (!(list.get(i) == value)) return false;
        i++;
    }
    return true;
}

// True if calling f() throws std::out_of_range (and nothing else).
template <typename F>
static bool throwsOutOfRange(F f) {
    try { f(); }
    catch (const out_of_range&) { return true; }
    catch (...) { return false; }
    return false;
}

template <template <typename> class List>
void runAllTests(const string& name) {
    cout << "\n===== " << name << " =====\n";

    // 1. Construct an empty list.
    {
        List<int> list;
        check(list.getLength() == 0, name, "1. Construct an empty list");
    }

    // 2. Insert at the beginning.
    {
        List<int> list;
        list.insert(0, 20);
        list.insert(0, 10);
        check(equals(list, {10, 20}), name, "2. Insert at the beginning");
    }

    // 3. Insert in the middle.
    {
        List<int> list;
        list.insert(0, 10);
        list.insert(1, 30);
        list.insert(1, 20);
        check(equals(list, {10, 20, 30}), name, "3. Insert in the middle");
    }

    // 4. Insert at the end.
    {
        List<int> list;
        list.insert(0, 10);
        list.insert(1, 20);
        list.insert(2, 30);
        check(equals(list, {10, 20, 30}), name, "4. Insert at the end");
    }

    // 5. Remove the first element.
    {
        List<int> list;
        for (int i = 0; i < 4; i++) list.insert(i, (i + 1) * 10);   // 10 20 30 40
        list.remove(0);
        check(equals(list, {20, 30, 40}), name, "5. Remove the first element");
    }

    // 6. Remove a middle element.
    {
        List<int> list;
        for (int i = 0; i < 4; i++) list.insert(i, (i + 1) * 10);
        list.remove(1);
        check(equals(list, {10, 30, 40}), name, "6. Remove a middle element");
    }

    // 7. Remove the last element (and removing down to empty, then reusing).
    {
        List<int> list;
        for (int i = 0; i < 4; i++) list.insert(i, (i + 1) * 10);
        list.remove(3);
        bool ok = equals(list, {10, 20, 30});
        list.remove(2); list.remove(1); list.remove(0);
        ok = ok && list.getLength() == 0;
        list.insert(0, 99);
        ok = ok && equals(list, {99});
        check(ok, name, "7. Remove the last element (down to empty and back)");
    }

    // 8. Access every valid index.
    {
        List<int> list;
        for (int i = 0; i < 25; i++) list.insert(i, i * 3);
        bool ok = true;
        for (int i = 0; i < 25; i++) ok = ok && (list.get(i) == i * 3);
        check(ok, name, "8. Access every valid index");
    }

    // 9. Attempt to access an invalid index.
    {
        List<int> list;
        list.insert(0, 1);
        list.insert(1, 2);
        bool ok = throwsOutOfRange([&] { list.get(-1); })
               && throwsOutOfRange([&] { list.get(2); })
               && throwsOutOfRange([&] { list.get(100); })
               && throwsOutOfRange([&] { list.insert(-1, 5); })
               && throwsOutOfRange([&] { list.insert(3, 5); })
               && throwsOutOfRange([&] { list.remove(-1); })
               && throwsOutOfRange([&] { list.remove(2); });
        List<int> empty;
        ok = ok && throwsOutOfRange([&] { empty.get(0); })
                && throwsOutOfRange([&] { empty.remove(0); });
        ok = ok && equals(list, {1, 2});   // failed operations must not modify the list
        check(ok, name, "9. Invalid index throws out_of_range (get/insert/remove)");
    }

    // 10. Clear an empty list.
    {
        List<int> list;
        list.clear();
        check(list.getLength() == 0, name, "10. Clear an empty list");
    }

    // 11. Clear a nonempty list.
    {
        List<int> list;
        for (int i = 0; i < 15; i++) list.insert(i, i);
        list.clear();
        bool ok = list.getLength() == 0 && throwsOutOfRange([&] { list.get(0); });
        check(ok, name, "11. Clear a nonempty list");
    }

    // 12. Reuse a list after calling clear().
    {
        List<int> list;
        for (int i = 0; i < 15; i++) list.insert(i, i);
        list.clear();
        list.insert(0, 7);
        list.insert(1, 8);
        list.insert(0, 6);
        bool ok = equals(list, {6, 7, 8});
        list.clear();
        list.clear();                         // clearing twice is harmless
        list.insert(0, 1);
        ok = ok && equals(list, {1});
        check(ok, name, "12. Reuse a list after clear()");
    }

    // 13. Trigger multiple array resizes.
    {
        List<int> list;
        const int N = 1000;                   // default capacity is small: many doublings
        for (int i = 0; i < N; i++) list.insert(list.getLength(), i);
        bool ok = list.getLength() == N;
        for (int i = 0; i < N && ok; i++) ok = (list.get(i) == i);
        for (int i = 0; i < N; i++) list.insert(0, -1 - i);   // grow again from the front
        ok = ok && list.getLength() == 2 * N && list.get(0) == -N
                && list.get(N - 1) == -1 && list.get(N) == 0 && list.get(2 * N - 1) == N - 1;
        check(ok, name, "13. Multiple resizes preserve all elements");
    }

    // 14. Copy an empty list.
    {
        List<int> original;
        List<int> copy(original);
        bool ok = copy.getLength() == 0;
        copy.insert(0, 5);                    // copy must be usable
        ok = ok && equals(copy, {5}) && original.getLength() == 0;
        check(ok, name, "14. Copy an empty list");
    }

    // 15. Copy a nonempty list.
    {
        List<int> original;
        for (int i = 0; i < 30; i++) original.insert(i, i * 2);
        List<int> copy(original);
        bool ok = copy.getLength() == 30;      // length (not capacity) must be copied
        for (int i = 0; i < 30 && ok; i++) ok = (copy.get(i) == i * 2);
        check(ok, name, "15. Copy a nonempty list");
    }

    // 16. Modify the original after copying it.
    {
        List<int> original;
        for (int i = 0; i < 5; i++) original.insert(i, i + 1);   // 1 2 3 4 5
        List<int> copy(original);
        original.insert(0, 100);
        original.remove(3);
        original.insert(original.getLength(), 200);
        bool ok = equals(copy, {1, 2, 3, 4, 5});   // copy unaffected (deep copy)
        check(ok, name, "16. Modify original after copying; copy unchanged");
    }

    // 17. Modify the copy without affecting the original.
    {
        List<int> original;
        for (int i = 0; i < 5; i++) original.insert(i, i + 1);
        List<int> copy(original);
        copy.insert(0, 100);
        copy.remove(2);
        copy.clear();
        copy.insert(0, 9);
        bool ok = equals(original, {1, 2, 3, 4, 5}) && equals(copy, {9});
        check(ok, name, "17. Modify copy; original unchanged");
    }

    // 18. Assign one list to another.
    {
        List<int> a;
        List<int> b;
        for (int i = 0; i < 5; i++) a.insert(i, i + 1);          // 1 2 3 4 5
        for (int i = 0; i < 40; i++) b.insert(i, -i);            // bigger, different contents
        b = a;
        bool ok = equals(b, {1, 2, 3, 4, 5});
        b.insert(0, 50);
        a.remove(0);
        ok = ok && equals(a, {2, 3, 4, 5}) && equals(b, {50, 1, 2, 3, 4, 5});   // independent
        List<int> chained1, chained2, empty;                     // chained + empty assignment
        chained1 = chained2 = a;
        ok = ok && equals(chained1, {2, 3, 4, 5}) && equals(chained2, {2, 3, 4, 5});
        chained1 = empty;
        ok = ok && chained1.getLength() == 0 && equals(chained2, {2, 3, 4, 5});
        List<int>& alias = a;                                    // self-assignment
        a = alias;
        ok = ok && equals(a, {2, 3, 4, 5});
        a.insert(0, 1);
        ok = ok && equals(a, {1, 2, 3, 4, 5});                   // still valid afterwards
        check(ok, name, "18. Assignment (deep, chained, empty, self-assignment)");
    }

    // 19. Destroy a nonempty list (run under ASan/valgrind to confirm no leaks).
    {
        List<int>* list = new List<int>();
        for (int i = 0; i < 100; i++) list->insert(i, i);
        delete list;
        List<string> strings;                  // non-trivial element type, also deep-copied
        strings.insert(0, "snake");
        strings.insert(1, "food");
        List<string> stringCopy(strings);
        strings.remove(0);
        check(equals(stringCopy, {string("snake"), string("food")}) &&
              equals(strings, {string("food")}),
              name, "19. Destroy nonempty lists / non-trivial element type");
    }
}

int main() {
    runAllTests<ArrayList>("ArrayList");
    runAllTests<LinkedList>("LinkedList");

    cout << "\n=============================\n";
    cout << "Passed: " << passed << "   Failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}