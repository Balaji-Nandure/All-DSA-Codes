// Problem: Why Strings are Immutable in Java? (Core Concept & Architectural Deep Dive)
// Link: NA (Classic Java & Language Architecture Interview Question)
// Article: https://www.geeksforgeeks.org/java/java-string-is-immutable-what-exactly-is-the-meaning/
// Difficulty: Conceptual / Technical Interview Core
// Topic: Memory Architecture, String Constant Pool, Thread Safety, Security, HashCode Caching

/*
Problem Statement:
Explain why the `String` class in Java is designed to be immutable (i.e. once created, 
its character sequence cannot be changed). What architectural benefits does immutability 
provide, what are the potential performance trade-offs, and how is mutable string manipulation 
handled when needed?

Also contrast Java's String model with C++'s `std::string` and `std::string_view`.
*/

// =============================================================================
// HOW THIS DIFFERS FROM REGULAR CODING QUESTIONS:
// =============================================================================
// - This is a conceptual system design & programming language theory question.
// - It tests your understanding of:
//     1. Heap vs Stack Memory & String Constant Pool (SCP).
//     2. Concurrency & Thread Safety without locking overhead.
//     3. System Security (Network Sockets, File Paths, Database URLs, Classloading).
//     4. Caching & Fast Hash Table lookups (`hashCode()` memoization).

// =============================================================================
// 5 CORE ARCHITECTURAL REASONS WHY STRINGS ARE IMMUTABLE:
// =============================================================================
// 1. String Constant Pool (SCP) / Memory Optimization:
//    - If strings were mutable, multiple reference variables pointing to the same literal
//      in the pool would suffer catastrophic side-effects:
//      E.g., `String s1 = "Apple"; String s2 = "Apple";` (both point to the same memory).
//      If `s1` could modify "Apple" to "Pear", `s2`'s value would silently corrupt!
//    - Immutability guarantees that shared literals in the pool remain universally safe.
//
// 2. Security & System Integrity:
//    - Strings are ubiquitous in security-sensitive operations: file paths, network connections,
//      database connection strings, and ClassLoader parameters.
//    - If a method checks a file path for authorization, a malicious background thread could
//      mutate the string *after* the check but *before* execution (Time-of-Check to Time-of-Use / TOCTOU vulnerability).
//    - Immutability eliminates this entire class of security exploits.
//
// 3. Thread Safety (Zero Synchronization Overhead):
//    - Immutable objects are inherently thread-safe. Multiple threads can read the same String
//      instance concurrently without any locks, mutexes, or synchronization penalties.
//
// 4. HashCode Caching (Hash-based Collections Optimization):
//    - Strings are the most common keys in `HashMap`, `HashSet`, and `Hashtable`.
//    - In Java's `String`, `hash` is computed lazily once and cached in a private field.
//    - Because the string never changes, the cached hashcode is guaranteed to remain invariant.
//    - If strings were mutable, mutating a key inside a HashMap would change its bucket, 
//      making the entry permanently lost / unretrievable!
//
// 5. Class Loading Mechanism:
//    - The JVM uses strings as arguments to load classes (e.g., `"java.sql.Connection"`).
//    - Immutability prevents tampering with class names during runtime dynamic loading.

// =============================================================================
// COMPARISON: JAVA VS C++ STRING MODELS:
// =============================================================================
// | Feature             | Java `String`              | C++ `std::string`          |
// |---------------------|----------------------------|----------------------------|
// | Mutability          | Strictly Immutable         | Mutable by default         |
// | Modification        | Creates a new String object| Modifies buffer in-place   |
// | Mutable Alternative | `StringBuilder` / `StringBuffer` | N/A (Already mutable) |
// | Constant / View     | Standard `String`          | `const std::string&`, `std::string_view` |
// | Interning Pool      | Built-in JVM String Pool   | None (developer managed)   |

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;

// =============================================================================
// C++ SIMULATION: Demonstrating String Pooling & Why Immutability is Essential
// =============================================================================

// Simulated Immutable String class with cached hash code (like Java's String)
class JavaStyleImmutableString {
private:
    const string data;
    mutable size_t cachedHash;
    mutable bool hashComputed;

public:
    JavaStyleImmutableString(string val) 
        : data(std::move(val)), cachedHash(0), hashComputed(false) {}

    const string& get() const { return data; }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Hash code is computed once and permanently cached. Safe ONLY because `data` is immutable!
    size_t hashCode() const {
        if (!hashComputed) {
            cachedHash = hash<string>{}(data);
            hashComputed = true;
        }
        return cachedHash;
    }

    bool operator==(const JavaStyleImmutableString& other) const {
        return data == other.data;
    }
};

// Simulated String Constant Pool
class StringConstantPool {
private:
    unordered_map<string, shared_ptr<JavaStyleImmutableString>> pool;

public:
    shared_ptr<JavaStyleImmutableString> intern(const string& text) {
        if (pool.find(text) == pool.end()) {
            pool[text] = make_shared<JavaStyleImmutableString>(text);
        }
        return pool[text];
    }
};

int main() {
    StringConstantPool scp;

    // Both s1 and s2 reference the EXACT SAME underlying memory instance
    auto s1 = scp.intern("Antigravity");
    auto s2 = scp.intern("Antigravity");

    cout << "=== Why Strings are Immutable in Java ===\n\n";
    cout << "s1 memory address: " << s1.get() << "\n";
    cout << "s2 memory address: " << s2.get() << "\n";
    cout << "Are s1 and s2 sharing the exact same pointer? " 
         << (s1.get() == s2.get() ? "YES (Shared via String Pool)" : "NO") << "\n\n";

    cout << "If s1 were allowed to mutate, s2 would simultaneously be corrupted!\n";
    cout << "Cached HashCode for s1: " << s1->hashCode() << "\n";
    cout << "Cached HashCode for s2: " << s2->hashCode() << " (Zero recalculation needed!)\n\n";

    cout << "Summary of Key Reasons:\n";
    cout << "1. String Constant Pool (Memory sharing across references)\n";
    cout << "2. Security (Network URLs, File Paths cannot be hijacked via TOCTOU)\n";
    cout << "3. Thread-Safety (Lock-free concurrent reads across threads)\n";
    cout << "4. HashCode Caching (High-performance HashMap and HashSet key lookups)\n";
    cout << "5. ClassLoader Security (Class names cannot be modified during loading)\n";

    return 0;
}

/*
Complexity & Memory Considerations:
- String concatenation in a loop:
  * Using `String` + operator in Java: O(N^2) time because every `+` copies the entire prefix.
  * Correct practice: Use `StringBuilder` (single mutable buffer, O(N) amortized).
- C++ equivalent:
  * `std::string` can append in-place with `+=` or `push_back()` in O(1) amortized.
*/
