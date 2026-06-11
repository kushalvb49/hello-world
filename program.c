#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 24

#define EMPTY '_'
#define PIXEL '*'
#define MAX_OBJECTS 50

char picture[HEIGHT][WIDTH];

struct Shape {
    int id;
    int type;   // 1-Line, 2-Rectangle, 3-Circle, 4-Triangle
    int x1, y1, x2, y2, x3, y3;
    int radius;
};

struct Shape objects[MAX_OBJECTS];
int objectCount = 0;
int nextId = 1;

void clearPicture() {
    int i, j;

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            picture[i][j] = EMPTY;
        }
    }
}

void displayPicture() {
    int i, j;

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            printf("%c", picture[i][j]);
        }
        printf("\n");
    }
}

void setPixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        picture[y][x] = PIXEL;
    }
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx, sy, err, e2;

    if (x1 < x2)
        sx = 1;
    else
        sx = -1;

    if (y1 < y2)
        sy = 1;
    else
        sy = -1;

    err = dx - dy;

    while (1) {
        setPixel(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        e2 = 2 * err;

        if (e2 > -dy) {
            err = err - dy;
            x1 = x1 + sx;
        }

        if (e2 < dx) {
            err = err + dx;
            y1 = y1 + sy;
        }
    }
}

void drawRectangle(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y1);
    drawLine(x2, y1, x2, y2);
    drawLine(x2, y2, x1, y2);
    drawLine(x1, y2, x1, y1);
}

void drawCircle(int cx, int cy, int radius) {
    int x, y;
    int value;

    for (y = -radius; y <= radius; y++) {
        for (x = -radius; x <= radius; x++) {
            value = x * x + y * y;

            if (value >= radius * radius - radius &&
                value <= radius * radius + radius) {
                setPixel(cx + x, cy + y);
            }
        }
    }
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

void addObject(int type, int x1, int y1, int x2, int y2, int x3, int y3, int radius) {
    if (objectCount >= MAX_OBJECTS) {
        printf("Object limit reached.\n");
        return;
    }
    objects[objectCount].id = nextId;
    objects[objectCount].type = type;
    objects[objectCount].x1 = x1;
    objects[objectCount].y1 = y1;
    objects[objectCount].x2 = x2;
    objects[objectCount].y2 = y2;
    objects[objectCount].x3 = x3;
    objects[objectCount].y3 = y3;
    objects[objectCount].radius = radius;

    printf("Object added with ID %d\n", nextId);

    objectCount++;
    nextId++;
}

void redrawPicture() {
    int i;

    clearPicture();

    for (i = 0; i < objectCount; i++) {
        if (objects[i].type == 1) {
            drawLine(objects[i].x1, objects[i].y1,
                     objects[i].x2, objects[i].y2);
        }
        else if (objects[i].type == 2) {
            drawRectangle(objects[i].x1, objects[i].y1,
                          objects[i].x2, objects[i].y2);
        }
        else if (objects[i].type == 3) {
            drawCircle(objects[i].x1, objects[i].y1,
                       objects[i].radius);
        }
        else if (objects[i].type == 4) {
            drawTriangle(objects[i].x1, objects[i].y1,
                         objects[i].x2, objects[i].y2,
                         objects[i].x3, objects[i].y3);
        }
    }
}   

void listObjects() {
    int i;

    if (objectCount == 0) {
        printf("No objects added.\n");
        return;
    }

    printf("\nObject List:\n");

    for (i = 0; i < objectCount; i++) {
        printf("ID: %d  Type: ", objects[i].id);

        if (objects[i].type == 1)
            printf("Line\n");
        else if (objects[i].type == 2)
            printf("Rectangle\n");
        else if (objects[i].type == 3)
            printf("Circle\n");
        else if (objects[i].type == 4)
            printf("Triangle\n");
    }
}

void deleteObject() {
    int id, i, j;
    int found = 0;

    printf("Enter object ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < objectCount; i++) {
        if (objects[i].id == id) {
            found = 1;

            for (j = i; j < objectCount - 1; j++) {
                objects[j] = objects[j + 1];
            }

            objectCount--;
            break;
        }
    }

    if (found == 1) {
        redrawPicture();
        printf("Object deleted successfully.\n");
    }
    else {
        printf("Object not found.\n");
    }
}

void modifyObject() {
    int id, i;
    int found = 0;

    printf("Enter object ID to modify: ");
    scanf("%d", &id);

    for (i = 0; i < objectCount; i++) {
        if (objects[i].id == id) {
            found = 1;

            if (objects[i].type == 1 || objects[i].type == 2) {
                printf("Enter new x1 y1 x2 y2: ");
                scanf("%d %d %d %d",
                      &objects[i].x1, &objects[i].y1,
                      &objects[i].x2, &objects[i].y2);
            }
            else if (objects[i].type == 3) {
                printf("Enter new center x y and radius: ");
                scanf("%d %d %d",
                      &objects[i].x1, &objects[i].y1,
                      &objects[i].radius);
            }
            else if (objects[i].type == 4) {
                printf("Enter new x1 y1 x2 y2 x3 y3: ");
                scanf("%d %d %d %d %d %d",
                      &objects[i].x1, &objects[i].y1,
                      &objects[i].x2, &objects[i].y2,
                      &objects[i].x3, &objects[i].y3);
            }

            break;
        }
    }

    if (found == 1) {
        redrawPicture();
        printf("Object modified successfully.\n");
    }
    else {
        printf("Object not found.\n");
    }
}

void clearAllObjects() {
    objectCount = 0;
    clearPicture();
    printf("All objects cleared.\n");
}

int main() {
    int choice;

    clearPicture();

    printf("2D Graphics Editor\n");
    printf("Canvas size: %d x %d\n", WIDTH, HEIGHT);
    printf("Use coordinates x y.\n");
    printf("x range: 0 to %d\n", WIDTH - 1);
    printf("y range: 0 to %d\n", HEIGHT - 1);

    while (1) {
        printf("\nMenu\n");
        printf("1. Draw Line\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Circle\n");
        printf("4. Draw Triangle\n");
        printf("5. Display Picture\n");
        printf("6. List Objects\n");
        printf("7. Delete Object\n");
        printf("8. Modify Object\n");
        printf("9. Clear All Objects\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        if (choice == 1) {
            int x1, y1, x2, y2;

            printf("Enter x1 y1 x2 y2: ");
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

            drawLine(x1, y1, x2, y2);
            addObject(1, x1, y1, x2, y2, 0, 0, 0);
        }
        else if (choice == 2) {
            int x1, y1, x2, y2;

            printf("Enter top-left x y and bottom-right x y: ");
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

            drawRectangle(x1, y1, x2, y2);
            addObject(2, x1, y1, x2, y2, 0, 0, 0);
        }
        else if (choice == 3) {
            int cx, cy, radius;

            printf("Enter center x y and radius: ");
            scanf("%d %d %d", &cx, &cy, &radius);

            drawCircle(cx, cy, radius);
            addObject(3, cx, cy, 0, 0, 0, 0, radius);
        }
        else if (choice == 4) {
            int x1, y1, x2, y2, x3, y3;

            printf("Enter x1 y1 x2 y2 x3 y3: ");
            scanf("%d %d %d %d %d %d",
                  &x1, &y1, &x2, &y2, &x3, &y3);

            drawTriangle(x1, y1, x2, y2, x3, y3);
            addObject(4, x1, y1, x2, y2, x3, y3, 0);
        }
        else if (choice == 5) {
            redrawPicture();
            printf("The picture is:\n");
            displayPicture();
        }
        else if (choice == 6) {
            listObjects();
        }
        else if (choice == 7) {
            deleteObject();
        }
        else if (choice == 8) {
            modifyObject();
        }
        else if (choice == 9) {
            clearAllObjects();
        }
        else if (choice == 0) {
            printf("Exiting program.\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}