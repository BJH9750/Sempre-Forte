#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <deque>

using namespace std;

class TreeNode{
public:
    int		stone;
	int		type;
	int		depth;
	int	    score;
	int		num_nodes;
	vector<struct TreeNode*>	next_nodes;

	TreeNode(int a, int b, int c)
	{
	    stone = a;
	    type = a;
	    depth = b;
	    score = a;
	    num_nodes = c;;
	};
};


void print_log(FILE *fp, TreeNode* top)
{
	const TreeNode *head = NULL;
	const TreeNode *cur = NULL;
	deque<const TreeNode *> q;
	int depth = 0;
	int i;

	head = top;
	q.push_back(head);
	while (!q.empty()) {
		cur = q.front();
		q.pop_front();
		for (auto node : cur->next_nodes) q.push_back(node);
		const TreeNode *tmp = cur;

		printf("depth:%6d\t", tmp->depth);
		for (i = 0; i < q.size() && tmp->depth == q[i]->depth;i++) printf("depth:%6d\t", q[i]->depth);
		printf("\n");
		printf("Stone:%6d\t", tmp->stone);
		for (i = 0; i < q.size() && tmp->depth == q[i]->depth;i++) printf("Stone:%6d\t", q[i]->stone);
		printf("\n");
		printf("Type :%6d\t", tmp->type);
		for (i = 0; i < q.size() && tmp->depth == q[i]->depth;i++) printf("Type :%6d\t", q[i]->type);
		printf("\n");
		printf("Score:%6d\t", tmp->score);
		for (i = 0; i < q.size() && tmp->depth == q[i]->depth;i++) printf("Score:%6d\t", q[i]->score);
		printf("\n");

		for (int j = 0; j < i; j++) {
			tmp = q.front();
			q.pop_front();
			for (auto node : tmp->next_nodes) q.push_back(node);
		}
		if (cur->depth != q[0]->depth && !q.empty()) {
			printf("================================\n");
			printf("depth : %d\n", q[0]->depth);
		}
	}
}

/*
depth:     0
Stone:     0
Type :     0
Score:     0
================================
depth : 1
depth:     1    depth:     1    depth:     1
Stone:     1    Stone:     2    Stone:     3
Type :     1    Type :     2    Type :     3
Score:     1    Score:     2    Score:     3
================================
depth : 2
depth:     2    depth:     2    depth:     2
Stone:     4    Stone:     5    Stone:     6
Type :     4    Type :     5    Type :     6
Score:     4    Score:     5    Score:     6
*/

int main()
{
    TreeNode *tmp0 = new TreeNode(0,0,3);
    TreeNode *tmp1 = new TreeNode(1,1,2);
    TreeNode *tmp2 = new TreeNode(2,1,1);
    TreeNode *tmp3 = new TreeNode(3,1,0);
    TreeNode *tmp4 = new TreeNode(4,2,0);
    TreeNode *tmp5 = new TreeNode(5,2,0);
    TreeNode *tmp6 = new TreeNode(6,2,0);


    tmp0->next_nodes.push_back(tmp1);
    tmp0->next_nodes.push_back(tmp2);
    tmp0->next_nodes.push_back(tmp3);

    tmp1->next_nodes.push_back(tmp4);
    tmp1->next_nodes.push_back(tmp5);
    tmp2->next_nodes.push_back(tmp6);

    print_log(NULL, tmp0);
}
