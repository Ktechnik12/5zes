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
    char getPixel(int x, int y) const {
        return pixels[y][x];
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
    virtual std::unique_ptr<Figure> clone() const = 0;

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
    std::unique_ptr<Figure> clone() const override {
        return std::unique_ptr<Figure>(new Square(*this));
    }

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
    std::unique_ptr<Figure> clone() const override {
        return std::unique_ptr<Figure>(new Square(*this));
    }

    virtual void draw(Canvas& canvas) override {
        for (int y = 0; y < canvas.getHeight(); ++y) {
            for (int x = 0; x < canvas.getWidth(); ++x) {
                if (std::sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY)) <= radius) {
                    canvas.setPixel(x, y, symbol);
                }
            }
        }
    }
};

// Klasa reprezentująca źródło światła
class Light {
private:
    int posX;
    int posY;
    char symbol;
    int intensity;

public:
    Light(int x, int y, char sym, int i) : posX(x), posY(y), symbol(sym), intensity(i) {}

    void castShadow(Canvas& canvas) {
        int canvasWidth = canvas.getWidth();
        int canvasHeight = canvas.getHeight();

        for (int y = 0; y < canvasHeight; ++y) {
            for (int x = 0; x < canvasWidth; ++x) {
                int dx = std::abs(posX - x);
                int dy = std::abs(posY - y);
                int distance = std::sqrt(dx * dx + dy * dy);

                if (distance < intensity) {
                    double brightness = 1.0 - static_cast<double>(distance) / intensity;
                    char pixel = canvas.getPixel(x, y);
                    if (pixel != ' ') {
                        brightness *= 0.5;
                    }
                    canvas.setPixel(x, y, symbol);
                }
            }
        }
    }
    std::unique_ptr<Figure> clone() const {
        return std::unique_ptr<Figure>(new Light(*this));
    }


};

int main() {
    int canvasWidth, canvasHeight;
    std::cout << "Podaj szerokość płótna: ";
    std::cin >> canvasWidth;
    std::cout << "Podaj wysokość płótna: ";
    std::cin >> canvasHeight;

    Canvas canvas(canvasWidth, canvasHeight);

    std::vector<std::unique_ptr<Figure>> figures;

    std::ifstream configFile("config.txt");
    if (!configFile) {
        std::cerr << "Błąd: Nie można otworzyć pliku konfiguracyjnego." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(configFile, line)) {
        std::istringstream iss(line);
        std::string figureType;
        iss >> figureType;

        if (figureType == "Square") {
            int x, y, size;
            char symbol;
            iss >> x >> y >> size >> symbol;
            figures.push_back(std::make_unique<Square>(x, y, size, symbol));
        } else if (figureType == "Circle") {
            int x, y, radius;
            char symbol;
            iss >> x >> y >> radius >> symbol;
            figures.push_back(std::make_unique<Circle>(x, y, radius, symbol));
        } else if (figureType == "Light") {
            int x, y, intensity;
            char symbol;
            iss >> x >> y >> intensity >> symbol;
            figures.push_back(std::unique_ptr<Figure>(new Light(x, y, symbol, intensity)));



        }
    }

    configFile.close();

    for (const auto& figure : figures) {
        figure->draw(canvas);
    }

    for (const auto& figure : figures) {
        if (dynamic_cast<Light*>(figure.get())) {
            auto light = dynamic_cast<Light*>(figure.get());
            light->castShadow(canvas);
        }
    }

    canvas.draw();
    canvas.saveToFile("output.txt");

    return 0;
}
