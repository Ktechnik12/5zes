#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <memory>
// Klasa reprezentująca canvas
class Canvas {
protected:
    int width;
    int height;
    std::vector<std::string> pixels;

public:
    Canvas(int w, int h) : width(w), height(h) {
        pixels.resize(height, std::string(width, ' '));
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    void draw() const {
        std::cout << "|";
        for (int i = 0; i < width; ++i) {
            std::cout << "=";
        }
        std::cout << "|" << std::endl;
        int i = 1;
        for (const auto& row : pixels) {
            std::cout << i << "\t|" << row << "|" << std::endl;
            i++;
        }

        std::cout << "|";
        for (int i = 0; i < width; ++i) {
            std::cout << "=";
        }
        std::cout << "|" << std::endl;
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << "|";
            for (int i = 0; i < width; ++i) {
                file << "=";
            }
            file << "|" << std::endl;

            for (const auto& row : pixels) {
                file << "|" << row << "|" << std::endl;
            }

            file << "|";
            for (int i = 0; i < width; ++i) {
                file << "=";
            }
            file << "|" << std::endl;

            file.close();
        }
    }

    void setPixel(int x, int y, char symbol) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y][x] = symbol;
        }
    }
};

// Klasa abstrakcyjna reprezentująca figurę
class Figure {
public:
    virtual ~Figure() {}
    virtual void draw(Canvas& canvas) = 0;
};

// Kwadrat
class Square : public Figure {
private:
    int centerX;
    int centerY;
    int size;
    char symbol;

public:
    Square(int x, int y, int s, char sym) : centerX(x), centerY(y), size(s), symbol(sym) {}

    void draw(Canvas& canvas) override {
        int startX = centerX - size / 2;
        int startY = centerY - size / 2;

        for (int y = startY; y < startY + size; ++y) {
            for (int x = startX; x < startX + size; ++x) {
                canvas.setPixel(x, y, symbol);
            }
        }
    }
};

// Kolo
class Circle : public Figure {
private:
    int centerX;
    int centerY;
    int radius;
    char symbol;

public:
    Circle(int x, int y, int r, char sym)
        : centerX(x), centerY(y), radius(r), symbol(sym) {}

    virtual void draw(Canvas& canvas) {
        for (int y = centerY - radius; y <= ((centerY + radius)); ++y) {
            for (int x = centerX - radius; x <= centerX + radius; ++x) {
                if (isInside(x, y)) {
                    canvas.setPixel(x, y, symbol);
                }
            }
        }
    }

private:
    bool isInside(int x, int y) {
        int dx = x - centerX;
        int dy = y - centerY;
        return dx * dx + dy * dy <= radius * radius;
    }
};

// Trojkat1 prawo >
class Triangle1 : public Figure {
private:
    int centerX;
    int centerY;
    int size;
    char symbol;

public:
    Triangle1(int x, int y, int r, char sym)
        : centerX(x), centerY(y), size(r), symbol(sym) {}

    virtual void draw(Canvas& canvas) {
        int startX = centerX - size/2;
        int startY = centerY - size/2;
        for (int y = startY; y < startY + size; ++y) {
            for (int x = 0; x < y-startY+1; ++x) {
                canvas.setPixel(startX+x, y, symbol);
            }
        }
    }
};

// // Trojkat2 prawo <
class Triangle2 : public Figure {
private:
    int centerX;
    int centerY;
    int size;
    char symbol;

public:
    Triangle2(int x, int y, int r, char sym)
        : centerX(x), centerY(y), size(r), symbol(sym) {}

    virtual void draw(Canvas& canvas) {
        int startX = centerX - size/2;
        int startY = centerY + size/2;
        for (int y = startY; y > startY - size; --y) {
            for (int x = 0; x < startY - y + 1; ++x) {
                canvas.setPixel(startX + x, y, symbol);
            }
        }
    }
};

// Trojkat3 lewo >
class Triangle3 : public Figure {
private:
    int centerX;
    int centerY;
    int size;
    char symbol;

public:
    Triangle3(int x, int y, int r, char sym)
        : centerX(x), centerY(y), size(r), symbol(sym) {}

    virtual void draw(Canvas& canvas) {
        int startX = centerX+size/2;
        int startY = centerY - size/2;
        for (int y = startY; y < startY + size; ++y) {
            for (int x = 0; x < y-startY+1; ++x) {
                canvas.setPixel(startX-x, y, symbol);
            }
        }
    }
};

// Trojkat4 lewo <
class Triangle4 : public Figure {
private:
    int centerX;
    int centerY;
    int size;
    char symbol;

public:
    Triangle4(int x, int y, int r, char sym)
        : centerX(x), centerY(y), size(r), symbol(sym) {}

    virtual void draw(Canvas& canvas) {
        int startX = centerX+size/2;
        int startY = centerY + size/2;
        for (int y = startY; y > startY - size; --y) {
            for (int x = 0; x < startY - y + 1; ++x) {
                canvas.setPixel(startX - x, y, symbol);  // Zmieniamy znak dodatni na ujemny
            }
        }
    }
};

// Klasa reprezentująca punktowe źródło światła
class Light {
private:
    int x;
    int y;
    char symbol;

public:
    Light(int x, int y, char sym) : x(x), y(y), symbol(sym) {}

    void castShadow(Canvas& canvas) {
        int width = canvas.getWidth();
        int height = canvas.getHeight();

        // Ustawienie znaku cienia na całej planszy
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                canvas.setPixel(col, row, symbol);
            }
        }

        // Ustawienie znaku źródła światła na odpowiednich współrzędnych
        canvas.setPixel(x, y, symbol);
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Podaj nazwę pliku konfiguracyjnego jako argument." << std::endl;
        return 1;
    }

    std::string configFilename = argv[1];
    std::ifstream configFile(configFilename);
    if (!configFile.is_open()) {
        std::cout << "Nie można otworzyć pliku konfiguracyjnego: " << configFilename << std::endl;
        return 1;
    }

    int canvasWidth = 0;
    int canvasHeight = 0;
    std::string outputFilename;
    char emptySymbol;
    std::vector<Figure*> figures;
    std::vector<std::unique_ptr<Light>> lights;

    //std::vector<Light> lights;  // Vector przechowujący źródła światła

    std::string line;
    while (std::getline(configFile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;  // Pomijamy puste linie i komentarze
        }

        std::string key;
        std::istringstream iss(line);
        iss >> key;

        if (key == "canvas_width") {
            iss >> canvasWidth;
        } else if (key == "canvas_height") {
            iss >> canvasHeight;
        } else if (key == "output_filename") {
            iss >> outputFilename;
        } else if (key == "empty_symbol") {
            iss >> emptySymbol;
        } else if (key == "figure") {
            std::string figureType;
            int x, y, size;
            char symbol;
            iss >> figureType >> x >> y >> size >> symbol;

            Figure* figure = nullptr;
            if (figureType == "square") {
                figure = new Square(x, y, size, symbol);
            } else if (figureType == "circle") {
                figure = new Circle(x, y, size, symbol);
            }else if (figureType == "triangle1") {
                figure = new Triangle1 (x, y, size, symbol);;
            }else if (figureType == "triangle2") {
                figure = new Triangle2 (x, y, size, symbol);;
            }else if (figureType == "triangle3") {
                figure = new Triangle3 (x, y, size, symbol);;
            }else if (figureType == "triangle4") {
                figure = new Triangle4 (x, y, size, symbol);;
            }

            if (figure) {
                figures.push_back(figure);
            }
        } else if (key == "light") {
            int x, y;
            char symbol;
            iss >> x >> y >> symbol;

            auto light = std::make_unique<Light>(x, y, symbol);
            lights.push_back(std::move(light));

        }
    }

    configFile.close();

    Canvas canvas(canvasWidth, canvasHeight);
    for (const auto& figure : figures) {
        figure->draw(canvas);
    }

    for (const auto& light : lights) {
        light->castShadow(canvas);
    }

    canvas.draw();
    if (!outputFilename.empty()) {
        canvas.saveToFile(outputFilename);
    }

    for (const auto& figure : figures) {
        delete figure;
    }

    return 0;
}
