#include <iostream>
#include <string>
using namespace std;

#define   size   100

typedef struct
{
        // (x, y) represents chess board coordinates
        // distance represent its minimum distance from the source
        int x, y, distance;
} itemtype;

struct queuetype
{ itemtype items [size];
  int front, rear;
};

typedef struct queuetype queue;


#define N 8

// Below arrays details all 8 possible movements
// for a knight
int row[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int col[] = { -1, 1, 1, -1, 2, -2, 2, -2 };
int visited[8][8] = {{0},{0}, {0},{0}, {0},{0}, {0},{0}};

// Check if (x, y) is valid chess board coordinates
// Note that a knight cannot go out of the chessboard

bool valid(int x, int y)
{
        if (x < 0 || y < 0 || x >= N || y >= N)
                return false;
        return true;
}

// queue node used in BFS

int empty(queue q)
{
        return q.front == q.rear;
}

int full(queue q)
{
        return q.front == (q.rear+1)%size;
}

void clear(queue & q)
{
        q.front = q.rear = 0;
}

void insert(queue &q , itemtype i)
{   if (!full(q))
        {  q.rear = (q.rear+1)%size;
           q.items[q.rear] = i;
    }
    else cout << "Queue is full";
}

itemtype remove (queue &q)
{   if(!empty(q))
     { q.front = (q.front+1)%size;
           return q.items[q.front];
     }
    else
           cout << "Queue is empty";
}



// Find minimum number of steps taken by the knight
// from source to reach destination using BFS
int BFS(itemtype src, itemtype dest)
{
        // set to check if matrix cell is visited before or not
        
//      visited[src.x][src.y] = 1;
        // create a queue and enqueue first node
        queue q;
        clear(q);
        insert(q, src);

        // run till queue is not empty
        while (!empty(q))
        {
                // pop front node from queue and process it
                itemtype node = remove(q);

                int x = node.x;
                int y = node.y;
                int distance = node.distance;
                
                // if destination is reached, return distance
                if (x == dest.x && y == dest.y)
                        return distance;

                // Skip if location is visited before
                if (!visited[node.x][node.y])
                {
                        // mark current node as visited
                        visited[node.x][node.y] = 1;

                        // check for all 8 possible movements for a knight
                        // and enqueue each valid movement into the queue
                        for (int i = 0; i < 8; ++i)
                        {
                                // Get the new valid position of Knight from current
                                // position on chessboard and enqueue it in the
                                // queue with +1 distance
                                int x1 = x + row[i];
                                int y1 = y + col[i];
                                int d1 = distance + 1;
                                node.x = x1; node.y = y1; node.distance = d1;
                                if (valid(x1, y1) && !visited[x1][y1])
                                        insert(q,node);
                        }
                }
        }

        // return INFINITY if path is not possible
        return INT_MAX;
}

// main function
int main()
{
        // source coordinates
        itemtype src = {0, 7, 0};
    
        // destination coordinates
        itemtype dest = {7, 0, 0};

        cout << "Minimum number of steps required is " << BFS(src, dest);
        

        return 0;
}

