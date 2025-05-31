//
// Created by xyx on 25-5-31.
//

#include "Photo.h"
#include <fstream>
#include <sstream>
#include <random>

int getRandom(int min, int max) {
    static mt19937 gen(random_device{}());
    uniform_int_distribution<size_t> dis(min, max);
    return dis(gen);
}

#ifdef _WIN32
string Photo::filePath = "..\\.file\\photos\\photopath.txt";
#else
string Photo::filePath = "../.file/photos/photopath.txt";
#endif

vector<QPixmap> Photo::photos;
vector<QPixmap> Photo::backgrounds;
vector<QPixmap> Photo::dialogBackgrounds;
vector<QIcon> Photo::windowIcons;

void Photo::loadPhotos() {
    if (hasPhoto() && hasBackground()) {
        return;
    }
    ifstream in(filePath);
    if (!in) {
        return;
    }
    stringstream ss;
    ss << in.rdbuf();
    string line;

    while (getline(ss, line)) {
        if (line.empty()) {
            continue;
        }
        if (line == "[BACKGROUND]") {
            loadPhotos(backgrounds, ss);
        } else if (line == "[PHOTO]") {
            loadPhotos(photos, ss);
        } else if (line == "[DIALOG-BACKGROUND]") {
            loadPhotos(dialogBackgrounds, ss);
        } else if (line == "[WINDOW-ICON]") {
            loadPhotos(windowIcons, ss);
        }
    }
}

template<typename T>
void Photo::loadPhotos(vector<T> &container, stringstream &in) {
    string line;
    while (getline(in, line)) {
        if (line.empty()) {
            continue;
        }
        if (line == "[END]") {
            return;
        }
        T elem(QString::fromStdString(line));
        if constexpr (is_same_v<T, QPixmap>) {
            if (elem.isNull()) {
                continue;
            }

        }
        if constexpr (is_same_v<T, QIcon>) {
            if (elem.availableSizes().isEmpty()) {
                continue;
            }
        }
        container.push_back(elem);
    }
}

bool Photo::hasPhoto() {
    return !photos.empty();
}

int Photo::getPhotoNumber() {
    return photos.size();
}

QPixmap Photo::getRandomPhoto() {
    if (!hasPhoto()) {
        throw runtime_error("Invalid photo");
    }
    return photos[getRandom(0, getPhotoNumber() - 1)];
}

QPixmap Photo::getBackground() {
    if (!hasBackground()) {
        throw runtime_error("Invalid background");
    }
    return backgrounds[getRandom(0, getBackgroundNumber() - 1)];
}

bool Photo::hasBackground() {
    return !backgrounds.empty();
}

int Photo::getBackgroundNumber() {
    return backgrounds.size();
}

bool Photo::hasDialogBackground() {
    return !dialogBackgrounds.empty();
}

int Photo::getDialogBackgroundNumber() {
    return dialogBackgrounds.size();
}

QPixmap Photo::getDialogBackground() {
    if (!hasDialogBackground()) {
        throw runtime_error("Invalid dialog background");
    }
    return dialogBackgrounds[getRandom(0, getDialogBackgroundNumber() - 1)];
}

bool Photo::hasWindowIcon() {
    return !windowIcons.empty();
}

int Photo::getWindowIconNumber() {
    return windowIcons.size();
}

 QIcon Photo::getWindowIcon() {
    if (!hasWindowIcon()) {
        throw runtime_error("Invalid window icon");
    }
    return windowIcons[getRandom(0, getWindowIconNumber() - 1)];
}

template void Photo::loadPhotos<QPixmap>(vector<QPixmap>&, stringstream&);
template void Photo::loadPhotos<QIcon>(vector<QIcon>&, stringstream&);
