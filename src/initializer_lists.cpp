#include <vector>
#include <string>

static bool skip_crashes = false;
#define SKIP_COMPILER_CRASHES 0

#define BEGIN_CRASHES_ON(desc) if (!skip_crashes) {
#define END_CRASHES_ON }
#define BEGIN_COMPILER_CRASH_ON(desc) {
#define END_COMPILER_CRASH_ON }

struct A
{
        std::string name;
};

struct B
{
        std::string name;
        std::vector<A> otherNames;
};

std::string extractor(A value)
{
        return value.name;
}

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

void test_initializer_lists()
{
        BEGIN_CRASHES_ON("Visual Studio Express 2013 Update 3")
        {
                auto value = extractor({ "Hello, World" });
                printf("should be a greeting: %s\n", value.c_str());
        }
        END_CRASHES_ON;

        {
                auto value = extractor(A{ "Hello, World" });
                printf("should be a greeting: %s\n", value.c_str());
        }

        BEGIN_CRASHES_ON("Visual Studio Express 2013 Update 3")
        {
                auto index = extractor2(
                    { "b" }, { "collection", { { "a" }, { "b" }, { "c" } } });
                printf("should be 1: %lu\n", index);
        }
        END_CRASHES_ON;

#if !SKIP_COMPILER_CRASHES
        BEGIN_COMPILER_CRASH_ON("Visual Studio Express 2013 Update 3")
        {
                auto index = extractor2(
                    A{ "b" }, { "collection", { { "a" }, { "b" }, { "c" } } });
                printf("should be 1: %lu\n", index);
        }
        END_COMPILER_CRASH_ON;
#endif
}

int main()
{
        test_initializer_lists();
}
