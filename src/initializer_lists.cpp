#include <vector>
#include <string>

static bool skip_crashes = true;
#define SKIP_COMPILER_CRASHES 1

#define BEGIN_CRASHES_ON(desc) if (!skip_crashes) {
#define END_CRASHES_ON }
#define BEGIN_COMPILER_CRASH_ON(desc) {
#define END_COMPILER_CRASH_ON }

namespace
{

struct A {
        std::string name;
};

struct B {
        std::string name;
        std::vector<A> otherNames;
};

std::string extractor(A value) { return value.name; }

std::string extractorByRef(A const &value) { return value.name; }

size_t extractor2(A value, B collection)
{
        size_t i = 0;
        for (auto const &element : collection.otherNames) {
                if (element.name == value.name) {
                        break;
                }
                i++;
        }

        return i;
}

size_t extractor2ByRef(A const &value, B const &collection)
{
        size_t i = 0;
        for (auto const &element : collection.otherNames) {
                if (element.name == value.name) {
                        break;
                }
                i++;
        }

        return i;
}
}

void test_simple_aggregate()
{
        BEGIN_CRASHES_ON("Visual Studio Express 2013 Update 3")
        {
                auto value = extractor({"Hello, World"});
                printf("should be a greeting: %s\n", value.c_str());
        }
        END_CRASHES_ON;

        {
                auto value = extractorByRef({"Hello, World"});
                printf("should be a greeting: %s\n", value.c_str());
        }

        {
                auto value = extractor(A{"Hello, World"});
                printf("should be a greeting: %s\n", value.c_str());
        }
}

void test_complex_aggregate()
{
        BEGIN_CRASHES_ON("Visual Studio Express 2013 Update 3")
        {
                auto index =
                    extractor2({"b"}, {"collection", {{"a"}, {"b"}, {"c"}}});
                printf("should be 1: %lu\n", index);
        }
        END_CRASHES_ON;

        {
                auto index = extractor2ByRef(
                    {"b"}, {"collection", {{"a"}, {"b"}, {"c"}}});
                printf("should be 1: %lu\n", index);
        }

#if !SKIP_COMPILER_CRASHES
        BEGIN_COMPILER_CRASH_ON("Visual Studio Express 2013 Update 3")
        {
                auto index =
                    extractor2(A{"b"}, {"collection", {{"a"}, {"b"}, {"c"}}});
                printf("should be 1: %lu\n", index);
        }
        END_COMPILER_CRASH_ON;
#endif
}

void test_initializer_lists()
{
        test_simple_aggregate();
        test_complex_aggregate();
}

int main() { test_initializer_lists(); }
