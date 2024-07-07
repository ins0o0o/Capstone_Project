#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UNSEEN (-INT_MAX)
#define MAX_NODE 100

int GM[MAX_NODE][MAX_NODE];

int distance[MAX_NODE];
int check[MAX_NODE];
int parent[MAX_NODE];
FILE* fp;


int name2int(char c) {
	return c - 'A'; // A부터 0 B는1을 반환하기 위한 문자
}
char int2name(int i) {
	return i + 'A';
}


void input_adjmatrix_Dijkstra(int g[][MAX_NODE], int* V, int* E)
{
	char vertex[3];
	int i, j, k, w;
	printf("\nInput number of nodes and edges\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			g[i][j] = 1000;
	for (i = 0; i < *V; i++)
		g[i][i] = 0;

	printf("\nInput two nodes consisting of edge --> ");

	for (k = 0; k < *E; k++) {
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		g[i][j] = w;
		g[j][i] = w;
	}
}

void print_adjmatrix(int a[][MAX_NODE], int V)
{
	int i, j;
	printf("   "); // 칸맞추기용
	for (i = 0; i < V; i++)
		printf("%7c", int2name(i));
	printf("\n");
	for (i = 0; i < V; i++) {
		printf("%7c", int2name(i));
		for (j = 0; j < V; j++)
			printf("%7d", a[i][j]);
		printf("\n");
	}
}



//--------------------------------------------------------------




void print_tree(int p[], int V)
{
	printf("\n--Tree structure--\n");
	//node의 개수만큼 알파벳 순차출력
	printf("Son:    ");
	for (int i = 0; i < V; i++)
		printf("%c ", int2name(i));
	printf("\n-----------------------------");
	//해당 노드의 부모 노드 출력(첫번째 노드는 .)
	printf("\nParent: ");
	for (int i = 0; i < V; i++)
		printf("%c ", int2name(p[i]));

	printf("\n");
}

int print_cost(int w[], int V)
{
	int cost = 0;
	// 최소비용은 weight를 모두 더한 값
	for (int i = 1; i < V; i++) { //뿌리노드는 안더함 1부터 시작함으로써

		cost += w[i];
	}
	printf("%d", cost);
	return cost;
}

void print_distance(int a[], int s, int V)
{
	printf("%5c", int2name(s));

	for (int j = 0; j < V; j++)
	{
		printf("%5d", distance[j]);
	}
	printf("\n");
}


//--------------------------------------------------------------


void dijkstra(int a[][MAX_NODE], int s, int V) {
	int x, y, d;
	int i, checked = 0;
	for (x = 0; x < V; x++) {
		distance[x] = a[s][x]; // s가 시작 행 그래서 main에서 s를 입력받고 0부터 쭉 distance 입력
		if (x != s) parent[x] = s; // 대각 행렬이 아니면 x의 부모는 s이다. s가 집어넣었기 때문
	}
	check[s] = 1; // 방문했음을 표시
	checked++;
	print_distance(distance, s, V); // 일단 한줄 출력
	while (checked < V) { // 알파벳 갯수보다 작으면 반복 why?  같으면 다 된거니까 checked는 0부터 시작해서 올라왔기 때문에
		x = 0; // x를 0부터 다시 시작
		while (check[x]) x++; // 방문하지 않은 첫번째 노드 찾기
		for (i = x; i < V; i++) // x는 방문하지 않은 첫번째 노드
			if (check[i] == 0 && distance[i] < distance[x]) x = i; // 방문하지 않은 노드중 가장 최단 거리 찾기
		check[x] = 1; //방문했다.
		checked++; // 방문한 노드 수 증가
		for (y = 0; y < V; y++) {
			if (x == y || a[x][y] >= 1000 || check[y]) continue; //자기 자신, 1000이상, 이미 방문했으면 넘어가기
			d = distance[x] + a[x][y]; // 선택한 노드중 다른 노드로 가는 거리 더하기
			if (d < distance[y]) { // 원래 가중치 값보다 더한 값이 더 작다면
				distance[y] = d; // 거리 갱신
				parent[y] = x; // 부모 갱신
			}
		}
		print_distance(distance, x, V); // 출력
	}
}


void main()
{
	int V, E;
	fp = fopen("graph_simple.txt", "rt");

	input_adjmatrix_Dijkstra(GM, &V, &E);
	printf("\n");


	dijkstra(GM, 2, V);

	printf("\n");

	print_tree(parent, V);
	fclose(fp);
	printf("\n");
}