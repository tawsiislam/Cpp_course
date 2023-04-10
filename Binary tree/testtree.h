#include <cxxtest/TestSuite.h>
#include "bintree.cpp"


class TestSuite: public CxxTest::TestSuite{
    public:
        void testEmptyTree(void){
            Node *bintree = nullptr;
            TS_ASSERT_THROWS(find(bintree,2),out_of_range);
            TS_ASSERT_THROWS(edit(bintree,4),out_of_range);
            TS_ASSERT_THROWS(remove(bintree,1),out_of_range);
            
            TS_ASSERT_EQUALS(max_height(bintree),0);
            TS_ASSERT_EQUALS(min_height(bintree),0);
            TS_ASSERT_EQUALS(size(bintree),0);
            TS_ASSERT_EQUALS(is_balanced(bintree),true);
            delete_tree(bintree);
        }

        void testRemove(void){
            Node *bintree = nullptr;
            insert(bintree,1,1);
            insert(bintree,6,6);
            insert(bintree,2,2);
            insert(bintree,4,4);
            insert(bintree,3,3);
            insert(bintree,5,5);
            TS_ASSERT_EQUALS(size(bintree),6);
            remove(bintree,2); //Remove node with one child on right
            TS_ASSERT_EQUALS(size(bintree),5);
            TS_ASSERT_EQUALS(bintree -> right -> left -> key,4);
            TS_ASSERT_EQUALS(bintree -> right -> left -> right -> key,5);
            TS_ASSERT_EQUALS(bintree -> right -> left -> left -> key,3);            
            delete_tree(bintree);
            TS_ASSERT_EQUALS(bintree,nullptr);
            
            insert(bintree,1,1);
            insert(bintree,4,4);
            insert(bintree,7,7);
            insert(bintree,6,6);
            insert(bintree,5,5);
            TS_ASSERT_EQUALS(size(bintree),5);
            remove(bintree,7);  //Remove node with one child on left
            TS_ASSERT_EQUALS(bintree -> right -> right -> key,6);
            TS_ASSERT_EQUALS(bintree -> right -> right -> right,nullptr);
            TS_ASSERT_EQUALS(bintree -> right -> right -> left -> key, 5);
            TS_ASSERT_EQUALS(size(bintree),4);
            delete_tree(bintree);

            insert(bintree,1,1);
            insert(bintree,4,4);
            insert(bintree,7,7);
            insert(bintree,5,5);
            insert(bintree,6,6);
            TS_ASSERT_EQUALS(size(bintree),5);
            remove(bintree,7);  //Same as above, but different with 5 and 6
            TS_ASSERT_EQUALS(bintree -> right -> right -> key,5);
            TS_ASSERT_EQUALS(bintree -> right -> right -> left,nullptr);
            TS_ASSERT_EQUALS(bintree -> right -> right -> right -> key, 6);
            TS_ASSERT_EQUALS(size(bintree),4);
            delete_tree(bintree);
            
            insert(bintree,1,1);
            insert(bintree,3,3);
            insert(bintree,2,2);
            insert(bintree,4,4);
            insert(bintree,5,5);
            remove(bintree,3); //Remove node with two child
            TS_ASSERT_EQUALS(bintree -> right -> key,4);
            TS_ASSERT_EQUALS(bintree -> right -> left -> key,2);
            TS_ASSERT_EQUALS(bintree -> right -> right -> key,5);
            delete_tree(bintree);
        }

        void testSizeOneTree(void){
            Node *bintree = nullptr;
            insert(bintree,3,1.01);
            TS_ASSERT_EQUALS(bintree -> key,3);
            TS_ASSERT_EQUALS(bintree -> data,1.01);
            TS_ASSERT_THROWS_ANYTHING(edit(bintree,2)); //Checks throwing out of range (My compiler gave error with TS_Assert_Throw sometimes in some places)
            TS_ASSERT_THROWS_ANYTHING(find(bintree,1));
            edit(bintree,3) = 2;
            TS_ASSERT_EQUALS(find(bintree,3),2);
            insert(bintree,3,3);    //Test overwriting
            TS_ASSERT_EQUALS(find(bintree,3),3);
            TS_ASSERT_EQUALS(max_height(bintree),1);
            TS_ASSERT_EQUALS(min_height(bintree),1);
            TS_ASSERT_EQUALS(size(bintree),1);
            TS_ASSERT_EQUALS(is_balanced(bintree),true);
            remove(bintree,3);
            TS_ASSERT_THROWS_ANYTHING(find(bintree,3)); //Checks out of range throwing
            TS_ASSERT_THROWS_ANYTHING(remove(bintree,3));
            delete_tree(bintree);
            TS_ASSERT_EQUALS(bintree,nullptr);
        }

        void testLargeTreeUnbalanced(void){
            Node *bintree = nullptr;
            insert(bintree,6,6);
            insert(bintree,5,5);
            insert(bintree,2,2);
            insert(bintree,1,1);
            insert(bintree,9,9);
            TS_ASSERT_EQUALS(find(bintree,1),1);
            TS_ASSERT_EQUALS(find(bintree,2),2);
            TS_ASSERT_EQUALS(min_height(bintree),2);
            TS_ASSERT_EQUALS(max_height(bintree),4);
            TS_ASSERT_EQUALS(size(bintree),5);
            TS_ASSERT_EQUALS(is_balanced(bintree),false);
            edit(bintree,5) = 7;
            TS_ASSERT_EQUALS(find(bintree,5),7);
            auto leftTree = bintree -> left;    //Used to check tree on left side is correct
            remove(bintree,6);
            TS_ASSERT_EQUALS(bintree -> key, 9);    //check 9 is the new root node
            TS_ASSERT_EQUALS(bintree -> data, 9);
            TS_ASSERT_EQUALS(bintree->right,nullptr);
            TS_ASSERT_EQUALS(bintree->left, leftTree);
            TS_ASSERT_EQUALS(size(bintree),4);
            delete_tree(bintree);
        }

        void testLargeTreeBalanced(void){
            Node *bintree = nullptr;
            insert(bintree,5,5);
            insert(bintree,7,7);
            insert(bintree,2,2);
            insert(bintree,1,1);
            insert(bintree,6,6);
            insert(bintree,9,9);
            insert(bintree,3,3);
            TS_ASSERT_EQUALS(is_balanced(bintree),true);
            TS_ASSERT_EQUALS(max_height(bintree),3);
            TS_ASSERT_EQUALS(min_height(bintree),3);
            TS_ASSERT_EQUALS(size(bintree),7);
            TS_ASSERT_EQUALS(find(bintree,3),3);
            remove(bintree,3);
            TS_ASSERT_EQUALS(size(bintree),6);
            TS_ASSERT_EQUALS(is_balanced(bintree),true);
            TS_ASSERT_EQUALS(bintree->left->right,nullptr); //Check the 3 is not there anymore
            remove(bintree,2);
            TS_ASSERT_EQUALS(bintree->left->key,1);
            remove(bintree,7);
            auto rightTree = bintree->right;    //used to check tree on right side is correct
            TS_ASSERT_EQUALS(rightTree->key,9); 
            TS_ASSERT_EQUALS(rightTree->left->key,6);
            TS_ASSERT_EQUALS(rightTree->right,nullptr);
            TS_ASSERT_EQUALS(is_balanced(bintree),true);
            TS_ASSERT_EQUALS(size(bintree),4);
            TS_ASSERT_THROWS(remove(bintree,2),out_of_range);
            TS_ASSERT_THROWS(edit(bintree,2),out_of_range);
            TS_ASSERT_THROWS(find(bintree,2),out_of_range);
            delete_tree(bintree);
        }
};