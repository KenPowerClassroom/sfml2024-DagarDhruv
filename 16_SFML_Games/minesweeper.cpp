#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;
const int TILE_SIZE = 32;
const int GRID_SIZE = 12;
const int MINE = 9;
const int HIDDEN = 10;
const int FLAGGED = 11;
int countMinesAround(int grid[][GRID_SIZE], int x, int y);
void initializeGrids(int grid[][GRID_SIZE ], int sgrid[][GRID_SIZE]);
void loadtexture();
void handleEvents(sf::RenderWindow &app, int grid[][GRID_SIZE], int sgrid[][GRID_SIZE]);
void renderGrid(sf::RenderWindow &app, int sgrid[][GRID_SIZE], sf::Sprite &sprite);


int minesweeper()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");
    Texture texture;
    texture.loadFromFile("images/minesweeper/tiles.jpg");
    Sprite sprite(texture);
    int grid[GRID_SIZE][GRID_SIZE];
    int sgrid[GRID_SIZE][GRID_SIZE]; //for showing

   loadtexture();
   initializeGrids(grid, sgrid);

    while (app.isOpen())
    {
        handleEvents(app, grid, sgrid);
        renderGrid(app, sgrid, sprite);
    }

    return 0;
}

int countMinesAround(int grid[][GRID_SIZE], int x, int y) {
        int n = 0;
        if (grid[x + 1][y] == MINE) n++;
        if (grid[x - 1][y] == MINE) n++;
        if (grid[x][y + 1] == MINE) n++;
        if (grid[x][y - 1] == MINE) n++;
        if (grid[x + 1][y + 1] == MINE) n++;
        if (grid[x - 1][y - 1] == MINE) n++;
        if (grid[x - 1][y + 1] == MINE) n++;
        if (grid[x + 1][y - 1] == MINE) n++;
        return n;
}
void initializeGrids(int grid[][GRID_SIZE], int sgrid[][GRID_SIZE]) {
    for (int i = 1; i <= GRID_SIZE; i++) {
        for (int j = 1; j <= GRID_SIZE; j++) {
            sgrid[i][j] = HIDDEN;
            grid[i][j] = (rand() % 5 == 0) ? MINE : 0;
        }
    }

    for (int i = 1; i <= GRID_SIZE; i++) {
        for (int j = 1; j <= GRID_SIZE; j++) {
            if (grid[i][j] != MINE)
                grid[i][j] = countMinesAround(grid, i, j);
        }
    }
}





void renderGrid(RenderWindow &app, int sgrid[][GRID_SIZE], Sprite &sprite)
{
    app.clear(Color::White);

    for (int i = 1; i <= GRID_SIZE; i++) {
        for (int j = 1; j <= GRID_SIZE; j++) {
            sprite.setTextureRect(IntRect(sgrid[i][j] * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
            sprite.setPosition(i * TILE_SIZE, j * TILE_SIZE);
            app.draw(sprite);
        }
    }

    app.display();
}

void handleEvents(RenderWindow &app, int grid[][GRID_SIZE], int sgrid[][GRID_SIZE])
{
    Event e;
    while (app.pollEvent(e)) {
        if (e.type == Event::Closed)
            app.close();

        if (e.type == Event::MouseButtonPressed) {
            Vector2i pos = Mouse::getPosition(app);
            int x = pos.x / TILE_SIZE;
            int y = pos.y / TILE_SIZE;

            if (e.mouseButton.button == Mouse::Left) {
                sgrid[x][y] = grid[x][y]; // Reveal tile
            } else if (e.mouseButton.button == Mouse::Right) {
                sgrid[x][y] = FLAGGED; // Flag tile
            }
        }
    }
}
