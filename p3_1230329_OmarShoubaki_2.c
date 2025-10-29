// Omar Shoubaki 1230329 sec:2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXCITIES 200
#define NAMELEN 50
int cityCount = 0;

typedef struct Edge{
    int c1;
    int c2;
    int distance;
}Edge;
typedef struct Graph {
    int V;
    int E;
    Edge roads[MAXCITIES * MAXCITIES];
    char cities[MAXCITIES][NAMELEN];
} Graph;
typedef struct UnionFind {// used in kruskal
    int leader[MAXCITIES];
    int rank[MAXCITIES];
} UnionFind;

void loadCities(Graph *);
void toLowerCase(char*);
int addCity(Graph *, char *);
int getCityIndex(Graph *, char*);
void applyPrim(Graph*, int);
void applyKruskal(Graph*, int);
void makeSet(UnionFind*,int);
int find(UnionFind*,int);
void mergeSets(UnionFind*,int,int);
void heapify(Edge[],int,int);
void buildMinHeap(Edge [],int);
Edge getMin(Edge[],int*);


int main()
{
    printf("\nWelcome to my Palestinian cities road network\n");
    int choice=0;
    Graph g= {0};
    while(choice!=5){
        printf("\nPlease select an operation 1-5: \n");
        printf("1) Load cities\n");
        printf("2) Apply Prim's Algorithm\n");
        printf("3) Apply Kruskal's Algorithm\n");
        printf("4) Compare both Algorithms\n");
        printf("5) Exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: loadCities(&g);
            break;
            case 2:
                applyPrim(&g, 1);
                break;
            case 3:
                applyKruskal(&g, 1);
                break;
            case 4:
                applyPrim(&g,0);
                applyKruskal(&g,0);
                break;
            case 5: printf("\n Thanks for using my cities road network\n");
            break;
            default: printf("\nPlease enter a number 1-5 \n");



        }
    }

}
void loadCities(Graph *graph) {
    FILE *file = fopen("cities.txt", "r");
    if (!file) {
        printf("File not found\n");
        return;
    }


    char line[200];
    char city1[NAMELEN], city2[NAMELEN];
    int dist;

    cityCount = 0;
    graph->E = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        char *token1 = strtok(line, "#");
        char *token2 = strtok(NULL, "#");
        char *token3 = strtok(NULL, "#");

        if (token1 && token2 && token3) {
            strcpy(city1, token1);
            strcpy(city2, token2);
            dist = atoi(token3);

            int u = addCity(graph, city1);
            int v = addCity(graph, city2);
            if (u == -1 || v == -1) {
                printf("Skipping invalid edge: %s - %s\n", city1, city2);
                continue;
            }

            graph->roads[graph->E].c1 = u;
            graph->roads[graph->E].c2 = v;
            graph->roads[graph->E].distance = dist;
            graph->E++;
        }
    }

    graph->V = cityCount;
    fclose(file);
    printf("\nCities loaded successfully: %d cities, %d roads\n", graph->V, graph->E);
}
void toLowerCase(char* input) {
    for (int i = 0; input[i]; i++) {
        input[i] = tolower(input[i]);
    }
}
int addCity(Graph *g, char *name) {
    char lower[NAMELEN];
    strcpy(lower,name);
    toLowerCase(lower);

    for (int i = 0; i < cityCount; i++) {
        char temp[NAMELEN];
        strcpy(temp, g->cities[i]);
        toLowerCase(temp);
        if (strcmp(temp, lower) == 0) {
            return i;
        }
    }
    if (cityCount >= MAXCITIES) {
        printf("Cannot add more cities max cities %d reached\n", MAXCITIES);
        return -1;
    }
    strcpy(g->cities[cityCount], name);
    return cityCount++;
}
int getCityIndex(Graph *g, char *name) {
    toLowerCase(name);

    for (int i = 0; i < cityCount; i++) {
        char temp[NAMELEN];
        strcpy(temp, g->cities[i]);
        toLowerCase(temp);
        if (strcmp(temp, name) == 0) {
            return i;
        }
    }

    return -1;
}
void applyPrim(Graph *g, int p) {// p is for printing
    char startCity[NAMELEN];
    printf("Enter the city you wish to start from: ");
    scanf("%s", startCity);
    int startIndex = getCityIndex(g, startCity);
    if (startIndex == -1) {
        printf("\n%s not found in graph, could not perform Prim's Algorithm\n", startCity);
        return;
    }
    int V= g->V; //number of cities
    int connected[MAXCITIES];// to see which cities is connected
    int minDist[MAXCITIES];
    int inMST[MAXCITIES];// checks if the city is in the mst
    int totalCost = 0;// total distance
    for (int i = 0; i < V; i++) {
        minDist[i] = 1e9;// initial distance for all cities but the starting point is infinity at first
        inMST[i] = 0;// marked as not in mst
        connected[i] = -1;// not connected to any city yet
    }

    minDist[startIndex] = 0;// distance between start city and itself is zero
    clock_t start = clock();
    for (int count = 0; count < V - 1; count++) {
        int minValue = 1e9;
        int u = -1;
        for (int i = 0; i < V; i++) {// check for the smallest distance to add to the mst
            if (!inMST[i] && minDist[i] < minValue) {
                minValue = minDist[i];
                u = i;
            }
        }
        if (u == -1){
            break;}
        inMST[u] = 1;
        for (int i = 0; i < g->E; i++) {
            int v = -1;
            if (g->roads[i].c1 == u) {// checks if any of the roads is connected to the newly added city to the mst
                    v = g->roads[i].c2;}
            else if (g->roads[i].c2 == u) {
                    v = g->roads[i].c1;}
             if (v != -1 && !inMST[v] && g->roads[i].distance < minDist[v]) {
                minDist[v] = g->roads[i].distance;
                connected[v] = u;
            }
        }
    }
    clock_t end= clock();
    if(p==1){
      printf("\nPrim's MST starting from %s:\n", g->cities[startIndex]);}
    for (int i = 0; i < V; i++) {
        if (connected[i] != -1) {
                if(p==1){
            printf("%s - %s: %d\n", g->cities[connected[i]], g->cities[i], minDist[i]);}
            totalCost += minDist[i];
        }
    }

    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nPrim's Algorithm stats:\n");
    printf("\nTotal cost: %d\n", totalCost);
    printf("Execution time: %f seconds\n", timeTaken);
}
void makeSet(UnionFind* x, int n) {
    for (int i = 0; i < n; i++) {
        x->leader[i] = i;// making every city its own leader in the mst
        x->rank[i] = 0;// since each city is its own tree every tree height is 0 when initializing
    }
}
int find(UnionFind* u, int i) {// find the leader/root of whatever city
    if (u->leader[i] != i){
        u->leader[i] = find(u, u->leader[i]);
    }
    return u->leader[i];
}
void mergeSets(UnionFind* u, int x,int y){// used to merge two trees together
    int rootX= find(u,x);
    int rootY= find(u,y);
    if(rootX!=rootY){
        if(u->rank[rootX]< u->rank[rootY]){
            u->leader[rootX]= rootY;
        }
        else if (u->rank[rootY]< u->rank[rootX]){
                u->leader[rootY]= rootX;

        }
        else {
            u->leader[rootY] = rootX;
            u->rank[rootX]++;

    }

}
}

void heapify(Edge heap[], int n, int i) {
    int smallest = i;// assuming the minimum value is at i at first
    int l = 2 * i + 1;//index of the city on the left in the tree
    int r = 2 * i + 2;// index of the city on the right in the tree
    if(l<n&& heap[l].distance<heap[smallest].distance){//checks if the left child exists(it exists if the result of the eq is less than the number of cities n
        smallest=l;//set smallest index to the left child
    }
    if(r<n&& heap[r].distance<heap[smallest].distance){//checks if the right child exists(it exists if the result of the eq is less than the number of cities n
        smallest=r;
    }
    if (smallest != i) {//if the left or right child had a smaller distance that i
    Edge temp = heap[i];// swaps the heaps around
    heap[i] = heap[smallest];
    heap[smallest] = temp;
    heapify(heap, n, smallest);// recursive calls until we make sure we finally have a min heap
}}

void buildMinHeap(Edge heap[], int n) {
    for (int i = (n / 2 )- 1; i >= 0; i--)// eq for the last non-leaf node is (n/2)-1
        heapify(heap, n, i);
}

Edge getMin(Edge heap[], int* size) {//this function removes the root(city with smallest distance);
    Edge root = heap[0];
    heap[0] = heap[*size - 1];//in heaps when we remove the root we replace it with last index in array
    (*size)--;
    heapify(heap, *size, 0);//we heapify it again to ensure its always a min heap
    return root;
}
void applyKruskal(Graph* g, int p) {
    int V = g->V;//number of cities
    int E = g->E;//number of roads

    Edge heap[MAXCITIES * MAXCITIES];
    for (int i = 0; i < E; i++) {//copies all the road from the graph into a heap array
        heap[i] = g->roads[i];
    }

    buildMinHeap(heap, E);//builds a min heap based on the distances between the roads

    UnionFind u;
    makeSet(&u, V);
    int totalCost = 0;
    int edgeCount = 0;
    clock_t start = clock();
     while (edgeCount < V - 1 && E > 0) {// building the mst until we have v-1 edges
        Edge minEdge = getMin(heap, &E);//get the smallest edge also incrementing the number of edges
        int group1 = find(&u, minEdge.c1);// finds the current leader of c1 and c2 that are connected by minEdge
        int group2 = find(&u, minEdge.c2);
        if (group1 != group2) {//if they dont have the same leader it means adding them wont make a cycle
            if(p==1){
            printf("%s - %s: %d\n", g->cities[minEdge.c1], g->cities[minEdge.c2], minEdge.distance);}
            totalCost += minEdge.distance;
            mergeSets(&u, group1, group2);
            edgeCount++;
        }
    }
    clock_t end = clock();
    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nKruskal's Algorithm stats:\n");
    printf("\nTotal cost: %d\n", totalCost);
    printf("Execution time: %f seconds\n", timeTaken);
}




