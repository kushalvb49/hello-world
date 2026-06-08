#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 24

#define EMPTY '_'
#define PIXEL '*'

char picture[HEIGHT][WIDTH];

void clearPicture() {
    /*
        TODO:
        Fill the entire 2D array picture with EMPTY character '_'.
    */
}

void displayPicture() {
    /*
        TODO:
        Print the 2D picture array row by row.
    */
}

void setPixel(int x, int y) {
    /*
        TODO:
        If x and y are inside the canvas,
        set picture[y][x] to PIXEL character '*'.
    */
}

void drawLine(int x1, int y1, int x2, int y2) {
    /*
        TODO:
        Draw a line from (x1, y1) to (x2, y2)
        using the '*' character.
    */
}

void drawRectangle(int x1, int y1, int x2, int y2) {
    /*
        TODO:
        Draw a rectangle using four lines.
        Top-left corner is (x1, y1).
        Bottom-right corner is (x2, y2).
    */
}

void drawCircle(int cx, int cy, int radius) {
    /*
        TODO:
        Draw a circle with center (cx, cy)
        and given radius using '*'.
    */
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    /*
        TODO:
        Draw a triangle by joining the three given points.
    */
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
        printf("0. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        if (choice == 1) {
            int x1, y1, x2, y2;

            printf("Enter x1 y1 x2 y2: ");
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

            drawLine(x1, y1, x2, y2);
        }
        else if (choice == 2) {
            int x1, y1, x2, y2;

            printf("Enter top-left x y and bottom-right x y: ");
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

            drawRectangle(x1, y1, x2, y2);
        }
        else if (choice == 3) {
            int cx, cy, radius;

            printf("Enter center x y and radius: ");
            scanf("%d %d %d", &cx, &cy, &radius);

            drawCircle(cx, cy, radius);
        }
        else if (choice == 4) {
            int x1, y1, x2, y2, x3, y3;

            printf("Enter x1 y1 x2 y2 x3 y3: ");
            scanf("%d %d %d %d %d %d",
                  &x1, &y1, &x2, &y2, &x3, &y3);

            drawTriangle(x1, y1, x2, y2, x3, y3);
        }
        else if (choice == 5) {
            printf("The picture is:\n");
            displayPicture();
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
