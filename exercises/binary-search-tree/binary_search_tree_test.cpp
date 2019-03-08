#include "binary_search_tree.h"
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <vector>

// test data version: 1.0.0
// Bonus - templatize for strings

template<typename T>
using tree_ptr = typename std::unique_ptr<binary_tree::binary_tree<T>>;

template<typename T>
static void test_branch(const tree_ptr<T> &br, bool has)
{
    BOOST_REQUIRE_EQUAL((bool) br, has);
}

template<typename T>
static void test_leaf(const tree_ptr<T> &tree, 
                      const T& data, bool has_left, bool has_right)
{
    BOOST_REQUIRE_EQUAL(data, tree->data());
    test_branch(tree->left(), has_left);
    test_branch(tree->right(), has_right);
}

template<typename T>
static tree_ptr<T> make_tree(const std::vector<T> &data)
{
    if (data.empty())
        return tree_ptr<T>(nullptr);
    
    auto data_iter = data.begin();
    auto tree = tree_ptr<T>(new binary_tree::binary_tree<T>(*data_iter));
    ++data_iter;

    for (; data_iter != data.end(); ++data_iter)
    {
        tree->insert(*data_iter);
    }

    return tree;
}

#if defined(EXERCISM_RUN_ALL_TESTS)
BOOST_AUTO_TEST_CASE(data_is_retained)
{
    auto tested = make_tree<uint32_t>({4});
    test_leaf<uint32_t>(tested, 4, false, false);
}


BOOST_AUTO_TEST_CASE(smaller_number_at_left_node)
{
    auto tested = make_tree<uint32_t>({4, 2});

    test_leaf<uint32_t>(tested, 4, true, false);
    test_leaf<uint32_t>(tested->left(), 2, false, false);
}

BOOST_AUTO_TEST_CASE(same_number_at_left_node)
{
    auto tested = make_tree<uint32_t>({4, 4});

    test_leaf<uint32_t>(tested, 4, true, false);
    test_leaf<uint32_t>(tested->left(), 4, false, false);
}

BOOST_AUTO_TEST_CASE(greater_number_at_right_node)
{
    auto tested = make_tree<uint32_t>({4, 5});
    
    test_leaf<uint32_t>(tested, 4, false, true);
    test_leaf<uint32_t>(tested->right(), 5, false, false);
}

BOOST_AUTO_TEST_CASE(can_create_complex_tree)
{
    auto tested = make_tree<uint32_t>({4, 2, 6, 1, 3, 5, 7});

    test_leaf<uint32_t>(tested, 4, true, true);
    test_leaf<uint32_t>(tested->left(), 2, true, true);
    test_leaf<uint32_t>(tested->right(), 6, true, true);

    test_leaf<uint32_t>(tested->left()->left(), 1, false, false);
    test_leaf<uint32_t>(tested->left()->right(), 3, false, false);

    test_leaf<uint32_t>(tested->right()->left(), 5, false, false);
    test_leaf<uint32_t>(tested->right()->right(), 7, false, false);
}

template<typename T>
static void test_sort(const tree_ptr<T> &tree, const std::vector<T> &expected)
{
    BOOST_REQUIRE_EQUAL_COLLECTIONS(tree->begin(), tree->end(), expected.begin(), expected.end());
}


BOOST_AUTO_TEST_CASE(can_sort_single_number)
{
    test_sort(make_tree<uint32_t>({2}), {2});
}

BOOST_AUTO_TEST_CASE(can_sort_if_second_number_is_smaller_than_first)
{
    test_sort(make_tree<uint32_t>({2, 1}), {1, 2});
}

BOOST_AUTO_TEST_CASE(can_sort_if_second_number_is_same_as_first)
{
    test_sort(make_tree<uint32_t>({2, 2}), {2, 2});
}

BOOST_AUTO_TEST_CASE(can_sort_if_second_number_is_greater_than_first)
{
    test_sort(make_tree<uint32_t>({2, 3}), {2, 3});
}

BOOST_AUTO_TEST_CASE(can_sort_complex_tree)
{
    test_sort(make_tree<uint32_t>({2, 1, 3, 6, 7, 5}), {1, 2, 3, 5, 6, 7});
}

// strings

BOOST_AUTO_TEST_CASE(can_create_complex_tree_strings)
{
    auto tested = make_tree<std::string>({"4", "2", "6", "1", "3", "5", "7"});

    test_leaf<std::string>(tested, "4", true, true);
    test_leaf<std::string>(tested->left(), "2", true, true);
    test_leaf<std::string>(tested->right(), "6", true, true);

    test_leaf<std::string>(tested->left()->left(), "1", false, false);
    test_leaf<std::string>(tested->left()->right(), "3", false, false);

    test_leaf<std::string>(tested->right()->left(), "5", false, false);
    test_leaf<std::string>(tested->right()->right(), "7", false, false);
}

BOOST_AUTO_TEST_CASE(can_sort_complex_tree_strings)
{
    test_sort(make_tree<std::string>({"2", "1", "3", "6", "7", "5"}), {"1", "2", "3", "5", "6", "7"});
}

#endif