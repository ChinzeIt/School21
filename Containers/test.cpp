#include <gtest/gtest.h>

#include "s21_containers.h"
#include "s21_containersplus.h"

template <typename T>
class ListIteratorTest : public ::testing::Test {
 protected:
  s21::List<T> list;

  void SetUp() {
    list.push_back(T(1));
    list.push_back(T(2));
    list.push_back(T(3));
  }
};

using TestTypes = ::testing::Types<int, float, double, char>;
TYPED_TEST_SUITE(ListIteratorTest, TestTypes);

TYPED_TEST(ListIteratorTest, DefaultConstructor) {
  typename s21::List<TypeParam>::iterator it;
}

TYPED_TEST(ListIteratorTest, ValueConstructor) {
  auto it = this->list.begin();
  EXPECT_EQ(*it, TypeParam(1));
}

TYPED_TEST(ListIteratorTest, CopyConstructor) {
  auto it1 = this->list.begin();
  auto it2(it1);
  EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(it1.current, it2.current);
}

TYPED_TEST(ListIteratorTest, MoveConstructor) {
  auto it1 = this->list.begin();
  auto it2(std::move(it1));
  EXPECT_EQ(*it2, TypeParam(1));
}

TYPED_TEST(ListIteratorTest, DereferenceOperator) {
  auto it = this->list.begin();
  EXPECT_EQ(*it, TypeParam(1));
}

TYPED_TEST(ListIteratorTest, PreIncrement) {
  auto it = this->list.begin();
  EXPECT_EQ(*++it, TypeParam(2));
}

TYPED_TEST(ListIteratorTest, PreDecrement) {
  auto it = this->list.begin();
  ++it;
  EXPECT_EQ(*--it, TypeParam(1));
}

TYPED_TEST(ListIteratorTest, EqualityOperators) {
  auto it1 = this->list.begin();
  auto it2 = this->list.begin();
  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 != it2);
  ++it2;
  EXPECT_FALSE(it1 == it2);
  EXPECT_TRUE(it1 != it2);
}

TYPED_TEST(ListIteratorTest, BeginEndComparison) {
  auto begin = this->list.begin();
  auto end = this->list.end();
  EXPECT_NE(begin, end);
  begin = end;
  EXPECT_EQ(begin, end);
}

template <typename T>
class ConstListIteratorTest : public ::testing::Test {
 protected:
  s21::List<T> list;

  void SetUp() override {
    list.push_back(T(1));
    list.push_back(T(2));
    list.push_back(T(3));
  }
};

using TestTypes = ::testing::Types<int, float, double, char>;
TYPED_TEST_SUITE(ConstListIteratorTest, TestTypes);

TYPED_TEST(ConstListIteratorTest, DefaultConstructor) {
  typename s21::List<TypeParam>::const_iterator it;
  SUCCEED();
}

TYPED_TEST(ConstListIteratorTest, ValueConstructor) {
  const auto& clist = this->list;
  auto it = clist.begin();
  EXPECT_EQ(*it, TypeParam(1));
}

TYPED_TEST(ConstListIteratorTest, DereferenceOperator) {
  const auto& clist = this->list;
  auto it = clist.begin();
  static_assert(std::is_const_v<std::remove_reference_t<decltype(*it)>>,
                "Should return const reference");
  EXPECT_EQ(*it, TypeParam(1));
}

TYPED_TEST(ConstListIteratorTest, PreIncrement) {
  const auto& clist = this->list;
  auto it = clist.begin();
  EXPECT_EQ(*++it, TypeParam(2));
}

TYPED_TEST(ConstListIteratorTest, PreDecrement) {
  const auto& clist = this->list;
  auto it = clist.begin();
  ++it;
  EXPECT_EQ(*--it, TypeParam(1));
}

TYPED_TEST(ConstListIteratorTest, EqualityOperators) {
  const auto& clist = this->list;
  auto it1 = clist.begin();
  auto it2 = clist.begin();
  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 != it2);
  ++it2;
  EXPECT_FALSE(it1 == it2);
  EXPECT_TRUE(it1 != it2);
}

TYPED_TEST(ConstListIteratorTest, BeginEndComparison) {
  const auto& clist = this->list;
  auto begin = clist.begin();
  auto end = clist.end();
  EXPECT_NE(begin, end);
  begin = end;
  EXPECT_EQ(begin, end);
}

TYPED_TEST(ConstListIteratorTest, ConstCorrectness) {
  const auto& clist = this->list;
  auto it = clist.begin();

  static_assert(!std::is_assignable_v<decltype(*it), TypeParam>,
                "Should not allow modification through const_iterator");
}

using namespace s21;

template <typename T>
class ListConstructorsTest : public ::testing::Test {
 protected:
  using ListType = s21::List<T>;

  void SetUp() override { test_values = ListType({T(1), T(2), T(3)}); }

  ListType test_values;
};

using TestTypes = ::testing::Types<int, float, double, char>;
TYPED_TEST_SUITE(ListConstructorsTest, TestTypes);

TYPED_TEST(ListConstructorsTest, DefaultConstructor) {
  typename TestFixture::ListType list;
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.begin(), list.end());
}

TYPED_TEST(ListConstructorsTest, SizeConstructor) {
  typename TestFixture::ListType list(3);
  EXPECT_EQ(list.size(), 3);
  for (const auto& item : list) {
    EXPECT_EQ(item, TypeParam());
  }
}

TYPED_TEST(ListConstructorsTest, InitializerListConstructor) {
  typename TestFixture::ListType list(this->test_values);
  EXPECT_EQ(list.size(), 3);

  auto it = list.begin();
  EXPECT_EQ(*it, TypeParam(1));
  ++it;
  EXPECT_EQ(*it, TypeParam(2));
  ++it;
  EXPECT_EQ(*it, TypeParam(3));
}

TYPED_TEST(ListConstructorsTest, CopyConstructor) {
  typename TestFixture::ListType original(this->test_values);
  typename TestFixture::ListType copy(original);

  EXPECT_EQ(original.size(), copy.size());
  auto it1 = original.begin();
  auto it2 = copy.begin();
  while (it1 != original.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TYPED_TEST(ListConstructorsTest, CopyConstructorEmptyList) {
  typename TestFixture::ListType original;
  EXPECT_THROW(typename TestFixture::ListType copy(original),
               std::out_of_range);
}

TYPED_TEST(ListConstructorsTest, MoveConstructor) {
  typename TestFixture::ListType original(this->test_values);
  typename TestFixture::ListType moved(std::move(original));

  EXPECT_EQ(moved.size(), 3);
  EXPECT_TRUE(original.empty());

  auto it = moved.begin();
  EXPECT_EQ(*it, TypeParam(1));
  ++it;
  EXPECT_EQ(*it, TypeParam(2));
  ++it;
  EXPECT_EQ(*it, TypeParam(3));
}

TYPED_TEST(ListConstructorsTest, MoveAssignmentOperator) {
  typename TestFixture::ListType source(this->test_values);
  typename TestFixture::ListType target;
  target.push_back(TypeParam(4));

  target = std::move(source);

  EXPECT_EQ(target.size(), 3);
  EXPECT_TRUE(source.empty());

  auto it = target.begin();
  EXPECT_EQ(*it, TypeParam(1));
  ++it;
  EXPECT_EQ(*it, TypeParam(2));
  ++it;
  EXPECT_EQ(*it, TypeParam(3));
}

TYPED_TEST(ListConstructorsTest, Destructor) {
  auto* list = new typename TestFixture::ListType(this->test_values);
  delete list;
  SUCCEED();
}

TYPED_TEST(ListConstructorsTest, FrontReturnsFirstElement) {
  typename TestFixture::ListType list(this->test_values);
  EXPECT_EQ(list.front(), TypeParam(1));
}

TYPED_TEST(ListConstructorsTest, BackReturnsLastElement) {
  typename TestFixture::ListType list(this->test_values);
  EXPECT_EQ(list.back(), TypeParam(3));
}

TYPED_TEST(ListConstructorsTest, FrontThrowsIfEmpty) {
  typename TestFixture::ListType list;
  EXPECT_THROW(list.front(), std::out_of_range);
}

TYPED_TEST(ListConstructorsTest, BackThrowsIfEmpty) {
  typename TestFixture::ListType list;
  EXPECT_THROW(list.back(), std::out_of_range);
}

TYPED_TEST(ListConstructorsTest, InsertAtBeginning) {
  typename TestFixture::ListType list(this->test_values);
  auto it = list.begin();
  list.insert(it, TypeParam(0));

  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list.front(), TypeParam(0));
}

TYPED_TEST(ListConstructorsTest, InsertAtEnd) {
  typename TestFixture::ListType list(this->test_values);
  auto it = list.end();
  list.insert(it, TypeParam(4));

  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list.back(), TypeParam(4));
}

TYPED_TEST(ListConstructorsTest, InsertInMiddle) {
  typename TestFixture::ListType list(this->test_values);
  auto it = list.begin();
  ++it;
  list.insert(it, TypeParam(9));

  EXPECT_EQ(list.size(), 4);

  auto iter = list.begin();
  EXPECT_EQ(*iter, TypeParam(1));
  ++iter;
  EXPECT_EQ(*iter, TypeParam(9));
  ++iter;
  EXPECT_EQ(*iter, TypeParam(2));
  ++iter;
  EXPECT_EQ(*iter, TypeParam(3));
}

TYPED_TEST(ListConstructorsTest, EraseFromBeginning) {
  typename TestFixture::ListType list(this->test_values);
  auto it = list.begin();
  list.erase(it);

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.front(), TypeParam(2));
}

TYPED_TEST(ListConstructorsTest, EraseFromMiddle) {
  typename TestFixture::ListType list(this->test_values);
  auto it = list.begin();
  ++it;
  list.erase(it);

  EXPECT_EQ(list.size(), 2);
  auto iter = list.begin();
  EXPECT_EQ(*iter, TypeParam(1));
  ++iter;
  EXPECT_EQ(*iter, TypeParam(3));
}

TYPED_TEST(ListConstructorsTest, EraseThrowsOnInvalidIterator) {
  typename TestFixture::ListType list(this->test_values);
  typename TestFixture::ListType::iterator invalid;
  EXPECT_THROW(list.erase(invalid), std::out_of_range);
}

TYPED_TEST(ListConstructorsTest, EraseAllElements) {
  typename TestFixture::ListType list(this->test_values);
  while (!list.empty()) {
    list.erase(list.begin());
  }
  EXPECT_EQ(list.size(), 0);
  EXPECT_THROW(list.front(), std::out_of_range);
  EXPECT_THROW(list.back(), std::out_of_range);
}

TYPED_TEST(ListConstructorsTest, PushFrontIncreasesSizeAndAddsElement) {
  typename TestFixture::ListType list;
  list.push_front(TypeParam(10));
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.front(), TypeParam(10));
  EXPECT_EQ(list.back(), TypeParam(10));

  list.push_front(TypeParam(20));
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.front(), TypeParam(20));
  EXPECT_EQ(list.back(), TypeParam(10));
}

TYPED_TEST(ListConstructorsTest, PopFrontRemovesFirstElement) {
  typename TestFixture::ListType list(this->test_values);
  TypeParam first = list.front();
  list.pop_front();
  EXPECT_EQ(list.size(), 2);
  EXPECT_NE(list.front(), first);
}

TYPED_TEST(ListConstructorsTest, PopFrontThrowsIfEmpty) {
  typename TestFixture::ListType list;
  EXPECT_THROW(list.pop_front(), std::out_of_range);
}

TYPED_TEST(ListConstructorsTest, PopBackRemovesLastElement) {
  typename TestFixture::ListType list(this->test_values);
  TypeParam last = list.back();
  list.pop_back();
  EXPECT_EQ(list.size(), 2);
  EXPECT_NE(list.back(), last);
}

TYPED_TEST(ListConstructorsTest, PopBackThrowsIfEmpty) {
  typename TestFixture::ListType list;
  EXPECT_THROW(list.pop_back(), std::out_of_range);
}

TYPED_TEST(ListConstructorsTest, SwapExchangesContents) {
  typename TestFixture::ListType list1(this->test_values);
  typename TestFixture::ListType list2;
  list2.push_back(TypeParam(100));

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 1);
  EXPECT_EQ(list1.front(), TypeParam(100));
  EXPECT_EQ(list2.size(), 3);
  EXPECT_EQ(list2.front(), TypeParam(1));
}

TYPED_TEST(ListConstructorsTest, MergeWithEmptyThrows) {
  typename TestFixture::ListType list1(this->test_values);
  typename TestFixture::ListType list2;
  EXPECT_THROW(list1.merge(list2), std::out_of_range);
}

TYPED_TEST(ListConstructorsTest, MergeWithSelfThrows) {
  typename TestFixture::ListType list(this->test_values);
  EXPECT_THROW(list.merge(list), std::out_of_range);
}

TYPED_TEST(ListConstructorsTest, MergeSortedLists) {
  typename TestFixture::ListType list1;
  list1.push_back(TypeParam(1));
  list1.push_back(TypeParam(3));
  list1.push_back(TypeParam(5));

  typename TestFixture::ListType list2;
  list2.push_back(TypeParam(2));
  list2.push_back(TypeParam(4));
  list2.push_back(TypeParam(6));

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());

  auto it = list1.begin();
  for (int val : {1, 2, 3, 4, 5, 6}) {
    EXPECT_EQ(*it, TypeParam(val));
    ++it;
  }
}

TEST(ListMergeTest, ThisListHasRemainingElements) {
  s21::List<int> a = {1, 3, 5, 7, 9};
  s21::List<int> b = {2, 4};

  a.merge(b);

  auto it = a.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 7);
  ++it;
  EXPECT_EQ(*it, 9);
  ++it;
  EXPECT_EQ(it, a.end());
}

TEST(ListSpliceTest, SpliceIntoBeginning) {
  s21::List<int> list1 = {3, 4, 5};
  s21::List<int> list2 = {1, 2};

  const s21::List<int>& const_list1 = list1;
  s21::List<int>::const_iterator pos = const_list1.begin();
  list1.splice(pos, list2);

  s21::List<int>::iterator it = list1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(it, list1.end());

  EXPECT_TRUE(list2.empty());
}

TEST(ListSpliceTest, SpliceIntoMiddle) {
  s21::List<int> list1 = {1, 4, 5};
  s21::List<int> list2 = {2, 3};

  const s21::List<int>& const_list1 = list1;
  s21::List<int>::const_iterator pos = const_list1.begin();
  ++pos;
  list1.splice(pos, list2);

  s21::List<int>::iterator it = list1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(it, list1.end());

  EXPECT_TRUE(list2.empty());
}

TEST(ListSpliceTest, SpliceIntoEnd) {
  s21::List<int> list1 = {1, 2};
  s21::List<int> list2 = {3, 4, 5};

  const s21::List<int>& const_list1 = list1;
  s21::List<int>::const_iterator pos = const_list1.end();
  list1.splice(pos, list2);

  s21::List<int>::iterator it = list1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(it, list1.end());

  EXPECT_TRUE(list2.empty());
}

TEST(ListSpliceTest, SpliceEmptyOtherThrows) {
  s21::List<int> list1 = {1, 2, 3};
  s21::List<int> list2;

  const s21::List<int>& const_list1 = list1;
  EXPECT_THROW(list1.splice(const_list1.begin(), list2), std::out_of_range);
}

TEST(ListSpliceTest, SpliceIntoEmptyList) {
  s21::List<int> list1;
  s21::List<int> list2;

  list2.push_back(1);
  list2.push_back(2);
  list2.push_back(3);

  const s21::List<int>& const_list1 = list1;
  s21::List<int>::const_iterator pos = const_list1.end();

  list1.splice(pos, list2);

  EXPECT_EQ(const_list1.size(), 3);
  EXPECT_EQ(list2.size(), 0);
  int expected[] = {1, 2, 3};
  int i = 0;
  for (auto it = const_list1.begin(); it != const_list1.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
}

TEST(ListTest, ReverseNormal) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.reverse();

  auto it = list.begin();
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 1);
}

TEST(ListTest, ReverseEmpty) {
  s21::List<int> list;
  EXPECT_NO_THROW(list.reverse());
  ASSERT_TRUE(list.empty());
}

TEST(ListTest, UniqueNormal) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(3);
  list.push_back(3);
  list.push_back(4);

  list.unique();

  ASSERT_EQ(list.size(), 4);

  auto it = list.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 4);
}

TEST(ListTest, UniqueEmptyThrows) {
  s21::List<int> list;
  EXPECT_THROW(list.unique(), std::out_of_range);
}

TEST(ListTest, SortNormal) {
  s21::List<int> list;
  list.push_back(3);
  list.push_back(1);
  list.push_back(2);

  list.sort();

  auto it = list.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
}

TEST(ListTest, SortEmptyThrows) {
  s21::List<int> list;
  EXPECT_THROW(list.sort(), std::out_of_range);
}

TEST(ListTest, SortSingleElementThrows) {
  s21::List<int> list;
  list.push_back(1);
  EXPECT_THROW(list.sort(), std::out_of_range);
}

TEST(ListTest, UniqueRemovesDuplicateAtTail) {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(3);

  size_t old_size = list.size();

  list.unique();

  ASSERT_EQ(list.size(), old_size - 1);

  auto it = list.begin();
  ++it;
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(it, list.end());
}

TEST(ListTest, MaxSizeIsCorrect) {
  s21::List<int> list;
  size_t max = list.max_size();

  EXPECT_EQ(max, std::numeric_limits<std::size_t>::max());

  EXPECT_GT(max, 1000000);
}

template <typename T>
class QueueTest : public ::testing::Test {
 public:
  using QueueType = s21::Queue<T>;
};

using MyTypes = ::testing::Types<int, float, double, char>;
TYPED_TEST_SUITE(QueueTest, MyTypes);

TYPED_TEST(QueueTest, DefaultConstructor) {
  typename TestFixture::QueueType q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0u);
}

TYPED_TEST(QueueTest, InitializerListConstructor) {
  typename TestFixture::QueueType q = {TypeParam(1), TypeParam(2),
                                       TypeParam(3)};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 3u);
  EXPECT_EQ(q.front(), TypeParam(1));
  EXPECT_EQ(q.back(), TypeParam(3));
}

TYPED_TEST(QueueTest, CopyConstructor) {
  typename TestFixture::QueueType q1 = {TypeParam(10), TypeParam(20),
                                        TypeParam(30)};
  typename TestFixture::QueueType q2(q1);
  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.front(), q2.front());
  EXPECT_EQ(q1.back(), q2.back());
}

TYPED_TEST(QueueTest, MoveConstructor) {
  typename TestFixture::QueueType q1 = {TypeParam(100), TypeParam(200)};
  typename TestFixture::QueueType q2(std::move(q1));
  EXPECT_EQ(q2.size(), 2u);
  EXPECT_EQ(q2.front(), TypeParam(100));
  EXPECT_EQ(q2.back(), TypeParam(200));
  EXPECT_TRUE(q1.empty());
}

TYPED_TEST(QueueTest, MoveAssignmentOperator) {
  typename TestFixture::QueueType q1 = {TypeParam(5), TypeParam(6),
                                        TypeParam(7)};
  typename TestFixture::QueueType q2;
  q2 = std::move(q1);
  EXPECT_EQ(q2.size(), 3u);
  EXPECT_EQ(q2.front(), TypeParam(5));
  EXPECT_EQ(q2.back(), TypeParam(7));
  EXPECT_TRUE(q1.empty());
}

TYPED_TEST(QueueTest, DestructorDoesNotCrash) {
  {
    typename TestFixture::QueueType q = {TypeParam(1), TypeParam(2),
                                         TypeParam(3)};
  }
  SUCCEED();
}

TYPED_TEST(QueueTest, PopWorks) {
  typename TestFixture::QueueType q;
  q.push(TypeParam(10));
  EXPECT_EQ(q.front(), TypeParam(10));
  q.pop();
  EXPECT_TRUE(q.empty());
}

TYPED_TEST(QueueTest, PopThrowsWhenEmpty) {
  typename TestFixture::QueueType q;
  EXPECT_THROW(q.pop(), std::out_of_range);
}

TYPED_TEST(QueueTest, SwapExchangesContents) {
  typename TestFixture::QueueType q1;
  typename TestFixture::QueueType q2;
  q1.push(TypeParam(1));
  q1.push(TypeParam(2));
  q2.push(TypeParam(3));
  q2.push(TypeParam(4));
  q2.push(TypeParam(5));

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 3u);
  EXPECT_EQ(q2.size(), 2u);
  EXPECT_EQ(q1.front(), TypeParam(3));
  EXPECT_EQ(q2.front(), TypeParam(1));
}

using namespace s21;

template <typename T>
class VectorIteratorTest : public ::testing::Test {
 protected:
  Vector<T> vec = {T(1), T(2), T(3)};
};

TYPED_TEST_SUITE(VectorIteratorTest, TestTypes);

TYPED_TEST(VectorIteratorTest, DefaultConstructor) {
  typename Vector<TypeParam>::iterator it;
  EXPECT_EQ(it.current, nullptr);
  EXPECT_EQ(it.begin_, nullptr);
  EXPECT_EQ(it.end_, nullptr);
}

TYPED_TEST(VectorIteratorTest, IteratorIncrementThrowsAtEnd) {
  Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3)};
  auto it = vec.end();

  EXPECT_THROW(++it, std::out_of_range);
}

TYPED_TEST(VectorIteratorTest, ParameterizedConstructor) {
  auto it = this->vec.begin();
  EXPECT_EQ(*it, TypeParam(1));
  EXPECT_EQ(it.begin_, this->vec.data());
  EXPECT_EQ(it.end_, this->vec.data() + this->vec.size());
}

TYPED_TEST(VectorIteratorTest, DereferenceOperator) {
  auto it = this->vec.begin();
  EXPECT_EQ(*it, TypeParam(1));
  *it = TypeParam(10);
  EXPECT_EQ(*it, TypeParam(10));
}

TYPED_TEST(VectorIteratorTest, PreIncrement) {
  auto it = this->vec.begin();
  EXPECT_EQ(*++it, TypeParam(2));
  EXPECT_EQ(*it, TypeParam(2));
}

TYPED_TEST(VectorIteratorTest, EqualityOperators) {
  auto it1 = this->vec.begin();
  auto it2 = this->vec.begin();
  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 != it2);

  ++it2;
  EXPECT_FALSE(it1 == it2);
  EXPECT_TRUE(it1 != it2);
}

TYPED_TEST(VectorIteratorTest, BoundaryChecks) {
  auto begin = this->vec.begin();
  auto end = this->vec.end();

  EXPECT_EQ(begin.begin_, this->vec.data());
  EXPECT_EQ(begin.end_, this->vec.data() + this->vec.size());
  EXPECT_EQ(end.begin_, begin.begin_);
  EXPECT_EQ(end.end_, begin.end_);

  EXPECT_EQ(end - begin, 3);
}

TYPED_TEST(VectorIteratorTest, PreDecrementOperator) {
  Vector<int> vec{10, 20, 30};
  auto it = vec.begin();
  ++it;
  ++it;

  EXPECT_EQ(*--it, 20);
  EXPECT_EQ(*--it, 10);

  EXPECT_THROW(--it, std::out_of_range);

  Vector<int> empty_vec;
  auto empty_it = empty_vec.begin();
  EXPECT_THROW(--empty_it, std::out_of_range);
}

template <typename T>
class ConstVectorIteratorTest : public ::testing::Test {
 protected:
  Vector<T> vec = {T(1), T(2), T(3)};
};

TYPED_TEST_SUITE(ConstVectorIteratorTest, TestTypes);

TYPED_TEST(ConstVectorIteratorTest, DefaultConstructor) {
  typename Vector<TypeParam>::const_iterator it;
  EXPECT_EQ(it.current, nullptr);
  EXPECT_EQ(it.begin_, nullptr);
  EXPECT_EQ(it.end_, nullptr);
}

TYPED_TEST(ConstVectorIteratorTest, ConstIteratorIncrementThrowsAtEnd) {
  const Vector<TypeParam>& cvec = this->vec;
  auto it = cvec.end();
  EXPECT_THROW(++it, std::out_of_range);
}

TYPED_TEST(ConstVectorIteratorTest, ParameterizedConstructor) {
  const auto& cvec = this->vec;
  auto it = cvec.begin();
  EXPECT_EQ(*it, TypeParam(1));
  EXPECT_EQ(it.begin_, cvec.data());
  EXPECT_EQ(it.end_, cvec.data() + cvec.size());
}

TYPED_TEST(ConstVectorIteratorTest, DereferenceOperator) {
  const auto& cvec = this->vec;
  auto it = cvec.begin();
  EXPECT_EQ(*it, TypeParam(1));
}

TYPED_TEST(ConstVectorIteratorTest, PreIncrement) {
  const auto& cvec = this->vec;
  auto it = cvec.begin();
  EXPECT_EQ(*++it, TypeParam(2));
  EXPECT_EQ(*it, TypeParam(2));
}

TYPED_TEST(ConstVectorIteratorTest, PreDecrementOperator) {
  const auto& cvec = this->vec;
  auto it = cvec.begin();
  ++it;
  ++it;
  EXPECT_EQ(*--it, TypeParam(2));
  EXPECT_EQ(*--it, TypeParam(1));
  EXPECT_THROW(--it, std::out_of_range);

  Vector<TypeParam> empty_vec;
  auto empty_it = empty_vec.begin();
  EXPECT_THROW(--empty_it, std::out_of_range);
}

TYPED_TEST(ConstVectorIteratorTest, EqualityOperators) {
  const auto& cvec = this->vec;
  auto it1 = cvec.begin();
  auto it2 = cvec.begin();
  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 != it2);

  ++it2;
  EXPECT_FALSE(it1 == it2);
  EXPECT_TRUE(it1 != it2);
}

TYPED_TEST(ConstVectorIteratorTest, BoundaryChecks) {
  const auto& cvec = this->vec;
  auto begin = cvec.begin();
  auto end = cvec.end();

  EXPECT_EQ(begin.begin_, cvec.data());
  EXPECT_EQ(begin.end_, cvec.data() + cvec.size());
  EXPECT_EQ(end.begin_, begin.begin_);
  EXPECT_EQ(end.end_, begin.end_);

  EXPECT_EQ(end - begin, 3);
}

template <typename T>
class VectorTest : public ::testing::Test {
 protected:
  Vector<T> vec;
};

TYPED_TEST_SUITE(VectorTest, TestTypes);

TYPED_TEST(VectorTest, DefaultConstructor) {
  EXPECT_EQ(this->vec.size(), 0);
  EXPECT_EQ(this->vec.capacity(), 0);
  EXPECT_EQ(this->vec.data(), nullptr);
}

TYPED_TEST(VectorTest, InitializerListConstructor) {
  Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3)};
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], TypeParam(1));
  EXPECT_EQ(vec[1], TypeParam(2));
  EXPECT_EQ(vec[2], TypeParam(3));
}

TYPED_TEST(VectorTest, CopyConstructor) {
  Vector<TypeParam> original = {TypeParam(10), TypeParam(20)};
  Vector<TypeParam> copy(original);

  EXPECT_EQ(copy.size(), original.size());
  for (size_t i = 0; i < original.size(); ++i) {
    EXPECT_EQ(copy[i], original[i]);
  }
}

TYPED_TEST(VectorTest, MoveConstructor) {
  Vector<TypeParam> original = {TypeParam(1), TypeParam(2)};
  Vector<TypeParam> moved(std::move(original));

  EXPECT_EQ(moved.size(), 2);
  EXPECT_EQ(original.data(), nullptr);
  EXPECT_EQ(original.size(), 0);
}

TYPED_TEST(VectorTest, MoveAssignmentOperator) {
  Vector<TypeParam> v1 = {TypeParam(1), TypeParam(2)};
  Vector<TypeParam> v2;
  v2 = std::move(v1);

  EXPECT_EQ(v2.size(), 2);
  EXPECT_EQ(v2[0], TypeParam(1));
  EXPECT_EQ(v2[1], TypeParam(2));
  EXPECT_EQ(v1.data(), nullptr);
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.capacity(), 0);
}

TYPED_TEST(VectorTest, AtReturnsCorrectElement) {
  Vector<TypeParam> vec = {TypeParam(10), TypeParam(20)};
  EXPECT_EQ(vec.at(0), TypeParam(10));
  EXPECT_EQ(vec.at(1), TypeParam(20));
}

TYPED_TEST(VectorTest, AtThrowsOutOfRange) {
  Vector<TypeParam> vec = {TypeParam(1)};
  EXPECT_THROW(vec.at(1), std::out_of_range);
}

TYPED_TEST(VectorTest, FrontReturnsFirstElement) {
  Vector<TypeParam> vec = {TypeParam(42), TypeParam(100)};
  EXPECT_EQ(vec.front(), TypeParam(42));
}

TYPED_TEST(VectorTest, FrontThrowsIfEmpty) {
  Vector<TypeParam> vec;
  EXPECT_THROW(vec.front(), std::out_of_range);
}

TYPED_TEST(VectorTest, BackReturnsLastElement) {
  Vector<TypeParam> vec = {TypeParam(7), TypeParam(8), TypeParam(9)};
  EXPECT_EQ(vec.back(), TypeParam(9));
}

TYPED_TEST(VectorTest, BackThrowsIfEmpty) {
  Vector<TypeParam> vec;
  EXPECT_THROW(vec.back(), std::out_of_range);
}

TYPED_TEST(VectorTest, EmptyReturnsTrueForDefaultConstructed) {
  Vector<TypeParam> vec;
  EXPECT_TRUE(vec.empty());
}

TYPED_TEST(VectorTest, SizeReturnsCorrectValue) {
  Vector<TypeParam> vec = {TypeParam(1), TypeParam(2)};
  EXPECT_EQ(vec.size(), 2);
}

TYPED_TEST(VectorTest, CapacityReflectsReserve) {
  Vector<TypeParam> vec;
  vec.reserve(10);
  EXPECT_GE(vec.capacity(), 10);
}

TYPED_TEST(VectorTest, MaxSizeIsCorrect) {
  Vector<TypeParam> vec;
  EXPECT_EQ(vec.max_size(),
            std::numeric_limits<typename Vector<TypeParam>::size_type>::max());
}

TYPED_TEST(VectorTest, ReserveIncreasesCapacity) {
  Vector<TypeParam> vec = {TypeParam(1), TypeParam(2)};
  size_t old_capacity = vec.capacity();
  vec.reserve(old_capacity + 10);
  EXPECT_GE(vec.capacity(), old_capacity + 10);
  EXPECT_EQ(vec.size(), 2);
}

TYPED_TEST(VectorTest, ReserveThrowsIfNewSizeIsNotGreater) {
  Vector<TypeParam> vec = {TypeParam(1)};
  size_t cap = vec.capacity();
  EXPECT_THROW(vec.reserve(cap), std::out_of_range);
}

TYPED_TEST(VectorTest, ShrinkToFitReducesCapacityToSize) {
  Vector<TypeParam> vec;
  vec.reserve(10);
  vec.push_back(TypeParam(1));
  vec.push_back(TypeParam(2));

  EXPECT_GT(vec.capacity(), vec.size());
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());
}

TYPED_TEST(VectorTest, ShrinkToFitThrowsIfCapacityEqualsSize) {
  Vector<TypeParam> vec = {TypeParam(1), TypeParam(2)};
  EXPECT_THROW(vec.shrink_to_fit(), std::out_of_range);
}

TYPED_TEST(VectorTest, ClearEmptiesVector) {
  Vector<TypeParam> vec = {TypeParam(1), TypeParam(2)};
  vec.clear();
  EXPECT_TRUE(vec.empty());
  EXPECT_EQ(vec.data(), nullptr);
}

TYPED_TEST(VectorTest, InsertAtBeginning) {
  Vector<TypeParam> vec = {TypeParam(2), TypeParam(3)};
  auto it = vec.insert(vec.begin(), TypeParam(1));
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], TypeParam(1));
  EXPECT_EQ(*it, TypeParam(1));
}

TYPED_TEST(VectorTest, InsertInMiddle) {
  Vector<TypeParam> vec = {TypeParam(1), TypeParam(3)};
  auto it = vec.begin();
  ++it;
  it = vec.insert(it, TypeParam(2));
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[1], TypeParam(2));
  EXPECT_EQ(*it, TypeParam(2));
}

TYPED_TEST(VectorTest, InsertAtEnd) {
  Vector<TypeParam> vec = {TypeParam(1), TypeParam(2)};
  auto it = vec.insert(vec.end(), TypeParam(3));
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[2], TypeParam(3));
  EXPECT_EQ(*it, TypeParam(3));
}

TYPED_TEST(VectorTest, InsertThrowsIfOutOfBounds) {
  Vector<TypeParam> vec = {TypeParam(1)};

  typename Vector<TypeParam>::iterator fake_it(nullptr, nullptr, nullptr);

  EXPECT_THROW(vec.insert(fake_it, TypeParam(2)), std::out_of_range);
}

TYPED_TEST(VectorTest, EraseFromBeginning) {
  Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3)};
  vec.erase(vec.begin());
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], TypeParam(2));
}

TYPED_TEST(VectorTest, EraseFromMiddle) {
  Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3)};

  auto it = vec.begin();
  ++it;

  vec.erase(it);

  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[1], TypeParam(3));
}

TYPED_TEST(VectorTest, EraseThrowsIfOutOfBounds) {
  Vector<TypeParam> vec = {TypeParam(1)};

  typename Vector<TypeParam>::iterator fake_it(nullptr, nullptr, nullptr);

  EXPECT_THROW(vec.erase(fake_it), std::out_of_range);
}

TYPED_TEST(VectorTest, PushBackAddsElement) {
  Vector<TypeParam> vec;
  vec.push_back(TypeParam(42));
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], TypeParam(42));
}

TYPED_TEST(VectorTest, PopBackRemovesLastElement) {
  Vector<TypeParam> vec = {TypeParam(1), TypeParam(2)};
  vec.pop_back();
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], TypeParam(1));
}

TYPED_TEST(VectorTest, PopBackThrowsIfEmpty) {
  Vector<TypeParam> vec;
  EXPECT_THROW(vec.pop_back(), std::out_of_range);
}

TYPED_TEST(VectorTest, SwapExchangesContents) {
  Vector<TypeParam> a = {TypeParam(1), TypeParam(2)};
  Vector<TypeParam> b = {TypeParam(3)};
  a.swap(b);

  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(a[0], TypeParam(3));
  EXPECT_EQ(b.size(), 2);
  EXPECT_EQ(b[0], TypeParam(1));
}

TYPED_TEST(VectorTest, ConstructorWithSize_DefaultValues) {
  const size_t n = 5;
  Vector<TypeParam> vec(n);

  EXPECT_EQ(vec.size(), 0);

  EXPECT_EQ(vec.capacity(), 0);

  EXPECT_NE(vec.data(), nullptr);
}

template <typename T>
class StackTest : public ::testing::Test {
 protected:
  Stack<T> stack;
};

TYPED_TEST_SUITE(StackTest, TestTypes);

TYPED_TEST(StackTest, DefaultConstructor) { EXPECT_EQ(this->stack.size(), 0u); }

TYPED_TEST(StackTest, PushIncreasesSize) {
  this->stack.push(TypeParam(1));
  EXPECT_EQ(this->stack.size(), 1u);
  this->stack.push(TypeParam(2));
  EXPECT_EQ(this->stack.size(), 2u);
}

TYPED_TEST(StackTest, TopReturnsLastPushedElement) {
  this->stack.push(TypeParam(42));
  EXPECT_EQ(this->stack.top(), TypeParam(42));
  this->stack.push(TypeParam(99));
  EXPECT_EQ(this->stack.top(), TypeParam(99));
}

TYPED_TEST(StackTest, PopRemovesLastElement) {
  this->stack.push(TypeParam(1));
  this->stack.push(TypeParam(2));
  EXPECT_EQ(this->stack.top(), TypeParam(2));
  this->stack.pop();
  EXPECT_EQ(this->stack.top(), TypeParam(1));
  EXPECT_EQ(this->stack.size(), 1u);
}

TYPED_TEST(StackTest, IsEmptyAfterClearing) {
  this->stack.push(TypeParam(10));
  this->stack.pop();
  EXPECT_EQ(this->stack.size(), 0u);
}

TYPED_TEST(StackTest, InitializerListConstructor) {
  Stack<TypeParam> s = {TypeParam(1), TypeParam(2), TypeParam(3)};
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.top(), TypeParam(3));
}

TYPED_TEST(StackTest, CopyConstructor) {
  this->stack.push(TypeParam(7));
  this->stack.push(TypeParam(8));
  Stack<TypeParam> copy(this->stack);
  EXPECT_EQ(copy.size(), 2u);
  EXPECT_EQ(copy.top(), TypeParam(8));
}

TYPED_TEST(StackTest, MoveConstructor) {
  this->stack.push(TypeParam(9));
  Stack<TypeParam> moved(std::move(this->stack));
  EXPECT_EQ(moved.size(), 1u);
  EXPECT_EQ(moved.top(), TypeParam(9));
  EXPECT_EQ(this->stack.size(), 0u);
}

TYPED_TEST(StackTest, MoveAssignment) {
  this->stack.push(TypeParam(3));
  Stack<TypeParam> other;
  other = std::move(this->stack);
  EXPECT_EQ(other.size(), 1u);
  EXPECT_EQ(other.top(), TypeParam(3));
  EXPECT_EQ(this->stack.size(), 0u);
}

TYPED_TEST(StackTest, Clear) {
  Stack<TypeParam> s = {TypeParam(1), TypeParam(2), TypeParam(3)};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 3u);

  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
  EXPECT_NO_THROW(s.clear());
}

TYPED_TEST(StackTest, SwapWithNonEmpty) {
  Stack<TypeParam> a = {TypeParam(1), TypeParam(2)};
  Stack<TypeParam> b = {TypeParam(8), TypeParam(9), TypeParam(10)};

  a.swap(b);

  EXPECT_EQ(a.size(), 3u);
  EXPECT_EQ(b.size(), 2u);
  EXPECT_EQ(a.top(), TypeParam(10));
  EXPECT_EQ(b.top(), TypeParam(2));
}

TYPED_TEST(StackTest, SwapWithEmpty) {
  Stack<TypeParam> a = {TypeParam(1)};
  Stack<TypeParam> b;

  a.swap(b);

  EXPECT_TRUE(a.empty());
  EXPECT_FALSE(b.empty());
  EXPECT_EQ(b.size(), 1u);
  EXPECT_EQ(b.top(), TypeParam(1));
}

template <typename T>
class ArrayTest : public ::testing::Test {
 public:
  static constexpr std::size_t kSize = 3;
  s21::Array<T, kSize> array;
};

TYPED_TEST_SUITE(ArrayTest, TestTypes);

TYPED_TEST(ArrayTest, DefaultConstructor) {
  EXPECT_EQ(this->array.max_size(), 3);
  EXPECT_FALSE(this->array.empty());
}

TYPED_TEST(ArrayTest, InitializerListConstructor) {
  s21::Array<TypeParam, 3> array = {TypeParam(1), TypeParam(2), TypeParam(3)};
  EXPECT_EQ(array.size(), 3);
  EXPECT_EQ(array[0], TypeParam(1));
  EXPECT_EQ(array[1], TypeParam(2));
  EXPECT_EQ(array[2], TypeParam(3));
}

TYPED_TEST(ArrayTest, InitializerListWithDefaultInitialization) {
  s21::Array<TypeParam, 5> array = {TypeParam(1), TypeParam(2), TypeParam(3)};

  EXPECT_EQ(array[0], TypeParam(1));
  EXPECT_EQ(array[1], TypeParam(2));
  EXPECT_EQ(array[2], TypeParam(3));

  EXPECT_EQ(array[3], TypeParam());
  EXPECT_EQ(array[4], TypeParam());
}

TYPED_TEST(ArrayTest, DefaultConstructedArrayIsZeroInitialized) {
  for (std::size_t i = 0; i < this->array.size(); ++i) {
    EXPECT_EQ(this->array[i], TypeParam());
  }
}

TYPED_TEST(ArrayTest, AtThrowsIfOutOfBounds) {
  EXPECT_THROW(this->array.at(this->array.size()), std::out_of_range);
}

TYPED_TEST(ArrayTest, AtReturnsCorrectValue) {
  this->array[2] = TypeParam(42);
  EXPECT_EQ(this->array.at(2), TypeParam(42));
}

TYPED_TEST(ArrayTest, FrontBackWorkCorrectly) {
  this->array[0] = TypeParam(10);
  this->array[2] = TypeParam(20);
  EXPECT_EQ(this->array.front(), TypeParam(10));
  EXPECT_EQ(this->array.back(), TypeParam(20));
}

TYPED_TEST(ArrayTest, EmptyReturnsFalseIfSizeNonZero) {
  EXPECT_FALSE(this->array.empty());
}

TYPED_TEST(ArrayTest, FillAssignsAllValues) {
  this->array.fill(TypeParam(7));
  for (std::size_t i = 0; i < this->array.size(); ++i) {
    EXPECT_EQ(this->array[i], TypeParam(7));
  }
}

TYPED_TEST(ArrayTest, SwapExchangesValues) {
  s21::Array<TypeParam, 3> other;
  for (std::size_t i = 0; i < 3; ++i) {
    this->array[i] = TypeParam(i);
    other[i] = TypeParam(i + 10);
  }
  this->array.swap(other);
  for (std::size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(this->array[i], TypeParam(i + 10));
    EXPECT_EQ(other[i], TypeParam(i));
  }
}

TYPED_TEST(ArrayTest, IteratorsAccessSameData) {
  this->array.fill(TypeParam(5));
  for (auto it = this->array.begin(); it != this->array.end(); ++it) {
    EXPECT_EQ(*it, TypeParam(5));
  }
}

TYPED_TEST(ArrayTest, ConstIteratorsWork) {
  const auto& const_array = this->array;
  for (auto it = const_array.begin(); it != const_array.end(); ++it) {
    EXPECT_EQ(*it, TypeParam());
  }
}

TYPED_TEST(ArrayTest, CopyConstructorCopiesElements) {
  using T = TypeParam;
  constexpr std::size_t kSize = ArrayTest<TypeParam>::kSize;

  s21::Array<T, kSize> original = {T(1), T(2), T(3)};
  s21::Array<T, kSize> copy(original);

  for (std::size_t i = 0; i < kSize; ++i) {
    EXPECT_EQ(copy[i], original[i]);
  }
}

TYPED_TEST(ArrayTest, MoveConstructorMovesElements) {
  using T = TypeParam;
  constexpr std::size_t kSize = ArrayTest<TypeParam>::kSize;

  s21::Array<T, kSize> original = {T(10), T(20), T(30)};
  s21::Array<T, kSize> moved(std::move(original));

  EXPECT_EQ(moved[0], T(10));
  EXPECT_EQ(moved[1], T(20));
  EXPECT_EQ(moved[2], T(30));
}

TYPED_TEST(ArrayTest, MoveAssignmentOperatorMovesElements) {
  using T = TypeParam;
  constexpr std::size_t kSize = ArrayTest<TypeParam>::kSize;

  s21::Array<T, kSize> source = {T(7), T(8), T(9)};
  s21::Array<T, kSize> target;
  target = std::move(source);

  EXPECT_EQ(target[0], T(7));
  EXPECT_EQ(target[1], T(8));
  EXPECT_EQ(target[2], T(9));
}

TYPED_TEST(ArrayTest, DataReturnsIteratorToFirstElement) {
  using T = TypeParam;
  constexpr std::size_t kSize = ArrayTest<TypeParam>::kSize;

  s21::Array<T, kSize> arr = {T(10), T(20), T(30)};
  auto it = arr.data();

  EXPECT_EQ(*it, arr[0]);
}

TYPED_TEST(ArrayTest, ConstDataReturnsConstIteratorToFirstElement) {
  using T = TypeParam;
  constexpr std::size_t kSize = ArrayTest<TypeParam>::kSize;

  const s21::Array<T, kSize> arr = {T(5), T(6), T(7)};
  auto it = arr.data();

  EXPECT_EQ(*it, arr[0]);
}

TYPED_TEST(ArrayTest, FrontThrowsIfArrayIsEmpty) {
  using T = TypeParam;
  s21::Array<T, 0> arr;
  EXPECT_THROW(arr.front(), std::out_of_range);
}

TYPED_TEST(ArrayTest, BackThrowsIfArrayIsEmpty) {
  using T = TypeParam;
  s21::Array<T, 0> arr;
  EXPECT_THROW(arr.back(), std::out_of_range);
}

TYPED_TEST(ArrayTest, IteratorDecrementMovesBackward) {
  using T = TypeParam;
  s21::Array<T, 3> arr = {T(1), T(2), T(3)};
  auto it = arr.end();
  --it;
  EXPECT_EQ(*it, T(3));
  --it;
  EXPECT_EQ(*it, T(2));
  --it;
  EXPECT_EQ(*it, T(1));
}

TYPED_TEST(ArrayTest, IteratorEqualityComparison) {
  using T = TypeParam;
  s21::Array<T, 3> arr = {T(10), T(20), T(30)};
  auto it1 = arr.begin();
  auto it2 = arr.begin();
  auto it3 = arr.end();

  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 == it3);
}

TYPED_TEST(ArrayTest, DefaultConstIteratorIsNull) {
  using T = TypeParam;
  typename s21::Array<T, 3>::const_iterator it1;
  typename s21::Array<T, 3>::const_iterator it2(nullptr);

  EXPECT_TRUE(it1 == it2);
}

TYPED_TEST(ArrayTest, DefaultIteratorIsNull) {
  using T = TypeParam;
  typename s21::Array<T, 3>::iterator it1;
  typename s21::Array<T, 3>::iterator it2(nullptr);

  EXPECT_TRUE(it1 == it2);
}

TYPED_TEST(ArrayTest, ConstIteratorDecrementMovesBackward) {
  using T = TypeParam;
  const s21::Array<T, 3> arr = {T(1), T(2), T(3)};
  auto it = arr.end();
  --it;
  EXPECT_EQ(*it, T(3));
  --it;
  EXPECT_EQ(*it, T(2));
  --it;
  EXPECT_EQ(*it, T(1));
}

template <typename T>
class MapTest : public ::testing::Test {
 protected:
  s21::Map<int, T> map_;
};

TYPED_TEST_SUITE(MapTest, TestTypes);

TYPED_TEST(MapTest, DefaultConstructor) {
  EXPECT_TRUE(this->map_.empty());
  EXPECT_EQ(this->map_.size(), 0);
}

TYPED_TEST(MapTest, InitializerListConstructor) {
  s21::Map<int, TypeParam> map = {{1, TypeParam(10)}, {2, TypeParam(20)}};
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.at(1), TypeParam(10));
  EXPECT_EQ(map.at(2), TypeParam(20));
}

TYPED_TEST(MapTest, CopyConstructor) {
  this->map_.insert({1, TypeParam(10)});
  s21::Map<int, TypeParam> copy(this->map_);
  EXPECT_EQ(copy.at(1), TypeParam(10));
  EXPECT_EQ(copy.size(), 1);
}

TYPED_TEST(MapTest, MoveConstructor) {
  this->map_.insert({1, TypeParam(10)});
  s21::Map<int, TypeParam> moved(std::move(this->map_));
  EXPECT_EQ(moved.at(1), TypeParam(10));
  EXPECT_EQ(moved.size(), 1);
}

TYPED_TEST(MapTest, CopyAssignment) {
  this->map_.insert({1, TypeParam(42)});
  s21::Map<int, TypeParam> copy;
  copy = this->map_;
  EXPECT_EQ(copy.at(1), TypeParam(42));
}

TYPED_TEST(MapTest, MoveAssignment) {
  this->map_.insert({2, TypeParam(99)});
  s21::Map<int, TypeParam> moved;
  moved = std::move(this->map_);
  EXPECT_EQ(moved.at(2), TypeParam(99));
}

TYPED_TEST(MapTest, InsertAndAt) {
  this->map_.insert({5, TypeParam(100)});
  EXPECT_EQ(this->map_.at(5), TypeParam(100));
}

TYPED_TEST(MapTest, InsertOrAssign) {
  this->map_.insert({1, TypeParam(5)});
  this->map_.insert_or_assign(1, TypeParam(99));
  EXPECT_EQ(this->map_.at(1), TypeParam(99));
}

TYPED_TEST(MapTest, OperatorSquareBrackets) {
  this->map_[3] = TypeParam(15);
  EXPECT_EQ(this->map_.at(3), TypeParam(15));
}

TYPED_TEST(MapTest, Contains) {
  this->map_.insert({7, TypeParam(70)});
  EXPECT_TRUE(this->map_.contains(7));
  EXPECT_FALSE(this->map_.contains(8));
}

TYPED_TEST(MapTest, Erase) {
  auto [it, _] = this->map_.insert({9, TypeParam(90)});
  this->map_.erase(it);
  EXPECT_FALSE(this->map_.contains(9));
}

TYPED_TEST(MapTest, Find) {
  this->map_.insert({4, TypeParam(44)});
  auto it = this->map_.find(4);
  EXPECT_EQ(*it, TypeParam(44));
}

TYPED_TEST(MapTest, Clear) {
  this->map_.insert({1, TypeParam(1)});
  this->map_.clear();
  EXPECT_TRUE(this->map_.empty());
}

TYPED_TEST(MapTest, Swap) {
  s21::Map<int, TypeParam> other;
  this->map_.insert({1, TypeParam(11)});
  other.insert({2, TypeParam(22)});

  this->map_.swap(other);
  EXPECT_TRUE(this->map_.contains(2));
  EXPECT_TRUE(other.contains(1));
}

TYPED_TEST(MapTest, AtThrowsIfKeyNotFound) {
  EXPECT_THROW(this->map_.at(42), std::out_of_range);
  this->map_.insert(1, TypeParam{});
  EXPECT_THROW(this->map_.at(99), std::out_of_range);
}

TYPED_TEST(MapTest, OperatorSquareBracketsReturnsExistingValue) {
  this->map_.insert(1, TypeParam{42});
  TypeParam& value = this->map_[1];
  EXPECT_EQ(value, TypeParam{42});
  value = TypeParam{99};
  EXPECT_EQ(this->map_.at(1), TypeParam{99});
}

TYPED_TEST(MapTest, InsertOrAssignInsertsIfKeyNotFound) {
  EXPECT_EQ(this->map_.contains(42), false);
  auto result = this->map_.insert_or_assign(42, TypeParam{123});
  EXPECT_TRUE(result.second);
  EXPECT_EQ(this->map_.at(42), TypeParam{123});
}

TYPED_TEST(MapTest, BeginReturnsIteratorToFirstElement) {
  this->map_.insert(2, TypeParam{20});
  this->map_.insert(1, TypeParam{10});
  this->map_.insert(3, TypeParam{30});

  auto it = this->map_.begin();

  EXPECT_EQ(it.getKey(), 1);
  EXPECT_EQ(it.getData(), TypeParam{10});
}

TYPED_TEST(MapTest, MaxSizeReturnsPositiveValue) {
  auto max_sz = this->map_.max_size();

  EXPECT_GT(max_sz, 0u);
}

template <typename T>
class SetTest : public ::testing::Test {
 protected:
  s21::Set<T, T> set_;
};

TYPED_TEST_SUITE(SetTest, TestTypes);

TYPED_TEST(SetTest, DefaultConstructor) {
  EXPECT_TRUE(this->set_.empty());
  EXPECT_EQ(this->set_.size(), 0);
}

TYPED_TEST(SetTest, InitializerListConstructor) {
  s21::Set<TypeParam, TypeParam> set = {TypeParam(1), TypeParam(2),
                                        TypeParam(3)};
  EXPECT_EQ(set.size(), 3);
  EXPECT_TRUE(set.contains(TypeParam(1)));
  EXPECT_TRUE(set.contains(TypeParam(2)));
  EXPECT_TRUE(set.contains(TypeParam(3)));
}

TYPED_TEST(SetTest, CopyConstructor) {
  this->set_.insert(TypeParam(10));
  s21::Set<TypeParam, TypeParam> copy(this->set_);
  EXPECT_TRUE(copy.contains(TypeParam(10)));
  EXPECT_EQ(copy.size(), 1);
}

TYPED_TEST(SetTest, MoveConstructor) {
  this->set_.insert(TypeParam(42));
  s21::Set<TypeParam, TypeParam> moved(std::move(this->set_));
  EXPECT_TRUE(moved.contains(TypeParam(42)));
  EXPECT_EQ(moved.size(), 1);
}

TYPED_TEST(SetTest, CopyAssignment) {
  this->set_.insert(TypeParam(7));
  s21::Set<TypeParam, TypeParam> copy;
  copy = this->set_;
  EXPECT_TRUE(copy.contains(TypeParam(7)));
  EXPECT_EQ(copy.size(), 1);
}

TYPED_TEST(SetTest, MoveAssignment) {
  this->set_.insert(TypeParam(9));
  s21::Set<TypeParam, TypeParam> moved;
  moved = std::move(this->set_);
  EXPECT_TRUE(moved.contains(TypeParam(9)));
  EXPECT_EQ(moved.size(), 1);
}

TYPED_TEST(SetTest, Insert) {
  auto [it, inserted] = this->set_.insert(TypeParam(55));
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, TypeParam(55));

  auto [it2, inserted2] = this->set_.insert(TypeParam(55));
  EXPECT_FALSE(inserted2);  // уже существует
}

TYPED_TEST(SetTest, Contains) {
  this->set_.insert(TypeParam(1));
  EXPECT_TRUE(this->set_.contains(TypeParam(1)));
  EXPECT_FALSE(this->set_.contains(TypeParam(2)));
}

TYPED_TEST(SetTest, Erase) {
  auto [it, _] = this->set_.insert(TypeParam(88));
  this->set_.erase(it);
  EXPECT_FALSE(this->set_.contains(TypeParam(88)));
}

TYPED_TEST(SetTest, Find) {
  this->set_.insert(TypeParam(123));
  auto it = this->set_.find(TypeParam(123));
  EXPECT_EQ(*it, TypeParam(123));
}

TYPED_TEST(SetTest, Clear) {
  this->set_.insert(TypeParam(5));
  this->set_.clear();
  EXPECT_TRUE(this->set_.empty());
  EXPECT_EQ(this->set_.size(), 0);
}

TYPED_TEST(SetTest, Swap) {
  this->set_.insert(TypeParam(1));
  s21::Set<TypeParam, TypeParam> other;
  other.insert(TypeParam(2));

  this->set_.swap(other);

  EXPECT_TRUE(this->set_.contains(TypeParam(2)));
  EXPECT_TRUE(other.contains(TypeParam(1)));
}

TYPED_TEST(SetTest, Merge) {
  this->set_.insert(TypeParam(1));
  s21::Set<TypeParam, TypeParam> other = {TypeParam(2), TypeParam(1)};

  this->set_.merge(other);

  EXPECT_TRUE(this->set_.contains(TypeParam(1)));
  EXPECT_TRUE(this->set_.contains(TypeParam(2)));
  EXPECT_FALSE(other.contains(TypeParam(2)));
  EXPECT_TRUE(other.contains(TypeParam(1)));
}

TYPED_TEST(SetTest, Iterators) {
  this->set_.insert(TypeParam(10));
  this->set_.insert(TypeParam(20));
  size_t count = 0;
  for (auto it = this->set_.begin(); it != this->set_.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, this->set_.size());
}

TYPED_TEST(SetTest, MaxSizeIsGreaterThanZero) {
  EXPECT_GT(this->set_.max_size(), 0u);
}

template <typename T>
class RBTreeTest : public ::testing::Test {
 protected:
  s21::RBTree<T, T> tree;
};

TYPED_TEST_SUITE(RBTreeTest, TestTypes);

TYPED_TEST(RBTreeTest, DefaultConstructor) {
  EXPECT_EQ(this->tree.size(), 0);
  EXPECT_EQ(this->tree.root, nullptr);
}

TYPED_TEST(RBTreeTest, InsertAndFindNode) {
  this->tree.insert(TypeParam(1), true, false);
  auto node = this->tree.findNode(this->tree.root, TypeParam(1));
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->data, TypeParam(1));
}

TYPED_TEST(RBTreeTest, InsertDuplicateNotAllowed) {
  bool first = this->tree.insert(TypeParam(1), true, false);
  bool second = this->tree.insert(TypeParam(1), true, false);
  EXPECT_TRUE(first);
  EXPECT_FALSE(second);
  EXPECT_EQ(this->tree.size(), 1);
}

TYPED_TEST(RBTreeTest, InsertDuplicateAllowed) {
  bool first = this->tree.insert(TypeParam(1), true, true);
  bool second = this->tree.insert(TypeParam(1), true, true);
  EXPECT_TRUE(first);
  EXPECT_TRUE(second);
  EXPECT_EQ(this->tree.size(), 2);
}

TYPED_TEST(RBTreeTest, RemoveSingleNode) {
  this->tree.insert(TypeParam(1), true, false);
  this->tree.remove(TypeParam(1), true);
  EXPECT_EQ(this->tree.size(), 0);
  EXPECT_EQ(this->tree.findNode(this->tree.root, TypeParam(1)), nullptr);
}

TYPED_TEST(RBTreeTest, ClearTree) {
  this->tree.insert(TypeParam(1), true, false);
  this->tree.insert(TypeParam(2), true, false);
  this->tree.clear();
  EXPECT_EQ(this->tree.size(), 0);
  EXPECT_EQ(this->tree.root, nullptr);
}

TYPED_TEST(RBTreeTest, CopyConstructor) {
  this->tree.insert(TypeParam(42), true, false);
  s21::RBTree<TypeParam, TypeParam> copy(this->tree);
  EXPECT_EQ(copy.size(), 1);
  EXPECT_TRUE(copy.findNode(copy.root, TypeParam(42)));
}

TYPED_TEST(RBTreeTest, MoveConstructor) {
  this->tree.insert(TypeParam(99), true, false);
  s21::RBTree<TypeParam, TypeParam> moved(std::move(this->tree));
  EXPECT_EQ(moved.size(), 1);
  EXPECT_TRUE(moved.findNode(moved.root, TypeParam(99)));
}

TYPED_TEST(RBTreeTest, CopyAssignment) {
  this->tree.insert(TypeParam(123), true, false);
  s21::RBTree<TypeParam, TypeParam> copy;
  copy = this->tree;
  EXPECT_EQ(copy.size(), 1);
  EXPECT_TRUE(copy.findNode(copy.root, TypeParam(123)));
}

TYPED_TEST(RBTreeTest, MoveAssignment) {
  this->tree.insert(TypeParam(123), true, false);
  s21::RBTree<TypeParam, TypeParam> moved;
  moved = std::move(this->tree);
  EXPECT_EQ(moved.size(), 1);
  EXPECT_TRUE(moved.findNode(moved.root, TypeParam(123)));
}

TYPED_TEST(RBTreeTest, IteratorsForward) {
  this->tree.insert(TypeParam(2), true, false);
  this->tree.insert(TypeParam(1), true, false);
  this->tree.insert(TypeParam(3), true, false);

  auto it = this->tree.begin();
  std::vector<TypeParam> collected;
  while (it != this->tree.end()) {
    collected.push_back(*it);
    ++it;
  }

  std::sort(collected.begin(), collected.end());
  EXPECT_EQ(collected.size(), 3);
  EXPECT_EQ(collected[0], TypeParam(1));
  EXPECT_EQ(collected[1], TypeParam(2));
  EXPECT_EQ(collected[2], TypeParam(3));
}

TYPED_TEST(RBTreeTest, LowerBound) {
  this->tree.insert(TypeParam(5), true, false);
  this->tree.insert(TypeParam(10), true, false);
  this->tree.insert(TypeParam(15), true, false);

  auto it = this->tree.lower_bound(TypeParam(8));
  EXPECT_EQ(*it, TypeParam(10));
}

TYPED_TEST(RBTreeTest, UpperBound) {
  this->tree.insert(TypeParam(5), true, false);
  this->tree.insert(TypeParam(10), true, false);
  this->tree.insert(TypeParam(15), true, false);

  auto it = this->tree.upper_bound(TypeParam(10));
  EXPECT_EQ(*it, TypeParam(15));
}

TYPED_TEST(RBTreeTest, SwapTrees) {
  this->tree.insert(TypeParam(1), true, false);
  s21::RBTree<TypeParam, TypeParam> other;
  other.insert(TypeParam(2), true, false);

  this->tree.swap(other);

  EXPECT_TRUE(this->tree.findNode(this->tree.root, TypeParam(2)));
  EXPECT_TRUE(other.findNode(other.root, TypeParam(1)));
}

TYPED_TEST(RBTreeTest, MaxSizeGreaterThanZero) {
  EXPECT_GT(this->tree.max_size(), 0u);
}

TYPED_TEST(RBTreeTest, CopyTree_WithLeftChild) {
  this->tree.insert(10, true, false);
  this->tree.insert(5, true, false);
  this->tree.insert(15, true, false);

  s21::RBTree<TypeParam, TypeParam> copy = this->tree;

  EXPECT_EQ(copy.size(), 3);
  EXPECT_NE(copy.begin(), copy.end());
}

TYPED_TEST(RBTreeTest, Transplant_LeftChild) {
  this->tree.insert(10, true, false);
  this->tree.insert(5, true, false);
  this->tree.remove(5, true);

  EXPECT_EQ(this->tree.size(), 1);
}

TYPED_TEST(RBTreeTest, Transplant_RightChild) {
  this->tree.insert(10, true, false);
  this->tree.insert(15, true, false);
  this->tree.remove(15, true);

  EXPECT_EQ(this->tree.size(), 1);
}

TYPED_TEST(RBTreeTest, RemoveBinary_AllBranches) {
  this->tree.insert(10, true, false);
  this->tree.insert(5, true, false);
  this->tree.insert(15, true, false);
  this->tree.insert(3, true, false);
  this->tree.insert(7, true, false);
  this->tree.remove(3, true);
  this->tree.remove(7, true);
  this->tree.remove(5, true);

  EXPECT_GT(this->tree.size(), 0);
}

TYPED_TEST(RBTreeTest, FixInsert_RightRotationNeeded) {
  s21::RBTree<int, int> tree;
  tree.insert(10, true, false);
  tree.insert(20, true, false);
  tree.insert(15, true, false);
  EXPECT_EQ(tree.root->key, 15);
  EXPECT_EQ(tree.root->left->key, 10);
  EXPECT_EQ(tree.root->right->key, 20);
}

TYPED_TEST(RBTreeTest, RemoveBinary_OneChildRight) {
  s21::RBTree<int, int> tree;
  tree.insert(10, false, false);
  tree.insert(20, false, false);
  tree.remove(10, false);
  EXPECT_EQ(tree.root->key, 20);
}

TYPED_TEST(RBTreeTest, RemoveBinary_OneChildLeft) {
  s21::RBTree<int, int> tree;
  tree.insert(10, false, false);
  tree.insert(5, false, false);
  tree.remove(10, false);
  EXPECT_EQ(tree.root->key, 5);
}

TYPED_TEST(RBTreeTest, FixDelete_CallsAllBranches) {
  s21::RBTree<int, int> tree;
  tree.insert(10, true, false);
  tree.insert(5, true, false);
  tree.insert(15, true, false);
  tree.insert(12, true, false);
  tree.insert(18, true, false);

  tree.remove(5, true);
  EXPECT_EQ(tree.size(), 4);
}

template <typename T>
class MultiSetTest : public ::testing::Test {
 protected:
  s21::MultiSet<T, T> mset;
};

TYPED_TEST_SUITE(MultiSetTest, TestTypes);

TYPED_TEST(MultiSetTest, CopyAssignmentOperator) {
  s21::MultiSet<TypeParam, TypeParam> ms1 = {TypeParam(1)};
  s21::MultiSet<TypeParam, TypeParam> ms2;
  ms2 = ms1;
  EXPECT_EQ(ms2.size(), 1);
  EXPECT_TRUE(ms2.contains(TypeParam(1)));
}

TYPED_TEST(MultiSetTest, MoveAssignmentOperator) {
  s21::MultiSet<TypeParam, TypeParam> ms1 = {TypeParam(1)};
  s21::MultiSet<TypeParam, TypeParam> ms2;
  ms2 = std::move(ms1);
  EXPECT_EQ(ms2.size(), 1);
  EXPECT_TRUE(ms2.contains(TypeParam(1)));
}

TYPED_TEST(MultiSetTest, InitializerListConstructor) {
  s21::MultiSet<TypeParam, TypeParam> ms = {TypeParam(1), TypeParam(2),
                                            TypeParam(2), TypeParam(3)};
  EXPECT_EQ(ms.size(), 4);
  EXPECT_EQ(ms.count(TypeParam(2)), 2);
  EXPECT_TRUE(ms.contains(TypeParam(3)));
}

TYPED_TEST(MultiSetTest, CopyConstructor) {
  s21::MultiSet<TypeParam, TypeParam> original = {TypeParam(1), TypeParam(2)};
  s21::MultiSet<TypeParam, TypeParam> copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_TRUE(copy.contains(TypeParam(1)));
}

TYPED_TEST(MultiSetTest, MoveConstructor) {
  s21::MultiSet<TypeParam, TypeParam> original = {TypeParam(1), TypeParam(2)};
  s21::MultiSet<TypeParam, TypeParam> moved(std::move(original));
  EXPECT_EQ(moved.size(), 2);
  EXPECT_TRUE(moved.contains(TypeParam(2)));
}

TYPED_TEST(MultiSetTest, InsertAndSize) {
  EXPECT_TRUE(this->mset.empty());
  this->mset.insert(TypeParam(1));
  this->mset.insert(TypeParam(1));
  this->mset.insert(TypeParam(2));
  EXPECT_EQ(this->mset.size(), 3);
  EXPECT_FALSE(this->mset.empty());
}

TYPED_TEST(MultiSetTest, EraseElement) {
  auto it = this->mset.insert(TypeParam(1));
  this->mset.insert(TypeParam(2));
  EXPECT_EQ(this->mset.size(), 2);
  this->mset.erase(it);
  EXPECT_EQ(this->mset.size(), 1);
}

TYPED_TEST(MultiSetTest, ClearTest) {
  this->mset.insert(TypeParam(1));
  this->mset.insert(TypeParam(2));
  this->mset.clear();
  EXPECT_TRUE(this->mset.empty());
  EXPECT_EQ(this->mset.size(), 0);
}

TYPED_TEST(MultiSetTest, CountTest) {
  this->mset.insert(TypeParam(5));
  this->mset.insert(TypeParam(5));
  this->mset.insert(TypeParam(5));
  this->mset.insert(TypeParam(2));
  EXPECT_EQ(this->mset.count(TypeParam(5)), 3);
  EXPECT_EQ(this->mset.count(TypeParam(2)), 1);
  EXPECT_EQ(this->mset.count(TypeParam(10)), 0);
}

TYPED_TEST(MultiSetTest, FindAndContains) {
  this->mset.insert(TypeParam(7));
  this->mset.insert(TypeParam(8));
  auto it = this->mset.find(TypeParam(7));
  EXPECT_EQ(*it, TypeParam(7));
  EXPECT_TRUE(this->mset.contains(TypeParam(8)));
  EXPECT_FALSE(this->mset.contains(TypeParam(3)));
}

TYPED_TEST(MultiSetTest, EqualRangeTest) {
  this->mset.insert(TypeParam(3));
  this->mset.insert(TypeParam(3));
  this->mset.insert(TypeParam(4));
  auto range = this->mset.equal_range(TypeParam(3));
  int count = 0;
  for (auto it = range.first; it != range.second; ++it) count++;
  EXPECT_EQ(count, 2);
}

TYPED_TEST(MultiSetTest, LowerUpperBoundTest) {
  this->mset.insert(TypeParam(2));
  this->mset.insert(TypeParam(4));
  this->mset.insert(TypeParam(6));
  auto lower = this->mset.lower_bound(TypeParam(4));
  auto upper = this->mset.upper_bound(TypeParam(4));
  EXPECT_EQ(*lower, TypeParam(4));
  EXPECT_EQ(*upper, TypeParam(6));
}

TYPED_TEST(MultiSetTest, SwapTest) {
  s21::MultiSet<TypeParam, TypeParam> other;
  this->mset.insert(TypeParam(1));
  other.insert(TypeParam(2));
  this->mset.swap(other);
  EXPECT_TRUE(this->mset.contains(TypeParam(2)));
  EXPECT_TRUE(other.contains(TypeParam(1)));
}

TYPED_TEST(MultiSetTest, MergeTest) {
  s21::MultiSet<TypeParam, TypeParam> other;
  this->mset.insert(TypeParam(1));
  this->mset.insert(TypeParam(2));
  other.insert(TypeParam(3));
  other.insert(TypeParam(4));
  this->mset.merge(other);
  EXPECT_EQ(this->mset.size(), 4);
  EXPECT_TRUE(this->mset.contains(TypeParam(3)));
  EXPECT_TRUE(this->mset.contains(TypeParam(4)));
  EXPECT_EQ(other.size(), 0);
}

TYPED_TEST(MultiSetTest, MaxSizeTest) { EXPECT_GT(this->mset.max_size(), 0); }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}